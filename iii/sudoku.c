/* 
 *   Name       : sudoku.c
 *   Assignment : CS40 Homework 2 (iii)
 *   Purpose    : EXIT_SUCCESS if it is a valid sudoku, 
 *                EXIT_FAILURE if it is not a valid sudoku
 *   Editors    : Matthew Wong (mwong14), Ivi Fung (sfung02)
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "sudokuChecker.h"


int main(int argc, char *argv[]) {
        assert(argc < 3);
        
        FILE *inputFile = stdin;
        if (argc == 2) {
                inputFile = fopen(argv[1], "r");
                assert(inputFile != NULL);
        }

        bool isValidSudoku = sudoku(inputFile);

        if (argc == 2) {
                fclose(inputFile);
        }

        if (isValidSudoku) {
                exit(EXIT_SUCCESS);
        }
        else {
                exit(EXIT_FAILURE);
        }
        
}
