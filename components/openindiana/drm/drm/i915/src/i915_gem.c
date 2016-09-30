/*
 * Copyright (c) 2006, 2016, Oracle and/or its affiliates. All rights reserved.
 */

/*
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
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Eric Anholt <eric@anholt.net>
 *
 */

#include <sys/x86_archext.h>
#include <sys/vfs_opreg.h>
#include "drmP.h"
#include "drm.h"
#include "drm_mm.h"
#include "i915_drm.h"
#include "i915_drv.h"
#include "intel_drv.h"

static void i915_gem_object_flush_gtt_write_domain(struct drm_i915_gem_object *obj);
static void i915_gem_object_flush_cpu_write_domain(struct drm_i915_gem_object *obj);
static int i915_gem_object_bind_to_gtt(struct drm_i915_gem_object *obj,
						    unsigned alignment,
						    bool map_and_fenceable,
						    bool nonblocking);
static int i915_gem_phys_pwrite(struct drm_device *dev,
				struct drm_i915_gem_object *obj,
				struct drm_i915_gem_pwrite *args,
				struct drm_file *file);
static void i915_gem_write_fence(struct drm_device *dev, int reg,
				 struct drm_i915_gem_object *obj);
static void i915_gem_object_update_fence(struct drm_i915_gem_object *obj,
					 struct drm_i915_fence_reg *fence,
					 bool enable);

int i915_gem_object_get_pages(struct drm_i915_gem_object *obj);

static inline void i915_gem_object_fence_lost(struct drm_i915_gem_object *obj)
{
	if (obj->tiling_mode)
		i915_gem_release_mmap(obj);

	/* As we do not have an associated fence register, we will force
	 * a tiling change if we ever need to acquire one.
	 */
	obj->fence_dirty = false;
	obj->fence_reg = I915_FENCE_REG_NONE;
}

/* some bookkeeping */
static void i915_gem_info_add_obj(struct drm_i915_private *dev_priv,
				  size_t size)
{
	dev_priv->mm.object_count++;
	dev_priv->mm.object_memory += size;
}

static void i915_gem_info_remove_obj(struct drm_i915_private *dev_priv,
				     size_t size)
{
	dev_priv->mm.object_count--;
	dev_priv->mm.object_memory -= size;
}

static int
i915_gem_wait_for_error(struct i915_gpu_error *error)
{

#define EXIT_COND (!i915_reset_in_progress(error) || \
		   i915_terminally_wedged(error))
	if (EXIT_COND)
		return 0;

	/*
	 * Only wait 10 seconds for the gpu reset to complete to avoid hanging
	 * userspace. If it takes that long something really bad is going on and
	 * we should simply try to bail out and fail as gracefully as possible.
	 */
	if (wait_for(EXIT_COND, 10*1000)) {
		DRM_ERROR("Timed out waiting for the gpu reset to complete\n");
		return -EIO;
	}
#undef EXIT_COND

	return 0;
}

int
i915_mutex_lock_interruptible(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int ret;

	ret = i915_gem_wait_for_error(&dev_priv->gpu_error);
	if (ret)
		return ret;

	/* fix me mutex_lock_interruptible */
	mutex_lock(&dev->struct_mutex);

	WARN_ON(i915_verify_lists(dev));
	return 0;
}

static inline bool
i915_gem_object_is_inactive(struct drm_i915_gem_object *obj)
{
	return obj->gtt_space && !obj->active;
}

int
/* LINTED */
i915_gem_init_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_i915_gem_init *args = data;
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (drm_core_check_feature(dev, DRIVER_MODESET))
		return -ENODEV;

	if (args->gtt_start >= args->gtt_end ||
	    (args->gtt_end | args->gtt_start) & (PAGE_SIZE - 1))
		return -EINVAL;

	/* GEM with user mode setting was never supported on ilk and later. */
	if (INTEL_INFO(dev)->gen >= 5)
		return -ENODEV;

	mutex_lock(&dev->struct_mutex);
	i915_gem_setup_global_gtt(dev, args->gtt_start, args->gtt_end,
				  args->gtt_end);
	dev_priv->gtt.mappable_end = args->gtt_end;
	mutex_unlock(&dev->struct_mutex);

	return 0;
}

int
/* LINTED */
i915_gem_get_aperture_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_i915_gem_get_aperture *args = data;
	struct drm_i915_gem_object *obj;
	size_t pinned;

	pinned = 0;
	mutex_lock(&dev->struct_mutex);
	list_for_each_entry(obj, struct drm_i915_gem_object, &dev_priv->mm.bound_list, global_list)
		if (obj->pin_count)
			pinned += obj->gtt_space->size;
	mutex_unlock(&dev->struct_mutex);

	args->aper_size = dev_priv->gtt.total;
	args->aper_available_size = args->aper_size -pinned;

	return 0;
}

void *i915_gem_object_alloc(struct drm_device *dev)
{
	return NULL;
}

void i915_gem_object_free(struct drm_i915_gem_object *obj)
{
}

static int
i915_gem_create(struct drm_file *file,
		struct drm_device *dev,
		uint64_t size,
		uint32_t *handle_p)
{
	struct drm_i915_gem_object *obj;
	int ret;
	u32 handle;

	size = roundup(size, PAGE_SIZE);
	if (size == 0)
		return -EINVAL;

	/* Allocate the new object */
	obj = i915_gem_alloc_object(dev, size);
	if (obj == NULL)
		return -ENOMEM;

	ret = drm_gem_handle_create(file, &obj->base, &handle);
	if (ret) {
		drm_gem_object_release(&obj->base);
		i915_gem_info_remove_obj(dev->dev_private, obj->base.size);
		i915_gem_object_free(obj);
		return ret;
	}

	/* drop reference from allocate - handle holds it now */
	drm_gem_object_unreference(&obj->base);

	*handle_p = handle;
	return 0;
}

int
i915_gem_dumb_create(struct drm_file *file,
		     struct drm_device *dev,
		     struct drm_mode_create_dumb *args)
{
	/* have to work out size/pitch and return them */
	args->pitch = ALIGN(args->width * ((args->bpp + 7) / 8), 64);
	args->size = args->pitch * args->height;
	return i915_gem_create(file, dev,
			       args->size, &args->handle);
}

int i915_gem_dumb_destroy(struct drm_file *file,
			  struct drm_device *dev,
			  uint32_t handle)
{
	return drm_gem_handle_delete(file, handle);
}
/**
 * Creates a new mm object and returns a handle to it.
 */
int
/* LINTED */
i915_gem_create_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_i915_gem_create *args = data;
	return i915_gem_create(file, dev,
			       args->size, &args->handle);
}

static inline void
slow_shmem_bit17_copy(caddr_t gpu_page,
		      int gpu_offset,
		      uint32_t *cpu_page,
		      int cpu_offset,
		      int length,
		      int is_read)
{

	int ret;
	/* Use the unswizzled path if this page isn't affected. */
	if ((page_to_phys(gpu_page) & (1 << 17)) == 0) {
		if (is_read)
			ret = DRM_COPY_TO_USER(cpu_page + cpu_offset,
					       gpu_page + gpu_offset, length);
		else
			ret = DRM_COPY_FROM_USER(gpu_page + gpu_offset,
					       cpu_page + cpu_offset, length);
		if (ret)
			DRM_ERROR("slow_shmem_bit17_copy unswizzled path failed, ret = %d", ret);
		return;
	}

	/* Copy the data, XORing A6 with A17 (1). The user already knows he's
	 * XORing with the other bits (A9 for Y, A9 and A10 for X)
	 */
	while (length > 0) {
		int cacheline_end = ALIGN(gpu_offset + 1, 64);
		int this_length = min(cacheline_end - gpu_offset, length);
		int swizzled_gpu_offset = gpu_offset ^ 64;

		if (is_read) {
			ret = DRM_COPY_TO_USER(cpu_page + cpu_offset,
			       gpu_page + swizzled_gpu_offset,
			       this_length);
		} else {
			ret = DRM_COPY_FROM_USER(gpu_page + swizzled_gpu_offset,
			       cpu_page + cpu_offset,
			       this_length);
		}
		cpu_offset += this_length;
		gpu_offset += this_length;
		length -= this_length;
	}
	if (ret)
		DRM_ERROR("slow_shmem_bit17_copy failed, ret = %d", ret);

}

int
/* LINTED */
i915_gem_shmem_pread(struct drm_device *dev,
		      struct drm_i915_gem_object *obj,
		      struct drm_i915_gem_pread *args,
		      struct drm_file *file_priv)
{
	ssize_t remain, page_length;
	uint32_t offset;
	uint64_t first_data_page;
	int shmem_page_index, shmem_page_offset;
	int data_page_index,  data_page_offset;
	int ret = 0;
	uint64_t data_ptr = args->data_ptr;
	int do_bit17_swizzling;
	int needs_clflush = 0;
	uint32_t *user_data = (uint32_t *)(uintptr_t)args->data_ptr;

	remain = args->size;

	do_bit17_swizzling = i915_gem_object_needs_bit17_swizzle(obj);

	if (!(obj->base.read_domains & I915_GEM_DOMAIN_CPU)) {
		/* If we're not in the cpu read domain, set ourself into the gtt
		 * read domain and manually flush cachelines (if required). This
		 * optimizes for the case when the gpu will dirty the data
		 * anyway again before the next pread happens. */
		if (obj->cache_level == I915_CACHE_NONE)
			needs_clflush = 1;
		if (obj->gtt_space) {
			ret = i915_gem_object_set_to_gtt_domain(obj, false);
			if (ret)
				return ret;
		}
	}

	ret = i915_gem_object_get_pages(obj);
	if (ret)
		return ret;

	i915_gem_object_pin_pages(obj);

	first_data_page = data_ptr / PAGE_SIZE;

	offset = args->offset;

	if (needs_clflush)
		i915_gem_clflush_object(obj);

	if (do_bit17_swizzling) {
		while (remain > 0) {
			/* Operation in this page
			 *
			 * shmem_page_index = page number within shmem file
			 * shmem_page_offset = offset within page in shmem file
			 * data_page_index = page number in get_user_pages return
			 * data_page_offset = offset with data_page_index page.
			 * page_length = bytes to copy for this page
			 */
			shmem_page_index = offset / DRM_PAGE_SIZE;
			shmem_page_offset = offset & ~DRM_PAGE_MASK;
			data_page_index = data_ptr / DRM_PAGE_SIZE - first_data_page;
			data_page_offset = data_ptr & ~DRM_PAGE_MASK;

			page_length = remain;
			if ((shmem_page_offset + page_length) > DRM_PAGE_SIZE)
				page_length = PAGE_SIZE - shmem_page_offset;
			if ((data_page_offset + page_length) > DRM_PAGE_SIZE)
				page_length = PAGE_SIZE - data_page_offset;

				slow_shmem_bit17_copy(obj->page_list[shmem_page_index],
						shmem_page_offset,
						user_data + data_page_index * DRM_PAGE_SIZE,
						data_page_offset,
						page_length,
						1);

			remain -= page_length;
			data_ptr += page_length;
			offset += page_length;
		}
	} else {
		ret = DRM_COPY_TO_USER((caddr_t)user_data,
					obj->base.kaddr + args->offset,
					args->size);
		if (ret)
			DRM_ERROR("shmem_pread_copy failed, ret = %d", ret);
	}
	i915_gem_object_unpin_pages(obj);
	return ret;
}

/**
 * Reads data from the object referenced by handle.
 *
 * On error, the contents of *data are undefined.
 */
int
/* LINTED */
i915_gem_pread_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_i915_gem_pread *args = data;
	struct drm_i915_gem_object *obj;
	int ret = 0;

	if (args->size == 0)
		return 0;

	ret = i915_mutex_lock_interruptible(dev);
	if (ret)
		return ret;

	obj = to_intel_bo(drm_gem_object_lookup(dev, file, args->handle));
	if (&obj->base == NULL) {
		ret = -ENOENT;
		goto unlock;
	}

	/* Bounds check source.  */
	if (args->offset > obj->base.size ||
	    args->size > obj->base.size - args->offset) {
		ret = -EINVAL;
		goto out;
	}

	/* prime objects have no backing filp to GEM pread/pwrite
	 * pages from.
	 */
	ret = i915_gem_shmem_pread(dev, obj, args, file);

	TRACE_GEM_OBJ_HISTORY(obj, "pread");

out:
	drm_gem_object_unreference(&obj->base);
unlock:
	mutex_unlock(&dev->struct_mutex);
	return ret;
}

static int
i915_gem_gtt_pwrite_fast(struct drm_device *dev,
		    struct drm_i915_gem_object *obj,
		    struct drm_i915_gem_pwrite *args,
		    /* LINTED */
		    struct drm_file *file_priv)
{
	uint32_t *user_data;
	int ret = 0;
	ret = i915_gem_object_pin(obj, 0, true, true);
	if (ret)
		goto out;

	ret = i915_gem_object_set_to_gtt_domain(obj, true);
	if (ret)
		goto out_unpin;

	ret = i915_gem_object_put_fence(obj);
	if (ret)
		goto out_unpin;
	user_data = (uint32_t *)(uintptr_t)args->data_ptr;

	ret = DRM_COPY_FROM_USER(obj->base.kaddr + args->offset, user_data, args->size);
	if (ret) {
		DRM_ERROR("copy_from_user failed, ret = %d", ret);
		return ret;
	}

out_unpin:
	i915_gem_object_unpin(obj);
out:
	return ret;
}

int
i915_gem_shmem_pwrite(struct drm_device *dev,
			struct drm_i915_gem_object *obj,
		      struct drm_i915_gem_pwrite *args,
		      /* LINTED */
		      struct drm_file *file_priv)
{
	ssize_t remain, page_length;
	uint32_t offset;
	uint64_t first_data_page;
	int shmem_page_index, shmem_page_offset;
	int data_page_index,  data_page_offset;
	int ret = 0;
	uint64_t data_ptr = args->data_ptr;
	int needs_clflush_after = 0;
	int needs_clflush_before = 0;
	int do_bit17_swizzling;
	uint32_t *user_data = (uint32_t *)(uintptr_t)args->data_ptr;

	remain = args->size;

	/* Pin the user pages containing the data.  We can't fault while
	 * holding the struct mutex, and all of the pwrite implementations
	 * want to hold it while dereferencing the user data.
	 */
	first_data_page = data_ptr / PAGE_SIZE;

	do_bit17_swizzling = i915_gem_object_needs_bit17_swizzle(obj);

	if (obj->base.write_domain != I915_GEM_DOMAIN_CPU) {
		/* If we're not in the cpu write domain, set ourself into the gtt
		 * write domain and manually flush cachelines (if required). This
		 * optimizes for the case when the gpu will use the data
		 * right away and we therefore have to clflush anyway. */
		if (obj->cache_level == I915_CACHE_NONE)
			needs_clflush_after = 1;
		if (obj->gtt_space) {
			ret = i915_gem_object_set_to_gtt_domain(obj, true);
			if (ret)
				return ret;
		}
	}
	/* Same trick applies for invalidate partially written cachelines before
	 * writing.  */
	if (!(obj->base.read_domains & I915_GEM_DOMAIN_CPU)
	    && obj->cache_level == I915_CACHE_NONE)
		needs_clflush_before = 1;

