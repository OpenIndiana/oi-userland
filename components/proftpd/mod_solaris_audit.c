/*
 * ProFTPD - FTP server daemon
 * Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307, USA.
 *
 * As a special exemption, copyright holders give permission to link
 * this program with OpenSSL, and distribute the resulting executable,
 * without including the source code for OpenSSL in the source distribution.
 *
 */

#include "conf.h"
#include <bsm/adt.h>
#include <bsm/adt_event.h>
#include <security/pam_appl.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <ucred.h>

#ifndef ADT_ftpd
#define ADT_ftpd	152
#endif

#ifndef ADT_ftpd_logout
#define ADT_ftpd_logout	153
#endif

module solaris_audit_module;

static adt_session_data_t *asession = NULL;

static int auth_retval = PAM_AUTH_ERR;

static void audit_autherr_ev(const void *event_data, void *user_data) {

  switch (*(int *)event_data) {
  case PR_AUTH_NOPWD:
    auth_retval = PAM_USER_UNKNOWN;
    break;
  case PR_AUTH_AGEPWD:
    auth_retval = PAM_CRED_EXPIRED;
    break;
  case PR_AUTH_DISABLEDPWD:
    auth_retval = PAM_ACCT_EXPIRED;
    break;
  case PR_AUTH_CRED_INSUFF:
    auth_retval = PAM_CRED_INSUFFICIENT;
    break;
  case PR_AUTH_CRED_UNAVAIL:
    auth_retval = PAM_CRED_UNAVAIL;
    break;
  case PR_AUTH_CRED_ERR:
    auth_retval = PAM_CRED_ERR;
    break;
  case PR_AUTH_UNAVAIL:
    auth_retval = PAM_AUTHINFO_UNAVAIL;
    break;
  case PR_AUTH_MAXTRIES:
    auth_retval = PAM_MAXTRIES;
    break;
  case PR_AUTH_INIT_FAIL:
    auth_retval = PAM_SESSION_ERR;
    break;
  case PR_AUTH_NEWTOK:
    auth_retval = PAM_NEW_AUTHTOK_REQD;
    break;
  case PR_AUTH_OPEN_ERR:
    auth_retval = PAM_OPEN_ERR;
    break;
  case PR_AUTH_SYMBOL_ERR:
    auth_retval = PAM_SYMBOL_ERR;
    break;
  case PR_AUTH_SERVICE_ERR:
    auth_retval = PAM_SERVICE_ERR;
    break;
  case PR_AUTH_SYSTEM_ERR:
    auth_retval = PAM_SYSTEM_ERR;
    break;
  case PR_AUTH_BUF_ERR:
    auth_retval = PAM_BUF_ERR;
    break;
  case PR_AUTH_CONV_ERR:
    auth_retval = PAM_CONV_ERR;
    break;
  case PR_AUTH_PERM_DENIED:
    auth_retval = PAM_PERM_DENIED;
    break;
  default: /* PR_AUTH_BADPWD */
    auth_retval = PAM_AUTH_ERR;
    break;
  }

}

static void audit_failure(pool *p, char *authuser) {
  adt_event_data_t *event = NULL;
  const char *how;
  int saved_errno = 0;
  struct passwd pwd;
  struct passwd *result = NULL;
  char *pwdbuf = NULL;
  size_t pwdbuf_len;
  long pwdbuf_len_max;
  uid_t uid = ADT_NO_ATTRIB;
  gid_t gid = ADT_NO_ATTRIB;

  if ((pwdbuf_len_max = sysconf(_SC_GETPW_R_SIZE_MAX)) == -1) {
    saved_errno = errno;
    how = "couldn't determine maximum size of password buffer";
    goto fail;
  }

  pwdbuf_len = (size_t)pwdbuf_len_max;
  pwdbuf = pcalloc(p, pwdbuf_len);

  if (adt_start_session(&asession, NULL, ADT_USE_PROC_DATA) != 0) {
    saved_errno = errno;
    how = "couldn't start adt session";
    goto fail;
  }

  if ((authuser != NULL) && (authuser[0] != NULL) &&
    (getpwnam_r(authuser, &pwd, pwdbuf, pwdbuf_len, &result) == 0) &&
    (result != NULL)) {
    uid = pwd.pw_uid;
    gid = pwd.pw_gid;
  } 

  if (adt_set_user(asession, uid, gid, uid, gid, NULL, ADT_NEW) != 0) {
    saved_errno = errno;
    how = "couldn't set adt user";
    goto fail;
  }

  if ((event = adt_alloc_event(asession, ADT_ftpd)) == NULL) {
    saved_errno = errno;
    how = "couldn't allocate adt event";
    goto fail;
  }

  if (adt_put_event(event, ADT_FAILURE, ADT_FAIL_PAM + auth_retval) != 0) {
    saved_errno = errno;
    how = "couldn't put adt event";
    goto fail;
  }

  adt_free_event(event);
  (void) adt_end_session(asession);
  asession = NULL;
  return;

fail:
  pr_log_pri(PR_LOG_ERR, "Auditing of login failed: %s (%s)", how,
    strerror(saved_errno));

  adt_free_event(event);
  (void) adt_end_session(asession);
  asession = NULL;
}

