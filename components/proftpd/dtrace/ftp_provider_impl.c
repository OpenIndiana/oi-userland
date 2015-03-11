/*
 * Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
 */

#include <sys/int_types.h>

#include "ftp_provider_impl.h"
#include "ftp_provider.h"

int
ftp_transfer_start_enabled(void)
{
	return (FTP_TRANSFER_START_ENABLED());
}

int
ftp_transfer_done_enabled(void)
{
	return (FTP_TRANSFER_DONE_ENABLED());
}

void
ftp_transfer_start(struct ftpproto *ptr)
{
	FTP_TRANSFER_START(ptr);
}

void
ftp_transfer_done(struct ftpproto *ptr)
{
	FTP_TRANSFER_DONE(ptr);
}
