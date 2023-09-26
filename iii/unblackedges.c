/* 
 *   Name       : unblackedges.c
 *   Assignment : CS40 Homework 2 (iii)
 *   Purpose    : Removes black edges from given bitmap
 *   Editors    : Matthew Wong (mwong14), Ivi Fung (sfung02)
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "removeBlackEdges.h"
#include "bit2.h"

/* 
 *  Name:      : unblackedges
 *  Purpose    : Remove the black edges of the given file
 *  Parameters : (FILE *) The PGM file with the original image;
 *               (FILE *) The output file to write to
 *  Return     : None
 *  Notes      : Will CRE if no file is given;
 *               Will CRE if the file is not a PBM;
 *               Will CRE if there is a memory issue;
 *               Will CRE if couldn't make the bitmap;
 *               Will CRE if memory can't be allocated
 */

void unblackedges(FILE *bitmapFile, FILE *outputFile) {
        assert(bitmapFile != NULL);
        Bit2_T bitmap = RemoveBlackEdges_makeBitmap(bitmapFile);
        assert(bitmap != NULL);

        RemoveBlackEdges_removeEdges(bitmap);
        assert(bitmap != NULL);

        RemoveBlackEdges_writeBitmap(outputFile, bitmap);

        Bit2_free(&bitmap);

}

int main(int argc, char *argv[]) {
        assert(argc < 3);
        
        FILE *inputFile = stdin;
        if (argc == 2) {
                inputFile = fopen(argv[1], "r");
                assert(inputFile != NULL);
        }

        unblackedges(inputFile, stdout);

        if (argc == 2) {
                fclose(inputFile);
        }

        
}
