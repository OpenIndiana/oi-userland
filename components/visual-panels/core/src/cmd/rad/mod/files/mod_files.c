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
 * Copyright (c) 2009, 2012, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * Unfortunately, the behavior this module has inherited is not one
 * of "get me information about file X or directory Y", but "tell me
 * what calling 'new File(X)' would do in Java".  This includes
 * nonsense like manufacturing correct fake data for nonexistent
 * files.
 *
 * This sorely needs to be ripped out and replaced with a sane
 * api.
 */

#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <libgen.h>
#include <limits.h>

#include <rad/adr.h>
#include <rad/rad_modapi.h>

#include "api_file.h"

static adr_data_t *
empty_file(adr_data_t *data, const char *apath, const char *cpath)
{
	adr_struct_set(data, "absolutePath",
	    adr_data_new_string(apath, LT_COPY));
	adr_struct_set(data, "canonicalPath",
	    adr_data_new_string(cpath, LT_COPY));
	adr_struct_set(data, "canonical", adr_data_new_boolean(B_TRUE));
	adr_struct_set(data, "baseName", adr_data_new_string("", LT_COPY));
	adr_struct_set(data, "exists", adr_data_new_boolean(B_FALSE));
	adr_struct_set(data, "readable", adr_data_new_boolean(B_FALSE));
	adr_struct_set(data, "writable", adr_data_new_boolean(B_FALSE));
	adr_struct_set(data, "hidden", adr_data_new_boolean(B_FALSE));
	adr_struct_set(data, "directory", adr_data_new_boolean(B_FALSE));
	adr_struct_set(data, "file", adr_data_new_boolean(B_FALSE));
	adr_struct_set(data, "lastModified", adr_data_new_time(0, 0));
	adr_struct_set(data, "length", adr_data_new_long(0));
	adr_struct_set(data, "freeSpace", adr_data_new_long(0));
	adr_struct_set(data, "totalSpace", adr_data_new_long(0));
	adr_struct_set(data, "usableSpace", adr_data_new_long(0));
	return (adr_data_purify(data));
}

static adr_data_t *
read_file(const char *path, const char *file)
{
	struct stat64 st;
	char apath[PATH_MAX] = "";
	char cpath[PATH_MAX] = "";
	const char *name = file != NULL ? file : path;

	adr_data_t *data = adr_data_new_struct(&t__FileSnapshot);
	adr_struct_set(data, "path", adr_data_new_string(name, LT_COPY));
	adr_struct_set(data, "absolute", adr_data_new_boolean(name[0] == '/'));

	if (path[0] != '/') {
		if (getcwd(apath, PATH_MAX) == NULL) {
			adr_data_free(data);
			return (NULL);
		}
		if (apath[1] != '\0')
			(void) strlcat(apath, "/", PATH_MAX);
		(void) strlcat(apath, path, PATH_MAX);
	} else {
		(void) strlcpy(apath, path, PATH_MAX);
	}

	if (resolvepath(apath, cpath, PATH_MAX) == -1 ||
	    stat64(path, &st) == -1)
		return (empty_file(data, apath, apath));

	adr_struct_set(data, "absolutePath",
	    adr_data_new_string(apath, LT_COPY));
	adr_struct_set(data, "canonicalPath",
	    adr_data_new_string(cpath, LT_COPY));
	adr_struct_set(data, "canonical",
	    adr_data_new_boolean(strcmp(apath, cpath) == 0));
	adr_struct_set(data, "baseName",
	    adr_data_new_string(basename(apath), LT_COPY));
	adr_struct_set(data, "exists", adr_data_new_boolean(B_TRUE));
	adr_struct_set(data, "readable",
	    adr_data_new_boolean(access(path, R_OK) == 0));
	adr_struct_set(data, "writable",
	    adr_data_new_boolean(access(path, W_OK) == 0));
	adr_struct_set(data, "hidden", adr_data_new_boolean(B_FALSE));
	adr_struct_set(data, "directory",
	    adr_data_new_boolean(S_ISDIR(st.st_mode)));
	adr_struct_set(data, "file", adr_data_new_boolean(S_ISREG(st.st_mode)));
	adr_struct_set(data, "lastModified", adr_data_new_time_ts(&st.st_mtim));
	/* XXX: 64-bitify */
	adr_struct_set(data, "length", adr_data_new_long(st.st_size));
	adr_struct_set(data, "freeSpace", adr_data_new_long(0));
	adr_struct_set(data, "totalSpace", adr_data_new_long(0));
	adr_struct_set(data, "usableSpace", adr_data_new_long(0));
	return (adr_data_purify(data));
}

/* ARGSUSED */
conerr_t
interface_FileBrowser_read_roots(rad_instance_t *inst, adr_attribute_t *attr,
    adr_data_t **data, adr_data_t **error)
{
	adr_data_t *result = adr_data_new_array(&t_array__FileSnapshot, 1);
	(void) adr_array_add(result, read_file("/", NULL));
	*data = adr_data_purify(result);
	return (ce_ok);
}

/* ARGSUSED */
conerr_t
interface_FileBrowser_invoke_getFile(rad_instance_t *inst, adr_method_t *meth,
    adr_data_t **ret, adr_data_t **args, int count, adr_data_t **error)
{
	*ret = read_file(adr_data_to_string(args[0]), NULL);
	return (ce_ok);
}

/* ARGSUSED */
conerr_t
interface_FileBrowser_invoke_getFiles(rad_instance_t *inst, adr_method_t *meth,
    adr_data_t **ret, adr_data_t **args, int count, adr_data_t **error)
{
	const char *path = adr_data_to_string(args[0]);
	DIR *d = opendir(path);
	struct dirent *ent;
	adr_data_t *result;

	if (d == NULL)
		return (ce_object);

	result = adr_data_new_array(&t_array__FileSnapshot, 1);
	while ((ent = readdir(d)) != NULL) {
		char buf[PATH_MAX];
		if (strcmp(ent->d_name, ".") == 0 ||
		    strcmp(ent->d_name, "..") == 0)
			continue;
		int len = strlen(path);
		while (len > 0 && path[len - 1] == '/')
			len--;
		(void) snprintf(buf, PATH_MAX, "%.*s/%s", len, path,
		    ent->d_name);
		adr_data_t *file = read_file(buf, NULL);
		if (file != NULL)
			(void) adr_array_add(result, file);
	}
	(void) closedir(d);
	*ret = adr_data_purify(result);

	return (ce_ok);
}

static rad_modinfo_t modinfo = { "files", "File Browser module" };

int
_rad_init(void *handle)
{
	if (rad_module_register(handle, RAD_MODVERSION, &modinfo) == -1)
		return (-1);

	if (rad_isproxy)
		return (0);

	(void) cont_insert_singleton(rad_container, adr_name_fromstr(
	    "com.oracle.solaris.vp.panel.common.api.file:type=FileBrowser"),
	    &interface_FileBrowser_svr);

	return (0);
}