static void audit_success(void) {
  adt_event_data_t *event = NULL;
  const char *how;
  int saved_errno = 0;

  if (adt_start_session(&asession, NULL, ADT_USE_PROC_DATA) != 0) {
    saved_errno = errno;
    how = "couldn't start adt session";
    goto fail;
  }

  if ((event = adt_alloc_event(asession, ADT_ftpd)) == NULL) {
    saved_errno = errno;
    how = "couldn't allocate adt event";
    goto fail;
  }

  if (adt_put_event(event, ADT_SUCCESS, ADT_SUCCESS) != 0) {
    saved_errno = errno;
    how = "couldn't put adt event";
    goto fail;
  }

  adt_free_event(event);

  /* Don't end adt session - leave for when logging out. */
  return;

fail:
  pr_log_pri(PR_LOG_ERR, "Auditing of login failed: %s (%s)", how,
    strerror(saved_errno));

  adt_free_event(event);

  /* Don't end adt session - leave for when logging out. */

}

static void audit_logout(void) {
  adt_event_data_t *event = NULL;
  const char *how;
  int saved_errno = 0;

  /* If audit session was not created during login then leave */
  if (asession == NULL)
    return;

  if ((event = adt_alloc_event(asession, ADT_ftpd_logout)) == NULL) {
    saved_errno = errno;
    how = "couldn't allocate adt event";
    goto fail;
  }

  if (adt_put_event(event, ADT_SUCCESS, ADT_SUCCESS) != 0) {
    saved_errno = errno;
    how = "couldn't put adt event";
    goto fail;
  }

  adt_free_event(event);
  (void) adt_end_session(asession);
  asession = NULL;
  return;

fail:
  pr_log_pri(PR_LOG_ERR, "Auditing of logout failed: %s (%s)", how,
    strerror(saved_errno));

  adt_free_event(event);
  (void) adt_end_session(asession);
  asession = NULL;
}

/* Logout */
static void audit_exit_ev(const void *event_data, void *user_data) {
  audit_logout();
}

/* Login passed */
MODRET solaris_audit_post_pass(cmd_rec *cmd) {

  audit_success();

  /* Set handler for logout/timeout */
  pr_event_register(&solaris_audit_module, "core.exit", audit_exit_ev, NULL);

  return PR_DECLINED(cmd);
}

/* Login failed */
MODRET solaris_audit_post_fail(cmd_rec *cmd) {
  char *login_user;

  login_user = pr_table_get(session.notes, "mod_auth.orig-user", NULL);

  audit_failure(cmd->tmp_pool, login_user);
  return PR_DECLINED(cmd);
}

static int audit_sess_init(void) {
  adt_session_data_t *aht;
  adt_termid_t *termid;
  priv_set_t *privset;
  int rval = -1;					

  /* add privs for audit init */
  if ((privset = priv_allocset()) == NULL) {
    pr_log_pri(PR_LOG_ERR, "Auditing privilege initialization failed");
    return rval;
  }

  (void) getppriv(PRIV_INHERITABLE, privset);
  priv_addset(privset, PRIV_PROC_AUDIT);
  (void) setppriv(PRIV_SET, PRIV_INHERITABLE, privset);

  (void) getppriv(PRIV_EFFECTIVE, privset);
  priv_addset(privset, PRIV_SYS_AUDIT);
  (void) setppriv(PRIV_SET, PRIV_EFFECTIVE, privset);

  /* basic terminal id setup */
  if (adt_start_session(&aht, NULL, 0) != 0) {
    pr_log_pri(PR_LOG_ERR, "pam adt_start_session: %s", strerror(errno));
    goto out;
  }
  if (adt_load_termid(session.c->rfd, &termid) != 0) {
    pr_log_pri(PR_LOG_ERR, "adt_load_termid: %s", strerror(errno));
    (void) adt_end_session(aht);
    goto out;
  }

  if (adt_set_user(aht, ADT_NO_AUDIT, ADT_NO_AUDIT, 0, ADT_NO_AUDIT, termid,
    ADT_SETTID) != 0) {
    pr_log_pri(PR_LOG_ERR, "adt_set_user: %", strerror(errno));
    free(termid);
    (void) adt_end_session(aht);
    goto out;
  }
  free(termid);
  if (adt_set_proc(aht) != 0) {
    pr_log_pri(PR_LOG_ERR, "adt_set_proc: %", strerror(errno));
    (void) adt_end_session(aht);
    goto out;
  }
  (void) adt_end_session(aht);

  /* Set handler for authentication error */
  pr_event_register(&solaris_audit_module, "mod_auth.authentication-code",
    audit_autherr_ev, NULL);

  rval = 0;

out:

  /* remove unneeded privileges */
  priv_delset(privset, PRIV_SYS_AUDIT);
  (void) setppriv(PRIV_SET, PRIV_EFFECTIVE, privset);
  (void) setpflags(PRIV_AWARE_RESET, 1);
  priv_freeset(privset);

  return rval;
}

