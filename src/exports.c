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

#include "../header/exports.h"

const char *analyze_exported_nid(u32 nid) {
    switch(nid) {
        case MODULE_BOOTSTART:
            return "function: module_bootstart             ";
        case MODULE_START:
            return "function: module_start                 ";
        case MODULE_STOP:
            return "function: module_stop                  ";
        case MODULE_START_THREAD_PARAM:
            return "variable: module_start_thread_parameter";
        case MODULE_STOP_THREAD_PARAM:
            return "variable: module_stop_thread_parameter ";
        case MODULE_INFO:
            return "variable: module_info                  ";
        default:
            return "Unknown function/variable.             ";
    }
}

void get_exported_libraries(SceModule2 *mod, const char *modName) {
    void *entCur = mod->ent_top;
    void *entEnd = mod->ent_top + mod->ent_size;
    int ioOpenFlag = PSP_O_RDWR | PSP_O_CREAT | PSP_O_TRUNC;
    
    while (entCur < entEnd) {
           map_exported_functions(&ioOpenFlag, (SceLibraryEntryTable *)entCur, modName);    
           entCur += ((SceLibraryEntryTable *)entCur)->len * 4;
    } 
}

 void map_exported_functions(int *ioOpenFlag, SceLibraryEntryTable *entTable, const char *modName) {
    char *libExportsBuf = NULL;
    char buf[128];
    u32 exports;
    int ioObjDesc;
    u32 textLength;
    u32 libExpBufSize;
    int blockId;
    
    memset(buf, 0, sizeof(buf));   
    
    sprintf(buf, MODULE_LIB_EXPORTS_FILE_PATH, modName);
    ioObjDesc = create_open_IoObject(IO_FILE, buf, *ioOpenFlag, 0777);
    
    if (IO_OBJECT_DESCRIPTOR_VALID(ioObjDesc)) {
        exports = entTable->stubcount + entTable->vstubcount;
        textLength = sprintf(buf, "-Exported NIDs from library: %s\n", entTable->libname);
        libExpBufSize = textLength + EXPORTED_NID_INFO_LINE_LENGTH * exports;
        
        libExportsBuf = (char *)allocate_memory_buffer(&blockId, MEM_PARTITION_USER, "library_exports", 
                                               PSP_SMEM_High, libExpBufSize, NULL);
        
        if (libExportsBuf != NULL) {
            strncpy(libExportsBuf, buf, libExpBufSize); 
            
            int i;
            for (i = 0; i < exports; i++) {
                 u32 nid = ((u32 *)entTable->entrytable)[i]; 
                 textLength = sprintf(buf, EXPORTED_NID_INFO_LINE, i + 1, nid, ((u32 *)entTable->entrytable)[i + exports], 
                                      analyze_exported_nid(nid)); 
                 strncat(libExportsBuf, buf, textLength);
            }
            sceIoWrite(ioObjDesc, libExportsBuf, libExpBufSize);
            sceKernelFreePartitionMemory(blockId);   
        }
        else {
             sceIoWrite(ioObjDesc, MEMORY_ERROR_INFO, strlen(MEMORY_ERROR_INFO));
        }
    }
    sceIoClose(ioObjDesc);
    *ioOpenFlag = PSP_O_RDWR | PSP_O_CREAT | PSP_O_APPEND;
} 