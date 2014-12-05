/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright (c) 2014, Oracle and/or its affiliates. All rights reserved.
 */

#include "includes.h"
#if defined(USE_SOLARIS_AUDIT)

#include "audit.h"
#include "buffer.h"
#include "key.h"
#include "hostfile.h"
#include "auth.h"
#include "log.h"
#include "packet.h"

#include <errno.h>
#include <pwd.h>
#include <string.h>

#include <bsm/adt.h>
#include <bsm/adt_event.h>

#ifdef	ADT_DEBUG
#include <bsm/audit.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <values.h>
#include <errno.h>
#include <pwd.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ucred.h>
#include <values.h>

#include <bsm/adt.h>
#include <bsm/audit.h>

#include <sys/types.h>
#include <sys/stat.h>

/* semi private adt functions to extract information */

extern void adt_get_asid(const adt_session_data_t *, au_asid_t *);
extern void adt_get_auid(const adt_session_data_t *, au_id_t *);
extern void adt_get_mask(const adt_session_data_t *, au_mask_t *);
extern void adt_get_termid(const adt_session_data_t *, au_tid_addr_t *);

extern void __auditd_debug(char *, ...);

void
__audit_pidinfo(void)
{
	adt_session_data_t *ah = NULL;
	au_id_t	auid;
	char *auid_name = "badname";
	struct passwd *pwd;
	au_asid_t asid;
	au_mask_t mask;
	char flags[512];
	au_tid_addr_t tid;
	char	pbuf[INET6_ADDRSTRLEN];
	int	af = AF_INET;
	int	remote;
	int	local;

	if (adt_start_session(&ah, NULL, ADT_USE_PROC_DATA) != 0) {
		__auditd_debug("cannot start session %s\n", strerror(errno));
		return;
	}
	if (ah == NULL) {
		__auditd_debug("ah is NULL\n");
		return;
	}
	adt_get_auid(ah, &auid);
	if ((pwd = getpwuid((uid_t)auid)) != NULL) {
		auid_name = pwd->pw_name;
	}
	__auditd_debug("audit id = %s(%d)\n", auid_name, auid);

	adt_get_mask(ah, &mask);
	if (getauditflagschar(flags, &mask, NULL) < 0) {
		(void) strlcpy(flags, "badflags", sizeof (flags));
	}
#ifdef	_LP64
	__auditd_debug("preselection mask = %s(0x%lx,0x%lx)\n", flags,
	    mask.am_success, mask.am_failure);
#else	/* _ILP32 */
	__auditd_debug("preselection mask = %s(0x%llx,0x%llx)\n", flags,
	    mask.am_success, mask.am_failure);
#endif	/* _LP64 */

	adt_get_termid(ah, &tid);
	__auditd_debug("tid type=%d, maj=%u, min=%u, addr=%x:%x:%x:%x\n",
	    tid.at_type,
	    (uint16_t)((tid.at_port) >> BITS(uint16_t)),
	    (uint16_t)(tid.at_port & UINT16_MAX),
	    tid.at_addr[0],
	    tid.at_addr[1],
	    tid.at_addr[2],
	    tid.at_addr[3]);
	if (tid.at_type == AU_IPv6) {
		af = AF_INET6;
	}
	(void) inet_ntop(af, (void *)(tid.at_addr), pbuf,
	    sizeof (pbuf));
	remote = (tid.at_port >> BITS(uint16_t));
	local = (tid.at_port & UINT16_MAX);
	__auditd_debug("tid type-%d (remote,local,host)= %u,%u,%s\n",
	    tid.at_type, remote, local, pbuf);
	adt_get_asid(ah, &asid);
	__auditd_debug("audit session id = %u\n",  asid);
	(void) adt_end_session(ah);
}
#else	/* !ADT_DEBUG */
/*ARGSUSED*/
/*PRINTFLIKE1*/
static void
__auditd_debug(char *fmt, ...)
{
}
static void
__audit_pidinfo()
{
}
#endif	/* ADT_DEBUG */

#include <security/pam_appl.h>

#include <sys/types.h>

extern Authctxt *the_authctxt;

