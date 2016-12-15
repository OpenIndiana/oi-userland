/*
 * Copyright (c) 2012, 2013, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * Copyright © 2008,2010, 2013 Intel Corporation
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
 *    Chris Wilson <chris@chris-wilson.co.uk>
 *
 */

#include "drmP.h"
#include "drm.h"
#include "i915_drm.h"
#include "i915_drv.h"
#include "intel_drv.h"

struct eb_objects {
	int and;
	struct drm_file *file_priv;
};

static struct eb_objects *
eb_create(int size, struct drm_file *file_priv)
{
	struct eb_objects *eb;
	eb = kzalloc(sizeof(struct eb_objects), GFP_KERNEL);
	if (eb == NULL)
		return eb;
	eb->file_priv = file_priv;
	eb->and = size;
	return eb;
}

static void
eb_reset(struct eb_objects *eb)
{
}

static void
eb_add_object(struct eb_objects *eb, struct drm_i915_gem_object *obj)
{
}

static struct drm_i915_gem_object *
eb_get_object(struct eb_objects *eb, unsigned long handle)
{
	return NULL;
}

static void
eb_destroy(struct eb_objects *eb)
{
	kfree(eb, sizeof(struct eb_objects));
}

static inline int use_cpu_reloc(struct drm_i915_gem_object *obj)
{
	return (obj->base.write_domain == I915_GEM_DOMAIN_CPU ||
		!obj->map_and_fenceable ||
		obj->cache_level != I915_CACHE_NONE);
}

static int
i915_gem_execbuffer_relocate_entry(struct drm_i915_gem_object *obj,
				   struct eb_objects *eb,
				   struct drm_i915_gem_relocation_entry *reloc)
{
	struct drm_device *dev = obj->base.dev;
	struct drm_gem_object *target_obj;
	struct drm_i915_gem_object *target_i915_obj;
	uint32_t reloc_val, reloc_offset;
	uint32_t target_offset;
	uint32_t *reloc_entry;
	int ret = -EINVAL;

	target_obj = drm_gem_object_lookup(dev, eb->file_priv,
					   reloc->target_handle);
	if (target_obj == NULL)
		return -ENOENT;

	target_i915_obj = to_intel_bo(target_obj);
	target_offset = target_i915_obj->gtt_offset;

	/* Sandybridge PPGTT errata: We need a global gtt mapping for MI and
	 * pipe_control writes because the gpu doesn't properly redirect them
	 * through the ppgtt for non_secure batchbuffers. */
	if (IS_GEN6(dev) &&
	    reloc->write_domain == I915_GEM_DOMAIN_INSTRUCTION &&
	    !target_i915_obj->has_global_gtt_mapping) {
		i915_gem_gtt_bind_object(target_i915_obj,
					 target_i915_obj->cache_level);
	}

	/* Validate that the target is in a valid r/w GPU domain */
	if (reloc->write_domain & (reloc->write_domain - 1)) {
		DRM_DEBUG("reloc with multiple write domains: "
			  "obj %p target %d offset %d "
			  "read %08x write %08x",
			  obj, reloc->target_handle,
			  (int) reloc->offset,
			  reloc->read_domains,
			  reloc->write_domain);
		goto err;
	}
	if (unlikely((reloc->write_domain | reloc->read_domains)
		     & ~I915_GEM_GPU_DOMAINS)) {
		DRM_DEBUG("reloc with read/write non-GPU domains: "
			  "obj %p target %d offset %d "
			  "read %08x write %08x",
			  obj, reloc->target_handle,
			  (int) reloc->offset,
			  reloc->read_domains,
			  reloc->write_domain);
		goto err;
	}

	target_obj->pending_read_domains |= reloc->read_domains;
	target_obj->pending_write_domain |= reloc->write_domain;

	/* If the relocation already has the right value in it, no
	 * more work needs to be done.
	 */
	if (target_offset == reloc->presumed_offset)
		goto out;

	/* Check that the relocation address is valid... */
	if (reloc->offset > obj->base.size - 4) {
		DRM_ERROR("Relocation beyond object bounds: "
			  "obj %p target %d offset %d size %d.\n",
			  obj, reloc->target_handle,
			  (int) reloc->offset,
			  (int) obj->base.size);
		goto err;
	}
	if (reloc->offset & 3) {
		DRM_ERROR("Relocation not 4-byte aligned: "
			  "obj %p target %d offset %d.\n",
			  obj, reloc->target_handle,
			  (int) reloc->offset);
		goto err;
	}

		ret = i915_gem_object_set_to_gtt_domain(obj, true);
		if (ret)
			return ret;

		ret = i915_gem_object_put_fence(obj);
		if (ret)
			return ret;

	/* Map the page containing the relocation we're going to
	 * perform.
	 */
	int reloc_base = (reloc->offset & ~(PAGE_SIZE-1));
	reloc_offset = reloc->offset & (PAGE_SIZE-1);
	reloc_entry = (uint32_t *)(uintptr_t)(obj->page_list[reloc_base/PAGE_SIZE] + reloc_offset);
	reloc_val = target_offset + reloc->delta;

	*reloc_entry = reloc_val;

