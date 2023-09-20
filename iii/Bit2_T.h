#import <bit.h>

#ifndef BIT2_H_
#define BIT2_H_

typedef struct Bit2_T *Bit2_T;

Bit2_T Bit2_new(int width, int height, int size);

void Bit2_free(Bit2_T *bit2Pointer);

void *Bit2_get(Bit2_T bit2, int col, int row);

void *Bit2_put(Bit2_T bit2, int col, int row, int data);

int Bit2_width(Bit2_T bit2);

int Bit2_height(Bit2_T bit2);

void Bit2_map_col_major(Bit2_T bit2, 
                        void (*apply)(int, int, Bit2_T, int, int, void *), 
                        void *cl);

void Bit2_map_row_major(Bit2_T bit2, 
                        void (*apply)(int, int, Bit2_T, int, int, void *), 
                        void *cl);


#endif