#define EVENT_KEY       "event"

/* Helper functions and global variables
 * for the file transfer command handlers.
 * {
 */

static char src_realpath[PATH_MAX];
static char dst_realpath[PATH_MAX];


/*
 * If an error occurs in any of the file transfer handlers,
 * and the handler wants to return PR_ERROR(cmd), then it is necessary
 * to send some FTP error message to user. This is in order to prevent
 * a hang-up of the user's ftp client.
 *
 * This function sends the 451 error message to the user.
 * It is only called in the "pre-" handlers. When a "pre-" handler
 * returns PR_ERROR(cmd), then the corresponding "post_err-"
 * handler is also called. Therefore it can happen that an error condition
 * (such as no memory) can be logged (with the pr_log_pri() routine) twice.
 * Once in the "pre-" handler, and once in the "post_err-" handler.
 */
static void error_451(void)
{
  pr_response_add_err(R_451,
    "Requested action aborted: local error in processing.\n");
}

/*
 * Allocate resources to process a command outcome.
 *
 * All file transfer command handlers need to allocate adt_event_data_t
 * structure and also make a copy of the command argument.
 * This function does both. If it can't, it logs an error and returns NULL.
 * On success, it returns the pointer (event) to the allocated adt_event_data_t
 * structure.
 *
 * If arg2 is not NULL, it makes a copy of the first (and only) command
 * argument (using the memory pool "pool" from "cmd") and stores it to *arg2.
 * There must be always exactly one command argument, otherwise it is an error.
 *
 * On success, the pointer to the created event structure is stored
 * into cmd under "notes" variable, so that it is accessible
 * by the subsequent corresponding "post-" or "post_err-" command handler.
 */
adt_event_data_t* __solaris_audit_pre_arg2(
    cmd_rec *cmd, const char* description, int event_type, char **arg2) {

  adt_event_data_t *event = NULL;
  const char *how = "";
  char *tmp = NULL;

  /* The ftp server code will save errno into this variable
   * in case an error happens, and there is a valid errno for it.
   */
  cmd->error_code = ADT_FAILURE;

  if (cmd->arg == NULL) {
    pr_log_pri(PR_LOG_ERR, "Auditing of %s failed: %s",
      description, "bad argument");
    goto err;
  }

  if (arg2 != NULL) {
    *arg2 = NULL;

    if ((tmp = pstrdup(cmd->pool, cmd->arg)) == NULL) {
      how = "no memory";
      pr_log_pri(PR_LOG_ERR, "Auditing of %s(%s) failed: %s",
        description, cmd->arg, how);
      goto err;
    }
    *arg2 = tmp;
  }

  if (cmd->notes == NULL) {
    pr_log_pri(PR_LOG_ERR, "Auditing of %s(%s) failed: %s",
      description, cmd->arg, "API error, notes is NULL");
    goto err;
  }

  if ((event = adt_alloc_event(asession, event_type)) == NULL) {
    how = "couldn't allocate adt event";
    pr_log_pri(PR_LOG_ERR, "Auditing of %s(%s) failed: %s(%s)",
      description, cmd->arg, how, strerror(errno));
    goto err;
  }

  if (pr_table_add(cmd->notes, EVENT_KEY, event, sizeof(*event)) == -1) {
    how = "pr_table_add() failed";
    pr_log_pri(PR_LOG_ERR, "Auditing of %s(%s) failed: %s",
      description, cmd->arg, how);
    adt_free_event(event);
    goto err;
  }
  
  return event;

err:
  return NULL;
}

/*
 * This function implements logic that is common to most "post-"
 * and "post_err-" file transfer command handlers.
 *
 * It retrieves the pointer (event) to the adt_event_data_t structure
 * from "cmd->notes" and logs it. This structure has been created by the
 * __solaris_audit_pre_arg2() function.
 * 
 * Some audit event structures contain an optional *_stat member.
 * If "fill_attr" is not NULL, it is called to fill in this member,
 * before the audit event is logged.
 *
 * This function always returns PR_DECLINED, even if it failed
 * to log the audit event. The reason is that it is called in the
 * "post-" file transfer command handlers, which means that the command
 * has been already successfully executed by the ftp server.
 */
