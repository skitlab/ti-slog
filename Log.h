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

#ifndef LOG__include
#define LOG__include

#include "sstd.h"
#include "Types.h"
#include "Text.h"
#include "Diags.h"
#include <Config.h>


#ifndef Module__MID
#define Module__MID 0x8000
#endif
/* Macros */
#ifndef REGISTRY__MODE

/*
 *  ======== Module__DGSINCL ========
 *  DGSINCL is the mask of all bits which were not configured as ALWAYS_OFF.
 *  In other words, it is the mask of all bits which could *possibly* be on.
 */
#ifndef Module__DGSINCL
#define Module__DGSINCL ~(Diags_dictElems[Module__MID - 0x8000].diagsIncluded)
#endif

/*
 *  ======== Module__DGSENAB ========
 *  DGSENAB is the mask of all bits which were configured as ALWAYS_ON.
 *  If a bit is on in this mask, then the DGSMASK is not checked.
 */
#ifndef Module__DGSENAB
#define Module__DGSENAB (Diags_dictElems[Module__MID - 0x8000].diagsEnabled)
#endif

/*
 *  ======== Module__DGSMASK ========
 *  Redefine the module diags mask to reference the mask that is part of 
 *  xdc_runtime_Registry_CURDESC (which is initialized at runtime).
 */
#ifndef Module__DGSMASK
#define Module__DGSMASK (Diags_dictElems[Module__MID - 0x8000].mask)
#endif

#endif
//#endif


/*-----------------------------------------------------------
 ************************ Extra Code ************************
 *-----------------------------------------------------------
*/
#define _replace_1(logger, write, id) logger##_write##id
#define _replace_2(logger, write, id) _replace_1(logger, write, id)
typedef IArg Log_EventRec__arg[8];


/* NUMARGS */
#define Log_NUMARGS (8)

/* PRINTFID */
#define Log_PRINTFID (0)

/* EventRec */
typedef struct{
    Types_Timestamp64 tstamp;
    Bits32 serial;
    Types_Event evt;
    Log_EventRec__arg arg;
} Log_EventRec;

/* Event */

/* EventId */
typedef Bits16 Log_EventId;
typedef Bits32 Log_Event;

Log_Event Text_Error;
Log_Event Log_L_error;
Log_Event Log_L_construct;
Log_Event Log_L_create;
Log_Event Log_L_destruct;
Log_Event Log_L_delete;
Log_Event Log_L_warning;
Log_Event Log_L_info;



/*-----------------------------------------------------------
 ******************* From Log_epilogue.h*********************
 *-----------------------------------------------------------
*/
/*
 *  ======== xdc_runtime_Log_getEventId ========
 */



#define Diags_setMask(src)    \
    Sdiags_setMask(src)
#define Log_print0(mask, fmt)  \
    Slog_print0(mask, fmt)
#define Log_print1(mask, fmt, a1) \
    Slog_print1(mask, fmt, a1)
#define Log_print2(mask, fmt, a1, a2) \
    Slog_print2(mask, fmt, a1, a2)
#define Log_print3(mask, fmt, a1, a2, a3) \
    Slog_print3(mask, fmt, a1, a2, a3)
#define Log_print4(mask, fmt, a1, a2, a3, a4) \
    Slog_print4(mask, fmt, a1, a2, a3, a4)
#define Log_print5(mask, fmt, a1, a2, a3, a4, a5) \
    Slog_print5(mask, fmt, a1, a2, a3, a4, a5)
#define Log_print6(mask, fmt, a1, a2, a3, a4, a5, a6) \
    Slog_print6(mask, fmt, a1, a2, a3, a4, a5, a6)

