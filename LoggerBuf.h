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

#ifndef LOGGERBUF__include
#define LOGGERBUF__include
#include "sstd.h"
#include "Diags.h"
#include "Log.h"
#include <Types.h>
#include <TimestampStd.h>
#include <TimestampNull.h>

/* BufType */
enum LoggerBuf_Buf_Type {
    LoggerBuf_BufType_CIRCULAR,
    LoggerBuf_BufType_FIXED
};

typedef enum LoggerBuf_Buf_Type LoggerBuf_BufType;

/* FULL */
#define LoggerBuf_FULL (-1)

/* WRAP */
#define LoggerBuf_WRAP (0)

/* NEXT */
#define LoggerBuf_NEXT (1)

typedef struct {
    Types_Timestamp64 tstamp;
    Bits32 serial;
    Types_Event evt;
    IArg arg1;
    IArg arg2;
    IArg arg3;
    IArg arg4;
} LoggerBuf_Entry;

typedef struct {
    Diags_Mask level1;
    Diags_Mask level2;
    Diags_Mask level3;
}LoggerBuf_Module_State;

/* Module__state__V */

/* Object */
typedef struct{
    LoggerBuf_Entry * entryArr;
    LoggerBuf_Entry* curEntry;
    LoggerBuf_Entry* endEntry;
    LoggerBuf_Entry* readEntry;
    LoggerBuf_BufType type;
    Bits32 serial;
    Int16 numEntries;
    Int8 advance;
    Bool enabled;
    Bool flush;
}LoggerBuf_Object;

extern LoggerBuf_Object* loggerObj;
extern LoggerBuf_Module_State* LoggerBuf_module;

Int LoggerBuf_Instance_init();
Void LoggerBuf_Instance_finalize(LoggerBuf_Object *obj, Int status);
Void LoggerBuf_instanceStartup(LoggerBuf_Object *obj);
/*
 *  ======== LoggerBuf_enable ========
 */
Bool LoggerBuf_enable(LoggerBuf_Object* obj);

/*
 *  ======== LoggerBuf_disable ========
 */
Bool LoggerBuf_disable(LoggerBuf_Object* obj);

Void LoggerBuf_write0(LoggerBuf_Object* obj, Log_Event evt,Types_ModuleId mid);
Void LoggerBuf_write1(LoggerBuf_Object* obj, Log_Event evt,Types_ModuleId mid, IArg a1);
Void LoggerBuf_write2(LoggerBuf_Object* obj, Log_Event evt,Types_ModuleId mid, IArg a1, IArg a2);
Void LoggerBuf_write4(LoggerBuf_Object* obj, Log_Event evt, Types_ModuleId mid, IArg a1,
                        IArg a2, IArg a3, IArg a4);
Void LoggerBuf_write8(LoggerBuf_Object* obj, Log_Event evt, Types_ModuleId mid, IArg a1, IArg a2, 
                        IArg a3, IArg a4, IArg a5, IArg a6, IArg a7, IArg a8);
//Void LoggerBuf_flushAll();
//Void LoggerBuf_flushAllInternal(Int stat);

Void SharedMemoryBuffer(unsigned int add);
Void LoggerBuf_flush();
Int LoggerBuf_getNextEntry(LoggerBuf_Object *obj, Log_EventRec *evtRec);


#endif /* LOGGERBUF_H_ */
