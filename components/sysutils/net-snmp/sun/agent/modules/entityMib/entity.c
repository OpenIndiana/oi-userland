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
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include "stdhdr.h"
#include "entPhysicalTable.h"
#include "entLogicalTable.h"
#include "entLPMappingTable.h"
#include "entAliasMappingTable.h"
#include "entPhysicalContainsTable.h"
#include "entLastChangeTime.h"


void
init_entity(void) 
{
  init_entPhysicalTable();
  init_entLogicalTable();
  init_entLPMappingTable();
  init_entAliasMappingTable();
  init_entPhysicalContainsTable();
  init_entLastChangeTime();
}
