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

#include "../header/io.h"

int create_open_IoObject(IoObject objectFlag, const char *path, int flags, SceMode mode) {
    int ioObjDesc;
    
    switch(objectFlag) {
        case IO_FILE:
            ioObjDesc = sceIoOpen(path, flags, mode);
            return ioObjDesc;
        case IO_DIRECTORY:
            ioObjDesc = sceIoDopen(path);
            if (!IO_OBJECT_DESCRIPTOR_VALID(ioObjDesc)) {
                memset(strrchr(path, '/'), 0, 1);
                sceIoMkdir(path, mode);
                ioObjDesc = sceIoDopen(path);
            }
            return ioObjDesc;
        default:
            return IO_OBJECT_ERROR_NOT_SUPPORTED;           
    }
}