	/* and update the user's relocation entry */
	reloc->presumed_offset = target_offset;

out:
	ret = 0;
err:
	drm_gem_object_unreference(target_obj);
	return ret;
}

static int
i915_gem_execbuffer_relocate_object(struct drm_i915_gem_object *obj,
				    struct eb_objects *eb)
{
#define N_RELOC(x) ((x) / sizeof(struct drm_i915_gem_relocation_entry))
	struct drm_i915_gem_relocation_entry stack_reloc[N_RELOC(512)];
	struct drm_i915_gem_relocation_entry __user *user_relocs;
	struct drm_i915_gem_exec_object2 *entry = obj->exec_entry;
	int remain, ret;

	user_relocs = (void __user *)(uintptr_t)entry->relocs_ptr;

	remain = entry->relocation_count;
	while (remain) {
		struct drm_i915_gem_relocation_entry *r = stack_reloc;
		int count = remain;
		if (count > ARRAY_SIZE(stack_reloc))
			count = ARRAY_SIZE(stack_reloc);
		remain -= count;

		if (DRM_COPY_FROM_USER(r, user_relocs, count*sizeof(r[0])))
			return -EFAULT;

		do {
			u64 offset = r->presumed_offset;

			ret = i915_gem_execbuffer_relocate_entry(obj, eb, r);
			if (ret)
				return ret;

			if (r->presumed_offset != offset &&
				DRM_COPY_TO_USER(&user_relocs->presumed_offset,
						    &r->presumed_offset,
						    sizeof(r->presumed_offset))) {
				return -EFAULT;
			}

			user_relocs++;
			r++;
		} while (--count);
	}

	return 0;
#undef N_RELOC
}

static int
i915_gem_execbuffer_relocate_object_slow(struct drm_i915_gem_object *obj,
					 struct eb_objects *eb,
					 struct drm_i915_gem_relocation_entry *relocs)
{
	const struct drm_i915_gem_exec_object2 *entry = obj->exec_entry;
	int i, ret;

	for (i = 0; i < entry->relocation_count; i++) {
		ret = i915_gem_execbuffer_relocate_entry(obj, eb, &relocs[i]);
		if (ret)
			return ret;
	}

	return 0;
}

static int
i915_gem_execbuffer_relocate(struct drm_device *dev,
			     struct eb_objects *eb,
			     struct list_head *objects)
{
	struct drm_i915_gem_object *obj;
	int ret = 0;

	list_for_each_entry(obj, struct drm_i915_gem_object, objects, exec_list) {
		ret = i915_gem_execbuffer_relocate_object(obj, eb);
		if (ret)
			break;
	}
	return ret;
}

#define  __EXEC_OBJECT_HAS_PIN (1UL<<31)
#define  __EXEC_OBJECT_HAS_FENCE (1UL<<30)

static int
need_reloc_mappable(struct drm_i915_gem_object *obj)
{
	struct drm_i915_gem_exec_object2 *entry = obj->exec_entry;
	return entry->relocation_count && !use_cpu_reloc(obj);
}

static int
i915_gem_execbuffer_reserve_object(struct drm_i915_gem_object *obj,
				   struct intel_ring_buffer *ring,
				   bool *need_reloc)
{
	struct drm_i915_private *dev_priv = obj->base.dev->dev_private;
	struct drm_i915_gem_exec_object2 *entry = obj->exec_entry;
	bool has_fenced_gpu_access = INTEL_INFO(ring->dev)->gen < 4;
	bool need_fence, need_mappable;
	int ret;

	need_fence =
		has_fenced_gpu_access &&
		entry->flags & EXEC_OBJECT_NEEDS_FENCE &&
		obj->tiling_mode != I915_TILING_NONE;

	/* workaround for GEN5 for gpu hang with ugnx */
	if (IS_GEN5(ring->dev))
		need_fence = obj->tiling_mode != I915_TILING_NONE;

	need_mappable = need_fence || need_reloc_mappable(obj);

	ret = i915_gem_object_pin(obj, entry->alignment, need_mappable, false);
	if (ret)
		return ret;

	entry->flags |= __EXEC_OBJECT_HAS_PIN;

	if (has_fenced_gpu_access) {
		if (entry->flags & EXEC_OBJECT_NEEDS_FENCE) {
			ret = i915_gem_object_get_fence(obj);
			if (ret)
				return ret;

			if (i915_gem_object_pin_fence(obj))
				entry->flags |= __EXEC_OBJECT_HAS_FENCE;

			obj->pending_fenced_gpu_access = true;
		}
		}

	/* Ensure ppgtt mapping exists if needed */
	if (dev_priv->mm.aliasing_ppgtt && !obj->has_aliasing_ppgtt_mapping) {
		i915_ppgtt_bind_object(dev_priv->mm.aliasing_ppgtt,
				       obj, obj->cache_level);

		obj->has_aliasing_ppgtt_mapping = 1;
	}

	if (entry->offset != obj->gtt_offset) {
		entry->offset = obj->gtt_offset;
		*need_reloc = true;
	}

	if (entry->flags & EXEC_OBJECT_WRITE) {
		obj->base.pending_read_domains = I915_GEM_DOMAIN_RENDER;
		obj->base.pending_write_domain = I915_GEM_DOMAIN_RENDER;
	}

	if (entry->flags & EXEC_OBJECT_NEEDS_GTT &&
	    !obj->has_global_gtt_mapping)
		i915_gem_gtt_bind_object(obj, obj->cache_level);

	return 0;
}

