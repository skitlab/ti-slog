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

#ifndef LOGGERSYS__include
#define LOGGERSYS__include

#include <sstd.h>
#include <Types.h>
#include <Log.h>

/* Object */
typedef struct{
    Bool enabled;
} LoggerSys_Object ;

extern LoggerSys_Object* loggerObj;

/*
 *  ======== LoggerSys_disable ========
 */
Bool LoggerSys_disable(LoggerSys_Object* obj);

/*
 *  ======== LoggerSys_enable ========
 */
Bool LoggerSys_enable(LoggerSys_Object* obj);


Void LoggerSys_write0(LoggerSys_Object* obj, Log_Event evt, Types_ModuleId mid);


/*
 *  ======== write1 =========
 */
Void LoggerSys_write1(LoggerSys_Object* obj, Log_Event evt,
                  Types_ModuleId mid, IArg a1);

/*
 *  ======== write2 =========
 */
Void LoggerSys_write2(LoggerSys_Object* obj, Log_Event evt,
                  Types_ModuleId mid, IArg a1, IArg a2);

/*
 *  ======== write4 =========
 */
Void LoggerSys_write4(LoggerSys_Object* obj, Log_Event evt,
                  Types_ModuleId mid, IArg a1, IArg a2, IArg a3, IArg a4);

/*
 *  ======== write8 =========
 */
Void LoggerSys_write8(LoggerSys_Object* obj, Log_Event evt,Types_ModuleId mid, IArg a1, IArg a2,
                  IArg a3, IArg a4, IArg a5, IArg a6, IArg a7, IArg a8);


#endif /* LOGGERSYS_H_ */
