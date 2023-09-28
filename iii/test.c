
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <pnmrdr.h>
#include "bit2.h"
#include "uarray2.h"
#include "removeBlackEdges.h"
#include "sudokuChecker.h"

/* Functions in the other files */

 /* UArray2 Tests */
void writeUArray2(int col, int row, UArray2_T board, 
                  void *data, void *cl) {
        Pnmrdr_T      reader       = cl;
        unsigned int *valuePointer = UArray2_at(board, col, row);
        unsigned int  nextSquare   = Pnmrdr_get(reader);
        
        *valuePointer = nextSquare;
        (void) data;
}

void printBoardUArray2(int col, int row, UArray2_T board, 
                       void *data, void *cl) 
{
        FILE         *outputFile = cl;
        unsigned int *val        = data;
        fprintf(outputFile, "%i ", *val);
        if (col == UArray2_width(board) - 1) {
                fprintf(outputFile, "\n");
        }
        (void) row;
}

void printBoard(UArray2_T board, FILE *output) 
{
        UArray2_map_row_major(board, printBoardUArray2, output);
}

UArray2_T uarray2Pnmrdr(FILE *input) 
{
        Pnmrdr_T       reader   = Pnmrdr_new(input);
        Pnmrdr_mapdata data     = Pnmrdr_data(reader);

        int            width    = data.width;
        int            height   = data.height;
        
        UArray2_T board = UArray2_new(width, height, sizeof(unsigned int));
        UArray2_map_row_major(board, writeUArray2, reader);
        Pnmrdr_free(&reader);

        return board;
}

void zeroUArray2Test(FILE *input, FILE *output)
{
        UArray2_T zeroTest = UArray2_new(0, 0, 1);
        assert(zeroTest != NULL);
        fprintf(output, "NOTHING THERE \n");
        printBoard(zeroTest, output);
        fprintf(output, "\n");
        UArray2_free(&zeroTest);
        assert(zeroTest == NULL);
        (void) input;
}

void longLongUArray2Test(FILE *input, FILE *output) 
{
        UArray2_T differentTypeTest = UArray2_new(5, 2, sizeof(long long));
        for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 2; j++) {
                        int *val = UArray2_at(differentTypeTest, i, j);
                        *val = i + j;
                }
        }

        printBoard(differentTypeTest, output);
        fprintf(output, "\n");
        UArray2_free(&differentTypeTest);
        assert(differentTypeTest == NULL);
        (void) input;
}

void pnmUArray2Test(FILE *input, FILE *output) 
{
        UArray2_T pnmTest = uarray2Pnmrdr(input);
        
        printBoard(pnmTest, output);
        fprintf(output, "\n");
        UArray2_free(&pnmTest);
}

void boolUArray2Test(FILE *input, FILE *output) 
{
        UArray2_T boolTest = UArray2_new(5, 3, sizeof(bool));
        for (int c = 0; c < 5; c++) {
                for (int r = 0; r < 3; r++) {
                        bool *value = UArray2_at(boolTest, c, r);
                        *value = (r + c) % 2 == 0;
                }
        }

        for (int c = 0; c < UArray2_width(boolTest); c++) {
                for (int r = 0; r < UArray2_height(boolTest); r++) {
                        bool *value = UArray2_at(boolTest, c, r);
                        if (*value) {
                                fprintf(output, "True  ");
                        } else {
                                fprintf(output, "False ");
                        }
                }
                fprintf(output, "\n");
        }
        /* printBoard(boolTest, output); */
        fprintf(output, "\n");
        UArray2_free(&boolTest);
        (void) input;
}

void wrongInputTest(FILE *input, FILE *output) { 
        UArray2_T wrongInput = UArray2_new(10, 10, sizeof(char));
        int *value = UArray2_at(wrongInput, 9, 9);
        *value = 50;
        printBoard(wrongInput, output);
        UArray2_free(&wrongInput);
        fprintf(output, "\n");
        (void) input;
}
void creTests(FILE *input, FILE *output) {

        fprintf(output, "\n");
        (void) input;
}

void freeTest(FILE *input, FILE *output) {
        UArray2_T board = UArray2_new(1, 1, 1);
        
        if (board != NULL) {
                fprintf(output, "Not null before free\n");
        }

        UArray2_free(&board);
        
        if (board == NULL) {
                fprintf(output, "Free is now null\n");
        }
        fprintf(output, "\n");
        (void) input;
}

void uarray2Tests(FILE *input, FILE *output) 
{
        longLongUArray2Test(input, output);
        zeroUArray2Test(input, output);
        boolUArray2Test(input, output);
        wrongInputTest(input, output);
        freeTest(input, output);
        /* pnmUArray2Test(input, output); */
        
}

/* Bit2 Tests */
void writeBit2(int col, int row, Bit2_T bitmap, 
               int data, void *cl) 
{
        Pnmrdr_T      reader       = cl;
        unsigned int  nextSquare   = Pnmrdr_get(reader);
        Bit2_put(bitmap, col, row, nextSquare);

        (void) data;

}
Bit2_T bit2Pnmrdr(FILE *input) 
{
        Pnmrdr_T       reader   = Pnmrdr_new(input);
        Pnmrdr_mapdata data     = Pnmrdr_data(reader);

        int            width    = data.width;
        int            height   = data.height;

        Bit2_T bitmap = Bit2_new(width, height);
        Bit2_map_row_major(bitmap, writeBit2, reader);
        Pnmrdr_free(&reader);

        return bitmap;
}

void printBoardBit2(int col, int row, Bit2_T bitmap, 
                    int data, void *cl) 
{
        FILE *outputFile = cl;
        fprintf(outputFile, "%i ", data);
        if (col == Bit2_width(bitmap) - 1) {
                fprintf(outputFile, "\n");
        }
        (void) row;
}

void bit2Tests(FILE *input, FILE *output) 
{
        Bit2_T pnmTest = bit2Pnmrdr(input);
        
        Bit2_free(&pnmTest);
        (void) output;
}

void unblackedgesTest(FILE *input, FILE *output) 
{
        unblackedges(input, output);
}

void sudokuTests(FILE *input, FILE *output) 
{
        bool sudokuResult = sudoku(input);
        if (sudokuResult) {
                fprintf(output, "Sudoku is valid\n");
        }
        else {
                fprintf(output, "Sudoku is invalid\n");
        }
}

void test(FILE *input, FILE *output) 
{
        /* uarray2Tests(input, output); */
        /* bit2Tests(input, output); */
        sudokuTests(input, output);
        /* unblackedgesTest(input, output); */
}

int main(int argc, char *argv[]) 
{
        assert(argc < 3);
        
        FILE *inputFile  = stdin;
        FILE *outputFile = stdout;
        if (argc >= 2) {
                inputFile = fopen(argv[1], "r");
                assert(inputFile != NULL);
        }

        if (argc >= 3) {
                outputFile = fopen(argv[2], "w");
                assert(outputFile != NULL);
        }

        test(inputFile, outputFile);

        if (argc >= 2) {
                fclose(inputFile);
        }

        if (argc >= 3) {
                fclose(outputFile);
        }
        
}