	ret = i915_gem_object_get_pages(obj);
	if (ret)
		return ret;

	i915_gem_object_pin_pages(obj);

	if (needs_clflush_before)
		i915_gem_clflush_object(obj);

	offset = args->offset;
	obj->dirty = 1;

	if (do_bit17_swizzling) {
		while (remain > 0) {
			/* Operation in this page
			 *
			 * shmem_page_index = page number within shmem file
			 * shmem_page_offset = offset within page in shmem file
			 * data_page_index = page number in get_user_pages return
			 * data_page_offset = offset with data_page_index page.
			 * page_length = bytes to copy for this page
			 */
			shmem_page_index = offset / DRM_PAGE_SIZE;
			shmem_page_offset = offset & ~DRM_PAGE_MASK;
			data_page_index = data_ptr / DRM_PAGE_SIZE - first_data_page;
			data_page_offset = data_ptr & ~DRM_PAGE_MASK;

			page_length = remain;
			if ((shmem_page_offset + page_length) > DRM_PAGE_SIZE)
				page_length = PAGE_SIZE - shmem_page_offset;
			if ((data_page_offset + page_length) > DRM_PAGE_SIZE)
				page_length = PAGE_SIZE - data_page_offset;

				slow_shmem_bit17_copy(obj->page_list[shmem_page_index],
						shmem_page_offset,
						user_data + data_page_index * DRM_PAGE_SIZE,
						data_page_offset,
						page_length,
						0);

			remain -= page_length;
			data_ptr += page_length;
			offset += page_length;
		}
	} else {
		ret = DRM_COPY_FROM_USER(obj->base.kaddr + args->offset,
				(caddr_t)user_data,
				args->size);
		if (ret)
			DRM_ERROR("shmem_pwrite_copy failed, ret = %d", ret);
	}

	i915_gem_object_unpin_pages(obj);

	if (needs_clflush_after)
		i915_gem_chipset_flush(dev);
	return ret;
}

/**
 * Writes data to the object referenced by handle.
 *
 * On error, the contents of the buffer that were to be modified are undefined.
 */
int
/* LINTED */
i915_gem_pwrite_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_i915_gem_pwrite *args = data;
	struct drm_i915_gem_object *obj;
	int ret;

	if (args->size == 0)
		return 0;

	ret = i915_mutex_lock_interruptible(dev);
	if (ret)
		return ret;

	obj = to_intel_bo(drm_gem_object_lookup(dev, file, args->handle));
	if (&obj->base == NULL) {
		ret = -ENOENT;
		goto unlock;
	}

	/* Bounds check destination. */
	if (args->offset > obj->base.size ||
	    args->size > obj->base.size - args->offset) {
		ret = -EINVAL;
		goto out;
	}

	/* prime objects have no backing filp to GEM pread/pwrite
	 * pages from.
	 */
	TRACE_GEM_OBJ_HISTORY(obj, "pwrite");
	ret = -EFAULT;
	/* We can only do the GTT pwrite on untiled buffers, as otherwise
	 * it would end up going through the fenced access, and we'll get
	 * different detiling behavior between reading and writing.
	 * pread/pwrite currently are reading and writing from the CPU
	 * perspective, requiring manual detiling by the client.
	 */
	if (obj->phys_obj) {
		ret = i915_gem_phys_pwrite(dev, obj, args, file);
		goto out;
	}

	if (obj->cache_level == I915_CACHE_NONE &&
	    obj->tiling_mode == I915_TILING_NONE &&
	    obj->base.write_domain != I915_GEM_DOMAIN_CPU) {
		ret = i915_gem_gtt_pwrite_fast(dev, obj, args, file);
		/* Note that the gtt paths might fail with non-page-backed user
		 * pointers (e.g. gtt mappings when moving data between
		 * textures). Fallback to the shmem path in that case. */

		/* Flushing cursor object */
		if (obj->is_cursor)
			i915_gem_clflush_object(obj);
	}

	if (ret == -EFAULT || ret == -ENOSPC)
		ret = i915_gem_shmem_pwrite(dev, obj, args, file);

out:
	drm_gem_object_unreference(&obj->base);
unlock:
	mutex_unlock(&dev->struct_mutex);
	return ret;
}

int
i915_gem_check_wedge(struct i915_gpu_error *error,
		     bool interruptible)
{
	if (i915_reset_in_progress(error)) {
		/* Non-interruptible callers can't handle -EAGAIN, hence return
		 * -EIO unconditionally for these. */
		if (!interruptible)
			return -EIO;

		/* Recovery complete, but the reset failed ... */
		if (i915_terminally_wedged(error))
			return -EIO;

		return -EAGAIN;
	}

	return 0;
}

/*
 * Compare seqno against outstanding lazy request. Emit a request if they are
 * equal.
 */
static int
i915_gem_check_olr(struct intel_ring_buffer *ring, u32 seqno)
{
	int ret;

	BUG_ON(!mutex_is_locked(&ring->dev->struct_mutex));

	ret = 0;
	if (seqno == ring->outstanding_lazy_request)
		ret = i915_add_request(ring, NULL);

	return ret;
}

/**
 * __wait_seqno - wait until execution of seqno has finished
 * @ring: the ring expected to report seqno
 * @seqno: duh!
 * @reset_counter: reset sequence associated with the given seqno
 * @interruptible: do an interruptible wait (normally yes)
 * @timeout: in - how long to wait (NULL forever); out - how much time remaining
 *
 * Note: It is of utmost importance that the passed in seqno and reset_counter
 * values have been read by the caller in an smp safe manner. Where read-side
 * locks are involved, it is sufficient to read the reset_counter before
 * unlocking the lock that protects the seqno. For lockless tricks, the
 * reset_counter _must_ be read before, and an appropriate smp_rmb must be
 * inserted.
 *
 * Returns 0 if the seqno was found within the alloted time. Else returns the
 * errno with remaining time filled in timeout argument.
 */
static int __wait_seqno(struct intel_ring_buffer *ring, u32 seqno,
			unsigned reset_counter,
			bool interruptible, clock_t timeout)
{
	drm_i915_private_t *dev_priv = ring->dev->dev_private;
	clock_t wait_time = timeout;
	bool wait_forever = false;
	int ret = 0, end = 0;

	if (i915_seqno_passed(ring->get_seqno(ring, true), seqno))
		return 0;

	if (wait_time == 0) {
		wait_time = 3 * DRM_HZ;
	}

	if (!ring->irq_get(ring))
		return -ENODEV;

#define EXIT_COND \
	(i915_seqno_passed(ring->get_seqno(ring, false), seqno) || \
	 i915_reset_in_progress(&dev_priv->gpu_error) || \
	 reset_counter != atomic_read(&dev_priv->gpu_error.reset_counter))
	do {
		/* busy check is faster than cv wait on gen6+ */
		if (IS_GEN6(ring->dev)) {
			if (wait_for(EXIT_COND, jiffies_to_msecs(wait_time)))
				ret = -EBUSY;
		} else if (IS_GEN7(ring->dev) && !IS_HASWELL(ring->dev)) {
			/*
			 * Frequently read CS register may cause my GEN7 platform hang,
			 * but it's crucial for missed IRQ issue.
			 * So the first wait busy check the seqno,
			 * the second wait force correct ordering
			 * between irq and seqno writes then check again.
			 */
			u32 *regs = ring->status_page.page_addr;
			if (wait_for(i915_seqno_passed(regs[I915_GEM_HWS_INDEX],
				seqno) || i915_reset_in_progress(&dev_priv->gpu_error) ||
				reset_counter != atomic_read(&dev_priv->gpu_error.reset_counter),
				 2500)) {
				if (wait_for(i915_seqno_passed(ring->get_seqno(ring, false),
					seqno) || i915_reset_in_progress(&dev_priv->gpu_error) ||
					reset_counter != atomic_read(&dev_priv->gpu_error.reset_counter),
					500)) {
					ret = -EBUSY;
				}
			}
		} else {
			DRM_WAIT(ret, &ring->irq_queue, EXIT_COND);
		}

		/* We need to check whether any gpu reset happened in between
		 * the caller grabbing the seqno and now ... */
		if (reset_counter != atomic_read(&dev_priv->gpu_error.reset_counter))
			ret = -EAGAIN;

		/* ... but upgrade the -EGAIN to an -EIO if the gpu is truely
		 * gone. */
		end = i915_gem_check_wedge(&dev_priv->gpu_error, interruptible);
		if (end)
			ret = end;
	} while (end == 0 && wait_forever);


	ring->irq_put(ring);
#undef EXIT_COND
	if (ret) {
		if ((gpu_dump > 0) && !IS_GEN7(ring->dev)) {
			ring_dump(ring->dev, ring);
			register_dump(ring->dev);
			gtt_dump(ring->dev);
		}
		DRM_ERROR("%s returns %d (awaiting %d at %d, next %d)\n",
			  __func__, ret, seqno, ring->get_seqno(ring, true),
			  dev_priv->next_seqno);
	}

	return (ret);
}

/**
 * Waits for a sequence number to be signaled, and cleans up the
 * request and object lists appropriately for that event.
 */
int
i915_wait_seqno(struct intel_ring_buffer *ring, uint32_t seqno)
{
	struct drm_device *dev = ring->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	bool interruptible = dev_priv->mm.interruptible;
	int ret;

	BUG_ON(!mutex_is_locked(&dev->struct_mutex));
	BUG_ON(seqno == 0);

	ret = i915_gem_check_wedge(&dev_priv->gpu_error, interruptible);
	if (ret)
		return ret;

	ret = i915_gem_check_olr(ring, seqno);
	if (ret)
		return ret;

	return __wait_seqno(ring, seqno,
			    atomic_read(&dev_priv->gpu_error.reset_counter),
			    interruptible, NULL);
}

static int
i915_gem_object_wait_rendering__tail(struct drm_i915_gem_object *obj,
				     struct intel_ring_buffer *ring)
{
	i915_gem_retire_requests_ring(ring);

	/* Manually manage the write flush as we may have not yet
	 * retired the buffer.
	 *
	 * Note that the last_write_seqno is always the earlier of
	 * the two (read/write) seqno, so if we haved successfully waited,
	 * we know we have passed the last write.
	 */
	obj->last_write_seqno = 0;
	obj->base.write_domain &= ~I915_GEM_GPU_DOMAINS;

	return 0;
}

/**
 * Ensures that all rendering to the object has completed and the object is
 * safe to unbind from the GTT or access from the CPU.
 */
static int
i915_gem_object_wait_rendering(struct drm_i915_gem_object *obj,
			       bool readonly)
{
	struct intel_ring_buffer *ring = obj->ring;
	u32 seqno;
	int ret;

	seqno = readonly ? obj->last_write_seqno : obj->last_read_seqno;
	if (seqno == 0)
		return 0;

	ret = i915_wait_seqno(ring, seqno);
	if (ret)
		return ret;

	return i915_gem_object_wait_rendering__tail(obj, ring);
}

/* A nonblocking variant of the above wait. This is a highly dangerous routine
 * as the object state may change during this call.
 */
static int
i915_gem_object_wait_rendering__nonblocking(struct drm_i915_gem_object *obj,
					    bool readonly)
{
	struct drm_device *dev = obj->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_ring_buffer *ring = obj->ring;
	unsigned reset_counter;
	u32 seqno;
	int ret;

	BUG_ON(!mutex_is_locked(&dev->struct_mutex));
	BUG_ON(!dev_priv->mm.interruptible);

	seqno = readonly ? obj->last_write_seqno : obj->last_read_seqno;
	if (seqno == 0)
		return 0;

	ret = i915_gem_check_wedge(&dev_priv->gpu_error, true);
	if (ret)
		return ret;

	ret = i915_gem_check_olr(ring, seqno);
	if (ret)
		return ret;

	reset_counter = atomic_read(&dev_priv->gpu_error.reset_counter);
	mutex_unlock(&dev->struct_mutex);
	ret = __wait_seqno(ring, seqno, reset_counter, true, NULL);
	mutex_lock(&dev->struct_mutex);
	if (ret)
	return ret;

	return i915_gem_object_wait_rendering__tail(obj, ring);
}

/**
 * Called when user space prepares to use an object with the CPU, either
 * through the mmap ioctl's mapping or a GTT mapping.
 */
int
/* LINTED */
i915_gem_set_domain_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_i915_gem_set_domain *args = data;
	struct drm_i915_gem_object *obj;
	uint32_t read_domains = args->read_domains;
	uint32_t write_domain = args->write_domain;
	int ret;

	/* Only handle setting domains to types used by the CPU. */
	if (write_domain & I915_GEM_GPU_DOMAINS)
		return -EINVAL;

	if (read_domains & I915_GEM_GPU_DOMAINS)
		return -EINVAL;

	/* Having something in the write domain implies it's in the read
	 * domain, and only that read domain.  Enforce that in the request.
	 */
	if (write_domain != 0 && read_domains != write_domain)
		return -EINVAL;

	ret = i915_mutex_lock_interruptible(dev);
	if (ret)
		return ret;

	obj = to_intel_bo(drm_gem_object_lookup(dev, file, args->handle));
	if (&obj->base == NULL) {
		ret = -ENOENT;
		goto unlock;
	}

	/* Try to flush the object off the GPU without holding the lock.
	 * We will repeat the flush holding the lock in the normal manner
	 * to catch cases where we are gazumped.
	 */
	ret = i915_gem_object_wait_rendering__nonblocking(obj, !write_domain);
	if (ret)
		goto unref;

	if (read_domains & I915_GEM_DOMAIN_GTT) {
		ret = i915_gem_object_set_to_gtt_domain(obj, write_domain != 0);

		/* Silently promote "you're not bound, there was nothing to do"
		 * to success, since the client was just asking us to
		 * make sure everything was done.
		 */
		if (ret == -EINVAL)
			ret = 0;
	} else {
		ret = i915_gem_object_set_to_cpu_domain(obj, write_domain != 0);
	}

unref:
	drm_gem_object_unreference(&obj->base);
unlock:
	mutex_unlock(&dev->struct_mutex);
	return ret;
}

/**
 * Called when user space has done writes to this buffer
 */
int
/* LINTED */
i915_gem_sw_finish_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_i915_gem_sw_finish *args = data;
	struct drm_i915_gem_object *obj;
	int ret = 0;

	ret = i915_mutex_lock_interruptible(dev);
	if (ret)
		return ret;

	obj = to_intel_bo(drm_gem_object_lookup(dev, file, args->handle));
	if (&obj->base == NULL) {
		ret = -ENOENT;
		goto unlock;
	}

	/* Pinned buffers may be scanout, so flush the cache */
	if (obj->pin_count)
		i915_gem_object_flush_cpu_write_domain(obj);

	drm_gem_object_unreference(&obj->base);
unlock:
	mutex_unlock(&dev->struct_mutex);
	return ret;
}

/**
 * Maps the contents of an object, returning the address it is mapped
 * into.
 *
 * While the mapping holds a reference on the contents of the object, it doesn't
 * imply a ref on the object itself.
 */
