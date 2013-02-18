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

#ifndef CONFIGMODULE__include
#define CONFIGMODULE__include


/* Included Files */

#include <Config.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sstd.h"
#include "Types.h"
#include "Diags.h"
#include "Log.h"


/* Macros */
#if mode == 0
#ifdef Module__MID
#if Module__MID < noofmodules

/*
 *  ======== Module__DGSINCL ========
 *  DGSINCL is the mask of all bits which were not configured as ALWAYS_OFF.
 *  In other words, it is the mask of all bits which could *possibly* be on.
 */
#undef Module__DGSINCL
#define Module__DGSINCL ~(Diags_dictElems[Module__MID].diagsIncluded)

/*
 *  ======== Module__DGSENAB ========
 *  DGSENAB is the mask of all bits which were configured as ALWAYS_ON.
 *  If a bit is on in this mask, then the DGSMASK is not checked.
 */
#undef Module__DGSENAB
#define Module__DGSENAB (Diags_dictElems[Module__MID].diagsEnabled)

/*
 *  ======== Module__DGSMASK ========
 *  Redefine the module diags mask to reference the mask that is part of 
 *  xdc_runtime_Registry_CURDESC (which is initialized at runtime).
 */
#undef Module__DGSMASK
#define Module__DGSMASK (Diags_dictElems[Module__MID].mask)
#else
#error Module__MID not correct.
#endif
#endif
#endif

/* Structure storing details about the modules defined in the static mode.
 * @param modName Name of the module
 * @param id Module ID
 * @param mask Runtime configurable mask of the module
 * @param diagsIncluded The mask of all bits which were not configured as ALWAYS_OFF.
 *  In other words, it is the mask of all bits which could *possibly* be on.
 * @param diagsEnabled The mask of all bits which were configured as ALWAYS_ON.
 *  If a bit is on in this mask, then the DGSMASK is not checked.
 */
/*struct Config_ModDesc{
    String modName;
    Types_ModuleId id;
    Types_DiagsMask mask;
    Types_DiagsMask diagsIncluded; 
    Types_DiagsMask diagsEnabled;
};

typedef struct Config_ModDesc ConfigMod_Desc;
*/
//ConfigMod_Desc Diags_dictElems[];

/* Default events. Application's main file should define each of them for 
 * proper working of Log_X APIs
 **/
/*Event Text_Error;
Event Log_L_error;
Event Log_L_construct;
Event Log_L_create;
Event Log_L_destruct;
Event Log_L_delete;
Event Log_L_warning;
Event Log_L_info;
*/
#endif /* CONFIGMODULE_H_ */
