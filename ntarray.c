#include "macro.h"
#include "ntarray.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//TODO NTFree - A function that frees an entire NTArray

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
	array->data = malloc(sizeof(char*));
	array->data[0] = NULL;
	return array;
}

int addToArray(NTArray* array, char* data) {
	CHECK(array != NULL, -1);
	int len = ntLen(array->data);
	CHECK(len != -1, -1);
	array->data = realloc(array->data, sizeof(char*) * (len + 2));
	array->data[len] = malloc(strlen(data));
	strcpy(array->data[len], data);
	array->data[len + 1] = NULL;
	return 1;
}

/*char*** addToArray(char*** array, char* data) {
	CHECK(data != NULL, NULL);

	if(*array == NULL) {
		*array = malloc(sizeof(char*));
		CHECK(*array != NULL, NULL);
		*array[0] = NULL;
	}

	int len = ntLen(*array);

	*array = realloc(*array, sizeof(char*) * (len + 2));
	CHECK(*array != NULL, NULL);

	*array[len] = malloc(strlen(data));
	CHECK(*array[len] != NULL, NULL);

	strcpy(*array[len], data);
	*array[len + 1] = NULL;
	return array;
} */

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

NTArray* randKey(char** fileWords) {
  int len = ntLen(fileWords);

  if(len < 1) {
    return NULL;
  }
  int ran = rand() % len;

  NTArray* key = createArray();
	addToArray(key, fileWords[ran]);

	return key;
}


//Take in ntarray of any size, build key to the size of depth if possible.
// Less is okay if not
NTArray* buildKey(NTArray* words, int depth) {
	NTArray* key = createArray();
	int len = ntLen(words->data) - 1; // subtract 1 for final word position

	int i;
	for (i = 0; i < depth; i++) {
		if(len - i >= 0) {
			addToArray(key, words->data[len - i]);
		}
	}
	return key;
}