int
/* LINTED */
i915_gem_mmap_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_i915_gem_mmap *args = data;
	struct drm_gem_object *obj;
	caddr_t vvaddr = NULL;
	int ret;

	if (!(dev->driver->driver_features & DRIVER_GEM))
		return -ENODEV;

	obj = drm_gem_object_lookup(dev, file, args->handle);
	if (obj == NULL)
		return -EBADF;

	/* prime objects have no backing filp to GEM mmap
	 * pages from.
	 */

	if (obj->size > dev_priv->gtt.mappable_end) {
		drm_gem_object_unreference_unlocked(obj);
		return -E2BIG;
	}

	ret = ddi_devmap_segmap(dev_id, (off_t)obj->maplist.user_token,
	    ttoproc(curthread)->p_as, &vvaddr, obj->maplist.map->size,
	    PROT_ALL, PROT_ALL, MAP_SHARED, credp);
	if (ret)
		return ret;

	mutex_lock(&dev->struct_mutex);
	drm_gem_object_unreference(obj);
	mutex_unlock(&dev->struct_mutex);

	args->addr_ptr = (uint64_t)(uintptr_t)vvaddr;

	return 0;
}

void
i915_gem_fault(struct drm_gem_object *obj)
{
	struct drm_device *dev = obj->dev;
	struct drm_i915_gem_object *obj_priv = to_intel_bo(obj);
	uint64_t start;
	int ret = 0;

	if (obj->maplist.map->gtt_mmap)
		return;

	/* Now bind it into the GTT if needed */
	mutex_lock(&dev->struct_mutex);

	TRACE_GEM_OBJ_HISTORY(obj_priv, "gfault");

	/* Access to snoopable pages through the GTT is incoherent. */
	if (obj_priv->cache_level != I915_CACHE_NONE && !HAS_LLC(dev)) {
		ret = -EINVAL;
		goto unlock;
	}

	ret = i915_gem_object_pin(obj_priv, 0, true, false);
	if (ret)
		goto unlock;

	ret = i915_gem_object_set_to_gtt_domain(obj_priv, 1);
	if (ret)
		goto unpin;

	ret = i915_gem_object_get_fence(obj_priv);
	if (ret)
		goto unpin;

	obj_priv->fault_mappable = true;

	start = (dev->agp_aperbase + obj_priv->gtt_offset);

	/* Finally, remap it using the new GTT offset */
	drm_gem_mmap(obj, start);

	obj->maplist.map->gtt_mmap = 1;

unpin:
	i915_gem_object_unpin(obj_priv);
unlock:
	mutex_unlock(&dev->struct_mutex);
}

/**
 * i915_gem_create_mmap_offset - create a fake mmap offset for an object
 * @obj: obj in question
 *
 * GEM memory mapping works by handing back to userspace a fake mmap offset
 * it can use in a subsequent mmap(2) call.  The DRM core code then looks
 * up the object based on the offset and sets up the various memory mapping
 * structures.
 *
 * This routine allocates and attaches a fake offset for @obj.
 */
static int
i915_gem_create_mmap_offset(struct drm_i915_gem_object *obj)
{
	struct ddi_umem_cookie *umem_cookie = obj->base.maplist.map->umem_cookie;
	int ret;

	if (obj->base.gtt_map_kaddr == NULL) {
		ret = drm_gem_create_mmap_offset(&obj->base);
		if (ret) {
			DRM_ERROR("failed to alloc kernel memory");
			return ret;
		}
	}

	umem_cookie->cvaddr = obj->base.gtt_map_kaddr;

	/* user_token is the fake offset
	 * which create in drm_map_handle at alloc time
	 */
	obj->mmap_offset = obj->base.maplist.user_token;
	obj->base.maplist.map->callback = 1;

	return 0;
}

/**
 * i915_gem_release_mmap - remove physical page mappings
 * @obj: obj in question
 *
 * Preserve the reservation of the mmaping with the DRM core code, but
 * relinquish ownership of the pages back to the system.
 *
 * It is vital that we remove the page mapping if we have mapped a tiled
 * object through the GTT and then lose the fence register due to
 * resource pressure. Similarly if the object has been moved out of the
 * aperture, than pages mapped into userspace must be revoked. Removing the
 * mapping will then trigger a page fault on the next user access, allowing
 * fixup by i915_gem_fault().
 */
void
i915_gem_release_mmap(struct drm_i915_gem_object *obj)
{
	struct drm_device *dev = obj->base.dev;
	struct gem_map_list *entry, *temp;

	if (obj->base.maplist.map->gtt_mmap) {
		mutex_lock(&dev->page_fault_lock);
		if (!list_empty(&obj->base.seg_list)) {
			list_for_each_entry_safe(entry, temp, struct gem_map_list, &obj->base.seg_list, head) {
				devmap_unload(entry->dhp, entry->mapoffset, entry->maplen);
				list_del(&entry->head);
				drm_free(entry, sizeof (struct gem_map_list), DRM_MEM_MAPS);
			}
		}
		mutex_unlock(&dev->page_fault_lock);
		drm_gem_release_mmap(&obj->base);
		obj->base.maplist.map->gtt_mmap = 0;
	}
}

static void
i915_gem_free_mmap_offset(struct drm_i915_gem_object *obj)
{
	drm_gem_free_mmap_offset(&obj->base);
	obj->mmap_offset = 0;
}

uint32_t
i915_gem_get_gtt_size(struct drm_device *dev, uint32_t size, int tiling_mode)
{
	uint32_t gtt_size;

	if (INTEL_INFO(dev)->gen >= 4 ||
	    tiling_mode == I915_TILING_NONE)
		return size;

	/* Previous chips need a power-of-two fence region when tiling */
	if (INTEL_INFO(dev)->gen == 3)
		gtt_size = 1024*1024;
	else
		gtt_size = 512*1024;

	while (gtt_size < size)
		gtt_size <<= 1;

	return gtt_size;
}

/**
 * i915_gem_get_gtt_alignment - return required GTT alignment for an object
 * @obj: object to check
 *
 * Return the required GTT alignment for an object, taking into account
 * potential fence register mapping if needed.
 */
uint32_t
i915_gem_get_gtt_alignment(struct drm_device *dev, uint32_t size,
			   int tiling_mode, bool fenced)
{
	/*
	 * Minimum alignment is 4k (GTT page size), but might be greater
	 * if a fence register is needed for the object.
	 */
	if (INTEL_INFO(dev)->gen >= 4 || (!fenced && IS_G33(dev)) ||
		tiling_mode == I915_TILING_NONE)
		return 4096;

	/*
	 * Previous chips need to be aligned to the size of the smallest
	 * fence register that can contain the object.
	 */
	return i915_gem_get_gtt_size(dev, size, tiling_mode);
}


int
i915_gem_mmap_gtt(struct drm_file *file,
		  struct drm_device *dev,
		  uint32_t handle,
		  uint64_t *offset)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_i915_gem_object *obj;
	int ret;

	ret = i915_mutex_lock_interruptible(dev);
	if (ret)
		return ret;

	obj = to_intel_bo(drm_gem_object_lookup(dev, file, handle));
	if (&obj->base == NULL) {
		ret = -ENOENT;
		goto unlock;
	}

	if (obj->base.size > dev_priv->gtt.mappable_end) {
		ret = -E2BIG;
		goto out;
	}

	if (!obj->mmap_offset) {
		ret = i915_gem_create_mmap_offset(obj);
		if (ret)
			goto out;
	}

	*offset = obj->mmap_offset;

out:
	drm_gem_object_unreference(&obj->base);
unlock:
	mutex_unlock(&dev->struct_mutex);
	return ret;
}

/**
 * i915_gem_mmap_gtt_ioctl - prepare an object for GTT mmap'ing
 * @dev: DRM device
 * @data: GTT mapping ioctl data
 * @file_priv: GEM object info
 *
 * Simply returns the fake offset to userspace so it can mmap it.
 * The mmap call will end up in drm_gem_mmap(), which will set things
 * up so we can get faults in the handler above.
 *
 * The fault handler will take care of binding the object into the GTT
 * (since it may have been evicted to make room for something), allocating
 * a fence register, and mapping the appropriate aperture address into
 * userspace.
 */
int
/* LINTED */
i915_gem_mmap_gtt_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_i915_gem_mmap_gtt *args = data;

	return i915_gem_mmap_gtt(file, dev, args->handle, &args->offset);
}

static void
i915_gem_object_put_pages_gtt(struct drm_i915_gem_object *obj)
{
	int ret;
	ret = i915_gem_object_set_to_cpu_domain(obj, true);
	if (ret) {
		/* In the event of a disaster, abandon all caches and
		 * hope for the best.
		 */
		WARN_ON(ret != -EIO);
		i915_gem_clflush_object(obj);
		obj->base.read_domains = obj->base.write_domain = I915_GEM_DOMAIN_CPU;
	}
	if (i915_gem_object_needs_bit17_swizzle(obj))
		i915_gem_object_save_bit_17_swizzle(obj);

	obj->dirty = 0;

	kmem_free(obj->page_list,
	    btop(obj->base.size) * sizeof(caddr_t));
	obj->page_list = NULL;
}

static int
i915_gem_object_put_pages(struct drm_i915_gem_object *obj)
{
	const struct drm_i915_gem_object_ops *ops = obj->ops;

	if (obj->page_list == NULL)
		return 0;

	BUG_ON(obj->gtt_space);

	if (obj->pages_pin_count)
		return -EBUSY;

	ops->put_pages(obj);
	obj->page_list = NULL;

	list_del(&obj->global_list);
	return 0;
}

static int
i915_gem_object_get_pages_gtt(struct drm_i915_gem_object *obj)
{
	pgcnt_t np = btop(obj->base.size);
	caddr_t va;
	long i;

	obj->page_list = kmem_zalloc(np * sizeof(caddr_t), KM_SLEEP);
	if (obj->page_list == NULL) {
		DRM_ERROR("Faled to allocate page list. size = %ld", np * sizeof(caddr_t));
		return -ENOMEM;
	}

	for (i = 0, va = obj->base.kaddr; i < np; i++, va += PAGESIZE) {
		obj->page_list[i] = va;
	}

	if (i915_gem_object_needs_bit17_swizzle(obj))
		i915_gem_object_do_bit_17_swizzle(obj);
	return 0;
}


/* Ensure that the associated pages are gathered from the backing storage
 * and pinned into our object. i915_gem_object_get_pages() may be called
 * multiple times before they are released by a single call to
 * i915_gem_object_put_pages() - once the pages are no longer referenced
 * either as a result of memory pressure (reaping pages under the shrinker)
 * or as the object is itself released.
 */
int
i915_gem_object_get_pages(struct drm_i915_gem_object *obj)
{
	struct drm_i915_private *dev_priv = obj->base.dev->dev_private;
	const struct drm_i915_gem_object_ops *ops = obj->ops;
	int ret;

	if (obj->page_list)
		return 0;

	BUG_ON(obj->pages_pin_count);

	ret = ops->get_pages(obj);
	if (ret)
		return ret;

	list_add_tail(&obj->global_list, &dev_priv->mm.unbound_list, (caddr_t)obj);
	return 0;
}

void
i915_gem_object_move_to_active(struct drm_i915_gem_object *obj,
			       struct intel_ring_buffer *ring)
{
	struct drm_device *dev = obj->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 seqno = intel_ring_get_seqno(ring);

	BUG_ON(ring == NULL);
	if (obj->ring != ring && obj->last_write_seqno) {
		/* Keep the seqno relative to the current ring */
		obj->last_write_seqno = seqno;
	}
	obj->ring = ring;

	/* Add a reference if we're newly entering the active list. */
	if (!obj->active) {
		drm_gem_object_reference(&obj->base);
		obj->active = 1;
	}

	/* Move from whatever list we were on to the tail of execution. */
	list_move_tail(&obj->mm_list, &dev_priv->mm.active_list, (caddr_t)obj);
	list_move_tail(&obj->ring_list, &ring->active_list, (caddr_t)obj);
	obj->last_read_seqno = seqno;

	if (obj->fenced_gpu_access) {
		obj->last_fenced_seqno = seqno;

               /* Bump MRU to take account of the delayed flush */
               if (obj->fence_reg != I915_FENCE_REG_NONE) {
                       struct drm_i915_fence_reg *reg;

                       reg = &dev_priv->fence_regs[obj->fence_reg];
                       list_move_tail(&reg->lru_list, &dev_priv->mm.fence_list, (caddr_t)reg);
               }
	}
	TRACE_GEM_OBJ_HISTORY(obj, "to active");
}

static void
i915_gem_object_move_to_inactive(struct drm_i915_gem_object *obj)
{
	struct drm_device *dev = obj->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;

	BUG_ON(obj->base.write_domain & ~I915_GEM_GPU_DOMAINS);
	BUG_ON(!obj->active);

	list_move_tail(&obj->mm_list, &dev_priv->mm.inactive_list, (caddr_t)obj);

	list_del_init(&obj->ring_list);
	obj->ring = NULL;

	obj->last_read_seqno = 0;
	obj->last_write_seqno = 0;
	obj->base.write_domain = 0;

	obj->last_fenced_seqno = 0;
	obj->fenced_gpu_access = false;

	obj->active = 0;
	TRACE_GEM_OBJ_HISTORY(obj, "to inactive");
	drm_gem_object_unreference(&obj->base);

	WARN_ON(i915_verify_lists(dev));
}

static int
i915_gem_init_seqno(struct drm_device *dev, u32 seqno)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_ring_buffer *ring;
	int ret, i, j;

	/* Carefully retire all requests without writing to the rings */
	for_each_ring(ring, dev_priv, i) {
		ret = intel_ring_idle(ring);
		if (ret)
			return ret;
	}
	i915_gem_retire_requests(dev);

	/* Finally reset hw state */
	for_each_ring(ring, dev_priv, i) {
		intel_ring_init_seqno(ring, seqno);

		for (j = 0; j < ARRAY_SIZE(ring->sync_seqno); j++)
			ring->sync_seqno[j] = 0;
	}

	return 0;
}

int i915_gem_set_seqno(struct drm_device *dev, u32 seqno)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int ret;

	if (seqno == 0)
		return -EINVAL;

	/* HWS page needs to be set less than what we
	 * will inject to ring
	 */
	ret = i915_gem_init_seqno(dev, seqno - 1);
	if (ret)
		return ret;

	/* Carefully set the last_seqno value so that wrap
	 * detection still works
	 */
	dev_priv->next_seqno = seqno;
	dev_priv->last_seqno = seqno - 1;
	if (dev_priv->last_seqno == 0)
		dev_priv->last_seqno--;

	return 0;
}

int
i915_gem_get_seqno(struct drm_device *dev, u32 *seqno)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	/* reserve 0 for non-seqno */
	if (dev_priv->next_seqno == 0) {
		int ret = i915_gem_init_seqno(dev, 0);
		if (ret)
			return ret;

		dev_priv->next_seqno = 1;
	}

	*seqno = dev_priv->last_seqno = dev_priv->next_seqno++;
	return 0;
}