static void
i915_gem_execbuffer_unreserve_object(struct drm_i915_gem_object *obj)
{
	struct drm_i915_gem_exec_object2 *entry;

	if (!obj->gtt_space)
		return;

	entry = obj->exec_entry;

	if (entry->flags & __EXEC_OBJECT_HAS_FENCE)
		i915_gem_object_unpin_fence(obj);

	if (entry->flags & __EXEC_OBJECT_HAS_PIN)
		i915_gem_object_unpin(obj);

	entry->flags &= ~(__EXEC_OBJECT_HAS_FENCE | __EXEC_OBJECT_HAS_PIN);
}

static int
i915_gem_execbuffer_reserve(struct intel_ring_buffer *ring,
			    struct drm_file *file,
			    struct list_head *objects,
			    bool *need_relocs)
{
	struct drm_i915_gem_object *obj;
	struct list_head ordered_objects;
	struct list_head *tmp;
	bool has_fenced_gpu_access = INTEL_INFO(ring->dev)->gen < 4;
	struct drm_i915_gem_object *batch_obj;
	int retry;
	batch_obj = list_entry(objects->prev,
				struct drm_i915_gem_object,
				exec_list);

	INIT_LIST_HEAD(&ordered_objects);
	while (!list_empty(objects)) {
		struct drm_i915_gem_exec_object2 *entry;
		bool need_fence, need_mappable;

		obj = list_first_entry(objects,
				       struct drm_i915_gem_object,
				       exec_list);
		entry = obj->exec_entry;

		need_fence =
			has_fenced_gpu_access &&
			entry->flags & EXEC_OBJECT_NEEDS_FENCE &&
			obj->tiling_mode != I915_TILING_NONE;

		/* workaround for GEN5 for gpu hang with ugnx */
		if (IS_GEN5(ring->dev))
			need_fence = obj->tiling_mode != I915_TILING_NONE;
		need_mappable = need_fence || need_reloc_mappable(obj);

		if (need_mappable)
			list_move(&obj->exec_list, &ordered_objects, (caddr_t)obj);
		else
			list_move_tail(&obj->exec_list, &ordered_objects, (caddr_t)obj);

		obj->base.pending_read_domains = I915_GEM_GPU_DOMAINS & ~I915_GEM_DOMAIN_COMMAND;
		obj->base.pending_write_domain = 0;
		obj->pending_fenced_gpu_access = false;

		if (IS_GEN5(ring->dev) && (batch_obj != obj) && obj->gtt_offset) {
			int err;
			if (obj->tiling_mode != I915_TILING_NONE)
				err = i915_gem_object_get_fence(obj);
			else
				err = i915_gem_object_put_fence(obj);
			if (err)
				DRM_ERROR("failed to get obj 0x%p fence %d", obj, err);
			obj->pending_fenced_gpu_access = true;
		}
	}

	tmp = objects->next;
	list_splice(&ordered_objects, objects, tmp);

	/* Attempt to pin all of the buffers into the GTT.
	 * This is done in 3 phases:
	 *
	 * 1a. Unbind all objects that do not match the GTT constraints for
	 *     the execbuffer (fenceable, mappable, alignment etc).
	 * 1b. Increment pin count for already bound objects.
	 * 2.  Bind new objects.
	 * 3.  Decrement pin count.
	 *
	 * This avoid unnecessary unbinding of later objects in order to makr
	 * room for the earlier objects *unless* we need to defragment.
	 */
	retry = 0;
	do {
		int ret = 0;

		/* Unbind any ill-fitting objects or pin. */
		list_for_each_entry(obj, struct drm_i915_gem_object, objects, exec_list) {
			struct drm_i915_gem_exec_object2 *entry = obj->exec_entry;
			bool need_fence, need_mappable;
			if (!obj->gtt_space)
				continue;
			need_fence =
				has_fenced_gpu_access &&
				entry->flags & EXEC_OBJECT_NEEDS_FENCE &&
				obj->tiling_mode != I915_TILING_NONE;

			/* workaround for GEN5 for gpu hang with ugnx */
			if (IS_GEN5(ring->dev))
				need_fence = obj->tiling_mode != I915_TILING_NONE;
			need_mappable = need_fence || need_reloc_mappable(obj);


			if ((entry->alignment && obj->gtt_offset & (entry->alignment - 1)) ||
			    (need_mappable && !obj->map_and_fenceable))
				ret = i915_gem_object_unbind(obj, 1);
			else
				ret = i915_gem_execbuffer_reserve_object(obj, ring, need_relocs);
			if (ret)
				goto err;
		}

		/* Bind fresh objects */
		list_for_each_entry(obj, struct drm_i915_gem_object, objects, exec_list) {
			if (obj->gtt_space)
				continue;

			ret = i915_gem_execbuffer_reserve_object(obj, ring, need_relocs);
			if (ret)
				goto err;
		}

err:		/* Decrement pin count for bound objects */
		list_for_each_entry(obj, struct drm_i915_gem_object, objects, exec_list)
			i915_gem_execbuffer_unreserve_object(obj);

		if (ret != -ENOSPC || retry++)
			return ret;

		ret = i915_gem_evict_everything(ring->dev);
		if (ret)
			return ret;
	} while (1);
/* LINTED */
}

