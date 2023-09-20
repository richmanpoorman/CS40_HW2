

#ifndef UARRAY2_H_
#define UARRAY2_H_

typedef struct UArray2_T *UArray2_T;

UArray2_T UArray2_new(int width, int height, int size);

void UArray2_free(UArray2_T *uArray2Pointer);

void *UArray2_at(UArray2_T uArray2, int col, int row);

int UArray2_width(UArray2_T uArray2);

int UArray2_height(UArray2_T uArray2);

int UArray2_size(UArray2_T uArray2);

void UArray2_map_col_major(UArray2_T uArray2, 
                           void (*apply)(int, int, UArray2_T, void *, void *), 
                           void *cl);

void UArray2_map_row_major(UArray2_T uArray2, 
                           void (*apply)(int, int, UArray2_T, void *, void *), 
                           void *cl);


#endif