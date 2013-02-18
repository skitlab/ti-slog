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

#ifndef REGISTRY__include
#define REGISTRY__include

/*
 * ======== INCLUDES ========
 */
#define REGISTRY__MODE
 
 
#include <sstd.h>
#include <Types.h>
#include <Log.h>

#include <Config.h>


//#if mode == 1
#ifndef Module__MID
#define Module__MID ((Registry_findByName("main"))->id)
#endif

#undef Module__DGSINCL
#define Module__DGSINCL  \
    Registry_getDGSINCLMask((Registry_findById(Module__MID))->modName)

#undef Module__DGSENAB	
#define Module__DGSENAB  \
    Registry_getDGSENABMask((Registry_findById(Module__MID))->modName)

#undef Module__DGSMASK	
#define Module__DGSMASK  \
    Registry_getDGSMask((Registry_findById(Module__MID))->modName)
//#endif

typedef Types_RegDesc Registry_Desc;

typedef struct {
    Registry_Desc* listHead;
    Types_ModuleId curId;
}Registry_State;

typedef enum  {
    Registry_SUCCESS,
    Registry_ALLOC_FAILED,
    Registry_ALREADY_ADDED,
    Registry_ALL_IDS_USED
}Registry_Result;



Types_DiagsMask Registry_getDGSINCLMask(String name);
Types_DiagsMask Registry_getDGSENABMask(String name);
Types_DiagsMask Registry_getDGSMask(String name);
Registry_Result Registry_addModule(Registry_Desc *desc, String modName,
                                     Types_DiagsMask RuntimeOn,  
                             Types_DiagsMask AlwaysOff, 
                             Types_DiagsMask AlwaysOn, 
                             Types_DiagsMask RuntimeOff);
Registry_Desc *Registry_findByName(String name);
Registry_Desc *Registry_findByNameInList(String name, Registry_Desc *listHead);
Registry_Desc *Registry_findByNamePattern(String namePat, Int len, 
                                             Registry_Desc *prev);
Bool Registry_matchPattern(String pattern, Int len, String modName);
Registry_Desc *Registry_findById(Types_ModuleId mid);
Bool Registry_getMask(String name, Types_DiagsMask *mask);
Bool Registry_isMember(Types_ModuleId mid);
Registry_Desc *Registry_getNextModule(Registry_Desc *desc);
String Registry_getModuleName(Registry_Desc *desc);
Types_ModuleId Registry_getModuleId(Registry_Desc *desc);    

#endif
