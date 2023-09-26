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