MODRET __solaris_audit_post(cmd_rec *cmd,
  const char* description, int exit_status, int __unused,
  const char* (*fill_event)(cmd_rec *cmd, adt_event_data_t *event))
{
  adt_event_data_t *event = NULL;
  const char* how = "";
  const char* msg = NULL;
  size_t size = 0;
  int exit_error = cmd->error_code;

  event = (adt_event_data_t*)pr_table_remove(cmd->notes, EVENT_KEY, &size);
  if (event == NULL) {
    how = "event is NULL";
    pr_log_pri(PR_LOG_ERR, "Auditing of %s failed: %s", description, how);
    goto out;
  }

  if (size != sizeof(*event)) {
    how = "bad event size";
    pr_log_pri(PR_LOG_ERR, "Auditing of %s failed: %s", description, how);
    goto out;
  }

  if (fill_event != NULL) {
    msg = fill_event(cmd, event);
    if (msg != NULL) {
      pr_log_pri(PR_LOG_ERR, "Auditing of %s failed: %s", description, msg);
      goto out;
    }
  }

  /* It can happen, that the ftp command succeeds but only to some degree.
   * In such case, the exit_error might contain the errno number
   * of the failure.
   */
  if (exit_status == ADT_SUCCESS) {
    if (exit_error == ADT_FAILURE)
      exit_error = ADT_SUCCESS;
  }

  if (adt_put_event(event, exit_status, exit_error) != 0) {
    how = "couldn't put adt event";
    pr_log_pri(PR_LOG_ERR, "Auditing of %s failed: %s (%s)",
      description, how, strerror(errno));
  }

  adt_free_event(event);

out:
  return PR_DECLINED(cmd);
}

/*
 * This is a generic function to fill in the given "stat" member
 * of some audit event structure. The path and the member are specified
 * by the caller. The pointer to cmd is supplied, because the stat64
 * structure has to be allocated (the "stat" member is a pointer).
 *
 * The function returns NULL on success.
 * In case of an error, it returns a descriptive message.
 * This message is used by the caller to log an error.
 *
 * For some file transfer commands, the "stat" member is filled in
 * the "pre-" handler (because the file is expected to exist prior
 * to the execution of the command). For other file transfer commands,
 * the "stat" member is filled in the "post-" handler (because
 * the file is expected _not_ to exist prior to the execution of the command,
 * but to exist after the command execution).
 */
static const char* __fill_attr
(
  cmd_rec *cmd, const char* path, adt_stat_t **ret)
{
  struct stat64 *ptr;
  int err;

  if (ret == NULL)
    return "NULL pointer";

  *ret = NULL;

  ptr = palloc(cmd->pool, sizeof(*ptr));
  if (ptr == NULL)
    return "no memory";

  err = stat64(path, ptr);
  if (err == -1)
    return "stat64() failed";

  *ret = ptr;
  return NULL;
}
/* } */


/* Delete file. { */
static const char* dele_fill_attr(cmd_rec *cmd, adt_event_data_t *event) {
  return __fill_attr(
    cmd, event->adt_ft_remove.f_path, &(event->adt_ft_remove.f_attr)
  );
}

MODRET solaris_audit_pre_dele(cmd_rec *cmd) {
  adt_event_data_t *event = NULL;
  char* ptr = NULL;
  char* rp = NULL;

  event = __solaris_audit_pre_arg2(cmd, "remove", ADT_ft_remove, &ptr);
  if (event == NULL) {
    error_451();
    return PR_ERROR(cmd);
  }

  rp = realpath(ptr, src_realpath);
  if (rp == NULL) {
    if (errno != ENOENT) {
      pr_log_pri(PR_LOG_ERR, "Auditing of %s(%s) failed: %s",
        "remove", ptr, "realpath() failed");
      cmd->error_code = errno;
      error_451();
      return PR_ERROR(cmd);
    }
    /* If rp is NULL and errno is ENOENT, it means that 
     * the file to be deleted does not exist. In this case,
     * the post_dele_err callback will be called to log this.
     */
  }

  if (rp != NULL)
    ptr = rp;    

  event->adt_ft_remove.f_path = ptr;
  (void) dele_fill_attr(cmd, event);

  return PR_DECLINED(cmd);
}

MODRET solaris_audit_post_dele(cmd_rec *cmd) {
  return __solaris_audit_post(
    cmd, "remove", ADT_SUCCESS, ADT_SUCCESS, NULL);
}

MODRET solaris_audit_post_dele_err(cmd_rec *cmd) {
  return __solaris_audit_post(cmd, "remove", ADT_FAILURE, ADT_FAILURE, NULL);
}
/* } */


/* Make directory. { */
MODRET solaris_audit_pre_mkd(cmd_rec *cmd) {
  adt_event_data_t *event = NULL;
  char* ptr = NULL;

  event = __solaris_audit_pre_arg2(cmd, "mkdir", ADT_ft_mkdir, &ptr);
  if (event == NULL) {
    error_451();
    return PR_ERROR(cmd);
  }

  event->adt_ft_mkdir.d_path = ptr;
  event->adt_ft_mkdir.d_attr = NULL;

  /* Value 0777 is hardcoded in the ftp server. */
  event->adt_ft_mkdir.arg = 0777;
  event->adt_ft_mkdir.arg_id = 2;
  event->adt_ft_mkdir.arg_desc = "mode";

  return PR_DECLINED(cmd);
}

static const char* mkd_fill_event(cmd_rec *cmd, adt_event_data_t *event) {
  char *rp = NULL;

  rp = realpath(event->adt_ft_mkdir.d_path, src_realpath);
  if (rp == NULL) {
    cmd->error_code = errno;
    return "realpath() failed";
  }

  event->adt_ft_mkdir.d_path = rp;
  return __fill_attr(
    cmd, event->adt_ft_mkdir.d_path, &(event->adt_ft_mkdir.d_attr)
  );
}

