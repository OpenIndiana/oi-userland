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


#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include "stdhdr.h"
#include "entPhysicalTable.h"
#include "entLogicalTable.h"
#include "entPhysicalContainsTable.h"
#include "entAliasMappingTable.h"
#include "entLPMappingTable.h"
#include "MyTable.h"

/*
 These are global arrays that manage the physical indexes
 and logical indexes within the scope of this program.
 Similar index management scheme will be 
 developed within the program that uses the entity MIB
 skeleton. The array is statically allocated here
 for convience in the example
*/
int i=0, j=0;
int physicalIndex[25], logicalIndex[25];


/* 
This is the initialisation function for the library. 
This function is always named as init_<library name>. This function is called during
when this library gets loaded in the agent. Make sure that the libentity.so
library is already loaded before this library is loaded.

*/

void init_demo_module_11(void) {

 entPhysicalEntry_t zEntry;
 entLogicalEntry_t zLogEntry;

/*
 All these are ficitious OIDs created for this example. Do not
 rely on these OID numbers, these are used just for demonstration
 purposes
*/
 oid chassis_oid[] = {  1, 3, 6, 1, 4, 1, 42, 200, 1 };
 oid slot_oid[] = {  1, 3, 6, 1, 4, 1, 42, 201, 1 };
 oid cpu_oid1[] = {  1, 3, 6, 1, 4, 1, 42, 202, 14 };
 oid cpu_oid2[] = {  1, 3, 6, 1, 4, 1, 42, 202, 15 };
 oid cpu_oid3[] = {  1, 3, 6, 1, 4, 1, 42, 202, 25 };

 oid module_oid1[] = {  1, 3, 6, 1, 4, 1, 42, 203, 2 };
 oid module_oid2[] = {  1, 3, 6, 1, 4, 1, 42, 203, 5 };

 oid port_oid[] = {  1, 3, 6, 1, 4, 1, 42, 204, 5 };

 oid solaris_oid[] = {  1, 3, 6, 1, 4, 1, 42, 2, 1 };
 oid SunExample_oid[] = {  1, 3, 6, 1, 4, 1, 42, 1005 };

 oid ifIndex_oid1[] = { 1,3,6,1,2,1,2,2,1,1,1 };
 oid ifIndex_oid2[] = { 1,3,6,1,2,1,2,2,1,1,2 };
 oid ifIndex_oid3[] = { 1,3,6,1,2,1,2,2,1,1,3 };


/* 
   Assuming that the entity MIB skeleton is already loaded, the
   following lines adds all the Physical objects that will
   be present in the modelled system
*/

 FillentPhysicalEntry(&zEntry, "Sun Chassis Model b1000", chassis_oid, sizeof(chassis_oid),
	          0, 3, -1, "b1000", "A(1.00.02)", "", "", "C100076544",
		  "Sun Microsystems", "CHS-1000", "cl-SJ17-3-006:rack1:rtr-U3", 
		  "0007372293", MIB_TRUE);
 physicalIndex[i++] = allocPhysicalEntry(0, &zEntry);

 FillentPhysicalEntry(&zEntry, "Sun Chassis Slot Type AA", slot_oid, 
                  sizeof(slot_oid), 1, 5, 1, "S1", "B(1.00.01)", "", "", "",
		  "Sun Microsystems", "SLT-AA97", "", "", MIB_FALSE);
 physicalIndex[i++] = allocPhysicalEntry(0, &zEntry);

 FillentPhysicalEntry(&zEntry, "Sun Chassis Slot Type AA", slot_oid, 
                  sizeof(slot_oid), 1, 5, 2, "S2", "1.00.07", "", "", "",
		  "Sun Microsystems", "SLT-AA97", "", "", MIB_FALSE);
 physicalIndex[i++] = allocPhysicalEntry(0, &zEntry);

 FillentPhysicalEntry(&zEntry, "Sun Chassis Slot Type AA", slot_oid, 
                  sizeof(slot_oid), 1, 5, 3, "S3", "1.00.07", "", "", "",
		  "Sun Microsystems", "SLT-AA97", "", "", MIB_FALSE);
 physicalIndex[i++] = allocPhysicalEntry(0, &zEntry);

 FillentPhysicalEntry(&zEntry, "Sun CPU-100", cpu_oid1, 
                  sizeof(cpu_oid1), 2, 9, 1, "M1", "1.00.07", "1.5.1", "A(1.1)",
		  "C100087363", "Sun Microsystems", "R10-FE00", 
		  "rtr-U3:m1:SJ17-3-eng", "0007372562", MIB_TRUE);
 physicalIndex[i++] = allocPhysicalEntry(0, &zEntry);


 FillentPhysicalEntry(&zEntry, "Sun Ultrasparc-III 400MHz", module_oid1, 
                  sizeof(module_oid1), 5, 1, 1, "P1", "G(1.02)", "", "1.1", "", 
		  "Sun Microsystems", "SFE-400M", "", "", MIB_FALSE);
 physicalIndex[i++] = allocPhysicalEntry(0, &zEntry);

 FillentPhysicalEntry(&zEntry, "Sun Ultrasparc-III 400MHz", module_oid1, 
                  sizeof(module_oid1), 5, 1, 2, "P2", "G(1.02)", "", "1.1", "", 
		  "Sun Microsystems", "SFE-400M", "", "", MIB_FALSE);
 physicalIndex[i++] = allocPhysicalEntry(0, &zEntry);

 FillentPhysicalEntry(&zEntry, "Sun CPU-200", cpu_oid2, 
                  sizeof(cpu_oid2), 3, 9, 1, "M2", "2.01.00", "3.0.7", "A(1.2)", 
		  "C100098732", "Sun Microsystems", "R10-FE0C", 
		  "rtr-U3:m2:SJ17-2-eng", "0007373982", MIB_TRUE);
 physicalIndex[i++] = allocPhysicalEntry(0, &zEntry);

 FillentPhysicalEntry(&zEntry, "Sun Ultrasparc-III 400MHz", module_oid2, 
                  sizeof(module_oid2), 8, 1, 1, "P3", "CC(1.07)", "2.0.34", "1.1", "", 
		  "Sun Microsystems", "SFE-400M", "", "", MIB_FALSE);
 physicalIndex[i++] = allocPhysicalEntry(0, &zEntry);

 FillentPhysicalEntry(&zEntry, "Sun Ultrasparc-III 400MHz", module_oid1, 
                  sizeof(module_oid1), 8, 1, 2, "P4", "G(1.04)", "", "1.3", "", 
		  "Sun Microsystems", "SFE-400M", "", "", MIB_FALSE);
 physicalIndex[i++] = allocPhysicalEntry(0, &zEntry);

 FillentPhysicalEntry(&zEntry, "Sun port-200", cpu_oid3, 
                  sizeof(cpu_oid3), 4, 9, 1, "M2", "2.01.00", "3.0.7", "A(1.2)", 
		  "C100098732", "Sun Microsystems", "R11-C100", 
		  "rtr-U3:m2:SJ17-2-eng", "0007373982", MIB_TRUE);
 physicalIndex[i++] = allocPhysicalEntry(0, &zEntry);


 FillentPhysicalEntry(&zEntry, "Sun Ethernet-100 Port", port_oid, 
                  sizeof(port_oid), 11, 10, 1, "P3", "CC(1.07)", "2.0.34", "1.1", 
		  "", "Sun Microsystems", "SFE-P100", "", "", MIB_FALSE);
 physicalIndex[i++] = allocPhysicalEntry(0, &zEntry);

 FillentPhysicalEntry(&zEntry, "Sun Ethernet-100 Port", port_oid, 
                  sizeof(port_oid), 11, 10, 2, "Ethernet B", "G(1.04)", "", "1.3", 
		  "", "Sun Microsystems", "SFE-P100", "", "", MIB_FALSE);
 physicalIndex[i++] = allocPhysicalEntry(0, &zEntry);

 FillentPhysicalEntry(&zEntry, "Sun Ethernet-100 Port", port_oid, 
                  sizeof(port_oid), 11, 10, 3, "Ethernet B", "G(1.04)", "", "1.3", 
		  "", "Sun Microsystems", "SFE-P100", "", "", MIB_FALSE);
 physicalIndex[i++] = allocPhysicalEntry(0, &zEntry);

/*
   The following lines adds all the logical instances that will
   be present in the modelled system. Here first parameter to
   allocLogicalEntry is ignored for now, it may be used in the 
   future to request a particular index in the table
*/

 FillentLogicalEntry(&zLogEntry, "Domain A", solaris_oid, 
                          sizeof(solaris_oid), "public-dom1", "124.125.126.127:161",
                          SunExample_oid, sizeof(SunExample_oid), "", "");
 logicalIndex[j++] = allocLogicalEntry(0, &zLogEntry);

 FillentLogicalEntry(&zLogEntry, "Domain B", solaris_oid, 
                          sizeof(solaris_oid), "public-dom2", "124.125.126.128:161",
                          SunExample_oid, sizeof(SunExample_oid), "", "");
 logicalIndex[j++] = allocLogicalEntry(0, &zLogEntry);

 FillentLogicalEntry(&zLogEntry, "Sun Firewall v2.1.1", solaris_oid, 
                          sizeof(solaris_oid), "public-firewall1", "124.125.126.129:161",
                          SunExample_oid, sizeof(SunExample_oid), "", "");
 logicalIndex[j++] = allocLogicalEntry(0, &zLogEntry);

 FillentLogicalEntry(&zLogEntry, "Sun Firewall v2.1.1", solaris_oid, 
                          sizeof(solaris_oid), "public-firewall2", "124.125.126.130:161",
                          SunExample_oid, sizeof(SunExample_oid), "", "");
 logicalIndex[j++] = allocLogicalEntry(0, &zLogEntry);


/*

 Now we add all the relationships into the entity MIB. The
 physical and logical indexes must be present to create
 any relationships, and so the relationship table is 
 filled after the physical and logical tables are 
 populated

*/

 if (addLPMappingTableEntry(1, 5))
	snmp_log(LOG_ERR, "LPMappingTable Addition failed");

 if (addLPMappingTableEntry(1, 12))
	snmp_log(LOG_ERR, "LPMappingTable Addition failed");

 if (addLPMappingTableEntry(2, 8))
	snmp_log(LOG_ERR, "LPMappingTable Addition failed");

 if (addLPMappingTableEntry(2, 13))
	snmp_log(LOG_ERR, "LPMappingTable Addition failed");

 if (addLPMappingTableEntry(2, 14))
	snmp_log(LOG_ERR, "LPMappingTable Addition failed");

 if (addLPMappingTableEntry(3, 6))
	snmp_log(LOG_ERR, "LPMappingTable Addition failed");

 if (addLPMappingTableEntry(3, 12))
	snmp_log(LOG_ERR, "LPMappingTable Addition failed");

 if (addLPMappingTableEntry(4, 9))
	snmp_log(LOG_ERR, "LPMappingTable Addition failed");

 if (addLPMappingTableEntry(4, 13))
	snmp_log(LOG_ERR, "LPMappingTable Addition failed");

 if (addLPMappingTableEntry(4, 14))
	snmp_log(LOG_ERR, "LPMappingTable Addition failed");

/*

 Any error in addition to the relationship table will
 be logged in the agent's log file

*/

 if (addAliasMappingTableEntry(12, 0, ifIndex_oid1, sizeof(ifIndex_oid1)))
	snmp_log(LOG_ERR, "AliasMappingTable Addition failed");

 if (addAliasMappingTableEntry(13, 0, ifIndex_oid2, sizeof(ifIndex_oid2)))
	snmp_log(LOG_ERR, "AliasMappingTable Addition failed");

 if (addAliasMappingTableEntry(14, 0, ifIndex_oid3, sizeof(ifIndex_oid3)))
	snmp_log(LOG_ERR, "AliasMappingTable Addition failed");

/*
 The physical child table must not contains any recursive relationships
 Care must be taken to avoid them. The entity MIB infrastructure should
 be able to check this in the future
*/

 if (addPhysicalContainsTableEntry(1, 2))
	snmp_log(LOG_ERR, "PhysicalChild Table Addition failed");
 if (addPhysicalContainsTableEntry(1, 3))
	snmp_log(LOG_ERR, "PhysicalChild Table Addition failed");
 if (addPhysicalContainsTableEntry(1, 4))
	snmp_log(LOG_ERR, "PhysicalChild Table Addition failed");
 if (addPhysicalContainsTableEntry(2, 5))
	snmp_log(LOG_ERR, "PhysicalChild Table Addition failed");
 if (addPhysicalContainsTableEntry(3, 8))
	snmp_log(LOG_ERR, "PhysicalChild Table Addition failed");
 if (addPhysicalContainsTableEntry(4, 11))
	snmp_log(LOG_ERR, "PhysicalChild Table Addition failed");
 if (addPhysicalContainsTableEntry(4, 6))
	snmp_log(LOG_ERR, "PhysicalChild Table Addition failed");
 if (addPhysicalContainsTableEntry(4, 7))
	snmp_log(LOG_ERR, "PhysicalChild Table Addition failed");
 if (addPhysicalContainsTableEntry(8, 9))
	snmp_log(LOG_ERR, "PhysicalChild Table Addition failed");
 if (addPhysicalContainsTableEntry(8, 10))
	snmp_log(LOG_ERR, "PhysicalChild Table Addition failed");
 if (addPhysicalContainsTableEntry(11, 12))
	snmp_log(LOG_ERR, "PhysicalChild Table Addition failed");
 if (addPhysicalContainsTableEntry(11, 13))
	snmp_log(LOG_ERR, "PhysicalChild Table Addition failed");
 if (addPhysicalContainsTableEntry(11, 14))
	snmp_log(LOG_ERR, "PhysicalChild Table Addition failed");

/*
 printTableIndex();
*/


}