extern const char *audit_username(void);
extern const char *audit_event_lookup(ssh_audit_event_t);

static adt_session_data_t *ah = NULL;		/* audit session handle */
static adt_termid_t	*tid = NULL;		/* peer terminal id */

static void audit_login(void);
static void audit_logout(void);
static void audit_fail(int);

/* Below is the sshd audit API Solaris adt interpretation */

/*
 * Called after a connection has been accepted but before any authentication
 * has been attempted.
 */
/* ARGSUSED */
void
audit_connection_from(const char *host, int port)
{
	int peer = packet_get_connection_in();
	adt_session_data_t	*ah;

	if (adt_load_termid(peer, &tid) != 0) {
		error("adt audit_connection_from: unable to load tid for %d:%s",
		    peer, strerror(errno));
	}
	if (adt_start_session(&ah, NULL, 0) != 0) {
		error("adt audit_connection_from: unable to start session "
		    "for %s:%d:%s", host, port, strerror(errno));
	}
	if (adt_set_user(ah, ADT_NO_AUDIT, ADT_NO_AUDIT, 0,
	    ADT_NO_AUDIT, tid, ADT_SETTID) != 0) {
		error("adt audit_connection_from: unable to set user "
		    "for %s:%d:%s", host, port, strerror(errno));
		(void) adt_end_session(ah);
		ah = NULL;
	}
	if (adt_set_proc(ah) != 0) {
		error("adt audit_connection_from: unable to set proc "
		    "for %s:%d:%s", host, port, strerror(errno));
	}
	(void) adt_end_session(ah);
	debug("adt audit_connection_from(%s, %d): peerfd=%d", host, port,
	    peer);
	__auditd_debug("%d/%d:%d-adt audit_connection_from(%s, %d)ctxt=%p: "
	    "peerfd=%d\n", getpid(), getuid(), geteuid(), host, port,
	    (void *)the_authctxt, peer);
	__audit_pidinfo();
}

/*
 * Called when various events occur (see audit.h for a list of possible
 * events and what they mean).
 *
 *	Entry	the_authcntxt
 */
