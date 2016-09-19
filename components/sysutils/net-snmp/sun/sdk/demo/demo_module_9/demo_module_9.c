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

/*  @example demo_module_9.c
 *  
 *
 * This example demonstrates how to implement objects that normally would 
 * block the agent as it waits for external events in such a way that the 
 * agent can continue responding to other requests while this implementation waits.
 *
 * This example uses the following features of SMA:
 *
 * - Use of the instance helper, which registers an exact OID such that GENEXT requests 
 *   are handled entirely by the helper.
 *
 * - Setting the delegated member of the requests structure to 1 to indicate to the
 *   agent that this request should be delayed.  The agent queues this request
 *   to be handled later and then is available to handle other requests.  The
 *   agent is not blocked by this request.
 *
 * - Registering an SNMP alarm to update the results at a later time. 
 *
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include "demo_module_9.h"

// default delay time for SNMP alarm
static u_long   delay_time = 1;

void
init_demo_module_9(void)
{
    static oid      my_delayed_oid[] =
        { 1, 3, 6, 1, 4, 1,42, 2, 2, 4, 4, 9, 1, 1, 0 };

    /*
     * Creates a registration handler, my_test, and passes
     * the pointer it returns to the netsnmp_register_instance
     * helper function. 
     */
    netsnmp_handler_registration *my_test;
    DEBUGMSGTL(("demo_module_9", "Initializing\n"));
    my_test =
        netsnmp_create_handler_registration("delayed_instance_example",
                                            delayed_instance_handler,
                                            my_delayed_oid,
                                            OID_LENGTH(my_delayed_oid),
                                            HANDLER_CAN_RWRITE);

    netsnmp_register_instance(my_test);
}

#define DELAYED_INSTANCE_SET_NAME "test_delayed"

int
delayed_instance_handler(netsnmp_mib_handler *handler,
                         netsnmp_handler_registration *reginfo,
                         netsnmp_agent_request_info *reqinfo,
                         netsnmp_request_info *requests)
{
	/*
	This handler is called to handle SNMP GET and SNMP SET
	requests for the my_delayed_oid object. If it is called to
	handle SNMP GET requests, the handler does not need to
	handle a GETNEXT if it is registered as an instance handler.
	Instance handlers only deliver one request at a time, so we
	do not need to loop over a list of requests. */

    DEBUGMSGTL(("demo_module_9", "Handler got request, mode = %d:\n",
                reqinfo->mode));

    switch (reqinfo->mode) {
        /*
         * here we merely mention that we'll answer this request
         * later.  we don't actually care about the mode type in this
         * example, but for certain cases you may, so I'll leave in the
         * otherwise useless switch and case statements 
         */

    default:
        /*
         * Mark this variable as something that cannot be handled now
	 * by setting the delegated member of the requests structure
	 * to 1. The agent queues the request to be handled at a later
	 * time and continues responding to other client requests.
         *  
         */
        requests->delegated = 1;
	DEBUGMSGTL(("demo_module_9", "Delegated is %d\n",
                requests->delegated));

        /*
         * Register an alarm to update the results at a later
         * time.  Normally, we might have to query something else
         * (like an external request sent to a different network
         * or system socket, etc), but for this example we'll do
         * something really simply and just insert an alarm for a
         * certain period of time. 
         */
        DEBUGMSGTL(("demo_module_9", "Delay is %d\n",
                delay_time));
        snmp_alarm_register(delay_time, /* seconds */
                            0,  /* dont repeat. */
                            return_delayed_response,    /* the function
                                                         * to call */
                            /*
                             * Create a "cache" of useful
                             * information that can be retrieved
                             * at a later time.  This argument is
                             * passed back to the module in the callback 
                             * function for an alarm. 
                             */
                            (void *)
                            netsnmp_create_delegated_cache(handler,
                                                           reginfo,
                                                           reqinfo,
                                                           requests,
                                                           NULL));
        break;

    }

    return SNMP_ERR_NOERROR;
}

