#ifndef PARAPHRACE_NTARRAY
#define PARAPHRACE_NTARRAY

typedef struct nta {
	char** data;
} NTArray;

int ntLen(char** array);
//char*** addToArray(char*** array, char* data);
NTArray* createArray();
int addToArray(NTArray* array, char* data);
char** fileToArray(char* file);
NTArray* randKey(char** fileWords);
NTArray* buildKey(NTArray* words, int depth);

#endif
