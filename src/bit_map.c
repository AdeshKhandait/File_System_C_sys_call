#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include "file_system.h"


// Assumation
// 1 = Free DiskBlock
// 0 = Occupied DiskBlock
// Zero Indexing
#define BIT_BLOCK 64


#define SET_BIT(BF, N) BF |= ((__uint64_t)0x0000000000000001 << N)
#define CLR_BIT(BF, N) BF &= ~((__uint64_t)0x0000000000000001 << N)
#define IS_BIT_SET(BF, N) ((BF>>N) & 01)


//-------------------------------------------------------------------DISK BLOCK-------------------------------------------------------

// setting the all bit to  empty
void set_all_bit_DBK() {
    for (long int i = 0; i < map_size_DBK; i++)
    {
        BitMap_DBK[i] = -1; 
    }
}

// Check is all the bit Set 
void check_all_set_DBK() {

    for (long int i = 0; i < map_size_DBK; i++)
    {
        if (BitMap_DBK[i] != -1)
        {
            perror("\n%d Block is unset\n");
            exit(1);
        }
    }
    printf("\nAll the Disk Block Bits are Set!\n");
}

// Bit 64 Bit Block
void print_bit_DBK(long int number) {

    printf("Number %ld: ",number);
    for (int i = 0; i < 64; i++)
    {
        printf("%ld,",IS_BIT_SET(BitMap_DBK[number],i));        
    }
    printf("\n");
}

// Empty Bit Map
void create_empty_bit_map_DBK() {

// Find the Number Bit Require
    map_size_DBK = num_DiskBlock/64 + 1;

    BitMap_DBK = malloc(sizeof(long int)*map_size_DBK);
    
    // Setting all the Bits 1
    set_all_bit_DBK();
    
    // Check if all th bits are set
    check_all_set_DBK();
}

// Search Empty Bit
long int search_empty_DBK() {

    for (int i = 0; i < map_size_DBK; i++)
    {
        if (BitMap_DBK[i] == 0)
        {
            continue;
        }
        else
        {
            // printf("Case 2:\n");
            for (int j = 0; j < 64; i++)
            {
                if (IS_BIT_SET(BitMap_DBK[i],j))
                {
                    // printf("Case 3:\n");
                    return i+j;
                }
                else{
                    // printf("Case 4:\n");
                    continue;
                }
            }
            
        }
        
    }
    printf("\nDisk is Full\n");
}

// Setting the bit with Block
void Clear_Bit_DBK(long int number) {

    long int Index = number/BIT_BLOCK;
    printf("Index: %ld\n",Index);
    long int BIT_NUM = number % BIT_BLOCK;
    printf("BIT: %ld\n",BIT_NUM);
    CLR_BIT(BitMap_DBK[Index],BIT_NUM);
}

//-------------------------------------------------------------------INODES-------------------------------------------------------

// setting the all bit to  empty
void set_all_bit_IN() {
    for (long int i = 0; i < map_size_IN; i++)
    {
        BitMap_IN[i] = -1; 
    }
}

// Check is all the bit Set 
void check_all_set_IN() {

    for (long int i = 0; i < map_size_IN; i++)
    {
        if (BitMap_IN[i] != -1)
        {
            perror("\n%d Block is unset\n");
            exit(1);
        }
    }
    printf("\nAll the Inodes Bits are Set!\n");
}

// Bit 64 Bit Block
void print_bit_IN(long int number) {

    printf("Number %ld: ",number);
    for (int i = 0; i < 64; i++)
    {
        printf("%ld,",IS_BIT_SET(BitMap_IN[number],i));        
    }
    printf("\n");
}

// Empty Bit Map
void create_empty_bit_map_IN() {

// Find the Number Bit Require
    map_size_IN = num_MetaData/BIT_BLOCK + 1;

    BitMap_IN = malloc(sizeof(long int)*map_size_IN);
    
    // Setting all the Bits 1
    set_all_bit_IN();
    
    // Check if all th bits are set
    check_all_set_IN();
}

// Search Empty Bit
long int search_empty_IN() {

    for (int i = 0; i < map_size_IN; i++)
    {
        if (BitMap_IN[i] == 0)
        {
            continue;
        }
        else
        {
            // printf("Case 2:\n");
            for (int j = 0; j < BIT_BLOCK; i++)
            {
                if (IS_BIT_SET(BitMap_IN[i],j))
                {
                    // printf("Case 3:\n");
                    return i+j;
                }
                else{
                    // printf("Case 4:\n");
                    continue;
                }
            }
            
        }
        
    }
    printf("\nDisk is Full\n");
}

// Setting the bit with Block
void Clear_Bit_IN(long int number) {

    long int Index = number/BIT_BLOCK;
    printf("Index: %ld\n",Index);
    long int BIT_NUM = number % BIT_BLOCK;
    printf("BIT: %ld\n",BIT_NUM);
    CLR_BIT(BitMap_IN[Index],BIT_NUM);
}