void
return_delayed_response(unsigned int clientreg, void *clientarg)
{
    /*
     * Extract the cache from the passed argument. 
     */
    netsnmp_delegated_cache *cache = (netsnmp_delegated_cache *) clientarg;

    netsnmp_request_info *requests;
    netsnmp_agent_request_info *reqinfo;
    u_long         *delay_time_cache = NULL;

    /*
     * Make sure the cache created earlier is still
     * valid.  If not, the request timed out for some reason and we
     * do not need to keep processing things.  Should never happen, but
     * this double checks. 
     */
    cache = netsnmp_handler_check_cache(cache);

    if (!cache) {
        snmp_log(LOG_ERR, "illegal call to return delayed response\n");
        return;
    }

    /*
     * Re-establish the previous pointers,
     */
    reqinfo = cache->reqinfo;
    requests = cache->requests;

    DEBUGMSGTL(("demo_module_9",
                "continuing delayed request, mode = %d\n",
                cache->reqinfo->mode));


    /*
     * Set delegated to zero to indicate that the request is no longer
     * delegated and answer the query.
     */
    requests->delegated = 0;

    DEBUGMSGTL(("demo_module_9", "Set delegated to %d\n",
                requests->delegated));


    switch (cache->reqinfo->mode) {
        /*
         * Registering as an instance means we do not need to deal with
         * GETNEXT processing, so we do not handle it here at all.
         * 
         * However, since the instance handler already reset the mode
         * back to GETNEXT from the GET mode, we need to do the
         * same thing in both cases.
	 *
         */

    case MODE_GET:
    case MODE_GETNEXT:
        /*
         * Return the current delay time
         */
	DEBUGMSGTL(("demo_module_9", "Got to MODE_GETNEXT\n"));

        snmp_set_var_typed_value(cache->requests->requestvb,
                                 ASN_INTEGER,
                                 (u_char *) & delay_time,
                                 sizeof(delay_time));
	DEBUGMSGTL(("demo_module_9",
                "Got delay time = %d\n",
                delay_time));	
        break;

    case MODE_SET_RESERVE1:
	    DEBUGMSGTL(("demo_module_9", "Got to MODE_SET_RESERVE1\n"));

        /*
         * check type 
         */
        if (requests->requestvb->type != ASN_INTEGER) {
            /*
             * If not an integer, return SNMP error. 
             */
            netsnmp_set_request_error(reqinfo, requests,
                                      SNMP_ERR_WRONGTYPE);
            /*
             * Free cache. It is no longer needed. 
             */
            netsnmp_free_delegated_cache(cache);
            return;
        }
        break;

    case MODE_SET_RESERVE2:
	    DEBUGMSGTL(("demo_module_9", "Got to MODE_SET_RESERVE2\n"));
        /*
         * Store old value for UNDO support in the future. 
         */
        memdup((u_char **) & delay_time_cache,
               (u_char *) & delay_time, sizeof(delay_time));

        /*
         * malloc failed 
         */
        if (delay_time_cache == NULL) {
            netsnmp_set_request_error(reqinfo, requests,
                                      SNMP_ERR_RESOURCEUNAVAILABLE);
            netsnmp_free_delegated_cache(cache);
            return;
        }

        /*
         * Add our temporary information to the request itself.
         * This is then retrivable later.  The free function
         * passed auto-frees it when the request is later
         * deleted.  
         */
        netsnmp_request_add_list_data(requests,
                                      netsnmp_create_data_list
                                      (DELAYED_INSTANCE_SET_NAME,
                                       delay_time_cache, free));
        break;

    case MODE_SET_ACTION:
	    DEBUGMSGTL(("demo_module_9", "Got to MODE_SET_ACTION\n"));
        /*
         * Update current value. 
         */
        delay_time = *(requests->requestvb->val.integer);
        DEBUGMSGTL(("demo_module_9", "updated delay_time -> %d\n",
                    delay_time));
        break;

    case MODE_SET_UNDO:
	    DEBUGMSGTL(("demo_module_9", "Got to MODE_SET_UNDO\n"));
	    
        /*
         * A failure occurred. Reset to the
         * previously value by extracting the previosuly
         * stored information from the request.
         */
        delay_time =
            *((u_long *) netsnmp_request_get_list_data(requests,
                                                       DELAYED_INSTANCE_SET_NAME));
        break;

    case MODE_SET_COMMIT:
    case MODE_SET_FREE:
	    DEBUGMSGTL(("demo_module_9", "Got to MODE_SET_UNDO\n"));
        /*
         * The only thing to do here is free the old memdup'ed
         * value, but it's auto-freed by the datalist recovery, so
         * we don't have anything to actually do here 
         */
        break;
    }

    /*
     * free the information cache 
     */
    netsnmp_free_delegated_cache(cache);
}
