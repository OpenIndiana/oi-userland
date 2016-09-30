/*
 * Copyright (c) 2006, 2014, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * drm_drv.h -- Generic driver template -*- linux-c -*-
 * Created: Thu Nov 23 03:10:50 2000 by gareth@valinux.com
 */
/*
 * Copyright 1999, 2000 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.
 * Copyright (c) 2009, 2013, Intel Corporation.
 * All Rights Reserved.
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
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Rickard E. (Rik) Faith <faith@valinux.com>
 *    Gareth Hughes <gareth@valinux.com>
 *
 */

#include "drm.h"
#include "drmP.h"
#include "drm_core.h"
#include "drm_io32.h"
#include "drm_sarea.h"
#include "drm_linux_list.h"

static int drm_version(DRM_IOCTL_ARGS);

/** Ioctl table */
static struct drm_ioctl_desc drm_ioctls[] = {
	DRM_IOCTL_DEF(DRM_IOCTL_VERSION, drm_version, DRM_UNLOCKED, copyin32_drm_version, copyout32_drm_version),
	DRM_IOCTL_DEF(DRM_IOCTL_GET_UNIQUE, drm_getunique, 0, copyin32_drm_unique, copyout32_drm_unique),
	DRM_IOCTL_DEF(DRM_IOCTL_GET_MAGIC, drm_getmagic, 0, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_IRQ_BUSID, drm_irq_by_busid, DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_GET_MAP, drm_getmap, DRM_UNLOCKED, copyin32_drm_map, copyout32_drm_map),
	DRM_IOCTL_DEF(DRM_IOCTL_GET_CLIENT, drm_getclient, DRM_UNLOCKED, copyin32_drm_client, copyout32_drm_client),
	DRM_IOCTL_DEF(DRM_IOCTL_GET_STATS, drm_getstats, DRM_UNLOCKED, NULL, copyout32_drm_stats),
	DRM_IOCTL_DEF(DRM_IOCTL_GET_CAP, drm_getcap, DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_SET_VERSION, drm_setversion, DRM_MASTER, NULL, NULL),

	DRM_IOCTL_DEF(DRM_IOCTL_SET_UNIQUE, drm_setunique, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_BLOCK, drm_noop, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_UNBLOCK, drm_noop, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_AUTH_MAGIC, drm_authmagic, DRM_AUTH|DRM_MASTER, NULL, NULL),

	DRM_IOCTL_DEF(DRM_IOCTL_ADD_MAP, drm_addmap_ioctl, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, copyin32_drm_map, copyout32_drm_map),
	DRM_IOCTL_DEF(DRM_IOCTL_RM_MAP, drm_rmmap_ioctl, DRM_AUTH, copyin32_drm_map, copyout32_drm_map),

	DRM_IOCTL_DEF(DRM_IOCTL_SET_SAREA_CTX, drm_setsareactx, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, copyin32_drm_ctx_priv_map, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_GET_SAREA_CTX, drm_getsareactx, DRM_AUTH, copyin32_drm_ctx_priv_map, copyout32_drm_ctx_priv_map),

	DRM_IOCTL_DEF(DRM_IOCTL_SET_MASTER, drm_setmaster_ioctl, DRM_ROOT_ONLY, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_DROP_MASTER, drm_dropmaster_ioctl, DRM_ROOT_ONLY, NULL, NULL),

	DRM_IOCTL_DEF(DRM_IOCTL_ADD_CTX, drm_addctx, DRM_AUTH|DRM_ROOT_ONLY, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_RM_CTX, drm_rmctx, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MOD_CTX, drm_modctx, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_GET_CTX, drm_getctx, DRM_AUTH, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_SWITCH_CTX, drm_switchctx, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_NEW_CTX, drm_newctx, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_RES_CTX, drm_resctx, DRM_AUTH, copyin32_drm_ctx_res, copyout32_drm_ctx_res),

	DRM_IOCTL_DEF(DRM_IOCTL_ADD_DRAW, drm_noop, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_RM_DRAW, drm_noop, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),

	DRM_IOCTL_DEF(DRM_IOCTL_LOCK, drm_lock, DRM_AUTH, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_UNLOCK, drm_unlock, DRM_AUTH, NULL, NULL),

	DRM_IOCTL_DEF(DRM_IOCTL_FINISH, drm_noop, DRM_AUTH, NULL, NULL),

