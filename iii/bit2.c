/* 
 *   Name       : bit2.h
 *   Assignment : CS40 Homework 2 (iii)
 *   Purpose    : Represents a 2-dimensional array of bits
 *   Editors    : Matthew Wong (mwong14), Ivi Fung (sfung02)
 */

#include <bit.h>
#include <mem.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Bit2_T {
    int width;
    int height;
    Bit_T data;
} *Bit2_T;


/* 
 *  Name:      : Bit2_getKey
 *  Purpose    : Maps the 2D array indicies to the 1D array index
 *  Parameters : (Bit2_T) The Bit2_T to get the index in the 1D array;
 *               (int) The column of the data point in the 2D array;
 *               (int) The row of the data point in the 2D array;
 *  Return     : (int) The index in the underlying 1D array
 *  Notes      : Meant only for private use (not client use);
 *               Will CRE if bit2 is NULL
 */
int Bit2_getKey(Bit2_T bit2, int col, int row);

/* 
 *  Name:      : Bit2_isInBounds
 *  Purpose    : Checks if the values are within the bounds of the 2D array
 *  Parameters : (Bit2_T) The Bit2_T to check within the bounds of;
 *               (int) The column of the data point in the 2D array;
 *               (int) The row of the data point in the 2D array;
 *  Return     : (bool) If the data is within the bounds or not
 *  Notes      : Meant only for private use (not client use);
 *               Will CRE if bit2 is NULL
 */
bool Bit2_isInBounds(Bit2_T bit2, int col, int row);

/* 
 *  Name:      : Bit2_new
 *  Purpose    : Create a rectangular 2D array that stores bits
 *  Parameters : (int) The height of the 2D array;
 *               (int) The width of the 2D array;
 *  Return     : (Bit2_T) An array that can hold the bits
 *  Notes      : Will CRE on failure to allocate memory
 *               Will CRE if width, height, or size are negative
 */
Bit2_T Bit2_new(int width, int height);

/* 
 *  Name:      : Bit2_free
 *  Purpose    : Free up the memory the 2D array after the client is done
 *  Parameters : (Bit2_T *) The pointer to the 2D array to free up
 *  Return     : None
 *  Notes      : Sets the pointer data to NULL so no accidental references
 *               can be made
 */
void Bit2_free(Bit2_T *bit2Pointer);

/* 
 *  Name:      : Bit2_get
 *  Purpose    : Get the bit at (col, row)
 *  Parameters : (Bit2_T) The 2D array where the data is stored
 *               (int) The column that the data is located at in the 2D array;
 *               (int) The row that the data is located 
 *  Return     : (int) Returns 0 if the bit is 0 and 1 if the bit is 1
 *  Notes      : Does not check if data has previously been set there or not;
 *               only gives the pointer to the data
 *               Undefined behavior before setting the pointer to (col, row)
 *               to any value;
 *               CRE when out-of-bounds 
 */
int Bit2_get(Bit2_T bit2, int col, int row);

/* 
 *  Name:      : Bit2_put
 *  Purpose    : Set the bit at (col, row) 
 *               for setting and getting
 *  Parameters : (Bit2_T) The 2D array where the data is at
 *               (int) The column that the data is located at in the 2D array;
 *               (int) The row that the data is loacated 
 *               (int) The value to set the bit to
 *  Return     : None
 *  Notes      : Does not check if data has previously been set there or not;
 *               only gives the pointer to the data
 *               Undefined behavior before setting the pointer to (col, row)
 *               to any value;
 *               CRE when out-of-bounds
 *               CRE when data is not 0 or 1
 */
void Bit2_put(Bit2_T bit2, int col, int row, int data);

/* 
 *  Name:      : Bit2_width
 *  Purpose    : Get the width of the 2D array
 *  Parameters : (Bit2_T) The 2D array to get the width of
 *  Return     : (int) The width of the given 2D array
 *  Notes      : Width can't be changed after being initially set
 */
int Bit2_width(Bit2_T bit2);

/* 
 *  Name:      : Bit2_height
 *  Purpose    : Get the height of the 2D array
 *  Parameters : (Bit2_T) The 2D array to get the height of
 *  Return     : (int) The height of the given 2D array
 *  Notes      : Height can't be changed after being initially set
 */
