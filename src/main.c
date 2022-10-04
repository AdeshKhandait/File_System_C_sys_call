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
    // print_bit_DBK(0);
    printf("\nDBK: \n");
    long int temp = search_empty_DBK();
    printf("\n1 : %ld\n",temp);
    Clear_Bit_DBK(temp);
    // print_bit_DBK(0);
    temp = search_empty_DBK();
    printf("\n2 : %ld\n",temp);
    Clear_Bit_DBK(temp);
    // print_bit_DBK(0);
    temp = search_empty_DBK();
    printf("\n3 : %ld\n",temp);
    Clear_Bit_DBK(temp);
    // print_bit_DBK(0);
    temp = search_empty_DBK();
    printf("\n4 : %ld\n",temp);
    Clear_Bit_DBK(temp);
    // print_bit_DBK(0);


    printf("\nInode: \n");
    temp = search_empty_IN();
    printf("\n1 : %ld\n",temp);
    Clear_Bit_IN(temp);
    // print_bit_DBK(0);
    temp = search_empty_IN();
    printf("\n2 : %ld\n",temp);
    Clear_Bit_IN(temp);
    // print_bit_DBK(0);
    temp = search_empty_IN();
    printf("\n3 : %ld\n",temp);
    Clear_Bit_IN(temp);
    // print_bit_DBK(0);
    temp = search_empty_IN();
    printf("\n4 : %ld\n",temp);
    Clear_Bit_IN(temp);
    // print_bit_DBK(0);
}