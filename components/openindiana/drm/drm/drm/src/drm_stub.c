/*
 * Copyright (c) 2006, 2013, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * Copyright (c) 2012, 2013 Intel Corporation.  All rights reserved.
 */

/**
 * \file drm_stub.h
 * Stub support
 *
 * \author Rickard E. (Rik) Faith <faith@valinux.com>
 */

/*
 * Created: Fri Jan 19 10:48:35 2001 by faith@acm.org
 *
 * Copyright 2001 VA Linux Systems, Inc., Sunnyvale, California.
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
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "drmP.h"
#include "drm_core.h"
#include "drm_linux_list.h"

unsigned int drm_vblank_offdelay = 5000;    /* Default to 5000 msecs. */
unsigned int drm_timestamp_precision = 20;  /* Default to 20 usecs. */

struct idr drm_minors_idr;

static int drm_minor_get_id(struct drm_device *dev, int type)
{
	int new_id;
	int ret;
	int base, limit;

	switch (type) {
	case DRM_MINOR_LEGACY:
		base = DRM_MINOR_ID_BASE_LEGACY;
		limit = DRM_MINOR_ID_LIMIT_LEGACY;
		break;
	case DRM_MINOR_CONTROL:
		base = DRM_MINOR_ID_BASE_CONTROL;
		limit = DRM_MINOR_ID_LIMIT_CONTROL;
		break;
	case DRM_MINOR_RENDER:
		base = DRM_MINOR_ID_BASE_RENDER;
		limit = DRM_MINOR_ID_LIMIT_RENDER;
		break;
	case DRM_MINOR_VGATEXT:
		base = DRM_MINOR_ID_BASE_VGATEXT;
		limit = DRM_MINOR_ID_LIMIT_VGATEXT;
		break;
	case DRM_MINOR_AGPMASTER:
		base = DRM_MINOR_ID_BASE_AGPMASTER;
		limit = DRM_MINOR_ID_LIMIT_AGPMASTER;
		break;
	default:
		return -EINVAL;
	}

	mutex_lock(&dev->struct_mutex);
	ret = idr_get_new_above(&drm_minors_idr, NULL,
				base, &new_id);
	mutex_unlock(&dev->struct_mutex);

	if (ret) {
		return ret;
	}

	if (new_id > limit) {
		(void) idr_remove(&drm_minors_idr, new_id);
		return -EINVAL;
	}
	return new_id;
}

struct drm_master *drm_master_create(struct drm_minor *minor)
{
	struct drm_master *master;
	int i;

	master = kzalloc(sizeof(*master), GFP_KERNEL);
	if (!master)
		return NULL;

	kref_init(&master->refcount);
	mutex_init(&master->lock.lock_mutex, NULL, MUTEX_DRIVER, (void *)minor->dev->pdev->intr_block);
	cv_init(&master->lock.lock_cv, NULL, CV_DRIVER, NULL);

	for (i = 0; i < DRM_HASH_SIZE; i++) {
		master->magiclist[i].head = NULL;
		master->magiclist[i].tail = NULL;
	}

	master->minor = minor;

	list_add_tail(&master->head, &minor->master_list, (caddr_t)master);

	return master;
}

struct drm_master *drm_master_get(struct drm_master *master)
{
	kref_get(&master->refcount);
	return master;
}

void drm_master_destroy(struct kref *kref)
{
	struct drm_master *master = container_of(kref, struct drm_master, refcount);
	struct drm_magic_entry *pt, *next;
	struct drm_device *dev = master->minor->dev;
	struct drm_map_list *r_list, *list_temp;
	int i;

	list_del(&master->head);

	if (dev->driver->master_destroy)
		dev->driver->master_destroy(dev, master);

	list_for_each_entry_safe(r_list, list_temp, struct drm_map_list, &dev->maplist, head) {
		if (r_list->master == master) {
			(void) drm_rmmap_locked(dev, r_list->map);
			r_list = NULL;
		}
	}

	if (master->unique) {
		kfree(master->unique, master->unique_size);
		master->unique = NULL;
		master->unique_len = 0;

	}

	for (i = 0; i < DRM_HASH_SIZE; i++) {
		for (pt = master->magiclist[i].head; pt; pt = next) {
			next = pt->next;
			drm_free(pt, sizeof(*pt), DRM_MEM_MAGIC);
		}
		master->magiclist[i].head = master->magiclist[i].tail = NULL;
	}

	cv_destroy(&master->lock.lock_cv);
	mutex_destroy(&master->lock.lock_mutex);

	kfree(master, sizeof (struct drm_master));
}

