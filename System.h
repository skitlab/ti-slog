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

#ifndef SYSTEM__include
#define SYSTEM__include
#include <sstd.h>
#include <Types.h>



struct System_ParseData {
    Int width;
    Bool lFlag;
    Bool lJust;
    Int precis;
    Int len;
    Int zpad;
    Char* end;
    Bool aFlag;
    Char* ptr;
};

Void SSystem_putch(Char ch);
Char *SSystem_formatNum(Char *ptr, UInt32 un, Int zpad, Int base);
Int SSystem_doPrint(Char *buf, String fmt, VaList *pva, Bool aFlag);
Void SSystem_putchar(Char **bufp, Char c);
Int SSystem_printf( String fmt, ... ) ;
Int SSystem_aprintf( String fmt, ... ) ;
Int System_printfExtend(Char **pbuf, Char **pfmt,VaList *pva, 
                          struct System_ParseData *parse);
Int System_vsprintf(Char buf[], String fmt, VaList va);
/*
 *  ======== System_aprintf_va ========
 */
Int System_aprintf_va(String fmt, VaList va);

/*
 *  ======== System_avprintf ========
 */
Int System_avprintf(String fmt, VaList va);

/*
 *  ======== System_printf_va ========
 */
Int System_printf_va(String fmt, VaList va);

/*
 *  ======== System_vprintf ========
 */
Int System_vprintf(String fmt, VaList va);


#endif /* SYSTEM_H_ */
