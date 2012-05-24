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

#include <sys/types.h>
#include <sys/processor.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <libscf.h>

#include <rad/adr.h>
#include <rad/rad_modapi.h>

#include "smfutil.h"
#include "api_time.h"

#define	NTP_CONF	"/etc/inet/ntp.conf"
#define	NTP_CONF_BAK	"/etc/inet/ntp.bak"
#define	NTP_CONF_TMP	"/etc/inet/ntp.tmp"
#define	SMF_TZ_PGNAME	"environment"
#define	SMF_TZ_PROPNAME	"TZ"
#define	ZONEINFO_DIR	"/usr/share/lib/zoneinfo/" /* trailing / essential */

/*ARGSUSED*/
conerr_t
interface_Time_read_time(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	*data = data_new_time_now();
	return (ce_ok);
}

#define	NSPERUS	(NANOSEC / MICROSEC)

/*ARGSUSED*/
conerr_t
interface_Time_write_time(rad_instance_t *inst, adr_attribute_t *attr,
    data_t *data, data_t **error)
{
	long long seconds = data_to_time_secs(data);
	int nanos = data_to_time_nsecs(data);
	int micros = nanos / NSPERUS;
	time_t newtime;
	struct timeval adj;

	if (nanos - (micros * NSPERUS) >= NSPERUS / 2) {
		micros++;
		if (micros >= MICROSEC) {
			seconds++;
			micros = 0;
		}
	}

	if (seconds > LONG_MAX)
		return (ce_object);

	newtime = (time_t)seconds;
	adj.tv_sec = 0;
	adj.tv_usec = micros;

	if (stime(&newtime) == -1 || adjtime(&adj, NULL) == -1) {
		if (errno == EPERM)
			return (ce_priv);
		return (ce_object);
	}

	return (ce_ok);
}

/*ARGSUSED*/
conerr_t
interface_Time_read_defaultTimeZone(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	char zonefile[PATH_MAX];
	int n = snprintf(zonefile, PATH_MAX, "%s", ZONEINFO_DIR);
	char *tz = zonefile + n;
	conerr_t err = smfu_get_property((char *)SCF_INSTANCE_ENV,
	    SMF_TZ_PGNAME, SMF_TZ_PROPNAME, tz, PATH_MAX - n);

	if (err == ce_ok) {
		/*
		 * The stored time zone may be the name of a symlink
		 * (i.e. "localtime"), under ZONEINFO_DIR.  Resolve that symlink
		 * and pass the actual time zone to the client.
		 */
		char resolved[PATH_MAX];
		if (realpath(zonefile, resolved) != NULL &&
		    strncmp(resolved, ZONEINFO_DIR, n) == 0) {
			tz = resolved + n;
		}
		*data = data_new_string(tz, lt_copy);
	}

	return (err);
}

/*ARGSUSED*/
conerr_t
interface_Time_write_defaultTimeZone(rad_instance_t *inst,
    adr_attribute_t *attr, data_t *data, data_t **error)
{
	conerr_t err = smfu_set_property((char *)SCF_INSTANCE_ENV,
	    SMF_TZ_PGNAME, SMF_TZ_PROPNAME, (char *)data_to_string(data));
	return (err);
}

static void
removenl(char *str)
{
	char *nl = strchr(str, '\n');
	if (nl != NULL)
		*nl = '\0';
}

/* We only recognize the disabled entries we write */
static const char *disabled = "# server ";
static const char *enabled = "server ";
static const char *ntpservers[] = {
	"time.nist.gov",
	"time-a.nist.gov",
	"time-b.nist.gov",
	"time-nw.nist.gov"
};

static const char * const si_server_path[] = { "server", NULL };

static void
disable(data_t *array, const char *srv, int len)
{
	if (array_nsearch(array, srv, len, si_server_path) >= 0)
		return;
	data_t *entry = data_new_struct(&t__ServerInfo);
	struct_set(entry, "server", data_new_nstring(srv, len));
	struct_set(entry, "enabled", data_new_boolean(B_FALSE));
	(void) array_add(array, entry);
}

static void
enable(data_t *array, const char *srv, int len)
{
	int index = array_nsearch(array, srv, len, si_server_path);
	if (index >= 0) {
		struct_set(array_get(array, index), "enabled",
		    data_new_boolean(B_TRUE));
		return;
	}
	data_t *entry = data_new_struct(&t__ServerInfo);
	struct_set(entry, "server", data_new_nstring(srv, len));
	struct_set(entry, "enabled", data_new_boolean(B_TRUE));
	(void) array_add(array, entry);
}

