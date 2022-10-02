#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "file_system.h"

// Basic Information
// 1GB = 1000000000
// Empty = -1
// Occupied = -2


// ---------------------------------------------------------------Variables----------------------------------------------------------

// Define the MetaData Variables

// Size of the HDD
long int sizeHDD;

// Size of Start Block
long int size_Start_Block;

// HDD - Size of Start_Block
long int sizeHDD_StartBlock;

// Size of the MetaData
long int size_MetaData;

// Size of the DiskBlock
long int size_Disk_Block;

// MetaData + DiskBlock
long int size_MetaData_DiskBlock;

// Number of MetaData
long int num_MetaData;

// Number of the DiskBlock
long int num_DiskBlock;

// Availabel Space in Disk
long int Space;


//---------------------------------------------------------------Declaring the Structs----------------------------------------------
struct StartBlock SB;
struct MetaData *Inodes;
struct Disk_Block *DBK;



//-------------------------------------------------------------------Functions-------------------------------------------------------

// Creating the file System
void create_file_system() {

//-------------------------------------------------------------------File System Size-------------------------------------------------------
    printf("Enter the File Size in GB: ");
    sizeHDD = input_long_int();

    //Converting into bytes
    sizeHDD = sizeHDD*1000000000;
    printf("sizeHDD: %ld\n",sizeHDD);

    // Size of the StartBlock
    size_Start_Block = sizeof(struct StartBlock);
    printf("Size of the StartBlock: %ld\n",size_Start_Block);

    // sizeHDD - StartBlock
    sizeHDD_StartBlock = sizeHDD - size_Start_Block;
    printf("sizeHDD: %ld\n",sizeHDD);

    // Size of the MetaData
    size_MetaData = sizeof(struct MetaData);
    printf("Size of the MetaData: %ld\n", size_MetaData);

    // Size of the Disk_Block
    size_Disk_Block = sizeof(struct Disk_Block);
    printf("Size of the Disk_Block: %ld\n", size_Disk_Block);

    // MetaData + Disk_Block
    size_MetaData_DiskBlock = size_MetaData + size_Disk_Block;
    printf("MetaData + Disk_Block: %ld\n", size_MetaData_DiskBlock);

    // Number of the MetaData
    num_MetaData = sizeHDD_StartBlock / size_MetaData_DiskBlock;
    printf("Number of the MetaData: %ld\n", num_MetaData);

    // Number of the Disk_Block
    num_DiskBlock = num_MetaData;
    printf("Number of the Disk_Block: %ld\n", num_DiskBlock);



//-------------------------------------------------------------------SettingUPMetaData-------------------------------------------------------

}

