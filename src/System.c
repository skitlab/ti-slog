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
 *  ======== System.c ========
 */

#include <System.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <Config.h>
/* 
 * the maximum length of a string representing a 32-bit number in base 8 
 * plus 5 to accomodate the decimal point and 4 digits after the decimal 
 * point 
 */
#define OUTMAX      ((32 + 2) / 3) + 5

static const Char digtohex[] = "0123456789abcdef";

Int System_extendFxn(Char **pbuf, Char **pfmt,
    VaList *pva, struct System_ParseData *parse)
    {
    System_printfExtend(pbuf, pfmt, pva, parse);
    }

Int SSystem_printf( String fmt, ... )
{
    Int __ret;
    va_list __va; va_start(__va, fmt);
    __ret = System_printf_va(fmt, __va);
    va_end(__va);
    return __ret;
}

Int SSystem_aprintf( String fmt, ... )
{
    Int __ret;
    va_list __va; va_start(__va, fmt);
    __ret = System_aprintf_va(fmt, __va);
    va_end(__va);
    return __ret;
}

/*
 *  ======== SSSystem_putch ========
 */
Void SSystem_putch(Char ch)
{
    putchar(ch);
}

/*
 *  ======== System_aprintf_va ========
 */
Int System_aprintf_va(String fmt, VaList va)
{
    return (System_avprintf(fmt, va));
}

/*
 *  ======== System_avprintf ========
 */
Int System_avprintf(String fmt, VaList va)
{
    return (SSystem_doPrint(NULL, fmt, &va, TRUE));
}

/*
 *  ======== System_printf_va ========
 */
Int System_printf_va(String fmt, VaList va)
{
    return (System_vprintf(fmt, va));
}

/*
 *  ======== System_vprintf ========
 */
Int System_vprintf(String fmt, VaList va)
{
    return (SSystem_doPrint(NULL, fmt, &va, FALSE));
}

/*
 *  ======== System_vsprintf ========
 */
Int System_vsprintf(Char buf[], String fmt, VaList va)
{
    return (SSystem_doPrint(buf, fmt, &va, FALSE));
}

/*
 *  ======== System_doPrint ========
 *  Internal function
 *
 *  If buf == NULL, characters are sent to System_SupportProxy_putch();
 *  otherwise, they are written into buf. The return value contains the number
 *  of characters printed.
 */