/*ARGSUSED*/
conerr_t
interface_Time_read_ntpServers(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	data_t *result = data_new_array(&t_array__ServerInfo, 4);
	for (int i = 0; i < RAD_COUNT(ntpservers); i++) {
		data_t *si = data_new_struct(&t__ServerInfo);
		struct_set(si, "server",
		    data_new_string(ntpservers[i], lt_copy));
		struct_set(si, "enabled", data_new_boolean(B_FALSE));
		(void) array_add(result, si);
	}

	FILE *file = fopen(NTP_CONF, "r");
	if (file != NULL) {
		char buf[1024];
		while (fgets(buf, sizeof (buf), file) != NULL) {
			boolean_t isenabled;
			char *str = buf;

			removenl(buf);
			if (rad_strccmp(disabled, str, strlen(disabled)) == 0) {
				isenabled = B_FALSE;
				str += strlen(disabled);
			} else if (rad_strccmp(enabled, str, strlen(enabled))
			    == 0) {
				isenabled = B_TRUE;
				str += strlen(enabled);
			} else {
				continue;
			}

			int len = strcspn(str, " \t");
			if (len == 0)
				continue;
			if (isenabled)
				enable(result, str, len);
			else
				disable(result, str, len);
		}
		(void) fclose(file);
	}

	*data = result;
	return (ce_ok);
}

/*ARGSUSED*/
conerr_t
interface_Time_read_sufficientlyPrivileged(rad_instance_t *inst,
    adr_attribute_t *attr, data_t **data, data_t **error)
{
	/* XXX: Crude */
	*data = data_new_boolean(getuid() == 0);
	return (ce_ok);
}

/*ARGSUSED*/
conerr_t
interface_Time_read_continents(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	FILE *file = fopen("/usr/share/lib/zoneinfo/tab/continent.tab", "r");
	char str[1024];
	data_t *result = data_new_array(&t_array__Continent, 5);
	while (fgets(str, sizeof (str), file) != NULL) {
		if (str[0] == '#')
			continue;
		removenl(str);

		char *eq = strchr(str, '\t');
		if (eq == NULL)
			continue;
		data_t *name = data_new_nstring(str, eq - str);
		data_t *desc = data_new_string(eq + 1, lt_copy);
		data_t *cont = data_new_struct(&t__Continent);
		struct_set(cont, "name", name);
		struct_set(cont, "description", desc);
		(void) array_add(result, cont);
	}
	(void) fclose(file);
	*data = result;

	return (ce_ok);
}

/*ARGSUSED*/
conerr_t
interface_Time_read_countries(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	FILE *file = fopen("/usr/share/lib/zoneinfo/tab/country.tab", "r");
	char str[1024];
	data_t *result = data_new_array(&t_array__Country, 5);
	while (fgets(str, sizeof (str), file) != NULL) {
		if (str[0] == '#')
			continue;
		removenl(str);

		char *eq = strchr(str, '\t');
		if (eq == NULL)
			continue;
		if (rad_strccmp("ee", str, eq - str) == 0 ||
		    rad_strccmp("we", str, eq - str) == 0 ||
		    rad_strccmp("me", str, eq - str) == 0)
			continue;
		data_t *code = data_new_nstring(str, eq - str);
		data_t *desc = data_new_string(eq + 1, lt_copy);
		data_t *country = data_new_struct(&t__Country);
		struct_set(country, "code", code);
		struct_set(country, "description", desc);
		(void) array_add(result, country);
	}
	(void) fclose(file);
	*data = result;

	return (ce_ok);
}

/*
 * Parse ISO 6709 -formatted coordinates
 */
struct coord {
	int deg;
	int min;
	int sec;
};

static boolean_t
parse_coord(const char *str, int len, struct coord *c)
{
	char *dot = strchr(str, '.');
	if (dot != NULL && dot < str + len)
		len = dot - str;

	if (len < 2 || len > 7)
		return (B_FALSE);

	if (len > 5) {
		const char *fmt = (len & 1) ? "%3u%2u%2u" : "%2u%2u%2u";
		return (sscanf(str, fmt, &c->deg, &c->min, &c->sec) == 3);
	} else {
		const char *fmt = (len & 1) ? "%3u%2u" : "%2u%2u";
		return (sscanf(str, fmt, &c->deg, &c->min) == 2);
	}
}

static data_t *
parse_coords(const char *str, int len)
{
	int isnorth, iseast;

	if (len > 0 && str[0] == '+')
		isnorth = 1;
	else if (len > 0 && str[0] == '-')
		isnorth = -1;
	else
		return (NULL);

	str++;
	len--;
	char *eq = strchr(str, '+');
	if (eq == NULL || eq >= str + len)
		eq = strchr(str, '-');
	if (eq == NULL || eq >= str + len)
		return (NULL);
	iseast = (*eq == '+') ? 1 : -1;

	struct coord north = { 0 };
	struct coord east = { 0 };

	if (!parse_coord(str, eq - str, &north) ||
	    !parse_coord(eq + 1, len - (eq - str + 1), &east))
		return (NULL);

	data_t *result = data_new_struct(&t__Coordinates);
	struct_set(result, "degreesE", data_new_integer(east.deg * iseast));
	struct_set(result, "minutesE", data_new_integer(east.min));
	struct_set(result, "secondsE", data_new_integer(east.sec));
	struct_set(result, "degreesN", data_new_integer(north.deg * isnorth));
	struct_set(result, "minutesN", data_new_integer(north.min));
	struct_set(result, "secondsN", data_new_integer(north.sec));
	return (result);
}

