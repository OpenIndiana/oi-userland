/*
 * ProFTPD - FTP server daemon
 * Copyright (c) 1997, 1998 Public Flood Software
 * Copyright (c) 2003-2010 The ProFTPD Project team
 * Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
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
 * As a special exemption, the copyright holders give permission to link
 * this program with OpenSSL and distribute the resulting executable without
 * including the source code for OpenSSL in the source distribution.
 */

/* Use Solaris privileges to severely limit root's access. After user
 * authentication, this module _completely_ gives up most privileges,
 * except for the * bare minimum functionality that is required. 
 * VERY highly recommended for security-consious admins.
 *
 * The concept of this was copied from the Linux mod_cap.  Solaris
 * also has the concept of basic privileges that we can take away to further
 * restrict a process lower than what a normal user process can do, this
 * module removes some of those as well.
 */

#include <stdio.h>
#include <stdlib.h>

#include <priv.h>

#include "conf.h"
#include "privs.h"

#define MOD_SOLARIS_PRIV_VERSION	"mod_solaris_priv/1.0"

/* Configuration handlers
 */

#define	PRIV_USE_FILE_CHOWN		0x0001
#define	PRIV_USE_FILE_CHOWN_SELF	0x0002
#define	PRIV_USE_DAC_READ		0x0004
#define	PRIV_USE_DAC_WRITE		0x0008
#define	PRIV_USE_DAC_SEARCH		0x0010
#define	PRIV_USE_SETID			0x0020
#define	PRIV_USE_FILE_OWNER		0x0040
#define	PRIV_DROP_FILE_WRITE		0x0080

static unsigned int solaris_priv_flags = 0;
static unsigned char use_privs = TRUE;

MODRET set_solaris_priv(cmd_rec *cmd) {
  unsigned int flags = 0;
  config_rec *c = NULL;
  register unsigned int i = 0;

  if (cmd->argc - 1 < 1)
    CONF_ERROR(cmd, "need at least one parameter");

  CHECK_CONF(cmd, CONF_ROOT|CONF_VIRTUAL|CONF_GLOBAL);

  /* PRIV_CHOWN is enabled by default. */
  flags |= PRIV_USE_FILE_CHOWN;

  for (i = 1; i < cmd->argc; i++) {
    char *cp = cmd->argv[i];
    cp++;

    if (*cmd->argv[i] != '+' && *cmd->argv[i] != '-')
      CONF_ERROR(cmd, pstrcat(cmd->tmp_pool, ": bad option: '",
        cmd->argv[i], "'", NULL));

    if (strcasecmp(cp, "PRIV_USE_FILE_CHOWN") == 0) {
      if (*cmd->argv[i] == '-')
        flags &= ~PRIV_USE_FILE_CHOWN;

    } else if (strcasecmp(cp, "PRIV_FILE_CHOWN_SELF") == 0) {
      if (*cmd->argv[i] == '-')
        flags &= ~PRIV_USE_FILE_CHOWN_SELF;

    } else if (strcasecmp(cp, "PRIV_DAC_READ") == 0) {
      if (*cmd->argv[i] == '+')
        flags |= PRIV_USE_DAC_READ;

    } else if (strcasecmp(cp, "PRIV_DAC_WRITE") == 0) {
      if (*cmd->argv[i] == '+')
        flags |= PRIV_USE_DAC_WRITE;

    } else if (strcasecmp(cp, "PRIV_DAC_SEARCH") == 0) {
      if (*cmd->argv[i] == '+')
        flags |= PRIV_USE_DAC_SEARCH;

    } else if (strcasecmp(cp, "PRIV_FILE_OWNER") == 0) {
      if (*cmd->argv[i] == '+')
        flags |= PRIV_USE_FILE_OWNER;

    } else {
      CONF_ERROR(cmd, pstrcat(cmd->tmp_pool, "unknown privilege: '",
        cp, "'", NULL));
    }
  }

  c = add_config_param(cmd->argv[0], 1, NULL);
  c->argv[0] = pcalloc(c->pool, sizeof(unsigned int));
  *((unsigned int *) c->argv[0]) = flags;

  return PR_HANDLED(cmd);
}


