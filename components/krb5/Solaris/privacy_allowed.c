/*
 * Copyright (c) 1998, 2015, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * privacy_allowed.c:
 *
 * This is to provide a solaris specific interface to meet the dependencies of
 * ON.
 *
 */

#include <krb5.h>

krb5_boolean
krb5_privacy_allowed(void)
{
	return (TRUE);
}
