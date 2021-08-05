#ifndef FILE_OBJECT
#define FILE_OBJECT

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

#include "md5mit.h"

typedef struct fileInfoObj{
	char* fileName;
	char* MD5;
	char* path;
}fileInfo;

typedef struct arrayListObj{
	int num;
	fileInfo* head;
	fileInfo* array;
}arrayList;

void printFileInfo(fileInfo* f);

fileInfo* newFileInfo(char* fileName, char* MD5, char* path);

void freeFileInfo(fileInfo* f);

fileInfo* testNewFileInfo();

void printArrayList(arrayList* al);

arrayList* newArrayList();

void add(arrayList* al, fileInfo* element);

#endif
