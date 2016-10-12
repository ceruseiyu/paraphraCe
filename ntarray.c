#include "macro.h"
#include "ntarray.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void freeArray(char** array) {
	int len = ntLen(array);
	CHECKVOID(len > 0);
	int i;
	for(i = 0; i < len; i++) {
		free(array[i]);
	}
}

void ntFree(NTArray* array) {
	CHECKVOID(array != NULL);
	freeArray(array->data);
	free(array);
}

char* ntRandom(char** array) {
	CHECK(array != NULL, NULL);
	int len = ntLen(array);
	CHECK(len > 0, NULL);
	int ran = rand() % len;
	return array[ran];
}

int ntLen(char** array) {
	CHECK(array != NULL, -1);
	int i = 0;
	while(array[i] != NULL) {
		i++;
	}
	return i;
}

NTArray* createArray() {
	NTArray* array = malloc(sizeof(NTArray));
	CHECK(array != NULL, NULL);
	array->data = malloc(sizeof(char*));
	if(array->data == NULL) {
		free(array);
		return NULL;
	}
	array->data[0] = NULL;
	return array;
}

int addToArray(NTArray* array, char* data) {
	CHECK(array != NULL, -1);
	int len = ntLen(array->data);
	CHECK(len != -1, -1);
	array->data = realloc(array->data, sizeof(char*) * (len + 2));
	CHECK(array->data != NULL, -1);
	array->data[len] = malloc(strlen(data));
	CHECK(array->data[len] != NULL, -1);
	strcpy(array->data[len], data);
	array->data[len + 1] = NULL;
	return 1;
}

char** fileToArray(char* file) {
	CHECK(file != NULL, NULL);

	FILE* fileptr = fopen(file, "r");
	CHECK(fileptr != NULL, NULL);

	char** words = malloc(sizeof(char*));
	if(words == NULL) {
		fclose(fileptr);
		return NULL;
	}
	int wordCount = 0;

	char* curWord = malloc(1);
	if(curWord == NULL) {
		fclose(fileptr);
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
			} else{
				free(curWord);
				curWord = malloc(1);
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

NTArray* randKey(char** fileWords) {
  int len = ntLen(fileWords) - 1;

  if(len < 2) {
    return NULL;
  }
  int ran = rand() % len;

  NTArray* key = createArray();
	CHECK(key != NULL, NULL);
	CHECK(addToArray(key, fileWords[ran]) != -1, NULL);

	return key;
}

NTArray* buildKey(NTArray* words, int depth) {
	NTArray* key = createArray();
	CHECK(key != NULL, NULL);
	int len = ntLen(words->data) - 1; // subtract 1 for final word position

	int i;
	for (i = 0; i < depth; i++) {
		if(len - i >= 0) {
			addToArray(key, words->data[len - i]);
		}
	}
	CHECK(ntLen(key->data) > 0, NULL);
	return key;
}
