/*
 * Wyllys Ingersoll <wyllys.ingersoll@sun.com>
 *
 * Based on work by
 *   Daniel Kouril <kouril@users.sourceforge.net>
 *   James E. Robinson, III <james@ncstate.net>
 *   Daniel Henninger <daniel@ncsu.edu>
 *   Ludek Sulak <xsulak@fi.muni.cz>
 */

/* ====================================================================
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 2000-2003 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Apache" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 * Portions of this software are based upon public domain software
 * originally written at the National Center for Supercomputing Applications,
 * University of Illinois, Urbana-Champaign.
 */

/*
 * Copyright (c) 2007, 2011, Oracle and/or its affiliates. All rights reserved.
 */


#include <sys/types.h>
#include <strings.h>

#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_log.h"
#include "http_protocol.h"
#include "http_request.h"
#include "ap_config.h"
#include "apr_base64.h"
#include "apr_lib.h"
#include "apr_time.h"
#include "apr_errno.h"
#include "apr_global_mutex.h"
#include "apr_strings.h"
#include "ap_compat.h"

#include <gssapi/gssapi.h>
#include <gssapi/gssapi_ext.h>

module auth_gss_module;

static void *gss_create_dir_config(apr_pool_t *, char *);

int gss_authenticate(request_rec *);

typedef struct {
	char *gss_service_name;
	char *keytab_file;
	int gss_debug;
} gss_auth_config;

static const char *set_service_name(cmd_parms *cmd, void *config,
	const char *name)
{
    ((gss_auth_config *) config)->gss_service_name = (char *)name;
    return NULL;
}

static const char *set_keytab_file(cmd_parms *cmd, void *config,
	const char *file)
{
	((gss_auth_config *) config)->keytab_file = (char *)file;
	return NULL;
}

static const char *set_gss_debug(cmd_parms *cmd, void *config,
	const char *debugflag)
{
	((gss_auth_config *) config)->gss_debug = atoi(debugflag);
	return NULL;
}

static const command_rec gss_auth_cmds[] = {
	AP_INIT_TAKE1("AuthGSSServiceName", set_service_name, NULL,
		OR_AUTHCFG, "Service name used for authentication."),

	AP_INIT_TAKE1("AuthGSSKeytabFile", set_keytab_file, NULL,
		OR_AUTHCFG,
		"Location of Kerberos V5 keytab file."),

	AP_INIT_TAKE1("AuthGssDebug", set_gss_debug, NULL,
		OR_AUTHCFG,
		"Enable debug logging in error_log"),
	{ NULL }
};