int __i915_add_request(struct intel_ring_buffer *ring,
		       struct drm_file *file,
		       struct drm_i915_gem_object *obj,
		       u32 *out_seqno)
{
	drm_i915_private_t *dev_priv = ring->dev->dev_private;
	struct drm_i915_gem_request *request;
	u32 request_ring_position, request_start;
	int was_empty;
	int ret;

	request_start = intel_ring_get_tail(ring);
	/*
	 * Emit any outstanding flushes - execbuf can fail to emit the flush
	 * after having emitted the batchbuffer command. Hence we need to fix
	 * things up similar to emitting the lazy request. The difference here
	 * is that the flush _must_ happen before the next request, no matter
	 * what.
	 */
	ret = intel_ring_flush_all_caches(ring);
	if (ret)
		return ret;

	request = kmalloc(sizeof(*request), GFP_KERNEL);
	if (request == NULL)
		return -ENOMEM;


	/* Record the position of the start of the request so that
	 * should we detect the updated seqno part-way through the
	 * GPU processing the request, we never over-estimate the
	 * position of the head.
	 */
	request_ring_position = intel_ring_get_tail(ring);

	ret = ring->add_request(ring);
	if (ret) {
		kfree(request, sizeof(*request));
		return ret;
	}

	request->seqno = intel_ring_get_seqno(ring);
	request->ring = ring;
	request->head = request_start;
	request->tail = request_ring_position;
	request->ctx = ring->last_context;
	request->batch_obj = obj;

	/* Whilst this request exists, batch_obj will be on the
	 * active_list, and so will hold the active reference. Only when this
	 * request is retired will the the batch_obj be moved onto the
	 * inactive_list and lose its active reference. Hence we do not need
	 * to explicitly hold another reference here.
	 */

	if (request->ctx)
		i915_gem_context_reference(request->ctx);

	request->emitted_jiffies = jiffies;
	was_empty = list_empty(&ring->request_list);
	list_add_tail(&request->list, &ring->request_list, (caddr_t)request);
	request->file_priv = NULL;

	if (file) {
		struct drm_i915_file_private *file_priv = file->driver_priv;
		if (file_priv->status == 1) {
			spin_lock(&file_priv->mm.lock);
			request->file_priv = file_priv;
			list_add_tail(&request->client_list,
			      &file_priv->mm.request_list, (caddr_t)request);
			spin_unlock(&file_priv->mm.lock);
		}
	}

	ring->outstanding_lazy_request = 0;

	if (!dev_priv->mm.suspended && !dev_priv->gpu_hang) {
		if (i915_enable_hangcheck) {
			mod_timer(&dev_priv->gpu_error.hangcheck_timer,
				msecs_to_jiffies(DRM_I915_HANGCHECK_PERIOD));
		}
		if (was_empty) {
			/* change to delay HZ and then run work (not insert to workqueue of Linux) */
			test_set_timer(&dev_priv->mm.retire_timer, DRM_HZ);
			DRM_DEBUG("i915_gem: schedule_delayed_work");
			intel_mark_busy(dev_priv->dev);
		}
	}

	if (out_seqno)
		*out_seqno = request->seqno;

	return 0;
}

static inline void
i915_gem_request_remove_from_client(struct drm_i915_gem_request *request)
{
	struct drm_i915_file_private *file_priv = request->file_priv;

	if (!file_priv)
		return;

	spin_lock(&file_priv->mm.lock);
	if (request->file_priv) {
		list_del(&request->client_list);
		request->file_priv = NULL;
	}
	spin_unlock(&file_priv->mm.lock);
}

static bool i915_head_inside_object(u32 acthd, struct drm_i915_gem_object *obj)
{
	if (acthd >= obj->gtt_offset &&
	    acthd < obj->gtt_offset + obj->base.size)
		return true;

	return false;
}

static bool i915_head_inside_request(const u32 acthd_unmasked,
				     const u32 request_start,
				     const u32 request_end)
{
	const u32 acthd = acthd_unmasked & HEAD_ADDR;

	if (request_start < request_end) {
		if (acthd >= request_start && acthd < request_end)
			return true;
	} else if (request_start > request_end) {
		if (acthd >= request_start || acthd < request_end)
			return true;
	}

	return false;
}

static bool i915_request_guilty(struct drm_i915_gem_request *request,
				const u32 acthd, bool *inside)
{
	/* There is a possibility that unmasked head address
	 * pointing inside the ring, matches the batch_obj address range.
	 * However this is extremely unlikely.
	 */

	if (request->batch_obj) {
		if (i915_head_inside_object(acthd, request->batch_obj)) {
			*inside = true;
			return true;
		}
	}

	if (i915_head_inside_request(acthd, request->head, request->tail)) {
		*inside = false;
		return true;
	}

	return false;
}

static void i915_set_reset_status(struct intel_ring_buffer *ring,
				  struct drm_i915_gem_request *request,
				  u32 acthd)
{
	struct i915_ctx_hang_stats *hs = NULL;
	bool inside, guilty;

	/* Innocent until proven guilty */
	guilty = false;

	if (ring->hangcheck.action != wait &&
	    i915_request_guilty(request, acthd, &inside)) {
		DRM_ERROR("%s hung %s bo (0x%x ctx %d) at 0x%x\n",
			  ring->name,
			  inside ? "inside" : "flushing",
			  request->batch_obj ?
			  request->batch_obj->gtt_offset : 0,
			  request->ctx ? request->ctx->id : 0,
			  acthd);

		guilty = true;
	}

	/* If contexts are disabled or this is the default context, use
	 * file_priv->reset_state
	 */
	if (request->ctx && request->ctx->id != DEFAULT_CONTEXT_ID)
		hs = &request->ctx->hang_stats;
	else if (request->file_priv)
		hs = &request->file_priv->hang_stats;

	if (hs) {
		if (guilty)
			hs->batch_active++;
		else
			hs->batch_pending++;
	}
}

static void i915_gem_free_request(struct drm_i915_gem_request *request)
{
	list_del(&request->list);
	i915_gem_request_remove_from_client(request);

	if (request->ctx)
		i915_gem_context_unreference(request->ctx);

	kfree(request, sizeof(*request));
}

static void i915_gem_reset_ring_lists(struct drm_i915_private *dev_priv,
				      struct intel_ring_buffer *ring)
{
	u32 completed_seqno;
	u32 acthd;

	acthd = intel_ring_get_active_head(ring);
	completed_seqno = ring->get_seqno(ring, false);

	while (!list_empty(&ring->request_list)) {
		struct drm_i915_gem_request *request;

		request = list_first_entry(&ring->request_list,
					   struct drm_i915_gem_request,
					   list);

		if (request->seqno > completed_seqno)
			i915_set_reset_status(ring, request, acthd);

		i915_gem_free_request(request);
	}

	while (!list_empty(&ring->active_list)) {
		struct drm_i915_gem_object *obj;

		obj = list_first_entry(&ring->active_list,
					    struct drm_i915_gem_object,
					    ring_list);

		i915_gem_object_move_to_inactive(obj);
	}
}

void i915_gem_restore_fences(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int i;

	for (i = 0; i < dev_priv->num_fence_regs; i++) {
		struct drm_i915_fence_reg *reg = &dev_priv->fence_regs[i];

		/*
		 * Commit delayed tiling changes if we have an object still
		 * attached to the fence, otherwise just clear the fence.
		 */
		if (reg->obj) {
			i915_gem_object_update_fence(reg->obj, reg,
						     reg->obj->tiling_mode);
		} else {
			i915_gem_write_fence(dev, i, NULL);
		}
	}
}

void i915_gem_reset(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_i915_gem_object *obj;
	struct intel_ring_buffer *ring;
	int i;

	for_each_ring(ring, dev_priv, i)
		i915_gem_reset_ring_lists(dev_priv, ring);

	/* Move everything out of the GPU domains to ensure we do any
	 * necessary invalidation upon reuse.
	 */
	list_for_each_entry(obj, struct drm_i915_gem_object,
			    &dev_priv->mm.inactive_list,
			    mm_list)
	{
		obj->base.read_domains &= ~I915_GEM_GPU_DOMAINS;
	}

	i915_gem_restore_fences(dev);
}

/**
 * This function clears the request list as sequence numbers are passed.
 */
void
i915_gem_retire_requests_ring(struct intel_ring_buffer *ring)
{
	uint32_t seqno;

	if (list_empty(&ring->request_list))
		return;

	WARN_ON(i915_verify_lists(ring->dev));

	seqno = ring->get_seqno(ring, true);

	while (!list_empty(&ring->request_list)) {
		struct drm_i915_gem_request *request;

		request = list_first_entry(&ring->request_list,
					   struct drm_i915_gem_request,
					   list);

		if (!i915_seqno_passed(seqno, request->seqno))
			break;

		/* We know the GPU must have read the request to have
		 * sent us the seqno + interrupt, so use the position
		 * of tail of the request to update the last known position
		 * of the GPU head.
		 */
		ring->last_retired_head = request->tail;

		i915_gem_free_request(request);
	}

	/* Move any buffers on the active list that are no longer referenced
	 * by the ringbuffer to the flushing/inactive lists as appropriate.
	 */
	while (!list_empty(&ring->active_list)) {
		struct drm_i915_gem_object *obj;

		obj = list_first_entry(&ring->active_list,
					    struct drm_i915_gem_object,
					    ring_list);

		if (!i915_seqno_passed(seqno, obj->last_read_seqno))
			break;

		i915_gem_object_move_to_inactive(obj);
	}

	if (ring->trace_irq_seqno &&
		     i915_seqno_passed(seqno, ring->trace_irq_seqno)) {
		ring->irq_put(ring);
		ring->trace_irq_seqno = 0;
	}

	WARN_ON(i915_verify_lists(ring->dev));
}

void
i915_gem_retire_requests(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct intel_ring_buffer *ring;
	int i;

	for_each_ring(ring, dev_priv, i)
		i915_gem_retire_requests_ring(ring);
}

static void
i915_gem_retire_work_handler(struct work_struct *work)
{
	drm_i915_private_t *dev_priv = container_of(work, drm_i915_private_t,
						mm.retire_work);
	struct drm_device *dev = dev_priv->dev;
	struct intel_ring_buffer *ring;
	bool idle;
	int i;

	/* Come back later if the device is busy... */
	if (!mutex_tryenter(&dev->struct_mutex)) {
		test_set_timer(&dev_priv->mm.retire_timer, DRM_HZ);
		return;
	}

	i915_gem_retire_requests(dev);

	/* Send a periodic flush down the ring so we don't hold onto GEM
	 * objects indefinitely.
	 */
	idle = true;
	for_each_ring(ring, dev_priv, i) {
		if (ring->gpu_caches_dirty)
			i915_add_request(ring, NULL);

		idle &= list_empty(&ring->request_list);
	}

	if (!dev_priv->mm.suspended && !idle && !dev_priv->gpu_hang)
	{
		DRM_DEBUG("i915_gem: schedule_delayed_work");
		test_set_timer(&dev_priv->mm.retire_timer, DRM_HZ);
	}
	if (idle)
		intel_mark_idle(dev);
	mutex_unlock(&dev->struct_mutex);
}

void
i915_gem_retire_work_timer(void *device)
{
	struct drm_device *dev = (struct drm_device *)device;
	drm_i915_private_t *dev_priv = dev->dev_private;
	queue_work(dev_priv->wq, &dev_priv->mm.retire_work);
}

/**
 * Ensures that an object will eventually get non-busy by flushing any required
 * write domains, emitting any outstanding lazy request and retiring and
 * completed requests.
 */
static int
i915_gem_object_flush_active(struct drm_i915_gem_object *obj)
{
	int ret;

	if (obj->active) {
		ret = i915_gem_check_olr(obj->ring, obj->last_read_seqno);
		if (ret)
			return ret;

		i915_gem_retire_requests_ring(obj->ring);
	}

	return 0;
}

/**
 * i915_gem_wait_ioctl - implements DRM_IOCTL_I915_GEM_WAIT
 * @DRM_IOCTL_ARGS: standard ioctl arguments
 *
 * Returns 0 if successful, else an error is returned with the remaining time in
 * the timeout parameter.
 *  -ETIME: object is still busy after timeout
 *  -ERESTARTSYS: signal interrupted the wait
 *  -ENONENT: object doesn't exist
 * Also possible, but rare:
 *  -EAGAIN: GPU wedged
 *  -ENOMEM: damn
 *  -ENODEV: Internal IRQ fail
 *  -E?: The add request failed
 *
 * The wait ioctl with a timeout of 0 reimplements the busy ioctl. With any
 * non-zero timeout parameter the wait ioctl will wait for the given number of
 * nanoseconds on an object becoming unbusy. Since the wait itself does so
 * without holding struct_mutex the object may become re-busied before this
 * function completes. A similar but shorter * race condition exists in the busy
 * ioctl
 */
int
i915_gem_wait_ioctl(DRM_IOCTL_ARGS)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct drm_i915_gem_wait *args = data;
	struct drm_i915_gem_object *obj;
	struct intel_ring_buffer *ring = NULL;
	clock_t timeout = NULL;
	unsigned reset_counter;
	u32 seqno = 0;
	int ret = 0;

	if (args->timeout_ns >= 0) {
		timeout = drv_usectohz(args->timeout_ns / 1000);
	}

	ret = i915_mutex_lock_interruptible(dev);
	if (ret)
		return ret;

	obj = to_intel_bo(drm_gem_object_lookup(dev, file, args->bo_handle));
	if (&obj->base == NULL) {
		mutex_unlock(&dev->struct_mutex);
		return -ENOENT;
	}

	/* Need to make sure the object gets inactive eventually. */
	ret = i915_gem_object_flush_active(obj);
	if (ret)
		goto out;

	if (obj->active) {
		seqno = obj->last_read_seqno;
		ring = obj->ring;
	}

	if (seqno == 0)
		 goto out;

	/* Do this after OLR check to make sure we make forward progress polling
	 * on this IOCTL with a 0 timeout (like busy ioctl)
	 */
	if (!args->timeout_ns) {
		ret = -ETIME;
		goto out;
	}

	drm_gem_object_unreference(&obj->base);
	reset_counter = atomic_read(&dev_priv->gpu_error.reset_counter);
	mutex_unlock(&dev->struct_mutex);

	ret = __wait_seqno(ring, seqno, reset_counter, true, timeout);
	if (timeout) {
		args->timeout_ns = drv_hztousec(timeout) * 1000;
	}
	return ret;

out:
	drm_gem_object_unreference(&obj->base);
	mutex_unlock(&dev->struct_mutex);
	return ret;
}

/**
 * i915_gem_object_sync - sync an object to a ring.
 *
 * @obj: object which may be in use on another ring.
 * @to: ring we wish to use the object on. May be NULL.
 *
 * This code is meant to abstract object synchronization with the GPU.
 * Calling with NULL implies synchronizing the object with the CPU
 * rather than a particular GPU ring.
 *
 * Returns 0 if successful, else propagates up the lower layer error.
 */