static int
i915_gem_execbuffer_relocate_slow(struct drm_device *dev,
				  struct drm_i915_gem_execbuffer2 *args,
				  struct drm_file *file,
				  struct intel_ring_buffer *ring,
				  struct list_head *objects,
				  struct eb_objects *eb,
				  struct drm_i915_gem_exec_object2 *exec,
				  int count)
{
	struct drm_i915_gem_relocation_entry *reloc;
	struct drm_i915_gem_object *obj;
	bool need_relocs;
	int *reloc_offset;
	int i, total, ret;

	/* We may process another execbuffer during the unlock... */
	while (!list_empty(objects)) {
		obj = list_first_entry(objects,
				       struct drm_i915_gem_object,
				       exec_list);
		list_del_init(&obj->exec_list);
		drm_gem_object_unreference(&obj->base);
	}

	mutex_unlock(&dev->struct_mutex);

	total = 0;
	for (i = 0; i < count; i++)
		total += exec[i].relocation_count;

	reloc_offset = drm_calloc(count, sizeof(*reloc_offset), DRM_MEM_DRIVER);
	reloc = drm_calloc(total, sizeof(*reloc), DRM_MEM_DRIVER);
	if (reloc == NULL || reloc_offset == NULL) {
	drm_free(reloc, total * sizeof(*reloc), DRM_MEM_DRIVER);
	drm_free(reloc_offset, count * sizeof(*reloc_offset), DRM_MEM_DRIVER);
		mutex_lock(&dev->struct_mutex);
		return -ENOMEM;
	}

	total = 0;
	for (i = 0; i < count; i++) {
		struct drm_i915_gem_relocation_entry __user *user_relocs;

		user_relocs = (void __user *)(uintptr_t)exec[i].relocs_ptr;

		if (copy_from_user(reloc+total, user_relocs,
				   exec[i].relocation_count * sizeof(*reloc))) {
			ret = -EFAULT;
			mutex_lock(&dev->struct_mutex);
			goto err;
		}

		reloc_offset[i] = total;
		total += exec[i].relocation_count;
	}

	ret = i915_mutex_lock_interruptible(dev);
	if (ret) {
		mutex_lock(&dev->struct_mutex);
		goto err;
	}

	/* reacquire the objects */
	eb_reset(eb);
	for (i = 0; i < count; i++) {
		obj = to_intel_bo(drm_gem_object_lookup(dev, file,
							exec[i].handle));
		if (&obj->base == NULL) {
			DRM_DEBUG("Invalid object handle %d at index %d\n",
				   exec[i].handle, i);
			ret = -ENOENT;
			goto err;
		}

		list_add_tail(&obj->exec_list, objects, (caddr_t)obj);
		obj->exec_handle = exec[i].handle;
		obj->exec_entry = &exec[i];
		eb_add_object(eb, obj);
	}

	need_relocs = (args->flags & I915_EXEC_NO_RELOC) == 0;

	ret = i915_gem_execbuffer_reserve(ring, file, objects, &need_relocs);
	if (ret)
		goto err;

	list_for_each_entry(obj, struct drm_i915_gem_object, objects, exec_list) {
		int offset = obj->exec_entry - exec;
		ret = i915_gem_execbuffer_relocate_object_slow(obj, eb,
							       reloc + reloc_offset[offset]);
		if (ret)
			goto err;
	}

	/* Leave the user relocations as are, this is the painfully slow path,
	 * and we want to avoid the complication of dropping the lock whilst
	 * having buffers reserved in the aperture and so causing spurious
	 * ENOSPC for random operations.
	 */

err:
	drm_free(reloc, total * sizeof(*reloc), DRM_MEM_DRIVER);
	drm_free(reloc_offset, count * sizeof(*reloc_offset), DRM_MEM_DRIVER);
	return ret;
}

static int
i915_gem_execbuffer_move_to_gpu(struct intel_ring_buffer *ring,
				struct list_head *objects)
{
	struct drm_i915_gem_object *obj;
	uint32_t flush_domains = 0;
	int ret;

	list_for_each_entry(obj, struct drm_i915_gem_object, objects, exec_list) {
		ret = i915_gem_object_sync(obj, ring);
		if (ret)
			return ret;

		if (obj->base.write_domain & I915_GEM_DOMAIN_CPU)
			i915_gem_clflush_object(obj);

		flush_domains |= obj->base.write_domain;
	}

	if (flush_domains & I915_GEM_DOMAIN_CPU)
		i915_gem_chipset_flush(ring->dev);

	if (flush_domains & I915_GEM_DOMAIN_GTT)
		membar_producer();

	/* Unconditionally invalidate gpu caches and ensure that we do flush
	 * any residual writes from the previous batch.
	 */
	return intel_ring_invalidate_all_caches(ring);
}