	DRM_IOCTL_DEF(DRM_IOCTL_ADD_BUFS, drm_addbufs, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, copyin32_drm_buf_desc, copyout32_drm_buf_desc),
	DRM_IOCTL_DEF(DRM_IOCTL_MARK_BUFS, drm_markbufs, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_INFO_BUFS, drm_infobufs, DRM_AUTH, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MAP_BUFS, drm_mapbufs, DRM_AUTH, copyin32_drm_buf_map, copyout32_drm_buf_map),
	DRM_IOCTL_DEF(DRM_IOCTL_FREE_BUFS, drm_freebufs, DRM_AUTH, copyin32_drm_buf_free, NULL),
	/* The DRM_IOCTL_DMA ioctl should be defined by the driver. */
	DRM_IOCTL_DEF(DRM_IOCTL_DMA, NULL, DRM_AUTH, NULL, NULL),

	DRM_IOCTL_DEF(DRM_IOCTL_CONTROL, drm_control, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),

	DRM_IOCTL_DEF(DRM_IOCTL_AGP_ACQUIRE, drm_agp_acquire_ioctl, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_AGP_RELEASE, drm_agp_release_ioctl, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_AGP_ENABLE, drm_agp_enable_ioctl, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_AGP_INFO, drm_agp_info_ioctl, DRM_AUTH, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_AGP_ALLOC, drm_agp_alloc_ioctl, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_AGP_FREE, drm_agp_free_ioctl, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_AGP_BIND, drm_agp_bind_ioctl, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_AGP_UNBIND, drm_agp_unbind_ioctl, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),

	DRM_IOCTL_DEF(DRM_IOCTL_SG_ALLOC, drm_sg_alloc_ioctl, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, copyin32_drm_scatter_gather, copyout32_drm_scatter_gather),
	DRM_IOCTL_DEF(DRM_IOCTL_SG_FREE, drm_sg_free, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, copyin32_drm_scatter_gather, NULL),

	DRM_IOCTL_DEF(DRM_IOCTL_WAIT_VBLANK, drm_wait_vblank, DRM_UNLOCKED, copyin32_drm_wait_vblank, copyout32_drm_wait_vblank),

	DRM_IOCTL_DEF(DRM_IOCTL_MODESET_CTL, drm_modeset_ctl, 0, NULL, NULL),

	DRM_IOCTL_DEF(DRM_IOCTL_UPDATE_DRAW, drm_noop, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),

	DRM_IOCTL_DEF(DRM_IOCTL_GEM_CLOSE, drm_gem_close_ioctl, DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_GEM_FLINK, drm_gem_flink_ioctl, DRM_AUTH|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_GEM_OPEN, drm_gem_open_ioctl, DRM_AUTH|DRM_UNLOCKED, NULL, NULL),

	DRM_IOCTL_DEF(DRM_IOCTL_MODE_GETRESOURCES, drm_mode_getresources, DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),

