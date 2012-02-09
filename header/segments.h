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
 * segments.h
 *    Maps the different program segments of a module.
 * Author: _Felix_
 */

#ifndef SEGMENTS_H
#define	SEGMENTS_H

#include <psploadcore.h>
#include "../header/io.h"
#include "../header/libraries.h"
#include "../header/memory_alloc.h"

/** The base file path for the module memory segment. */
#define MODULE_MEM_SEGMENTS_FILE_PATH           "ms0:/Module_Analyzer/Your_Program_Name/%s_segments.txt"

/** The layout a .scratchpad info line. */
#define SCRATCHPAD_SEG_INFO_LINE                "Segment: .scratchpad: 0x%08X - 0x%08X\n"

/** The basic layout of a .text info line. */
#define TEXT_SEG_INFO_LINE                      "Segment: .text: 0x%08X - 0x%08X\n"

/** The layout of a .sceStub.text. segment info line. */
#define STUB_SEG_INFO_LINE                      "Segment: .sceStub.text.%s: 0x%08X - 0x%08X\n"

/** The length of a .scratchpad info line. */
#define SCRATCHPAD_SEG_INFO_LINE_LENGTH         strlen("Segment: .scratchpad: 0x08800000 - 0x08804000\n")

/** The length of a .text info line. */
#define TEXT_SEG_INFO_LINE_LENGTH               strlen("Segment: .text: 0x00000000 - 0x00000000\n")

/** The length of a .sceStub.text. segment info line. */
#define STUB_SEG_INFO_LINE_LENGTH               strlen("Segment: .sceStub.text.: 0x00000000 - 0x00000000\n")

/** The start address of the .scratchpad Segment. */
#define SCRATCHPAD_SEG_START_ADDR               0x08800000

/** The end address of the .scratchpad Segment. */
#define SCRATCHPAD_SEG_END_ADDR                 0x08804000

/** The max. custom address for a function stub in order to not collect it again. */
#define MAX_CUSTOM_FUNC_STUB_ADDR               0xFFFFFFFF

/** The headline of the RAM segments file. */
#define SEGMENT_FILE_HEADLINE                   "RAM segments: \n\n"

/** The length of the RAM segments file's headline. */
#define SEGMENT_FILE_HEADLINE_LENGTH            strlen("RAM segments: \n\n")

/** The default size of a segment buffer. */
#define DEFAULT_SEG_BUF_SIZE                    SCRATCHPAD_SEG_INFO_LINE_LENGTH + TEXT_SEG_INFO_LINE_LENGTH + SEGMENT_FILE_HEADLINE_LENGTH + STUB_SEG_INFO_LINE_LENGTH

#ifdef	__cplusplus
extern "C" {
#endif
    
    /** Supported segment types. */
    typedef enum _SegTypes {
        /** Indicates segment as .scratchpad. */
        SCRATCHPAD_SEG = 0,
        /** Indicates segment as .text. */
        TEXT_SEG = 1,
        /** Indicates segment as .sceStub.text.. */
        STUB_SEG = 2,
    } SegTypes;   
    
    
    /**
     * Map segments of a game's RAM.
     * 
     * @param mod - Used to determine the start address of the .text segment of the current module.
     * @param modName - The name of the module which is currently analyzed
     * @param libSegPtr - Pointer to a LibStubSegment holding information about a .sceStub.text segment. 
     * @param impLibs - The number of imported libraries by the module.
     * @param libNameLengths - The length of all imported library names added together. Used as an information
     *                         how much memory has to be allocated as a segmentBuffer.
     */
    void map_segments(SceModule2 *mod, const char *modName, LibStubSegment *libSegPtr, u32 impLibs, u32 libNameLengths);


#ifdef	__cplusplus
}
#endif

#endif	/* SEGMENTS_H */