static bool
i915_gem_check_execbuffer(struct drm_i915_gem_execbuffer2 *exec)
{
	return ((exec->batch_start_offset | exec->batch_len) & 0x7) == 0;
}

static int
validate_exec_list(struct drm_i915_gem_exec_object2 *exec,
		   int count)
{
	int i;
	int relocs_total = 0;
	int relocs_max = INT_MAX /
	    sizeof(struct drm_i915_gem_relocation_entry);

	for (i = 0; i < count; i++) {
#if 0  /* Should match the if a few lines below */
		char __user *ptr = (char __user *)(uintptr_t)exec[i].relocs_ptr;
		int length; /* limited by fault_in_pages_readable() */
#endif

		/*
		 * First check for malicious input causing overflow in
		 * the worst case where we need to allocate the entire
		 * relocation tree as a single array.
		 */
		if (exec[i].relocation_count>  relocs_max - relocs_total)
			return -EINVAL;
		relocs_total += exec[i].relocation_count;
#if 0
		length = exec[i].relocation_count *
			sizeof(struct drm_i915_gem_relocation_entry);
		if (!access_ok(VERIFY_READ, ptr, length))
			return -EFAULT;

		/* we may also need to update the presumed offsets */
		if (!access_ok(VERIFY_WRITE, ptr, length))
			return -EFAULT;

		if (fault_in_pages_readable(ptr, length))
			return -EFAULT;
#endif
	}

	return 0;
}

static void
i915_gem_execbuffer_move_to_active(struct list_head *objects,
				   struct intel_ring_buffer *ring)
{
	struct drm_i915_gem_object *obj;

	list_for_each_entry(obj, struct drm_i915_gem_object, objects, exec_list) {
		obj->base.write_domain = obj->base.pending_write_domain;
		if (obj->base.write_domain == 0)
			obj->base.pending_read_domains |= obj->base.read_domains;
		obj->base.read_domains = obj->base.pending_read_domains;
		obj->fenced_gpu_access = obj->pending_fenced_gpu_access;

		i915_gem_object_move_to_active(obj, ring);
		if (obj->base.write_domain) {
			obj->dirty = 1;
			obj->last_write_seqno = intel_ring_get_seqno(ring);
			if (obj->pin_count) /* check for potential scanout */
				intel_mark_fb_busy(obj, ring);
		}

	}
}

static void
i915_gem_execbuffer_retire_commands(struct drm_device *dev,
				    struct drm_file *file,
				    struct intel_ring_buffer *ring,
				    struct drm_i915_gem_object *obj)
{
	/* Unconditionally force add_request to emit a full flush. */
	ring->gpu_caches_dirty = true;

	/* Add a breadcrumb for the completion of the batch buffer */
	(void)__i915_add_request(ring, file, obj, NULL);
}

static int
i915_reset_gen7_sol_offsets(struct drm_device *dev,
			    struct intel_ring_buffer *ring)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	int ret, i;

	if (!IS_GEN7(dev) || ring != &dev_priv->ring[RCS])
		return 0;

	ret = intel_ring_begin(ring, 4 * 3);
	if (ret)
		return ret;

	for (i = 0; i < 4; i++) {
		intel_ring_emit(ring, MI_LOAD_REGISTER_IMM(1));
		intel_ring_emit(ring, GEN7_SO_WRITE_OFFSET(i));
		intel_ring_emit(ring, 0);
	}

	intel_ring_advance(ring);

	return 0;
}