void drm_master_put(struct drm_master **master)
{
	kref_put(&(*master)->refcount, drm_master_destroy);
	*master = NULL;
}

/* LINTED */
int drm_setmaster_ioctl(DRM_IOCTL_ARGS)
{
	int ret = 0;

	if (dev->driver->entervt)
		dev->driver->entervt(dev);

	if (file->is_master)
		return 0;

	if (file->minor->master && file->minor->master != file->master)
		return -EINVAL;

	if (!file->master)
		return -EINVAL;

	if (!file->minor->master &&
	    file->minor->master != file->master) {
		mutex_lock(&dev->struct_mutex);
		file->minor->master = drm_master_get(file->master);
		file->is_master = 1;
		if (dev->driver->master_set) {
			ret = dev->driver->master_set(dev, file, false);
			if (unlikely(ret != 0)) {
				file->is_master = 0;
				drm_master_put(&file->minor->master);
			}
		}
		mutex_unlock(&dev->struct_mutex);
	}

	return 0;
}

/* LINTED */
int drm_dropmaster_ioctl(DRM_IOCTL_ARGS)
{
	if (!file->is_master)
		return -EINVAL;

	if (!file->minor->master)
		return -EINVAL;

	if (dev->driver->leavevt)
		dev->driver->leavevt(dev);

	mutex_lock(&dev->struct_mutex);
	if (dev->driver->master_drop)
		dev->driver->master_drop(dev, file, false);
	drm_master_put(&file->minor->master);
	file->is_master = 0;
	mutex_unlock(&dev->struct_mutex);
	return 0;
}

static int drm_fill_in_dev(struct drm_device * dev, struct pci_dev *pdev,
			   struct drm_driver *driver)
{
	int retcode;

	INIT_LIST_HEAD(&dev->filelist);
	INIT_LIST_HEAD(&dev->ctxlist);
	INIT_LIST_HEAD(&dev->maplist);
	INIT_LIST_HEAD(&dev->vblank_event_list);
	INIT_LIST_HEAD(&dev->gem_objects_list);

	mutex_init(&dev->count_lock, NULL, MUTEX_DRIVER, (void *)pdev->intr_block);
	mutex_init(&dev->event_lock, NULL, MUTEX_DRIVER, (void *)pdev->intr_block);
	mutex_init(&dev->struct_mutex, NULL, MUTEX_DRIVER, NULL);	//adaptive locks
	mutex_init(&dev->ctxlist_mutex, NULL, MUTEX_DRIVER, NULL);
	mutex_init(&dev->irq_lock, NULL, MUTEX_DRIVER, (void *)pdev->intr_block);
	mutex_init(&dev->track_lock, NULL, MUTEX_DRIVER, (void *)pdev->intr_block);
	mutex_init(&dev->page_fault_lock, NULL, MUTEX_DRIVER, NULL);

	dev->pdev = pdev;
	dev->pci_device = pdev->device;
	dev->pci_vendor = pdev->vendor;

	idr_init(&dev->map_idr);

	/* the DRM has 6 basic counters */
	dev->counters = 6;
	dev->types[0] = _DRM_STAT_LOCK;
	dev->types[1] = _DRM_STAT_OPENS;
	dev->types[2] = _DRM_STAT_CLOSES;
	dev->types[3] = _DRM_STAT_IOCTLS;
	dev->types[4] = _DRM_STAT_LOCKS;
	dev->types[5] = _DRM_STAT_UNLOCKS;

