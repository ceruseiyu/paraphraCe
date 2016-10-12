# paraphraCe
Markov chain text generator written in C

Generates text of a given length by finding words that come after sequences of words of varying depth, applying weight values proportionally to them and then choosing one at random.

Comes with the library for the application, makefile and an example program in main.

## Using the example program
After compiling, the example program takes in commands like so:

`./paraphrace filename wordcount depth`

With filename being the relative text file the program will read from, wordcount the number of words for the program to output and depth the amount of words the program will check in the past to assign weighting values to possible new words.

For example:

`./paraphrace test.txt 100 5`

If you only specify the filename, or the filename and the wordcount, it will set the default values and still run. The default values are 50 for wordcount and 3 for depth.

## Using the library
You'll neeed to include in the paraphrace library in your program:

`#include "paraphrace.h"`

This comes with 2 functions, paraBuild and arrayToStr.

### paraBuild
paraBuild() creates a null terminated array of character pointers when given a file name to read, wordcount and depth. If you leave wordcount and depth as 0 or -1, it will use the default values for those parameters.

For example:

`paraBuild("test.txt", -1, -1);
parabuild(fileName, 100, 20);`

The output of a null terminated array of character pointers makes it easy to iterate over and perform changes to the text if desired, but in order to print it, we'll need to turn it back into a string.

### arrayToStr
Outputs a string in the form of an array of characters when given a null terminated array of character pointers. Can be directly fed the output of paraBuild.

For example:
`arrayToStr(paraBuild("test.txt", -1, -1));`
