/*      libstrings

        A library for reading and writing STRINGS, ILSTRINGS and DLSTRINGS files.

    Copyright (C) 2012    WrinklyNinja

        This file is part of libstrings.

    libstrings is free software: you can redistribute
        it and/or modify it under the terms of the GNU General Public License
        as published by the Free Software Foundation, either version 3 of
        the License, or (at your option) any later version.

    libstrings is distributed in the hope that it will
        be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libstrings.  If not, see
        <http://www.gnu.org/licenses/>.
*/

#ifndef __LIBSTRINGS_H__
#define __LIBSTRINGS_H__

#include <stdint.h>
#include <stddef.h>

#if defined(_MSC_VER)
//MSVC doesn't support C99, so do the stdbool.h definitions ourselves.
//START OF stdbool.h DEFINITIONS.
#       ifndef __cplusplus
#               define bool     _Bool
#               define true     1
#               define false   0
#       endif
#       define __bool_true_false_are_defined   1
//END OF stdbool.h DEFINITIONS.
#else
#       include <stdbool.h>
#endif

// set up dll import/export decorators
// when compiling the dll on windows, ensure LIBSTRINGS_EXPORT is defined.  clients
// that use this header do not need to define anything to import the symbols
// properly.
#if defined(_WIN32) || defined(_WIN64)
#       ifdef LIBSTRINGS_STATIC
#               define LIBSTRINGS
#   elif defined LIBSTRINGS_EXPORT
#       define LIBSTRINGS __declspec(dllexport)
#   else
#       define LIBSTRINGS __declspec(dllimport)
#   endif
#else
#   define LIBSTRINGS
#endif

#ifdef __cplusplus
extern "C"
{
#endif


/*------------------------------
   Types
------------------------------*/

/* Abstraction of strings file info structure while providing type safety. */
typedef struct _strings_handle_int * strings_handle;

/* Structure containing ID and data for a string.
   Used by Get/SetStrings to ensure IDs and string data don't get mixed up. */
typedef struct {
        uint32_t id;
        char * data;
} string_data;

/* Return codes */
LIBSTRINGS extern const unsigned int LIBSTRINGS_OK;
LIBSTRINGS extern const unsigned int LIBSTRINGS_ERROR_INVALID_ARGS;
LIBSTRINGS extern const unsigned int LIBSTRINGS_ERROR_NO_MEM;
LIBSTRINGS extern const unsigned int LIBSTRINGS_ERROR_FILE_WRITE_FAIL;
LIBSTRINGS extern const unsigned int LIBSTRINGS_ERROR_FILE_READ_FAIL;
LIBSTRINGS extern const unsigned int LIBSTRINGS_ERROR_BAD_STRING;
LIBSTRINGS extern const unsigned int LIBSTRINGS_RETURN_MAX;


/*------------------------------
   Version Functions
------------------------------*/

/* Returns whether this version of libstrings is compatible with the given
   version of libstrings. */
LIBSTRINGS bool IsCompatibleVersion (const unsigned int versionMajor, const unsigned int versionMinor, const unsigned int versionPatch);

/* Gets the version numbers for the libary. */
LIBSTRINGS void GetVersionNums(unsigned int * const versionMajor, unsigned int * const versionMinor, unsigned int * const versionPatch);


/*------------------------------
   Error Handling Functions
------------------------------*/

/* Gets a string with details about the last error returned. */
LIBSTRINGS unsigned int GetLastErrorDetails(const char ** const details);

/* Frees the memory allocated to the last error details string. */
LIBSTRINGS void CleanUpErrorDetails();


/*----------------------------------
   Lifecycle Management Functions
----------------------------------*/

/* Opens a STRINGS, ILSTRINGS or DLSTRINGS file at path, returning a handle
   sh. If the strings file doesn't exist then a handle for a new file will be
   created. */
LIBSTRINGS unsigned int OpenStringsFile(strings_handle * const sh, const char * const path, const char * const fallbackEncoding);

/* Saves the strings associated with the given handle to the given path. */
LIBSTRINGS unsigned int SaveStringsFile(strings_handle sh, const char * const path);

/* Closes the file associated with the given handle, freeing any memory
   allocated during its use. */
LIBSTRINGS void CloseStringsFile(strings_handle sh);


/*------------------------------
   String Reading Functions
------------------------------*/

/* Gets an array of all strings (with assigned IDs) in the file. */
LIBSTRINGS unsigned int GetStrings(strings_handle sh, string_data ** const strings, size_t * const numStrings);

/* Gets an array of any strings in the file that are not assigned IDs. */
LIBSTRINGS unsigned int GetUnreferencedStrings(strings_handle sh, char *** const strings, size_t * const numStrings);

/* Gets the string with the given ID from the file. */
LIBSTRINGS unsigned int GetString(strings_handle sh, const uint32_t stringId, char ** const string);


/*------------------------------
   String Writing Functions
------------------------------*/

/* Replaces all existing strings in the file with the given strings. */
LIBSTRINGS unsigned int SetStrings(strings_handle sh, const string_data * const strings, const size_t numStrings);

/* Adds the given string to the file. */
LIBSTRINGS unsigned int AddString(strings_handle sh, const uint32_t stringId, const char * const str);

/* Replaces the string corresponding to the given ID with the given string. */
LIBSTRINGS unsigned int EditString(strings_handle sh, const uint32_t stringId, const char * const newString);

/* Removes the string corresponding to the given ID. */
LIBSTRINGS unsigned int RemoveString(strings_handle sh, const uint32_t stringId);

#ifdef __cplusplus
}
#endif

#endif
