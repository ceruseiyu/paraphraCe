#include "ntarray.h"
#include "dictionary.h"
#include <stdlib.h>
#define DEFAULT_LENGTH 50
#define DEFAULT_DEPTH 3

char* paraBuild(char* file, int count, int depth) {
  initDict();
  char** fileWords = fileToArray(file);
  if(fileWords == NULL) {
    return NULL;
  }

  char** key = randKey(fileWords, depth);
  if(key == NULL) {
    return NULL;
  }
}

char* paraBuild(char* file, int count) {
  paraBuild(file, count, DEFAULT_DEPTH);
}

char* paraBuild(char* file) {
  paraBuild(file, DEFAULT_LENGTH, DEFAULT_DEPTH);
}
