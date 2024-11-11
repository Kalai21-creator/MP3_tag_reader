#include <stdio.h>
#include <string.h>
#include "types.h"
#include "mp3_view.h"

/**
 * Validates and reads the MP3 file for viewing.
 * This function checks the file extension and opens the file for viewing.
 * 
 * Parameters:
 *   argv (char*[]): The command-line arguments, with the second argument being the MP3 file name.
 *   mp3View (Mp3ViewInfo*): A pointer to the structure where MP3 file information will be stored.
 * 
 * Returns:
 *   Status: e_success if validation passes and file is ready to view, e_failure if there's an error.
 */
Status read_and_validation_view(char *argv[], Mp3ViewInfo *mp3View)
{
    char extn[10];

    // Check if the file has an extension
    if (strchr(argv[2], '.') == NULL)
    {
        printf("-------------------------------------------------------------------------------\n\n");
        printf("ERROR: ./a.out : INVALID EXTENSION\n");
        printf("-------------------------------------------------------------------------------\n");
        return e_failure;
    }

    // Extract the file extension
    strcpy(extn, strchr(argv[2], '.'));

    // Check if the file extension is ".mp3"
    if (strcmp(extn, ".mp3") != 0)
    {
        printf("-------------------------------------------------------------------------------\n\n");
        printf("ERROR: ./a.out : INVALID EXTENSION\n");
        printf("-------------------------------------------------------------------------------\n");
        return e_failure;
    }

    // Store the file name in the mp3View structure
    mp3View->file_name = argv[2];

    return e_success;
}

/**
 * Displays the information stored in the MP3 file's ID3 tag.
 * It opens the file, validates the ID3 tag, and then reads specific information like
 * title, artist, album, year, music genre, and comments.
 * 
 * Parameters:
 *   mp3View (Mp3ViewInfo*): A pointer to the structure containing MP3 file information.
 * 
 * Returns:
 *   Status: e_success if all information is successfully displayed, e_failure if an error occurs.
 */
Status view_info(Mp3ViewInfo *mp3View)
{
    // Open the MP3 file for reading
    if (open_mp3file(mp3View) == e_failure)
    {
        printf("Error in opening mp3View file\n");
        return e_failure;
    }

    // Check if the MP3 file has a valid ID3 tag
    if (check_ID(mp3View) == e_failure)
    {
        printf("Invalid Mp3 ID format\n");
        return e_failure;
    }

    // Check if the MP3 file has a valid ID3 version
    if (check_version(mp3View) == e_failure)
    {
        printf("Invalid ID3 version\n");
        return e_failure;
    }

    // Display the MP3 file's details (title, artist, album, year, music genre, comments)
    printf("TITLE    :   ");
    if (read_info(mp3View, "TIT2") == e_failure)
    {
        printf("Error in getting title name\n");
    }

    printf("ARTIST   :   ");
    if (read_info(mp3View, "TPE1") == e_failure)
    {
        printf("Error in getting artist name\n");
    }

    printf("ALBUM    :   ");
    if (read_info(mp3View, "TALB") == e_failure)
    {
        printf("Error in getting album name\n");
    }

    printf("YEAR     :   ");
    if (read_info(mp3View, "TYER") == e_failure)
    {
        printf("Error in getting year\n");
    }

    printf("MUSIC    :   ");
    if (read_info(mp3View, "TCON") == e_failure)
    {
        printf("Error in getting music\n");
    }

    printf("COMMENT  :   ");
    if (read_info(mp3View, "COMM") == e_failure)
    {
        printf("Error in getting comments\n");
    }

    return e_success;
}

/**
 * Opens the MP3 file in read mode.
 * 
 * Parameters:
 *   mp3View (Mp3ViewInfo*): A pointer to the structure containing MP3 file information.
 * 
 * Returns:
 *   Status: e_success if the file is successfully opened, e_failure if there is an error.
 */
Status open_mp3file(Mp3ViewInfo *mp3View)
{
    // Open the file for reading
    mp3View->fptr_file = fopen(mp3View->file_name, "r");
    if (mp3View->fptr_file == NULL)
    {
        return e_failure;
    }
    return e_success;
}

