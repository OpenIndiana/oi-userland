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
#include <signal.h>

#include <me1LoadGroup.h>

static int keep_running;

RETSIGTYPE
stop_server(int a)
{
	keep_running = 0;
}

int
main(int argc, char **argv)
{
	int agentx_subagent = 1;
	//Change to make an SNMP master agent

	/* print log errors to stderr */
		snmp_enable_stderrlog();

	/* we're an agentx subagent? */
	if (agentx_subagent) {
		/*
		 * This is an agentx client. Specify 0 for
		 * NETSNMP_DS_AGENT_ROLE if the agent is master agent.
		 * Specify 1 for NETSNMP_DS_AGENT_ROLE, if the agent is a
		 * client.
		 */
		netsnmp_ds_set_boolean(NETSNMP_DS_APPLICATION_ID,
				NETSNMP_DS_AGENT_ROLE, 1);
		DEBUGMSGTL(("demo_module_8",
				"NETSNMP_DS_APPLICATION_ID = %s:\n",
				NETSNMP_DS_APPLICATION_ID));
		DEBUGMSGTL(("demo_module_8", "NETSNMP_DS_AGENT_ROLE = %s:\n",
				NETSNMP_DS_AGENT_ROLE));
	}
	/*
	 * Initializes the embedded agent.  Call this function before the
	 * init_snmp() call. The string name specifies which .conf file to
	 * read when init_snmp() is called later.
	 */
	init_agent("demo_module_8");
	DEBUGMSGTL(("demo_module_8", "CALLING init_agent\n"));

	/* initialize mib code here */

	/* mib code: init_me1LoadGroup from me1LoadGroup.c */
	init_me1LoadGroup();

	/*
	 * Initializes the SNMP library, which causes the agent to read your
	 * application's configuration files. The agent first tries to read
	 * the configuration files named by the string passed as an argument.
	 * You might use this to configure  access  control, for example.
	 */
	init_snmp("demo_module_8");

	/*
	 * Initializes the master agent and causes it to listen for SNMP
	 * requests on its default UDP port of 161. Open the port to listen
	 * (defaults to udp: 161)
	 */
	if (!agentx_subagent)
		init_master_agent();

	/* In case we get a request to stop (kill -TERM or kill -INT) */
	keep_running = 1;
	signal(SIGTERM, stop_server);
	signal(SIGINT, stop_server);

	/*
	 * The main loop. If you use select(), see snmp_select_info() in
	 * snmp_api(3). This checks for packets arriving on the SNMP port and
	 * processes them if some are found. If block is non zero, the
	 * function call blocks until a packet arrives or an alarm must be
	 * run (see snmp_alarm(3)).
	 *
	 * The return value from this function is a positive integer if packets
	 * were processed, zero if an alarm occurre, and -1 if an error
	 * occured.
	 */

	while (keep_running) {
		/* OR */
		agent_check_and_process(1);	/* 0 == don't block */
	}
	/*
	 * Shuts down the agent, saving any needed persistent storage.
	 */
	snmp_shutdown("demo_module_8");
}