int Bit2_height(Bit2_T bit2);

/* 
 *  Name:      : Bit2_map_col_major
 *  Purpose    : Use the apply function on each bit of the 2D array going
 *               column by column, from top of the column to the 
 *               bottom of the column
 *  Parameters : (Bit2_T) The 2D array with the bits;
 *               (function) the function to apply to every bit, which has
 *                  parameters that the column, row, 2D array,
 *                  the data value, and a pointer to an accumulator
 *                  variable
 *               (void *) The pointer to the accumulator in its initial state
 *  Return     : None
 *  Notes      : This is a mapping function
 */
void Bit2_map_col_major(Bit2_T bit2, 
                        void (*apply)(int, int, Bit2_T, int, void *), 
                        void *cl);

/* 
 *  Name:      : Bit2_map_row_major
 *  Purpose    : Use the apply function on each bit of the 2D array going
 *               row by row, from left of the row to the right of the row
 *  Parameters : (Bit2_T) The 2D array with the bits;
 *               (function) the function to apply to every bit, which has
 *                  parameters that the column, row, 2D array,
 *                  the data value, and a pointer to an accumulator
 *                  variable
 *               (void *) The pointer to the accumulator in its initial state
 *  Return     : None
 *  Notes      : This is a mapping function
 */
void Bit2_map_row_major(Bit2_T bit2, 
                        void (*apply)(int, int, Bit2_T, int, void *), 
                        void *cl);


/* Implementations */
int Bit2_getKey(Bit2_T bit2, int col, int row) {
        assert(bit2 != NULL);
        return row * Bit2_width(bit2) + col; 
}

bool Bit2_isInBounds(Bit2_T bit2, int col, int row) {
        assert(bit2 != NULL);
        return row >= 0 && col >= 0 && 
               row < Bit2_height(bit2) && col < Bit2_width(bit2);
}

Bit2_T Bit2_new(int width, int height) {
        assert(width >= 0);
        assert(height >= 0);
        assert(size > 0);

        Bit2_T new2DArray = ALLOC(sizeof(*new2DArray));
        Bit_T  data       = UArray_new(width * height, size);

        assert(new2DArray != NULL);

        new2DArray -> width  = width;
        new2DArray -> height = height;
        new2DArray -> data   = data; 

        return new2DArray;
}

void Bit2_free(Bit2_T *bit2Pointer) {
        assert(bit2Pointer  != NULL);
        assert(*bit2Pointer != NULL);

        UArray_free(&((*bit2Pointer) -> data));
        FREE(*bit2Pointer);
        *bit2Pointer = NULL;
}

int Bit2_get(Bit2_T bit2, int col, int row) {
        assert(bit2 != NULL);
        return Bit_get(bit2 -> data, Bit2_getKey(bit2, col, row));
}

void Bit2_put(Bit2_T bit2, int col, int row, int data) {
        assert(bit2 != NULL);
        return Bit_set(bit2 -> data, Bit2_getKey(bit2, col, row), data);
}

int Bit2_width(Bit2_T bit2) {
        assert(bit2 != NULL);
        return bit2 -> width;
}

int Bit2_height(Bit2_T bit2) {
        assert(bit2 != NULL);
        return bit2 -> height;
}

void Bit2_map_col_major(Bit2_T bit2, 
                        void (*apply)(int, int, Bit2_T, int, void *), 
                        void *cl) {
        assert(bit2 != NULL);
        int height = Bit2_height(bit2);
        int width  = Bit2_width(bit2);

        for (int col = 0; col < width; col++) {
                for (int row = 0; row < height; row++) {
                        int value = Bit2_get(bit2, col, row);
                        apply(col, row, bit2, value, cl);
                }
        }
}

void Bit2_map_row_major(Bit2_T bit2, 
                        void (*apply)(int, int, Bit2_T, int, void *), 
                        void *cl) {
        assert(bit2 != NULL);
        int height = Bit2_height(bit2);
        int width  = Bit2_width(bit2);

        for (int row = 0; row < height; row++) {
                for (int col = 0; col < width; col++) {
                        int value = Bit2_get(bit2, col, row);
                        apply(col, row, bit2, value, cl);
                }
        }
}