static void
gss_register_hooks(apr_pool_t *p)
{
	ap_hook_check_user_id(gss_authenticate,NULL,NULL,APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA auth_gss_module = {
	STANDARD20_MODULE_STUFF,
	gss_create_dir_config,	/* dir config creater */
	NULL,			/* dir merger --- default is to override */
	NULL,			/* server config */
	NULL,			/* merge server config */
	gss_auth_cmds,		/* command apr_table_t */
	gss_register_hooks		/* register hooks */
};

typedef struct {
	gss_ctx_id_t context;
	gss_cred_id_t server_creds;
} gss_connection_t;

static gss_connection_t *gss_connection = NULL;

static void *
gss_create_dir_config(apr_pool_t *p, char *d)
{
	gss_auth_config *rec =
		(gss_auth_config *) apr_pcalloc(p, sizeof(gss_auth_config));

	((gss_auth_config *)rec)->gss_service_name = "HTTP";
	((gss_auth_config *)rec)->keytab_file = "/var/apache2/http.keytab";
	((gss_auth_config *)rec)->gss_debug = 0;

	return rec;
}

#define log_rerror ap_log_rerror

/*********************************************************************
 * GSSAPI Authentication
 ********************************************************************/
static const char *
gss_error_msg(apr_pool_t *p, OM_uint32 maj, OM_uint32 min, char *prefix)
{
	OM_uint32 maj_stat, min_stat; 
	OM_uint32 msg_ctx = 0;
	gss_buffer_desc msg;

	char *err_msg = (char *)apr_pstrdup(p, prefix);

	do {
		maj_stat = gss_display_status (&min_stat,
			maj, GSS_C_GSS_CODE,
			GSS_C_NO_OID, &msg_ctx,
			&msg);
		if (GSS_ERROR(maj_stat))
			break;

		err_msg = apr_pstrcat(p, err_msg, ": ", (char*) msg.value,
			NULL);
		(void) gss_release_buffer(&min_stat, &msg);
      
		maj_stat = gss_display_status (&min_stat,
			min, GSS_C_MECH_CODE,
			GSS_C_NULL_OID, &msg_ctx,
			&msg);
		if (!GSS_ERROR(maj_stat)) {
			err_msg = apr_pstrcat(p, err_msg,
				" (", (char*) msg.value, ")", NULL);
			(void) gss_release_buffer(&min_stat, &msg);
		}
	} while (!GSS_ERROR(maj_stat) && msg_ctx != 0);

	return (err_msg);
}

static int
cleanup_gss_connection(void *data)
{
	OM_uint32 ret;
	OM_uint32 minor_status;
	gss_connection_t *gss_conn = (gss_connection_t *)data;

	if (data == NULL)
		return 0; 

	if (gss_conn->context != GSS_C_NO_CONTEXT) {
		(void) gss_delete_sec_context(&minor_status,
			&gss_conn->context,
			GSS_C_NO_BUFFER);
	}

	if (gss_conn->server_creds != GSS_C_NO_CREDENTIAL) {
		(void) gss_release_cred(&minor_status, &gss_conn->server_creds);
	}

	gss_connection = NULL;

	return 0; 
}

static int
acquire_server_creds(request_rec *r,
	gss_auth_config *conf,
	gss_OID_set mechset,
	gss_cred_id_t *server_creds)
{
	int ret = 0;
	gss_buffer_desc input_token = GSS_C_EMPTY_BUFFER;
	OM_uint32 major_status, minor_status, minor_status2;
	gss_name_t server_name = GSS_C_NO_NAME;
	char buf[1024];

	snprintf(buf, sizeof(buf), "%s@%s",
		conf->gss_service_name, r->hostname);

	if (conf->gss_debug)
   		log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
			"acquire_server_creds for %s", buf);

	input_token.value = buf;
	input_token.length = strlen(buf) + 1;

	major_status = gss_import_name(&minor_status, &input_token,
 			  GSS_C_NT_HOSTBASED_SERVICE,
			  &server_name);

	if (GSS_ERROR(major_status)) {
		log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
			"%s", gss_error_msg(r->pool, major_status, minor_status,
			"gss_import_name() failed"));
		return (HTTP_INTERNAL_SERVER_ERROR);
	}

	major_status = gss_acquire_cred(&minor_status, server_name,
		GSS_C_INDEFINITE,
		mechset, GSS_C_ACCEPT,
		server_creds, NULL, NULL);

	if (GSS_ERROR(major_status)) {
		log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
			"%s", gss_error_msg(r->pool, major_status, minor_status,
		      "gss_acquire_cred() failed"));
		ret = HTTP_INTERNAL_SERVER_ERROR;
	}
	(void) gss_release_name(&minor_status2, &server_name);

	return (ret);
}

