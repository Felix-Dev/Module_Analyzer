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

#include "../header/libraries.h"
#include "../header/memory_alloc.h"

u32 count_imported_libs(SceModule2 *mod) {
    void *stubCur = mod->stub_top;
    void *stubEnd = mod->stub_top + mod->stub_size;
    u32 impLibs = 0;
    
    while (stubCur < stubEnd) { 
           stubCur += ((SceLibraryStubTable *)stubCur)->len * 4;
           impLibs += 1;
           
    }
    return impLibs;
}

SceLibraryStubTable *findImportedLibByName(SceModule2 *mod, const char *libName) {
    void *stubCur = mod->stub_top;
    void *stubEnd = mod->stub_top + mod->stub_size;
    
    while (stubCur < stubEnd) {
           if (strcmp(((SceLibraryStubTable *)stubCur)->libname, libName) == 0) {
               return (SceLibraryStubTable *)stubCur;
           }
           stubCur += ((SceLibraryStubTable *)stubCur)->len * 4;
    }
    return NULL;
}

int get_imported_libraries(SceModule2 *mod, const char *modName, LibStubSegment *libSeg) {
    void *stubCur = mod->stub_top;
    void *stubEnd = mod->stub_top + mod->stub_size;
    int ioOpenFlag = PSP_O_RDWR | PSP_O_CREAT | PSP_O_TRUNC;
    int libNameLengths = 0;
    int index = 0;
    
    while (stubCur < stubEnd) {
           map_imported_functions(&ioOpenFlag, (SceLibraryStubTable *)stubCur, modName, &libSeg[index], &libNameLengths);    
           stubCur += ((SceLibraryStubTable *)stubCur)->len * 4;
           index++;
    }
    return libNameLengths;
}

u32 get_importedLibrary_segAttr(SceLibraryStubTable *stubTable, LibStubSegment *libSegPtr, u32 stubs) {
    int stubTop = stubTable->stubtable;
    int stubEnd = stubTop + stubs * STUB_SIZE;
    
    libSegPtr->libName = (char *)allocate_memory_buffer(&libSegPtr->blockId, MEM_PARTITION_USER, "Library Name", 
                                                        PSP_SMEM_High, sizeof(stubTable->libname), NULL);
    strcpy(libSegPtr->libName, stubTable->libname);
    
    libSegPtr->stubTop = stubTop;
    libSegPtr->stubEnd = stubEnd;
    
    return strlen(stubTable->libname);
}