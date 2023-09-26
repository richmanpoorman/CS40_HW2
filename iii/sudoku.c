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

/* 
 *  Name:      : sudoku
 *  Purpose    : Check if the given PGM file is a valid sudoku board
 *  Parameters : (FILE *) The PGM file with the sudoku board to check
 *  Return     : (bool) True if the board is a valid sudoku board, 
 *                      False otherwise
 *  Notes      : Will CRE if no file is given;
 *               Will CRE if the file is not a graymap PGM;
 *                Will CRE if memory can't be allocated
 */
bool sudoku(FILE *sudokuFile) {
        assert(sudokuFile != NULL);
        UArray2_T board = SudokuChecker_makeBoard(sudokuFile);
        if (board == NULL) {
                return false;
        }
        
        bool check = SudokuChecker_checkSudoku(board);
        UArray2_free(&board);
        return check;
}

int main(int argc, char *argv[]) {
        assert(argc < 3);
        
        FILE *inputFile = stdin;
        if (argc == 2) {
                inputFile = fopen(argv[1], "r");
                assert(inputFile != NULL);
        }

        bool sudokuResult = sudoku(inputFile);

        if (argc == 2) {
                fclose(inputFile);
        }

        if (sudokuResult) {
                exit(EXIT_SUCCESS);
        }
        else {
                exit(EXIT_FAILURE);
        }
        
}
