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
 * Stubs.h
 *    Maps the imported NIDs of imported libraries.
 * Author: _Felix_
 */

#ifndef STUBS_H
#define	STUBS_H

#include <psploadcore.h>
#include "../header/io.h"
#include "../header/libraries.h"
#include "../header/segments.h"

/** The basic file path for module library imports. */
#define MODULE_LIB_IMPORTS_FILE_PATH                   "ms0:/Module_Analyzer/Your_Program_Name/%s_imports.txt"

/** The layout of an imported NID info line. */
#define IMPORTED_NID_INFO_LINE                         "\t NID_%03d: 0x%08X - stub address: 0x%08X\n"

/** The length of an imported NID info line. */
#define IMPORTED_NID_INFO_LINE_LENGTH                  strlen("\t NID_999: 0x00000000 - stub address: 0x00000000\n") 

/** The size of a function stub. */
#define STUB_SIZE                                      (8)

/**
 * Map the imported NIDs of a library with their equivalent stub addresses.
 * 
 * @param ioOpenFlag - Pointer to an int specifying how the file is to be opened.
 * @param stubTable - Pointer to an imported library (represented as a SceLibraryStubTable).
 * @param modName - The name of the module.
 * @param libSegPtr - Pointer to a LibStubSegment to store the library's sceStub.text. segment attributes.
 * @param libNameLengths - The sum of the length of all imported library names. 
 *                         Used as one indicator for the size of allocated memory in map_segments.
 */
void map_imported_functions(int *ioOpenFlag, SceLibraryStubTable *stubTable, const char *modName, LibStubSegment *libSegPtr, int *libNameLengths);


#endif	/* STUBS_H */