	DRM_IOCTL_DEF(DRM_IOCTL_MODE_GETPLANERESOURCES, drm_mode_getplane_res, DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_GETCRTC, drm_mode_getcrtc, DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_SETCRTC, drm_mode_setcrtc, DRM_MASTER|DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_GETPLANE, drm_mode_getplane, DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_SETPLANE, drm_mode_setplane, DRM_MASTER|DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_CURSOR, drm_mode_cursor_ioctl, DRM_MASTER|DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_GETGAMMA, drm_mode_gamma_get_ioctl, DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_SETGAMMA, drm_mode_gamma_set_ioctl, DRM_MASTER|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_GETENCODER, drm_mode_getencoder, DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_GETCONNECTOR, drm_mode_getconnector, DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_ATTACHMODE, drm_noop, DRM_MASTER|DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_DETACHMODE, drm_noop, DRM_MASTER|DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_GETPROPERTY, drm_mode_getproperty_ioctl, DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_SETPROPERTY, drm_mode_connector_property_set_ioctl, DRM_MASTER|DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_GETPROPBLOB, drm_mode_getblob_ioctl, DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_GETFB, drm_mode_getfb, DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_ADDFB, drm_mode_addfb, DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_ADDFB2, drm_mode_addfb2, DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_RMFB, drm_mode_rmfb, DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_PAGE_FLIP, drm_mode_page_flip_ioctl, DRM_MASTER|DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_DIRTYFB, drm_mode_dirtyfb_ioctl, DRM_MASTER|DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_CREATE_DUMB, drm_mode_create_dumb_ioctl, DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_MAP_DUMB, drm_mode_mmap_dumb_ioctl, DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_DESTROY_DUMB, drm_mode_destroy_dumb_ioctl, DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_OBJ_GETPROPERTIES, drm_mode_obj_get_properties_ioctl, DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_OBJ_SETPROPERTY, drm_mode_obj_set_property_ioctl, DRM_MASTER|DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	DRM_IOCTL_DEF(DRM_IOCTL_MODE_CURSOR2, drm_mode_cursor2_ioctl, DRM_MASTER|DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL)
};

#define DRM_CORE_IOCTL_COUNT	ARRAY_SIZE( drm_ioctls )

/**
 * Take down the DRM device.
 *
 * \param dev DRM device structure.
 *
 * Frees every resource in \p dev.
 *
 * \sa drm_device
 */
int drm_lastclose(struct drm_device * dev)
{
	DRM_DEBUG("\n");

	if (dev->driver->lastclose)
		dev->driver->lastclose(dev);
	DRM_DEBUG("driver lastclose completed\n");

	if (dev->irq_enabled && !drm_core_check_feature(dev, DRIVER_MODESET))
		(void) drm_irq_uninstall(dev);

	mutex_lock(&dev->struct_mutex);

	/* Clear AGP information */
	if (drm_core_has_AGP(dev) && dev->agp &&
			!drm_core_check_feature(dev, DRIVER_MODESET)) {
		struct drm_agp_mem *entry, *tempe;

		/* Remove AGP resources, but leave dev->agp
		   intact until drv_cleanup is called. */
		list_for_each_entry_safe(entry, tempe, struct drm_agp_mem, &dev->agp->memory, head) {
			if (entry->bound)
				(void) drm_agp_unbind_memory(entry->handle, dev);
			kfree(entry, sizeof (*entry));
		}
		INIT_LIST_HEAD(&dev->agp->memory);

		if (dev->agp->acquired)
			(void) drm_agp_release(dev);

		dev->agp->acquired = 0;
		dev->agp->enabled = 0;
	}
	if (drm_core_check_feature(dev, DRIVER_SG) && dev->sg &&
	    !drm_core_check_feature(dev, DRIVER_MODESET)) {
		drm_sg_cleanup(dev->sg);
		dev->sg = NULL;
	}

	if (drm_core_check_feature(dev, DRIVER_HAVE_DMA) &&
	    !drm_core_check_feature(dev, DRIVER_MODESET))
		drm_dma_takedown(dev);

	mutex_unlock(&dev->struct_mutex);

	DRM_DEBUG("lastclose completed\n");
	return 0;
}

/**
 * Module initialization. Called via init_module at module load time, or via
 * linux/init/main.c (this is not currently supported).
 *
 * \return zero on success or a negative number on failure.
 *
 * Initializes an array of drm_device structures, and attempts to
 * initialize all available devices, using consecutive minors, registering the
 * stubs and initializing the AGP device.
 *
 * Expands the \c DRIVER_PREINIT and \c DRIVER_POST_INIT macros before and
 * after the initialization for driver customization.
 */
int drm_init(struct drm_device *dev, struct drm_driver *driver)
{
	dev_info_t *dip = dev->devinfo;
	struct pci_dev *pdev = NULL;
	struct dev_ops *devop;
	int ret, i;

	DRM_DEBUG("\n");

	pdev = pci_dev_create(dev);
	if (!pdev)
		return -EFAULT;

	for (i = 0; driver->id_table[i].vendor != 0; i++) {
		if ((driver->id_table[i].vendor == pdev->vendor) &&
		    (driver->id_table[i].device == pdev->device)) {
		        ret = drm_get_dev(dev, pdev, driver, driver->id_table[i].driver_data);
			if (ret) {
				pci_dev_destroy(pdev);
				return ret;
			}

			/*
			 * DRM drivers are required to use common cb_ops
			 */
			devop = ddi_get_driver(dev->devinfo);
			if (devop->devo_cb_ops != &drm_cb_ops) {
				devop->devo_cb_ops = &drm_cb_ops;
			}
			/*
			 * Initialize for fma support
			 */
			dev->drm_fm_cap = ddi_prop_get_int(DDI_DEV_T_ANY, dip,
			    DDI_PROP_DONTPASS, "fm-capable",
			    DDI_FM_EREPORT_CAPABLE | DDI_FM_DMACHK_CAPABLE |
			    DDI_FM_ACCCHK_CAPABLE | DDI_FM_ERRCB_CAPABLE);

			drm_fm_init(dev);
			return 0;
		}
	}

	pci_dev_destroy(pdev);
	return -ENODEV;
}

void drm_exit(struct drm_device *dev)
{
	drm_put_dev(dev);
	pci_dev_destroy(dev->pdev);
	drm_fm_fini(dev);
}

int __init drm_core_init(void)
{
	INIT_LIST_HEAD(&drm_iomem_list);

	idr_init(&drm_minors_idr);

	DRM_INFO("Initialized %s %d.%d.%d %s\n",
		 CORE_NAME, CORE_MAJOR, CORE_MINOR, CORE_PATCHLEVEL, CORE_DATE);
	return 0;
}

void __exit drm_core_exit(void)
{
	idr_remove_all(&drm_minors_idr);
	idr_destroy(&drm_minors_idr);
}

/**
 * Copy and IOCTL return string to user space
 */
static int drm_copy_field(char *buf, size_t *buf_len, const char *value)
{
	int len;

	/* don't overflow userbuf */
	len = strlen(value);
	if (len > *buf_len)
		len = *buf_len;

	/* let userspace know exact length of driver value (which could be
	 * larger than the userspace-supplied buffer) */
	*buf_len = strlen(value);

	/* finally, try filling in the userbuf */
	if (len && buf)
		if (copy_to_user(buf, value, len))
			return -EFAULT;
	return 0;
}

/**
 * Get version information
 *
 * \return zero on success or negative number on failure.
 *
 * Fills in the version information in \p arg.
 */
/* LINTED */
static int drm_version(DRM_IOCTL_ARGS)
{
	struct drm_version *version = data;
	int err;

	version->version_major = dev->driver->major;
	version->version_minor = dev->driver->minor;
	version->version_patchlevel = dev->driver->patchlevel;
	err = drm_copy_field(version->name, &version->name_len,
			dev->driver->name);
	if (!err)
		err = drm_copy_field(version->date, &version->date_len,
				dev->driver->date);
	if (!err)
		err = drm_copy_field(version->desc, &version->desc_len,
				dev->driver->desc);

	return err;
}

/**
 * Called whenever a process performs an ioctl on /dev/drm.
 *
 * \return zero on success or negative number on failure.
 *
 * Looks up the ioctl function in the ::ioctls table, checking for root
 * previleges if so required, and dispatches to the respective function.
 */
int drm_ioctl(dev_t dev_id, struct drm_file *file_priv,
	int cmd, intptr_t arg, int mode, cred_t *credp)
{
	struct drm_device *dev = file_priv->minor->dev;
	struct drm_ioctl_desc *ioctl;
	drm_ioctl_t *func;
	unsigned int nr = DRM_IOCTL_NR(cmd);
	int retcode = -EINVAL;
	char stack_kdata[128];
	char *kdata = NULL;
	unsigned int usize, asize;

	atomic_inc(&dev->ioctl_count);
	atomic_inc(&dev->counts[_DRM_STAT_IOCTLS]);
	++file_priv->ioctl_count;

	if ((nr >= DRM_CORE_IOCTL_COUNT) &&
	    ((nr < DRM_COMMAND_BASE) || (nr >= DRM_COMMAND_END)))
		goto err_i1;
	if ((nr >= DRM_COMMAND_BASE) && (nr < DRM_COMMAND_END) &&
	    (nr < DRM_COMMAND_BASE + dev->driver->num_ioctls)) {
		ioctl = &dev->driver->ioctls[nr - DRM_COMMAND_BASE];
		usize = asize = _IOC_SIZE(cmd);
		cmd = ioctl->cmd;
	}
	else if ((nr >= DRM_COMMAND_END) || (nr < DRM_COMMAND_BASE)) {
		ioctl = &drm_ioctls[nr];
		cmd = ioctl->cmd;
		usize = asize = _IOC_SIZE(cmd);
	} else
		goto err_i1;

	/* Do not trust userspace, use our own definition */
	func = ioctl->func;
	/* is there a local override? */
	if ((nr == DRM_IOCTL_NR(DRM_IOCTL_DMA)) && dev->driver->dma_ioctl)
		func = dev->driver->dma_ioctl;

	if (!func) {
		DRM_DEBUG("no function\n");
		retcode = -EINVAL;
	} else if (((ioctl->flags & DRM_ROOT_ONLY) && !DRM_SUSER(credp)) ||
		   ((ioctl->flags & DRM_AUTH) && !file_priv->authenticated) ||
		   ((ioctl->flags & DRM_MASTER) && !file_priv->is_master) ||
		   (!(ioctl->flags & DRM_CONTROL_ALLOW) && (file_priv->minor->type == DRM_MINOR_CONTROL))) {
		retcode = -EACCES;
	} else {
		if (cmd & (IOC_IN | IOC_OUT)) {
			if (asize <= sizeof(stack_kdata)) {
				kdata = stack_kdata;
			} else {
				kdata = kmalloc(asize, GFP_KERNEL);
				if (!kdata) {
					retcode = -ENOMEM;
					goto err_i1;
				}
			}
			if (asize > usize)
				(void) memset(kdata + usize, 0, asize - usize);
		}

		if (cmd & IOC_IN) {
#ifdef	_MULTI_DATAMODEL
			if (ddi_model_convert_from(mode & FMODELS) == DDI_MODEL_ILP32 && ioctl->copyin32) {
				if (ioctl->copyin32((void*)kdata, (void*)arg)) {
					retcode = -EFAULT;
					goto err_i1;
				}
			} else {
#endif
			if (DRM_COPY_FROM_USER(kdata, (void __user *)arg,
					   _IOC_SIZE(cmd)) != 0) {
				retcode = -EFAULT;
				goto err_i1;
			}
#ifdef	_MULTI_DATAMODEL
			}
#endif
		}
		retcode = func(dev_id, dev, kdata, file_priv, mode, credp);

		if (cmd & IOC_OUT) {
#ifdef	_MULTI_DATAMODEL
			if (ddi_model_convert_from(mode & FMODELS) == DDI_MODEL_ILP32 && ioctl->copyout32) {
				if (ioctl->copyout32((void*)arg, (void*)kdata)) {
					retcode = -EFAULT;
					goto err_i1;
				}
			} else {
#endif
			if (DRM_COPY_TO_USER((void __user *)arg, kdata,
					 _IOC_SIZE(cmd)) != 0)
				retcode = -EFAULT;
#ifdef	_MULTI_DATAMODEL
			}
#endif
		}
	}

err_i1:
	if (kdata && (kdata != stack_kdata))
		kfree(kdata, asize);
	atomic_dec(&dev->ioctl_count);
	if (retcode)
		DRM_DEBUG("ret = %d\n", -retcode);
	return retcode;
}

struct drm_local_map *drm_getsarea(struct drm_device *dev)
{
	struct drm_map_list *entry;

