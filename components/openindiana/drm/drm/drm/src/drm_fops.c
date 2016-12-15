/*
 * Copyright (c) 2006, 2013, Oracle and/or its affiliates. All rights reserved.
 */

/**
 * \file drm_fops.c
 * File operations for DRM
 *
 * \author Rickard E. (Rik) Faith <faith@valinux.com>
 * \author Daryll Strauss <daryll@valinux.com>
 * \author Gareth Hughes <gareth@valinux.com>
 */

/*
 * Created: Mon Jan  4 08:58:31 1999 by faith@valinux.com
 *
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
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
 */

#include "drmP.h"

static int drm_open_helper(struct drm_minor *minor,
			int clone_id, int flags, cred_t *credp);

static __inline__ int drm_device_is_agp(struct drm_device *dev)
{
	if (drm_core_check_feature(dev, DRIVER_USE_PLATFORM_DEVICE))
		return 0;
	if (dev->driver->device_is_agp != NULL) {
		int err = (*dev->driver->device_is_agp) (dev);

		if (err != 2) {
			return err;
		}
	}

	return pci_find_capability(dev->pdev, PCI_CAP_ID_AGP);
}

static int drm_setup(struct drm_device * dev)
{
	int i;
	int ret;
	static bool first_call = true;

	if (first_call) {
		/* OSOL_drm: moved from drm_fill_in_dev */
		if (drm_core_has_AGP(dev)) {
			if (drm_device_is_agp(dev))
				dev->agp = drm_agp_init(dev);
			if (drm_core_check_feature(dev, DRIVER_REQUIRE_AGP)
			    && (dev->agp == NULL)) {
				DRM_ERROR("Cannot initialize the agpgart module.\n");
				return -EINVAL;
			}
		}
	}

	if (dev->driver->firstopen) {
		ret = dev->driver->firstopen(dev);
		if (ret != 0)
			return ret;
	}

	if (first_call) {
		/* OSOL_drm: moved from drm_get_dev */
		/* setup the grouping for the legacy output */
		if (drm_core_check_feature(dev, DRIVER_MODESET)) {
			ret = drm_mode_group_init_legacy_group(dev, &dev->primary->mode_group);
			if (ret)
				return ret;
		}
	}

	atomic_set(&dev->ioctl_count, 0);

	if (drm_core_check_feature(dev, DRIVER_HAVE_DMA) &&
	    !drm_core_check_feature(dev, DRIVER_MODESET)) {
		dev->buf_use = 0;
		atomic_set(&dev->buf_alloc, 0);

		i = drm_dma_setup(dev);
		if (i < 0)
			return i;
	}

	for (i = 0; i < DRM_ARRAY_SIZE(dev->counts); i++)
		atomic_set(&dev->counts[i], 0);

	dev->context_flag = 0;
	dev->last_context = 0;
	dev->if_version = 0;


	DRM_DEBUG("\n");

	/*
	 * The kernel's context could be created here, but is now created
	 * in drm_dma_enqueue.  This is more resource-efficient for
	 * hardware that does not do DMA, but may mean that
	 * drm_select_queue fails between the time the interrupt is
	 * initialized and the time the queues are initialized.
	 */

	first_call = false;
	return 0;
}

/**
 * Open file.
 *
 * \return zero on success or a negative number on failure.
 *
 * Searches the DRM device with the same minor number, calls open_helper(), and
 * increments the device open count. If the open count was previous at zero,
 * i.e., it's the first that the device is open, then calls setup().
 */
int drm_open(struct drm_minor *minor, int clone_id, int flags, cred_t *credp)
{
	struct drm_device *dev = minor->dev;
	int retcode = 0;

	DRM_DEBUG("minor->index=%d, clone_id=%d", minor->index, clone_id);

	retcode = drm_open_helper(minor, clone_id, flags, credp);
	if (!retcode) {
		atomic_inc(&dev->counts[_DRM_STAT_OPENS]);
		spin_lock(&dev->count_lock);
		if (!dev->open_count++) {
			spin_unlock(&dev->count_lock);
			retcode = drm_setup(dev);
			goto out;
		}
		spin_unlock(&dev->count_lock);
	}
out:
	return retcode;
}

/**
 * Called whenever a process opens /dev/drm.
 *
 * Creates and initializes a drm_file structure for the file private data in \p
 * filp and add it into the double linked list in \p dev.
 */
