#include "dictionary.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
	Dictionary *dict = createDict();
	addToDict(dict, "key1", "data");
	addToDict(dict, "key2", "data");
}