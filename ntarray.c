#include "macro.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int ntLen(char** array) {
	CHECK(array != NULL, -1);

	int i = 0;
	while(array[i] != NULL) {
		i++;
	}
	return i;
}

char** addToArray(char** array, char* data) {
	CHECK(data != NULL, NULL);

	if(array == NULL) {
		array = malloc(sizeof(char*));
		CHECK(array != NULL, NULL);
		array[0] = NULL;
	}

	int len = ntLen(array);

	array = realloc(array, sizeof(char*) * (len + 1));
	CHECK(array != NULL, NULL);

	array[len] = malloc(strlen(data));
	CHECK(array[len] != NULL, NULL);

	strcpy(array[len], data);
	return array;
}

char** fileToArray(char* file) {
	CHECK(file != NULL, NULL);

	FILE* fileptr = fopen(file, "r");
	CHECK(fileptr != NULL, NULL);

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
				if(curWord == NULL){
					free(words);
					return NULL;
				}

				curWord[charCount] = '\0';
				words = realloc(words, sizeof(char*) * (wordCount + 1));
				if(words == NULL) {
					free(curWord);
					return NULL;
				}

				curWord = malloc(1);
				if(curWord == NULL) {
					free(words);
					return NULL;
				}

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

  char** key = malloc(sizeof(char*)* 2);
  key[0] = malloc(strlen(fileWords[ran]));
  strcpy(key[0], fileWords[ran]);
  key[1] = NULL;

	return key;
}