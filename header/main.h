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
 * main.h
 *    The main file of module_analyzer.
 * Author: _Felix_
 */

#ifndef MAIN_H
#define	MAIN_H

#include <pspkernel.h>
#include <psputilsforkernel.h>
#include <systemctrl.h>
#include "../header/exports.h"
#include "../header/io.h"
#include "../header/libraries.h"
#include "../header/memory_alloc.h"
#include "../header/segments.h"
#include "../header/stubs.h"

/** The module name. */
#define MODULE_NAME                             "Module Analyzer"

/** The major number of the module's current version. */
#define MOD_VER_MAJ                             (1)

/** The minor number of the module's current version. */
#define MOD_VER_MIN                             (1)

/** The start value of the module counter. */
#define START_COUNTER_VAL                       (1)

/** The basic folder path. */
#define BASE_DIR_PATH                           "ms0:/Module_Analyzer/"

/** The basic folder path for import/export files. */
#define BASE_GAME_DIR_PATH                      "ms0:/Module_Analyzer/Your_Program_Name/"

/** The path for the text file containing the loaded modules info. */
#define GAME_MODULE_FILE_PATH                   "ms0:/Module_Analyzer/Your_Program_Name/modules.txt"

/** The layout of a .stub segment info line. */
#define STUB_SEGMENT_INFO_LINE                  "\t - .stub segment: 0x%08X - 0x%08X\n"

/** The layout of an entry address info line. */
#define ENTRY_ADDRESS_INFO_LINE                 "\t - entry address: 0x%08X\n"

/** The layout of a global pointer info line. */
#define GLOBAL_POINTER_INFO_LINE                "\t - global pointer: 0x%08X\n\n"

/** The length of a .stub segment info line. */
#define STUB_SEGMENT_INFO_LINE_LENGTH           strlen("\t - .stub segment: 0x00000000 - 0x00000000\n")

/** The length of an entry info line. */
#define ENTRY_SEGMENT_INFO_LINE_LENGTH          strlen("\t - entry address: 0x00000000\n")

/** The length of a global pointer info line. */
#define GLOBAL_POINTER_INFO_LINE_LENGTH         strlen("\t - global pointer: 0x00000000\n\n")

/** The length of a module info text. */
#define MODULE_INFO_PRINT_LENGTH                STUB_SEGMENT_INFO_LINE_LENGTH + ENTRY_SEGMENT_INFO_LINE_LENGTH + GLOBAL_POINTER_INFO_LINE_LENGTH

/** The maximal length of a module attribute info line. */
#define MAX_INFO_LINE_LENGTH                    STUB_SEGMENT_INFO_LINE_LENGTH


#endif	/* MAIN_H */