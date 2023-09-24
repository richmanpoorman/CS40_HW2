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
 *  Purpose    : Assigns the sudoku board to the 9 x 9 2D array
 *  Parameters : 
 *  Return     : 
 *  Notes      : 
 */
void SudokuChecker_mapBoardElement(int col, int row, UArray2_T board, 
                                   void *data, void *cl);

/* 
 *  Name:      : 
 *  Purpose    : 
 *  Parameters : 
 *  Return     : 
 *  Notes      : 
 */
bool SudokuChecker_checkRows(UArray2_T sudokuBoard);

/* 
 *  Name:      : 
 *  Purpose    : 
 *  Parameters : 
 *  Return     : 
 *  Notes      : 
 */
bool SudokuChecker_checkSingleRow(UArray2_T sudokuBoard, int row);

/* 
 *  Name:      : 
 *  Purpose    : 
 *  Parameters : 
 *  Return     : 
 *  Notes      : 
 */
bool SudokuChecker_checkColumns(UArray2_T sudokuBoard);

/* 
 *  Name:      : 
 *  Purpose    : 
 *  Parameters : 
 *  Return     : 
 *  Notes      : 
 */
bool SudokuChecker_checkSingleColumn(UArray2_T sudokuBoard, int col);

/* 
 *  Name:      : 
 *  Purpose    : 
 *  Parameters : 
 *  Return     : 
 *  Notes      : 
 */
bool SudokuChecker_checkBoxes(UArray2_T sudokuBoard);

/* 
 *  Name:      : 
 *  Purpose    : 
 *  Parameters : 
 *  Return     : 
 *  Notes      : 
 */
bool SudokuChecker_checkSingleBox(UArray2_T sudokuBoard, int col, int row);

/* 
 *  Name:      : 
 *  Purpose    : 
 *  Parameters : 
 *  Return     : 
 *  Notes      : 
 */
bool SudokuChecker_setFlag(int current, int *flags);

/* 
 *  Name:      : 
 *  Purpose    : 
 *  Parameters : 
 *  Return     : 
 *  Notes      : 
 */
bool SudokuChecker_hasAllItems(int flag);

/* Implementation */
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
        if (sudokuBoard == NULL) {
                return false;
        }
        return SudokuChecker_checkRows(sudokuBoard) && 
               SudokuChecker_checkColumns(sudokuBoard) && 
               SudokuChecker_checkBoxes(sudokuBoard);
}

void SudokuChecker_mapBoardElement(int col, int row, UArray2_T board, 
                                   void *data, void *cl) {
        Pnmrdr_T  reader       = cl;
        char         *valuePointer = UArray2_at(board, col, row);
        unsigned int  nextSquare   = Pnmrdr_get(reader);
        *valuePointer = nextSquare;
        (void) cl;
        (void) data;
}

bool SudokuChecker_checkRows(UArray2_T sudokuBoard) {
        for (int row = 0; row < 9; row++) {
                bool rowValid = SudokuChecker_checkSingleRow(
                                        sudokuBoard, row);
                if (!rowValid) {
                        return false;
                }
        }
        return true;
}

bool SudokuChecker_checkColumns(UArray2_T sudokuBoard) {
        for (int col = 0; col < 9; col++) {
                bool colValid = SudokuChecker_checkSingleColumn(
                                        sudokuBoard, col);
                if (!colValid) {
                        return false;
                }
        }
        return true;
}

bool SudokuChecker_checkBoxes(UArray2_T sudokuBoard) {
        for (int row = 0; row < 9; row += 3) {
                for (int col = 0; col < 9; col += 3) {
                        bool boxValid = SudokuChecker_checkSingleBox(
                                                sudokuBoard, col, row);
                        if (!boxValid) {
                                return false;
                        }
                }
                
        }
        return true;
}

bool SudokuChecker_checkSingleRow(UArray2_T sudokuBoard, int row) {
        int flags = 0;
        int width = UArray2_width(sudokuBoard);
        for (int col = 0; col < width; col++) {
                int *value = UArray2_at(sudokuBoard, col, row);
                bool isValid = SudokuChecker_setFlag(*value, &flags);
                if (!isValid) {
                        return false;
                }
        }
        
        return SudokuChecker_hasAllItems(flags);
}

bool SudokuChecker_checkSingleColumn(UArray2_T sudokuBoard, int col) {
        int flags = 0;
        int height = UArray2_height(sudokuBoard);
        for (int row = 0; row < height; row++) {
                int *value = UArray2_at(sudokuBoard, col, row);
                bool isValid = SudokuChecker_setFlag(*value, &flags);
                if (!isValid) {
                        return false;
                }
        }
        
        return SudokuChecker_hasAllItems(flags);
}

bool SudokuChecker_checkSingleBox(UArray2_T sudokuBoard, int col, int row) {
        int flags = 0;
        for (int squareIndex = 0; squareIndex < 9; squareIndex++) {
                int currRow = row + squareIndex / 3;
                int currCol = col + squareIndex % 3;
                int *value  = UArray2_at(sudokuBoard, currCol, currRow);
                
                bool isValid = SudokuChecker_setFlag(*value, &flags);
                if (!isValid) {
                        return false;
                }
        }
        
        return SudokuChecker_hasAllItems(flags);
}

bool SudokuChecker_setFlag(int value, int *flags) {
        if (value < 1 || value > 9) {
                return false;
        }
        int currFlag = 1 << (value - 1);
        if ((currFlag & (*flags)) > 0) {
                return false;
        }
        *flags += currFlag;
        return true;
}

bool SudokuChecker_hasAllItems(int flags) {
        
        int allFlagsActive = (1 << 9) - 1;
        return flags == allFlagsActive;
}