static int
authenticate_user_gss(request_rec *r, gss_auth_config *conf,
	const char *auth_line, char **negotiate_ret_value)
{
	int ret = 0;
	OM_uint32 major_status, minor_status, minor_status2;
	gss_buffer_desc input_token = GSS_C_EMPTY_BUFFER;
	gss_buffer_desc output_token = GSS_C_EMPTY_BUFFER;
	const char *auth_param = NULL;
	gss_name_t client_name = GSS_C_NO_NAME;
	gss_cred_id_t delegated_cred = GSS_C_NO_CREDENTIAL;

	if (conf->gss_debug)
		log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
		"authenticate_user_gss called");

	*negotiate_ret_value = (char *)"";

	if (gss_connection == NULL) {
		gss_connection = apr_pcalloc(r->connection->pool, sizeof(*gss_connection));
		if (gss_connection == NULL) {
			log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
		           "apr_pcalloc() failed (not enough memory)");
			ret = HTTP_INTERNAL_SERVER_ERROR;
			goto end;
		}
		(void) memset(gss_connection, 0, sizeof(*gss_connection));
		apr_pool_cleanup_register(r->connection->pool, gss_connection,
			cleanup_gss_connection, apr_pool_cleanup_null);
	}

	if (conf->keytab_file) {
		char *ktname;
		/*
		 * We don't use the ap_* calls here, since the string 
		 * passed to putenv() will become part of the enviroment 
		 * and shouldn't be free()ed by apache.
		 */
		ktname = malloc(strlen("KRB5_KTNAME=") + strlen(conf->keytab_file) + 1);
		if (ktname == NULL) {
			log_rerror(APLOG_MARK, APLOG_ERR, 0, r, 
				"malloc() failed: not enough memory");
			ret = HTTP_INTERNAL_SERVER_ERROR;
			goto end;
		}
		/*
		 * Put the keytab name in the environment so that Kerberos
		 * knows where to look later.
		 */
		sprintf(ktname, "KRB5_KTNAME=%s", conf->keytab_file);
		putenv(ktname);
		if (conf->gss_debug)
			log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "Using keytab: %s", ktname);
	}

	/* ap_getword() shifts parameter */
	auth_param = ap_getword_white(r->pool, &auth_line);
	if (auth_param == NULL) {
		log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
			"No Authorization parameter in request from client");
		ret = HTTP_UNAUTHORIZED;
		goto end;
	}

	input_token.length = apr_base64_decode_len(auth_param) + 1;
	input_token.value = apr_pcalloc(r->connection->pool, input_token.length);

	if (input_token.value == NULL) {
		log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
	   	"apr_pcalloc() failed (not enough memory)");
		ret = HTTP_INTERNAL_SERVER_ERROR;
		goto end;
	}
	input_token.length = apr_base64_decode(input_token.value, auth_param);

	if (gss_connection->server_creds == GSS_C_NO_CREDENTIAL) {
		gss_OID_set_desc desiredMechs;
		gss_OID_desc client_mech_desc;
		gss_OID client_mechoid = &client_mech_desc;
		char *mechstr = NULL;

		if (!__gss_get_mech_type(client_mechoid, &input_token)) {
			mechstr = (char *)__gss_oid_to_mech(client_mechoid);
		}
		if (mechstr == NULL) {
			client_mechoid = GSS_C_NULL_OID;
			mechstr = "<unknown>";
		}

		if (conf->gss_debug)   
			log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
				"Client wants GSS mech: %s", mechstr);

		desiredMechs.count = 1;
		desiredMechs.elements = client_mechoid;

		/* Get creds using the mechanism that the client requested */
		ret = acquire_server_creds(r, conf, &desiredMechs,
			&gss_connection->server_creds);
		if (ret)
			goto end;
	} 
	/*
	 * Try to display the server creds information.
	 */
	if (conf->gss_debug) {
		gss_name_t sname;
		gss_buffer_desc dname;

		major_status = gss_inquire_cred(&minor_status,
			gss_connection->server_creds,
			&sname, NULL, NULL, NULL);
		if (major_status == GSS_S_COMPLETE) {
			major_status = gss_display_name(&minor_status,
				sname, &dname, NULL);
		}
		if (major_status == GSS_S_COMPLETE) {
			log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
				"got server creds for: %.*s",
				(int)dname.length,
				(char *)dname.value);
			(void) gss_release_name(&minor_status, &sname);
			(void) gss_release_buffer(&minor_status, &dname);
		}
	}

	major_status = gss_accept_sec_context(&minor_status,
			  &gss_connection->context,
			  gss_connection->server_creds,
			  &input_token,
			  GSS_C_NO_CHANNEL_BINDINGS,
			  &client_name,
			  NULL,
			  &output_token,
			  NULL,
			  NULL,
			  &delegated_cred);

	if (output_token.length) {
		char *token = NULL;
		size_t len;
		len = apr_base64_encode_len(output_token.length) + 1;
		token = apr_pcalloc(r->connection->pool, len + 1);
		if (token == NULL) {
			log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
			"apr_pcalloc() failed (not enough memory)");
			ret = HTTP_INTERNAL_SERVER_ERROR;
			gss_release_buffer(&minor_status2, &output_token);
			goto end;
		}
		apr_base64_encode(token, output_token.value, output_token.length);
		token[len] = '\0';
		*negotiate_ret_value = token;
	}

	if (GSS_ERROR(major_status)) {
		log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
			"%s", gss_error_msg(r->pool, major_status, minor_status,
			"gss_accept_sec_context() failed"));
		/* Don't offer the Negotiate method again if call to GSS layer failed */
		*negotiate_ret_value = NULL;
		ret = HTTP_UNAUTHORIZED;
		goto end;
	}

	if (major_status == GSS_S_CONTINUE_NEEDED) {
		/*
		 * Some GSSAPI mechanisms may require multiple iterations to
		 * establish authentication.  Most notably, when MUTUAL_AUTHENTICATION
		 * flag is used, multiple round trips are needed.
		 */
		ret = HTTP_UNAUTHORIZED;
		goto end;
	}

	if (client_name != GSS_C_NO_NAME) {
		gss_buffer_desc name_token = GSS_C_EMPTY_BUFFER;
		major_status = gss_display_name(&minor_status, client_name,
			&name_token, NULL);

		if (GSS_ERROR(major_status)) {
			log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
				"%s", gss_error_msg(r->pool, major_status,
				minor_status,
				"gss_export_name() failed"));
			ret = HTTP_INTERNAL_SERVER_ERROR;
			goto end;
		}
		if (name_token.length)  {
			r->user = apr_pstrdup(r->pool, name_token.value);
			gss_release_buffer(&minor_status, &name_token);
		}

		if (conf->gss_debug)
			log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
				"Authenticated user: %s",
			r->user ?  r->user : "<unknown>");
	} 
	r->ap_auth_type = "Negotiate";
	ret = OK;
