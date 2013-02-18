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

#ifndef DIAGS__include
#define DIAGS__include

#include <sstd.h>
#include <Types.h>


/*---------------------------------------------------------------
 *************** From Diags_epilogue.h **************************
 *---------------------------------------------------------------
 */
/*
 *  ======== xdc_runtime_Diags_query ========
 *  Returns true iff:
 *       1. the current module's included diags intersect evt's mask, and
 *       2. either the permanently enabled diags intersect evt's mask or
 *          the runtime controllable diags intersect evt's mask.
 */
#define Diags_query(evt) \
    (Module__DGSINCL & (evt) \
        && (Module__DGSENAB & (evt) || Module__DGSMASK & (evt)))

/*
 *  ======== xdc_runtime_Diags_getLevel ========
 *  Returns the event level set in the given diags mask. The level is a value
 *  stored using two bits of the diags mask.
 */
#define Diags_getLevel(mask) \
    (Diags_LEVEL & mask)

/*
 *  ======== xdc_runtime_Diags_compareLevels ========
 *  The definition of the diags levels assigns the value '0' to the highest
 *  priority events and '3' to the lowest, so the comparison is done backwards.
 *  For example, for (LEVEL4 (0), LEVEL1 (3)) this must return false.
 */
#define Diags_compareLevels(levelA, levelB) \
    (levelA > levelB)
/*
 *  @(#) xdc.runtime; 2, 1, 0,292; 9-14-2010 16:36:39; /db/ztree/library/trees/xdc/xdc-v49x/src/packages/
 */


/*---------------------------------------------------------------
 ****************************************************************
 *---------------------------------------------------------------
 */
/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Mask */
typedef Types_DiagsMask Diags_Mask;

/* ENTRY */
#define Diags_ENTRY (0x0001)

/* EXIT */
#define Diags_EXIT (0x0002)

/* LIFECYCLE */
#define Diags_LIFECYCLE (0x0004)

/* INTERNAL */
#define Diags_INTERNAL (0x0008)

/* ASSERT */
#define Diags_ASSERT (0x0010)

/* STATUS */
#define Diags_STATUS (0x0080)

/* LEVEL */
#define Diags_LEVEL (0x0060)

/* USER1 */
#define Diags_USER1 (0x0100)

/* USER2 */
#define Diags_USER2 (0x0200)

/* USER3 */
#define Diags_USER3 (0x0400)

/* USER4 */
#define Diags_USER4 (0x0800)

/* USER5 */
#define Diags_USER5 (0x1000)

/* USER6 */
#define Diags_USER6 (0x2000)

/* USER7 */
#define Diags_USER7 (0x4000)

/* INFO */
#define Diags_INFO (0x4000)

/* USER8 */
#define Diags_USER8 (0x8000)

/* ANALYSIS */
#define Diags_ANALYSIS (0x8000)

/* ALL */
#define Diags_ALL (0xFF9F)

/* ALL_LOGGING */
#define Diags_ALL_LOGGING (0xFF9F & (~0x0010) & (~0x0008))

/* EventLevel */
enum Diags_EventLevel {
    Diags_LEVEL1 = 0x0,
    Diags_LEVEL2 = 0x20,
    Diags_LEVEL3 = 0x40,
    Diags_LEVEL4 = 0x60
};
typedef enum Diags_EventLevel Diags_EventLevel;

/* EMERGENCY */
#define Diags_EMERGENCY (Diags_LEVEL1)

/* CRITICAL */
#define Diags_CRITICAL (Diags_LEVEL2)

/* ERROR */
#define Diags_ERROR (Diags_LEVEL3)

/* WARNING */
#define Diags_WARNING (Diags_LEVEL4)


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* DictElem */
typedef struct {
    String modName;
    Types_ModuleId modId;
    Types_DiagsMask mask;
    Types_DiagsMask diagsIncluded; 
    Types_DiagsMask diagsEnabled;
} Diags_DictElem;

extern Diags_DictElem Diags_dictElems[];

extern Diags_DictElem* Diags_dictBase;


Void Sdiags_setMask(String src);

#endif /* DIAGS_H_ */