void
audit_event(ssh_audit_event_t event)
{
	static boolean_t logged_in = B_FALSE;	/* if user did login */
	int fail = PAM_IGNORE;		/* default unset */
	static boolean_t did_maxtries = B_FALSE; /* if interactive and abort */

	debug("adt audit_event(%s)", audit_event_lookup(event));
	__auditd_debug("%d/%d:%d-adt audit_event(%s/%s)ctxt=%p\n",
	    getpid(), getuid(), geteuid(), audit_event_lookup(event),
	    audit_username(), (void *)the_authctxt);
	__audit_pidinfo();

	switch (event) {
	case SSH_AUTH_SUCCESS:		/* authentication success */
		logged_in = B_TRUE;
		audit_login(); 		/* ADT_ssh; */
		return;

	case SSH_CONNECTION_CLOSE:	/* connection closed, all done */
		if (logged_in) {
			audit_logout();		/* ADT_logout; */
			logged_in = B_FALSE;
		} else {
			error("adt audit_event logout without login");
		}
		return;

	/* Translate fail events to Solaris PAM errors */

	/* auth2.c: userauth_finish as audit_event(SSH_LOGIN_EXCEED_MAXTRIES) */
	/* auth1.c:do_authloop audit_event(SSH_LOGIN_EXCEED_MAXTRIES) */
	case SSH_LOGIN_EXCEED_MAXTRIES:
		fail = PAM_MAXTRIES;
		did_maxtries = B_TRUE;
		break;

	/* auth2.c: userauth_finish as audit_event(SSH_LOGIN_ROOT_DENIED) */
	/* auth1.c:do_authloop audit_event(SSH_LOGIN_ROOT_DENIED) */
	case SSH_LOGIN_ROOT_DENIED:
		fail = PAM_PERM_DENIED;
		break;

	/* auth2.c: input_userauth_request as audit_event(SSH_INVALID_USER) */
	/* auth.c: getpwnamallow as audit_event(SSH_INVALID_USER) */
	case SSH_INVALID_USER:
		fail = PAM_USER_UNKNOWN;
		break;

	/* seems unused, but translate to the Solaris PAM error */
	case SSH_NOLOGIN:
		fail = PAM_LOGINS_DISABLED;
		break;

	/*
	 * auth.c in auth_log as it's walking through methods calls
	 * audit_classify_method(method) which maps
	 *
	 * none		-> SSH_AUTH_FAIL_NONE
	 * password	-> SSH_AUTH_FAIL_PASSWD
	 *
	 * publickey	-> SSH_AUTH_FAIL_PUBKEY
	 * rsa		-> SSH_AUTH_FAIL_PUBKEY
	 *
	 * keyboard-interactive	-> SSH_AUTH_FAIL_KBDINT
	 * challenge-response	-> SSH_AUTH_FAIL_KBDINT
	 *
	 * hostbased	-> SSH_AUTH_FAIL_HOSTBASED
	 * rhosts-rsa	-> SSH_AUTH_FAIL_HOSTBASED
	 *
	 * gssapi-with-mic	-> SSH_AUTH_FAIL_GSSAPI
	 *
	 * unknown method	-> SSH_AUDIT_UNKNOWN
	 */
	/*
	 * see mon_table mon_dispatch_proto20[], mon_dispatch_postauth20[],
	 * mon_dispatch_proto15[], mon_dispatch_postauth15[]:
	 * MONITOR_REQ_AUDIT_EVENT
	 * called from monitor.c:mm_answer_audit_event()
	 * SSH_AUTH_FAIL_PUBKEY, SSH_AUTH_FAIL_HOSTBASED,
	 * SSH_AUTH_FAIL_GSSAPI, SSH_LOGIN_EXCEED_MAXTRIES,
	 * SSH_LOGIN_ROOT_DENIED, SSH_CONNECTION_CLOSE SSH_INVALID_USER
	 * monitor_wrap.c: mm_audit_event()
	 */
	case SSH_AUTH_FAIL_NONE:	/* auth type none */
	case SSH_AUTH_FAIL_PUBKEY:	/* authtype publickey */
		break;

	case SSH_AUTH_FAIL_PASSWD:	/* auth type password */
	case SSH_AUTH_FAIL_KBDINT:	/* authtype keyboard-interactive */
	case SSH_AUTH_FAIL_HOSTBASED:	/* auth type hostbased */
	case SSH_AUTH_FAIL_GSSAPI:	/* auth type gssapi-with-mic */
	case SSH_AUDIT_UNKNOWN:		/* auth type unknown */
		fail = PAM_AUTH_ERR;
		break;

	/* sshd.c: cleanup_exit: server specific fatal cleanup */
	case SSH_CONNECTION_ABANDON:	/* bailing with fatal error */
		/*
		 * This seems to occur with OpenSSH client when
		 * the user login shell exits.
		 */
		if (logged_in) {
			audit_logout();		/* ADT_logout; */
			logged_in = B_FALSE;
			return;
		} else if (!did_maxtries) {
			fail = PAM_AUTHINFO_UNAVAIL;
		} else {
			/* reset saw max tries */
			did_maxtries = FALSE;
		}
		break;

	default:
		error("adt audit_event: unknown event %d", event);
		__auditd_debug("%d/%d:%d-unknown event %d",
		    getpid(), getuid(), geteuid(), event);
		__audit_pidinfo();
		break;
	}
	audit_fail(fail);
}

/*
 * Called when a user session is started.  Argument is the tty allocated to
 * the session, or NULL if no tty was allocated.
 *
 * Note that this may be called multiple times if multiple sessions are used
 * within a single connection.
 */
/* ARGSUSED */
void
audit_session_open(struct logininfo *li)
{
	const char *t = li->line ? li->line : "(no tty)";

	debug("adt audit_session_open: user=%s:tty=%s", audit_username(),
	    t);
	__auditd_debug("%d/%d:%d-adt audit_session_open:ctxt=%p "
	    "user=%s:tty=%s\n", getpid(), getuid(), geteuid(),
	    (void *)the_authctxt, audit_username(), t);
	__audit_pidinfo();
}

