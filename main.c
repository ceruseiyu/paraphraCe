#include "dictionary.h"
#include "markov.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
	Dictionary *dict = createDict();
	addToDict(dict, "key1", "data");
	addToDict(dict, "key2", "data");
	addToDict(dict, "key3", "This one has potatoes");
	Dictionary *second_dict = getFromDict(dict, "key3");
	printf("%s\n", second_dict->start->data);
	deleteDict(dict);
	deleteDict(second_dict);

	Dictionary *third_dict = fileToDict("read.txt");
	printf("%s\n", third_dict->start->next->data);
	Dictionary *search_dict = getFromDict(third_dict, "into");
	printf("%s\n", search_dict->start->data);
	deleteDict(third_dict);
	printf("Segfault nearby!\n");
	deleteDict(search_dict);
	printf("No errors\n");
	return 1;
}
