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

#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <libxml/tree.h>
#include <limits.h>
#include <openssl/evp.h>
#include <openssl/md5.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "api_panels.h"

#define	PANELDESCDIR	"/usr/share/vpanels/conf"

#define	HASH_BSIZE	65536

/*
 * Function prototypes
 */

static int md5_file(const char *fname, unsigned char *hash);
static data_t *get_text(xmlDoc *doc, xmlNode *node);
static char *get_text_str(xmlDoc *doc, xmlNode *node);
static data_t *get_prop(xmlNode *node, const char *name);
static data_t *file_to_token(rad_locale_t *rlocale, const char *pname,
    char *file);
static conerr_t token_to_file(data_t *t, char **f);
static data_t *create_resource(rad_locale_t *rlocale, const char *pname,
    char *file);
static void add_localized(rad_locale_t *rlocale, const char *pname,
    data_t *farray, char *file);
static data_t *read_panel_path(rad_locale_t *rlocale, const char *path);
static data_t *read_panel(const char *locale, const char *pname);

/*
 * Static data
 */

static xmlDtd *dtd;
static rad_modinfo_t modinfo = { "panels", "Visual Panels module" };

/*
 * Static functions
 */

static int
md5_file(const char *fname, unsigned char *hash)
{
	int fd, len = -1;
	MD5_CTX ctx;

	char *buffer = malloc(HASH_BSIZE);
	if (buffer == NULL)
		return (-1);

	if ((fd = open(fname, O_RDONLY)) == -1) {
		free(buffer);
		return (-1);
	}

	if (MD5_Init(&ctx) == 0)
		goto out;

	while ((len = read(fd, buffer, HASH_BSIZE)) > 0)
		if (MD5_Update(&ctx, buffer, len) == 0) {
			len = -1;
			break;
		}
	if (MD5_Final(hash, &ctx) == 0)
		len = -1;

out:
	(void) close(fd);
	free(buffer);
	return (len);	/* Should be 0 or -1 */
}

/*
 * Seems like overkill, but it's better than mixing xml-allocated
 * and other strings.
 */
static data_t *
get_text(xmlDoc *doc, xmlNode *node)
{
	data_t *result;
	xmlChar *d = xmlNodeListGetString(doc, node, 1);
	if (d == NULL)
		return (NULL);

	result = data_new_string((char *)d, lt_copy);
	xmlFree(d);
	return (result);
}

static char *
get_text_str(xmlDoc *doc, xmlNode *node)
{
	char *result;
	xmlChar *d = xmlNodeListGetString(doc, node, 1);
	if (d == NULL)
		return (NULL);

	result = strdup((char *)d);
	xmlFree(d);
	return (result);
}

static data_t *
get_prop(xmlNode *node, const char *name)
{
	data_t *result;
	xmlChar *d = xmlGetProp(node, (xmlChar *)name);
	if (d == NULL)
		return (NULL);

	result = data_new_string((char *)d, lt_copy);
	xmlFree(d);
	return (result);
}

static data_t *
file_to_token(rad_locale_t *rlocale, const char *pname, char *file)
{
	int llen = strlen(rlocale->locale);
	int plen = strlen(pname);
	int flen = strlen(file);
	int tokenlen = llen + 1 + plen + 1 + flen + 1;

	char *token = rad_zalloc(tokenlen);
	if (token == NULL) {
		return (NULL);
	}

	char *p = token;
	(void) strcpy(p, rlocale->locale);
	p += llen + 1;
	(void) strcpy(p, pname);
	p += plen + 1;
	(void) strcpy(p, file);

	return (data_new_opaque(token, tokenlen, lt_free));
}

static conerr_t
token_to_file(data_t *t, char **f)
{
	char *token = data_to_opaque(t);
	char tokenlen = opaque_size(t);

	/* Cursory validation */
	int nullcnt = 0;
	for (int i = 0; i < tokenlen; i++) {
		if (token[i] == '\0') {
			nullcnt++;
		}
	}
	if (nullcnt != 3 || token[tokenlen - 1] != '\0') {
		/* Bad token */
		return (ce_object);
	}

	char *locale = token;
	char *pname = locale + strlen(locale) + 1;
	char *file = pname + strlen(pname) + 1;

	data_t *panel = read_panel(locale, pname);
	if (panel == NULL) {
		/* Bad panel */
		return (ce_object);
	}

	data_t *resources = struct_get(panel, "resourceDescriptors");
	static const char * const path[] = { "file", NULL };
	int index = array_search(resources, file, path);
	data_free(panel);
	if (index == -1) {
		/* Bad file */
		return (ce_object);
	}

	*f = strdup(file);
	if (*f == NULL) {
		return (ce_nomem);
	}

	return (ce_ok);
}

