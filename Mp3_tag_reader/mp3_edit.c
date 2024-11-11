#include <stdio.h>
#include <string.h>
#include "mp3_edit.h"
#include "types.h"

/**
 * Validates and reads the MP3 file for editing.
 * This function checks if the file has a valid extension (.mp3), verifies the command-line arguments,
 * and stores relevant information into the `mp3Edit` structure.
 * 
 * Parameters:
 *   argv (char*[]): The command-line arguments, with the fourth argument being the MP3 file name.
 *   mp3Edit (Mp3EditInfo*): A pointer to the structure where MP3 file information will be stored.
 * 
 * Returns:
 *   Status: e_success if validation passes, e_failure if there's an error.
 */
Status read_and_validation_edit(char *argv[], Mp3EditInfo *mp3Edit)
{
    char extn[10];

    // Check if the file has an extension
    if (strchr(argv[4], '.') == NULL)
    {
        printf("-------------------------------------------------------------------------------\n\n");
        printf("ERROR: ./a.out : INVALID EXTENSION\n");
        printf("-------------------------------------------------------------------------------\n");
        return e_failure;
    }

    // Extract the file extension
    strcpy(extn, strchr(argv[4], '.'));

    // Check if the file extension is ".mp3"
    if (strcmp(extn, ".mp3") != 0)
    {
        printf("-------------------------------------------------------------------------------\n\n");
        printf("ERROR: ./a.out : INVALID EXTENSION\n");
        printf("-------------------------------------------------------------------------------\n");
        return e_failure;
    }

    // Store file name and other command-line arguments
    mp3Edit->src_fname = argv[4];
    if (strcmp(argv[2], "-t") != 0 && strcmp(argv[2], "-a") != 0 && strcmp(argv[2], "-A") != 0 && strcmp(argv[2], "-m") != 0 && strcmp(argv[2], "-y") != 0 && strcmp(argv[2], "-c") != 0)
    {
        printf("-------------------------------------------------------------------------------\n\n");
        printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
        printf("USAGE :\nTo edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
        printf("-------------------------------------------------------------------------------\n");
        return e_failure;
    }

    // Store the frame type and data to be modified
    mp3Edit->frame = argv[2];
    mp3Edit->modify_data = argv[3];
    mp3Edit->data_length = strlen(mp3Edit->modify_data) + 1;

    return e_success;
}

/**
 * Edits the MP3 file information based on the specified frame (e.g., title, artist, album).
 * It validates the MP3 file, opens necessary files, and makes the modifications.
 * 
 * Parameters:
 *   mp3Edit (Mp3EditInfo*): A pointer to the structure containing MP3 file information.
 * 
 * Returns:
 *   Status: e_success if editing is successful, e_failure if an error occurs.
 */
Status edit_info(Mp3EditInfo *mp3Edit)
{
    // Open input and output files
    if (open_files(mp3Edit) == e_failure)
    {
        printf("Error in opening files\n");
        return e_failure;
    }

    // Check if the MP3 file has a valid ID3 tag and version
    if (check_ID3(mp3Edit) == e_failure)
    {
        printf("Invalid Mp3 ID format\n");
        return e_failure;
    }
    if (check_mp3version(mp3Edit) == e_failure)
    {
        printf("Invalid ID3 version\n");
        return e_failure;
    }

    // Copy header to output file
    if (copy_header(mp3Edit->fptr_out, mp3Edit->fptr_src) == e_failure)
    {
        printf("Error in copying header\n");
        return e_failure;
    }

    // Modify various frames based on input arguments
    int flag = 0;

    // Change Title
    if (do_change(mp3Edit, "TIT2", "-t", &flag) == e_failure || flag)
    {
        if (flag)
        {
            printf("----------[ CHANGE THE TITLE ]-------------\n\n");
            printf("TITLE   : %s\n\n", mp3Edit->modify_data);
            fclose(mp3Edit->fptr_src);
            fclose(mp3Edit->fptr_out);
            file_copy(mp3Edit);
            printf("----------<< TITLE CHANGED SUCCESSFULLY >>----------\n\n");
            return e_success;
        }
        printf("Error\n");
        return e_failure;
    }

    // Change Artist
    if (do_change(mp3Edit, "TPE1", "-a", &flag) == e_failure || flag)
    {
        if (flag)
        {
            printf("----------[ CHANGE THE ARTIST ]-------------\n\n");
            printf("ARTIST   : %s\n\n", mp3Edit->modify_data);
            fclose(mp3Edit->fptr_src);
            fclose(mp3Edit->fptr_out);
            file_copy(mp3Edit);
            printf("----------<< ARTIST CHANGED SUCCESSFULLY >>----------\n\n");
            return e_success;
        }
        printf("Error\n");
        return e_failure;
    }

    // Change Album
    if (do_change(mp3Edit, "TALB", "-A", &flag) == e_failure || flag)
    {
        if (flag)
        {
            printf("----------[ CHANGE THE ALBUM ]-------------\n\n");
            printf("ALBUM   : %s\n\n", mp3Edit->modify_data);
            fclose(mp3Edit->fptr_src);
            fclose(mp3Edit->fptr_out);
            file_copy(mp3Edit);
            printf("----------<< ALBUM CHANGED SUCCESSFULLY >>----------\n\n");
            return e_success;
        }
        printf("Error\n");
        return e_failure;
    }

    // Change Year
    if (do_change(mp3Edit, "TYER", "-y", &flag) == e_failure || flag)
    {
        if (flag)
        {
            printf("----------[ CHANGE THE YEAR ]-------------\n\n");
            printf("YEAR   : %s\n\n", mp3Edit->modify_data);
            fclose(mp3Edit->fptr_src);
            fclose(mp3Edit->fptr_out);
            file_copy(mp3Edit);
            printf("----------<< YEAR CHANGED SUCCESSFULLY >>----------\n\n");
            return e_success;
        }
        printf("Error\n");
        return e_failure;
    }

    // Change Content
    if (do_change(mp3Edit, "TCON", "-m", &flag) == e_failure || flag)
    {
        if (flag)
        {
            printf("----------[ CHANGE THE CONTENT ]-------------\n\n");
            printf("CONTENT   : %s\n\n", mp3Edit->modify_data);
            fclose(mp3Edit->fptr_src);
            fclose(mp3Edit->fptr_out);
            file_copy(mp3Edit);
            printf("----------<< CONTENT CHANGED SUCCESSFULLY >>----------\n\n");
            return e_success;
        }
        printf("Error\n");
        return e_failure;
    }

    // Change Comment
    if (do_change(mp3Edit, "COMM", "-c", &flag) == e_failure || flag)
    {
        if (flag)
        {
            printf("----------[ CHANGE THE COMMENT ]-------------\n\n");
            printf("COMMENT   : %s\n\n", mp3Edit->modify_data);
            fclose(mp3Edit->fptr_src);
            fclose(mp3Edit->fptr_out);
            file_copy(mp3Edit);
            printf("----------<< COMMENT CHANGED SUCCESSFULLY >>----------\n\n");
            return e_success;
        }
        printf("Error\n");
        return e_failure;
    }

    return e_success;
}

/**
 * Changes the specified frame in the MP3 file based on the given arguments.
 * 
 * Parameters:
 *   mp3Edit (Mp3EditInfo*): A pointer to the structure containing MP3 file information.
 *   str (char[]): The frame type (e.g., TIT2 for title).
 *   frame (char[]): The argument for the frame to be edited (e.g., "-t").
 *   flag (int*): A flag to indicate whether the change was successful.
 * 
 * Returns:
 *   Status: e_success if the change is successful, e_failure if an error occurs.
 */
Status do_change(Mp3EditInfo *mp3Edit, char str[], char frame[], int *flag)
{
    // Check if the frame matches
    if (check_frame(mp3Edit, str) == e_failure)
    {
        printf("Frame Matching Error\n");
        return e_failure;
    }

    // Modify data if the frame matches
    if (strcmp(mp3Edit->frame, frame) == 0)
    {
        modify_data(mp3Edit);
        fseek(mp3Edit->fptr_src, mp3Edit->size - 1, SEEK_CUR);
        copy_remaining(mp3Edit->fptr_out, mp3Edit->fptr_src);
        *flag = 1;
        return e_success;
    }

    // Copy the same data if the frame doesn't match
    if (copy_same(mp3Edit) == e_failure)
    {
        printf("Error in copying title\n");
        return e_failure;
    }

    return e_success;
}

/**
 * Copies the same data from the source to the output file.
 * This is used to copy data when no change is required.
 * 
 * Parameters:
 *   mp3Edit (Mp3EditInfo*): A pointer to the structure containing MP3 file information.
 * 
 * Returns:
 *   Status: e_success if the copy is successful, e_failure if an error occurs.
 */
Status copy_same(Mp3EditInfo *mp3Edit)
{
    uint size = mp3Edit->size;
    convert_endianess((char *)&size, sizeof(int));
    fwrite(&size, 4, 1, mp3Edit->fptr_out);

    char flag[3];
    fread(flag, 3, 1, mp3Edit->fptr_src);
    fwrite(flag, 3, 1, mp3Edit->fptr_out);

    char data[mp3Edit->size];
    fread(data, mp3Edit->size - 1, 1, mp3Edit->fptr_src);
    fwrite(data, mp3Edit->size - 1, 1, mp3Edit->fptr_out);

    return e_success;
}

/**
 * Copies the remaining data from the source file to the destination file.
 * 
 * Parameters:
 *   fptr_dest (FILE*): Pointer to the destination file.
 *   fptr_src (FILE*): Pointer to the source file.
 * 
 * Returns:
 *   Status: e_success if the copy is successful, e_failure if an error occurs.
 */
Status copy_remaining(FILE *fptr_dest, FILE *fptr_src)
{
    char ch;
    while (fread(&ch, 1, 1, fptr_src) > 0)
    {
        fwrite(&ch, 1, 1, fptr_dest);
    }
    return e_success;
}

/**
 * Modifies the data of the MP3 file based on the given information.
 * 
 * Parameters:
 *   mp3Edit (Mp3EditInfo*): A pointer to the structure containing MP3 file information.
 * 
 * Returns:
 *   Status: e_success if the modification is successful, e_failure if an error occurs.
 */
Status modify_data(Mp3EditInfo *mp3Edit)
{
    convert_endianess((char *)&mp3Edit->data_length, sizeof(int));
    fwrite(&mp3Edit->data_length, 4, 1, mp3Edit->fptr_out);

    char flag[3];
    fread(flag, 3, 1, mp3Edit->fptr_src);
    fwrite(flag, 3, 1, mp3Edit->fptr_out);

    fwrite(mp3Edit->modify_data, strlen(mp3Edit->modify_data), 1, mp3Edit->fptr_out);

    return e_success;
}

/**
 * Copies the header from the source file to the destination file.
 * 
 * Parameters:
 *   fptr_dest (FILE*): Pointer to the destination file.
 *   fptr_src (FILE*): Pointer to the source file.
 * 
 * Returns:
 *   Status: e_success if the header copy is successful, e_failure if an error occurs.
 */
Status copy_header(FILE *fptr_dest, FILE *fptr_src)
{
    rewind(fptr_dest);
    rewind(fptr_src);
    char header[10];
    fread(header, 10, 1, fptr_src);
    fwrite(header, 10, 1, fptr_dest);

    return e_success;
}

/**
 * Checks if the specified frame exists in the MP3 file.
 * 
 * Parameters:
 *   mp3Edit (Mp3EditInfo*): A pointer to the structure containing MP3 file information.
 *   str (char[]): The frame type to be checked (e.g., TIT2 for title).
 * 
 * Returns:
 *   Status: e_success if the frame is found, e_failure if an error occurs.
 */
Status check_frame(Mp3EditInfo *mp3Edit, char str[])
{
    char buffer[4];
    fread(buffer, 4, 1, mp3Edit->fptr_src);

    if (strcmp(buffer, str) != 0)
    {
        return e_failure;
    }
    fwrite(buffer, 4, 1, mp3Edit->fptr_out);

    fread(&mp3Edit->size, 4, 1, mp3Edit->fptr_src);
    convert_endianess((char *)&mp3Edit->size, sizeof(int));

    return e_success;
}

/**
 * Opens the input and output MP3 files for reading and writing, respectively.
 * 
 * Parameters:
 *   mp3Edit (Mp3EditInfo*): A pointer to the structure containing MP3 file information.
 * 
 * Returns:
 *   Status: e_success if the files are opened successfully, e_failure if an error occurs.
 */
Status open_files(Mp3EditInfo *mp3Edit)
{
    mp3Edit->fptr_src = fopen(mp3Edit->src_fname, "r");
    if (mp3Edit->fptr_src == NULL)
    {
        return e_failure;
    }

    mp3Edit->fptr_out = fopen(mp3Edit->out_fname, "w");
    if (mp3Edit->fptr_out == NULL)
    {
        return e_failure;
    }

    return e_success;
}

/**
 * Checks if the MP3 file has a valid ID3 tag.
 * 
 * Parameters:
 *   mp3Edit (Mp3EditInfo*): A pointer to the structure containing MP3 file information.
 * 
 * Returns:
 *   Status: e_success if the ID3 tag is valid, e_failure if an error occurs.
 */
Status check_ID3(Mp3EditInfo *mp3Edit)
{
    char buffer[3];
    fread(buffer, 3, 1, mp3Edit->fptr_src);
    if (strcmp(buffer, "ID3") != 0)
    {
        return e_failure;
    }

    return e_success;
}

/**
 * Checks if the MP3 file uses ID3v2 version 3.
 * 
 * Parameters:
 *   mp3Edit (Mp3EditInfo*): A pointer to the structure containing MP3 file information.
 * 
 * Returns:
 *   Status: e_success if the MP3 version is 3, e_failure if the version is invalid.
 */
Status check_mp3version(Mp3EditInfo *mp3Edit)
{
    short version;
    fread(&version, 2, 1, mp3Edit->fptr_src);
    if (version != 3)
    {
        return e_failure;
    }

    return e_success;
}

/**
 * Copies the MP3 file from the source to the destination.
 * This is done after changes are made to the file.
 * 
 * Parameters:
 *   mp3Edit (Mp3EditInfo*): A pointer to the structure containing MP3 file information.
 * 
 * Returns:
 *   Status: e_success if the copy is successful, e_failure if an error occurs.
 */
Status file_copy(Mp3EditInfo *mp3Edit)
{
    mp3Edit->fptr_src = fopen(mp3Edit->src_fname, "w");
    mp3Edit->fptr_out = fopen(mp3Edit->out_fname, "r");

    rewind(mp3Edit->fptr_src);
    rewind(mp3Edit->fptr_out);

    char ch;
    while (fread(&ch, 1, 1, mp3Edit->fptr_out) > 0)
    {
        fwrite(&ch, 1, 1, mp3Edit->fptr_src);
    }

    return e_success;
}

/**
 * Converts the byte order (endianess) of the given data.
 * 
 * Parameters:
 *   ptr (char*): A pointer to the data to be converted.
 *   size (uint): The size of the data to be converted.
 */
void convert_endianess(char *ptr, uint size)
{
    char temp;
    for (int i = 0; i < size / 2; i++)
    {
        temp = ptr[i];
        ptr[i] = ptr[size - i - 1];
        ptr[size - i - 1] = temp;
    }
}
