/*
 * Copyright (c) 2006, 2012, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * Copyright (c) 2012 Intel Corporation.  All rights reserved.
 */

/**
 * \file drm_auth.c
 * IOCTLs for authentication
 *
 * \author Rickard E. (Rik) Faith <faith@valinux.com>
 * \author Gareth Hughes <gareth@valinux.com>
 */

/*
 * Created: Tue Feb  2 08:37:54 1999 by faith@valinux.com
 *
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.
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

/**
 * Generate a hash key from a magic.
 *
 * \param magic magic.
 * \return hash key.
 *
 * The key is the modulus of the hash table size, #DRM_HASH_SIZE, which must be
 * a power of 2.
 */
static int drm_hash_magic(drm_magic_t magic)
{
	return magic & (DRM_HASH_SIZE - 1);
}

/**
 * Find the file with the given magic number.
 *
 * \param dev DRM device.
 * \param magic magic number.
 *
 * Searches in drm_device::magiclist within all files with the same hash key
 * the one with matching magic number, while holding the drm_device::struct_mutex
 * lock.
 */
static struct drm_file *drm_find_file(struct drm_master *master, drm_magic_t magic)
{
	struct drm_file *retval = NULL;
	struct drm_magic_entry *pt;
	int hash = drm_hash_magic(magic);
	struct drm_device *dev = master->minor->dev;

	mutex_lock(&dev->struct_mutex);
	for (pt = master->magiclist[hash].head; pt; pt = pt->next) {
		if (pt->magic == magic) {
			retval = pt->priv;
			break;
		}
	}
	mutex_unlock(&dev->struct_mutex);
	return retval;
}

/**
 * Adds a magic number.
 *
 * \param dev DRM device.
 * \param priv file private data.
 * \param magic magic number.
 *
 * Creates a drm_magic_entry structure and appends to the linked list
 * associated the magic number hash key in drm_device::magiclist, while holding
 * the drm_device::struct_mutex lock.
 */
static int drm_add_magic(struct drm_master *master, struct drm_file *priv,
			 drm_magic_t magic)
{
	int hash;
	struct drm_magic_entry *entry;
	struct drm_device *dev = master->minor->dev;

	DRM_DEBUG("%d\n", magic);

	hash = drm_hash_magic(magic);
	entry = drm_alloc(sizeof(*entry), DRM_MEM_MAGIC);
	if (!entry)
		return -ENOMEM;
	(void) memset(entry, 0, sizeof(*entry));
	entry->magic = magic;
	entry->priv = priv;
	entry->next = NULL;

	mutex_lock(&dev->struct_mutex);
	if (master->magiclist[hash].tail) {
		master->magiclist[hash].tail->next = entry;
		master->magiclist[hash].tail = entry;
	} else {
		master->magiclist[hash].head = entry;
		master->magiclist[hash].tail = entry;
	}
	mutex_unlock(&dev->struct_mutex);

	return 0;
}

/**
 * Remove a magic number.
 *
 * \param dev DRM device.
 * \param magic magic number.
 *
 * Searches and unlinks the entry in drm_device::magiclist with the magic
 * number hash key, while holding the drm_device::struct_mutex lock.
 */
int drm_remove_magic(struct drm_master *master, drm_magic_t magic)
{
	struct drm_magic_entry *prev = NULL;
	struct drm_magic_entry *pt;
	int hash;
	struct drm_device *dev = master->minor->dev;

	DRM_DEBUG("%d\n", magic);
	hash = drm_hash_magic(magic);

	mutex_lock(&dev->struct_mutex);
	for (pt = master->magiclist[hash].head; pt; prev = pt, pt = pt->next) {
		if (pt->magic == magic) {
			if (master->magiclist[hash].head == pt) {
				master->magiclist[hash].head = pt->next;
			}
			if (master->magiclist[hash].tail == pt) {
				master->magiclist[hash].tail = prev;
			}
			if (prev) {
				prev->next = pt->next;
			}
			mutex_unlock(&dev->struct_mutex);
			drm_free(pt, sizeof (*pt), DRM_MEM_MAGIC);
			return 0;
		}
	}
	mutex_unlock(&dev->struct_mutex);

	return -EINVAL;
}

/**
 * Get a unique magic number (ioctl).
 *
 * \param inode device inode.
 * \param file_priv DRM file private.
 * \param cmd command.
 * \param arg pointer to a resulting drm_auth structure.
 * \return zero on success, or a negative number on failure.
 *
 * If there is a magic number in drm_file::magic then use it, otherwise
 * searches an unique non-zero magic number and add it associating it with \p
 * file_priv.
 * This ioctl needs protection by the drm_global_mutex, which protects
 * struct drm_file::magic and struct drm_magic_entry::priv.
 */
/* LINTED */
int drm_getmagic(DRM_IOCTL_ARGS)
{
	static drm_magic_t sequence = 0;
	struct drm_auth *auth = data;

	/* Find unique magic */
	if (file->magic) {
		auth->magic = file->magic;
	} else {
		do {
			int old = sequence;
			auth->magic = old + 1;
			if (!atomic_cmpset_int(&sequence, old, auth->magic))
				continue;
		} while (drm_find_file(file->master, auth->magic));
		file->magic = auth->magic;
		(void) drm_add_magic(file->master, file, auth->magic);
	}

	DRM_DEBUG("%u\n", auth->magic);

	return 0;
}

/**
 * Authenticate with a magic.
 *
 * \param inode device inode.
 * \param file_priv DRM file private.
 * \param cmd command.
 * \param arg pointer to a drm_auth structure.
 * \return zero if authentication successed, or a negative number otherwise.
 *
 * Checks if \p file_priv is associated with the magic number passed in \arg.
 * This ioctl needs protection by the drm_global_mutex, which protects
 * struct drm_file::magic and struct drm_magic_entry::priv.
 */
/* LINTED */
int drm_authmagic(DRM_IOCTL_ARGS)
{
	struct drm_auth *auth = data;
	struct drm_file *file_priv;

	DRM_DEBUG("%u\n", auth->magic);
	if ((file_priv = drm_find_file(file->master, auth->magic))) {
		file_priv->authenticated = 1;
		(void) drm_remove_magic(file->master, auth->magic);
		return 0;
	}
	return -EINVAL;
}
