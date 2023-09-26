/* 
 *   Name       : Point.c
 *   Assignment : CS40 Homework 2 (iii)
 *   Purpose    : Represents a 2D point
 *   Editors    : Matthew Wong (mwong14), Ivi Fung (sfung02)
 */

#include <stdlib.h>
#include <assert.h>
#include <mem.h>


typedef struct Point {
        int col;
        int row;
} *Point;

/* 
 *  Name:      : Point_new
 *  Purpose    : Make a new point representing a position (col, row)
 *  Parameters : (int) The column of the point;
 *               (int) The row of the point
 *  Return     : (Point) A Point struct representing the location
 *  Notes      : Throws an CRE if memory can not be allocated
 */
Point Point_new(int col, int row);

/* 
 *  Name:      : Point_get
 *  Purpose    : Get the column and row of the given point by writing 
 *               to the given inputs which are passed by reference
 *  Parameters : (Point) The point to get the position (col, row) from
 *               (int *) A pointer to hold the value of the point's column. 
 *                       The function can write to this as output, so that
 *                       the column value is accesible to the client
 *               (int *) A pointer to hold the value of the point's row. 
 *                       The function can write to this as output, so that
 *                       the row value is accesible to the client
 *  Return     : None
 *  Notes      : col and row are where the output of the data is, so
 *               column and row are passed by reference;
 *               Will CRE if the point, col reference, or row reference
 *                      is null
 */
void Point_get(Point point, int *col, int *row);

/* 
 *  Name:      : Point_free
 *  Purpose    : Frees the memory of the point object, and sets the reference
 *               to null after freeing it
 *  Parameters : (Point *) The pointer to the Point object to free
 *  Return     : None
 *  Notes      : Asserts if the pointer is null, or the Point to free is null;
 *               Makes the pointer given null
 */
void Point_free(Point *point);

Point Point_new(int col, int row) {
        Point point = ALLOC(sizeof(*point));
        assert(point != NULL);
        point -> col = col;
        point -> row = row;
        return point;
}

void Point_get(Point point, int *col, int *row) {
        assert(point != NULL);
        assert(col != NULL);
        assert(row != NULL);
        *col = point -> col;
        *row = point -> row;
}

void Point_free(Point *point) {
        assert(point != NULL);
        assert(*point != NULL);
        FREE(*point);
        *point = NULL;
}