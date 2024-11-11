#ifndef MP3_VIEW_H
#define MP3_VIEW_H

#include "types.h"

// Structure to store MP3 file viewing information
typedef struct Mp3ViewInfo
{
    char *file_name;   // File name of the MP3 to be viewed
    FILE *fptr_file;   // File pointer to the MP3 file
    char mp3Id[4];     // ID3 tag identifier (e.g., "ID3")
    short version;      // ID3 version (e.g., version 3)
} Mp3ViewInfo;

// Function Prototypes

/**
 * Determines the operation type based on the provided arguments.
 * 
 * @param argv (char*[]): Command-line arguments passed to the program.
 * 
 * @returns OperationType: The operation to be performed based on the input arguments.
 */
OperationType Check_operation(char *argv);


/**
 * Reads and validates the MP3 file for viewing. 
 * This function ensures the file has a valid extension and stores the file name.
 * 
 * @param argv (char*[]): Command-line arguments where the MP3 file name is at index 2.
 * @param mp3View (Mp3ViewInfo*): Structure to store MP3 file information.
 * 
 * @returns Status: e_success if validation is successful, e_failure if there's an error.
 */
Status read_and_validation_view(char *argv[], Mp3ViewInfo *mp3View);


/**
 * Displays the information (e.g., title, artist, album) of the MP3 file.
 * 
 * @param mp3View (Mp3ViewInfo*): Structure containing MP3 file information.
 * 
 * @returns Status: e_success if the information is successfully displayed, e_failure if an error occurs.
 */
Status view_info(Mp3ViewInfo *mp3View);


/**
 * Opens the MP3 file for reading.
 * 
 * @param mp3View (Mp3ViewInfo*): Structure containing MP3 file information.
 * 
 * @returns Status: e_success if the file is opened successfully, e_failure if there's an error.
 */
Status open_mp3file(Mp3ViewInfo *mp3View);


/**
 * Checks if the MP3 file has a valid ID3 tag.
 * 
 * @param mp3View (Mp3ViewInfo*): Structure containing MP3 file information.
 * 
 * @returns Status: e_success if the ID3 tag is found, e_failure if not.
 */
Status check_ID(Mp3ViewInfo *mp3View);


/**
 * Checks if the MP3 file has a valid ID3 version (version 3).
 * 
 * @param mp3View (Mp3ViewInfo*): Structure containing MP3 file information.
 * 
 * @returns Status: e_success if the version is 3, e_failure if not.
 */
Status check_version(Mp3ViewInfo *mp3View);


/**
 * Reads and displays the information of a specific frame (e.g., title, artist, album).
 * 
 * @param mp3View (Mp3ViewInfo*): Structure containing MP3 file information.
 * @param str (char[]): Frame identifier (e.g., "TIT2" for title, "TPE1" for artist).
 * 
 * @returns Status: e_success if the information is successfully read, e_failure if an error occurs.
 */
Status read_info(Mp3ViewInfo *mp3View, char str[]);


/**
 * Converts the byte order (endianness) of the given data.
 * This function is used to adjust byte order to match the system's architecture.
 * 
 * @param ptr (char*): Pointer to the data to be converted.
 * @param size (uint): Size of the data to be converted (e.g., 4 bytes for an integer).
 */
void little_to_big(char *ptr, uint size);

#endif