int
i915_gem_object_sync(struct drm_i915_gem_object *obj,
		     struct intel_ring_buffer *to)
{
	struct intel_ring_buffer *from = obj->ring;
	u32 seqno;
	int ret, idx;

	if (from == NULL || to == from)
		return 0;

	if (to == NULL || !i915_semaphore_is_enabled(obj->base.dev))
		return i915_gem_object_wait_rendering(obj, false);

	idx = intel_ring_sync_index(from, to);

	seqno = obj->last_read_seqno;
	if (seqno <= from->sync_seqno[idx])
		return 0;

	ret = i915_gem_check_olr(obj->ring, seqno);
	if (ret)
		return ret;

	ret = to->sync_to(to, from, seqno);
	if (!ret)
		/* We use last_read_seqno because sync_to()
		 * might have just caused seqno wrap under
		 * the radar.
		 */
		from->sync_seqno[idx] = obj->last_read_seqno;

	return ret;
}

static void i915_gem_object_finish_gtt(struct drm_i915_gem_object *obj)
{

	/* Force a pagefault for domain tracking on next user access */
	i915_gem_release_mmap(obj);

	if ((obj->base.read_domains & I915_GEM_DOMAIN_GTT) == 0)
		return;

	membar_producer();
	obj->base.read_domains &= ~I915_GEM_DOMAIN_GTT;
	obj->base.write_domain &= ~I915_GEM_DOMAIN_GTT;
}

/**
 * Unbinds an object from the GTT aperture.
 */
int
i915_gem_object_unbind(struct drm_i915_gem_object *obj, uint32_t type)
{
	drm_i915_private_t *dev_priv = obj->base.dev->dev_private;
	int ret;

	if (obj->gtt_space == NULL)
		return 0;

	if (obj->pin_count)
		return -EBUSY;

	BUG_ON(obj->page_list == NULL);

	ret = i915_gem_object_finish_gpu(obj);
	if (ret)
		return ret;
	/* Continue on if we fail due to EIO, the GPU is hung so we
	 * should be safe and we need to cleanup or else we might
	 * cause memory corruption through use-after-free.
	 */

	i915_gem_object_finish_gtt(obj);

	/* release the fence reg _after_ flushing */
	ret = i915_gem_object_put_fence(obj);
	if (ret)
		return ret;

	if (obj->has_global_gtt_mapping)
		i915_gem_gtt_unbind_object(obj, type);
	if (obj->has_aliasing_ppgtt_mapping) {
		i915_ppgtt_unbind_object(dev_priv->mm.aliasing_ppgtt, obj);
		obj->has_aliasing_ppgtt_mapping = 0;
	}
	i915_gem_gtt_finish_object(obj);
	i915_gem_object_unpin_pages(obj);

	list_del(&obj->mm_list);
	list_move_tail(&obj->global_list, &dev_priv->mm.unbound_list, (caddr_t)obj);
	/* Avoid an unnecessary call to unbind on rebind. */
	obj->map_and_fenceable = true;

	drm_mm_put_block(obj->gtt_space);
	obj->gtt_space = NULL;
	obj->gtt_offset = 0;
	TRACE_GEM_OBJ_HISTORY(obj, "unbind");
	return 0;
}


int i915_gpu_idle(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct intel_ring_buffer *ring;
	int ret, i;

	/* Flush everything onto the inactive list. */
	for_each_ring(ring, dev_priv, i) {
		ret = i915_switch_context(ring, NULL, DEFAULT_CONTEXT_ID);
		if (ret)
			return ret;

		ret = intel_ring_idle(ring);
		if (ret)
			return ret;
	}

	return 0;
}

static void i965_write_fence_reg(struct drm_device *dev, int reg,
				 struct drm_i915_gem_object *obj)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	int fence_reg;
	int fence_pitch_shift;

	if (INTEL_INFO(dev)->gen >= 6) {
		fence_reg = FENCE_REG_SANDYBRIDGE_0;
		fence_pitch_shift = SANDYBRIDGE_FENCE_PITCH_SHIFT;
	} else {
		fence_reg = FENCE_REG_965_0;
		fence_pitch_shift = I965_FENCE_PITCH_SHIFT;
	}

	fence_reg += reg * 8;

	/* To w/a incoherency with non-atomic 64-bit register updates,
	 * we split the 64-bit update into two 32-bit writes. In order
	 * for a partial fence not to be evaluated between writes, we
	 * precede the update with write to turn off the fence register,
	 * and only enable the fence as the last step.
	 *
	 * For extra levels of paranoia, we make sure each step lands
	 * before applying the next step.
	 */
	I915_WRITE(fence_reg, 0);
	POSTING_READ(fence_reg);

	if (obj) {
		u32 size = obj->gtt_space->size;
		uint64_t val;

		val = (uint64_t)((obj->gtt_offset + size - 4096) &
				 0xfffff000) << 32;
		val |= obj->gtt_offset & 0xfffff000;
		val |= (uint64_t)((obj->stride / 128) - 1) << fence_pitch_shift;
		if (obj->tiling_mode == I915_TILING_Y)
			val |= 1 << I965_FENCE_TILING_Y_SHIFT;
		val |= I965_FENCE_REG_VALID;

		I915_WRITE(fence_reg + 4, val >> 32);
		POSTING_READ(fence_reg + 4);

		I915_WRITE(fence_reg + 0, val);
		POSTING_READ(fence_reg);
	} else {
		I915_WRITE(fence_reg + 4, 0);
		POSTING_READ(fence_reg + 4);
	}
}

static void i915_write_fence_reg(struct drm_device *dev, int reg,
				 struct drm_i915_gem_object *obj)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	u32 val;

	if (obj) {
		u32 size = obj->gtt_space->size;
		int pitch_val;
		int tile_width;

		if((obj->gtt_offset & ~I915_FENCE_START_MASK) ||
		     (size & -size) != size ||
		     (obj->gtt_offset & (size - 1)))
		     DRM_ERROR("object 0x%08x [fenceable? %d] not 1M or pot-size (0x%08x) aligned\n",
		     obj->gtt_offset, obj->map_and_fenceable, size);

		if (obj->tiling_mode == I915_TILING_Y && HAS_128_BYTE_Y_TILING(dev))
			tile_width = 128;
		else
			tile_width = 512;

		/* Note: pitch better be a power of two tile widths */
		pitch_val = obj->stride / tile_width;
		pitch_val = ffs(pitch_val) - 1;

		val = obj->gtt_offset;
		if (obj->tiling_mode == I915_TILING_Y)
			val |= 1 << I830_FENCE_TILING_Y_SHIFT;
		val |= I915_FENCE_SIZE_BITS(size);
		val |= pitch_val << I830_FENCE_PITCH_SHIFT;
		val |= I830_FENCE_REG_VALID;
	} else
		val = 0;

	if (reg < 8)
		reg = FENCE_REG_830_0 + reg * 4;
	else
		reg = FENCE_REG_945_8 + (reg - 8) * 4;

	I915_WRITE(reg, val);
	POSTING_READ(reg);
}

static void i830_write_fence_reg(struct drm_device *dev, int reg,
				struct drm_i915_gem_object *obj)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	uint32_t val;

	if (obj) {
		u32 size = obj->gtt_space->size;
		uint32_t pitch_val;

		if((obj->gtt_offset & ~I830_FENCE_START_MASK) ||
		     (size & -size) != size ||
		     (obj->gtt_offset & (size - 1)))
		     DRM_ERROR("object 0x%08x not 512K or pot-size 0x%08x aligned\n",
		     obj->gtt_offset, size);

		pitch_val = obj->stride / 128;
		pitch_val = ffs(pitch_val) - 1;

		val = obj->gtt_offset;
		if (obj->tiling_mode == I915_TILING_Y)
			val |= 1 << I830_FENCE_TILING_Y_SHIFT;
		val |= I830_FENCE_SIZE_BITS(size);
		val |= pitch_val << I830_FENCE_PITCH_SHIFT;
		val |= I830_FENCE_REG_VALID;
	} else
		val = 0;

	I915_WRITE(FENCE_REG_830_0 + reg * 4, val);
	POSTING_READ(FENCE_REG_830_0 + reg * 4);
}

inline static bool i915_gem_object_needs_mb(struct drm_i915_gem_object *obj)
{
	return obj && obj->base.read_domains & I915_GEM_DOMAIN_GTT;
}

static void i915_gem_write_fence(struct drm_device *dev, int reg,
				 struct drm_i915_gem_object *obj)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	/* Ensure that all CPU reads are completed before installing a fence
	 * and all writes before removing the fence.
	 */
	if (i915_gem_object_needs_mb(dev_priv->fence_regs[reg].obj))
		membar_producer();

	if(obj && (!obj->stride || !obj->tiling_mode))
		DRM_ERROR("bogus fence setup with stride: 0x%x, tiling mode: %i\n",
			obj->stride, obj->tiling_mode);

	switch (INTEL_INFO(dev)->gen) {
	case 7:
	case 6:
	case 5:
	case 4: i965_write_fence_reg(dev, reg, obj); break;
	case 3: i915_write_fence_reg(dev, reg, obj); break;
	case 2: i830_write_fence_reg(dev, reg, obj); break;
	default: BUG();
	}

	/* And similarly be paranoid that no direct access to this region
	 * is reordered to before the fence is installed.
	 */
	if (i915_gem_object_needs_mb(obj))
		membar_producer();
}

static inline int fence_number(struct drm_i915_private *dev_priv,
			       struct drm_i915_fence_reg *fence)
{
	return fence - dev_priv->fence_regs;
}

static void i915_gem_object_update_fence(struct drm_i915_gem_object *obj,
					 struct drm_i915_fence_reg *fence,
					 bool enable)
{
	struct drm_i915_private *dev_priv = obj->base.dev->dev_private;
	int reg = fence_number(dev_priv, fence);

	i915_gem_write_fence(obj->base.dev, reg, enable ? obj : NULL);

	if (enable) {
		obj->fence_reg = reg;
		fence->obj = obj;
		list_move_tail(&fence->lru_list, &dev_priv->mm.fence_list, (caddr_t)fence);
	} else {
		obj->fence_reg = I915_FENCE_REG_NONE;
		fence->obj = NULL;
		list_del_init(&fence->lru_list);
	}
	obj->fence_dirty = false;
}

static int
i915_gem_object_wait_fence(struct drm_i915_gem_object *obj)
{
	if (obj->last_fenced_seqno) {
		int ret = i915_wait_seqno(obj->ring, obj->last_fenced_seqno);
		if (ret)
			return ret;

		obj->last_fenced_seqno = 0;
	}

	obj->fenced_gpu_access = false;
	return 0;
}

int
i915_gem_object_put_fence(struct drm_i915_gem_object *obj)
{
	struct drm_i915_private *dev_priv = obj->base.dev->dev_private;
	struct drm_i915_fence_reg *fence;
	int ret;

	ret = i915_gem_object_wait_fence(obj);
	if (ret)
		return ret;

	if (obj->fence_reg == I915_FENCE_REG_NONE)
		return 0;

	fence = &dev_priv->fence_regs[obj->fence_reg];

	i915_gem_object_fence_lost(obj);
	i915_gem_object_update_fence(obj, fence, false);

	return 0;
}

static struct drm_i915_fence_reg *
i915_find_fence_reg(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_i915_fence_reg *reg, *avail;
	int i;

	/* First try to find a free reg */
	avail = NULL;
	for (i = dev_priv->fence_reg_start; i < dev_priv->num_fence_regs; i++) {
		reg = &dev_priv->fence_regs[i];
		if (!reg->obj)
			return reg;

		if (!reg->pin_count)
			avail = reg;
	}

	if (avail == NULL)
		return NULL;

	/* None available, try to steal one or wait for a user to finish */
	list_for_each_entry(reg, struct drm_i915_fence_reg, &dev_priv->mm.fence_list, lru_list) {
		if (reg->pin_count)
			continue;

		return reg;
	}

	return NULL;
}

/**
 * i915_gem_object_get_fence_reg - set up a fence reg for an object
 * @obj: object to map through a fence reg
 *
 * When mapping objects through the GTT, userspace wants to be able to write
 * to them without having to worry about swizzling if the object is tiled.
 * This function walks the fence regs looking for a free one for @obj,
 * stealing one if it can't find any.
 *
 * It then sets up the reg based on the object's properties: address, pitch
 * and tiling format.
 *
 * For an untiled surface, this removes any existing fence.
 */
int
i915_gem_object_get_fence(struct drm_i915_gem_object *obj)
{
	struct drm_device *dev = obj->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	bool enable = obj->tiling_mode != I915_TILING_NONE;
	struct drm_i915_fence_reg *reg;
	int ret;

	/* Have we updated the tiling parameters upon the object and so
	 * will need to serialise the write to the associated fence register?
	 */
	if (obj->fence_dirty) {
		ret = i915_gem_object_wait_fence(obj);
		if (ret)
			return ret;
	}

	/* Just update our place in the LRU if our fence is getting reused. */
	if (obj->fence_reg != I915_FENCE_REG_NONE) {
		reg = &dev_priv->fence_regs[obj->fence_reg];
		if (!obj->fence_dirty) {
			list_move_tail(&reg->lru_list,
				       &dev_priv->mm.fence_list, (caddr_t)reg);
			return 0;
		}
	} else if (enable) {
		reg = i915_find_fence_reg(dev);
		if (reg == NULL)
			return -EDEADLK;

		if (reg->obj) {
			struct drm_i915_gem_object *old = reg->obj;

			ret = i915_gem_object_wait_fence(old);
			if (ret)
				return ret;

			i915_gem_object_fence_lost(old);
		}
	} else
		return 0;

	i915_gem_object_update_fence(obj, reg, enable);

	return 0;
}

static bool i915_gem_valid_gtt_space(struct drm_device *dev,
				     struct drm_mm_node *gtt_space,
				     unsigned long cache_level)
{
	struct drm_mm_node *other;

	/* On non-LLC machines we have to be careful when putting differing
	 * types of snoopable memory together to avoid the prefetcher
	 * crossing memory domains and dieing.
	 */
	if (HAS_LLC(dev))
		return true;

	if (gtt_space == NULL)
		return true;

	if (list_empty(&gtt_space->node_list))
		return true;

	other = list_entry(gtt_space->node_list.prev, struct drm_mm_node, node_list);
	if (other->allocated && !other->hole_follows && other->color != cache_level)
		return false;

	other = list_entry(gtt_space->node_list.next, struct drm_mm_node, node_list);
	if (other->allocated && !gtt_space->hole_follows && other->color != cache_level)
		return false;

	return true;
}