/**
 * Checks if the MP3 file has a valid ID3 tag.
 * This function reads the first 3 bytes of the file and checks if they match the "ID3" signature.
 * 
 * Parameters:
 *   mp3View (Mp3ViewInfo*): A pointer to the structure containing MP3 file information.
 * 
 * Returns:
 *   Status: e_success if the ID3 tag is valid, e_failure if the tag is invalid.
 */
Status check_ID(Mp3ViewInfo *mp3View)
{
    char buffer[3];

    // Read the first 3 bytes of the file to check for "ID3" signature
    fread(buffer, 3, 1, mp3View->fptr_file);

    // If the first 3 bytes aren't "ID3", return failure
    if (strcmp(buffer, "ID3") != 0)
    {
        return e_failure;
    }

    // Store the ID3 tag information
    strcpy(mp3View->mp3Id, buffer);

    return e_success;
}

/**
 * Checks if the MP3 file uses a valid ID3 version.
 * This function reads the version bytes from the MP3 file and checks if it matches version 3.
 * 
 * Parameters:
 *   mp3View (Mp3ViewInfo*): A pointer to the structure containing MP3 file information.
 * 
 * Returns:
 *   Status: e_success if the version is 3, e_failure if the version is different.
 */
Status check_version(Mp3ViewInfo *mp3View)
{
    // Read the version bytes (2 bytes)
    fread(&mp3View->version, 2, 1, mp3View->fptr_file);

    // If the version is not 3, return failure
    if (mp3View->version != 3)
    {
        return e_failure;
    }

    // Move the file pointer 10 bytes from the start (skip header information)
    fseek(mp3View->fptr_file, 10, SEEK_SET);

    return e_success;
}

/**
 * Reads and displays information (like title, artist, album, etc.) from the MP3 file.
 * This function reads the corresponding tag (e.g., TIT2 for title) and prints it to the console.
 * 
 * Parameters:
 *   mp3View (Mp3ViewInfo*): A pointer to the structure containing MP3 file information.
 *   str (char[]): The tag to be read (e.g., "TIT2" for title).
 * 
 * Returns:
 *   Status: e_success if information is successfully read and displayed, e_failure if there's an error.
 */
Status read_info(Mp3ViewInfo *mp3View, char str[])
{
    char buffer[4];

    // Read the next 4 bytes to check for the tag
    fread(buffer, 4, 1, mp3View->fptr_file);

    // If the tag doesn't match, return failure
    if (strcmp(buffer, str) != 0)
    {
        return e_failure;
    }

    // Read the size of the tag's content
    uint size;
    fread(&size, 4, 1, mp3View->fptr_file);

    // Rearrange bytes to match the system's endianness
    little_to_big((char *)&size, sizeof(int));

    // Skip 3 bytes (for other data in the tag)
    fseek(mp3View->fptr_file, 3, SEEK_CUR);

    // Read the title content
    char title[size];
    fread(title, size - 1, 1, mp3View->fptr_file);

    // If it's a comment, fix a special case in the title
    if (strcmp(buffer, "COMM") == 0)
    {
        if (title[3] == 0)
            title[3] = '.';
    }

    // Null-terminate the title string
    title[size - 1] = '\0';

    // Print the title (or other content)
    printf("%-15s\n", title);

    return e_success;
}

/**
 * Converts the byte order from little-endian to big-endian.
 * This is used to ensure correct byte order when reading sizes or other data from the MP3 file.
 * 
 * Parameters:
 *   ptr (char*): A pointer to the data to be rearranged.
 *   size (uint): The size of the data in bytes.
 */
void little_to_big(char *ptr, uint size)
{
    char temp;

    // Swap bytes to convert little-endian to big-endian
    for (int i = 0; i < size / 2; i++)
    {
        temp = ptr[i];
        ptr[i] = ptr[size - i - 1];
        ptr[size - i - 1] = temp;
    }
}