static int
/* LINTED */
i915_gem_do_execbuffer(struct drm_device *dev, void *data,
		       struct drm_file *file,
		       struct drm_i915_gem_execbuffer2 *args,
		       struct drm_i915_gem_exec_object2 *exec)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct list_head objects;
	struct eb_objects *eb;
	struct drm_i915_gem_object *batch_obj;
	struct drm_clip_rect *cliprects = NULL;
	struct intel_ring_buffer *ring;
	u32 ctx_id = i915_execbuffer2_get_context_id(*args);
	struct batch_info_list *node;
	u32 exec_start, exec_len;
	u32 mask, flags;
	int ret, mode, i;
	bool need_relocs;

	if (!i915_gem_check_execbuffer(args)) {
		DRM_DEBUG("execbuf with invalid offset/length\n");
		return -EINVAL;
	}

	ret = validate_exec_list(exec, args->buffer_count);
	if (ret)
		return ret;

	flags = 0;
	if (args->flags & I915_EXEC_SECURE) {
		if (!file->is_master)
		    return -EPERM;

		flags |= I915_DISPATCH_SECURE;
	}
	if (args->flags & I915_EXEC_IS_PINNED)
		flags |= I915_DISPATCH_PINNED;

	switch (args->flags & I915_EXEC_RING_MASK) {
	case I915_EXEC_DEFAULT:
	case I915_EXEC_RENDER:
		ring = &dev_priv->ring[RCS];
		break;
	case I915_EXEC_BSD:
		ring = &dev_priv->ring[VCS];
		if (ctx_id != 0) {
			DRM_DEBUG("Ring %s doesn't support contexts\n",
				  ring->name);
			return -EPERM;
		}
		break;
	case I915_EXEC_BLT:
		ring = &dev_priv->ring[BCS];
		if (ctx_id != 0) {
			DRM_DEBUG("Ring %s doesn't support contexts\n",
				  ring->name);
			return -EPERM;
		}
		break;
	case I915_EXEC_VEBOX:
		ring = &dev_priv->ring[VECS];
		if (ctx_id != 0) {
			DRM_DEBUG("Ring %s doesn't support contexts\n",
				  ring->name);
			return -EPERM;
		}
		break;

	default:
		DRM_DEBUG("execbuf with unknown ring: %d\n",
			  (int)(args->flags & I915_EXEC_RING_MASK));
		return -EINVAL;
	}
	if (!intel_ring_initialized(ring)) {
		DRM_DEBUG("execbuf with invalid ring: %d\n",
			  (int)(args->flags & I915_EXEC_RING_MASK));
		return -EINVAL;
	}

	mode = args->flags & I915_EXEC_CONSTANTS_MASK;
	mask = I915_EXEC_CONSTANTS_MASK;
	switch (mode) {
	case I915_EXEC_CONSTANTS_REL_GENERAL:
	case I915_EXEC_CONSTANTS_ABSOLUTE:
	case I915_EXEC_CONSTANTS_REL_SURFACE:
		if (ring == &dev_priv->ring[RCS] &&
		    mode != dev_priv->relative_constants_mode) {
			if (INTEL_INFO(dev)->gen < 4)
				return -EINVAL;

			if (INTEL_INFO(dev)->gen > 5 &&
			    mode == I915_EXEC_CONSTANTS_REL_SURFACE)
				return -EINVAL;

			/* The HW changed the meaning on this bit on gen6 */
			if (INTEL_INFO(dev)->gen >= 6)
				mask &= ~I915_EXEC_CONSTANTS_REL_SURFACE;
		}
		break;
	default:
		DRM_DEBUG("execbuf with unknown constants: %d\n", mode);
		return -EINVAL;
	}

	if (args->buffer_count < 1) {
		DRM_DEBUG("execbuf with %d buffers\n", args->buffer_count);
		return -EINVAL;
	}

	if (args->num_cliprects != 0) {
		if (ring != &dev_priv->ring[RCS]) {
			DRM_DEBUG("clip rectangles are only valid with the render ring\n");
			return -EINVAL;
		}

		if (INTEL_INFO(dev)->gen >= 5) {
			DRM_DEBUG("clip rectangles are only valid on pre-gen5\n");
			return -EINVAL;
		}

		if (args->num_cliprects > UINT_MAX / sizeof(*cliprects)) {
			DRM_DEBUG("execbuf with %u cliprects\n",
				  args->num_cliprects);
			return -EINVAL;
		}

		cliprects = kcalloc(args->num_cliprects, sizeof(*cliprects),
				    GFP_KERNEL);
		if (cliprects == NULL) {
			ret = -ENOMEM;
			goto pre_mutex_err;
		}

		if (DRM_COPY_FROM_USER(cliprects,
				     (struct drm_clip_rect __user *)
				     (uintptr_t) args->cliprects_ptr,
				     sizeof(*cliprects) * args->num_cliprects)) {
			ret = -EFAULT;
			goto pre_mutex_err;
		}
	}

	ret = i915_mutex_lock_interruptible(dev);
	if (ret)
		goto pre_mutex_err;

	if (dev_priv->mm.suspended || dev_priv->gpu_hang) {
		mutex_unlock(&dev->struct_mutex);
		ret = -EBUSY;
		goto pre_mutex_err;
	}

	eb = eb_create(args->buffer_count, file);
	if (eb == NULL) {
		mutex_unlock(&dev->struct_mutex);
		ret = -ENOMEM;
		goto pre_mutex_err;
	}

	if (MDB_TRACK_ENABLE) {
		node = drm_alloc(sizeof (struct batch_info_list), DRM_MEM_MAPS);
		node->num = args->buffer_count;
		node->obj_list = drm_alloc(node->num * sizeof(caddr_t), DRM_MEM_MAPS);
		list_add(&node->head, &dev_priv->batch_list, (caddr_t)node);
	}
	/* Look up object handles */
	INIT_LIST_HEAD(&objects);
	for (i = 0; i < args->buffer_count; i++) {
		struct drm_i915_gem_object *obj;

		obj = to_intel_bo(drm_gem_object_lookup(dev, file,
							exec[i].handle));
		if (&obj->base == NULL) {
			DRM_DEBUG("Invalid object handle %d at index %d\n",
				   exec[i].handle, i);
			/* prevent error path from reading uninitialized data */
			ret = -ENOENT;
			goto err;
		}

		if (!list_empty(&obj->exec_list)) {
			DRM_DEBUG("Object %p [handle %d, index %d] appears more than once in object list\n",
				   obj, exec[i].handle, i);
			ret = -EINVAL;
			goto err;
		}

		list_add_tail(&obj->exec_list, &objects, (caddr_t)obj);
		obj->exec_handle = exec[i].handle;
		obj->exec_entry = &exec[i];
		eb_add_object(eb, obj);

		if (MDB_TRACK_ENABLE)
			node->obj_list[i] = (caddr_t)obj;
		TRACE_GEM_OBJ_HISTORY(obj, "prepare emit");
	}

	/* take note of the batch buffer before we might reorder the lists */
	batch_obj = list_entry(objects.prev,
			       struct drm_i915_gem_object,
			       exec_list);

	/* Move the objects en-masse into the GTT, evicting if necessary. */
	need_relocs = (args->flags & I915_EXEC_NO_RELOC) == 0;
	ret = i915_gem_execbuffer_reserve(ring, file, &objects, &need_relocs);
		if (ret)
			goto err;

	/* The objects are in their final locations, apply the relocations. */
	if (need_relocs)
		ret = i915_gem_execbuffer_relocate(dev, eb, &objects);
	if (ret) {
		if (ret == -EFAULT) {
			ret = i915_gem_execbuffer_relocate_slow(dev, args, file, ring,
								&objects, eb,
								exec,
								args->buffer_count);
			BUG_ON(!mutex_is_locked(&dev->struct_mutex));
		}
		if (ret)
			goto err;
	}

	/* Set the pending read domains for the batch buffer to COMMAND */
	if (batch_obj->base.pending_write_domain) {
		DRM_DEBUG("Attempting to use self-modifying batch buffer\n");
		ret = -EINVAL;
		goto err;
	}
	batch_obj->base.pending_read_domains |= I915_GEM_DOMAIN_COMMAND;

	/* snb/ivb/vlv conflate the "batch in ppgtt" bit with the "non-secure
	 * batch" bit. Hence we need to pin secure batches into the global gtt.
	 * hsw should have this fixed, but let's be paranoid and do it
	 * unconditionally for now. */
	if (flags & I915_DISPATCH_SECURE && !batch_obj->has_global_gtt_mapping)
		i915_gem_gtt_bind_object(batch_obj, batch_obj->cache_level);

	ret = i915_gem_execbuffer_move_to_gpu(ring, &objects);
	if (ret)
		goto err;

	ret = i915_switch_context(ring, file, ctx_id);
	if (ret)
		goto err;

	if (ring == &dev_priv->ring[RCS] &&
	    mode != dev_priv->relative_constants_mode) {
		ret = intel_ring_begin(ring, 4);
		if (ret)
				goto err;

		intel_ring_emit(ring, MI_NOOP);
		intel_ring_emit(ring, MI_LOAD_REGISTER_IMM(1));
		intel_ring_emit(ring, INSTPM);
		intel_ring_emit(ring, mask << 16 | mode);
		intel_ring_advance(ring);

		dev_priv->relative_constants_mode = mode;
	}

	if (args->flags & I915_EXEC_GEN7_SOL_RESET) {
		ret = i915_reset_gen7_sol_offsets(dev, ring);
		if (ret)
			goto err;
	}

	exec_start = batch_obj->gtt_offset + args->batch_start_offset;
	exec_len = args->batch_len;
	if (cliprects) {
		for (i = 0; i < args->num_cliprects; i++) {
			ret = i915_emit_box(dev, &cliprects[i],
					    args->DR1, args->DR4);
			if (ret)
				goto err;

			ret = ring->dispatch_execbuffer(ring,
							exec_start, exec_len,
							flags);
			if (ret)
				goto err;
		}
	} else {
		ret = ring->dispatch_execbuffer(ring,
						exec_start, exec_len,
						flags);
		if (ret)
			goto err;
	}

	i915_gem_execbuffer_move_to_active(&objects, ring);
	i915_gem_execbuffer_retire_commands(dev, file, ring, batch_obj);

