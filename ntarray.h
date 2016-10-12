#ifndef PARAPHRACE_NTARRAY
#define PARAPHRACE_NTARRAY

typedef struct nta {
	char** data;
} NTArray;

char* ntRandom(char** array);
void freeArray(char** array);
void ntFree(NTArray* array);

int ntLen(char** array);

NTArray* createArray();
int addToArray(NTArray* array, char* data);
char** fileToArray(char* file);

NTArray* randKey(char** fileWords);
NTArray* buildKey(NTArray* words, int depth);

#endif
