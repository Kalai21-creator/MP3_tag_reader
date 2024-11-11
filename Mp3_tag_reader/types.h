#ifndef TYPES_H
#define TYPES_H

// Define a new type 'uint' as an alias for 'unsigned int'.
typedef unsigned int uint;

/**
 * Enum to represent different operation types.
 * This is used to indicate which action the program should perform.
 */
typedef enum
{
    view,         // Operation type for viewing MP3 file details
    edit,         // Operation type for editing MP3 file metadata
    help,         // Operation type for showing help information
    unsupported   // Operation type for unsupported actions or errors
} OperationType;

/**
 * Enum to represent the status of operations.
 * This is used to indicate the success or failure of a function.
 */
typedef enum
{
    e_success,    // Operation was successful
    e_failure     // Operation failed
} Status;

#endif
