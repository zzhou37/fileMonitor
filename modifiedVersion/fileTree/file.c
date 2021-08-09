#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#include "file.h"

void copyPointer(fileNode** p1, fileNode** p2){
    *p1 = *p2;
}
fileTree* newFileTree() {
    fileTree *ft = calloc(1, sizeof(fileTree));
    memset(ft, 0, sizeof(fileTree));
    return ft;
}

fileNode* newFileNode(int type, int exist, char* name, char* MD5, char* path){
    fileNode* fn = calloc(1, sizeof(fileNode));
    fn->type=type;
    fn->exist = exist;
    fn->name = calloc(strlen(name)+1, sizeof(char));
    fn->MD5 = calloc(strlen(MD5)+1, sizeof(char));
    fn->path = calloc(strlen(path)+1, sizeof(char));
    strcpy(fn->name, name);
    strcpy(fn->MD5, MD5);
    strcpy(fn->path, path);
    return fn;
}

void printFileNode(fileNode* fn, int depth){
    printf("%*sType:%d Exist:%d Name:%s MD5:%s Path:%s\n\n", depth, " ",fn->type, fn->exist, fn->name, fn->MD5, fn->path);
}

void printFileTree(fileNode * fn, int depth) {
    for (fileNode * curr = fn; curr != NULL; curr = curr->next) {
        if (curr->type == 0) {
            printf("DirName:%s fullPath:%s level:%d\n",curr->name, curr->path, depth/4);
            printFileTree(curr->item, depth+4);
        } else {
            printFileNode(curr, depth);
        }
    }
}

int countToken(char *path) {
    char pathCp[strlen(path) + 1];
    strcpy(pathCp, path);
    int count = 0;
    for (char *token = strtok(pathCp, "/"); token != NULL; token = strtok(NULL, "/")) {
        count++;
    }
    return count;
}

//return null if the dir doesn't exist
void appendNode(fileNode** fn, fileNode* item) {
    if(*fn==NULL){
        *fn = item;
        return;
    }
    fileNode * curr = *fn;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = item;
}

fileNode* findNode(fileNode* fn, char* name, int type){
    if(fn == NULL) return NULL;
    fileNode * curr = fn;
    while(curr != NULL){
        if(strcmp(curr->name, name) == 0 && curr->type == type){
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

static int defineType(int i, int count, int type){
    if(i<count-1 || type==0) return 0;
    else return 1;
}

void addFileNode(fileTree * ft, int type, char* name, char* MD5, char* path){
    char pathCp[strlen(path)];
    strcpy(pathCp, path);

    int count = countToken(path);
    int i = 0;

    char fullDirPath[260] = "";

    fileNode** curr;
    for(char *token = strtok(pathCp, "/"); token != NULL; token = strtok(NULL, "/")){
        //if the token is root
        //get the path for dir
        strcat(fullDirPath, token);
        strcat(fullDirPath,"/");
        //printf("%s\n",dirPath);
        if(strcmp(token, ".") == 0) {
            curr = &ft->head;
        }
        //try to find the token
        //if the token exist, cd into it
        else if(findNode(*curr, token, defineType(i,count,type)) != NULL){
            //if it is a dir, then cd
            if(i<count-1) curr = &findNode(*curr,token, 0)->item;
        }
        //if the token doesn't exist, creat and append it to the list
        else{
            //if it is not last token, add a dir and cd into it
            if(i<count-1){
                fullDirPath[strlen(fullDirPath)-1] = 0;
                fileNode* item = newFileNode(0, 1, token, "null", fullDirPath);
                strcat(fullDirPath,"/");
                appendNode(curr, item);
                curr = &findNode(*curr, token, 0)->item;
            }
            //if it is last token, creat a node with input type and add it
            else if(i == count-1){
                fileNode* item;
                if(type == 0) item = newFileNode(type, 1, token, "null", path);
                if(type == 1) item = newFileNode(type, 1, token, MD5, path);
                appendNode(curr, item);
            }
        }
        i++;
    }
}
fileNode* traceNode(char* path, int type){
    return NULL;
}

void updateFile(int type, char* name, char* MD5, char* path){
    //search fileNode and return fileNode
    //if file exist
        //compare MD5
            //if MD5 have not chang
                //do nothing
            //if MD5 changed
                //update MD5
                //print update statue
    //if file doesn't exist
        //add file into

}
static fileNode* testNewFileNode(){
    fileNode* a = newFileNode(1, 1,"file 0", "0", "./path0");
    return a;
}

int main() {
    fileTree *ft = newFileTree();
    addFileNode(ft, 0, "dir", "null", "./dir");
    addFileNode(ft, 1, "file3", "3", "./dir/file3");
    addFileNode(ft, 1, "file4", "4", "./dir/file4");
    addFileNode(ft, 0, "dir1", "null", "./dir/dir1");
    addFileNode(ft, 1, "file5", "5", "./dir/dir1/dir2/dir3/file5");
    addFileNode(ft, 1, "file3.1", "3.1", "./dir/dir1/dir2/file3.1");
    addFileNode(ft, 0, "dir2", "null", "./dir/dir2");
    printf("print tree now:\n");
    //printFileNode(ft->head);
    //printFileNode(ft->head->item);
    //printf("%d\n",ft->head->item->next->next->type);
    printFileTree(ft->head, 0);
    return 0;
}