static const char* mkd_fill_event_err(cmd_rec *cmd, adt_event_data_t *event) {
  char *rp = NULL;

  rp = realpath(event->adt_ft_mkdir.d_path, src_realpath);
  if (rp != NULL) {
    event->adt_ft_mkdir.d_path = rp;
    (void) __fill_attr(
      cmd, event->adt_ft_mkdir.d_path, &(event->adt_ft_mkdir.d_attr)); 
  }

  return NULL;
}

MODRET solaris_audit_post_mkd(cmd_rec *cmd) {
  return __solaris_audit_post(
    cmd, "mkdir", ADT_SUCCESS, ADT_SUCCESS, mkd_fill_event);
}

MODRET solaris_audit_post_mkd_err(cmd_rec *cmd) {
  return __solaris_audit_post(
    cmd, "mkdir", ADT_FAILURE, ADT_FAILURE, mkd_fill_event_err);
}
/* } */

/* Remove directory. { */
static const char* rmd_fill_attr(cmd_rec *cmd, adt_event_data_t *event) {
  return __fill_attr(
    cmd, event->adt_ft_rmdir.f_path, &(event->adt_ft_rmdir.f_attr)
  );
}

MODRET solaris_audit_pre_rmd(cmd_rec *cmd) {
  adt_event_data_t *event = NULL;
  char* ptr = NULL;
  char* rp = NULL;
 
  event = __solaris_audit_pre_arg2(cmd, "rmdir", ADT_ft_rmdir, &ptr);
  if (event == NULL) {
    error_451();
    return PR_ERROR(cmd);
  }

  rp = realpath(ptr, src_realpath);
  if (rp == NULL) {
    if (errno != ENOENT) {
      cmd->error_code = errno;
      pr_log_pri(PR_LOG_ERR, "Auditing of %s(%s) failed: %s",
        "rmdir", ptr, "realpath() failed");
      error_451();
      return PR_ERROR(cmd);
    }
  }

  if (rp != NULL)
    ptr = rp;

  event->adt_ft_rmdir.f_path = ptr;
  (void) rmd_fill_attr(cmd, event);

  return PR_DECLINED(cmd);
}

MODRET solaris_audit_post_rmd(cmd_rec *cmd) {
  return __solaris_audit_post(cmd, "rmdir", ADT_SUCCESS, ADT_SUCCESS, NULL);
}

MODRET solaris_audit_post_rmd_err(cmd_rec *cmd) {
  return __solaris_audit_post(cmd, "rmdir", ADT_FAILURE, ADT_FAILURE, NULL);
}
/* } */

/* Get modification time and date. { */
MODRET solaris_audit_pre_mdtm(cmd_rec *cmd) {
  adt_event_data_t *event = NULL;
  char* ptr = NULL;
  char* rp = NULL;
  
  event = __solaris_audit_pre_arg2(cmd, "utimes", ADT_ft_utimes, &ptr);
  if (event == NULL) {
    error_451();
    return PR_ERROR(cmd);
  }

  rp = realpath(ptr, src_realpath);
  if (rp == NULL) {
    if (errno != ENOENT) {
      cmd->error_code = errno;
      pr_log_pri(PR_LOG_ERR, "Auditing of %s(%s) failed: %s",
        "utimes", ptr, "realpath() failed");
      error_451();
      return PR_ERROR(cmd);
    }
  }

  if (rp != NULL)
    ptr = rp;

  event->adt_ft_utimes.f_path = ptr;
  event->adt_ft_utimes.f_attr = NULL;

  return PR_DECLINED(cmd);
}

static const char* mdtm_fill_attr(cmd_rec *cmd, adt_event_data_t *event) {
  return __fill_attr(
    cmd, event->adt_ft_utimes.f_path, &(event->adt_ft_utimes.f_attr)
  );
}

MODRET solaris_audit_post_mdtm(cmd_rec *cmd) {
  return __solaris_audit_post(
    cmd, "utimes", ADT_SUCCESS, ADT_SUCCESS, mdtm_fill_attr);
}

MODRET solaris_audit_post_mdtm_err(cmd_rec *cmd) {
  return __solaris_audit_post(cmd, "utimes", ADT_FAILURE, ADT_FAILURE, NULL);
}
/* } */

/* Upload file. { */
MODRET solaris_audit_pre_put(cmd_rec *cmd) {
  adt_event_data_t *event = NULL;
  char* ptr = NULL;
  
  event = __solaris_audit_pre_arg2(cmd, "put", ADT_ft_put, &ptr);
  if (event == NULL) {
    error_451();
    return PR_ERROR(cmd);
  }

  event->adt_ft_put.f_path = ptr;
  event->adt_ft_put.f_attr = NULL;

  return PR_DECLINED(cmd);
}

