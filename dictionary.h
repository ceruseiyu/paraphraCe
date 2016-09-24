#ifndef DICTIONARY_DEFINED
#define DICTIONARY_DEFINED

typedef struct itemtype {
	struct itemtype* next;
	char* data;
	int weight;
} DictItem;

void initDict();

DictItem* createDict(char* d, int w);

int addToDict(DictItem* dict, char* d, int w);

void deleteDict(DictItem* d);

int getDictWeight(DictItem* d);

char* pickRandWord(DictItem* d);

int ntLen(char** array);

int calcWeight(int w);

char** fileToArray(char* file);

DictItem* buildDict(char** words, char** keys);
/**
int addToDict(DictItem* dict, char* key, char* data);

int dictLength(DictItem* dict);

DictItem* getFromDict(DictItem* dict, char key[]);

DictItem* fileToDict(char* file);
void addFileToDict(DictItem* dict, char* file);*/


#endif