	dev->driver = driver;

	retcode = drm_ctxbitmap_init(dev);
	if (retcode) {
		DRM_ERROR("Cannot allocate memory for context bitmap.\n");
		goto error_out_unreg;
	}

	if (driver->driver_features & DRIVER_GEM) {
		retcode = drm_gem_init(dev);
		if (retcode) {
			DRM_ERROR("Cannot initialize graphics execution "
				  "manager (GEM)\n");
			goto error_out_unreg;
		}
	}

	dev->drm_wq = create_workqueue(dev->devinfo, "drm");
	if (dev->drm_wq == NULL) {
		DRM_ERROR("Failed to create drm workqueue.\n");
		goto error_out_unreg;
	}

	return 0;

      error_out_unreg:
	(void)drm_lastclose(dev);
	return retcode;
}


/**
 * Get a secondary minor number.
 *
 * \param dev device data structure
 * \param sec-minor structure to hold the assigned minor
 * \return negative number on failure.
 *
 * Search an empty entry and initialize it to the given parameters, and
 * create the proc init entry via proc_init(). This routines assigns
 * minor numbers to secondary heads of multi-headed cards
 */
static int drm_get_minor(struct drm_device *dev, struct drm_minor **minor, int type)
{
	struct drm_minor *new_minor;
	int ret;
	int minor_id;

	DRM_DEBUG("\n");

	minor_id = drm_minor_get_id(dev, type);
	if (minor_id < 0)
		return minor_id;

	new_minor = kzalloc(sizeof(struct drm_minor), GFP_KERNEL);
	if (!new_minor) {
		ret = -ENOMEM;
		goto err_idr;
	}

	new_minor->type = type;
	new_minor->dev = dev;
	new_minor->index = minor_id;
	INIT_LIST_HEAD(&new_minor->master_list);

	(void) idr_replace(&drm_minors_idr, new_minor, minor_id);

	if (type == DRM_MINOR_LEGACY)
		(void) sprintf(new_minor->name, "drm%d", new_minor->index);
	else if (type == DRM_MINOR_CONTROL)
		(void) sprintf(new_minor->name, "controlD%d", new_minor->index);
	else if (type == DRM_MINOR_RENDER)
		(void) sprintf(new_minor->name, "renderD%d", new_minor->index);
	else if (type == DRM_MINOR_VGATEXT)
		(void) sprintf(new_minor->name, "gfx%d", new_minor->index - DRM_MINOR_ID_BASE_VGATEXT);
	else if (type == DRM_MINOR_AGPMASTER)
		(void) sprintf(new_minor->name, "agpmaster%d", new_minor->index - DRM_MINOR_ID_BASE_AGPMASTER);

	idr_init(&new_minor->clone_idr);

	ret = drm_sysfs_device_add(new_minor);
	if (ret)
		goto err_g2;
	*minor = new_minor;

	DRM_DEBUG("new minor assigned %d\n", minor_id);
	return 0;


err_g2:
err_mem:
	kfree(new_minor, sizeof (*new_minor));
err_idr:
	(void) idr_remove(&drm_minors_idr, minor_id);
	*minor = NULL;
	return ret;
}

/**
 * Register.
 *
 * \return zero on success or a negative number on failure.
 *
 * Attempt to gets inter module "drm" information. If we are first
 * then register the character device and inter module information.
 * Try and register, if we fail to register, backout previous work.
 */
int drm_get_dev(struct drm_device *dev, struct pci_dev *pdev,
		struct drm_driver *driver, unsigned long driver_data)
{
	int ret;

	DRM_DEBUG("\n");

	if ((ret = drm_fill_in_dev(dev, pdev, driver))) {
		DRM_ERROR("DRM: Fill_in_dev failed");
		goto err_g1;
	}

	if ((ret = drm_get_minor(dev, &dev->vgatext, DRM_MINOR_VGATEXT))) {
		goto err_g2;
	}

	if (dev->driver->agp_support_detect)
		dev->driver->agp_support_detect(dev, driver_data);