static const char* put_fill_event(cmd_rec *cmd, adt_event_data_t *event) {
  char *rp = NULL;

  rp = realpath(event->adt_ft_put.f_path, src_realpath);
  if (rp == NULL) {
    cmd->error_code = errno;
    return "realpath() failed";
  }

  event->adt_ft_put.f_path = rp;
  return __fill_attr(
    cmd, event->adt_ft_put.f_path, &(event->adt_ft_put.f_attr)
  );
}

MODRET solaris_audit_post_put(cmd_rec *cmd) {
  return __solaris_audit_post(
    cmd, "put", ADT_SUCCESS, ADT_SUCCESS, put_fill_event);
}

MODRET solaris_audit_post_put_err(cmd_rec *cmd) {
  return __solaris_audit_post(cmd, "put", ADT_FAILURE, ADT_FAILURE, NULL);
}
/* } */

/* Download file. { */
MODRET solaris_audit_pre_get(cmd_rec *cmd) {
  adt_event_data_t *event = NULL;
  char* ptr = NULL;
  char* rp = NULL;
  
  event = __solaris_audit_pre_arg2(cmd, "get", ADT_ft_get, &ptr);
  if (event == NULL) {
    error_451();
    return PR_ERROR(cmd);
  }

  rp = realpath(ptr, src_realpath);
  if (rp == NULL) {
    if (errno != ENOENT) {
      cmd->error_code = errno;
      pr_log_pri(PR_LOG_ERR, "Auditing of %s(%s) failed: %s",
        "get", ptr, "realpath() failed");
      error_451();
      return PR_ERROR(cmd);
    }
  }

  if (rp != NULL)
    ptr = rp;

  event->adt_ft_get.f_path = ptr;
  event->adt_ft_get.f_attr = NULL;

  return PR_DECLINED(cmd);
}

static const char* get_fill_attr(cmd_rec *cmd, adt_event_data_t *event) {
  return __fill_attr(
    cmd, event->adt_ft_get.f_path, &(event->adt_ft_get.f_attr)
  );
}

MODRET solaris_audit_post_get(cmd_rec *cmd) {
  return __solaris_audit_post(
    cmd, "get", ADT_SUCCESS, ADT_SUCCESS, get_fill_attr);
}

MODRET solaris_audit_post_get_err(cmd_rec *cmd) {
  return __solaris_audit_post(cmd, "get", ADT_FAILURE, ADT_FAILURE, NULL);
}
/* } */

/* Rename file. { */
/*
 * The rename file implementation uses malloc()/free(),
 * which the ProFTP module interface prohibits. I do not see another way.
 * 
 * Any memory allocation method provided by the ProFTP API uses a memory pool.
 * To avoid malloc()/free() a persistent memory pool is needed.
 */

/*
 * To successfully log the rename audit event, a cooperation
 * of RNFR and RNTO command handlers is necessary.
 * The RNFR command specifies the source file name,
 * and the RNTO command specifies the destination file name.
 * 
 * The RNFR command handlers save the source file in the "src_path"
 * variable, so that it is available to the RNTO command handler,
 * which logs the audit event.
 */
static char* src_path = NULL;

/* RNFR. { */
static void __solaris_audit_rnfr_err(cmd_rec *cmd)
{
  adt_event_data_t *event = NULL;

  if (src_path == NULL)
    return;

  event = __solaris_audit_pre_arg2(cmd, "RNFR", ADT_ft_rename, NULL);
  if (event == NULL) {
    error_451();
    goto out;
  }

  event->adt_ft_rename.src_path = src_path;
  event->adt_ft_rename.src_attr = NULL;
  event->adt_ft_rename.dst_path = NULL;

  (void) __solaris_audit_post(cmd, "RNFR", ADT_FAILURE, ADT_FAILURE, NULL);

out:
  free(src_path);
  src_path = NULL;
}

MODRET solaris_audit_pre_rnfr(cmd_rec *cmd) {
  adt_event_data_t *event = NULL;
  char* ptr = NULL;

  /*
   * If src_path is not NULL, it means that this RNFR command immediatelly
   * follows a successfull RNFR command not terminated with a RNTO command.
   * In such case, log an audit error for this unterminated RNFR command,
   * and then continue normally.
   *
   * A correctly working ftp client can not cause this situation to happen.
   * But this situation can be created, for instance, by manually sending
   * commands to the ftp server with a telnet client.
   */
  if (src_path != NULL)
    __solaris_audit_rnfr_err(cmd);

  /*
   * Prepare the audit event structure and remember the new src_path.
   * This audit event structure will be used, if the RNFR command fails.
   * It will be unused, if it succeeds.
   */
  event = __solaris_audit_pre_arg2(cmd, "get", ADT_ft_rename, &ptr);
  if (event == NULL)
    goto err;

  event->adt_ft_rename.src_path = ptr;
  event->adt_ft_rename.src_attr = NULL;
  event->adt_ft_rename.dst_path = "";

  src_path = strdup(cmd->arg);
  if (src_path == NULL) {
    pr_log_pri(PR_LOG_ERR, "Auditing of %s(%s) failed: %s",
      "RNFR", ptr, "no memory");
    goto err;
  }

  return PR_DECLINED(cmd);
err:
  return PR_ERROR(cmd);
}

