/*
 * Copyright (c) 2009, 2015, Oracle and/or its affiliates. All rights reserved.
 */

#ifndef _FTP_PROVIDER_IMPL_H
#define	_FTP_PROVIDER_IMPL_H

/*
 * This structure must match the definition of same in ftp.d.
 */
typedef struct ftpproto {
	uint32_t ftp_user;	/* user name */
	uint32_t ftp_cmd;	/* FTP command */
	uint32_t ftp_pathname;  /* path of file being operated upon */
	uint32_t ftp_raddr;	/* remote address, as IPv6 address */
	uint32_t ftp_fd;	/* fd for transfer, if any */
	uint32_t ftp_pad;	/* padding for copyin() */
	uint64_t ftp_nbytes;	/* bytes transferred, if any */
} ftpproto_t;

#define	FTP_TRANSFER_PROTO(proto, fh, len) \
do { \
	bzero((proto), sizeof (struct ftpproto)); \
	(proto)->ftp_user = (uint32_t)session.user; \
	(proto)->ftp_cmd = (uint32_t)session.curr_cmd; \
	(proto)->ftp_pathname = (uint32_t)((fh)->fh_path); \
	(proto)->ftp_raddr = \
	    (int32_t)pr_netaddr_get_ipstr(session.c->remote_addr); \
	(proto)->ftp_fd = (uint32_t)((fh)->fh_fd); \
	(proto)->ftp_nbytes = (len); \
} while (0)

extern int ftp_transfer_start_enabled(void);
extern int ftp_transfer_done_enabled(void);
extern void ftp_transfer_start(struct ftpproto *);
extern void ftp_transfer_done(struct ftpproto *);

#endif /* _FTP_PROVIDER_IMPL_H */