/*
 *  Define flags for compiling out all Log calls
 *
 *  The intent of these flags is to allow users to completely optimize logging
 *  out of their code even when not using whole program optimization. This is
 *  implemented by controlling the definitions of the Log macros. This will
 *  only affect code compiled with the flag(s) set, so it will not disable 
 *  logging in any precompiled libraries.
 *
 *  The DISABLE_ALL flag will have the effect of disabling all Log put, write, 
 *  print, error, warning, and info log calls. The flag just has to be defined,
 *  we give it a value of zero or one to use in the macros.
 *
 *  There are additional flags which can be used to disable all log calls
 *  "except for". We use the presence of the DISABLE_ALL flag and the presence
 *  of any ENABLE_ERROR, ENABLE_INFO, or ENABLE_WARNING flags to compute the
 *  value of ENABLE_ERROR, etc., as zero or one.
 *
 *  We ensure that all of the flags are ultimately defined and given a zero or
 *  one value. Then the macro definitions are conditional on the value of the
 *  appropriate flag.
 */

/* 
 * If DISABLE_ALL is defined, give it the value 1, and assign values to all
 * of the ENABLE flags based on whether they've been defined or not.
 */
#ifdef Log_DISABLE_ALL

#define Log_DISABLE_ALL 1

#ifndef Log_ENABLE_ERROR
#define Log_ENABLE_ERROR 0
#else
#define Log_ENABLE_ERROR 1
#endif

#ifndef Log_ENABLE_WARNING
#define Log_ENABLE_WARNING 0
#else
#define Log_ENABLE_WARNING 1
#endif

#ifndef Log_ENABLE_INFO
#define Log_ENABLE_INFO 0
#else
#define Log_ENABLE_INFO 1
#endif

/*
 * If DISABLE_ALL has not been defined, just define it to 0 and define
 * all of the ENABLE flags to 1.
 */
#else
#define Log_DISABLE_ALL 0
#define Log_ENABLE_ERROR 1
#define Log_ENABLE_WARNING 1
#define Log_ENABLE_INFO 1
#endif

/*
 *  ======== xdc_runtime_Log_getMask ========
 */
#define Log_getMask(evt) ((evt) & 0x0000ffff)

/*
 *  ======== xdc_runtime_Log_getRope ========
 */
#define Log_getRope(evt) ((Types_RopeId)((evt) >> 16))

/*
 *  ======== xdc_runtime_Log_getEventId ========
 */
#define Log_getEventId(evt) \
    ((Log_EventId)((evt) >> 16))

/*
 *  ======== xdc_runtime_Log_doPut* ========
 *  The 'doPut' macros are the real implementation of the Log_put* APIs.
 *  The Log_put* macros are just stubs which point to these definitions. We do
 *  this so that we can disable the Log_put APIs but still leave their
 *  functionality available for any other Log macros which use them. 
 *  For example, if the flags DISABLE_ALL and ENABLE_ERROR were set, we'd want
 *  to disable the Log_put* macros, but not the Log_error* macros which are
 *  built on top of Log_put.
 */
#define Log_doPut0(evt, mid) \
    _replace_2(Logger,write,0)(Module__LOGOBJ, (evt), (mid))

#define Log_doPut1(evt, mid, a1) \
    _replace_2(Logger,write,1)(Module__LOGOBJ, (evt), (mid), (a1))

#define Log_doPut2(evt, mid, a1, a2) \
    _replace_2(Logger,write,2)(Module__LOGOBJ, (evt), (mid), (a1), (a2)) 

#define Log_doPut4(evt, mid, a1, a2, a3, a4) \
    _replace_2(Logger,write,4)(Module__LOGOBJ, (evt), (mid), (a1), (a2), (a3), (a4))

#define Log_doPut8(evt, mid, a1, a2, a3, a4, a5, a6, a7, a8) \
    _replace_2(Logger,write,8)(Module__LOGOBJ, (evt), (mid), (a1), (a2), (a3), (a4), \
                     (a5), (a6), (a7), (a8))
                     
/*
 *  ======== xdc_runtime_Log_put* ========
 *  See Log_doPut*
 */              
#if (!Log_DISABLE_ALL)

#define Log_put0(evt, mid) \
    Log_doPut0(evt, mid)

#define Log_put1(evt, mid, a1) \
    Log_doPut1(evt, mid, a1)

#define Log_put2(evt, mid, a1, a2) \
    Log_doPut2(evt, mid, a1, a2)

#define Log_put4(evt, mid, a1, a2, a3, a4) \
    Log_doPut4(evt, mid, a1, a2, a3, a4)

