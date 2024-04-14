/// @file
#ifndef ERROR_H
#define ERROR_H

/// @brief Stops program from running and displays message.
///
/// Displays message box with specified message and stops program running.
///
/// @param[in] message Message to be displayed in messge box
void FatalError(const char *message);
/// @brief Stops program from running with default message.
#define FATAL_ERROR() FatalError("Something went horribly wrong!\nThe application will be closed. See the logs for more information.")

#endif
