#include <assert.h>
#include <libintl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <unistd.h>

#define ST_GNU_MSG_FOUND 1
#define ST_GNU_MO_FOUND 2
#define ST_SUN_MO_FOUND 4

struct msg_pack {
	const char *locale, *domain, *binding, *msgid1;
	char msgfile[MAXPATHLEN];
	int status;
};

static char *
mk_msgfile(struct msg_pack *mp)
{
	int n = snprintf(mp->msgfile, sizeof (mp->msgfile),
	    "%s/%s/LC_MESSAGES/%s.mo", mp->binding, mp->locale, mp->domain);
	return (n < 0 || (size_t)n >= sizeof (mp->msgfile) ? NULL : mp->msgfile);
}

/* Use native gettext to decode each candidate catalogue. */
static char *
handle_mo(struct msg_pack *mp)
{
	char *result;
	if (access(mp->msgfile, R_OK) != 0)
		return (NULL);
	assert(setenv("NLSPATH", mp->msgfile, 1) == 0);
	mp->status |= ST_GNU_MO_FOUND;
	result = dgettext(mp->domain, mp->msgid1);
	if (strcmp(result, mp->msgid1) != 0)
		mp->status |= ST_GNU_MSG_FOUND;
	return (result);
}

#include "handle_locale.c"

int
main(int argc, char **argv)
{
	struct msg_pack mp = { 0 };
	char *result;
	assert(argc == 5);
	assert(unsetenv("LANGUAGE") == 0);
	mp.binding = argv[1];
	mp.locale = argv[2];
	mp.domain = argv[3];
	mp.msgid1 = "probe";
	result = handle_locale(&mp);
	assert(mp.locale == argv[2]);
	if (result == NULL)
		result = "probe";
	if (strcmp(result, argv[4]) != 0) {
		(void) fprintf(stderr, "%s: expected %s, got %s\n",
		    mp.locale, argv[4], result);
		return (1);
	}
	return (0);
}
