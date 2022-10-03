#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h> 
#include<errno.h> 
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
    printf("sizeHDD - StartBlock: %ld\n",sizeHDD_StartBlock);

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

//Inserting the Data into Start Block
    SB.size_HDD = sizeHDD;
    printf("SB.size_HDD: %ld\n",SB.size_HDD);
    SB.start_MetaData = size_Start_Block;
    printf("SB.start_MetaData: %ld\n",SB.start_MetaData);
    SB.start_Data_Block = num_MetaData*size_MetaData;
    printf("SB.start_Data_Block: %ld\n",SB.start_Data_Block);
    SB.size_block = BLOCKSIZE;
    printf("SB.size_block: %d\n",SB.size_block);


// Creating the Array in of MetaData
Inodes = malloc(sizeof(struct MetaData)*num_MetaData);

    // Inserting the data into MetaData
    for (int i = 0; i < num_MetaData; i++)
    {
        Inodes[i].file_number = -1;
        Inodes[i].file_size = -1;
        Inodes[i].first_Block = -1;
        strcpy(Inodes[i].file_name,"Empty");
    }
    
// Creating the Array of the MetaData
DBK = malloc(sizeof(struct Disk_Block)*num_DiskBlock);

    // Inserting the Data into DiskBlock
    for (int i = 0; i < num_MetaData; i++)
    {
        DBK[i].Next_Data_Block = -1;
        DBK[i].pos = 0;
    }


//-------------------------------------------------------------------Creating the File System-------------------------------------------------------

    create_file();
    sync_file_system();
    printf("\nFile_System_Successfully_Created!!\n");
}

void sync_file_system(){

// Opening the File
    int file = open_file();

// Writing the Start Block
int wrt_SB = write(file,&SB,size_Start_Block);
    if ( wrt_SB == size_Start_Block)
    {
        printf("\nStart Block Successfully Written!\n");
    }
    else{
        perror("Error in Writing the Start Block!\n");
    }

// Writing the MetaData
    long int wrt_IN = 0;
    
    for (long int i = 0; i < num_DiskBlock; i++)
    {
       long int temp2 =  write(file,&Inodes[i],size_MetaData);
        wrt_IN = wrt_IN + temp2;
    }
    
    if (wrt_IN == size_MetaData*num_MetaData)
    {
        printf("\nMetaData Successfully Written!\n");
    }
    else{
        perror("Error in Writing the MetaData!\n");
    }   
    
// Writing the Disk_Block
    long int wrt_DSK = 0;
    for (long int i = 0; i < num_DiskBlock; i++)
    {
       long int temp2 =  write(file,&DBK[i],size_Disk_Block);
        wrt_DSK = wrt_DSK + temp2;
    }
    
    if (wrt_DSK == size_Disk_Block*num_DiskBlock)
    {
        printf("\nDiskBlock Successfully Written!\n");
    }
    else{
        perror("Error in Writing the DiskBlock!\n");
    }

}