	if (drm_core_has_AGP(dev)) {
		if ((ret = drm_get_minor(dev, &dev->agpmaster, DRM_MINOR_AGPMASTER)))
			goto err_g1;
	}

	if (drm_core_check_feature(dev, DRIVER_MODESET)) {
		ret = drm_get_minor(dev, &dev->control, DRM_MINOR_CONTROL);
		if (ret)
			goto err_g3;
	}

	if ((ret = drm_get_minor(dev, &dev->primary, DRM_MINOR_LEGACY)))
		goto err_g4;

	if (dev->driver->load) {
		ret = dev->driver->load(dev, driver_data);
		if (ret)
			goto err_g5;
	}

	if (drm_init_kstats(dev)) {
		DRM_ERROR("init kstats error");
		ret = EFAULT;
		goto err_g5;
	}

	cmn_err(CE_CONT, "!Initialized %s v%d.%d.%d Modified date %s",
		 driver->name, driver->major, driver->minor, driver->patchlevel,
		 driver->date);

	return 0;

err_g5:
	(void) drm_put_minor(&dev->primary);
err_g4:
	if (drm_core_check_feature(dev, DRIVER_MODESET))
		(void) drm_put_minor(&dev->control);
err_g3:
	(void) drm_put_minor(&dev->vgatext);
err_g2:
	if (drm_core_has_AGP(dev))
		(void) drm_put_minor(&dev->agpmaster);
err_g1:
	return ret;
}

/**
 * Put a secondary minor number.
 *
 * \param sec_minor - structure to be released
 * \return always zero
 *
 * Cleans up the proc resources. Not legal for this to be the
 * last minor released.
 *
 */
int drm_put_minor(struct drm_minor **minor_p)
{
	struct drm_minor *minor = *minor_p;

	DRM_DEBUG("release secondary minor %d\n", minor->index);

	drm_sysfs_device_remove(minor);

	(void) idr_remove(&drm_minors_idr, minor->index);

	idr_destroy(&minor->clone_idr);

	kfree(minor, sizeof (*minor));
	*minor_p = NULL;
	return 0;
}

/**
 * Called via drm_exit() at module unload time or when pci device is
 * unplugged.
 *
 * Cleans up all DRM device, calling drm_lastclose().
 *
 * \sa drm_init
 */
void drm_put_dev(struct drm_device *dev)
{
	struct drm_driver *driver;
	struct drm_map_list *r_list, *list_temp;

	DRM_DEBUG("\n");

	if (!dev) {
		DRM_ERROR("cleanup called no dev\n");
		return;
	}
	driver = dev->driver;

	(void) drm_lastclose(dev);

	(void) destroy_workqueue(dev->drm_wq);

	if (dev->driver->unload)
		dev->driver->unload(dev);

	// gfxp_mempool_destroy();

	if (drm_core_has_AGP(dev) && dev->agp) {
		drm_agp_cleanup(dev);
		kfree(dev->agp, sizeof(*dev->agp));
		dev->agp = NULL;
	}

	drm_vblank_cleanup(dev);

	list_for_each_entry_safe(r_list, list_temp, struct drm_map_list, &dev->maplist, head)
		(void) drm_rmmap(dev, r_list->map);
	idr_destroy(&dev->map_idr);

	drm_ctxbitmap_cleanup(dev);

	(void) drm_put_minor(&dev->vgatext);

	if (drm_core_has_AGP(dev))
		(void) drm_put_minor(&dev->agpmaster);

	if (drm_core_check_feature(dev, DRIVER_MODESET))
		(void) drm_put_minor(&dev->control);

	if (driver->driver_features & DRIVER_GEM)
		drm_gem_destroy(dev);

	(void) drm_put_minor(&dev->primary);

	mutex_destroy(&dev->irq_lock);
	mutex_destroy(&dev->ctxlist_mutex);
	mutex_destroy(&dev->struct_mutex);
	mutex_destroy(&dev->event_lock);
	mutex_destroy(&dev->count_lock);

	drm_fini_kstats(dev);
}