/*
 * Called when a user session is closed.  Argument is the tty allocated to
 * the session, or NULL if no tty was allocated.
 *
 * Note that this may be called multiple times if multiple sessions are used
 * within a single connection.
 */
/* ARGSUSED */
void
audit_session_close(struct logininfo *li)
{
	const char *t = li->line ? li->line : "(no tty)";

	debug("adt audit_session_close: user=%s:tty=%s", audit_username(),
	    t);
	__auditd_debug("%d/%d:%d-adt audit_session_close:ctxt=%p "
	    "user=%s:tty=%s\n", getpid(), getuid(), geteuid(),
	    (void *)the_authctxt, audit_username(), t);
	__audit_pidinfo();
}

/*
 * This will be called when a user runs a non-interactive command.  Note that
 * it may be called multiple times for a single connection since SSH2 allows
 * multiple sessions within a single connection.
 */
/* ARGSUSED */
void
audit_run_command(const char *command)
{
	debug("adt audit_run_command: \"%s\"", command);
	__auditd_debug("%d/%d:%d-adt audit_run_command:ctxt=%p \"%s\"\n",
	    getpid(), getuid(), geteuid(), (void *)the_authctxt, command);
	__audit_pidinfo();
}

/*
 * audit_login - audit successful login
 *
 *	Entry	the_authctxt should be valid ;-)
 *		and pam_setcred called.
 *		adt_info &  ADT_INFO_PW_SUCCESS if successful
 *		password change.
 *
 *	Exit	ah = audit session established for audit_logout();
 */
static void
audit_login(void)
{
	adt_event_data_t *event;
	uid_t uid = ADT_NO_ATTRIB;
	gid_t gid = (gid_t)ADT_NO_ATTRIB;
	au_id_t	auid;

	if ((the_authctxt != NULL) && (the_authctxt->valid != 0)) {
		uid = the_authctxt->pw->pw_uid;
		gid = the_authctxt->pw->pw_gid;
	}

	if (adt_start_session(&ah, NULL, ADT_USE_PROC_DATA) != 0) {
		error("adt_start_session: %s", strerror(errno));
		return;
	}

	adt_get_auid(ah, &auid);

	if (adt_set_user(ah, uid, gid, uid, gid, NULL,
	    auid == AU_NOAUDITID ? ADT_NEW : ADT_USER)) {
		error("adt_set_user auid=%d, uid=%d", auid, uid);
		(void) adt_end_session(ah);
		ah = NULL;
		free(tid);
		tid = NULL;
		return;
	}
	if ((event = adt_alloc_event(ah, ADT_ssh)) == NULL) {
		error("adt_alloc_event(ADT_ssh): %s", strerror(errno));
		return;
	}
	if (adt_put_event(event, ADT_SUCCESS, ADT_SUCCESS) != 0) {
		error("adt_put_event(ADT_ssh, ADT_SUCCESS): %s",
		    strerror(errno));
	}
	/* should audit successful password change here */
	adt_free_event(event);
}

/*
 * audit_logout - audit the logout
 *
 *	Entry	ah = audit session.
 */
static void
audit_logout(void)
{
	adt_event_data_t *event;

	if ((event = adt_alloc_event(ah, ADT_logout)) == NULL) {
		error("adt_alloc_event(ADT_logout): %s", strerror(errno));
		return;
	}
	if (adt_put_event(event, ADT_SUCCESS, ADT_SUCCESS) != 0) {
		error("adt_put_event(ADT_logout, ADT_SUCCESS): %s",
		    strerror(errno));
	}
	adt_free_event(event);
	(void) adt_end_session(ah);
	ah = NULL;
	free(tid);
	tid = NULL;
}

/*
 * audit_fail - audit login failure.
 *
 *	Entry	the_authctxt assumed to have some info.
 *			user = user who asked to be authenticated.
 *		tid = connection audit TID set by audit_connect_from();
 *
 *	N.B.	pam_strerror() prototype takes a pam handle and error number.
 *		At least on Solaris, pam_strerror never uses the pam handle.
 *		Since there doesn't seem to be a pam handle available, this
 *		code just uses NULL.
 */
