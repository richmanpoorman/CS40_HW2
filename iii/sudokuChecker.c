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

UArray2_T SudokuChecker_makeBoard(FILE* sudokuFile);

void SudokuChecker_mapBoardElement(int col, int row, UArray2_T board, 
                                   void *data, void *cl);

bool SudokuChecker_checkSudoku(UArray2_T sudokuBoard);

bool SudokuChecker_checkRows(UArray2_T sudokuBoard);

bool SudokuChecker_checkSingleRow(UArray2_T sudokuBoard, int row);

bool SudokuChecker_checkColumns(UArray2_T sudokuBoard);

bool SudokuChecker_checkSingleColumn(UArray2_T sudokuBoard, int col);

bool SudokuChecker_checkBoxes(UArray2_T sudokuBoard);

bool SudokuChecker_checkSingleBox(UArray2_T sudokuBoard, int col, int row);

bool SudokuChecker_setFlag(int current, int *flags);

bool SudokuChecker_hasAllItems(int flag);

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

        UArray2_T board = UArray2_new(width, height, sizeof(char));
        UArray2_map_row_major(board, SudokuChecker_mapBoardElement, reader);

        return board;
}

void SudokuChecker_mapBoardElement(int col, int row, UArray2_T board, 
                                   void *data, void *cl) {
        Pnmrdr_T  reader       = cl;
        char         *valuePointer = UArray2_at(board, col, row);
        unsigned int  nextSquare   = Pnmrdr_get(reader);
        *valuePointer = (char)nextSquare;
        (void) cl;
        (void) data;
}

bool SudokuChecker_checkSudoku(UArray2_T sudokuBoard) {
        if (sudokuBoard == NULL) {
                return false;
        }
        return SudokuChecker_checkRows(sudokuBoard) && 
               SudokuChecker_checkColumns(sudokuBoard) && 
               SudokuChecker_checkBoxes(sudokuBoard);
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