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
 *  ======== Config.c ========
 */
#include <Diags.h>
#include <Config.h>
#include <Types.h>

/* appropriate logger file to be included depending on the logger
 * being used
 */
#include <LoggerSys.h>
//#include <LoggerBuf.h>

/* declares the Dict_dictBase 
 */
Diags_DictElem* Diags_dictBase = &Diags_dictElems[0];

/* Should be uncommented when the logger Used is loggerSys
 * Else Commented
 */
LoggerSys_Object LoggerSys_Object__table__V = {1};
LoggerSys_Object* loggerObj = (LoggerSys_Object* )&LoggerSys_Object__table__V;

/* Should be uncommented when the logger Used is loggerBuf
 * Else Commented
 */
//LoggerBuf_Object* loggerObj;
//LoggerBuf_Module_State LoggerBuf_state = {0x20,0,0};
//LoggerBuf_Module_State* LoggerBuf_module = &LoggerBuf_state;


/* Assigns appropriate timestamp proxy implementation depending 
 * on the timestamp Macro for loggersys
 */
inline LoggerSys_TimestampProxy_get64(Types_Timestamp64 *result)
{
#ifdef TIMESTAMPPROXY
TimestampStd_get64(result);
#else
TimestampNull_get64(result);
#endif
}


/* Assigns appropriate timestamp proxy implementation depending 
 * on the timestamp Macro for loggerbuf
 */
inline Void LoggerBuf_TimestampProxy_get64(Types_Timestamp64 *result)
{
#ifdef TIMESTAMPPROXY
TimestampStd_get64(result);
#else
TimestampNull_get64(result);
#endif
}