static void i915_gem_verify_gtt(struct drm_device *dev)
{
#if WATCH_GTT
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_i915_gem_object *obj;
	int err = 0;

	list_for_each_entry(obj, struct drm_i915_gem_object, &dev_priv->mm.gtt_list, global_list) {
		if (obj->gtt_space == NULL) {
			DRM_ERROR("object found on GTT list with no space reserved\n");
			err++;
			continue;
		}

		if (obj->cache_level != obj->gtt_space->color) {
			DRM_ERROR("object reserved space [%08lx, %08lx] with wrong color, cache_level=%x, color=%lx\n",
			       obj->gtt_space->start,
			       obj->gtt_space->start + obj->gtt_space->size,
			       obj->cache_level,
			       obj->gtt_space->color);
			err++;
			continue;
		}

		if (!i915_gem_valid_gtt_space(dev,
					      obj->gtt_space,
					      obj->cache_level)) {
			DRM_ERROR("invalid GTT space found at [%08lx, %08lx] - color=%x\n",
			       obj->gtt_space->start,
			       obj->gtt_space->start + obj->gtt_space->size,
			       obj->cache_level);
			err++;
			continue;
		}
	}

	WARN_ON(err);
#endif
}

/**
 * Finds free space in the GTT aperture and binds the object there.
 */
static int
i915_gem_object_bind_to_gtt(struct drm_i915_gem_object *obj,
			    unsigned alignment,
			    bool map_and_fenceable,
			    bool nonblocking)
{
	struct drm_device *dev = obj->base.dev;
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct drm_mm_node *node;
	u32 size, fence_size, fence_alignment, unfenced_alignment;
	bool mappable, fenceable;
	size_t gtt_max = map_and_fenceable ?
		dev_priv->gtt.mappable_end : dev_priv->gtt.total;
	int ret;

	fence_size = i915_gem_get_gtt_size(dev,
					   obj->base.size,
					   obj->tiling_mode);
	fence_alignment = i915_gem_get_gtt_alignment(dev,
						     obj->base.size,
						     obj->tiling_mode, true);
	unfenced_alignment =
		i915_gem_get_gtt_alignment(dev,
					    obj->base.size,
					    obj->tiling_mode, false);

	if (alignment == 0)
		alignment = map_and_fenceable ? fence_alignment :
						unfenced_alignment;
	if (map_and_fenceable && alignment & (fence_alignment - 1)) {
		DRM_ERROR("Invalid object alignment requested %u\n", alignment);
		return -EINVAL;
	}

	size = map_and_fenceable ? fence_size : obj->base.size;

	/* If the object is bigger than the entire aperture, reject it early
	 * before evicting everything in a vain attempt to find space.
	 */
	if (obj->base.size > gtt_max) {
		DRM_ERROR("Attempting to bind an object larger than the aperture: object=%zd > %s aperture=%zu\n",
			  obj->base.size,
			  map_and_fenceable ? "mappable" : "total",
			  gtt_max);
		return -E2BIG;
	}

	ret = i915_gem_object_get_pages(obj);
	if (ret)
		return ret;

	i915_gem_object_pin_pages(obj);

	node = kzalloc(sizeof(*node), GFP_KERNEL);
	if (node == NULL) {
		i915_gem_object_unpin_pages(obj);
		return -ENOMEM;
	}

search_free:
	ret = drm_mm_insert_node_in_range_generic(&dev_priv->mm.gtt_space, node,
						  size, alignment,
						  obj->cache_level, 0, gtt_max);
	if (ret) {
		ret = i915_gem_evict_something(dev, size, alignment,
					       obj->cache_level,
					       map_and_fenceable,
					       nonblocking);
		if (ret == 0)
			goto search_free;

		i915_gem_object_unpin_pages(obj);
		kfree(node, sizeof(*node));
		return ret;
	}
	if ((!i915_gem_valid_gtt_space(dev,
					      node,
					      obj->cache_level))) {
		i915_gem_object_unpin_pages(obj);
		drm_mm_put_block(node);
		return -EINVAL;
	}

	ret = i915_gem_gtt_prepare_object(obj);
	if (ret) {
		i915_gem_object_unpin_pages(obj);
		drm_mm_put_block(node);
			return ret;
	}

	list_move_tail(&obj->global_list, &dev_priv->mm.bound_list, (caddr_t)obj);
	list_add_tail(&obj->mm_list, &dev_priv->mm.inactive_list, (caddr_t)obj);

	obj->gtt_space = node;
	obj->gtt_offset = node->start;

	fenceable =
		node->size == fence_size &&
		(node->start & (fence_alignment - 1)) == 0;

	mappable =
		obj->gtt_offset + obj->base.size <= dev_priv->gtt.mappable_end;

	obj->map_and_fenceable = mappable && fenceable;

	TRACE_GEM_OBJ_HISTORY(obj, "bind gtt");
	i915_gem_verify_gtt(dev);
	return 0;
}

void
i915_gem_clflush_object(struct drm_i915_gem_object *obj)
{
	/* If we don't have a page list set up, then we're not pinned
	 * to GPU, and we can ignore the cache flush because it'll happen
	 * again at bind time.
	 */
	if (obj->page_list == NULL)
		return;

	/*
	 * Stolen memory is always coherent with the GPU as it is explicitly
	 * marked as wc by the system, or the system is cache-coherent.
	 */
	if (obj->stolen)
		return;

	/* If the GPU is snooping the contents of the CPU cache,
	 * we do not need to manually clear the CPU cache lines.  However,
	 * the caches are only snooped when the render cache is
	 * flushed/invalidated.  As we always have to emit invalidations
	 * and flushes when moving into and out of the RENDER domain, correct
	 * snooping behaviour occurs naturally as the result of our domain
	 * tracking.
	 */
	if (obj->cache_level != I915_CACHE_NONE)
		return;

	drm_clflush_pages(obj->page_list, obj->base.size / PAGE_SIZE);
	TRACE_GEM_OBJ_HISTORY(obj, "clflush");
}

/** Flushes the GTT write domain for the object if it's dirty. */
static void
i915_gem_object_flush_gtt_write_domain(struct drm_i915_gem_object *obj)
{
	if (obj->base.write_domain != I915_GEM_DOMAIN_GTT)
		return;

	/* No actual flushing is required for the GTT write domain.   Writes
	 * to it immediately go to main memory as far as we know, so there's
	 * no chipset flush.  It also doesn't land in render cache.
	 *
	 * However, we do have to enforce the order so that all writes through
	 * the GTT land before any writes to the device, such as updates to
	 * the GATT itself.
	 */
	membar_producer();

	obj->base.write_domain = 0;
}

/** Flushes the CPU write domain for the object if it's dirty. */
static void
i915_gem_object_flush_cpu_write_domain(struct drm_i915_gem_object *obj)
{
	struct drm_device *dev = obj->base.dev;

	if (obj->base.write_domain != I915_GEM_DOMAIN_CPU)
		return;

	i915_gem_clflush_object(obj);
	i915_gem_chipset_flush(dev);
	obj->base.write_domain = 0;
}

/**
 * Moves a single object to the GTT read, and possibly write domain.
 *
 * This function returns when the move is complete, including waiting on
 * flushes to occur.
 */
int
i915_gem_object_set_to_gtt_domain(struct drm_i915_gem_object *obj, int write)
{
	drm_i915_private_t *dev_priv = obj->base.dev->dev_private;
	int ret;

	/* Not valid to be called on unbound objects. */
	if (obj->gtt_space == NULL)
		return -EINVAL;

	if (obj->base.write_domain == I915_GEM_DOMAIN_GTT)
		return 0;

	ret = i915_gem_object_wait_rendering(obj, !write);
	if (ret)
		return ret;

	i915_gem_object_flush_cpu_write_domain(obj);

	/* Serialise direct access to this object with the barriers for
	 * coherent writes from the GPU, by effectively invalidating the
	 * GTT domain upon first access.
	 */
	if ((obj->base.read_domains & I915_GEM_DOMAIN_GTT) == 0)
		membar_producer();

	/* It should now be out of any other write domains, and we can update
	 * the domain values for our changes.
	 */
	/* GPU reset can handle this error */
//	BUG_ON((obj->base.write_domain & ~I915_GEM_DOMAIN_GTT) != 0);
	obj->base.read_domains |= I915_GEM_DOMAIN_GTT;
	if (write) {
		obj->base.read_domains = I915_GEM_DOMAIN_GTT;
		obj->base.write_domain = I915_GEM_DOMAIN_GTT;
		obj->dirty = 1;
	}

	/* And bump the LRU for this access */
	if (i915_gem_object_is_inactive(obj))
		list_move_tail(&obj->mm_list, &dev_priv->mm.inactive_list, (caddr_t)obj);

	return 0;
}

int i915_gem_object_set_cache_level(struct drm_i915_gem_object *obj,
				    enum i915_cache_level cache_level)
{
	struct drm_device *dev = obj->base.dev;
	drm_i915_private_t *dev_priv = dev->dev_private;
	int ret;

	if (obj->cache_level == cache_level)
		return 0;

	if (obj->pin_count) {
		DRM_DEBUG("can not change the cache level of pinned objects\n");
		return -EBUSY;
	}

	if (!i915_gem_valid_gtt_space(dev, obj->gtt_space, cache_level)) {
		ret = i915_gem_object_unbind(obj, true);
		if (ret)
			return ret;
	}

	if (obj->gtt_space) {
		ret = i915_gem_object_finish_gpu(obj);
		if (ret)
			return ret;

		i915_gem_object_finish_gtt(obj);

		/* Before SandyBridge, you could not use tiling or fence
		 * registers with snooped memory, so relinquish any fences
		 * currently pointing to our region in the aperture.
		 */
		if (INTEL_INFO(dev)->gen < 6) {
			ret = i915_gem_object_put_fence(obj);
			if (ret)
				return ret;
		}

		if (obj->has_global_gtt_mapping)
			i915_gem_gtt_bind_object(obj, cache_level);
		if (obj->has_aliasing_ppgtt_mapping)
			i915_ppgtt_bind_object(dev_priv->mm.aliasing_ppgtt,
					       obj, cache_level);

		obj->gtt_space->color = cache_level;
	}

	if (cache_level == I915_CACHE_NONE) {
		/* If we're coming from LLC cached, then we haven't
		 * actually been tracking whether the data is in the
		 * CPU cache or not, since we only allow one bit set
		 * in obj->write_domain and have been skipping the clflushes.
		 * Just set it to the CPU cache for now.
		 */
		WARN_ON(obj->base.write_domain & ~I915_GEM_DOMAIN_CPU);
		WARN_ON(obj->base.read_domains & ~I915_GEM_DOMAIN_CPU);

		obj->base.read_domains = I915_GEM_DOMAIN_CPU;
		obj->base.write_domain = I915_GEM_DOMAIN_CPU;
	}

	obj->cache_level = cache_level;
	i915_gem_verify_gtt(dev);
	return 0;
}

int i915_gem_get_caching_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_i915_gem_caching *args = data;
	struct drm_i915_gem_object *obj;
	int ret;

	ret = i915_mutex_lock_interruptible(dev);
	if (ret)
		return ret;

	obj = to_intel_bo(drm_gem_object_lookup(dev, file, args->handle));
	if (&obj->base == NULL) {
		ret = -ENOENT;
		goto unlock;
	}

	args->caching = obj->cache_level != I915_CACHE_NONE;

	drm_gem_object_unreference(&obj->base);
unlock:
	mutex_unlock(&dev->struct_mutex);
	return ret;
}

int i915_gem_set_caching_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_i915_gem_caching *args = data;
	struct drm_i915_gem_object *obj;
	enum i915_cache_level level;
	int ret;

	switch (args->caching) {
	case I915_CACHING_NONE:
		level = I915_CACHE_NONE;
		break;
	case I915_CACHING_CACHED:
		level = I915_CACHE_LLC;
		break;
	default:
		return -EINVAL;
	}

	ret = i915_mutex_lock_interruptible(dev);
	if (ret)
		return ret;

	obj = to_intel_bo(drm_gem_object_lookup(dev, file, args->handle));
	if (&obj->base == NULL) {
		ret = -ENOENT;
		goto unlock;
	}

	ret = i915_gem_object_set_cache_level(obj, level);

	drm_gem_object_unreference(&obj->base);
unlock:
	mutex_unlock(&dev->struct_mutex);
	return ret;
}

/*
 * Prepare buffer for display plane (scanout, cursors, etc).
 * Can be called from an uninterruptible phase (modesetting) and allows
 * any flushes to be pipelined (for pageflips).
 */
int
i915_gem_object_pin_to_display_plane(struct drm_i915_gem_object *obj,
				     u32 alignment,
				     struct intel_ring_buffer *pipelined)
{
	/* LINTED */
	u32 old_read_domains, old_write_domain;
	int ret;

	if (pipelined != obj->ring) {
		ret = i915_gem_object_sync(obj, pipelined);
		if (ret)
			return ret;
	}

	/* The display engine is not coherent with the LLC cache on gen6.  As
	 * a result, we make sure that the pinning that is about to occur is
	 * done with uncached PTEs. This is lowest common denominator for all
	 * chipsets.
	 *
	 * However for gen6+, we could do better by using the GFDT bit instead
	 * of uncaching, which would allow us to flush all the LLC-cached data
	 * with that bit in the PTE to main memory with just one PIPE_CONTROL.
	 */
	ret = i915_gem_object_set_cache_level(obj, I915_CACHE_NONE);
	if (ret)
		return ret;

	/* As the user may map the buffer once pinned in the display plane
	 * (e.g. libkms for the bootup splash), we have to ensure that we
	 * always use map_and_fenceable for all scanout buffers.
	 */
	ret = i915_gem_object_pin(obj, alignment, true, false);
	if (ret)
		return ret;

	i915_gem_object_flush_cpu_write_domain(obj);

	old_write_domain = obj->base.write_domain;
	old_read_domains = obj->base.read_domains;

	/* It should now be out of any other write domains, and we can update
	 * the domain values for our changes.
	 */
	obj->base.write_domain = 0;
	obj->base.read_domains |= I915_GEM_DOMAIN_GTT;

	return 0;
}

int
i915_gem_object_finish_gpu(struct drm_i915_gem_object *obj)
{
	int ret;

	if ((obj->base.read_domains & I915_GEM_GPU_DOMAINS) == 0)
		return 0;

	ret = i915_gem_object_wait_rendering(obj, false);
	if (ret)
		return ret;

	/* Ensure that we invalidate the GPU's caches and TLBs. */
	obj->base.read_domains &= ~I915_GEM_GPU_DOMAINS;
	return 0;
}

/**
 * Moves a single object to the CPU read, and possibly write domain.
 *
 * This function returns when the move is complete, including waiting on
 * flushes to occur.
 */
int
i915_gem_object_set_to_cpu_domain(struct drm_i915_gem_object *obj, bool write)
{
	/* LINTED */
	uint32_t old_write_domain, old_read_domains;
	int ret;

	if (obj->base.write_domain == I915_GEM_DOMAIN_CPU)
		return 0;

	ret = i915_gem_object_wait_rendering(obj, !write);
	if (ret)
		return ret;

	i915_gem_object_flush_gtt_write_domain(obj);

	old_write_domain = obj->base.write_domain;
	old_read_domains = obj->base.read_domains;

	/* Flush the CPU cache if it's still invalid. */
	if ((obj->base.read_domains & I915_GEM_DOMAIN_CPU) == 0) {
		i915_gem_clflush_object(obj);

		obj->base.read_domains |= I915_GEM_DOMAIN_CPU;
	}

	/* It should now be out of any other write domains, and we can update
	 * the domain values for our changes.
	 */
	BUG_ON((obj->base.write_domain & ~I915_GEM_DOMAIN_CPU) != 0);

	/* If we're writing through the CPU, then the GPU read domains will
	 * need to be invalidated at next use.
	 */
	if (write) {
		obj->base.read_domains = I915_GEM_DOMAIN_CPU;
		obj->base.write_domain = I915_GEM_DOMAIN_CPU;
	}

	return 0;
}

