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
 *  ======== Text.c ========
 */

#include <System.h>
#include <Types.h>
#include <Registry.h>
#include <string.h>
#include <stdarg.h>

#include <Diags.h>
#include <Text.h>

/*
 *  ======== matchRope ========
 */
Int Text_matchRope(Types_RopeId rope, String pat, Int *lenp)
{
    String modName = Diags_dictElems[rope - 0x8000].modName;
    
    Int len = *lenp;
	while(len--) {
        if(*pat != *modName) {
            /* 
             * If a character in pattern not matches 
             * with module name, return (-1) 
             */
            return (-1);
        }
		/* Move to the next character in the strings */
        pat++;
        modName++;
    }
    /* Successful Traversal */
	return(0);
}


/*
 *  ======== putMod ========
 */
Int Text_putMod(Types_ModuleId mid, Char **bufp, Int len)
{

    /* If this is an unnamed module... */
    if (mid <= Text_unnamedModsLastId) {
        return (Text_xprintf(bufp, "{module#%d}", mid));
    }
    
    /* If this is a dynamically registered module... */
    if (mid <= Text_registryModsLastId) {
        return (Text_xprintf(bufp, Registry_findById(mid)->modName));
    }

    /* If this is a static, named module, but the strings are not loaded... */
    if (!Text_isLoaded) {
        return (Text_xprintf(bufp, "{module-rope:%x}", mid));
    }
    
    /* Otherwise, this is a static, named module. */
	return(Text_xprintf(bufp, "%s", Diags_dictElems[mid-0x8000].modName));
}

/*
 *  ======== putSite ========
 *  len == -1 => infinite output
 *  
 *  If site->mod == 0, the module is unspecified and will be omitted from the output.
 */
Int Text_putSite(Types_Site *site, Char **bufp, Int len)
{
    Int res;
    Int max = len < 0 ? 0x7fff : len;   /* 0x7fff == infinite, well almost */

    res = 0;
    
    if (!site) {
        return (0);
    }

    /* The 'mod' field is optional; 0 if it's unspecified. */
    if (site->mod != 0) {
        res = Text_putMod(site->mod, bufp, max);
        max -= (res + 2);     /* +2 for the ": " string below */
    }
        
    if (max > 0) {
        /* Don't output this if there's no mod */
        if (site->mod != 0) {
            res += Text_xprintf(bufp, ": ");
        }

        if (site->line == 0) {
            return (res);
        }
    
        if (site->file && (max >= ((Int)strlen(site->file) + 4))) {
            Int oc = Text_xprintf(bufp, "\"%s\", ", site->file);
            res += oc;
            max -= oc;
        }
        
        /* 7 = length of "line : ", 10 = max decimal digits in 32-bit number */
        if (max >= (7 + 10)) {
            res += Text_xprintf(bufp, "line %d: ", site->line);
        }
    }

    return (res);
}

/*
 *  ======== ropeText ========
 */
String Text_ropeText(Text_RopeId rope)
{
    return (rope & 0x8000 ? NULL : Text_charTab + rope);
}
/*
 *  ======== xprintf ========
 */
Int Text_xprintf(Char **bufp, String fmt, ...)
{
    va_list va;
    Char *b;
    Int res;

    va_start(va, fmt);
    b = bufp && *bufp ? *bufp : NULL;

    res = System_vsprintf(b, fmt, va);

    if (b) {
        *bufp += res;
    }

    va_end(va);

    return (res);
}

void stringadd(String str)
{
    int i=0;
    String ptr = Text_charTab;
    int size = strlen(str)+ Text_charEnd + 1;
    String temp =(String)malloc(size*(sizeof(char)));
    memset(temp,'\0',size);
    while(i<Text_charEnd-1)
    {
       temp[i]=*ptr;
       ptr++;
       i++;
    }
    if(i!=0)
    temp[i++]='\0';

    while(i<size-1)
    {
       temp[i]=*str;
       str++;
       i++;
    }
    temp[i]='\0';
    Text_charTab = temp;
    Text_charEnd = size;
}

Bits32 createEvent(String msg, Bits16 mask, Bits16 level)
{
    Bits32 temp;
    temp = (Text_charEnd << 16)|(mask|level);
    stringadd(msg);
    return(temp);
}
/*
 *  @(#) xdc.runtime; 2, 1, 0,292; 9-14-2010 16:36:40; /db/ztree/library/trees/xdc/xdc-v49x/src/packages/
 */

