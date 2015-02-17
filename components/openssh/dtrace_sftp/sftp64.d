/*
 * Copyright (c) 2009, 2015, Oracle and/or its affiliates. All rights reserved.
 */

#pragma D depends_on library net.d
#pragma D depends_on library io.d
#pragma D depends_on module lofs

typedef struct sftpinfo {
	string sfi_user;		/* user name */
	string sfi_operation;		/* SFTP Operation */
	ssize_t sfi_nbytes;		/* bytes transferred, if any */
	string sfi_pathname;		/* pathname of transfer */
	string sfi_fsresource;		/* Dataset(ZFS) or resource name */
} sftpinfo_t;

/*
 * This structure must match the definition of same in sftp_provider_impl.h.
 */
typedef struct sftpproto {
	int64_t sftp_nbytes;		/* bytes written or read */
	uint64_t sftp_user;		/* user name */
	uint64_t sftp_operation;	/* SFTP operation */
	uint64_t sftp_raddr;		/* remote address */
	uint64_t sftp_pathname;		/* path with file name */
	int32_t sftp_fd;		/* fd for transfer, if any */
} sftpproto_t;

#pragma D binding "1.6.1" translator
translator conninfo_t <sftpproto_t *s> {
	ci_protocol = "tcp";
	ci_remote = copyinstr((uintptr_t)
	    *(uint64_t *)copyin((uintptr_t)&s->sftp_raddr, sizeof (uint64_t)));
	ci_local = "<unknown>";
};

#pragma D binding "1.6.1" translator
translator sftpinfo_t <sftpproto_t *s> {
	sfi_user = copyinstr((uintptr_t)
	    *(uint64_t *)copyin((uintptr_t)&s->sftp_user, sizeof (uint64_t)));
	sfi_operation = copyinstr((uintptr_t)
	    *(uint64_t *)copyin((uintptr_t)&s->sftp_operation,
	    sizeof (uint64_t)));
	sfi_nbytes =
	    *(uint64_t *)copyin((uintptr_t)&s->sftp_nbytes, sizeof (uint64_t));
	sfi_fsresource = stringof(fds[*(int32_t *)copyin((uintptr_t)&s->sftp_fd,
	    sizeof (int32_t))].fi_fs) == "lofs" ? stringof(((struct loinfo *)
	    curthread->t_procp->p_user.u_finfo.fi_list[*(int32_t *)copyin(
	    (uintptr_t)&s->sftp_fd, sizeof (int32_t))].uf_file->f_vnode->
	    v_vfsp->vfs_data)->li_realvfs->vfs_resource->rs_string) :
	    stringof(curthread->t_procp->p_user.u_finfo.fi_list[
	    *(int32_t *)copyin((uintptr_t)&s->sftp_fd, sizeof (int32_t))].
	    uf_file->f_vnode->v_vfsp->vfs_resource->rs_string);
	sfi_pathname = copyinstr((uintptr_t)*(uint64_t *)copyin(
	    (uintptr_t)&s->sftp_pathname, sizeof (uint64_t)));
};
