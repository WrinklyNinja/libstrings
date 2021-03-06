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

#ifndef __LIBSTRINGS_FORMAT_H__
#define __LIBSTRINGS_FORMAT_H__

#include "libstrings.h"
#include "helpers.h"
#include <stdint.h>
#include <string>
#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
#include <map>

/* See here for format details: http://www.uesp.net/wiki/Tes5Mod:String_Table_File_Format
   Files read may be in UTF-8, Windows-1252 or Windows-1251.
   Files written should be in UTF-8.
   Store strings in UTF-8. */
struct _strings_handle_int {
public:
    _strings_handle_int(const std::string& path, const std::string& fallbackEncoding);
    ~_strings_handle_int();

    //File data.
    boost::unordered_map<uint32_t, std::string> data;       //Internal data storage. uint32_t is the string id and std::string is the string itself.

    //External data pointers.
    st_string_data * extStringDataArr;
    char ** extStringArr;
    char * extString;

    //External data array sizes.
    size_t extStringDataArrSize;
    size_t extStringArrSize;

    //All the unreferenced strings in the file.
    boost::unordered_set<std::string> unrefStrings;

    //Save file data to given path.
    void Save(const std::string& path, const std::string& encoding);
};

#endif
