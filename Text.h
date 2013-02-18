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

#ifndef TEXT__include
#define TEXT__include

#define Text_registryModsLastId 0x7fff
#define Text_unnamedModsLastId 0x4000

#include <sstd.h>
#include <Types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* RopeId */
typedef Bits16 Text_RopeId;

String Text_charTab;
int Text_charEnd;

//typedef Bits32 Event;


String Text_RopeText(int index);
Int Text_putSite(Types_Site *site, Char **bufp, Int len);
Int Text_xprintf(Char **bufp, String fmt, ...);
Int Text_putMod(Types_ModuleId mid, Char **bufp, Int len);
Int Text_matchRope(Types_RopeId rope, String pat, Int *lenp);
void stringadd(String str);
Bits32 createEvent(String msg, Bits16 mask, Bits16 level);
#endif /* TEXT_H_ */
/*
 *  @(#) xdc.runtime; 2, 1, 0,292; 9-14-2010 16:36:40; /db/ztree/library/trees/xdc/xdc-v49x/src/packages/
 */
