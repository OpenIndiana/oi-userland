/*
 * Copyright (c) 2003, 2011, Oracle and/or its affiliates. All rights reserved.
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
 */
#ifndef STDHDR_H
#define STDHDR_H

#define LARGE_TABLE		200
#define MIB_TRUE        1
#define MIB_FALSE       2

#define entityMIB 1,3,6,1,2,1,47
#define entityMIBObjects entityMIB,1
#define entityMIBTraps entityMIB,2
#define entityMIBTrapPrefix entityMIBTraps,0
#define entityPhysical entityMIBObjects,1
#define entPhysicalTable entityPhysical,1
#define entPhysicalEntry entPhysicalTable,1
#define entPhysicalDesc entPhysicalEntry,2
/* 2^31 - 1 limit on all the indexes */
#define MAX_ENTITY_INDEX 2147483647

typedef long int_l; /* This is a workaround for ASN.c unable to handle 
                       int data type properly
                       in a 64 bit environment */


#endif /* STDHDR_H */
