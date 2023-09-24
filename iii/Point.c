#include <stdlib.h>
#include <assert.h>
#include <mem.h>


typedef struct Point {
        int col;
        int row;
} *Point;

Point Point_new(int col, int row);

void Point_get(Point point, int *col, int *row);

void Point_free(Point *point);

Point Point_new(int col, int row) {
        Point point = ALLOC(sizeof(*point));
        assert(point != NULL);
        point -> col = col;
        point -> row = row;
        return point;
}

void Point_get(Point point, int *col, int *row) {
        *col = point -> col;
        *row = point -> row;
}

void Point_free(Point *point) {
        FREE(*point);
        *point = NULL;
}