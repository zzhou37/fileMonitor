#include "file.h"

void printFileInfo(fileInfo* f){
	printf("Name:%s;\nPath:%s;\nMD5:%s;\n\n", f->fileName, f->path, f->MD5);
}

fileInfo* newFileInfo(char* fileName, char* MD5, char* path){
	char* fnCP = calloc(strlen(fileName)+1, sizeof(char));
	//printf("fileName:%lu\n", strlen(fileName));
	char* MD5Cp = calloc(strlen(MD5)+1, sizeof(char));
	//printf("MD5:%lu\n", strlen(MD5));
	char* pathCp = calloc(strlen(path)+1, sizeof(char));
	//printf("path:%lu\n", strlen(path));

	strcpy(fnCP, fileName);
	strcpy(MD5Cp, MD5);
	strcpy(pathCp, path);
	fileInfo* fi = malloc(sizeof(fileInfo));
	fi->fileName = fnCP;
	fi->MD5 = MD5Cp;
	fi->path = pathCp;
	return fi;
}

void freeFileInfo(fileInfo* f){
	memset(f->fileName,'0',strlen(f->fileName)*sizeof(char));
	free(f->fileName);
	memset(f->MD5,'0',strlen(f->MD5)*sizeof(char));
	free(f->MD5);
	memset(f->path,'0',strlen(f->path)*sizeof(char));
	free(f->path);
	memset(f,'0',sizeof(fileInfo));
	free(f);
}

fileInfo* testNewFileInfo(){
	char fileName[5] = "file";
	char MD5[3] = "110";
	char path[5] = "./dir";
	fileInfo* fp = newFileInfo(fileName, MD5, path);
	return fp;
}

void printArrayList(arrayList* al){
	for(int i = 0; i < al->num; i++){
		printFileInfo(&(al->array[i])); //al->array[i] is the fileInfo itself
	}
}

arrayList* newArrayList(){
	arrayList* al = calloc(1, sizeof(arrayList));
	al->num = 0;
	return al;
}

void add(arrayList* al, fileInfo* element){
	if(al->num == 0){
		al->array = calloc(1, sizeof(*element));
	}
	else{
		al->array = realloc(al->array, (al->num+1)*sizeof(*element));
	}
	al->array[al->num] = *element; //al->array[i] store fileInfo itself
	al->num++;
}

/*int main(){
	//fileInfo* fp = testNewFileInfo();
	//printFileInfo(fp);
	//freeFileInfo(fp);
	//printFileInfo(fp);
	arrayList* al = newArrayList();
	fileInfo* a = newFileInfo("file 0", "0", "/path0");
	fileInfo* b = newFileInfo("file 1", "1", "./path1");
	add(al, a);
	add(al, b);
	printArrayList(al);
	return 0;
}*/
