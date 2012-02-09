/*
 * This file is part of Module_Analyzer.

 * Module_Analyzer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Module_Analyzer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Module_Analyzer. If not, see <http://www.gnu.org/licenses/ .
 */

/* 
 * io.h
 *    Handles the opening/creating of a file or directory.
 * Author: _Felix_
 */

#ifndef IO_H
#define	IO_H

#include <string.h>
#include <stdio.h>
#include <pspkerneltypes.h>
#include <pspiofilemgr.h>

/** Indicates, if a value is negative or not. */
#define NOT_NEGATIVE                                    (0)

/** Indicates error accessing invalid IoObject to create/open. */
#define IO_OBJECT_ERROR_NOT_SUPPORTED                   (-1)

/** Indicates successful creating/opening of an IoObject. */
#define IO_OBJECT_DESCRIPTOR_VALID(IoObjDesc)           ((IoObjDesc & 0x80000000) == NOT_NEGATIVE)         

/** Listing of possible IoObject types. */
typedef enum _IoObject {
    /** Indicates IoObject type as a file.*/
    IO_FILE = 1,
    /** Indicates IoObject type as a directory. */
    IO_DIRECTORY = 2
} IoObject;

/**
 * Open or create a directory/file for reading/writing (only for file).
 * 
 * @param objectFlag - Determines the IoObject to create/open. One of ::IoObject.
 * @param path - Pointer to a string holding the name of the IoObject to create/open.
 * @param flags - Specifying how the file is to be opened.
 * @param mode - File access mode.
 * 
 * @return The IoObject file descriptor on success, a Sony error code on opening/creating failure
 *         or IO_OBJECT_ERROR_NOT_SUPPORTED for passing a non IoObject member as the objectFlag.
 */
int create_open_IoObject(IoObject objectFlag, const char *path, int flags, SceMode mode);


#endif	/* IO_H */