MODRET set_solaris_priv_engine(cmd_rec *cmd) {
  int bool = -1;
  config_rec *c = NULL;

  CHECK_ARGS(cmd, 1);
  CHECK_CONF(cmd, CONF_ROOT|CONF_VIRTUAL|CONF_GLOBAL);

  bool = get_boolean(cmd, 1);
  if (bool == -1)
    CONF_ERROR(cmd, "expecting Boolean parameter");

  c = add_config_param(cmd->argv[0], 1, NULL);
  c->argv[0] = pcalloc(c->pool, sizeof(unsigned char));
  *((unsigned char *) c->argv[0]) = bool;

  return PR_HANDLED(cmd);
}

/* Command handlers
 */

/* The pre and post adat command handlers first enable
 * and then disable file_dac_read. This is done in order
 * for the mod_gss module to be able to read /etc/krb5/krb5.keytab,
 * when the proftpd server runs as user/group ftp/ftp.
 */
MODRET solaris_priv_pre_adat(cmd_rec *cmd) {
    priv_set(PRIV_ON, PRIV_EFFECTIVE, PRIV_FILE_DAC_READ, NULL);
    return PR_DECLINED(cmd);
}

MODRET solaris_priv_post_adat(cmd_rec *cmd) {
    priv_set(PRIV_OFF, PRIV_EFFECTIVE, PRIV_FILE_DAC_READ, NULL);
    return PR_DECLINED(cmd);
}

static void set_privs(void) {
    /* This is for PAM code which decides to create an audit session
     * when the user is logging into ftp as root.
     */
    priv_set(PRIV_ON, PRIV_EFFECTIVE, PRIV_PROC_AUDIT, NULL);
    priv_set(PRIV_ON, PRIV_EFFECTIVE, PRIV_SYS_AUDIT, NULL);

    /* Needed to call seteuid(). */
    priv_set(PRIV_ON, PRIV_EFFECTIVE, PRIV_PROC_SETID, NULL);

    /* Needed to call settaskid(). */
    priv_set(PRIV_ON, PRIV_EFFECTIVE, PRIV_PROC_TASKID, NULL);

    /* Needed to access /dev/urandom. */
    priv_set(PRIV_ON, PRIV_EFFECTIVE, PRIV_SYS_DEVICES, NULL);

    /* Needed for pam_unix_cred to chown files. */
    priv_set(PRIV_ON, PRIV_EFFECTIVE, PRIV_FILE_CHOWN_SELF, NULL);
    priv_set(PRIV_ON, PRIV_EFFECTIVE, PRIV_FILE_CHOWN, NULL);
    priv_set(PRIV_ON, PRIV_EFFECTIVE, PRIV_FILE_OWNER, NULL);

    /* Needed to access /var/adm/wtmpx. */
    priv_set(PRIV_ON, PRIV_EFFECTIVE, PRIV_FILE_DAC_WRITE, NULL);

    /* Enable chroot for anonymous login. */
    priv_set(PRIV_ON, PRIV_EFFECTIVE, PRIV_PROC_CHROOT, NULL);
}

/* Setup priviledges before the user responds to the user prompt
 * from the ftp server so that a secure Kerberos session can be
 * established and also the user can login as root
 * when the ftp server is running as user/group ftp/ftp.
 */
MODRET solaris_priv_pre_pass(cmd_rec *cmd) {
    set_privs();
    return PR_DECLINED(cmd);
}

static priv_set_t* allocset(void) {
  priv_set_t* ret;

  if ((ret = priv_allocset()) == NULL) {
    pr_log_pri(PR_LOG_ERR, MOD_SOLARIS_PRIV_VERSION ": priv_allocset: %s",
      strerror(errno));
    pr_signals_unblock();
    end_login(1);
  }

  return ret;
}

static void delset(priv_set_t *sp, const char *priv) {
  if (priv_delset(sp, priv) != 0) {
    pr_log_pri(PR_LOG_ERR, MOD_SOLARIS_PRIV_VERSION ": priv_delset: %s",
      strerror(errno));
    pr_signals_unblock();
    end_login(1);
  }
}

static void addset(priv_set_t *sp, const char *priv) {
  if (priv_addset(sp, priv) != 0) {
    pr_log_pri(PR_LOG_ERR, MOD_SOLARIS_PRIV_VERSION ": priv_addset: %s",
      strerror(errno));
    pr_signals_unblock();
    end_login(1);
  }
}

static void _setppriv(priv_op_t op, priv_ptype_t which, priv_set_t *set) {
  if (setppriv(op, which, set) != 0) {
    pr_log_pri(PR_LOG_ERR, MOD_SOLARIS_PRIV_VERSION ": setppriv: %s",
      strerror(errno));
    pr_signals_unblock();
    end_login(1);
  }
}

