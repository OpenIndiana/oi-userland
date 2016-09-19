/*
 * Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include "me1LoadGroup.h"
#include <sys/loadavg.h>

char *
getLoadAvg(int timeAverage)
{
	double loadavg[3];
	char *data = malloc(30 * sizeof (char));
	int numOfSamples = getloadavg(loadavg, 3);
	sprintf(data, "%e", loadavg[timeAverage]);
	return (data);
}

/* Initializes the me1LoadGroup module */
void
init_me1LoadGroup(void)
{
	static oid me1SystemLoadAvg15min_oid[] =
		{ 1, 3, 6, 1, 4, 1, 42, 2, 2, 4, 4, 1, 1, 3, 0 };
	static oid me1SystemLoadAvg1min_oid[] =
		{1, 3, 6, 1, 4, 1, 42, 2, 2, 4, 4, 1, 1, 1, 0 };
	static oid me1SystemLoadAvg5min_oid[] =
		{1, 3, 6, 1, 4, 1, 42, 2, 2, 4, 4, 1, 1, 2, 0 };

	DEBUGMSGTL(("me1LoadGroup", "Initializing\n"));

	netsnmp_register_read_only_instance(netsnmp_create_handler_registration
					("me1SystemLoadAvg15min",
					get_me1SystemLoadAvg15min,
					me1SystemLoadAvg15min_oid,
					OID_LENGTH(me1SystemLoadAvg15min_oid),
					HANDLER_CAN_RONLY));
	netsnmp_register_read_only_instance(netsnmp_create_handler_registration
					("me1SystemLoadAvg1min",
					get_me1SystemLoadAvg1min,
					me1SystemLoadAvg1min_oid,
					OID_LENGTH(me1SystemLoadAvg1min_oid),
					HANDLER_CAN_RONLY));
	netsnmp_register_read_only_instance(netsnmp_create_handler_registration
					("me1SystemLoadAvg5min",
					get_me1SystemLoadAvg5min,
					me1SystemLoadAvg5min_oid,
					OID_LENGTH(me1SystemLoadAvg5min_oid),
					HANDLER_CAN_RONLY));
}

int
get_me1SystemLoadAvg15min(netsnmp_mib_handler * handler,
			netsnmp_handler_registration * reginfo,
			netsnmp_agent_request_info * reqinfo,
			netsnmp_request_info * requests)
{
	/*
	 * We are never called for a GETNEXT if it's registered as a
	 * "instance", as it's "magically" handled for us.
	 */

	/*
	 * a instance handler also only hands us one request at a time, so we
	 * don't need to loop over a list of requests; we'll only get one.
	 */
	char *data = getLoadAvg(LOADAVG_15MIN);
	switch (reqinfo->mode) {

	case MODE_GET:
		/*
		 * Get data from data collection routine, Hardcoded here for
		 * testing purpose
		 */
		snmp_set_var_typed_value(requests->requestvb,
			ASN_OCTET_STR, (u_char *) data, strlen(data));
		free(data);
		break;


	default:
		/* we should never get here, so this is a really bad error */
		return (SNMP_ERR_GENERR);
	}

	return (SNMP_ERR_NOERROR);
}
int
get_me1SystemLoadAvg1min(netsnmp_mib_handler * handler,
			netsnmp_handler_registration * reginfo,
			netsnmp_agent_request_info * reqinfo,
			netsnmp_request_info * requests)
{
	/*
	 * We are never called for a GETNEXT if it's registered as a
	 * "instance", as it's "magically" handled for us.
	 */

	/*
	 * a instance handler also only hands us one request at a time, so we
	 * don't need to loop over a list of requests; we'll only get one.
	 */

	char *data = getLoadAvg(LOADAVG_1MIN);
	switch (reqinfo->mode) {

	case MODE_GET:
		snmp_set_var_typed_value(requests->requestvb,
			ASN_OCTET_STR, (u_char *) data, strlen(data));
		free(data);
		break;


	default:
		/* we should never get here, so this is a really bad error */
		return (SNMP_ERR_GENERR);
	}

	return (SNMP_ERR_NOERROR);
}
int
get_me1SystemLoadAvg5min(netsnmp_mib_handler * handler,
			netsnmp_handler_registration * reginfo,
			netsnmp_agent_request_info * reqinfo,
			netsnmp_request_info * requests)
{
	/*
	 * We are never called for a GETNEXT if it's registered as a
	 * "instance", as it's "magically" handled for us.
	 */

	/*
	 * a instance handler also only hands us one request at a time, so we
	 * don't need to loop over a list of requests; we'll only get one.
	 */

	char *data = getLoadAvg(LOADAVG_5MIN);
	switch (reqinfo->mode) {
	case MODE_GET:
		snmp_set_var_typed_value(requests->requestvb,
			ASN_OCTET_STR, (u_char *) data, strlen(data));
		free(data);
		break;


	default:
		/* we should never get here, so this is a really bad error */
		return (SNMP_ERR_GENERR);
	}

	return (SNMP_ERR_NOERROR);
}
