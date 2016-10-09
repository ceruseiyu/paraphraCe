#ifndef PARAPHRACE_NTARRAY
#define PARAPHRACE_NTARRAY

void ntFree(char*** ntArray);
int ntLen(char** array);
int addToArray(char*** array, char* data);
char** fileToArray(char* file);
char** randKey(char** fileWords);
char** buildKey(char** fileWords, int depth);

#endif