#define Log_put8(evt, mid, a1, a2, a3, a4, a5, a6, a7, a8) \
    Log_doPut8(evt, mid, a1, a2, a3, a4, a5, a6, a7, a8)

#else

#define Log_put0(evt, mid)
#define Log_put1(evt, mid, a1)
#define Log_put2(evt, mid, a1, a2)
#define Log_put4(evt, mid, a1, a2, a3, a4)
#define Log_put8(evt, mid, a1, a2, a3, a4, a5, a6, a7, a8)

#endif

/*
 *  ======== xdc_runtime_Log_doWrite* ========
 *  The real implementations of the Log_write* APIs. See Log_doPut* for an
 *  explanation of why we stub-out the Log_put* and Log_write* APIs.
 */

#define Log_doWrite0(evt) \
    ((Module__LOGDEF && Diags_query(evt)) ? \
        (Log_doPut0((evt), Module__MID)) : (void)0 \
    )
    
#define Log_doWrite1(evt, a1) \
    ((Module__LOGDEF && Diags_query(evt)) ? \
        (Log_doPut1((evt), Module__MID, (a1))) : (void)0 \
    )
     
#define Log_doWrite2(evt, a1, a2) \
    ((Module__LOGDEF && Diags_query(evt)) ? \
        (Log_doPut2((evt), Module__MID, (a1), (a2))) : (void)0 \
    )
    
#define Log_doWrite3(evt, a1, a2, a3) \
    Log_doWrite4(evt, a1, a2, a3, 0)

#define Log_doWrite4(evt, a1, a2, a3, a4) \
    ((Module__LOGDEF && Diags_query(evt)) ? \
        Log_doPut4((evt), Module__MID, (a1), (a2), \
             (a3), (a4)) : (void)0 \
    )

#define Log_doWrite5(evt, a1, a2, a3, a4, a5) \
    Log_doWrite8(evt, a1, a2, a3, a4, a5, 0, 0, 0)
#define Log_doWrite6(evt, a1, a2, a3, a4, a5, a6) \
    Log_doWrite8(evt, a1, a2, a3, a4, a5, a6, 0, 0)
#define Log_doWrite7(evt, a1, a2, a3, a4, a5, a6, a7) \
    Log_doWrite8(evt, a1, a2, a3, a4, a5, a6, a7, 0)

#define Log_doWrite8(evt, a1, a2, a3, a4, a5, a6, a7, a8) \
    ((Module__LOGDEF && Diags_query(evt)) ? \
        Log_doPut8((evt), Module__MID, \
             (a1), (a2), (a3), (a4), (a5), (a6), (a7), (a8)) : (void)0 \
    )
    
/*
 *  ======== xdc_runtime_Log_write* ========
 *  See Log_doWrite*
 */
    
#if (!Log_DISABLE_ALL)
 
#define Log_write0(evt) \
    Log_doWrite0(evt)
    
#define Log_write1(evt, a1) \
    Log_doWrite1(evt, a1)
    
#define Log_write2(evt, a1, a2) \
    Log_doWrite2(evt, a1, a2)
    
#define Log_write3(evt, a1, a2, a3) \
    Log_doWrite3(evt, a1, a2, a3)

#define Log_write4(evt, a1, a2, a3, a4) \
    Log_doWrite4(evt, a1, a2, a3, a4)

#define Log_write5(evt, a1, a2, a3, a4, a5) \
    Log_doWrite5(evt, a1, a2, a3, a4, a5)
    
#define Log_write6(evt, a1, a2, a3, a4, a5, a6) \
    Log_doWrite6(evt, a1, a2, a3, a4, a5, a6)
    
#define Log_write7(evt, a1, a2, a3, a4, a5, a6, a7) \
    Log_doWrite7(evt, a1, a2, a3, a4, a5, a6, a7)

#define Log_write8(evt, a1, a2, a3, a4, a5, a6, a7, a8) \
    Log_doWrite8(evt, a1, a2, a3, a4, a5, a6, a7, a8)
    
#else

