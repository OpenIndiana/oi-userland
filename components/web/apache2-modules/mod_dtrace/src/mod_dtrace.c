/* 
* License:
* Copyright 2004 The Apache Software Foundation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* Module Name: mod_dtrace
*
* Purpose: Apache implements a set of hooks and filters to allow 
*          modules to view and modify requests sent to the server.
*          This module takes advantage of this architecture to 
*          implement several DTrace hooks.
*
* Notes: To get the most use out of the mod_dtrace Apache module, it will
*        be useful to familiarize yourself with the Apache request_rec,
*        server_rec and conn_rec structures. These can be viewed on the
*        docx website:
*
*        http://docx.webperf.org/httpd_8h-source.html
*
*        A basic overview of each structure is included below:
*
*           request_rec : Contains all of the attributes (URI, filename, 
*                         method, bytes_sent) needed to describe an
*                         HTTP request
*
*           conn_rec    : Stores the connection attributes including
*                         IP addresses and ports
*
*           server_rec  : Stores information to describe each virtual server
*
* Last Modified: 02-08-2007
*
* Author: Matty < matty91 at gmail dot com >
*
* Version: 0.3a
*
* Release history:
*
*    0.3a: Fixed bug due to NULL values -- Sebastien Bouchex Bellomie
*
*    0.2a: Initial release
*
* Build instructions are available at the following site:
*    http://prefetch.net/projects/apache_modtrace/build.txt
*
*/

#include "ap_config.h"
#include "httpd.h"
#include "http_config.h"
#include "http_connection.h"
#include "http_protocol.h"
#include "http_request.h"
#include <sys/sdt.h>

module AP_MODULE_DECLARE_DATA dtrace_module;

/* 
*   Probe Function Purpoose:
*   This probe will fire each time a request is send to the server. 
*
*   arg0 -> address of the request_rec structure 
*/
int apache_receive_request(request_rec *r)
{
    DTRACE_PROBE1(apache, 
                  receive__request, 
                  r);
   
    return DECLINED;
}

/* 
*   This probe will fire each time the web server invokes the logging handlers.
*   Since the request_rec, server_rec and conn_rec should be completely filled
*   in when this probe fires -- this will be a useful probe.
*   
*   arg0 -> The address of the request_rec structure
*/
int apache_log_request(request_rec *r)
{
    /* apr_table_get will return the value of User-Agent or NULL */
    const char *userAgent = NULL;
    if (r->headers_in != NULL)
    {
        userAgent = apr_table_get(r->headers_in, "User-Agent");
    }

    /* apr_table_get will return the value of Location or NULL */
    const char *redirectLocation = NULL;
    if (r->headers_out) {
        redirectLocation = apr_table_get(r->headers_out, "Location");
    }

    DTRACE_PROBE3(apache,
                  log__request,
                  r,
                  userAgent,
                  redirectLocation);

    return DECLINED;
}

/* 
*  This probe will fire each time an httpd child process is created 
*/
void apache_create_child(apr_pool_t *p, server_rec *s)
{
    DTRACE_PROBE(apache,
                 create__child);
}

/* 
*   This probe will fire each time a new TCP connection is created 
*
*   arg0 -> Client's IP address 
*/
int apache_accept_connection(conn_rec *c, void *csd)
{
    DTRACE_PROBE1(apache,
                  accept__connection,
                  c);

    return DECLINED;
}

/*
*   This probe will fire when the authentication stage is encountered
*
*   arg0 -> The address of the request_rec structure
*
*/
int apache_check_user(request_rec *r)
{
    DTRACE_PROBE1(apache,
                  check__user__credentials,
                  r);

    return DECLINED;
}

/*
*   This probe will fire when the access checking stage is encountered
*
*   arg0 -> The address of the request_rec structure
*
*/
int apache_check_access(request_rec *r)
{
    DTRACE_PROBE1(apache,
                  check__access,
                  r);

    return DECLINED;
}

/*
*   This probe will fire when the authorization checking stage is encountered
*
*   arg0 -> The address of the request_rec structure
*
*/
int apache_check_authorization(request_rec *r)
{
    DTRACE_PROBE1(apache,
                  check__authorization,
                  r);

    return DECLINED;
}

/*
*    Define the hooks and the functions registered to those hooks
*/
void dtrace_register_hooks(apr_pool_t *p)
{
    ap_hook_post_read_request(apache_receive_request,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_child_init(apache_create_child,NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_pre_connection(apache_accept_connection,NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_check_user_id(apache_check_user,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_access_checker(apache_check_access,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_auth_checker(apache_check_authorization,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_log_transaction(apache_log_request,NULL,NULL,APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA dtrace_module =
{
    STANDARD20_MODULE_STUFF,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    dtrace_register_hooks
};


