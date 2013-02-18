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

#ifndef Void
#ifndef std__include
#define std__include

#include <stdarg.h>
#include <stddef.h>

/* macros to simplify "stringification" and computed includes */
#define stringify(a) #a
#define local_include(a) stringify(a.h)
#define system_include(m) <m.h>

/* TitleCase standard types */

#define Void        void

typedef char             Char;
typedef unsigned char    UChar;
typedef short            Short;
typedef unsigned short  UShort;
typedef int              Int;
typedef unsigned int    UInt;
typedef long             Long;
typedef unsigned long    ULong;
typedef float            Float;
typedef double           Double;
typedef long double     LDouble;
typedef size_t           SizeT;
typedef va_list          VaList;

/* Generic Extended Types */

typedef unsigned short  Bool;
typedef void             *Ptr;        /* data pointer */
typedef char             *String;    /* null terminated string */
#if 0
/* we intentionally omit arguments from Fxn to indicate that it can have
 * any (or none).  Unfortunately this causes gcc to emit warnings when
 * -Wstrict-prototypes is used.  Newer gcc's support a pragma that
 * may work around this:
 *
 *    #pragma GCC diagnostic ignored "-Wstrict-prototype"
 */
typedef int              (*Fxn)();    /* function pointer */

/*
 * Import the target-specific std.h
 */
#ifdef target_types__
#define target__ <target_types__>
#endif
#ifdef target__
#include target__
#else
/*
 * 'target_types__' must be defined to name a target-specific header
 * file (e.g., ti/targets/std.h) that has definitions for the basic types:
 * Int8, Int16, ...
 *
 * For example, to build for a target in the ti.targets package you should
 * add the following Option to your compiler's command line:
 *    -Dtarget_types__=ti/targets/std.h
 */


/* the following definitions are required to keep the compiler from
 * complaining about references to these types in the rest of this header;
 * some compilers do not stop parsing this file after the #error above.
 */
typedef int IArg;
typedef unsigned int UArg;
typedef signed char Int8;
typedef unsigned char UInt8;
typedef short Int16;
typedef unsigned short UInt16;
typedef int Int32;
typedef unsigned int UInt32;
#endif
#endif

#include <gnu_targets_arm_std.h>

typedef unsigned short Bits16;
typedef unsigned int  Bits32;
typedef unsigned char Bits8;








/* Long Long Types */

#ifdef LONGLONG__
typedef long long                LLong;
typedef unsigned long long       ULLong;

#else

#ifndef INT64__
/* If the target doesn't support "long long" or a 64-bit integral type, we
 * simply use "long".  This is done to ensure that the type LLong always
 * exists, it's at least as long as a "long", and it's 64-bits wide whenever
 * possible.
 */
typedef long                     LLong;
typedef unsigned long            ULLong;
#endif

#endif

/* Arg to Ptr and Fxn conversion operators
 *
 * Individual targets may override these definitions in the event
 * that compilers issue warnings about shortening of an Arg to a pointer,
 * for example.
 */
#ifndef ARGTOPTR
static inline Ptr iargToPtr(IArg a) { return ((Ptr)a); }
static inline Ptr uargToPtr(UArg a) { return ((Ptr)a); }
#endif

/*#ifndef ARGTOFXN
static inline Fxn iargToFxn(IArg a) { return ((Fxn)a); }
static inline Fxn uargToFxn(UArg a) { return ((Fxn)a); }
#endif
*/

#ifndef ARGTOFLOAT
/*
 * functions to convert a single precision float to an arg
 * Here assumption is that sizeof(Float) <= sizeof(IArg);
 */
typedef union FloatData {
    Float f;
    IArg  a;
} FloatData;

static inline IArg floatToArg(Float f)
{
     FloatData u;
     u.f = f;

     return (u.a);
}

static inline Float argToFloat(IArg a)
{
     FloatData u;
     u.a = a;

     return (u.f);
}
#endif

/* restrict keyword */
#ifndef xdc__RESTRICT__
#define restrict
#endif

/* Standard Constants */

#undef NULL
#define NULL 0

#undef FALSE
#define FALSE 0

#undef TRUE
#define TRUE 1

/* Declaration Qualifiers */

#ifndef __FAR__
#define __FAR__
#endif



#endif /* STD_H_ */
#endif
