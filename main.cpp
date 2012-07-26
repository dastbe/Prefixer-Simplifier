// Main file for rewriting infix expressions as prefix
// and simplifying them
//
// Created by: David Bell
// April 26th, 2012

#include "expr_tree.h"
#include "visitor.h"
#include "stdio.h"
#include "stdlib.h"
#include "cstring"

// For communicating with Bison/Flex
extern int yyparse();
extern "C" FILE *yyin;

ExprTree *et;
// void printTree(ExprTree*);
// void simplifyTree(ExprTree*);

int main(int argc, char** argv)
{
	bool simplify = false;
	char *input_file = NULL;

	// Set up state according to CL arguments
	if (argc < 2) // Not enough arguments
	{
		printf("%s: (-r) FILENAME\n",argv[0]);
		exit(1);
	} else if (argc == 2) // Just a file name
	{
		input_file = argv[1];
	} else if (argc == 3) // optional parameter and file
	{
		if (strcmp(argv[1],"-r")) // Not a valid parameter
		{
			printf("Invalid argument %s\n%s: (-r) FILENAME\n",argv[1],argv[0]);
			exit(1);
		}

		simplify = true;
		input_file = argv[2];
	} else // Too many arguments!
	{
		printf("Too many arguments\n%s: (-r) FILENAME\n",argv[0]);
		exit(1);
	}

	// Try and open our file argument
	FILE *myfile = fopen(input_file, "r");

	if (!myfile) // File does not exist
	{
		printf("File %s does not exist!\n",input_file);
		exit(1);
	}

	yyin = myfile; // Sets lex to use our file as input

	yyparse(); // Creates ExprTree

	if (simplify) // Simplify the tree 
		simplifyTree(et);

	// Print our tree in prefix notation
	printTree(et);
	printf("\n");
}

