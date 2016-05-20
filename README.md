# paraphraCe
Markov chain text generator written in C

Produces text using markov chains of a required length, given a file to seed the chains with, with words in sentences seperated by spaces.

To compile with gcc:
gcc dictionary.c main.c -o paraphrace

To run:
./paraphrace file.txt

Generates a string of 50 (default) words in length based on the words and sentence structures of file.txt

./paraphrace file.txt 100

Generates a string of 100 words in length based on the words in file.txt

There must be at least one word to generate and one word in the file being read.