Int SSystem_doPrint(Char *buf, String fmt, VaList *pva, Bool aFlag)
{
    /* temp vars */
    Int     base;
    Char    c;
    Int     res;
    Char    outbuf[OUTMAX];
   
    /* vars passed to SSystem_extendFxn. Also keep track in while loop */
    struct System_ParseData parse;

    parse.aFlag = aFlag;

    res = 0;

    if (fmt == (Char *)NULL) {
        return (res);
    }

    while ((c = *fmt++) != '\0') {
        if (c != '%') {
            SSystem_putchar(&buf, c);
            res++;
        }
        else {
            c = *fmt++;
            /* check for - flag (pad on right) */
            if (c == '-') {
                parse.lJust = TRUE;
                c = *fmt++;
            }
            else {
                parse.lJust = FALSE;
            }
            /* check for leading 0 pad */
            if (c == '0') {
                parse.zpad = 1;
                c = *fmt++;
            }
            else {
                parse.zpad = 0;
            }

            /* allow optional field width/precision specification */
            parse.width = 0;
            parse.precis = -1;

            /* note: dont use isdigit (very large for C30) */
            if (c == '*') {
                parse.width = parse.aFlag
                    ? (int)va_arg(*pva, IArg) : (int)va_arg(*pva, int);
                c = *fmt++;
                if (parse.width < 0) {
                    parse.lJust = TRUE;
                    parse.width = -parse.width;
                }
            }
            else {
                while (c >= '0' && c <= '9') {
                    parse.width = parse.width * 10 + c - '0';
                    c = *fmt++;
                }
            }

            /* allow optional field precision specification */
            if (c == '.') {
                parse.precis = 0;
                c = *fmt++;
                if (c == '*') {
                    parse.precis = parse.aFlag ? (int)va_arg(*pva, IArg) :
                                     (int)va_arg(*pva, int);
                    if (parse.precis < 0) {
                        parse.precis = 0;
                    }
                    
                    c = *fmt++;
                }
                else {
                    while (c >= '0' && c <= '9') {
                        parse.precis = parse.precis * 10 + c - '0';
                        c = *fmt++;
                    }
                }
            }

            /* setup for leading zero padding */
            if (parse.zpad) {
                parse.zpad = parse.width;
            }

            if (parse.precis > parse.zpad) {
                parse.zpad = parse.precis;
            }

            /* check for presence of l flag (e.g., %ld) */
            if (c == 'l' || c == 'L') {
                parse.lFlag = TRUE;
                c = *fmt++;
            }
            else {
                parse.lFlag = FALSE;
            }

            parse.ptr = outbuf;
            parse.end = outbuf + OUTMAX;
            parse.len = 0;

            if (c == 'd' || c == 'i') {
                /* signed decimal */
                Int32 val =
                    parse.aFlag ? (Int32)va_arg(*pva, IArg) :
                    parse.lFlag ? (Int32)va_arg(*pva, long int) :
                    (Int32)va_arg(*pva, int);
                parse.ptr = SSystem_formatNum(parse.end, val, parse.zpad, -10);
                parse.len = parse.end - parse.ptr;
            }
            /* use comma operator to optimize code generation! */
            else if (((base = 10), (c == 'u')) ||       /* unsigned decimal */
                     ((base = 16), (c == 'x')) ||       /* unsigned hex */
                     ((base = 8),  (c == 'o'))) {       /* unsigned octal */

                UInt32 val =
                    parse.aFlag ? (UInt32)va_arg(*pva, IArg) :
                    parse.lFlag ? (UInt32)va_arg(*pva, unsigned long) :
                    (UInt32)va_arg(*pva, unsigned);
                parse.ptr = SSystem_formatNum(parse.end, val, parse.zpad, base);
                parse.len = parse.end - parse.ptr;
            }
            else if ((base = 16), (c == 'p')) {
                parse.zpad = 8;                       /* for 32 bit pointer */
                parse.ptr = SSystem_formatNum(
                    parse.end,
                    parse.aFlag
                        ? (UInt32)va_arg(*pva, IArg) : (UInt32)(UArg)va_arg(*pva, Ptr),
                    parse.zpad, base);
                *(--parse.ptr) = '@';
                parse.len = parse.end - parse.ptr;
            }
            else if (c == 'c') {
                /* character */
                *parse.ptr = parse.aFlag
                    ? (Char)va_arg(*pva, IArg) : (Char)va_arg(*pva, int);
                parse.len = 1;
            }
            else if (c == 's') {
                /* string */
                parse.ptr = parse.aFlag ? (String)iargToPtr(va_arg(*pva, IArg)) :
                              (String)va_arg(*pva, void *);

                /* substitute (null) for NULL pointer */
                if (parse.ptr == (char *)NULL) {
                    parse.ptr = "(null)";
                }
                parse.len = strlen(parse.ptr);
                if (parse.precis != -1 && parse.precis < parse.len) {
                    parse.len = parse.precis;
                }
            }
            else {
                fmt--;
                
                res += System_extendFxn(&buf, &fmt, pva, &parse);                 
            }

            /* compute number of characters left in field */
            parse.width -= parse.len;

            if (!parse.lJust) {
                /* pad with blanks on left */
                while (--parse.width >= 0) {
                    SSystem_putchar(&buf, ' ');
                    res++;
                }
            }

            /* output number, character or string */
            while (parse.len--) {
                SSystem_putchar(&buf, *parse.ptr++);
                res++;
            }
            /* pad with blanks on right */
            if (parse.lJust) {
                while (--parse.width >= 0) {
                    SSystem_putchar(&buf, ' ');
                    res++;
                }
            }
        } /* if */
    } /* while */

    if (buf) {
        *buf = '\0';
    }

    return (res);
}

/*
 *  ======== System_formatNum ========
 *  Internal function
 *
 *  Format unsigned long number in specified base, returning pointer to
 *  converted output.
 *
 *  Note: ptr points PAST end of the buffer, and is decremented as digits
 *  are converted from right to left!
 *
 *  Note: base is negative if n is signed else n unsigned!
 *
 *  ptr  - Pointer to the end of the working buffer where the string version
 *         of the number will be placed.
 *  un   - The unsigned number to be formated
 *  base - The base to format the number into. TODO - signed?
 */
Char *SSystem_formatNum(Char *ptr, UInt32 un, Int zpad, Int base)
{
    Int i = 0;
    Char sign = 0;

    UInt32 n;
    n = un;

    if (base < 0) {
        /* handle signed long case */
        base = -base;
        if ((Int32)n < 0) {
            n = -(Int32)n;

            /* account for sign '-': ok since zpad is signed */
            --zpad;
            sign = '-';
       }
    }

    /* compute digits in number from right to left */
    do {
        *(--ptr) = digtohex[(Int) (n % base)];
        n = n / base;
        ++i;
    } while (n);

    /* pad with leading 0s on left */
    while (i < zpad) {
        *(--ptr) = '0';
        ++i;
    }

    /* add sign indicator */
    if (sign) {
        *(--ptr) = sign;
    }
    return (ptr);
}

/*
 *  ======== System_putchar ========
 *  Internal function
 *
 *  Write character ch to the buffer and, if the buffer pointer is
 *  non-NULL, update the buffer pointer.
 */
