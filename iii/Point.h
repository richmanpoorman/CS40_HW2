/* 
 *   Name       : Point.h
 *   Assignment : CS40 Homework 2 (iii)
 *   Purpose    : Represents a 2D point
 *   Editors    : Matthew Wong (mwong14), Ivi Fung (sfung02)
 */

typedef struct Point *Point;

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
 *               (int *) A pointer to the column which the function 
 *                       can write to as an output
 *                       [the pointer is used to pass by reference]
 *               (int *) A pointer to the row which the function 
 *                       can write to as an output
 *                       [the pointer is used to pass by reference]
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