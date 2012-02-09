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

#include "../header/memory_alloc.h" 

void *allocate_memory_buffer(int *blockId, SceUID partitionId, const char *name, int type, SceSize size, void *addr) {
    
    *blockId = sceKernelAllocPartitionMemory(partitionId, name, type, size, addr);
    if (*blockId >= 0) {
        return sceKernelGetBlockHeadAddr(*blockId);
    }
    return NULL;
}

void free_libName_buffer(LibStubSegment *libSegPtr) {
    if (libSegPtr->libName != NULL) {
        sceKernelFreePartitionMemory(libSegPtr->blockId);
    }
}