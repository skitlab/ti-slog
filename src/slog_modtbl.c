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
/*
 *  ======== slog_modtbl.c ========
 */
#include <Log.h>
#include <LoggerSys.h>

/* This is the default table */
#define SLOG_DIAGS_ALL_MASKS (Diags_ENTRY | Diags_EXIT | Diags_LIFECYCLE | \
                         Diags_INTERNAL | Diags_ASSERT | Diags_STATUS |    \
                         Diags_USER1 | Diags_USER2 | Diags_USER3 |         \
                         Diags_USER4 | Diags_USER5 | Diags_USER6 |         \
                         Diags_INFO | Diags_ANALYSIS)

#define SLOG_RUNON  0x0000
#define SLOG_ALSON (Diags_ASSERT)
#define SLOG_ALSOFF ~(SLOG_ALSON) 

#define SLOG_MAX_DIAG_TABLE_ENTRY (30)
/* Have table entry for minimum SLOG_MAX_DIAG_TABLE_ENTRY entries, this is 
 * required as app may index any entries
 * & app does not define its own table, so in that case default table needs to 
 * ensure enough entries are present.
 * ofcouse system might crash if more than SLOG_MAX_DIAG_TABLE_ENTRY is indexed
 */
Diags_DictElem Diags_dictElems[SLOG_MAX_DIAG_TABLE_ENTRY] ={
                    {"main", 0x8000, SLOG_RUNON, SLOG_ALSOFF, SLOG_ALSON}, /* 0 */
                    {NULL, 0, 0, 0, 0}, /* 1 */
                    {NULL, 0, 0, 0, 0}, /* 2 */
                    {NULL, 0, 0, 0, 0}, /* 3 */
                    {NULL, 0, 0, 0, 0}, /* 4 */
                    {NULL, 0, 0, 0, 0}, /* 5 */
                    {NULL, 0, 0, 0, 0}, /* 6 */
                    {NULL, 0, 0, 0, 0}, /* 7 */
                    {NULL, 0, 0, 0, 0}, /* 8 */
                    {NULL, 0, 0, 0, 0}, /* 9 */
                    {NULL, 0, 0, 0, 0}, /* 10 */
                    {NULL, 0, 0, 0, 0}, /* 11 */
                    {NULL, 0, 0, 0, 0}, /* 12 */
                    {NULL, 0, 0, 0, 0}, /* 13 */
                    {NULL, 0, 0, 0, 0}, /* 14 */
                    {NULL, 0, 0, 0, 0}, /* 15 */
                    {NULL, 0, 0, 0, 0}, /* 16 */
                    {NULL, 0, 0, 0, 0}, /* 17 */
                    {NULL, 0, 0, 0, 0}, /* 18 */
                    {NULL, 0, 0, 0, 0}, /* 19 */
                    {NULL, 0, 0, 0, 0}, /* 20 */
                    {NULL, 0, 0, 0, 0}, /* 21 */
                    {NULL, 0, 0, 0, 0}, /* 22 */
                    {NULL, 0, 0, 0, 0}, /* 23 */
                    {NULL, 0, 0, 0, 0}, /* 24 */
                    {NULL, 0, 0, 0, 0}, /* 25 */
                    {NULL, 0, 0, 0, 0}, /* 26 */
                    {NULL, 0, 0, 0, 0}, /* 27 */
                    {NULL, 0, 0, 0, 0}, /* 28 */
                    {NULL, 0, 0, 0, 0}, /* 29 */
                    };
/*
 *  @(#) xdc.runtime; 2, 1, 0,292; 9-14-2010 16:36:39; /db/ztree/library/trees/xdc/xdc-v49x/src/packages/
 */