static int drm_open_helper(struct drm_minor *minor,
			int clone_id, int flags, cred_t *credp)
{
	struct drm_device *dev = minor->dev;
	struct drm_file *priv;
	int minor_id = minor->index;
	int ret;

	if (flags & FEXCL)
		return -EBUSY;	/* No exclusive opens */

	if (dev->switch_power_state != DRM_SWITCH_POWER_ON)
		return -EINVAL;

	DRM_DEBUG("pid = %d, minor = %d\n", ddi_get_pid(), minor_id);

	priv = kmalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	(void) memset(priv, 0, sizeof(*priv));
	(void) idr_replace(&minor->clone_idr, priv, clone_id);  /* OSOL_drm */
	priv->uid = crgetsuid(credp);
	priv->pid = ddi_get_pid();
	priv->minor = minor;
	priv->ioctl_count = 0;
	/* for compatibility root is always authenticated */
	priv->authenticated = DRM_SUSER(credp);
	priv->lock_count = 0;

	INIT_LIST_HEAD(&priv->lhead);
	INIT_LIST_HEAD(&priv->fbs);
	mutex_init(&priv->fbs_lock, NULL, MUTEX_DRIVER, NULL);
	INIT_LIST_HEAD(&priv->event_list);
	DRM_INIT_WAITQUEUE(&priv->event_wait, DRM_INTR_PRI(dev));
	priv->event_space = 4096; /* set aside 4k for event buffer */

	if (dev->driver->driver_features & DRIVER_GEM)
		drm_gem_open(dev, priv);

	if (dev->driver->open) {
		ret = dev->driver->open(dev, priv);
		if (ret < 0)
			goto out_free;
	}


	/* if there is no current master make this fd it */
	mutex_lock(&dev->struct_mutex);
	if (!priv->minor->master) {
		/* create a new master */
		priv->minor->master = drm_master_create(priv->minor);
		if (!priv->minor->master) {
			mutex_unlock(&dev->struct_mutex);
			ret = -ENOMEM;
			goto out_free;
		}

		priv->is_master = 1;
		/* take another reference for the copy in the local file priv */
		priv->master = drm_master_get(priv->minor->master);

		priv->authenticated = 1;

		mutex_unlock(&dev->struct_mutex);
		if (dev->driver->master_create) {
			ret = dev->driver->master_create(dev, priv->master);
			if (ret) {
				mutex_lock(&dev->struct_mutex);
				/* drop both references if this fails */
				drm_master_put(&priv->minor->master);
				drm_master_put(&priv->master);
				mutex_unlock(&dev->struct_mutex);
				goto out_free;
			}
		}
		mutex_lock(&dev->struct_mutex);
		if (dev->driver->master_set) {
			ret = dev->driver->master_set(dev, priv, true);
			if (ret) {
				/* drop both references if this fails */
				drm_master_put(&priv->minor->master);
				drm_master_put(&priv->master);
				mutex_unlock(&dev->struct_mutex);
				goto out_free;
			}
		}
		mutex_unlock(&dev->struct_mutex);
	} else {
		/* get a reference to the master */
		priv->master = drm_master_get(priv->minor->master);
		mutex_unlock(&dev->struct_mutex);
	}

	mutex_lock(&dev->struct_mutex);
	list_add(&priv->lhead, &dev->filelist, (caddr_t)priv);
	mutex_unlock(&dev->struct_mutex);

	return 0;
out_free:
	kfree(priv, sizeof (*priv));
	return ret;
}

void drm_master_release(struct drm_device *dev, struct drm_file *fpriv)
{
	struct drm_master *master = fpriv->master;

	if (drm_i_have_hw_lock(dev, fpriv)) {
		DRM_DEBUG("Process %d dead, freeing lock for context %d",
		    DRM_CURRENTPID,  _DRM_LOCKING_CONTEXT(master->lock.hw_lock->lock));
		(void) drm_lock_free(&master->lock,
		    _DRM_LOCKING_CONTEXT(master->lock.hw_lock->lock));
	}

}

static void drm_events_release(struct drm_file *file_priv)
{
	struct drm_device *dev = file_priv->minor->dev;
	struct drm_pending_event *e, *et;
	struct drm_pending_vblank_event *v, *vt;
	unsigned long flags;

	spin_lock_irqsave(&dev->event_lock, flags);

	/* Remove pending flips */
	list_for_each_entry_safe(v, vt, struct drm_pending_vblank_event, &dev->vblank_event_list, base.link)
	if (v->base.file_priv == file_priv) {
		list_del(&v->base.link);
		drm_vblank_put(dev, v->pipe);
		v->base.destroy(&v->base, sizeof(struct drm_pending_vblank_event));
	}

	/* Remove unconsumed events */
	list_for_each_entry_safe(e, et, struct drm_pending_event, &file_priv->event_list, link)
		e->destroy(e,  sizeof(struct drm_pending_vblank_event));

	spin_unlock_irqrestore(&dev->event_lock, flags);
}

/**
 * Release file.
 *
 * \return zero on success or a negative number on failure.
 *
 * If the hardware lock is held then free it, and take it again for the kernel
 * context since it's necessary to reclaim buffers. Unlink the file private
 * data from its list and free it. Decreases the open count and if it reaches
 * zero calls drm_lastclose().
 */
