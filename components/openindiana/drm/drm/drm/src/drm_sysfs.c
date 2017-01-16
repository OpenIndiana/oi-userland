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
#include "drmP.h"
#include <sys/agpgart.h>
#include <sys/agp/agpdefs.h>
#include <sys/agp/agpmaster_io.h>

/**
 * drm_sysfs_device_add - adds a class device to sysfs for a character driver
 * @dev: DRM device to be added
 * @head: DRM head in question
 *
 * Add a DRM device to the DRM's device model class.  We use @dev's PCI device
 * as the parent for the Linux device, and make sure it has a file containing
 * the driver we're using (for userspace compatibility).
 */
int drm_sysfs_device_add(struct drm_minor *minor)
{
	struct drm_device *dev = minor->dev;
	gfxp_vgatext_softc_ptr_t gfxp;
	int ret;

	switch (minor->type) {
	case DRM_MINOR_AGPMASTER:
		ret = agpmaster_attach(dev->devinfo,
		    (agp_master_softc_t **)&minor->private,
		    dev->pdev->pci_cfg_acc_handle, minor->index);
		if (ret != DDI_SUCCESS) {
			DRM_ERROR("agpmaster_attach failed");
			return (ret);
		}
		return (0);

	case DRM_MINOR_VGATEXT:
		/* Generic graphics initialization */
		gfxp = gfxp_vgatext_softc_alloc();
		ret = gfxp_vgatext_attach(dev->devinfo, DDI_ATTACH, gfxp);
		if (ret != DDI_SUCCESS) {
			DRM_ERROR("gfxp_vgatext_attach failed");
			return (EFAULT);
		}
		minor->private = gfxp;

		ret = ddi_create_minor_node(dev->devinfo,
		    minor->name, S_IFCHR, minor->index, DDI_NT_DISPLAY, NULL);
		if (ret != DDI_SUCCESS) {
			DRM_ERROR("ddi_create_minor_node failed");
			return (EFAULT);
		}
		return (0);

	case DRM_MINOR_LEGACY:
	case DRM_MINOR_CONTROL:
	case DRM_MINOR_RENDER:
		ret = ddi_create_minor_node(dev->devinfo,
		    minor->name, S_IFCHR, minor->index, DDI_NT_DISPLAY_DRM, NULL);
		if (ret != DDI_SUCCESS) {
			DRM_ERROR("ddi_create_minor_node failed");
			return (EFAULT);
		}
		return (0);
	}

	return (ENOTSUP);
}

/**
 * drm_sysfs_device_remove - remove DRM device
 * @dev: DRM device to remove
 *
 * This call unregisters and cleans up a class device that was created with a
 * call to drm_sysfs_device_add()
 */
void drm_sysfs_device_remove(struct drm_minor *minor)
{
	switch (minor->type) {
	case DRM_MINOR_AGPMASTER:
		if (minor->private) {
			agpmaster_detach(
			    (agp_master_softc_t **)&minor->private);
			minor->private = NULL;
		}
		break;

	case DRM_MINOR_VGATEXT:
		if (minor->private) {
			(void) gfxp_vgatext_detach(minor->dev->devinfo,
			    DDI_DETACH, minor->private);
			gfxp_vgatext_softc_free(minor->private);
			minor->private = NULL;
		}

	/* LINTED */
	case DRM_MINOR_LEGACY:
	case DRM_MINOR_CONTROL:
	case DRM_MINOR_RENDER:
		ddi_remove_minor_node(minor->dev->devinfo, minor->name);
	}
}