static data_t *
create_resource(rad_locale_t *rlocale, const char *pname, char *file)
{
	unsigned char hbuf[MD5_DIGEST_LENGTH];
	if (md5_file(file, hbuf) != 0) {
		return (NULL);
	}

	data_t *result = data_new_struct(&t__ResourceDescriptor);
	struct_set(result, "token", file_to_token(rlocale, pname, file));
	struct_set(result, "file", data_new_string(file, lt_copy));
	struct_set(result, "hashAlgorithm", data_new_string("MD5", lt_const));
	struct_set(result, "hash", data_new_opaque(hbuf, MD5_DIGEST_LENGTH,
	    lt_copy));

	return (result);
}

static void
add_localized(rad_locale_t *rlocale, const char *pname, data_t *farray,
    char *file)
{
	if (rlocale != NULL && rlocale->language != NULL &&
	    strlen(rlocale->language)) {
		char path[PATH_MAX + 1];
		(void) strlcpy(path, file, PATH_MAX);

		char *ext = strrchr(path, '.');
		if (ext != NULL && strcmp(ext, ".jar") == 0) {
			*ext = '\0';
			char *base = strrchr(path, '/');
			if (base == NULL) {
				return;
			}
			*base++ = '\0';

			char *fmt[] = {NULL, NULL, NULL};

			/*
			 * Use a ResourceBundle.getBundle-like algorithm -
			 * <language>[_<territory>[@<modifier>]] - and order
			 * from most- to least-specific.
			 */
			fmt[2] = "%s/locale/%s/%5$s_l10n.jar";
			if (rlocale->territory != NULL) {
				fmt[1] = "%s/locale/%s_%s/%5$s_l10n.jar";
				if (rlocale->modifier != NULL) {
					fmt[0] = "%s/locale/%s_%s@%s/"
					    "%5$s_l10n.jar";
				}
			}

			char l10njar[PATH_MAX];
			for (int i = 0; i < RAD_COUNT(fmt); i++) {
				if (fmt[i] == NULL) {
					continue;
				}
				/* LINTED: E_SEC_PRINTF_VAR_FMT */
				(void) snprintf(l10njar, RAD_COUNT(l10njar),
				    fmt[i], path, rlocale->language,
				    rlocale->territory, rlocale->modifier,
				    base);
				if (access(l10njar, F_OK) == 0) {
					(void) array_add(farray,
					    create_resource(rlocale, pname,
					    l10njar));
				}
			}
		}
	}
	(void) array_add(farray, create_resource(rlocale, pname, file));
}

static data_t *
read_panel_path(rad_locale_t *rlocale, const char *path)
{
	xmlParserCtxt *ctx;
	xmlValidCtxt *vctx;
	xmlDoc *doc;
	data_t *panel = NULL;

	ctx = xmlNewParserCtxt();
	vctx = xmlNewValidCtxt();
	if (vctx == NULL || ctx == NULL)
		return (NULL);

	doc = xmlCtxtReadFile(ctx, path, NULL, 0);
	if (doc == NULL) {
		xmlFreeValidCtxt(vctx);
		xmlFreeParserCtxt(ctx);
		rad_log(RL_WARN, "Empty/no such document: %s\n", path);
		return (NULL);
	}

	/*
	 * Validate against *our* DTD.
	 */
	if (xmlValidateDtd(vctx, doc, dtd) == 0) {
		rad_log(RL_WARN, "Invalid document: %s\n", path);
		goto out;
	}

	xmlNodePtr root = xmlDocGetRootElement(doc);
	if (root == NULL || strcmp((const char *)root->name, "panel") != 0) {
		rad_log(RL_WARN, "Not a panel definition: %s\n", path);
		goto out;
	}

	panel = data_new_struct(&t__CustomPanel);
	struct_set(panel, "locale", data_new_string(rlocale->locale, lt_copy));

	data_t *pname = get_prop(root, "name");
	struct_set(panel, "name", pname);

	data_t *farray = data_new_array(&t_array__ResourceDescriptor, 1);
	struct_set(panel, "resourceDescriptors", farray);

	char *aroot = NULL;
	for (xmlNode *np = root->children; np != NULL; np = np->next) {
		if (np->type != XML_ELEMENT_NODE)
			continue;
		if (strcmp((const char *)np->name, "mainclass") == 0) {
			data_t *mc = get_text(doc, np->children);
			struct_set(panel, "panelDescriptorClassName", mc);
		} else if (strcmp((const char *)np->name, "approot") == 0) {
			if (aroot != NULL)
				continue;	/* schema violation */
			aroot = get_text_str(doc, np->children);
		} else if (strcmp((const char *)np->name, "file") == 0) {
			char *file = get_text_str(doc, np->children);
			if (file == NULL) {
				rad_log(RL_WARN,
				    "Empty <file> declaration within %s\n",
				    path);
				continue;
			}

			if (aroot == NULL) {
				rad_log(RL_WARN, "App root not specified\n");
				continue;
			}

			char full[PATH_MAX];
			(void) snprintf(full, RAD_COUNT(full), "%s/%s", aroot,
			    file);
			free(file);

			add_localized(rlocale, data_to_string(pname), farray,
			    full);
		}
	}
	if (aroot != NULL)
		free(aroot);
out:
	xmlFreeValidCtxt(vctx);
	xmlFreeDoc(doc);
	xmlFreeParserCtxt(ctx);

	return (data_purify_deep(panel));
}