/*
 This function is just a conveience function to add many physical table
 entries
*/

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
    int entPhysicalIsFRU)
{
    phyStatic->entPhysicalDescr = entPhysicalDescr;
    phyStatic->entPhysicalVendorType = entPhysicalVendorType;
    phyStatic->entPhysicalVendorTypeSize = entPhysicalVendorTypeSize;
    phyStatic->entPhysicalContainedIn = entPhysicalContainedIn;
    phyStatic->entPhysicalClass = entPhysicalClass;
    phyStatic->entPhysicalParentRelPos = entPhysicalParentRelPos;
    phyStatic->entPhysicalName = entPhysicalName;
    phyStatic->entPhysicalHardwareRev = entPhysicalHardwareRev;
    phyStatic->entPhysicalFirmwareRev = entPhysicalFirmwareRev;
    phyStatic->entPhysicalSoftwareRev = entPhysicalSoftwareRev;
    phyStatic->entPhysicalSerialNum = entPhysicalSerialNum;
    phyStatic->entPhysicalMfgName = entPhysicalMfgName;
    phyStatic->entPhysicalModelName = entPhysicalModelName;
    phyStatic->entPhysicalAlias = entPhysicalAlias;
    phyStatic->entPhysicalAssetID = entPhysicalAssetID;
    phyStatic->entPhysicalIsFRU = entPhysicalIsFRU;
}