/* The POST_CMD handler for "PASS" is only called after PASS has
 * successfully completed, which means authentication is successful,
 * so we can "tweak" our root access down to almost nothing.
 */
MODRET solaris_priv_post_pass(cmd_rec *cmd) {
  int res = 0;
  priv_set_t *ps = NULL;

  if (!use_privs)
    return PR_DECLINED(cmd);

  pr_signals_block();

  /* The only privilege we need is PRIV_NET_PRIVADDR (bind
   * ports < 1024).  Everything else can be discarded.  We set this
   * in the permitted set only, as when we switch away from root
   * we lose effective anyhow, and must reset it.
   *
   * We also remove the basic Solaris privileges we know we will
   * never need.
   */

  ps = allocset();
  priv_basicset(ps);
  delset(ps, PRIV_PROC_EXEC);
  delset(ps, PRIV_PROC_FORK);
  delset(ps, PRIV_PROC_INFO);
  delset(ps, PRIV_PROC_SESSION);
  _setppriv(PRIV_SET, PRIV_INHERITABLE, ps);

  priv_basicset(ps);

  addset(ps, PRIV_NET_PRIVADDR);
  addset(ps, PRIV_PROC_AUDIT);

  delset(ps, PRIV_PROC_EXEC);
  delset(ps, PRIV_PROC_FORK);
  delset(ps, PRIV_PROC_INFO);
  delset(ps, PRIV_PROC_SESSION);

  /* If the proftpd process is not running as root, but as user ftp,
   * then this is necessary in order to make the setreuid work.
   * Without this, the setreuid would fail. The PRIV_PROC_SETID privilege 
   * is removed afterwards.
   */
  addset(ps, PRIV_PROC_SETID);

  /* Add any of the configurable privileges. */
  if (solaris_priv_flags & PRIV_USE_FILE_CHOWN)
    addset(ps, PRIV_FILE_CHOWN);

  if (solaris_priv_flags & PRIV_USE_FILE_CHOWN_SELF)
    addset(ps, PRIV_FILE_CHOWN_SELF);

  if (solaris_priv_flags & PRIV_USE_DAC_READ)
    addset(ps, PRIV_FILE_DAC_READ);

  if (solaris_priv_flags & PRIV_USE_DAC_WRITE)
    addset(ps, PRIV_FILE_DAC_WRITE);

  if (solaris_priv_flags & PRIV_USE_DAC_SEARCH)
    addset(ps, PRIV_FILE_DAC_SEARCH);

  if (solaris_priv_flags & PRIV_USE_FILE_OWNER)
    addset(ps, PRIV_FILE_OWNER);

  if (solaris_priv_flags & PRIV_DROP_FILE_WRITE)
    delset(ps, PRIV_FILE_WRITE);

  _setppriv(PRIV_SET, PRIV_PERMITTED, ps);
  _setppriv(PRIV_SET, PRIV_EFFECTIVE, ps);

  if (setreuid(session.uid, session.uid) == -1) {
    pr_log_pri(PR_LOG_ERR, MOD_SOLARIS_PRIV_VERSION ": setreuid: %s",
      strerror(errno));
    pr_signals_unblock();
    end_login(1);
  }

  if (!(solaris_priv_flags & PRIV_USE_SETID)) {
    delset(ps, PRIV_PROC_SETID);
    _setppriv(PRIV_SET, PRIV_PERMITTED, ps);
    _setppriv(PRIV_SET, PRIV_EFFECTIVE, ps);
  }

  priv_freeset(ps);

  pr_signals_unblock();

  /* That's it!  Disable all further id switching */
  session.disable_id_switching = TRUE;

  return PR_DECLINED(cmd);
}

/* Initialization routines
 */

