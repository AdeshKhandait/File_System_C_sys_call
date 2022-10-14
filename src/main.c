#include<stdio.h>
#include "file_system.h"


__uint64_t arr_bits = 0;

#define SET_BIT(BF, N) BF |= ((__uint64_t)0x0000000000000001 << N)
#define CLR_BIT(BF, N) BF &= ~((__uint64_t)0x0000000000000001 << N)
#define IS_BIT_SET(BF, N) ((BF>>N) & 01)



int main() {

    create_file_system();
    create_empty_bit_map_DBK();
    create_empty_bit_map_IN();
    insert_file();
    read_file(0);
    // read_Inode(0);
    // for (int i = 0; i < 14; i++)
    // {
    //     // print_bit_DBK(0);
    //     read_DBK(i);
    // }
    
    return 0;
}