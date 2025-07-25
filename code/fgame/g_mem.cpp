/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.

This file is part of Quake III Arena source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Quake III Arena source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/
//
//
// g_mem.c
//

#include "g_local.h"

#define POOLSIZE (256 * 1024)

static char memoryPool[POOLSIZE];
static int  allocPoint;

void *G_Alloc(int size)
{
    char *p;

    if (allocPoint + size > POOLSIZE) {
        G_Error("G_Alloc: failed on allocation of %i bytes\n", size);
        return NULL;
    }

    p = &memoryPool[allocPoint];

    allocPoint += (size + 31) & ~31;

    return p;
}

void G_InitMemory(void)
{
    allocPoint = 0;
}

void Svcmd_GameMem_f(void)
{
    G_Printf("Game memory status: %i out of %i bytes allocated\n", allocPoint, POOLSIZE);
}
