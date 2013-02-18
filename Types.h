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
 *      Texas Instruments - initial implementation
 * */

#ifndef TYPES__include
#define TYPES__include

#include <sstd.h>


typedef Bits16 Types_RopeId;

/* ModuleId*/
typedef Bits16 Types_ModuleId;

/* DiagsMask */
typedef Bits16 Types_DiagsMask;

/* Event */
typedef Bits32 Types_Event;

/* EventId */
typedef Types_Event Types_EventId;



#define Types_getEventId(evt) (\
    (Types_RopeId)((evt) >> 16))

/*
 *  ======== xdc_runtime_Types_makeEvent ========
 */
#define Types_makeEvent(id, site) (\
    (Types_Event)(((Bits32) id) << 16 | ((site) & 0x0000ffff)))

/*
 *  ======== xdc_runtime_Types_getModuleId ========
 */
#define Types_getModuleId(evt) ((evt) & 0x0000ffff)

struct Types_Timestamp64{
    Bits32 hi;
    Bits32 lo;
};

typedef struct Types_Timestamp64 Types_Timestamp64;

struct Types_RegDesc {
    struct Types_RegDesc* next;
    String modName;
    Types_ModuleId id;
    Types_DiagsMask mask;
    Types_DiagsMask diagsIncluded;
    Types_DiagsMask diagsEnabled;
};

typedef struct Types_RegDesc Types_RegDesc;

typedef struct  {
    Ptr handle;
    Types_ModuleId modId;
    String iname;
    Bool named;
}Types_Label;

typedef struct {
    Types_ModuleId mod;
    String file;
    Int line;
} Types_Site;


#endif /* TYPES_H_ */
