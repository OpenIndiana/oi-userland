/* This program writes the SMA build version and build date to standard output.
 *
 * Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
 *
 * U.S. Government Rights - Commercial software. Government users are subject
 * to the Sun Microsystems, Inc. standard license agreement and applicable
 * provisions of the FAR and its supplements.
 *
 *
 * This distribution may include materials developed by third parties. Sun,
 * Sun Microsystems, the Sun logo and Solaris are trademarks or registered
 * trademarks of Sun Microsystems, Inc. in the U.S. and other countries.
 *
 * $Log: sma_buildrev.c,v $
 * Revision 1.49  2004/04/12 19:25:15  rr144420
 * 9999999 - Build 51
 *
 * Revision 1.48  2004/03/11 12:47:45  rr144420
 * 9999999 - Build 50
 *
 * Revision 1.47  2004/03/09 18:02:13  rr144420
 * 9999999 - Build 49
 *
 * Revision 1.46  2004/03/02 12:31:51  rr144420
 * 9999999 - Build 48
 *
 * Revision 1.45  2004/02/25 17:57:47  rr144420
 * 9999999 - Build 47
 *
 * Revision 1.44  2004/02/17 13:20:31  rr144420
 * 9999999 - Build 46
 *
 * Revision 1.43  2004/02/06 20:36:51  rr144420
 * 9999999 - Build 45
 *
 * Revision 1.42  2004/01/29 14:23:31  rr144420
 * 9999999 - Build 44
 *
 * Revision 1.41  2004/01/22 19:33:00  rr144420
 * 9999999 - Build 43
 *
 * Revision 1.40  2004/01/15 18:18:10  rr144420
 * 9999999 - Build 42
 *
 * Revision 1.39  2004/01/12 18:59:23  rr144420
 * 9999999 - Build 41
 *
 * Revision 1.38  2004/01/09 14:46:22  rr144420
 * 9999999 - Build 40
 *
 * Revision 1.37  2004/01/06 17:01:26  rr144420
 * 9999999 - Build 39
 *
 * Revision 1.36  2004/01/05 18:09:03  rr144420
 * 9999999 - Build 38
 *
 * Revision 1.35  2003/12/24 18:44:35  rr144420
 * 9999999 - Build 37
 *
 * Revision 1.34  2003/12/23 16:38:14  rr144420
 * 9999999 - Build 36
 *
 * Revision 1.33  2003/12/18 20:12:53  rr144420
 * 9999999 - Build 35
 *
 * Revision 1.32  2003/12/15 14:59:29  rr144420
 * 9999999 - Build 34
 *
 * Revision 1.31  2003/12/08 13:15:41  rr144420
 * 9999999 - Build 33
 *
 * Revision 1.30  2003/12/01 13:54:58  rr144420
 * 9999999 - Build 32
 *
 * Revision 1.29  2003/11/24 14:20:54  rr144420
 * 9999999 - Build 31
 *
 * Revision 1.28  2003/11/17 13:40:43  rr144420
 * 9999999 - Build 30
 *
 * Revision 1.27  2003/11/12 13:37:18  rr144420
 * 9999999 - Build 29
 *
 * Revision 1.26  2003/11/10 14:10:57  rr144420
 * 9999999 - Build 28
 *
 * Revision 1.25  2003/11/04 16:35:41  rr144420
 * 9999999 - Build 27
 *
 * Revision 1.24  2003/10/27 13:41:17  rr144420
 * 9999999 - Build 26
 *
 * Revision 1.23  2003/10/20 11:47:02  rr144420
 * 9999999 - Build 25
 *
 * Revision 1.22  2003/09/29 12:07:53  rr144420
 * 9999999 - Build 22
 *
 * Revision 1.21  2003/09/22 12:01:15  rr144420
 * 9999999 - Build 21
 *
 * Revision 1.20  2003/09/19 17:08:41  rr144420
 * 9999999 - Build 20
 *
 * Revision 1.19  2003/09/19 11:25:15  rr144420
 * 9999999 - Build 19
 *
 * Revision 1.18  2003/09/18 11:59:46  rr144420
 * 9999999 - Build 18
 *
 * Revision 1.17  2003/09/17 11:19:15  rr144420
 * 9999999 - Build 17
 *
 * Revision 1.16  2003/09/15 12:09:08  rr144420
 * 9999999 - Build 16
 *
 * Revision 1.15  2003/09/12 14:18:30  rr144420
 * 9999999 - Build 15
 *
 * Revision 1.14  2003/09/10 12:04:22  rr144420
 * 9999999 - Build 14
 *
 * Revision 1.13  2003/09/08 12:03:37  rr144420
 * 9999999 - Build 13
 *
 * Revision 1.12  2003/09/03 16:12:42  rr144420
 * 9999999 - Build 12
 *
 * Revision 1.11  2003/09/01 14:43:33  rr144420
 * 9999999 - Build 11
 *
 * Revision 1.10  2003/08/25 12:34:24  rr144420
 * 9999999 - Build 10
 *
 * Revision 1.9  2003/08/21 14:41:58  rr144420
 * 4908816 - further makefile changes to install into correct lib
 *
 * Revision 1.8  2003/08/18 12:36:09  rr144420
 * 9999999 - Build 09
 *
 * Revision 1.7  2003/08/11 20:06:33  rr144420
 * Build 8
 *
 * Revision 1.6  2003/08/10 21:34:59  rr144420
 * Build 7
 *
 * Revision 1.5  2003/08/06 14:46:40  rr144420
 * Corrected build 6
 *
 * Revision 1.4  2003/08/05 20:18:46  rr144420
 * Build 6
 *
 * Revision 1.3  2003/08/04 14:11:45  rr144420
 * Build 5
 *
 * Revision 1.2  2003/07/28 20:16:06  rr144420
 * Build 4
 *
 * Revision 1.1  2003/07/23 16:06:35  rr144420
 * Build 3
 *
 * Revision 1.5  2003/07/15 14:06:09  rr144420
 * Build 2
 *
 * Revision 1.4  2003/07/08 15:50:52  rr144420
 * Tuesday 7/8 build - added --with-mib-modules to autobuild as requested by Hanwu
 *
 * Revision 1.3  2003/07/07 17:47:38  rr144420
 * open source merge net-snmp_0307071133
 *
 * Revision 1.2  2003/06/24 11:24:56  rr144420
 * SMA Build 1
 *
 * Revision 1.1  2003/06/20 16:25:59  rr144420
 * initial version
 *
 */

#include <stdio.h>
#define SMA_BUILD "sma1.0_b52"
/* Build 52 */

int main () {
  char rcs_date[] = "$Date: 2004/04/19 $";
  char dummy[] = "xDate:";
  char date[] = "yyyy/mm/dd";
  sscanf(rcs_date, "%6s %10s", dummy, date);
  printf ("SMA build %s, %s\n", SMA_BUILD, date);
}