/*
 * On success, the RNFR command handlers do not log any audit event.
 * A success means that a rename command is in progress and that
 * the immediatelly following command is to be RNTO. 
 */
MODRET solaris_audit_post_rnfr(cmd_rec *cmd) {

  char *ptr;

  ptr = realpath(src_path, src_realpath);
  if (ptr == NULL) {
    pr_log_pri(PR_LOG_ERR, "Auditing of %s(%s) failed: %s",
      "RNFR", src_path, "realpath() failed");
    error_451();
    return PR_ERROR(cmd);
  }

  /*
   * The argument to RNFR command is saved in src_path.
   * It will be used in the subsequent RNTO command, or RNFR command.
   */
  return PR_DECLINED(cmd);
}

/* It can happen, that RNFR command fails, but the source path exists.
 * Therefore make an attempt to resolve its realpath before doing
 * the audit log.
 *
 * Even if the realpath() call fails, the src_path contents are still
 * copied to src_realpath buffer. This makes them available to the RNTO
 * command handlers.
 */
static const char* rnfr_err_fill_event(cmd_rec *cmd, adt_event_data_t *event) {
  char *ptr = NULL;

  if (src_path != NULL) {
    ptr = realpath(src_path, src_realpath);
    if (ptr != NULL)
      event->adt_ft_rename.src_path = ptr;
  }

  return NULL;
}

/*
 * On error, an audit event is logged, specifying that a rename
 * command failed. The destination path in the audit event structure
 * is empty, simply because the corresponding RNTO command did not yet
 * happen, and it is not suppossed to happen.
 */
MODRET solaris_audit_post_rnfr_err(cmd_rec *cmd) {
  MODRET ret;

  ret = __solaris_audit_post(cmd, "RNFR", ADT_FAILURE, ADT_FAILURE,
    rnfr_err_fill_event);

  free(src_path);
  src_path = NULL;

  return ret;
}
/* } RNFR. */

/* RNTO. { */
static const char* rnto_fill_attr(cmd_rec *cmd, adt_event_data_t *event) {
  return __fill_attr(
    cmd, event->adt_ft_rename.src_path, &(event->adt_ft_rename.src_attr)
  );
}

MODRET solaris_audit_pre_rnto(cmd_rec *cmd) {
  adt_event_data_t *event = NULL;
  const char* msg = NULL;
  char* ptr = NULL;

  event = __solaris_audit_pre_arg2(cmd, "get", ADT_ft_rename, &ptr);
  if (event == NULL)
    goto err;

  /*
   * If src_path is NULL, this means that there is no previous
   * successfull RNFR command. The ftp server should know about this
   * and terminate this RNTO command with an error (call the error callback).
   */
  event->adt_ft_rename.src_path = (src_path)?src_path:"";
  event->adt_ft_rename.dst_path = ptr;

  /*
   * If the code executes here, it means that there is a successfully finished
   * RNFR command immediatelly before us, which means that the src_path exists,
   * and it should be therefore possible to get its status.
   */
  msg = rnto_fill_attr(cmd, event);  
  if (msg != NULL) {
    pr_log_pri(PR_LOG_ERR, "Auditing of %s(%s,%s) failed: %s",
      "RNTO", event->adt_ft_rename.src_path, ptr, msg);
    goto err;
  }

  return PR_DECLINED(cmd);

err:
  error_451();
  return PR_ERROR(cmd);
}

static const char* rnto_fill_event(cmd_rec *cmd, adt_event_data_t *event) {
  char *ptr;

  ptr = realpath(event->adt_ft_rename.dst_path, dst_realpath);
  if (ptr == NULL) {
    return "realpath() failed";
  }

  event->adt_ft_rename.src_path = src_realpath;
  event->adt_ft_rename.dst_path = dst_realpath;

  return NULL;
}

MODRET solaris_audit_post_rnto(cmd_rec *cmd) {
   MODRET retval;

  /* NULL means that there is no preceeding successfull RNFR command. */
  if (src_path == NULL)
    return PR_ERROR(cmd);

  retval = __solaris_audit_post(cmd, "RNTO", ADT_SUCCESS, ADT_SUCCESS,
    rnto_fill_event);
  
  free(src_path);
  src_path = NULL;

  return retval;
}

/* It can happen, that RNTO command fails, but the destination path exists.
 * Therefore make an attempt to resolve its realpath before doing
 * the audit log.
 */
static const char* rnto_err_fill_event(cmd_rec *cmd, adt_event_data_t *event) {

  (void) realpath(event->adt_ft_rename.dst_path, dst_realpath);
  event->adt_ft_rename.src_path = src_realpath;
  event->adt_ft_rename.dst_path = dst_realpath;

  return NULL;
}

MODRET solaris_audit_post_rnto_err(cmd_rec *cmd) {
  MODRET retval;
  retval = __solaris_audit_post(cmd, "RNTO", ADT_FAILURE, ADT_FAILURE,
    rnto_err_fill_event);
  if (src_path != NULL) {
    free(src_path);
    src_path = NULL;
  }
  return retval;
}
/* } RNTO. */

