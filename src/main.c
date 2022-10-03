#include<stdio.h>
#include "file_system.h"


__uint64_t arr_bits = 0;

#define SET_BIT(BF, N) BF |= ((__uint64_t)0x0000000000000001 << N)
#define CLR_BIT(BF, N) BF &= ~((__uint64_t)0x0000000000000001 << N)
#define IS_BIT_SET(BF, N) ((BF>>N) & 01)



int main() {

    create_file_system();
    return 0;
}