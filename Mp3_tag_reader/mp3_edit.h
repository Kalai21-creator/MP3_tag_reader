#ifndef MP3_EDIT_H
#define MP3_EDIT_H

#include "types.h"

// Structure to store MP3 file edit information
typedef struct Mp3EditInfo
{
    char *src_fname;       // Source MP3 file name
    FILE *fptr_src;        // File pointer for the source MP3 file

    char out_fname[20];    // Output file name
    FILE *fptr_out;        // File pointer for the output MP3 file

    char *modify_data;     // Data to modify (e.g., title, artist)
    int data_length;       // Length of the modification data
    char *frame;           // The MP3 frame type (e.g., "TIT2" for title)

    uint size;             // Size of the MP3 frame
} Mp3EditInfo;

// Function Prototypes

/**
 * Validates and reads the MP3 file for editing.
 * It checks if the file has a valid extension and stores relevant information into the `mp3Edit` structure.
 * 
 * @param argv (char*[]): Command-line arguments, where the MP3 filename is at index 4.
 * @param mp3Edit (Mp3EditInfo*): Structure to store MP3 file information.
 * 
 * @returns Status: e_success if validation is successful, e_failure if there's an error.
 */
Status read_and_validation_edit(char *argv[], Mp3EditInfo *mp3Edit);


/**
 * Checks if the specified frame exists in the MP3 file.
 * 
 * @param mp3Edit (Mp3EditInfo*): Structure containing MP3 file information.
 * @param str (char[]): Frame type (e.g., "TIT2" for title).
 * 
 * @returns Status: e_success if the frame exists, e_failure if not.
 */
Status check_frame(Mp3EditInfo *mp3Edit, char str[]);


/**
 * Edits the MP3 file's information based on the specified frame.
 * This function validates the MP3 file, opens necessary files, and applies the modification.
 * 
 * @param mp3Edit (Mp3EditInfo*): Structure containing MP3 file information.
 * 
 * @returns Status: e_success if editing is successful, e_failure if an error occurs.
 */
Status edit_info(Mp3EditInfo *mp3Edit);


/**
 * Opens the input and output MP3 files for reading and writing.
 * 
 * @param mp3Edit (Mp3EditInfo*): Structure containing MP3 file information.
 * 
 * @returns Status: e_success if the files are opened successfully, e_failure if an error occurs.
 */
Status open_files(Mp3EditInfo *mp3Edit);


/**
 * Checks if the MP3 file has a valid ID3 tag (ID3v2).
 * 
 * @param mp3Edit (Mp3EditInfo*): Structure containing MP3 file information.
 * 
 * @returns Status: e_success if the ID3 tag is valid, e_failure if not.
 */
Status check_ID3(Mp3EditInfo *mp3Edit);


/**
 * Checks if the MP3 file uses ID3v2 version 3.
 * 
 * @param mp3Edit (Mp3EditInfo*): Structure containing MP3 file information.
 * 
 * @returns Status: e_success if version 3 is found, e_failure if not.
 */
Status check_mp3version(Mp3EditInfo *mp3Edit);


/**
 * Copies the header from the source MP3 file to the output file.
 * 
 * @param fptr_dest (FILE*): File pointer to the destination (output) file.
 * @param fptr_src (FILE*): File pointer to the source file.
 * 
 * @returns Status: e_success if the header copy is successful, e_failure if an error occurs.
 */
Status copy_header(FILE *fptr_dest, FILE *fptr_src);


/**
 * Modifies a specified MP3 frame (e.g., title, artist) with the provided data.
 * 
 * @param mp3Edit (Mp3EditInfo*): Structure containing MP3 file information.
 * 
 * @returns Status: e_success if the modification is successful, e_failure if an error occurs.
 */
Status modify_data(Mp3EditInfo *mp3Edit);


/**
 * Copies the remaining data from the source file to the output file.
 * 
 * @param fptr_dest (FILE*): File pointer to the destination (output) file.
 * @param fptr_src (FILE*): File pointer to the source file.
 * 
 * @returns Status: e_success if the copy is successful, e_failure if an error occurs.
 */
Status copy_remaining(FILE *fptr_dest, FILE *fptr_src);


/**
 * Copies the same data from the source file to the output file when no modification is required.
 * 
 * @param mp3Edit (Mp3EditInfo*): Structure containing MP3 file information.
 * 
 * @returns Status: e_success if the copy is successful, e_failure if an error occurs.
 */
Status copy_same(Mp3EditInfo *mp3Edit);


/**
 * Copies the entire MP3 file from the source to the destination after modifications.
 * 
 * @param mp3Edit (Mp3EditInfo*): Structure containing MP3 file information.
 * 
 * @returns Status: e_success if the copy is successful, e_failure if an error occurs.
 */
Status file_copy(Mp3EditInfo *mp3Edit);


/**
 * Changes the specified MP3 frame (e.g., title, artist) based on the given arguments.
 * 
 * @param mp3Edit (Mp3EditInfo*): Structure containing MP3 file information.
 * @param str (char[]): The frame type (e.g., "TIT2" for title).
 * @param frame (char[]): Argument for the frame (e.g., "-t" for title).
 * @param flag (int*): A flag to indicate if the change was successful.
 * 
 * @returns Status: e_success if the change is successful, e_failure if an error occurs.
 */
Status do_change(Mp3EditInfo *mp3Edit, char str[], char frame[], int *flag);


/**
 * Converts the byte order (endianness) of the given data.
 * This function is used to convert data for compatibility with different architectures.
 * 
 * @param ptr (char*): Pointer to the data to be converted.
 * @param size (uint): Size of the data to be converted.
 */
void convert_endianess(char *ptr, uint size);

#endif
