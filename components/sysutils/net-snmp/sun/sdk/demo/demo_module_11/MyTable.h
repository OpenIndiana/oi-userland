/*
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
 */


#ifndef MYTABLE_H
#define MYTABLE_H

void FillentPhysicalEntry(entPhysicalEntry_t *phyStatic,
    char *entPhysicalDescr,
    oid *entPhysicalVendorType,
    int entPhysicalVendorTypeSize,
    int entPhysicalContainedIn,
    int entPhysicalClass,
    int entPhysicalParentRelPos,
    char *entPhysicalName,
    char *entPhysicalHardwareRev,
    char *entPhysicalFirmwareRev,
    char *entPhysicalSoftwareRev,
    char *entPhysicalSerialNum,
    char *entPhysicalMfgName,
    char *entPhysicalModelName,
    char *entPhysicalAlias,
    char *entPhysicalAssetID,
    int entPhysicalIsFRU);

void FillentLogicalEntry(entLogicalEntry_t *xLogicalStatic,
   char *entLogicalDescr,
   oid  *entLogicalType,
   int   entLogicalTypeSize,
   char *entLogicalCommunity,
   char *entLogicalTAddress,
   oid  *entLogicalTDomain,
   int   entLogicalTDomainSize,
   char *entLogicalContextEngineId,
   char *entLogicalContextName);

void printTableIndex();

#endif