#define Log_write0(evt)
#define Log_write1(evt, a1)  
#define Log_write2(evt, a1, a2)
#define Log_write3(evt, a1, a2, a3)
#define Log_write4(evt, a1, a2, a3, a4)
#define Log_write5(evt, a1, a2, a3, a4, a5)
#define Log_write6(evt, a1, a2, a3, a4, a5, a6)
#define Log_write7(evt, a1, a2, a3, a4, a5, a6, a7)
#define Log_write8(evt, a1, a2, a3, a4, a5, a6, a7, a8)

#endif

/*
 *  ======== Slog_print* ========
 *  Since "print" events do not have a rope, we use 0 (an invalid rope value)
 *  as the event Id and construct a Log_Event to pass to Log_put. This has the 
 *  benefit that the Log_Event is equal to just the mask: (0 | mask). For this 
 *  reason, we simply pass the 'mask' as the first argument to 'put'.
 *
 *  Each print function is mapped to a call to appropriate 'put' function.
 *  print0 -> put1
 *  print1 -> put2
 *  print2 -> print3 -> put4
 *  print3 -> put4
 *  print4 -> print6 -> put8
 *  print5 -> print6 -> put8
 *  print6 -> put8
 */

#if (!Log_DISABLE_ALL)
 
#define Slog_print0(mask, fmt) \
    ((Module__LOGDEF && Diags_query(mask)) ? \
        Log_doPut1(mask, Module__MID, (IArg) fmt) : (void)0 \
    )
    
#define Slog_print1(mask, fmt, a1) \
    ( (Module__LOGDEF && Diags_query(mask)) ? \
        Log_doPut2(mask, Module__MID, (IArg) fmt, (a1)) : (void)0 \
    )
    
#define Slog_print2(mask, fmt, a1, a2) \
    Slog_print3(mask, fmt, a1, a2, 0)

#define Slog_print3(mask, fmt, a1, a2, a3) \
    ((Module__LOGDEF && Diags_query(mask)) ? \
        Log_doPut4(mask, Module__MID, (IArg) fmt, \
                               (a1), (a2), (a3)) : (void)0 \
    )

#define Slog_print4(mask, fmt, a1, a2, a3, a4) \
    Slog_print6(mask, fmt, a1, a2, a3, a4, 0, 0)
#define Slog_print5(mask, fmt, a1, a2, a3, a4, a5) \
    Slog_print6(mask, fmt, a1, a2, a3, a4, a5, 0)

#define Slog_print6(mask, fmt, a1, a2, a3, a4, a5, a6) \
    ((Module__LOGDEF && Diags_query(mask)) ?    \
        Log_doPut8(mask, Module__MID, \
             (IArg)fmt, (a1), (a2), (a3), (a4), (a5), (a6), 0) : (void)0  \
    )

#else

#define Slog_print0(mask, fmt)
#define Slog_print1(mask, fmt, a1)
#define Slog_print2(mask, fmt, a1, a2)
#define Slog_print3(mask, fmt, a1, a2, a3)
#define Slog_print4(mask, fmt, a1, a2, a3, a4)
#define Slog_print5(mask, fmt, a1, a2, a3, a4, a5)
#define Slog_print6(mask, fmt, a1, a2, a3, a4, a5, a6)

#endif    

/*
 *  ======== Log_error* ========
 *  Log an error event
 */

#if Log_ENABLE_ERROR
 
#define Log_error0(fmt) \
    Log_error1(fmt,0)
        
#define Log_error1(fmt, a1) \
    ((Module__LOGDEF && Diags_query(Log_L_error)) ? \
        Log_doPut4((Log_L_error), Module__MID, \
             (IArg) __FILE__, (IArg)__LINE__, (IArg)fmt, (a1)) : (void)0 \
    )        
    
#define Log_error2(fmt, a1, a2) \
    Log_error5(fmt, a1, a2, 0, 0, 0)
#define Log_error3(fmt, a1, a2, a3) \
    Log_error5(fmt, a1, a2, a3, 0, 0)
#define Log_error4(fmt, a1, a2, a3, a4) \
    Log_error5(fmt, a1, a2, a3, a4, 0)
    
#define Log_error5(fmt, a1, a2, a3, a4, a5) \
    ((Module__LOGDEF && Diags_query(Log_L_error)) ? \
        Log_doPut8((Log_L_error), Module__MID, (IArg) __FILE__, \
              (IArg)__LINE__, (IArg)fmt, (a1), (a2), (a3), \
              (a4), (a5)) : (void)0 \
    )

