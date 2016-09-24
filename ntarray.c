#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int ntLen(char** array) {
	if(array == NULL) {
		return -1;
	}

	int i = 0;
	while(array[i] != NULL) {
		i++;
	}
	return i;
}

char** addToArray(char** array, char* data) {
	if(array == NULL) {
		array = {NULL};
	}

	int len = ntLen(array);
	array = realloc(array, sizeof(char*) * (len + 1));

}

char** fileToArray(char* file) {
	FILE* fileptr = fopen(file, "r");
	if(fileptr == NULL) {
		return NULL;
	}

	char** words = malloc(sizeof(char*));
	if(words == NULL) {
		return NULL;
	}
	int wordCount = 0;

	char* curWord = malloc(1);
	if(curWord == NULL) {
		free(words);
		return NULL;
	}
	int charCount = 0;
	char newChar;

	while((newChar = fgetc(fileptr)) != EOF) {
		if(newChar == ' ' || newChar == '\n') {
			if(charCount > 0) {
				words[wordCount] = curWord;
				wordCount++;
				curWord = realloc(curWord, charCount+1);
				curWord[charCount] = '\0';
				words = realloc(words, sizeof(char*) * (wordCount + 1));
				curWord = malloc(1);
				charCount = 0;
			}
		} else{
			curWord = realloc(curWord, charCount+1);
			if(curWord == NULL) {
				return NULL;
			}
			curWord[charCount] = newChar;
			charCount++;
		}
	}
	fclose(fileptr);

	if(charCount > 1) {
		words[wordCount] = curWord;
		wordCount++;
		words = realloc(words, sizeof(char*) * (wordCount + 1));
	}
	words[wordCount] = NULL; // Terminate array with NULL

	return words;
}

char** randKey(char** fileWords) {
  int len = ntLen(fileWords);

  if(len < 1) {
    return NULL;
  }
  int ran = rand() % len;

  char* key[2];
  key[0] = malloc(strlen(fileWords[ran]));
  strcpy(key[0], fileWords[ran]);
  key[1] = NULL;
}
