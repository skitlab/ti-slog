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
 
/*  File contails all the application specific configuration parameters.
 *  An application currently being  executed must first configure this file.
*/

#ifndef CONFIG__include
#define CONFIG__include
  
/*  mode is the mode of operation i.e Registry Based (mode =1) or static
 *  based (mode =0)
*/
//#define mode 0

/*  Number of modules used by the application. This is used only in
 *  static mode 
 */
//#define noofmodules 3

/*  Mode for printing the timestamp; 
 *  0 -> in Hexadecimal; 
 *  1 -> in Decimal;
 *  2 -> in MilliSec 
 *  3 -> Human readable Date/Time format
*/
#define TIMEDISPFORMAT 1

/*  Logger assigned to the module. */
//#define Logger LoggerSys
#define Logger LoggerSys

/*  TimeStampProxy assigned to the module */
#define TIMESTAMPPROXY

/*  Used to eliminating ability to control event masks at runtime.
 *  Set to 0 to eliminate*/
#define Diags_setMaskEnabled 1

/*  Enables additional formats for System _printf */
#define PRINTEXTEND

/* Used to prevent data being loaded into memory 
 * Currently not supported
 */
#define Text_isLoaded 1

/* Logger Object for a module */
#define Module__LOGOBJ loggerObj

/* Notifies whether logger being assigned or not
 * If 0 none of the loggers will work
 */
#define Module__LOGDEF 1

/* Used exclusively by loggerbuf. 
 * Control filtering by level of events
 */
#define LoggerBuf_filterByLevel 0

#endif
