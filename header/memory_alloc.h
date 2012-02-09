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
 * memory_alloc.h
 *    Handles Dynamic Memory Allocation.
 * Author: _Felix_
 */

#ifndef MEMORY_ALLOC_H
#define	MEMORY_ALLOC_H

#include <pspsysmem.h>
#include "../header/libraries.h"

/** Indicates the partition to allocate from as User Memory. */
#define MEM_PARTITION_USER      (2)

/** The message for an allocation/creation error. */
#define MEMORY_ERROR_INFO       "\t - A Memory Error occured! Printing of Module info failed.\n\n"

#ifdef	__cplusplus
extern "C" {
#endif  
    
    /**
     * Allocate memory buffer from a memory partition.
     * 
     * @param blockId - Pointer to an int receiving the ID of an allocated block.
     * @param partitionId - The UID of the partition to allocate from.
     * @param name - Name assigned to the new block.
     * @param type - Specifies how the block is allocated within the partition. One of ::PspSysMemBlockTypes.
     * @param size - Size of the memory block, in bytes.
     * @param addr - If type is PSP_SMEM_Addr, then addr specifies the lowest address allocate the block from.
     * 
     * @return A pointer to a buffer on success, otherwise NULL.
     */
    void *allocate_memory_buffer(int *blockId, SceUID partitionId, const char *name, int type, SceSize size, void *addr);
    
    /**
     * Free allocated memory used to hold the library's name. Allocated in 'get_importedLibrary_segAttr'.
     * 
     * @param libSegPtr - Pointer to a libStubSegment to free the allocated memory used by its libName member.
     */
    void free_libName_buffer(LibStubSegment *libSegPtr);


#ifdef	__cplusplus
}
#endif

#endif	/* MEMORY_ALLOC_H */