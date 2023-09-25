/* 
 *   Name       : removeBlackEdges.c
 *   Assignment : CS40 Homework 2 (iii)
 *   Purpose    : Removes black edges
 *   Editors    : Matthew Wong (mwong14), Ivi Fung (sfung02)
 */

#include "bit2.h"
#include "Point.h"
#include <seq.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <pnmrdr.h>

/* 
 *  Name:      : RemoveBlackEdges_makeBitmap
 *  Purpose    : Turns the given PBM file bitmap into an Bit2_T bitmap
 *  Parameters : (FILE *) The opened file with the bitmap
 *  Return     : (Bit2_T) A 2D bitmap with the bitmap
 *  Notes      : Will CRE if it is not a bitmap PBM;
 *               Client needs to free the Bit2_T and close the file
 */
Bit2_T RemoveBlackEdges_makeBitmap(FILE* bitmapFile);

/* 
 *  Name:      : RemoveBlackEdges_removeEdges
 *  Purpose    : Removes the 1 bits (black) on the edges,
 *               as well as the 1 bits
 *               adjacent to any of the removed bits
 *  Parameters : (Bit2_T) The bitmap in a Bit2_T before processing 
 *  Return     : None
 *  Notes      : The bitmap is edited in-place
 */
void RemoveBlackEdges_removeEdges(Bit2_T bitmap);

/* 
 *  Name:      : RemoveBlackEdges_writeBitMap
 *  Purpose    : Writes the given bitmap to the given output file
 *               adjacent to any of the removed bits
 *  Parameters : (Bit2_T) The bitmap in a Bit2_T before processing 
 *  Return     : None
 *  Notes      : Assumes the outputFile is open, and the bitmap is processed
 */
void RemoveBlackEdges_writeBitmap(FILE *outputFile, Bit2_T bitmap);

/* 
 *  Name:      : RemoveBlackEdges_writeBitMap
 *  Purpose    : Writes the given bitmap to the given output file
 *               adjacent to any of the removed bits
 *  Parameters : (Bit2_T) The bitmap in a Bit2_T before processing 
 *  Return     : None
 *  Notes      : Assumes the outputFile is open, and the bitmap is processed;
 *               Assumes that the function is only used with 
 *                      Bit2_map_row_major
 */
void RemoveBlackEdges_mapBitElement(int col, int row, Bit2_T bitmap, 
                                    int data, void *cl);

/* 
 *  Name:      : RemoveBlackEdges_dfs
 *  Purpose    : Does a depth first search for adjacent black pixels
 *               and turns them white, propogating to remove 
 *               "black edge" pixels
 *  Parameters : (Bit2_T) The bitmap as a 2D array that has the black edges
 *                        that need to be removed;
 *               (int) The column of the starting position to start searching;
 *               (int) The row of the starting position to start searching
 *  Return     : None
 *  Notes      : Alters the bitmap inplace
 *               Assumes that the starting (col, row) bit is a bit that is 
 *                      black along the edge of the image
 */
void RemoveBlackEdges_dfs(Bit2_T bitmap, int col, int row);

/* 
 *  Name:      : RemoveBlackEdges_mapBitToFile
 *  Purpose    : A mapping function that writes the bitmap to a file
 *  Parameters : (int) The column position of the bit to read from the bitmap;
 *               (int) The row position of the bit to read from the bitmap;
 *               (Bit2_T) The bitmap that is being read from with the 
 *                        black edges removed;
 *               (int) The bit data located at (col, row) in the bitmap;
 *               (void *) The pointer to the opened output file to print to
 *  Return     : None
 *  Notes      : 
 */
void RemoveBlackEdges_mapBitToFile(int col, int row, Bit2_T bitmap, 
                                   int data, void *cl);