static void
audit_fail(int pamerr)
{
	adt_session_data_t *ah = NULL;
	adt_event_data_t *event;
	uid_t	uid = ADT_NO_ATTRIB;
	gid_t	gid = (gid_t)ADT_NO_ATTRIB;

	__auditd_debug("%d/%d:%d-audit_fail(%s) ctxt=%p\n",
	    getpid(), getuid(), geteuid(), pam_strerror(NULL, pamerr),
	    (void *)the_authctxt);
	if (the_authctxt != NULL) {
		__auditd_debug("valid=%d, user=%s, uid=%d\n",
		    the_authctxt->valid, the_authctxt->user,
		    the_authctxt->pw->pw_uid);
	} else {
		__auditd_debug("\tNo autxctxt\n");
	}
	__audit_pidinfo();
	if (pamerr == PAM_IGNORE) {
		return;
	}
	if ((the_authctxt != NULL) || (the_authctxt->valid != 0)) {
		uid = the_authctxt->pw->pw_uid;
		gid = the_authctxt->pw->pw_gid;
	} else if ((the_authctxt != NULL) || (the_authctxt->user != NULL)) {
		struct passwd *pw;

		if ((pw = getpwnam(the_authctxt->user)) != NULL) {
			uid = pw->pw_uid;
			gid = pw->pw_gid;
		}
	}
	if (adt_start_session(&ah, NULL, 0) != 0) {
		error("adt_start_session(ADT_ssh, 0, fail=%s):"
		    " %s", pam_strerror(NULL, pamerr), strerror(errno));
		__auditd_debug("%d/%d:%d-adt_start_session(ADT_ssh, "
		    "PROC_DATA, fail=%s): %s", getpid(), getuid(),
		    geteuid(), pam_strerror(NULL, pamerr),
		    strerror(errno));
		return;
	}
	__auditd_debug("%d/%d:%d-audit_fail+start_session() ah=%p\n",
	    getpid(), getuid(), geteuid(), (void *)ah);
	if (adt_set_user(ah, uid, gid, uid, gid, tid, ADT_NEW) != 0) {
		error("adt_set_user(ADT_ssh, PROC_DATA, fail=%s): %s",
		    pam_strerror(NULL, pamerr), strerror(errno));
		__auditd_debug("%d/%d:%d-adt_set_user(ADT_ssh, "
		    "PROC_DATA, fail=%s): %s", getpid(), getuid(),
		    geteuid(), pam_strerror(NULL, pamerr),
		    strerror(errno));
		goto done;
	}
	__auditd_debug("%d/%d:%d-audit_fail+set_user() ah=%p\n", getpid(),
	    getuid(), geteuid(), (void *)ah);
	if ((event = adt_alloc_event(ah, ADT_ssh)) == NULL) {
		error("adt_alloc_event(ADT_ssh, fail=%s): %s",
		    pam_strerror(NULL, pamerr), strerror(errno));
		__auditd_debug("%d/%d:%d-adt_set_user(ADT_ssh, 0, "
		    "fail=%s): %s", getpid(), getuid(), geteuid(),
		    pam_strerror(NULL, pamerr), strerror(errno));
	} else if (adt_put_event(event, ADT_FAILURE,
	    ADT_FAIL_PAM + pamerr) != 0) {
		error("adt_put_event(ADT_ssh, fail=%s): %s",
		    pam_strerror(NULL, pamerr), strerror(errno));
		__auditd_debug("%d/%d:%d-adt_put_event(ADT_ssh, fail=%s): %s",
		    getpid(), getuid(), geteuid(), pam_strerror(NULL, pamerr),
		    strerror(errno));
	}
	__auditd_debug("%d/%d:%d-audit_fail+put_event() ah=%p\n", getpid(),
	    getuid(), geteuid(), (void *)ah);
	/* should audit authentication with failed password change here. */
	adt_free_event(event);
done:
	(void) adt_end_session(ah);
}
#endif	/* USE_SOLARIS_AUDIT */