int
drm_release(struct drm_file *file_priv)
{
	struct drm_device *dev = file_priv->minor->dev;
	int retcode = 0;



	DRM_DEBUG("open_count = %d\n", dev->open_count);

	if (dev->driver->preclose)
		dev->driver->preclose(dev, file_priv);

	/* ========================================================
	 * Begin inline drm_release
	 */

	/* Release any auth tokens that might point to this file_priv,
	   (do that under the drm_global_mutex) */
	if (file_priv->magic)
		(void) drm_remove_magic(file_priv->master, file_priv->magic);

	/* if the master has gone away we can't do anything with the lock */
	if (file_priv->minor->master)
		drm_master_release(dev, file_priv);

	if (drm_core_check_feature(dev, DRIVER_HAVE_DMA))
		drm_core_reclaim_buffers(dev, file_priv);

	drm_events_release(file_priv);

	if (dev->driver->driver_features & DRIVER_MODESET)
		drm_fb_release(file_priv);

	if (dev->driver->driver_features & DRIVER_GEM)
		drm_gem_release(dev, file_priv);

	mutex_lock(&dev->ctxlist_mutex);
	if (!list_empty(&dev->ctxlist)) {
		struct drm_ctx_list *pos, *n;

		list_for_each_entry_safe(pos, n, struct drm_ctx_list, &dev->ctxlist, head) {
			if (pos->tag == file_priv &&
			    pos->handle != DRM_KERNEL_CONTEXT) {
				if (dev->driver->context_dtor)
					dev->driver->context_dtor(dev,
								  pos->handle);

				drm_ctxbitmap_free(dev, pos->handle);

				list_del(&pos->head);
				kfree(pos, sizeof (*pos));
				--dev->ctx_count;
			}
		}
	}
	mutex_unlock(&dev->ctxlist_mutex);

	mutex_lock(&dev->struct_mutex);

	if (file_priv->is_master) {
		struct drm_master *master = file_priv->master;
		struct drm_file *temp;
		list_for_each_entry(temp, struct drm_file, &dev->filelist, lhead) {
			if ((temp->master == file_priv->master) &&
			    (temp != file_priv))
				temp->authenticated = 0;
		}

		/**
		 * Since the master is disappearing, so is the
		 * possibility to lock.
		 */

		if (master->lock.hw_lock) {
			master->lock.hw_lock = NULL;
			master->lock.file_priv = NULL;
		}

		if (file_priv->minor->master == file_priv->master) {
			/* drop the reference held my the minor */
			if (dev->driver->master_drop)
				dev->driver->master_drop(dev, file_priv, true);
			drm_master_put(&file_priv->minor->master);
		}
	}

	/* drop the reference held my the file priv */
	drm_master_put(&file_priv->master);
	file_priv->is_master = 0;
	list_del(&file_priv->lhead);
	mutex_unlock(&dev->struct_mutex);

	if (dev->driver->postclose)
		dev->driver->postclose(dev, file_priv);
	kfree(file_priv, sizeof (*file_priv));

	/* ========================================================
	 * End inline drm_release
	 */

	atomic_inc(&dev->counts[_DRM_STAT_CLOSES]);
	spin_lock(&dev->count_lock);
	if (!--dev->open_count) {
		if (atomic_read(&dev->ioctl_count)) {
			DRM_ERROR("Device busy: %d\n",
				  atomic_read(&dev->ioctl_count));
			spin_unlock(&dev->count_lock);
			return -EBUSY;
		}
		spin_unlock(&dev->count_lock);
		return drm_lastclose(dev);
	}
	spin_unlock(&dev->count_lock);

	return retcode;
}

static bool
drm_dequeue_event(struct drm_file *file_priv,
	size_t total, size_t max, struct drm_pending_event **out)
{
	struct drm_device *dev = file_priv->minor->dev;
	struct drm_pending_event *e;
	unsigned long flags;
	bool ret = false;

	spin_lock_irqsave(&dev->event_lock, flags);

	*out = NULL;
	if (list_empty(&file_priv->event_list))
		goto out;
	e = list_first_entry(&file_priv->event_list,
	struct drm_pending_event, link);
	if (e->event->length + total > max)
		goto out;

	file_priv->event_space += e->event->length;
	list_del(&e->link);
	*out = e;
	ret = true;

out:
	spin_unlock_irqrestore(&dev->event_lock, flags);
	return ret;
}

ssize_t drm_read(struct drm_file *file_priv, struct uio *uiop)
{
	struct drm_pending_event *e;
	size_t total;
	int ret = 0;

	DRM_WAIT(ret, &file_priv->event_wait,
		!list_empty(&file_priv->event_list));
	if (ret < 0) {
		DRM_ERROR("returns %d event_list is %d", ret, list_empty(&file_priv->event_list));
		return ret;
	}

	total = 0;
	while (drm_dequeue_event(file_priv, total, uiop->uio_iov->iov_len, &e)) {
		ret = uiomove((caddr_t)e->event, e->event->length, UIO_READ, uiop);
		if (ret) {
			DRM_ERROR("Failed to copy to user: %d", ret);
			return (0);
		}
		total += e->event->length;
		e->destroy(e, sizeof(struct drm_pending_vblank_event));
	}

	return total;
}

short drm_poll(struct drm_file *file_priv, short events)
{
	short revent = 0;

	if (!list_empty(&file_priv->event_list)) {
		if (events & POLLIN)
			revent |= POLLIN;
		if (events & POLLRDNORM)
			revent |= POLLRDNORM;
	}

	return revent;
}