/*
 This function is just a convenience function to add many logical table
 entries
*/

void FillentLogicalEntry(entLogicalEntry_t *xLogicalStatic,
   char *entLogicalDescr,
   oid  *entLogicalType,
   int   entLogicalTypeSize,
   char *entLogicalCommunity,
   char *entLogicalTAddress,
   oid  *entLogicalTDomain,
   int   entLogicalTDomainSize,
   char *entLogicalContextEngineId,
   char *entLogicalContextName)
{
    xLogicalStatic->entLogicalDescr = entLogicalDescr;
    xLogicalStatic->entLogicalType = entLogicalType;
    xLogicalStatic->entLogicalTypeSize = entLogicalTypeSize;
    xLogicalStatic->entLogicalCommunity = entLogicalCommunity;
    xLogicalStatic->entLogicalTAddress = entLogicalTAddress;
    xLogicalStatic->entLogicalTDomain = entLogicalTDomain;
    xLogicalStatic->entLogicalTDomainSize = entLogicalTDomainSize;
    xLogicalStatic->entLogicalContextEngineId = entLogicalContextEngineId;
    xLogicalStatic->entLogicalContextName = entLogicalContextName;
}


void printTableIndex()
{
 int k=0, m=0;
 printf("\n The physical indexes allocated are, \n");
 for (k=0; k<i; k++)
    printf("%d,", physicalIndex[k]);

 printf("\n The logical indexes allocated are, \n");
 for (m=0; m<j; m++)
    printf("%d,", logicalIndex[m]);
 printf("\n");
}
