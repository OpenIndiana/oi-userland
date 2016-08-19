/*
 * Copyright (c) 2006, 2013, Oracle and/or its affiliates. All rights reserved.
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

/*
 * Common misc module interfaces of DRM under Solaris
 */

/*
 * I915 DRM Driver for Solaris
 *
 * This driver provides the hardware 3D acceleration support for Intel
 * integrated video devices (e.g. i8xx/i915/i945 series chipsets), under the
 * DRI (Direct Rendering Infrastructure). DRM (Direct Rendering Manager) here
 * means the kernel device driver in DRI.
 *
 * I915 driver is a device dependent driver only, it depends on a misc module
 * named drm for generic DRM operations.
 *
 * This driver also calls into gfx and agpmaster misc modules respectively for
 * generic graphics operations and AGP master device support.
 */

#ifndef	_SYS_DRM_SUNMOD_H_
#define	_SYS_DRM_SUNMOD_H_

#ifdef	__cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <sys/errno.h>
#include <sys/conf.h>
#include <sys/kmem.h>
#include <sys/visual_io.h>
#include <sys/fbio.h>
#include <sys/ddi.h>
#include <sys/sunddi.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/open.h>
#include <sys/modctl.h>
#include <sys/pci.h>
#include <sys/kd.h>
#include <sys/ddi_impldefs.h>
#include <sys/sunldi.h>
#include <sys/mkdev.h>
#include <sys/gfx_private.h>
#include <sys/agpgart.h>
#include <sys/agp/agpdefs.h>
#include <sys/agp/agpmaster_io.h>
#include "drmP.h"
#include <sys/modctl.h>


/* graphics name for the common graphics minor node */
#define	GFX_NAME		"gfx"

/*
 * softstate for DRM module
 */
typedef struct drm_instance_state {
	kmutex_t		mis_lock;
	kmutex_t		dis_ctxlock;
	major_t			mis_major;
	dev_info_t		*mis_dip;
	drm_device_t	*mis_devp;
	ddi_acc_handle_t	mis_cfg_hdl;
	agp_master_softc_t	*mis_agpm;	/* agpmaster softstate ptr */
	gfxp_vgatext_softc_ptr_t	mis_gfxp;	/* gfx softstate */
} drm_inst_state_t;


struct drm_inst_state_list {
	drm_inst_state_t	disl_state;
	struct drm_inst_state_list *disl_next;

};
typedef struct drm_inst_state_list drm_inst_list_t;

extern struct list_head drm_iomem_list;

static int drm_sun_open(dev_t *, int, int, cred_t *);
static int drm_sun_close(dev_t, int, int, cred_t *);
static int drm_sun_ioctl(dev_t, int, intptr_t, int, cred_t *, int *);
static int drm_sun_devmap(dev_t, devmap_cookie_t,
	offset_t, size_t, size_t *, uint_t);
static int drm_sun_chpoll(dev_t, short, int, short *, struct pollhead **);
static int drm_sun_read(dev_t, struct uio *, cred_t *);

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_DRM_SUNMOD_H_ */
