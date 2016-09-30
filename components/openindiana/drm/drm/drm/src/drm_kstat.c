/*
 * Copyright (c) 2006, 2012, Oracle and/or its affiliates. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/*
 * Copyright (c) 2012 Intel Corporation.  All rights reserved.
 */

#include "drmP.h"
#include <sys/kstat.h>
#include <sys/ddi.h>
#include <sys/sunddi.h>
#include <sys/sunldi.h>

static char *drmkstat_name[] = {
	"opens",
	"closes",
	"IOCTLs",
	"locks",
	"unlocks",
	NULL
};

static int
drm_kstat_update(kstat_t *ksp, int flag)
{
	struct drm_device *sc;
	kstat_named_t *knp;
	int tmp;

	if (flag != KSTAT_READ)
		return (EACCES);

	sc = ksp->ks_private;
	knp = ksp->ks_data;

	for (tmp = 1; tmp < 6; tmp++) {
		(knp++)->value.ui32 = sc->counts[tmp];
	}

	return (0);
}

int
drm_init_kstats(struct drm_device *sc)
{
	int instance;
	kstat_t *ksp;
	kstat_named_t *knp;
	char *np;
	char **aknp;

	instance = ddi_get_instance(sc->devinfo);
	aknp = drmkstat_name;
	ksp = kstat_create("drm", instance, "drminfo", "drm",
	    KSTAT_TYPE_NAMED, sizeof (drmkstat_name)/sizeof (char *) - 1,
	    KSTAT_FLAG_PERSISTENT);
	if (ksp == NULL)
		return (NULL);

	ksp->ks_private = sc;
	ksp->ks_update = drm_kstat_update;
	for (knp = ksp->ks_data; (np = (*aknp)) != NULL; knp++, aknp++) {
		kstat_named_init(knp, np, KSTAT_DATA_UINT32);
	}
	kstat_install(ksp);

	sc->asoft_ksp = ksp;

	return (0);
}

void
drm_fini_kstats(struct drm_device *sc)
{
	if (sc->asoft_ksp)
		kstat_delete(sc->asoft_ksp);
	else
		cmn_err(CE_WARN, "attempt to delete null kstat");
}
