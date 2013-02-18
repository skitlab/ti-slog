/* 
 *  Copyright (c) 2008 Texas Instruments. All rights reserved. 
 *  This program and the accompanying materials are made available under the 
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at 
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *       Texas Instruments - initial implementation
 * */

/* Command to compile: gcc HelloWorld.c -o test -L"Path of the file libtest.a" -ltest*/

#undef Module__MID
#define Module__MID 0x8000

#include <stdio.h>
#include <Log.h>
#include <LoggerSys.h>

#define MAINRUNON  0xffff
#define MAINALSOFF 0x0000
#define MAINALSON 0x0000
Diags_DictElem Diags_dictElems[2] ={
                    {"main", 0x8000, MAINRUNON, MAINALSOFF, MAINALSON},
                    {NULL, 0, 0, 0, 0}
                    };

	
int main(int argc, String argv[])
{
    Log_print0(Diags_ENTRY, "Hello World");
    return(0);
}