	list_for_each_entry(entry, struct drm_map_list, &dev->maplist, head) {
		if (entry->map && entry->map->type == _DRM_SHM &&
		    (entry->map->flags & _DRM_CONTAINS_LOCK)) {
			return entry->map;
		}
	}
	return NULL;
}

void
drm_gem_object_reference(struct drm_gem_object *obj)
{
	kref_get(&obj->refcount);
}

void
drm_gem_object_unreference(struct drm_gem_object *obj)
{
	if (obj != NULL)
		kref_put(&obj->refcount, drm_gem_object_free);
}

void
drm_gem_object_unreference_unlocked(struct drm_gem_object *obj)
{
	if (obj != NULL) {
		struct drm_device *dev = obj->dev;
		mutex_lock(&dev->struct_mutex);
		kref_put(&obj->refcount, drm_gem_object_free);
		mutex_unlock(&dev->struct_mutex);
	}
}

void
drm_gem_object_handle_reference(struct drm_gem_object *obj)
{
	drm_gem_object_reference(obj);
	atomic_inc(&obj->handle_count);
}

void
drm_gem_object_handle_unreference(struct drm_gem_object *obj)
{
	if (obj == NULL)
		return;

	if (atomic_read(&obj->handle_count) == 0)
		return;
	/*
	 * Must bump handle count first as this may be the last
	 * ref, in which case the object would disappear before we
	 * checked for a name
	 */
	if (atomic_dec_and_test(&obj->handle_count))
		drm_gem_object_handle_free(obj);
	drm_gem_object_unreference(obj);
}

void
drm_gem_object_handle_unreference_unlocked(struct drm_gem_object *obj)
{
	if (obj == NULL)
		return;

	if (atomic_read(&obj->handle_count) == 0)
		return;

	/*
	* Must bump handle count first as this may be the last
	* ref, in which case the object would disappear before we
	* checked for a name
	*/

	if (atomic_dec_and_test(&obj->handle_count))
		drm_gem_object_handle_free(obj);
	drm_gem_object_unreference_unlocked(obj);
}


/*
 * PCI bus specific error callback
 */
/* ARGSUSED */
int
drm_fm_error_cb(
	dev_info_t	*dip,
	ddi_fm_error_t	*err,
	const void	*impl)
{

	pci_ereport_post(dip, err, NULL);

	return (err->fme_status);
}

void
drm_fm_init(struct drm_device *dev)
{
	dev_info_t *dip = dev->devinfo;
	if (dev->drm_fm_cap) {
		/* we do not care the iblk cookie */
		ddi_fm_init(dip, &dev->drm_fm_cap, NULL);

		/*
		 * Initialize pci ereport capabilities if ereport capable
		 */
		if (DDI_FM_EREPORT_CAP(dev->drm_fm_cap) ||
		    DDI_FM_ERRCB_CAP(dev->drm_fm_cap)) {
			pci_ereport_setup(dip);
		}

		/*
		 * Register error callback if error callback capable
		 */
		if (DDI_FM_ERRCB_CAP(dev->drm_fm_cap)) {
			ddi_fm_handler_register(dip,
			    drm_fm_error_cb, (void*) dev);
		}
	}
}

void
drm_fm_fini(struct drm_device *dev)
{
	dev_info_t *dip = dev->devinfo;
	if (dev->drm_fm_cap) {
		if (DDI_FM_EREPORT_CAP(dev->drm_fm_cap) ||
		    DDI_FM_ERRCB_CAP(dev->drm_fm_cap)) {
			pci_ereport_teardown(dip);
		}

		if (DDI_FM_ERRCB_CAP(dev->drm_fm_cap)) {
			ddi_fm_handler_unregister(dip);
		}

		ddi_fm_fini(dip);
	}
}

/*
 * report a device error.
 *   detail - DDI_FM_DEVICE_*
 */
void
drm_fm_ereport(
	struct drm_device	*dev,
	char		*detail)
{
	uint64_t ena;
	char buf[FM_MAX_CLASS];
	dev_info_t *dip = dev->devinfo;

	if (DDI_FM_EREPORT_CAP(dev->drm_fm_cap)) {

		(void) snprintf(buf, FM_MAX_CLASS, "%s.%s", DDI_FM_DEVICE,
		    detail);

		ena = fm_ena_generate(0, FM_ENA_FMT1);

		ddi_fm_ereport_post(dip, buf, ena, DDI_NOSLEEP,
		    FM_VERSION, DATA_TYPE_UINT8, FM_EREPORT_VERS0, NULL);
	}
}

/*
 * Check PIO Access error, like register access.
 */
int
drm_check_acc_handle(
	struct drm_device	*dev,
	ddi_acc_handle_t	handle)
{
	ddi_fm_error_t de;

	if (!DDI_FM_ACC_ERR_CAP(dev->drm_fm_cap)) {

		return (DDI_FM_OK);

	}

	ddi_fm_acc_err_get(handle, &de, DDI_FME_VERSION);
	ddi_fm_acc_err_clear(handle, DDI_FME_VERSION);

	return (de.fme_status);

}

/*
 * Check DMA Access error.
 */
int
drm_check_dma_handle(
	struct drm_device	*dev,
	ddi_dma_handle_t	handle)
{
	ddi_fm_error_t de;

	if (!DDI_FM_DMA_ERR_CAP(dev->drm_fm_cap)) {

		return (DDI_FM_OK);

	}

	ddi_fm_dma_err_get(handle, &de, DDI_FME_VERSION);
	ddi_fm_dma_err_clear(handle, DDI_FME_VERSION);

	return (de.fme_status);

}