end:
	if (delegated_cred)
		gss_release_cred(&minor_status, &delegated_cred);

	if (output_token.length) 
		gss_release_buffer(&minor_status, &output_token);

	if (client_name != GSS_C_NO_NAME)
		gss_release_name(&minor_status, &client_name);

	cleanup_gss_connection(gss_connection);

	return ret;
}

static int
already_succeeded(request_rec *r)
{
	if (ap_is_initial_req(r) || r->ap_auth_type == NULL)
		return 0;

	return (strcmp(r->ap_auth_type, "Negotiate") ||
		(strcmp(r->ap_auth_type, "Basic") && strchr(r->user, '@')));
}

static void
note_gss_auth_failure(request_rec *r, const gss_auth_config *conf,
	char *negotiate_ret_value)
{
	const char *auth_name = NULL;
	int set_basic = 0;
	char *negoauth_param;

	/* get the user realm specified in .htaccess */
	auth_name = ap_auth_name(r);
  
	if (conf->gss_debug)
   		log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
			"note_gss_auth_failure: auth_name = %s",
			auth_name ? auth_name : "<undefined>");

	if (negotiate_ret_value != NULL) {
		negoauth_param = (*negotiate_ret_value == '\0') ? "Negotiate" :
			apr_pstrcat(r->pool, "Negotiate ", negotiate_ret_value, NULL);
		apr_table_add(r->err_headers_out, "WWW-Authenticate", negoauth_param);
	}
}

int
gss_authenticate(request_rec *r)
{
	int ret;
	gss_auth_config *conf = 
		(gss_auth_config *) ap_get_module_config(r->per_dir_config,
			&auth_gss_module);
	const char *auth_type = NULL;
	const char *auth_line = NULL;
	const char *type = NULL;
	char *negotiate_ret_value;
	static int last_return = HTTP_UNAUTHORIZED;

	/* get the type specified in .htaccess */
	type = ap_auth_type(r);

	if (conf->gss_debug)
		log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
		"gss_authenticate: type = %s", type);

	if (type == NULL || (strcasecmp(type, "GSSAPI") != 0)) {
		return DECLINED;
	}

	/* get what the user sent us in the HTTP header */
	auth_line = apr_table_get(r->headers_in, "Authorization");

	if (!auth_line) {
		if (conf->gss_debug)
			log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
				"No authentication data found");
		note_gss_auth_failure(r, conf, "\0");
		return HTTP_UNAUTHORIZED;
	}
	auth_type = ap_getword_white(r->pool, &auth_line);

	if (already_succeeded(r))
		return last_return;

	if (strcasecmp(auth_type, "Negotiate") == 0) {
		ret = authenticate_user_gss(r, conf, auth_line, &negotiate_ret_value);
	} else {
		ret = HTTP_UNAUTHORIZED;
	}

	if (ret == HTTP_UNAUTHORIZED) {
		if (conf->gss_debug)
			log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
				"Authentication failed.");
		note_gss_auth_failure(r, conf, negotiate_ret_value);
	}

	last_return = ret;
	return ret;
}
