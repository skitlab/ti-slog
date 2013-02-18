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
/*
 *  ======== Registry.c ========
 */
#include <Types.h>
#include <Text.h>
#include <string.h>

#include <Registry.h>

/* Min and max registry module ids, inclusive. */
#define MAXMID  Text_registryModsLastId
#define MINMID  (Text_unnamedModsLastId + 1)

Registry_State Det_Registry = {NULL, 0x6fff};
Registry_State* Registry_module = &Det_Registry;

/*
 *  ======== Registry_addModule ========
 */
Registry_Result Registry_addModule(Registry_Desc *desc, String modName,
                                   Types_DiagsMask RuntimeOn,  
                                   Types_DiagsMask AlwaysOff, 
                                   Types_DiagsMask AlwaysOn, 
                                   Types_DiagsMask RuntimeOff)
{    
    /* First, verify the module has not already been added to the module. */
    if (Registry_findByName(modName) != NULL) {
        return (Registry_ALREADY_ADDED);
    }
    
    /* First verify there are more module ids available. */
    if (Registry_module->curId == MINMID) {
        return (Registry_ALL_IDS_USED);
    }
    
    /* Create a new "registry" module */
    
    /* Fill out the descriptor. */
    desc->id = Registry_module->curId--;
    desc->modName = modName;
    
    /* 
     * Initialize the new module's mask with the runtime values of the
     * Registry mask. This will enable any bits which are RUNTIME_ON.
     */
    desc->mask = RuntimeOn;
    desc->diagsIncluded = ~(AlwaysOff);
    desc->diagsEnabled = AlwaysOn;
    
    /* Add the descriptor to the current list. */
    desc->next = Registry_module->listHead;
    Registry_module->listHead = desc;
        
    return (Registry_SUCCESS);
}

/*
 *  ======== Registry_findByName ========
 */
Registry_Desc *Registry_findByName(String name)
{
    return (Registry_findByNameInList(name, Registry_module->listHead));
}

/*
 *  ======== Registry_findByNameInList ========
 */
Registry_Desc *Registry_findByNameInList(String name, Registry_Desc *listHead)
{
    Registry_Desc *dp;

    for (dp = listHead; dp != NULL; dp = dp->next) {
        if (strcmp(dp->modName, name) == 0) {
            return (dp);
        }
    }

    return (NULL);
}

/*
 *  ======== Registry_findByNamePattern ========
 */
Registry_Desc *Registry_findByNamePattern(String namePat, Int len, Registry_Desc *prev)
{
    Registry_Desc *dp;
    
    /* 
     * Determine where to start in the list. 
     * If this is the first call, start at the head.
     */
    if (prev == NULL) {
        dp = Registry_module->listHead;
    }
    /* Otherwise, start where we left off. */
    else {
        dp = prev->next;
    }
    
    /* Loop through the modules. */
    for (; dp != NULL; dp = dp->next) {
        /* If the module's name matches the pattern, return the descriptor. */
        if (Registry_matchPattern(namePat, len, dp->modName)) {
            return (dp);
        }
    }

    return (NULL);
}

/*
 *  ======== matchPattern ========
 *  Determines whether a given module name matches a given pattern.
 */
Bool Registry_matchPattern(String pattern, Int len, String modName)
{
    /* 
     * Move through both strings one character at a time. 
     * Break when:
     *  1. The characters don't match, but the pattern character is the
     *     wildcard, so the strings match.
     *  2. The characters don't match, and the pattern character is not
     *     the wildcard, so the strings don't match.
     *  3. We've reached the end of the pattern.
     */
    while (len--) {
        if (*pattern != *modName) {
            /* 
             * If the next character in 'pattern' is the wildcard, then the 
             * module name matches. 
             */
            return (*pattern == '%');
        }
        
        /* Move to the next character in the strings */
        pattern++;
        modName++;
    }

    /* 
     * We've reached the end of the pattern. If we've also reached the end
     * of the module name, then we have a match.
     */
    return (*modName == '\0');
}

/*
 *  ======== Registry_findById ========
 */
Registry_Desc *Registry_findById(Types_ModuleId mid)
{
    Registry_Desc *dp;

    for (dp = Registry_module->listHead; dp != NULL; dp = dp->next) {
        if (dp->id == mid) {
            return (dp);
        }
    }

    return (NULL);
}

/*
 *  ======== Registry_getMask ========
 */
Bool Registry_getMask(String name, Types_DiagsMask *mask)
{
    Registry_Desc *dp = Registry_findByName(name);

    if (dp != NULL) {
        *mask = dp->mask;
        return (TRUE);
    }

    return (FALSE);
}

/*
 *  ======== Registry_isMember ========
 */
Bool Registry_isMember(Types_ModuleId mid)
{
    return (mid <= MAXMID && mid >= MINMID);
}

/*
 *  ======== Registry_getNextModule ========
 */
Registry_Desc *Registry_getNextModule(Registry_Desc *desc)
{
    if (desc == NULL) {
        return (Registry_module->listHead);
    }
    else {
        return (desc->next);
    }
}

/*
 *  ======== getModuleName ========
 */
String Registry_getModuleName(Registry_Desc *desc)
{
    return (desc->modName);
}

/*
 *  ======== getModuleId ========
 */
Types_ModuleId Registry_getModuleId(Registry_Desc *desc)
{
    return (desc->id);
}
    

Types_DiagsMask Registry_getDGSINCLMask(String name)
{
    Registry_Desc *dp = Registry_findByName(name);
        if (dp != NULL) {
        return ( dp->diagsIncluded);
    }
    return (0);
}



Types_DiagsMask Registry_getDGSENABMask(String name)
{
    Registry_Desc *dp = Registry_findByName(name);
        if (dp != NULL) {
        return ( dp->diagsEnabled);
    }

    return (0);
}


Types_DiagsMask Registry_getDGSMask(String name)
{
    Registry_Desc *dp = Registry_findByName(name);
        if (dp != NULL) {
        return ( dp->mask);
    }

    return (0);
}
/*
 *  @(#) xdc.runtime; 2, 1, 0,292; 9-14-2010 16:36:40; /db/ztree/library/trees/xdc/xdc-v49x/src/packages/
 */
