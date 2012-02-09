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
 * export.h
 *    Maps the exported NIDs of exported functions/variables to the kernel.
 * Author: _Felix_
 */

#ifndef EXPORTS_H
#define	EXPORTS_H

#include <psploadcore.h>
#include "../header/io.h"
#include "../header/memory_alloc.h"

/** The basic file path for module library exports. */
#define MODULE_LIB_EXPORTS_FILE_PATH                   "ms0:/Module_Analyzer/Your_Program_Name/%s_exports.txt"

/** The layout of an exported NID info line. */
#define EXPORTED_NID_INFO_LINE                         "\t NID_%03d: 0x%08X - address: 0x%08X //%s\n"

/** The length of an exported NID info line. */
#define EXPORTED_NID_INFO_LINE_LENGTH                  strlen("\t NID_999: 0x00000000 - address: 0x00000000 //variable: module_start_thread_parameter\n") 

/** Exported NID defines. */
#define MODULE_BOOTSTART                               0xD3744BE0
#define MODULE_START                                   0xD632ACDB
#define MODULE_STOP                                    0xCEE8593C
#define MODULE_START_THREAD_PARAM                      0x0F7C276C
#define MODULE_STOP_THREAD_PARAM                       0xCF0CC697
#define MODULE_INFO                                    0xF01D73A7

#ifdef	__cplusplus
extern "C" {
#endif

    /**
     * Analyze a NID of an exported library and return the propper meaning of the NID.
     * 
     * @param nid - The NID to analyze.
     * @return Pointer to a string identifying the meaning of the NID.
     */
    const char *analyze_exported_nid(u32 nid);
    
    /**
     * Set up analyzing of the exported libraries of the specified module.
     * 
     * @param mod - The module to receive the exported libraries from.
     * @param modName - The name of the module.
     */
    void get_exported_libraries(SceModule2 *mod, const char *modName);

    /**
     * Map the exported NIDs of a library with their equivalent memory addresses.
     * 
     * @param ioOpenFlag - Pointer to an int specifying how the file is to be opened.
     * @param entry_table - Pointer to an exported library (represented as a SceLibraryEntryTable).
     * @param modName - The name of the module.
     */
    void map_exported_functions(int *ioOpenFlag, SceLibraryEntryTable *entTable, const char *modName);


#ifdef	__cplusplus
}
#endif

#endif	/* EXPORTS_H */