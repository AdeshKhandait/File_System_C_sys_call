// Meta Information about ther File System
// Assuming Zero Indexing

#define BLOCKSIZE 1024
#define NAME 256

//-------------------------------------------------------------------Structures-------------------------------------------------------
// StartBlock -> Stores Information
// - Size of File System
// - Start of MetaData
// - Start of Data_Block 
struct StartBlock
{
    // Size of the File system 
    long int size_HDD;
    long int start_MetaData;
    long int start_Data_Block;
    int size_block;
};

// MetaData -> Stores the Stores Information
// 1.File Size
// 2.First Data Block
// 3.File Number
// 4.File Name

struct MetaData
{
    long int file_size;
    long int first_Block;
    long int file_number;
    char file_name[NAME];
};

// Disk_Block
struct Disk_Block
{
    long int Next_Data_Block;
    int pos;
    char Data[BLOCKSIZE];
};


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

//----------------------------------------Declaration of the File System Operation---------------------------------------------------

// Creating the File System
void create_file_system();

// Sync the File System
void sync_file_system();

// Format the File system
void format_file_system();

// --------------------------------------------------IO_Open_Close-----------------------------------------------------------------

long int input_long_int();

void create_file();

int open_file();


//-------------------------------------------------------------------BitMap-------------------------------------------------------


// DISK BLOCK
long int map_size_DBK;
long int *BitMap_DBK;

// Set all the Bit
void set_all_bit_DBK();

// Create the Bit map
void create_empty_bit_map_DBK();

// Bit 64 Bit Block
void print_bit_DBK(long int number);

// Search Empty Bit
long int search_empty_DBK();

// Set the Bit Disk BLock
void Clear_Bit_DBK(long int number);



// INODES
// DISK BLOCK
long int map_size_IN;
long int *BitMap_IN;

// Set all the Bit
void set_all_bit_IN();

// Create the Bit map
void create_empty_bit_map_IN();

// Bit 64 Bit Block
void print_bit_IN(long int number);

// Search Empty Bit
long int search_empty_IN();

// Set the Bit Disk BLock
void Clear_Bit_IN(long int number);