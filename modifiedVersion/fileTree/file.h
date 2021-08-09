#ifndef FILE_OBJECT
#define FILE_OBJECT

typedef struct fileNodeObj{
	int type; //0 for dir; 1 for file
	int exist; 
	char* name;
	char* MD5;
	char* path;
	struct fileNodeObj* next;
	struct fileNodeObj* pre;
	struct fileNodeObj* item;
}fileNode;

typedef struct fileTreeObj{
	int num;
	fileNode* head;
}fileTree;
void copyPointer(fileNode** p1, fileNode** p2);

fileTree* newFileTree();

fileNode* newFileNode(int type, int exist, char* name, char* MD5, char* path);

void printFileNode(fileNode* fn, int depth);

void printFileTree(fileNode* fn, int depth);

int countToken(char* path);

void appendNode(fileNode** fn, fileNode *item);

fileNode* findNode(fileNode* fn, char* name, int type);

void addFileNode(fileTree * ft, int type, char* name, char* MD5, char* path);

fileNode* traceNode(char* path, int type);

#endif
