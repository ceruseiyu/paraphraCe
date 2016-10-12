#include "paraphrace.h"
#include "ntarray.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  if(argc < 2 || argc > 4) {
    printf("Incorrect number of arguments!\n");
    return -1;
  }
  char* file = argv[1];
  FILE* fileptr = fopen(file, "r");
  if(fileptr == NULL) {
    printf("No file selected!\n");
    return -1;
  }
  fclose(fileptr);

  if(file == NULL) {

  }

  int count;
  int depth;

  if(argc > 2) {
    count = atoi(argv[2]);
    if(count < 1) {
      count = -1;
    }
  } else {
    count = -1;
  }

  if(argc > 3) {
    depth = atoi(argv[3]);
    if(depth < 1) {
      depth = -1;
    }
  } else {
    depth = -1;
  }
  char** array = paraBuild(file, count, depth);
  if(array == NULL) {
    return -1;
  }
  char* str = arrayToStr(array);
  if(str == NULL) {
    freeArray(array);
    return -1;
  }
  printf("%s\n", str);
  free(str);
  freeArray(array);
  return 1;
}
