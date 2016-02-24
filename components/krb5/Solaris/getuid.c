/*
 * Copyright (c) 2007, 2015, Oracle and/or its affiliates. All rights reserved.
 */

#include	<sys/types.h>
#include	<unistd.h>
#include	<dlfcn.h>
#include	"k5-int.h"

#define		KRB5_UID	"app_krb5_user_uid"

/*
 * mech_krb5 makes various calls to getuid().  When employed by gssd(1M) and
 * ktkt_warnd(1M), app_krb5_user_uid() is used to select a given user's
 * credential cache, rather than the id of the process.
 */
uid_t
krb5_getuid()
{
	static uid_t	(*gptr)() = NULL;
	void		*handle;

	if (gptr == NULL) {
		/*
		 * Specifically look for app_krb5_user_uid() in the application,
		 * and don't fall into an exhaustive search through all of the
		 * process dependencies.  This interface is suplied from
		 * gssd(1M) and ktkt_warnd(1M).
		 */
		if (((handle = dlopen(0, (RTLD_LAZY | RTLD_FIRST))) == NULL) ||
		    ((gptr = (uid_t (*)())dlsym(handle, KRB5_UID)) == NULL)) {
			/*
			 * Fall back to the default getuid(), which is probably
			 * libc.
			 */
			gptr = &getuid;
		}
	}

	/*
	 * Return the appropriate uid.  Note, if a default getuid() couldn't
	 * be found, the getuid assignment would have failed to relocate, and
	 * hence this module would fail to load.
	 */
	return ((*gptr)());
}
