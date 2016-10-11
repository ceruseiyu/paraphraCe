#include "ntarray.h"
#include "dictionary.h"
#include <stdlib.h>
#include <stdio.h>
#define DEFAULT_LENGTH 50
#define DEFAULT_DEPTH 3

char* paraBuild(char* file, int count, int depth) {
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
    key = buildKey(para, depth);

    dict = buildDict(fileWords, key);

    addToArray(para, pickRandWord(dict));
    //printf(para->data[i]);

  }


  return "success\n";
}
