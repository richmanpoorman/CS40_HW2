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
/* 
 *  Name:      : sudoku
 *  Purpose    : Check if the given PGM file is a valid sudoku board
 *  Parameters : (FILE *) The PGM file with the sudoku board to check
 *  Return     : (bool) True if the board is a valid sudoku board, 
 *                      False otherwise
 *  Notes      : Will CRE if no file is given;
 *               Will CRE if the file is not a graymap PGM;
 *               Will CRE if memory can't be allocated
 */
bool sudoku(FILE *sudokuFile);

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

#endif