static int solaris_priv_sess_init(void) {
  /* Check to see if the lowering of capabilities has been disabled in the
   * configuration file.
   */
  if (use_privs) {
    unsigned char *solaris_priv_engine;

    solaris_priv_engine = get_param_ptr(main_server->conf, "PrivilegeEngine", FALSE);
    if (solaris_priv_engine &&
        *solaris_priv_engine == FALSE) {
      pr_log_debug(DEBUG3, MOD_SOLARIS_PRIV_VERSION
        ": lowering of capabilities disabled");
      use_privs = FALSE;
    }
  }

  /* Check for which specific capabilities to include/exclude. */
  if (use_privs) {
    int use_setuid = FALSE;
    config_rec *c;

    c = find_config(main_server->conf, CONF_PARAM, "PrivilegeSet", FALSE);
    if (c != NULL) {
      solaris_priv_flags = *((unsigned int *) c->argv[0]);

      if (!(solaris_priv_flags & PRIV_USE_FILE_CHOWN)) {
        pr_log_debug(DEBUG3, MOD_SOLARIS_PRIV_VERSION
          ": removing PRIV_CHOWN privilege");
      }

      if (solaris_priv_flags & PRIV_USE_DAC_READ) {
        pr_log_debug(DEBUG3, MOD_SOLARIS_PRIV_VERSION
          ": adding PRIV_FILE_DAC_READ privilege"); 
      }

      if (solaris_priv_flags & PRIV_USE_DAC_WRITE) {
        pr_log_debug(DEBUG3, MOD_SOLARIS_PRIV_VERSION
          ": adding PRIV_FILE_DAC_WRITE privilege"); 
      }

      if (solaris_priv_flags & PRIV_USE_DAC_SEARCH) {
        pr_log_debug(DEBUG3, MOD_SOLARIS_PRIV_VERSION
          ": adding PRIV_DAC_SEARCH privilege");
      }

      if (solaris_priv_flags & PRIV_USE_FILE_OWNER) {
        pr_log_debug(DEBUG3, MOD_SOLARIS_PRIV_VERSION
          ": adding PRIV_FILE_OWNER privilege");
      }
    }

    c = find_config(main_server->conf, CONF_PARAM, "AllowOverwrite", FALSE);
    if (c && *((int *) c->argv[0]) == FALSE) {
        pr_log_debug(DEBUG3, MOD_SOLARIS_PRIV_VERSION
          ": removing PRIV_FILE_WRITE basic privilege");
        solaris_priv_flags |= PRIV_DROP_FILE_WRITE;
    }
	    

    /* We also need to check for things which want to revoke root privs
     * altogether: mod_exec, mod_sftp, and the RootRevoke directive.
     * Revoking root privs completely requires the SETUID/SETGID
     * capabilities.
     */

    if (use_setuid == FALSE &&
        pr_module_exists("mod_sftp.c")) {
      c = find_config(main_server->conf, CONF_PARAM, "SFTPEngine", FALSE);
      if (c &&
          *((int *) c->argv[0]) == TRUE) {
        use_setuid = TRUE;
      }
    }

    if (use_setuid == FALSE &&
        pr_module_exists("mod_exec.c")) {
      c = find_config(main_server->conf, CONF_PARAM, "ExecEngine", FALSE);
      if (c &&
          *((unsigned char *) c->argv[0]) == TRUE) {
        use_setuid = TRUE;
      }
    }

    if (use_setuid == FALSE) {
      c = find_config(main_server->conf, CONF_PARAM, "RootRevoke", FALSE);
      if (c &&
          *((unsigned char *) c->argv[0]) == TRUE) {
        use_setuid = TRUE;
      }
    }

    if (use_setuid) {
      solaris_priv_flags |= PRIV_USE_SETID;
      pr_log_debug(DEBUG3, MOD_SOLARIS_PRIV_VERSION
        ": adding PRIV_SETID ");
    }

  }

  return 0;
}

static int solaris_priv_module_init(void) {

  return 0;
}


/* Module API tables
 */

static conftable solaris_priv_conftab[] = {
  { "PrivilegeEngine", set_solaris_priv_engine, NULL },
  { "PrivilegeSet",    set_solaris_priv,        NULL },
  { NULL, NULL, NULL }
};

static cmdtable solaris_priv_cmdtab[] = {
  { PRE_CMD, C_ADAT, G_NONE, solaris_priv_pre_adat, FALSE, FALSE },
  { POST_CMD, C_ADAT, G_NONE, solaris_priv_post_adat, FALSE, FALSE },
  { PRE_CMD, C_PASS, G_NONE, solaris_priv_pre_pass, FALSE, FALSE },
  { POST_CMD, C_PASS, G_NONE, solaris_priv_post_pass, FALSE, FALSE },
  { 0, NULL }
};

module solaris_priv_module = {
  NULL, NULL,

  /* Module API version */
  0x20,

  /* Module name */
  "cap",

  /* Module configuration handler table */
  solaris_priv_conftab,

  /* Module command handler table */
  solaris_priv_cmdtab,

  /* Module authentication handler table */
  NULL,

  /* Module initialization */
  solaris_priv_module_init,

  /* Session initialization */
  solaris_priv_sess_init,

  /* Module version */
  MOD_SOLARIS_PRIV_VERSION
};