static data_t *
read_panel(const char *locale, const char *pname)
{
	rad_locale_t *rlocale;
	if (rad_locale_parse(locale, &rlocale) != 0) {
		return (NULL);
	}

	char path[PATH_MAX];
	(void) snprintf(path, RAD_COUNT(path), "%s/%s.xml", PANELDESCDIR,
	    pname);
	data_t *panel = read_panel_path(rlocale, path);

	if (panel != NULL) {
		/* Sanity check - ensure panel @name matches file name */
		data_t *nameattr = struct_get(panel, "name");
		if (strcmp(data_to_string(nameattr), pname) != 0) {
			data_free(panel);
			panel = NULL;
		}
	}

	rad_locale_free(rlocale);

	return (panel);
}

/*
 * Extern functions
 */

int
_rad_init(void *handle)
{
	if (rad_module_register(handle, RAD_MODVERSION, &modinfo) == -1)
		return (-1);

	dtd = xmlParseDTD(NULL,
	    (xmlChar *)"/usr/share/lib/xml/dtd/vpanel.dtd.1");

	adr_name_t *name = adr_name_fromstr(
	    "com.oracle.solaris.vp.panel.common.api.panel:type=Panel");
	(void) cont_insert_singleton(rad_container, name, &interface_Panel_svr);

	return (0);
}

/* ARGSUSED */
conerr_t
interface_Panel_invoke_getPanel(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	const char *pname = data_to_string(args[0]);
	const char *locale = args[1] == NULL ? NULL : data_to_string(args[1]);

	data_t *panel = read_panel(locale, pname);
	if (panel == NULL) {
		/*
		 * Could be a memory or system error, but more likely an invalid
		 * name was specified.
		 */
		return (ce_object);
	}
	*ret = panel;

	return (ce_ok);
}

/* ARGSUSED */
conerr_t
interface_Panel_read_panelNames(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	data_t *array = data_new_array(&t_array_string, 0);
	if (array == NULL) {
		return (ce_nomem);
	}

	DIR *d;
	if ((d = opendir(PANELDESCDIR)) == NULL) {
		if (errno == ENOENT) {
			return (ce_ok);
		}
		return (ce_system);
	}

	struct dirent *ent;
	while ((ent = readdir(d)) != NULL) {
		char *ext = ".xml";
		size_t len = strlen(ent->d_name) - strlen(ext);
		if (len < 1 || strcmp(ent->d_name + len, ext) != 0) {
			continue;
		}
		(void) array_add(array, data_new_nstring(ent->d_name, len));
	}

	(void) closedir(d);
	*data = data_purify(array);

	return (*data == NULL ? ce_nomem : ce_ok);
}

/* ARGSUSED */
conerr_t
interface_Panel_invoke_getResource(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	char *file;
	conerr_t result = token_to_file(args[0], &file);
	if (result != ce_ok) {
		return (result);
	}

	struct stat st;
	if (stat(file, &st) != 0) {
		free(file);
		return (ce_object);
	}

	char *buffer = malloc(st.st_size);
	if (buffer == NULL) {
		free(file);
		return (ce_nomem);
	}

	int fd = open(file, O_RDONLY);
	free(file);
	if (fd == -1) {
		free(buffer);
		return (ce_priv);
	}

	if (read(fd, buffer, st.st_size) != st.st_size) {
		(void) close(fd);
		free(buffer);
		return (ce_system);
	}

	(void) close(fd);

	*ret = data_new_opaque(buffer, st.st_size, lt_free);
	return (*ret == NULL ? ce_nomem : ce_ok);
}
