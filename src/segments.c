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

#include "../header/segments.h"

/**
 * Add segment attributes to a buffer ready to be printed.
 * 
 * @param segFlag - Specifying what segment will be stored into segBuf. One of ::SegTypes.
 * @param segBuf - The buffer which will be used to hold a segment info line.
 * @param libName - The library name which is currently being analyzed. Pass NULL if the the segment is NOT a stub segment.
 * @param segTop - The start address of the segment which is to be stored into segBuf.
 * @param segEnd - The end address of the segment which is to be stored into segBuf.
 */
static void add_to_buffer(SegTypes segFlag, char *segBuf, const char *libName, u32 segTop, u32 segEnd) {    
    char buf[128];
    u32 textLength = 0;
    
    switch(segFlag) {
        case SCRATCHPAD_SEG:
            textLength = sprintf(buf, SCRATCHPAD_SEG_INFO_LINE, segTop, segEnd);
            break;
        case TEXT_SEG:
            textLength = sprintf(buf, TEXT_SEG_INFO_LINE, segTop, segEnd);
            break;
        case STUB_SEG:
            textLength = sprintf(buf, STUB_SEG_INFO_LINE, libName, segTop, segEnd);
            break;
    }
    strncat(segBuf, buf, textLength);
}

/**
 * Sort the imported .sceStub.text. sections from low-order to high-order to map them correctly.
 * 
 * @param mod - The currently investigated module, used to map its .text segment.
 * @param segBuf - The buffer which will hold the sorted .sceStub.text. info lines ready to be written to a file.
 * @param libSegPtr - Pointer to an array of stub segments, which have to be sorted (occurence in memory - low-order).
 * @param impLibs - The number of imported libraries by a module.
 */
static void sort_lib_sections(SceModule2 *mod, char *segBuf, LibStubSegment *libSegPtr, const u32 impLibs) {
    u32 sIndex;        
    u32 i;
    u32 count;
    u32 tempStubTop = MAX_CUSTOM_FUNC_STUB_ADDR;
    
    for (count = 0; count < impLibs; count++) {
         for (i = 0; i < impLibs; i++) {
              if (tempStubTop > (&libSegPtr[i])->stubTop) {
                  tempStubTop = (&libSegPtr[i])->stubTop;
                  sIndex = i;
              }
         }
         if (count == 0) { /* add .text segment info before listing .sceStub.text. segments. */
             add_to_buffer(TEXT_SEG, segBuf, NULL, mod->text_addr, tempStubTop);
         }
         add_to_buffer(STUB_SEG, segBuf, (&libSegPtr[sIndex])->libName, tempStubTop, (&libSegPtr[sIndex])->stubEnd);
         
         free_libName_buffer(&libSegPtr[sIndex]); //free libName buffer
         (&libSegPtr[sIndex])->stubTop = MAX_CUSTOM_FUNC_STUB_ADDR;
         tempStubTop = MAX_CUSTOM_FUNC_STUB_ADDR;
    }  
}

void map_segments(SceModule2 *mod, const char *modName, LibStubSegment *libSegPtr, const u32 impLibs, u32 const libNameLengths) {
    char *segBuf = NULL;
    char buf[128];
    int ioObjDesc;
    int blockId;
    u32 segBufSize = libNameLengths + DEFAULT_SEG_BUF_SIZE * impLibs;
    
    sprintf(buf, MODULE_MEM_SEGMENTS_FILE_PATH, modName);
    ioObjDesc = create_open_IoObject(IO_FILE, buf, PSP_O_RDWR | PSP_O_CREAT | PSP_O_TRUNC, 0777);
    
    if (IO_OBJECT_DESCRIPTOR_VALID(ioObjDesc)) {
        segBuf = (char *)allocate_memory_buffer(&blockId, MEM_PARTITION_USER, "Memory_Segments", 
                                        PSP_SMEM_High, segBufSize, NULL);
        
        if (segBuf != NULL) {
            strcpy(segBuf, SEGMENT_FILE_HEADLINE);
            add_to_buffer(SCRATCHPAD_SEG, segBuf, NULL, SCRATCHPAD_SEG_START_ADDR, SCRATCHPAD_SEG_END_ADDR);
            sort_lib_sections(mod, segBuf, libSegPtr, impLibs);
            
            sceIoWrite(ioObjDesc, segBuf, segBufSize);
        }
        sceKernelFreePartitionMemory(blockId);
    }
    sceIoClose(ioObjDesc);
}