err:
	eb_destroy(eb);
	while (!list_empty(&objects)) {
		struct drm_i915_gem_object *obj;

		obj = list_first_entry(&objects,
				       struct drm_i915_gem_object,
				       exec_list);
		TRACE_GEM_OBJ_HISTORY(obj, "finish emit");
		list_del_init(&obj->exec_list);
		drm_gem_object_unreference(&obj->base);
	}

	mutex_unlock(&dev->struct_mutex);

pre_mutex_err:

	drm_free(cliprects, args->num_cliprects * sizeof(*cliprects),
		 DRM_MEM_DRIVER);
	return ret;
}


/*
 * Legacy execbuffer just creates an exec2 list from the original exec object
 * list array and passes it to the real function.
 */
int
/* LINTED */
i915_gem_execbuffer(DRM_IOCTL_ARGS)
{
	struct drm_i915_gem_execbuffer *args = data;
	struct drm_i915_gem_execbuffer2 exec2;
	struct drm_i915_gem_exec_object *exec_list = NULL;
	struct drm_i915_gem_exec_object2 *exec2_list = NULL;
	int ret, i;

	if (args->buffer_count < 1) {
		DRM_DEBUG("execbuf with %d buffers\n", args->buffer_count);
		return -EINVAL;
	}

	/* Copy in the exec list from userland */
	exec_list = drm_calloc(sizeof(*exec_list), args->buffer_count, DRM_MEM_DRIVER);
	exec2_list = drm_calloc(sizeof(*exec2_list), args->buffer_count, DRM_MEM_DRIVER);
	if (exec_list == NULL || exec2_list == NULL) {
		DRM_DEBUG("Failed to allocate exec list for %d buffers\n",
			  args->buffer_count);
		drm_free(exec_list, args->buffer_count * sizeof(*exec_list), DRM_MEM_DRIVER);
		drm_free(exec2_list, args->buffer_count * sizeof(*exec2_list), DRM_MEM_DRIVER);
		return -ENOMEM;
	}
	ret = copy_from_user(exec_list,
			     (struct drm_i915_relocation_entry __user *)
			     (uintptr_t) args->buffers_ptr,
			     sizeof(*exec_list) * args->buffer_count);
	if (ret != 0) {
		DRM_DEBUG("copy %d exec entries failed %d\n",
			  args->buffer_count, ret);
		drm_free(exec_list, args->buffer_count * sizeof(*exec_list), DRM_MEM_DRIVER);
		drm_free(exec2_list, args->buffer_count * sizeof(*exec2_list), DRM_MEM_DRIVER);
		return -EFAULT;
	}

	for (i = 0; i < args->buffer_count; i++) {
		exec2_list[i].handle = exec_list[i].handle;
		exec2_list[i].relocation_count = exec_list[i].relocation_count;
		exec2_list[i].relocs_ptr = exec_list[i].relocs_ptr;
		exec2_list[i].alignment = exec_list[i].alignment;
		exec2_list[i].offset = exec_list[i].offset;
		if (INTEL_INFO(dev)->gen < 4)
			exec2_list[i].flags = EXEC_OBJECT_NEEDS_FENCE;
		else
			exec2_list[i].flags = 0;
	}

	exec2.buffers_ptr = args->buffers_ptr;
	exec2.buffer_count = args->buffer_count;
	exec2.batch_start_offset = args->batch_start_offset;
	exec2.batch_len = args->batch_len;
	exec2.DR1 = args->DR1;
	exec2.DR4 = args->DR4;
	exec2.num_cliprects = args->num_cliprects;
	exec2.cliprects_ptr = args->cliprects_ptr;
	exec2.flags = I915_EXEC_RENDER;
	i915_execbuffer2_set_context_id(exec2, 0);

	ret = i915_gem_do_execbuffer(dev, data, file, &exec2, exec2_list);
	if (!ret) {
		/* Copy the new buffer offsets back to the user's exec list. */
		for (i = 0; i < args->buffer_count; i++)
			exec_list[i].offset = exec2_list[i].offset;
		/* ... and back out to userspace */
		ret = copy_to_user((struct drm_i915_relocation_entry __user *)
				   (uintptr_t) args->buffers_ptr,
				   exec_list,
				   sizeof(*exec_list) * args->buffer_count);
		if (ret) {
			ret = -EFAULT;
			DRM_DEBUG("failed to copy %d exec entries "
				  "back to user (%d)\n",
				  args->buffer_count, ret);
		}
	}

	drm_free(exec_list, args->buffer_count * sizeof(*exec_list), DRM_MEM_DRIVER);
	drm_free(exec2_list, args->buffer_count * sizeof(*exec2_list), DRM_MEM_DRIVER);
	return ret;
}

