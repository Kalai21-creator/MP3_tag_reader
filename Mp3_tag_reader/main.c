#include <stdio.h>
#include <string.h>
#include "types.h"
#include "mp3_view.h"
#include "mp3_edit.h"

/**
 * Main function that controls the flow of the program based on the user arguments.
 * 
 * Parameters:
 *   argc (int): The number of command-line arguments passed.
 *   argv (char*[]): The array of command-line arguments.
 * 
 * Returns:
 *   int: Status code indicating success or failure. e_failure for error and e_success for successful execution.
 */
int main(int argc, char *argv[])
{
    // Check if there are sufficient arguments provided
    if(argc < 3)
    {
        printf("-------------------------------------------------------------------------------\n\n");
        printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
        printf("USAGE :\nTo view please pass like: ./a.out -v mp3filename\nTo edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\nTo get help pass like: ./a.out --help\n");
        printf("-------------------------------------------------------------------------------\n");
        return e_failure;
    }

    // Check if the operation is 'view'
    if(Check_operation(argv[1]) == view)
    {
        Mp3ViewInfo mp3View;
        // Validate the mp3 file for viewing
        if(read_and_validation_view(argv, &mp3View) == e_failure)
        {
            return e_failure;
        }
        printf("----------------------------------------[[ SELECTED VIEW DETAILS ]]----------------------------------------\n\n");
        printf("-----------------------------------------------------------------------------------------------------\n");
        printf("                               <<<<  MP3 TAG READER AND EDITOR FOR ID3 v2.3  >>>>                        \n");
        printf("-----------------------------------------------------------------------------------------------------\n");
        
        // View the mp3 file details
        if(view_info(&mp3View) == e_failure)
        {
            printf("Error in viewing information\n");
            return e_failure;
        }
        printf("-----------------------------------------------------------------------------------------------------\n\n");
        printf("---------------------------------[[ DETAILS DISPLAYED SUCCESSFULLY ]]--------------------------------------\n\n");
    }
    // Check if the operation is 'edit'
    else if(Check_operation(argv[1]) == edit)
    {
        Mp3EditInfo mp3Edit;
        // Check if the user has passed enough arguments for editing
        if(argc < 5)
        {
            printf("-------------------------------------------------------------------------------\n\n");
            printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
            printf("USAGE :To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
            printf("-------------------------------------------------------------------------------\n");
            return e_failure;
        }
        
        // Validate the mp3 file for editing
        if(read_and_validation_edit(argv, &mp3Edit) == e_failure)
        {
            return e_failure;
        }
        
        // Set output file name to "Modified.mp3"
        strcpy(mp3Edit.out_fname, "Modified.mp3");
        
        printf("----------------------------------------SELECTED EDIT DETAILS----------------------------------------\n\n");
        printf("----------SELECTED EDIT OPTION----------\n\n");
        
        // Edit the mp3 file's information
        if(edit_info(&mp3Edit) == e_failure)
        {
            printf("Error in editing information\n");
            return e_failure;
        }
    }
    // Check if the operation is 'help'
    else if(Check_operation(argv[1]) == help)
    {
        // Display the help menu with usage instructions
        printf("---------------------------------Help Menu---------------------------------\n\n");
        printf("1. -v -> to view mp3 file contents\n");
        printf("2. -e -> to edit mp3 file contents\n");
        printf("\t2.1. -t -> to edit song title\n");
        printf("\t2.2. -a -> to edit artist name\n");
        printf("\t2.3. -A -> to edit album name\n");
        printf("\t2.4. -y -> to edit year\n");
        printf("\t2.5. -m -> to edit content\n");
        printf("\t2.6. -c -> to edit comment\n\n");
        printf("---------------------------------------------------------------------------\n\n");
    }
    else
    {
        // If the operation is not recognized, return an error
        printf("Invalid operation\n");
        return e_failure;
    }

    return e_success;
}

/**
 * Checks the operation type based on the user input argument.
 * 
 * Parameters:
 *   argv (char*): The command-line argument representing the operation.
 * 
 * Returns:
 *   OperationType: The type of operation requested by the user. It can be:
 *                  - view: If the user wants to view the MP3 file.
 *                  - edit: If the user wants to edit the MP3 file.
 *                  - help: If the user requests help information.
 *                  - unsupported: If the operation is not recognized.
 */
OperationType Check_operation(char *argv)
{
    // Compare the input argument to determine the operation
    if(strcmp(argv, "-v") == 0 )
    {
        return view;
    }
    else if(strcmp(argv, "-e") == 0)
    {
        return edit;
    }
    else if(strcmp(argv, "--help") == 0)
    {
        return help;
    }
    else
    {
        // If the operation is not recognized, return unsupported
        return unsupported;
    }
}