static cmdtable solaris_audit_commands[] = {
    /* Login, logout. */
    { POST_CMD, C_PASS, G_NONE, solaris_audit_post_pass, FALSE, FALSE },
    { POST_CMD_ERR, C_PASS, G_NONE, solaris_audit_post_fail, FALSE, FALSE },

    /* Delete file. */
    { PRE_CMD, C_DELE, G_NONE, solaris_audit_pre_dele, FALSE, FALSE },
    { POST_CMD, C_DELE, G_NONE, solaris_audit_post_dele, FALSE, FALSE },
    { POST_CMD_ERR, C_DELE, G_NONE, solaris_audit_post_dele_err,
        FALSE, FALSE },

    /* Make directory. */
    { PRE_CMD, C_MKD, G_NONE, solaris_audit_pre_mkd, FALSE, FALSE },
    { POST_CMD, C_MKD, G_NONE, solaris_audit_post_mkd, FALSE, FALSE },
    { POST_CMD_ERR, C_MKD, G_NONE, solaris_audit_post_mkd_err,
        FALSE, FALSE },

    /* Remove directory. */
    { PRE_CMD, C_RMD, G_NONE, solaris_audit_pre_rmd, FALSE, FALSE },
    { POST_CMD, C_RMD, G_NONE, solaris_audit_post_rmd, FALSE, FALSE },
    { POST_CMD_ERR, C_RMD, G_NONE, solaris_audit_post_rmd_err,
        FALSE, FALSE },

    { PRE_CMD, C_XRMD, G_NONE, solaris_audit_pre_rmd, FALSE, FALSE },
    { POST_CMD, C_XRMD, G_NONE, solaris_audit_post_rmd, FALSE, FALSE },
    { POST_CMD_ERR, C_XRMD, G_NONE, solaris_audit_post_rmd_err,
        FALSE, FALSE },

    /* Get modification time. */
    { PRE_CMD, C_MDTM, G_NONE, solaris_audit_pre_mdtm, FALSE, FALSE },
    { POST_CMD, C_MDTM, G_NONE, solaris_audit_post_mdtm, FALSE, FALSE },
    { POST_CMD_ERR, C_MDTM, G_NONE, solaris_audit_post_mdtm_err,
        FALSE, FALSE },

    /* Upload file. */
    { PRE_CMD, C_STOR, G_WRITE, solaris_audit_pre_put, FALSE, FALSE },
    { POST_CMD, C_STOR, G_WRITE, solaris_audit_post_put, FALSE, FALSE },
    { POST_CMD_ERR, C_STOR, G_WRITE, solaris_audit_post_put_err,
        FALSE, FALSE },

    { PRE_CMD, C_STOU, G_WRITE, solaris_audit_pre_put, FALSE, FALSE },
    { POST_CMD, C_STOU, G_WRITE, solaris_audit_post_put, FALSE, FALSE },
    { POST_CMD_ERR, C_STOU, G_WRITE, solaris_audit_post_put_err,
        FALSE, FALSE },

    { PRE_CMD, C_APPE, G_WRITE, solaris_audit_pre_put, FALSE, FALSE },
    { POST_CMD, C_APPE, G_WRITE, solaris_audit_post_put, FALSE, FALSE },
    { POST_CMD_ERR, C_APPE, G_WRITE, solaris_audit_post_put_err,
        FALSE, FALSE },

    /* Download file. */
    { PRE_CMD, C_RETR, G_READ, solaris_audit_pre_get, FALSE, FALSE },
    { POST_CMD, C_RETR, G_READ, solaris_audit_post_get, FALSE, FALSE },
    { POST_CMD_ERR, C_RETR, G_READ, solaris_audit_post_get_err,
        FALSE, FALSE },

    /* Rename file. */
    { PRE_CMD, C_RNFR, G_NONE, solaris_audit_pre_rnfr, FALSE, FALSE },
    { POST_CMD, C_RNFR, G_NONE, solaris_audit_post_rnfr, FALSE, FALSE },
    { POST_CMD_ERR, C_RNFR, G_NONE, solaris_audit_post_rnfr_err,
        FALSE, FALSE },

    { PRE_CMD, C_RNTO, G_NONE, solaris_audit_pre_rnto, FALSE, FALSE },
    { POST_CMD, C_RNTO, G_NONE, solaris_audit_post_rnto, FALSE, FALSE },
    { POST_CMD_ERR, C_RNTO, G_NONE, solaris_audit_post_rnto_err,
        FALSE, FALSE },

	{ 0, NULL }
};

module solaris_audit_module = {
	NULL, NULL,		/* Always NULL */
	0x20,			/* API Version 2.0 */
	"solaris_audit",
	NULL,			/* configuration table */
	solaris_audit_commands,	/* command table is for local use only */
	NULL,			/* No authentication handlers */
	NULL,			/* No initialization function */
	audit_sess_init		/* Post-fork "child mode" init */
};
