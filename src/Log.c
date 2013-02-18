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
 *  ======== Log.c ========
 */
#include <sstd.h>

#include <System.h>
#include <Text.h>
#include <Types.h>

#include <Log.h>
#include <time.h>

/*
 * Conditionally set the format string depending on the width of data 
 * primitives. This should be removed once System_printf supports
 * 32-bit format strings
 */
#if (bitsPerChar * sizeof_Int) == 32
#define SERIAL "#%010u "
#define HI "%0.8x:"
#define LO "%0.8x] "
#elif (bitsPerChar * sizeof_Long) == 32 
#define SERIAL "#%010lu "
#define HI "%0.8lx:"
#define LO "%0.8lx] "
#else
#error xdc.runtime.Log does not support this target. 
#endif


/*
 *  ======== doPrint ========
 */
Void Log_doPrint(Log_EventRec *er)
{
    Text_RopeId rope;
    String fmt;
    Bits32 hi, lo;

    /* print serial number if there is one; 0 isn't a valid serial number */
    if (er->serial) {
        SSystem_printf(SERIAL, er->serial);
    }

    /* print timestamp if there is one; ~0 isn't a valid timestamp value */
    hi = er->tstamp.hi;
    lo = er->tstamp.lo;
    
#if TIMEDISPFORMAT == 0
        if (lo != ~0 && hi != ~0) {
            SSystem_printf("[t=0x");	
        if (hi) {
            SSystem_printf(HI, hi);
        }
        SSystem_printf(LO, lo);
	}
#elif TIMEDISPFORMAT == 1 || TIMEDISPFORMAT == 2 || TIMEDISPFORMAT == 3
        printTime(hi, lo);
#endif

    /* print module name */
    Text_putMod((Text_RopeId)Types_getModuleId(er->evt), NULL, -1);
    SSystem_printf(": ");
    
    /* print event */
    rope = Types_getEventId(er->evt);   /* the event id is the message rope */
    if (rope == 0) {
        /* Log_print() event */
        SSystem_aprintf((String)iargToPtr(er->arg[0]),
            er->arg[1], er->arg[2], er->arg[3], er->arg[4], 
            er->arg[5], er->arg[6], 0,          0);
    }
    else {
        /* Log_write() event */
        fmt = Text_ropeText(rope);
    
        if (Text_isLoaded) {
            SSystem_aprintf(fmt, er->arg[0], er->arg[1], er->arg[2], er->arg[3],
                er->arg[4], er->arg[5], er->arg[6], er->arg[7]);
        }
        else {
            SSystem_aprintf("{evt: fmt=%p, args=[0x%x, 0x%x ...]}",
                fmt, er->arg[0], er->arg[1]);
        }
    }

    SSystem_putch('\n');
}

/*
 *  ======== printAscii ========
 */
Void printAscii()
{
#define MAXTIMELEN 30
    time_t rawtime;
    struct tm * timeinfo;
    char* timeascii;
    char outputstring[MAXTIMELEN];
    
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    timeascii = asctime (timeinfo);
    
        if(strlen(timeascii) > MAXTIMELEN -1)
        {
            SSystem_printf("Time Length Exceeded ");
        }
        else
        {
            memset(outputstring, '\0', MAXTIMELEN);
            strncpy(outputstring, timeascii, MAXTIMELEN);
            outputstring[strlen(timeascii)-1] = ' ';
            SSystem_printf ( "%s", outputstring );
        }
}

/*
 *  ======== printTime ========
 */
Void printTime(Bits32 hi, Bits32 lo)
{
#if TIMEDISPFORMAT == 1 || TIMEDISPFORMAT == 2
    Long decTime;
#if TIMEDISPFORMAT == 2
	Long msfactor;
#endif
    if (lo != ~0 && hi != ~0) {
        SSystem_printf("[t=");
        if(hi)
            decTime = ((hi)<<32 || (lo));
        else
            decTime = (lo);
#if TIMEDISPFORMAT == 1
        SSystem_printf("%0.8ld] ",decTime);
#elif TIMEDISPFORMAT == 2
        msfactor = CLOCKS_PER_SEC/1000;
        SSystem_printf("%0.8ld ms] ",decTime/msfactor);
#endif
    }

#elif TIMEDISPFORMAT == 3
printAscii();
#endif
}
/*
 *  @(#) xdc.runtime; 2, 1, 0,292; 9-14-2010 16:36:39; /db/ztree/library/trees/xdc/xdc-v49x/src/packages/
 */

