/*
 * Copyright (c) 2009, 2015, Oracle and/or its affiliates. All rights reserved.
 */

#pragma D depends_on library net.d

typedef struct ftpinfo {
	string fti_user;                /* user name */
	string fti_cmd;                 /* FTP command */
	string fti_pathname;            /* path of file being operated upon */
	uint64_t fti_nbytes;            /* bytes transferred, if any */
	int fti_fd;                     /* fd for transfer, if any */
} ftpinfo_t;

/*
 * This structure must match the definition of same in ftp_provider_impl.h.
 */
typedef struct ftpproto {
	uint32_t ftp_user;              /* user name */
	uint32_t ftp_cmd;               /* FTP command */
	uint32_t ftp_pathname;          /* path of file being operated upon */
	uint32_t ftp_raddr;             /* remote address, as IPv6 address */
	uint32_t ftp_fd;                /* fd for transfer, if any */
	uint32_t ftp_pad;               /* padding for copyin() */
	uint64_t ftp_nbytes;            /* bytes transferred, if any */
} ftpproto_t;

#pragma D binding "1.6.1" translator
translator conninfo_t <ftpproto_t *f> {
	ci_protocol = "tcp";
	ci_remote = copyinstr((uintptr_t)
	*(uint32_t *)copyin((uintptr_t)&f->ftp_raddr, sizeof (uint32_t)));
	ci_local = "<unknown>";
};

#pragma D binding "1.6.1" translator
translator ftpinfo_t <ftpproto_t *f> {
	fti_user = copyinstr((uintptr_t)
	    *(uint32_t *)copyin((uintptr_t)&f->ftp_user, sizeof (uint32_t)));
	fti_cmd = copyinstr((uintptr_t)
	    *(uint32_t *)copyin((uintptr_t)&f->ftp_cmd, sizeof (uint32_t)));
	fti_pathname = copyinstr((uintptr_t)
	    *(uint32_t *)copyin((uintptr_t)&f->ftp_pathname,
	    sizeof (uint32_t)));
	fti_nbytes =
	    *(uint64_t *)copyin((uintptr_t)&f->ftp_nbytes, sizeof (uint64_t));
	fti_fd = *(uint32_t *)copyin((uintptr_t)&f->ftp_fd, sizeof (uint32_t));
};
