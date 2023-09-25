/* 
 *   Name       : sudokuChecker.c
 *   Assignment : CS40 Homework 2 (iii)
 *   Purpose    : Check if a given sudoku board is solved
 *   Editors    : Matthew Wong (mwong14), Ivi Fung (sfung02)
 */

#include "uarray2.h"
#include <stdio.h>
#include <pnmrdr.h>
#include <assert.h>
#include <stdbool.h>

/* 
 *  Name:      : SudokuChecker_makeBoard
 *  Purpose    : Turns the given PGM file sudoku board into an UArray2_T board
 *  Parameters : (FILE *) The opened file with the sudoku board
 *  Return     : (UArray2_T) A 9x9 2D array with the sudoku board information
 *  Notes      : Will CRE if it is not a graymap PGM;
 *               If max value isn't 9 or the PGM size is not (9, 9)
 *                      it will return NULL;
 *               Client needs to free the UArray2_T and close the file
 */
UArray2_T SudokuChecker_makeBoard(FILE* sudokuFile);

/* 
 *  Name:      : SudokuChecker_checkSudoku
 *  Purpose    : Checks if the given 2D Array is a valid sudoku board
 *  Parameters : (UArray2_T) The sudoku board as a 2D array
 *  Return     : (bool) True if the sudoku board is valid, false otherwise
 *  Notes      : Assumes that the 2D array given is a 9 x 9 with max value 9
 */
bool SudokuChecker_checkSudoku(UArray2_T sudokuBoard);


/* 
 *  Name:      : SudokuChecker_mapBoardElement
 *  Purpose    : Mapping function that assigns the elements of the 
 *               sudoku board to the 9 x 9 2D array
 *  Parameters : (int) Column of current element;
 *               (int) Row of current element;
 *               (UArray2_T) The current sudoku board;
 *               (void *) Pointer to the data stored at (col, row);
 *               (void *) Pointer to accumulator;
 *  Return     : None
 *  Notes      : Assumes that the function is only used with 
 *                      UArray2_map_row_major
 */
void SudokuChecker_mapBoardElement(int col, int row, UArray2_T board, 
                                   void *data, void *cl);

UArray2_T SudokuChecker_makeBoard(FILE* sudokuFile) {
        Pnmrdr_T       reader   = Pnmrdr_new(sudokuFile);
        Pnmrdr_mapdata data     = Pnmrdr_data(reader);

        Pnmrdr_maptype fileType = data.type;
        int            width    = data.width;
        int            height   = data.height;
        int            maxSize  = data.denominator;
        assert(fileType == Pnmrdr_gray);
        
        if (maxSize != 9 || width != 9 || height != 9) {
                return NULL;
        }
        UArray2_T board = UArray2_new(width, height, sizeof(unsigned int));
        UArray2_map_row_major(board, SudokuChecker_mapBoardElement, reader);
        Pnmrdr_free(&reader);

        return board;
}

bool SudokuChecker_checkSudoku(UArray2_T sudokuBoard) {
        /* 
         *  There are 9 different rows, columns, and boxes
         *  This is the initialization for the "sets" for each
         *      row, column, and box
         *  We use bitwise operators to check if it is seen
         *  (Each binary place represents a different digit 1-9)
         */
        int rowFlags[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        int colFlags[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        int boxFlags[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        
        int height = UArray2_height(sudokuBoard);
        int width  = UArray2_width(sudokuBoard);
        for (int row = 0; row < height; row++) {
                for (int col = 0; col < width; col++) {
                        int *value = UArray2_at(sudokuBoard, col, row);
   
                        /* Checks if value is in range */
                        if (*value < 1 || *value > 9) {
                                return false;
                        }

                        /* Gets the corresponding box */
                        int box = (row / 3) * 3 + col / 3;
                        int flag = 1 << (*value - 1);
                        
                        /*  
                         *  Checks if the value has been already found 
                         *  in the corresponding row, column, or box
                         */
                        if ((flag & rowFlags[row]) > 0 || 
                            (flag & colFlags[col]) > 0 || 
                            (flag & boxFlags[box]) > 0) {
                                return false;
                        }

                        /* If it has found it, mark as found */
                        rowFlags[row] += flag;
                        colFlags[col] += flag;
                        boxFlags[box] += flag;
                }
        }

        /* 
         *  All of digits 1-9 should have been used, so check that
         *      all of the sets contain all of the elements
         */ 
        int allFlagged = (1 << 9) - 1;
        for (int flagIndex = 0; flagIndex < 9; flagIndex++) {
                if (rowFlags[flagIndex] != allFlagged || 
                    colFlags[flagIndex] != allFlagged || 
                    boxFlags[flagIndex] != allFlagged) {
                        return false;
                }
        }

        /* If there are no problems, then the sudoku is solved */
        return true;
}

void SudokuChecker_mapBoardElement(int col, int row, UArray2_T board, 
                                   void *data, void *cl) {
        Pnmrdr_T      reader       = cl;
        unsigned int *valuePointer = UArray2_at(board, col, row);
        unsigned int  nextSquare   = Pnmrdr_get(reader);
        
        *valuePointer = nextSquare;
        (void) cl;
        (void) data;
}