/* Implementation */
Bit2_T RemoveBlackEdges_makeBitmap(FILE* bitmapFile) {
        Pnmrdr_T       reader   = Pnmrdr_new(bitmapFile);
        Pnmrdr_mapdata data     = Pnmrdr_data(reader);

        Pnmrdr_maptype fileType = data.type;
        int            width    = data.width;
        int            height   = data.height;
        assert(fileType == Pnmrdr_bit);
        assert(width != 0 && height != 0);

        Bit2_T bitmap = Bit2_new(width, height);
        Bit2_map_row_major(bitmap, RemoveBlackEdges_mapBitElement, 
                              reader);
        Pnmrdr_free(&reader);

        return bitmap;
}

void RemoveBlackEdges_removeEdges(Bit2_T bitmap) {
        int width  = Bit2_width(bitmap);
        int height = Bit2_height(bitmap);
        for (int col = 0; col < width; col++) {
                if (Bit2_get(bitmap, col, 0) == 1) {
                        RemoveBlackEdges_dfs(bitmap, col, 0);
                }

                if (Bit2_get(bitmap, col, height - 1) == 1) {
                        RemoveBlackEdges_dfs(bitmap, col, height - 1);
                }
        }

        for (int row = 0; row < height; row++) {
                if (Bit2_get(bitmap, 0, row) == 1) {
                        RemoveBlackEdges_dfs(bitmap, 0, row);
                }

                if (Bit2_get(bitmap, width - 1, row) == 1) {
                        RemoveBlackEdges_dfs(bitmap, width - 1, row);
                }
        }
}

void RemoveBlackEdges_writeBitmap(FILE *outputFile, Bit2_T bitmap) {
        assert(outputFile != NULL);
        assert(bitmap != NULL);
        int width  = Bit2_width(bitmap);
        int height = Bit2_height(bitmap);

        fprintf(outputFile, "P1\n\n");
        fprintf(outputFile, "%i %i\n", width, height);
        Bit2_map_row_major(bitmap, RemoveBlackEdges_mapBitToFile, outputFile);
}

void RemoveBlackEdges_mapBitElement(int col, int row, Bit2_T bitmap, 
                                      int data, void *cl) {
        Pnmrdr_T     reader  = cl;
        unsigned int nextBit = Pnmrdr_get(reader);

        Bit2_put(bitmap, col, row, nextBit);

        (void) cl;
        (void) data;
}

void RemoveBlackEdges_dfs(Bit2_T bitmap, int col, int row) {
        int width = Bit2_width(bitmap);
        int height = Bit2_height(bitmap);

        Seq_T dfs  = Seq_new(width + height);

        Seq_addhi(dfs, Point_new(col, row));
        Bit2_put(bitmap, col, row, 0);

        while (Seq_length(dfs) > 0) {
                Point curr = Seq_remhi(dfs);
                Point_get(curr, &col, &row);
                Point_free(&curr);

                /* Write the current element to 0 */

                if (col > 0 && Bit2_get(bitmap, col - 1, row) == 1) {
                        Bit2_put(bitmap, col - 1, row, 0);
                        Seq_addhi(dfs, Point_new(col - 1, row));
                }

                if (col < width - 1 && Bit2_get(bitmap, col + 1, row) == 1) {
                        Bit2_put(bitmap, col + 1, row, 0);
                        Seq_addhi(dfs, Point_new(col + 1, row));
                }

                if (row > 0 && Bit2_get(bitmap, col, row - 1) == 1) {
                        Bit2_put(bitmap, col, row - 1, 0);
                        Seq_addhi(dfs, Point_new(col, row - 1));
                }

                if (row < height - 1 && Bit2_get(bitmap, col, row + 1) == 1) {
                        Bit2_put(bitmap, col, row + 1, 0);
                        Seq_addhi(dfs, Point_new(col, row + 1));
                }
                
        }

        Seq_free(&dfs);

}

void RemoveBlackEdges_mapBitToFile(int col, int row, Bit2_T bitmap, 
                                   int data, void *cl) {
        int width        = Bit2_width(bitmap);
        FILE *outputFile = cl;

        fprintf(outputFile, "%i ", data);
        if (col == width - 1) {
                fprintf(outputFile, "\n");
        }

        (void) row;
        
}