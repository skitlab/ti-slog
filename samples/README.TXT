This utility is used in the EZSDK system, shows the detailed information about execution staus of each core & run time status of various modules. This utility can be used for various purpose like debug, analze, statistic collection, etc...

This utility has the look & feel of linux top and called as System Top or sys_top. One can filter the information by core id and by modules (Heap, Shared region) similar to the way we filter in Linux top command.

Usage:
=====
  ./sys_top "-c coreid [,coreid ...] -m module [h - Heap, s - Shared region ...]"

  Example:
  ========
     ./sys_top   <-- Shows the Entire system information
     ./sys_top -c 1 -m s <-- Shows the Shared region module information from Multi Proc core id 1

Build:
======
1. Update the below path in makefile
     CSTOOL_PATH 
     LDRMEMSEGCFG_PATH
2. execute below command
     make
3. The executable sys_top is present in the current directory


CHK_C6A8_2011_JUL_28_SLOG_UTILITY_ADDED

DEV_SLOG_04_00_00_01