int
/* LINTED */
i915_gem_execbuffer2(DRM_IOCTL_ARGS)
{
	struct drm_i915_gem_execbuffer2 *args = data;
	struct drm_i915_gem_exec_object2 *exec2_list = NULL;
	int ret;

	if (args->buffer_count < 1 ||
	    args->buffer_count > UINT_MAX / sizeof(*exec2_list)) {
		DRM_DEBUG("execbuf2 with %d buffers\n", args->buffer_count);
		return -EINVAL;
	}

	exec2_list = drm_calloc(sizeof(*exec2_list), args->buffer_count, DRM_MEM_DRIVER);
	if (exec2_list == NULL) {
		DRM_DEBUG("Failed to allocate exec list for %d buffers\n",
			  args->buffer_count);
		return -ENOMEM;
	}
	ret = copy_from_user(exec2_list,
			     (struct drm_i915_relocation_entry __user *)
			     (uintptr_t) args->buffers_ptr,
			     sizeof(*exec2_list) * args->buffer_count);
	if (ret != 0) {
		DRM_DEBUG("copy %d exec entries failed %d\n",
			  args->buffer_count, ret);
		drm_free(exec2_list, args->buffer_count * sizeof(*exec2_list), DRM_MEM_DRIVER);
		return -EFAULT;
	}

	ret = i915_gem_do_execbuffer(dev, data, file, args, exec2_list);
	if (!ret) {
		/* Copy the new buffer offsets back to the user's exec list. */
		ret = copy_to_user((struct drm_i915_relocation_entry __user *)
				   (uintptr_t) args->buffers_ptr,
				   exec2_list,
				   sizeof(*exec2_list) * args->buffer_count);
		if (ret) {
			ret = -EFAULT;
			DRM_DEBUG("failed to copy %d exec entries "
				  "back to user (%d)\n",
				  args->buffer_count, ret);
		}
	}

	drm_free(exec2_list, args->buffer_count * sizeof(*exec2_list), DRM_MEM_DRIVER);
	return ret;
}