/* Throttle our rendering by waiting until the ring has completed our requests
 * emitted over 20 msec ago.
 *
 * Note that if we were to use the current jiffies each time around the loop,
 * we wouldn't escape the function with any frames outstanding if the time to
 * render a frame was over 20ms.
 *
 * This should get us reasonable parallelism between CPU and GPU but also
 * relatively low latency when blocking on a particular request to finish.
 */
static int
i915_gem_ring_throttle(struct drm_device *dev, struct drm_file *file)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_i915_file_private *file_priv = file->driver_priv;
	unsigned long recent_enough = jiffies - msecs_to_jiffies(20);
	struct drm_i915_gem_request *request;
	struct intel_ring_buffer *ring = NULL;
	unsigned reset_counter;
	u32 seqno = 0;
	int ret;

	ret = i915_gem_wait_for_error(&dev_priv->gpu_error);
	if (ret)
		return ret;

	ret = i915_gem_check_wedge(&dev_priv->gpu_error, false);
	if (ret)
		return ret;
	spin_lock(&file_priv->mm.lock);
	list_for_each_entry(request, struct drm_i915_gem_request, &file_priv->mm.request_list, client_list) {
		if (time_after_eq(request->emitted_jiffies, recent_enough))
			break;

		ring = request->ring;
		seqno = request->seqno;
	}
	reset_counter = atomic_read(&dev_priv->gpu_error.reset_counter);
	spin_unlock(&file_priv->mm.lock);

	if (seqno == 0)
		return 0;

	ret = __wait_seqno(ring, seqno, reset_counter, true, NULL);
	if (ret == 0)
		test_set_timer(&dev_priv->mm.retire_timer, 0);

	return ret;
}

int
i915_gem_object_pin(struct drm_i915_gem_object *obj,
		    uint32_t alignment,
		    bool map_and_fenceable,
		    bool nonblocking)
{
	int ret;

	if ((obj->pin_count == DRM_I915_GEM_OBJECT_MAX_PIN_COUNT))
		return -EBUSY;

	if (obj->gtt_space != NULL) {
		if ((alignment && obj->gtt_offset & (alignment - 1)) ||
		    (map_and_fenceable && !obj->map_and_fenceable)) {
			DRM_INFO("bo is already pinned with incorrect alignment:"
			     " offset=%x, req.alignment=%x, req.map_and_fenceable=%d,"
			     " obj->map_and_fenceable=%d\n",
			     obj->gtt_offset, alignment,
			     map_and_fenceable,
			     obj->map_and_fenceable);
			ret = i915_gem_object_unbind(obj, 1);
			if (ret)
				return ret;
		}
	}

	if (obj->gtt_space == NULL) {
		struct drm_i915_private *dev_priv = obj->base.dev->dev_private;

		ret = i915_gem_object_bind_to_gtt(obj, alignment,
						  map_and_fenceable,
						  nonblocking);
		if (ret)
			return ret;

		if (!dev_priv->mm.aliasing_ppgtt)
			i915_gem_gtt_bind_object(obj, obj->cache_level);
	}

	if (!obj->has_global_gtt_mapping && map_and_fenceable)
		i915_gem_gtt_bind_object(obj, obj->cache_level);

	obj->pin_count++;
	obj->pin_mappable |= map_and_fenceable;

	return 0;
}

void
i915_gem_object_unpin(struct drm_i915_gem_object *obj)
{
	BUG_ON(obj->pin_count == 0);
	BUG_ON(obj->gtt_space == NULL);

	if (--obj->pin_count == 0)
		obj->pin_mappable = false;
}

int
/* LINTED */
i915_gem_pin_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_i915_gem_pin *args = data;
	struct drm_i915_gem_object *obj;
	int ret;

	ret = i915_mutex_lock_interruptible(dev);
	if (ret)
		return ret;

	obj = to_intel_bo(drm_gem_object_lookup(dev, file, args->handle));
	if (&obj->base == NULL) {
		ret = -ENOENT;
		goto unlock;
	}

	if (obj->pin_filp != NULL && obj->pin_filp != file) {
		DRM_ERROR("Already pinned in i915_gem_pin_ioctl(): %d\n",
			  args->handle);
		ret = -EINVAL;
		goto out;
	}

	obj->user_pin_count++;
	obj->pin_filp = file;
	if (obj->user_pin_count == 1) {
		ret = i915_gem_object_pin(obj, args->alignment, true, false);
		if (ret)
			goto out;
	}

	/* XXX - flush the CPU caches for pinned objects
	 * as the X server doesn't manage domains yet
	 */
	i915_gem_object_flush_cpu_write_domain(obj);
	args->offset = obj->gtt_offset;
out:
	drm_gem_object_unreference(&obj->base);
unlock:
	mutex_unlock(&dev->struct_mutex);
	return ret;
}

int
/* LINTED */
i915_gem_unpin_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_i915_gem_pin *args = data;
	struct drm_i915_gem_object *obj;
	int ret;

	ret = i915_mutex_lock_interruptible(dev);
	if (ret)
		return ret;

	obj = to_intel_bo(drm_gem_object_lookup(dev, file, args->handle));
	if (&obj->base == NULL) {
		ret = -ENOENT;
		goto unlock;
	}

	if (obj->pin_filp != file) {
		DRM_ERROR("Not pinned by caller in i915_gem_pin_ioctl(): %d\n",
			  args->handle);
		ret = -EINVAL;
		goto out;
	}
	obj->user_pin_count--;
	if (obj->user_pin_count == 0) {
		obj->pin_filp = NULL;
		i915_gem_object_unpin(obj);
	}

out:
	drm_gem_object_unreference(&obj->base);
unlock:
	mutex_unlock(&dev->struct_mutex);
	return ret;
}

int
/* LINTED */
i915_gem_busy_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_i915_gem_busy *args = data;
	struct drm_i915_gem_object *obj;
	int ret;

	ret = i915_mutex_lock_interruptible(dev);
	if (ret)
		return ret;

	obj = to_intel_bo(drm_gem_object_lookup(dev, file, args->handle));
	if (&obj->base == NULL) {
		ret = -ENOENT;
		goto unlock;
	}

	/* Count all active objects as busy, even if they are currently not used
	 * by the gpu. Users of this interface expect objects to eventually
	 * become non-busy without any further actions, therefore emit any
	 * necessary flushes here.
	 */
	ret = i915_gem_object_flush_active(obj);

	args->busy = obj->active;
	if (obj->ring) {
		args->busy |= intel_ring_flag(obj->ring) << 16;
	}

	drm_gem_object_unreference(&obj->base);
unlock:
	mutex_unlock(&dev->struct_mutex);
	return ret;
}

int
/* LINTED */
i915_gem_throttle_ioctl(DRM_IOCTL_ARGS)
{
    return i915_gem_ring_throttle(dev, file);
}

int
/* LINTED */
i915_gem_madvise_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_i915_gem_madvise *args = data;

	/* Don't enable buffer catch */
	args->retained = 0;
	return 0;
}

void i915_gem_object_init(struct drm_i915_gem_object *obj,
			  const struct drm_i915_gem_object_ops *ops)
{
	INIT_LIST_HEAD(&obj->mm_list);
	INIT_LIST_HEAD(&obj->global_list);
	INIT_LIST_HEAD(&obj->ring_list);
	INIT_LIST_HEAD(&obj->exec_list);

	obj->ops = ops;

	obj->fence_reg = I915_FENCE_REG_NONE;
	obj->madv = I915_MADV_WILLNEED;
	/* Avoid an unnecessary call to unbind on the first bind. */
	obj->map_and_fenceable = true;

	i915_gem_info_add_obj(obj->base.dev->dev_private, obj->base.size);
}

static const struct drm_i915_gem_object_ops i915_gem_object_ops = {
	.get_pages = i915_gem_object_get_pages_gtt,
	.put_pages = i915_gem_object_put_pages_gtt,
};

struct drm_i915_gem_object *i915_gem_alloc_object(struct drm_device *dev,
					      size_t size)
{
	struct drm_i915_gem_object *obj;
	int gen;

	obj = kzalloc(sizeof(*obj), GFP_KERNEL);
	if (obj == NULL)
		return NULL;

	if (IS_G33(dev))
		gen = 33;
	else
		gen = INTEL_INFO(dev)->gen * 10;

	if (drm_gem_object_init(dev, &obj->base, size, gen) != 0) {
		kfree(obj, sizeof(*obj));
		DRM_ERROR("failed to init gem object");
		return NULL;
	}


	i915_gem_object_init(obj, &i915_gem_object_ops);

	obj->base.write_domain = I915_GEM_DOMAIN_CPU;
	obj->base.read_domains = I915_GEM_DOMAIN_CPU;

	if (HAS_LLC(dev)) {
		/* On Gen6, we can have the GPU use the LLC (the CPU
		 * cache) for about a 10% performance improvement
		 * compared to uncached.  Graphics requests other than
		 * display scanout are coherent with the CPU in
		 * accessing this cache.  This means in this mode we
		 * don't need to clflush on the CPU side, and on the
		 * GPU side we only need to flush internal caches to
		 * get data visible to the CPU.
		 *
		 * However, we maintain the display planes as UC, and so
		 * need to rebind when first used as such.
		 */
		obj->cache_level = I915_CACHE_LLC;
	} else
		obj->cache_level = I915_CACHE_NONE;

	return obj;
}

int i915_gem_init_object(struct drm_gem_object *obj)
{
	DRM_ERROR("i915_gem_init_object is not supported, BUG!");
	return 0;
}

void i915_gem_free_object(struct drm_gem_object *gem_obj)
{
	struct drm_i915_gem_object *obj = to_intel_bo(gem_obj);
	struct drm_device *dev = obj->base.dev;
	drm_i915_private_t *dev_priv = dev->dev_private;
	int ret;

	if (obj->phys_obj)
		i915_gem_detach_phys_object(dev, obj);

	obj->pin_count = 0;
	ret = i915_gem_object_unbind(obj, 1);
	if (ret) {
		bool was_interruptible;
		was_interruptible = dev_priv->mm.interruptible;
		dev_priv->mm.interruptible = false;

		WARN_ON(i915_gem_object_unbind(obj, 1));

		dev_priv->mm.interruptible = was_interruptible;
	}

	/* Stolen objects don't hold a ref, but do hold pin count. Fix that up
	 * before progressing. */
	if (obj->stolen)
		i915_gem_object_unpin_pages(obj);

	if (obj->pages_pin_count)
		obj->pages_pin_count = 0;
	i915_gem_object_put_pages(obj);
	if (obj->mmap_offset)
		i915_gem_free_mmap_offset(obj);

//	if (obj->base.import_attach)
//		drm_prime_gem_destroy(&obj->base, NULL);

	i915_gem_info_remove_obj(dev_priv, obj->base.size);

	if (obj->bit_17 != NULL)
		kfree(obj->bit_17, BITS_TO_LONGS(obj->base.size >> PAGE_SHIFT) * sizeof(long));
	drm_gem_object_release(&obj->base);
	kfree(obj, sizeof(*obj));
}

int
i915_gem_idle(struct drm_device *dev, uint32_t type)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	int ret;

	mutex_lock(&dev->struct_mutex);

	if (dev_priv->mm.suspended) {
		mutex_unlock(&dev->struct_mutex);
		return 0;
	}

	ret = i915_gpu_idle(dev);
	if (ret) {
		mutex_unlock(&dev->struct_mutex);
		return ret;
	}
	i915_gem_retire_requests(dev);

	/* Under UMS, be paranoid and evict. */
	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		i915_gem_evict_everything(dev);

	/* Hack!  Don't let anybody do execbuf while we don't control the chip.
	 * We need to replace this with a semaphore, or something.
	 * And not confound mm.suspended!
	 */
	dev_priv->mm.suspended = 1;
	del_timer_sync(&dev_priv->gpu_error.hangcheck_timer);

	i915_kernel_lost_context(dev);
	i915_gem_cleanup_ringbuffer(dev);

	mutex_unlock(&dev->struct_mutex);

	/* Cancel the retire work handler, wait for it to finish if running
	 */
	del_timer_sync(&dev_priv->mm.retire_timer);
	cancel_delayed_work(dev_priv->wq);

	return 0;
}

void i915_gem_l3_remap(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	u32 misccpctl;
	int i;

	if (!HAS_L3_GPU_CACHE(dev))
		return;

	if (!dev_priv->l3_parity.remap_info)
		return;

	misccpctl = I915_READ(GEN7_MISCCPCTL);
	I915_WRITE(GEN7_MISCCPCTL, misccpctl & ~GEN7_DOP_CLOCK_GATE_ENABLE);
	POSTING_READ(GEN7_MISCCPCTL);

	for (i = 0; i < GEN7_L3LOG_SIZE; i += 4) {
		u32 remap = I915_READ(GEN7_L3LOG_BASE + i);
		if (remap && remap != dev_priv->l3_parity.remap_info[i/4])
			DRM_DEBUG("0x%x was already programmed to %x\n",
				  GEN7_L3LOG_BASE + i, remap);
		if (remap && !dev_priv->l3_parity.remap_info[i/4])
			DRM_DEBUG_DRIVER("Clearing remapped register\n");
		I915_WRITE(GEN7_L3LOG_BASE + i, dev_priv->l3_parity.remap_info[i/4]);
	}

	/* Make sure all the writes land before disabling dop clock gating */
	POSTING_READ(GEN7_L3LOG_BASE);

	I915_WRITE(GEN7_MISCCPCTL, misccpctl);
}

void i915_gem_init_swizzling(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;

	if (INTEL_INFO(dev)->gen < 5 ||
	    dev_priv->mm.bit_6_swizzle_x == I915_BIT_6_SWIZZLE_NONE)
		return;

	I915_WRITE(DISP_ARB_CTL, I915_READ(DISP_ARB_CTL) |
				 DISP_TILE_SURFACE_SWIZZLING);

	if (IS_GEN5(dev))
		return;

	I915_WRITE(TILECTL, I915_READ(TILECTL) | TILECTL_SWZCTL);
	if (IS_GEN6(dev))
		I915_WRITE(ARB_MODE, _MASKED_BIT_ENABLE(ARB_MODE_SWIZZLE_SNB));
	else if (IS_GEN7(dev))
		I915_WRITE(ARB_MODE, _MASKED_BIT_ENABLE(ARB_MODE_SWIZZLE_IVB));
	/* LINTED */
	else
		BUG();
}

static bool
intel_enable_blt(struct drm_device *dev)
{
	if (!HAS_BLT(dev))
		return false;

	return true;
}