Void SSystem_putchar(Char **bufp, Char c)
{
    /*
     *  If the buffer is non-NULL, use it, otherwise call the
     *  proxy's putch function (if it is ready).
     */
    if (*(bufp)) {
        (*(*(bufp))++ = (c));
        return;
    }
    SSystem_putch(c);
}



Int System_printfExtend(Char **pbuf, Char **pfmt,
    VaList *pva, struct System_ParseData *parse)
{
#ifdef PRINTEXTEND
    Char    *fmt = *pfmt;
    Int     res;
    Char    c;
    Bool    found = FALSE;

    /*
     * Create a local variable 'va' to ensure that the dereference of
     * pva only occurs once.
     */
    va_list va = *pva;

    res = 0;

    c = *fmt++;
    *pfmt = *pfmt + 1;


    if (c == '$') {
        c = *fmt++;
        *pfmt = *pfmt + 1;

        if (c == 'F') {
            Types_Site site;

             /* Retrieve the file name string from the argument list */
             site.file = parse->aFlag ? (Char *) iargToPtr(va_arg(va, IArg)) :
                                          (Char *) va_arg(va, Char *);

             /* Retrieve the line number from the argument list. */
             site.line = parse->aFlag ? (Int) va_arg(va, IArg) :
                                          (Int) va_arg(va, Int);

             /*
              * Omit the 'mod' field, set it to 0.
              * '0' is a safe sentinel value - the IDs for named modules are
              * 0x8000 and higher, and the IDs for unnamed modules go from 0x1
              * to 0x7fff.
              */
             site.mod = 0;

             /*
              * Call putSite to format the file and line number.
              * If a precision was specified, it will be used as the maximum
              * string lengrth.
              */
             res = Text_putSite(&site, pbuf, parse->precis);

             /*
              * Set the length to 0 to indicate to 'doPrint' that nothing should
              * be copied from parse.ptr.
              */
             parse->len = 0;

             /* Update the minimum width field */
             parse->width -= res;

             found = TRUE;
        }


        if (c == 'S') {
             /* Retrieve the format string from the argument list */
             parse->ptr = parse->aFlag ?
                 (Char *) iargToPtr(va_arg(va, IArg)) :
                 (Char *) va_arg(va, Char *);

             /* Update pva before passing it to doPrint. */
             *pva = va;

             /* Perform the recursive format. */
             res = SSystem_doPrint(*pbuf, parse->ptr, pva, parse->aFlag);

             /* Update the temporary variable with any changes to *pva */
             va = *pva;

             /*
              * Set the length to 0 to indicate to 'doPrint' that nothing should
              * be copied from parse.ptr.
              */
             parse->len = 0;

             /* Update the minimum width field */
             parse->width -= res;

             /* Indicate that we were able to interpret the specifier. */
             found = TRUE;
        }

    }

    if (c == 'f') {
        Double d;
        ULong  fract;
        Int    negative;


        if (parse->aFlag) {
             //xdc_runtime_Assert_isTrue((sizeof(Float) <= sizeof(IArg)),
               //  xdc_runtime_System_A_cannotFitIntoArg);
             d = argToFloat(va_arg(va, IArg));
        }
        else {
             d = va_arg(va, double);
        }

        if (d < 0.0) {
             d = -d;
             negative = TRUE;
             parse->zpad--;
        }
        else {
             negative = FALSE;
        }

        /*
          * output (error) if we can't print correct value
          */
        /*if (d > (double)LONG_MAX) {
             parse->ptr = "(error)";
             parse->len = 7;                 /* strlen("(error)"); */
     //        goto end;
       //  }

        /* Assumes four digits after decimal point. */
        fract = (ULong)((d - (Long)d) * 1e4);

        parse->ptr = SSystem_formatNum(parse->end, fract, 4, 10);
        *(--parse->ptr) = '.';

#if 0
        /* eliminate trailing zeros */
        do {
        } while (*(--parse->end) == '0');
        ++parse->end;
        parse->len = parse->end - parse->ptr;
#endif

        /* format integer part (right to left!) */
        parse->ptr = SSystem_formatNum(parse->ptr,
             (Long)d, parse->zpad - parse->len, 10);
        if (negative) {
             *(--parse->ptr) = '-';
        }

        parse->len = parse->end - parse->ptr;
        found = TRUE;
    }

    if (found == FALSE) {
        /* other character (like %) copy to output */
        *(parse->ptr) = c;
        parse->len = 1;
    }

    /*
     * Before returning, we must update the value of pva. We use a label here
     * so that all return points will go through this update.
     * The 'goto end' is here to ensure that there is always a reference to the
     * label (to avoid the compiler complaining).
     */
    goto end;
end:
    *pva = va;
    return (res);
#endif
}
/*
 *  @(#) xdc.runtime; 2, 1, 0,292; 9-14-2010 16:36:40; /db/ztree/library/trees/xdc/xdc-v49x/src/packages/
 */

