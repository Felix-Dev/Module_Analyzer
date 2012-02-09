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
 * libraries.h
 * Author: _Felix_
 *
 */

#ifndef LIBRARIES_H
#define	LIBRARIES_H

#include <pspiofilemgr.h>
#include <psploadcore.h>
#include <psptypes.h>

/** The size of a function stub. */
#define STUB_SIZE       (8)

#ifdef	__cplusplus
extern "C" {
#endif
    
    /** Information about a .sceStub.text. segment. */
    typedef struct _LibStubSegment {
        /** The name of the imported library. */
        char *libName;
        /** The start addres of a .sceStub.text segment. */
        u32 stubTop;
        /** The end addres of a .sceStub.text segment. */
        u32 stubEnd;
        /** The ID of the allocated memory block to hold the libName. */
        int blockId;
    } LibStubSegment;
    
    
    /**
     * Count imported libraries of a module.
     * 
     * @param mod - Pointer to a SceModule2 struct of a module to count its imported libraries.
     * 
     * @return The number of imported libraries.
     */    
    u32 count_imported_libs(SceModule2 *mod);
    
    /**
     * Find an imported library by its name.
     * 
     * @param mod - The module importing the library searched for.
     * @param libName - The name of the library.
     * 
     * @return Pointer to its ::SceLibraryStubTable if found, otherwise NULL.
     */
    SceLibraryStubTable *find_imported_lib_by_name(SceModule2 *mod, const char *libName);
    
    /**
     * Set up analyzing of the imported libraries of the specified module.
     * 
     * @param mod - The module to receive its imported libraries from.
     * @param modName - The name of the module.
     * @param libSegPtr - Pointer to a LibStubSegment to store the libraries sceStub.text. segment attributes.
     * 
     * @return The length of the imported libraries' names.
     */
    int get_imported_libraries(SceModule2 *mod, const char *modName, LibStubSegment *libSeg);
    
    /**
     * Retrieve attributes of an imported library (its name, its stubTop and its stubEnd)
     * in order to determine its .sceStub.text. segment.
     * 
     * @param stubTable - The current library to analyze.
     * @param libSegPtr - Pointer to a LibStubSegment to store the library's sceStub.text. segment attributes.
     * @param stubs - The number of imported NIDs belonging to this library.
     * 
     * @return The length of the library's name belonging to the .sceStub.text segment.
     */
    u32 get_importedLibrary_segAttr(SceLibraryStubTable *stubTable, LibStubSegment *libSegPtr, u32 stubs);


#ifdef	__cplusplus
}
#endif

#endif	/* LIBRARIES_H */