/*ARGSUSED*/
conerr_t
interface_Time_read_timeZones(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	FILE *file = fopen("/usr/share/lib/zoneinfo/tab/zone_sun.tab", "r");
	char buf[1024];
	data_t *result = data_new_array(&t_array__TimeZoneInfo, 5);
	while (fgets(buf, sizeof (buf), file) != NULL) {
		char *str = buf;
		if (str[0] == '#')
			continue;
		removenl(str);

		char *eq = strchr(str, '\t');
		if (eq == NULL)
			continue;
		if (rad_strccmp("ee", str, eq - str) == 0 ||
		    rad_strccmp("we", str, eq - str) == 0 ||
		    rad_strccmp("me", str, eq - str) == 0)
			continue;
		data_t *timezone = data_new_struct(&t__TimeZoneInfo);
		struct_set(timezone, "countryCode",
		    data_new_nstring(str, eq - str));

		str = eq + 1;
		eq = strchr(str, '\t');
		data_t *coords;
		if (eq == NULL ||
		    (coords = parse_coords(str, eq - str)) == NULL) {
			data_free(timezone);
			continue;
		}
		struct_set(timezone, "coordinates", coords);

		str = eq + 1;
		eq = strchr(str, '\t');
		data_t *tz = eq != NULL ? data_new_nstring(str, eq - str) :
		    data_new_string(str, lt_copy);
		struct_set(timezone, "name", tz);
		if (eq == NULL)
			goto done;

		str = eq + 1;
		eq = strchr(str, '\t');
		if (eq != NULL) {
			if (rad_strccmp("-", str, eq - str) != 0)
				struct_set(timezone, "altName",
				    data_new_nstring(str, eq - str));
		} else {
			if (strcmp("-", str) != 0)
				struct_set(timezone, "altName",
				    data_new_string(str, lt_copy));
			goto done;
		}

		str = eq + 1;
		if (*str != '\0' && strcmp(str, "-") != 0)
			struct_set(timezone, "comments",
			    data_new_string(str, lt_copy));

done:
		(void) array_add(result, timezone);
	}
	(void) fclose(file);
	*data = result;

	return (ce_ok);
}

/*ARGSUSED*/
conerr_t
interface_Time_write_ntpServers(rad_instance_t *inst, adr_attribute_t *attr,
    data_t *data, data_t **error)
{
	FILE *from, *to, *tmp; /* Read, write, & temp files */
	int err = 0; /* Indicates an error */
	int size = 256; /* Buffer size */
	char buffer[size]; /* Read buffer */
	size_t ch; /* Number chars read */

	/* Copy file to preserve ntp.conf upon error */
	from = fopen(NTP_CONF, "r");
	if (from == NULL) {
		if (errno == ENOENT) {
			goto nobackup;
		}
		err = errno;
		goto errorout;
	}

	to = fopen(NTP_CONF_BAK, "w");
	if (to == NULL) {
		err = errno;
		(void) fclose(from);
		goto errorout;
	}

	while ((ch = fread(buffer, 1, size, from)) > 0) {
		if (fwrite(buffer, 1, ch, to) != ch) {
			break;
		}
	}

	if (ferror(from) || ferror(to)) {
		// errno might be overwritten by fclose
		err = errno;
	}

	(void) fclose(from);
	(void) fclose(to);

	if (err != 0)
		goto errorout;

nobackup:
	/* Create temp file */
	tmp = fopen(NTP_CONF_TMP, "w");
	if (tmp == NULL) {
		err = errno;
		(void) fclose(tmp);
		goto errorout;
	}

	for (int i = 0; i < array_size(data); i++) {
		data_t *entry = array_get(data, i);
		data_t *enabled = struct_get(entry, "enabled");
		data_t *server = struct_get(entry, "server");
		if (fprintf(tmp,
		    data_to_boolean(enabled) ? "server %s\n" : "# server %s\n",
		    data_to_string(server)) < 0)
			goto writefailed;
	}
	if (fclose(tmp) == EOF)
		goto writefailed;

	/* Rename temp file */
	if (chmod(NTP_CONF_TMP, 0644) == 0 &&
	    rename(NTP_CONF_TMP, NTP_CONF) == 0)
		return (ce_ok);

writefailed:
	err = errno;
	(void) unlink(NTP_CONF_TMP);

errorout:
	return (err == EACCES ? ce_priv : ce_object);
}

static rad_modinfo_t modinfo = { "time", "Time panel support" };

int
_rad_init(void *handle)
{
	if (rad_module_register(handle, RAD_MODVERSION, &modinfo) == -1)
		return (-1);

	if (rad_isproxy)
		return (0);

	(void) cont_insert_singleton(rad_container,
	    adr_name_fromstr("com.oracle.solaris.vp.panels.time:type=Time"),
	    &interface_Time_svr);

	return (0);
}