static int i915_gem_init_rings(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int ret;

	ret = intel_init_render_ring_buffer(dev);
	if (ret)
		return ret;

	if (HAS_BSD(dev)) {
		ret = intel_init_bsd_ring_buffer(dev);
		if (ret)
			goto cleanup_render_ring;
	}

	if (intel_enable_blt(dev)) {
		ret = intel_init_blt_ring_buffer(dev);
		if (ret)
			goto cleanup_bsd_ring;
	}

	if (HAS_VEBOX(dev)) {
		ret = intel_init_vebox_ring_buffer(dev);
		if (ret)
			goto cleanup_blt_ring;
	}


	ret = i915_gem_set_seqno(dev, ((u32)~0 - 0x1000));
	if (ret)
		goto cleanup_vebox_ring;

	return 0;

cleanup_vebox_ring:
	intel_cleanup_ring_buffer(&dev_priv->ring[VECS]);
cleanup_blt_ring:
	intel_cleanup_ring_buffer(&dev_priv->ring[BCS]);
cleanup_bsd_ring:
	intel_cleanup_ring_buffer(&dev_priv->ring[VCS]);
cleanup_render_ring:
	intel_cleanup_ring_buffer(&dev_priv->ring[RCS]);

	return ret;
}

int
i915_gem_init_hw(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	int ret;

	if (IS_HASWELL(dev) && (I915_READ(0x120010) == 1))
		I915_WRITE(0x9008, I915_READ(0x9008) | 0xf0000);

	if (HAS_PCH_NOP(dev)) {
		u32 temp = I915_READ(GEN7_MSG_CTL);
		temp &= ~(WAIT_FOR_PCH_FLR_ACK | WAIT_FOR_PCH_RESET_ACK);
		I915_WRITE(GEN7_MSG_CTL, temp);
	}

	i915_gem_l3_remap(dev);

	i915_gem_init_swizzling(dev);

	ret = i915_gem_init_rings(dev);
	if (ret)
		return ret;

	/*
	 * XXX: There was some w/a described somewhere suggesting loading
	 * contexts before PPGTT.
	 */
	i915_gem_context_init(dev);
	if (dev_priv->mm.aliasing_ppgtt) {
		ret = dev_priv->mm.aliasing_ppgtt->enable(dev);
		if (ret) {
			i915_gem_cleanup_aliasing_ppgtt(dev);
			DRM_INFO("PPGTT enable failed. This is not fatal, but unexpected\n");
		}
	}

	return 0;
}

int i915_gem_init(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int ret;
	int size;

	mutex_lock(&dev->struct_mutex);

	if (IS_VALLEYVIEW(dev)) {
		/* VLVA0 (potential hack), BIOS isn't actually waking us */
		I915_WRITE(VLV_GTLC_WAKE_CTRL, 1);
		if (wait_for((I915_READ(VLV_GTLC_PW_STATUS) & 1) == 1, 10))
			DRM_DEBUG_DRIVER("allow wake ack timed out\n");
	}

	i915_gem_init_global_gtt(dev);

	size = drm_getfb_size(dev);
	dev_priv->fbcon_obj = NULL;
	if (size > 0) {
		/* save original fb GTT */
		dev->old_gtt_size = size;
		dev->old_gtt = kmem_zalloc(dev->old_gtt_size, KM_NOSLEEP);
		intel_rw_gtt(dev, dev->old_gtt_size,
			0, (void *) dev->old_gtt, 0);

		/*
		 * Some BIOSes fail to initialise the GTT, which will cause DMA faults when
		 * the IOMMU is enabled. We need to clear the whole GTT.
		 */
		i915_clean_gtt(dev, size);

		/* workaround: prealloc fb buffer, make sure the start address 0 */
		dev_priv->fbcon_obj = i915_gem_alloc_object(dev, size);
		if (!dev_priv->fbcon_obj) {
			DRM_ERROR("failed to allocate framebuffer");
			mutex_unlock(&dev->struct_mutex);
			teardown_scratch_page(dev);
			return (-ENOMEM);
		}

		/* copy old content to fb buffer */
		(void) memcpy(dev_priv->fbcon_obj->base.kaddr, dev->old_gtt, size);

		/* Flush everything out, we'll be doing GTT only from now on */
		ret = intel_pin_and_fence_fb_obj(dev, dev_priv->fbcon_obj, false);
		if (ret) {
			DRM_ERROR("failed to pin fb ret %d", ret);
			mutex_unlock(&dev->struct_mutex);
			teardown_scratch_page(dev);
			i915_gem_free_object(&dev_priv->fbcon_obj->base);
			return ret;
		}
	}

	dev_priv->mm.interruptible = true;

	ret = i915_gem_init_hw(dev);
	mutex_unlock(&dev->struct_mutex);
	if (ret) {
		i915_gem_cleanup_aliasing_ppgtt(dev);
		return ret;
	}

	/* Allow hardware batchbuffers unless told otherwise, but not for KMS. */
	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		dev_priv->dri1.allow_batchbuffer = 1;
	return 0;
}

void
i915_gem_cleanup_ringbuffer(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct intel_ring_buffer *ring;
	int i;

	for_each_ring(ring, dev_priv, i)
		intel_cleanup_ring_buffer(ring);
}

int
/* LINTED */
i915_gem_entervt_ioctl(DRM_IOCTL_ARGS)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	int ret;

	if (drm_core_check_feature(dev, DRIVER_MODESET))
		return 0;

	if (i915_reset_in_progress(&dev_priv->gpu_error)) {
		DRM_ERROR("Reenabling wedged hardware, good luck\n");
		atomic_set(&dev_priv->gpu_error.reset_counter, 0);
	}

	mutex_lock(&dev->struct_mutex);
	dev_priv->mm.suspended = 0;

	ret = i915_gem_init_hw(dev);
	if (ret != 0) {
		mutex_unlock(&dev->struct_mutex);
		return ret;
	}

	BUG_ON(!list_empty(&dev_priv->mm.active_list));
	mutex_unlock(&dev->struct_mutex);

	ret = drm_irq_install(dev);
	if (ret)
		goto cleanup_ringbuffer;

	return 0;

cleanup_ringbuffer:
	mutex_lock(&dev->struct_mutex);
	i915_gem_cleanup_ringbuffer(dev);
	dev_priv->mm.suspended = 1;
	mutex_unlock(&dev->struct_mutex);

	return ret;
}

int
/* LINTED */
i915_gem_leavevt_ioctl(DRM_IOCTL_ARGS)
{
	if (drm_core_check_feature(dev, DRIVER_MODESET))
		return 0;

	(void ) drm_irq_uninstall(dev);
	return i915_gem_idle(dev, 0);
}

void
i915_gem_lastclose(struct drm_device *dev)
{
	int ret;

	if (drm_core_check_feature(dev, DRIVER_MODESET))
		return;

	ret = i915_gem_idle(dev, 1);
	if (ret)
		DRM_ERROR("failed to idle hardware: %d\n", ret);
}

static void
init_ring_lists(struct intel_ring_buffer *ring)
{
	INIT_LIST_HEAD(&ring->active_list);
	INIT_LIST_HEAD(&ring->request_list);
}

void
i915_gem_load(struct drm_device *dev)
{
	int i;
	drm_i915_private_t *dev_priv = dev->dev_private;

	INIT_LIST_HEAD(&dev_priv->mm.active_list);
	INIT_LIST_HEAD(&dev_priv->mm.inactive_list);
	INIT_LIST_HEAD(&dev_priv->mm.unbound_list);
	INIT_LIST_HEAD(&dev_priv->mm.bound_list);
	INIT_LIST_HEAD(&dev_priv->mm.fence_list);
	for (i = 0; i < I915_NUM_RINGS; i++)
		init_ring_lists(&dev_priv->ring[i]);
	for (i = 0; i < I915_MAX_NUM_FENCES; i++)
		INIT_LIST_HEAD(&dev_priv->fence_regs[i].lru_list);

	INIT_WORK(&dev_priv->mm.retire_work, i915_gem_retire_work_handler);
	setup_timer(&dev_priv->mm.retire_timer, i915_gem_retire_work_timer,
			(void *)dev);

	/* On GEN3 we really need to make sure the ARB C3 LP bit is set */
	if (IS_GEN3(dev)) {
		I915_WRITE(MI_ARB_STATE,
			   _MASKED_BIT_ENABLE(MI_ARB_C3_LP_WRITE_ENABLE));
	}

	dev_priv->relative_constants_mode = I915_EXEC_CONSTANTS_REL_GENERAL;

	/* Old X drivers will take 0-2 for front, back, depth buffers */
	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		dev_priv->fence_reg_start = 3;

	if (INTEL_INFO(dev)->gen >= 7 && !IS_VALLEYVIEW(dev))
		dev_priv->num_fence_regs = 32;
	else if (INTEL_INFO(dev)->gen >= 4 || IS_I945G(dev) || IS_I945GM(dev) || IS_G33(dev))
		dev_priv->num_fence_regs = 16;
	else
		dev_priv->num_fence_regs = 8;

	/* Initialize fence registers to zero */
	INIT_LIST_HEAD(&dev_priv->mm.fence_list);
	i915_gem_restore_fences(dev);

	i915_gem_detect_bit_6_swizzle(dev);
	DRM_INIT_WAITQUEUE(&dev_priv->pending_flip_queue, DRM_INTR_PRI(dev));
	dev_priv->mm.interruptible = true;
}

/*
 * Create a physically contiguous memory object for this object
 * e.g. for cursor + overlay regs
 */
static int i915_gem_init_phys_object(struct drm_device *dev,
				     int id, int size, int align)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct drm_i915_gem_phys_object *phys_obj;
	int ret;

	if (dev_priv->mm.phys_objs[id - 1] || !size)
		return 0;

	phys_obj = kzalloc(sizeof(struct drm_i915_gem_phys_object), GFP_KERNEL);
	if (!phys_obj)
		return -ENOMEM;

	phys_obj->id = id;

	phys_obj->handle = drm_pci_alloc(dev, size, 0, 0xffffffff, 1);
	if (!phys_obj->handle) {
		ret = -ENOMEM;
		goto kfree_obj;
	}

	dev_priv->mm.phys_objs[id - 1] = phys_obj;

	return 0;
kfree_obj:
	kfree(phys_obj, sizeof (struct drm_i915_gem_phys_object));
	return ret;
}

static void i915_gem_free_phys_object(struct drm_device *dev, int id)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct drm_i915_gem_phys_object *phys_obj;

	if (!dev_priv->mm.phys_objs[id - 1])
		return;

	phys_obj = dev_priv->mm.phys_objs[id - 1];
	if (phys_obj->cur_obj) {
		i915_gem_detach_phys_object(dev, phys_obj->cur_obj);
	}

	drm_pci_free(phys_obj->handle);
	kfree(phys_obj, sizeof (struct drm_i915_gem_phys_object));
	dev_priv->mm.phys_objs[id - 1] = NULL;
}

void i915_gem_free_all_phys_object(struct drm_device *dev)
{
	int i;

	for (i = I915_GEM_PHYS_CURSOR_0; i <= I915_MAX_PHYS_OBJECT; i++)
		i915_gem_free_phys_object(dev, i);
}

void i915_gem_detach_phys_object(struct drm_device *dev,
				 struct drm_i915_gem_object *obj)
{
	int i, ret;
	int page_count;

	if (!obj->phys_obj)
		return;

	if (!obj->page_list) {
		ret = i915_gem_object_get_pages_gtt(obj);
		if (ret)
			goto out;
	}

	page_count = obj->base.size / PAGE_SIZE;

	for (i = 0; i < page_count; i++) {
		char *dst = obj->page_list[i];
		char *src = (caddr_t)(obj->phys_obj->handle->vaddr + (i * PAGE_SIZE));

		(void) memcpy(dst, src, PAGE_SIZE);
	}
	drm_clflush_pages(obj->page_list, page_count);
	i915_gem_chipset_flush(dev);

	i915_gem_object_put_pages_gtt(obj);
out:
	obj->phys_obj->cur_obj = NULL;
	obj->phys_obj = NULL;
}

int
i915_gem_attach_phys_object(struct drm_device *dev,
			    struct drm_i915_gem_object *obj,
			    int id,
			    int align)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	int ret = 0;
	int page_count;
	int i;

	if (id > I915_MAX_PHYS_OBJECT)
		return -EINVAL;

	if (obj->phys_obj) {
		if (obj->phys_obj->id == id)
			return 0;
		i915_gem_detach_phys_object(dev, obj);
	}

	/* create a new object */
	if (!dev_priv->mm.phys_objs[id - 1]) {
		ret = i915_gem_init_phys_object(dev, id,
						obj->base.size, align);
		if (ret) {
			DRM_ERROR("failed to init phys object %d size: %lu\n", id, obj->base.size);
			goto out;
		}
	}

	/* bind to the object */
	obj->phys_obj = dev_priv->mm.phys_objs[id - 1];
	obj->phys_obj->cur_obj = obj;

	if (!obj->page_list) {
		ret = i915_gem_object_get_pages_gtt(obj);
		if (ret) {
			DRM_ERROR("failed to get page list\n");
			goto out;
		}
	}

	page_count = obj->base.size / PAGE_SIZE;

	for (i = 0; i < page_count; i++) {
                char *dst = obj->page_list[i];
                char *src = (caddr_t)(obj->phys_obj->handle->vaddr + (i * PAGE_SIZE));
                (void) memcpy(dst, src, PAGE_SIZE);

	}

	i915_gem_object_put_pages_gtt(obj);

	return 0;
out:
	return ret;
}

static int
i915_gem_phys_pwrite(struct drm_device *dev,
		     struct drm_i915_gem_object *obj,
		     struct drm_i915_gem_pwrite *args,
		     /* LINTED */
		     struct drm_file *file_priv)
{
	void *obj_addr;
	int ret;
	char __user *user_data;

	user_data = (char __user *) (uintptr_t) args->data_ptr;
	obj_addr = (void *)(uintptr_t)(obj->phys_obj->handle->vaddr + args->offset);

	DRM_DEBUG("obj_addr %p, %ld\n", obj_addr, args->size);
	ret = DRM_COPY_FROM_USER(obj_addr, user_data, args->size);
	if (ret)
		return -EFAULT;

	i915_gem_chipset_flush(dev);
	return 0;
}

void i915_gem_release(struct drm_device * dev, struct drm_file *file)
{
	struct drm_i915_file_private *file_priv = file->driver_priv;

	file_priv->status = 0;

	mutex_lock(&dev->struct_mutex);
	/* i915_gpu_idle() generates warning message, so just ignore return */
	(void) i915_gpu_idle(dev);
	mutex_unlock(&dev->struct_mutex);

	/* Clean up our request list when the client is going away, so that
	 * later retire_requests won't dereference our soon-to-be-gone
	 * file_priv.
	 */
	spin_lock(&file_priv->mm.lock);
	while (!list_empty(&file_priv->mm.request_list)) {
		struct drm_i915_gem_request *request;

		request = list_first_entry(&file_priv->mm.request_list,
					   struct drm_i915_gem_request,
					   client_list);
		list_del(&request->client_list);
		request->file_priv = NULL;
	}
	spin_unlock(&file_priv->mm.lock);
}
