typedef struct Point *Point;

Point Point_new(int col, int row);

void Point_get(Point point, int *col, int *row);

void Point_free(Point *point);