#else

#define Log_error0(fmt)
#define Log_error1(fmt, a1)
#define Log_error2(fmt, a1, a2)
#define Log_error3(fmt, a1, a2, a3)
#define Log_error4(fmt, a1, a2, a3, a4)
#define Log_error5(fmt, a1, a2, a3, a4, a5)

#endif

/*
 *  ======== xdc_runtime_Log_warning* ========
 *  Log a warning event
 */

#if Log_ENABLE_WARNING
 
#define Log_warning0(fmt) \
    Log_warning1(fmt,0)
    
#define Log_warning1(fmt, a1) \
    ((Module__LOGDEF && Diags_query(Log_L_warning)) ? \
        Log_doPut4((Log_L_warning), Module__MID, \
             (IArg) __FILE__, (IArg) __LINE__, (IArg) fmt, a1) : (void)0 \
    )
    
#define Log_warning2(fmt, a1, a2) \
    Log_warning5(fmt, a1, a2, 0, 0, 0)
#define Log_warning3(fmt, a1, a2, a3) \
    Log_warning5(fmt, a1, a2, a3, 0, 0)
#define Log_warning4(fmt, a1, a2, a3, a4) \
    Log_warning5(fmt, a1, a2, a3, a4, 0)
    
#define Log_warning5(fmt, a1, a2, a3, a4, a5) \
    ((Module__LOGDEF && Diags_query(Log_L_warning)) ? \
        Log_doPut8((Log_L_warning), Module__MID, (IArg) __FILE__, \
             (IArg) __LINE__, (IArg) fmt, (a1), (a2), (a3), \
             (a4), (a5)) : (void)0 \
    )

#else

#define Log_warning0(fmt)
#define Log_warning1(fmt, a1)
#define Log_warning2(fmt, a1, a2)
#define Log_warning3(fmt, a1, a2, a3)
#define Log_warning4(fmt, a1, a2, a3, a4)
#define Log_warning5(fmt, a1, a2, a3, a4, a5)

#endif
    
/*
 *  ======== Log_info* ========
 *  Log an informational event
 */    
#if Log_ENABLE_INFO

#define Log_info0(fmt) \
    Log_info1(fmt,0)
    
#define Log_info1(fmt, a1) \
    ((Module__LOGDEF && Diags_query(Log_L_info)) ? \
        Log_doPut4((Log_L_info), Module__MID, (IArg) __FILE__, \
              (IArg) __LINE__, (IArg) fmt, (a1)) : (void)0 \
    )        
    
#define Log_info2(fmt, a1, a2) \
    Log_info5(fmt, a1, a2, 0, 0, 0)
#define Log_info3(fmt, a1, a2, a3) \
    Log_info5(fmt, a1, a2, a3, 0, 0)
#define Log_info4(fmt, a1, a2, a3, a4) \
    Log_info5(fmt, a1, a2, a3, a4, 0)
    
#define Log_info5(fmt, a1, a2, a3, a4, a5) \
    ((Module__LOGDEF && Diags_query(Log_L_info)) ? \
        Log_doPut8((Log_L_info), Module__MID, (IArg) __FILE__, \
             (IArg) __LINE__, (IArg) fmt, (a1), (a2), (a3), \
             (a4), (a5)) : (void)0 \
    )

#else

#define Log_info0(fmt)
#define Log_info1(fmt, a1)
#define Log_info2(fmt, a1, a2)
#define Log_info3(fmt, a1, a2, a3)
#define Log_info4(fmt, a1, a2, a3, a4)
#define Log_info5(fmt, a1, a2, a3, a4, a5)

#endif
                     
Void Log_doPrint(Log_EventRec *er);
Void printAscii();
Void printTime(Bits32 hi, Bits32 lo);

#endif /* LOG_H_ */
    
/*
 *  @(#) xdc.runtime; 2, 1, 0,292; 9-14-2010 16:36:39; /db/ztree/library/trees/xdc/xdc-v49x/src/packages/
 */

