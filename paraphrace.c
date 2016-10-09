#include "ntarray.h"
#include "dictionary.h"
#include <stdlib.h>
#define DEFAULT_LENGTH 50
#define DEFAULT_DEPTH 3

char* paraBuild(char* file, int count, int depth) {
  initDict();
  char** fileWords = fileToArray(file);
  if(fileWords == NULL || ntLen(fileWords) < 1) {
    return NULL;
  }

  char** key = randKey(fileWords);
  if(key == NULL || ntLen(key) < 1) {
    return NULL;
  }

  DictItem* dict = buildDict(fileWords, key);
  if(dict == NULL) {
    return NULL;
  }

  char** para = NULL;
  if(addToArray(&para, pickRandWord(dict)) == -1) {
    return NULL;
  }

  ntFree(&key);
  deleteDict(&dict);

  int i;
  for(i = 1; i < count; i++) {
    key = buildKey(para, depth);
    if(key == NULL || ntLen(key) < 1) {
      return NULL;
    }

    dict = buildDict(fileWords, key);
    if(dict == NULL) {
      return NULL;
    }

    if(addToArray(&para, pickRandWord(dict)) == -1) {
      return NULL;
    }

    ntFree(&key);
    deleteDict(&dict);
  }


  return "success\n";
}
