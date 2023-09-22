/* 
 *   Name       : sudokuChecker.h
 *   Assignment : CS40 Homework 2 (iii)
 *   Purpose    : Check if a given sudoku board is solved
 *   Editors    : Matthew Wong (mwong14), Ivi Fung (sfung02)
 */

#include "uarray2.h"
#include <stdio.h>

#ifndef SUDOKU_H_
#define SUDOKU_H_

UArray2_T SudokuChecker_makeBoard(FILE* sudokuFile);

int SudokuChecker_checkSudoku(UArray2_T sudokuBoard);

#endif