#include "ntarray.h"
#include "dictionary.h"
#include "macro.h"
#include <stdlib.h>
#include <string.h>
#define DEFAULT_LENGTH 50
#define DEFAULT_DEPTH 3

char** paraBuild(char* file, int count, int depth) {
  if(count < 1) {
    count = DEFAULT_LENGTH;
  }

  if(depth < 1) {
    depth = DEFAULT_DEPTH;
  }
  initDict();
  char** fileWords = fileToArray(file);
  if(fileWords == NULL || ntLen(fileWords) < 1) {
    return NULL;
  }
  NTArray* key = randKey(fileWords);
  DictItem* dict = buildDict(fileWords, key);
  if(dict == NULL) {
    return NULL;
  }
  NTArray* para = createArray();
  addToArray(para, pickRandWord(dict));
  int i;
  for(i = 1; i < count; i++) {
    deleteDict(&dict);
    ntFree(key);
    key = buildKey(para, depth);
    CHECK(key != NULL, NULL);
    dict = buildDict(fileWords, key);
    addToArray(para, pickRandWord(dict));
  }
  deleteDict(&dict);
  ntFree(key);
  freeArray(fileWords);
  char** paradata = para->data;
  free(para);
  return paradata;
}

char* arrayToStr(char** array) {
	if(array == NULL) {
		return NULL;
	}
	int len = ntLen(array);
	CHECK(len > 0, NULL);
	char* string = malloc(strlen(array[0]));
	CHECK(string != NULL, NULL);
	strcpy(string, array[0]);

	int i;
	for(i = 1; i < len; i++) {
		string = realloc(string, strlen(string) + strlen(array[i]) + 2);
		CHECK(string != NULL, NULL);
		strcat(string, " ");
		strcat(string, array[i]);
	}

	return string;
}
