
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "sudokuChecker.h"

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
