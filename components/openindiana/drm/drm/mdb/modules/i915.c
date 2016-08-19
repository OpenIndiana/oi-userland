/*
 * Copyright (c) 2012, 2013, Intel Corporation.
 * All Rights Reserved.
 */
/*
 * Copyright (c) 2012, 2015, Oracle and/or its affiliates. All rights reserved.
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

#include <sys/mdb_modapi.h>
#include <sys/proc.h>

#include <sys/drm/drmP.h>
#include <i915/src/i915_drv.h>
#include <i915/src/i915_drm.h>
#include <i915/src/intel_drv.h>


/*
 * Defines
 */
/* dcmd options */
#define	ACTIVE_LIST	0x01
#define	INACTIVE_LIST	0x02
#define	BOUND_LIST	0x04
#define	UNBOUND_LIST	0x08

#define	RENDER_RING	0x01
#define	BLT_RING	0x02
#define	BSD_RING	0x04

u32 count, mappable_count, purgeable_count;
size_t size, mappable_size, purgeable_size;

/*
 * Initialize the proc_t walker by either using the given starting address,
 * or reading the value of the kernel's practive pointer.  We also allocate
 * a proc_t for storage, and save this using the walk_data pointer.
 */
static int
head_list_walk_init(mdb_walk_state_t *wsp)
{

	if (wsp->walk_addr == NULL) {
		mdb_warn("head is NULL");
		return (WALK_ERR);
	}

	wsp->walk_data = mdb_alloc(sizeof (struct list_head), UM_SLEEP);

	if (mdb_vread(wsp->walk_data, sizeof (struct list_head),
	    wsp->walk_addr) == -1) {
		mdb_warn("failed to read list head at %p", wsp->walk_addr);
		return (WALK_DONE);
	}

	wsp->walk_arg = (void *)wsp->walk_addr;

	wsp->walk_addr =
	    (uintptr_t)(((struct list_head *)wsp->walk_data)->next);

	return (WALK_NEXT);
}

/*
 * At each step, read a proc_t into our private storage, and then invoke
 * the callback function.  We terminate when we reach a NULL p_next pointer.
 */
static int
head_list_walk_step(mdb_walk_state_t *wsp)
{
	int status;

	if (wsp->walk_addr == NULL) {
		mdb_warn("uncompletement list");
		return (WALK_DONE);
	}

	if (mdb_vread(wsp->walk_data, sizeof (struct list_head),
	    wsp->walk_addr) == -1) {
		mdb_warn("failed to read list at %p", wsp->walk_addr);
		return (WALK_DONE);
	}

	if ((void *)wsp->walk_addr == wsp->walk_arg) {
		return (WALK_DONE);
	}

	status = wsp->walk_callback(wsp->walk_addr, wsp->walk_data,
	    wsp->walk_cbdata);

	wsp->walk_addr =
	    (uintptr_t)(((struct list_head *)wsp->walk_data)->next);
	return (status);
}

/*
 * The walker's fini function is invoked at the end of each walk.  Since we
 * dynamically allocated a proc_t in sp_walk_init, we must free it now.
 */
static void
head_list_walk_fini(mdb_walk_state_t *wsp)
{
	mdb_free(wsp->walk_data, sizeof (proc_t));
}

static int
get_drm_dev(struct drm_device *drm_dev)
{
	uintptr_t i915_ss;
	void *state;
	i_ddi_soft_state *ss;
	uintptr_t array;

	state = mdb_alloc(sizeof (struct drm_device), UM_SLEEP);

	if (mdb_readsym(&i915_ss, sizeof (i915_ss),
	    "i915_statep") == -1) {
		mdb_warn("failed to read i915_statep");
		mdb_free(state, sizeof (struct drm_device));
		return (-1);
	}

	if (mdb_vread(state, sizeof (struct drm_device), i915_ss) == -1) {
		mdb_warn("Failed to read state\n");
		mdb_free(state, sizeof (struct drm_device));
		return (-1);
	}

	ss = (i_ddi_soft_state *) state;

	if (mdb_vread(&array, sizeof (uintptr_t), (uintptr_t)ss->array) == -1) {
		mdb_warn("Failed to read array\n");
		mdb_free(state, sizeof (struct drm_device));
		return (-1);
	}

	if (mdb_vread(drm_dev, sizeof (struct drm_device), array) == -1) {
		mdb_warn("Failed to read drm_dev\n");
		mdb_free(state, sizeof (struct drm_device));
		return (-1);
	}
	mdb_free(state, sizeof (struct drm_device));

	return (DCMD_OK);
}

static int
get_i915_private(struct drm_i915_private *dev_priv)
{
	struct drm_device *drm_dev;
	int ret;

	drm_dev = mdb_alloc(sizeof (struct drm_device), UM_SLEEP);
	ret = get_drm_dev(drm_dev);

	if (ret == DCMD_OK) {
		if (mdb_vread(dev_priv, sizeof (struct drm_i915_private),
		    (uintptr_t)drm_dev->dev_private) == -1) {
			mdb_warn("Failed to read i915 private\n");
			mdb_free(drm_dev, sizeof (struct drm_device));
			return (-1);
		}
	}
	mdb_free(drm_dev, sizeof (struct drm_device));
	return (ret);
}

void
i915_pciid_help(void)
{
	mdb_printf("Print device ID information of Intel graphics card.\n");
}

/* ARGSUSED */
static int
i915_pciid(uintptr_t addr, uint_t flags, int argc, const mdb_arg_t *argv)
{
	int ret;
	struct drm_device *drm_dev;

	if (flags & DCMD_ADDRSPEC) {
		mdb_printf("don't need to set address 0x%lx\n", addr);
		return (DCMD_OK);
	}

	drm_dev = mdb_alloc(sizeof (struct drm_device), UM_SLEEP);

	ret = get_drm_dev(drm_dev);
	if (ret == DCMD_OK)
		mdb_printf(" vendor 0x%x device 0x%x\n",
		    drm_dev->pci_vendor, drm_dev->pci_device);

	mdb_free(drm_dev, sizeof (struct drm_device));
	return (ret);
}

void
i915_gtt_total_help(void)
{
	mdb_printf("Print graphics translation table (GTT) size\n");
}

/* ARGSUSED */
static int
i915_gtt_total(uintptr_t addr, uint_t flags, int argc, const mdb_arg_t *argv)
{
	int ret;
	struct drm_i915_private *dev_priv;

	dev_priv = mdb_alloc(sizeof (struct drm_i915_private), UM_SLEEP);

	ret = get_i915_private(dev_priv);
	if (ret == DCMD_OK) {
		mdb_printf("gtt total size 0x%x", dev_priv->gtt.total);
		mdb_printf("gtt mappable size 0x%x",
		    dev_priv->gtt.mappable_end);
		mdb_printf("gtt stolen size 0x%x", dev_priv->gtt.stolen_size);
	}

	mdb_free(dev_priv, sizeof (struct drm_i915_private));
	return (ret);
}

static const char *get_pin_flag(struct drm_i915_gem_object *obj)
{
	if (obj->user_pin_count > 0)
		return ("P");
	else if (obj->pin_count > 0)
		return ("p");
	else
		return (" ");
}

static const char *get_tiling_flag(struct drm_i915_gem_object *obj)
{
	switch (obj->tiling_mode) {
	default:
	case I915_TILING_NONE: return " ";
	case I915_TILING_X: return "X";
	case I915_TILING_Y: return "Y";
	}
}

static const char *cache_level_str(int type)
{
	switch (type) {
	case I915_CACHE_NONE: return " uncached";
	case I915_CACHE_LLC: return " snooped (LLC)";
	case I915_CACHE_LLC_MLC: return " snooped (LLC+MLC)";
	default: return "";
	}
}

static void
describe_obj(struct drm_i915_gem_object *obj)
{

	mdb_printf("%p: %s%s %8zdKiB %02x %02x %d %d %d%s%s%s",
	    &obj->base,
	    get_pin_flag(obj),
	    get_tiling_flag(obj),
	    obj->base.size / 1024,
	    obj->base.read_domains,
	    obj->base.write_domain,
	    obj->last_read_seqno,
	    obj->last_write_seqno,
	    obj->last_fenced_seqno,
	    cache_level_str(obj->cache_level),
	    obj->dirty ? " dirty" : "",
	    obj->madv == I915_MADV_DONTNEED ? " purgeable" : "");
	if (obj->base.name)
		mdb_printf(" (name: %d)", obj->base.name);
	if (obj->pin_count)
		mdb_printf(" (pinned x %d)", obj->pin_count);
	if (obj->fence_reg != I915_FENCE_REG_NONE)
		mdb_printf(" (fence: %d)", obj->fence_reg);
	if (obj->gtt_space != NULL)
		mdb_printf(" (gtt offset: %08x, size: %08x)",
		    obj->gtt_offset, (unsigned int)obj->base.real_size);
	if (obj->pin_mappable || obj->fault_mappable) {
		char s[3], *t = s;
		if (obj->pin_mappable)
			*t++ = 'p';
		if (obj->fault_mappable)
			*t++ = 'f';
		*t = '\0';
		mdb_printf(" (%s mappable)", s);
	}

}

static void
i915_obj_info(struct drm_i915_gem_object *obj)
{

	/* "size", "gtt_off", "kaddr", "pfn_array" */

	mdb_printf(" 0x%-8x  0x%-8x  0x%lx  0x%lx\n",
	    obj->base.real_size, obj->gtt_offset, obj->base.kaddr,
	    obj->base.pfnarray);

	size += obj->base.real_size;
	++count;
	if (obj->map_and_fenceable) {
		mappable_size += obj->base.real_size;
		++mappable_count;
	}

}

void
i915_obj_list_node_help(void)
{
	mdb_printf("Print objects information for a given list pointer\n"
	"Fields printed:\n"
	"       obj:\tpointer to drm_i915_gem_object structure\n"
	"       size:\tobject size\n"
	"       gtt_off:\tobject offset in GTT (graphics address)\n"
	"       kaddr:\tobject kernel virtual address\n"
	"       pfn_array:\tArrary which contains object's PFN\n");
}

/* ARGSUSED */
static int
i915_obj_list_node(uintptr_t addr, uint_t flags, int argc,
    const mdb_arg_t *argv)
{
	int ret = DCMD_OK;
	struct list_head list;
	struct drm_i915_gem_object *obj;

	if (!(flags & DCMD_ADDRSPEC))
		return (DCMD_USAGE);

	if (mdb_vread(&list, sizeof (struct list), addr) == -1) {
		mdb_warn("failed to read list");
		return (DCMD_ERR);
	}

	if (list.contain_ptr == 0) {
		mdb_warn("no object!");
		return (DCMD_ERR);
	}

	obj = mdb_alloc(sizeof (struct drm_i915_gem_object), UM_SLEEP);
	if (mdb_vread(obj, sizeof (struct drm_i915_gem_object),
	    (uintptr_t)list.contain_ptr) == -1) {
		mdb_warn("failed to read object infor");
		ret = DCMD_ERR;
		goto err;
	}

	mdb_printf("0x%lx ", list.contain_ptr);
	i915_obj_info(obj);

err:
	mdb_free(obj, sizeof (struct drm_i915_gem_object));
	return (ret);
}

static int
obj_walk_list(uintptr_t addr, const char *str)
{
	struct list_head *head;
	int ret = DCMD_OK;

	head = mdb_alloc(sizeof (struct list_head), UM_SLEEP);

	if (mdb_vread(head, sizeof (struct list_head), addr) == -1) {
		mdb_warn("failed to read active_list");
		ret = DCMD_ERR;
		goto err;
	}
	mdb_printf("Dump %s List\n", str);
	mdb_printf("%s %20s %14s %9s %23s\n", "obj", "size", "gtt_off",
	    "kaddr", "pfn_array");

	if (mdb_pwalk_dcmd("head_list", "i915_obj_list_node",
	    0, NULL, (uintptr_t)head->prev) == -1) {
		mdb_warn("failed to walk head_list");
		ret = DCMD_ERR;
		goto err;
	}
err:
	mdb_free(head, sizeof (struct list_head));
	return (ret);
}

void
i915_obj_list_help(void)
{
	mdb_printf("Print object lists information\n"
	    "Fields printed:\n"
	    "       obj:\tpointer to drm_i915_gem_object structure\n"
	    "       size:\tobject size\n"
	    "       gtt_off:\tobject offset in GTT (graphics address)\n"
	    "       kaddr:\tobject kernel virtual address\n"
	    "       pfn_array:\tArrary which contains object's PFN\n"
	    "Options:\n"
	    "       -a flag:\tprint only active list with flag set\n"
	    "       -i flag:\tprint only inactive list with flag set\n"
	    "       -b flag:\tprint only bound list with flag set\n"
	    "       -u flag:\tprint only unbound list with flag set\n"
	    "\nWithout the option, print information about all objects in "
	    "system.\n"
	    "Please make sure mdb_track is enabled in i915 driver by "
	    "mdb_track_enable,\n"
	    "before dump all objects information.\n");
}

/* ARGSUSED */
static int
i915_obj_list(uintptr_t addr, uint_t flags, int argc, const mdb_arg_t *argv)
{
	uint_t	list_flag = 0;
	struct drm_i915_private *dev_priv;
	int ret = DCMD_OK;

	if (flags & DCMD_ADDRSPEC) {
		mdb_printf("don't need to set address 0x%lx, just ignore\n",
		    addr);
	}

	if (mdb_getopts(argc, argv,
	    'a', MDB_OPT_SETBITS, ACTIVE_LIST, &list_flag,
	    'i', MDB_OPT_SETBITS, INACTIVE_LIST, &list_flag,
	    'b', MDB_OPT_SETBITS, BOUND_LIST, &list_flag,
	    'u', MDB_OPT_SETBITS, UNBOUND_LIST, &list_flag, NULL) != argc) {
		mdb_printf("\nUsage:\n"
		    "-a dump active_list\n"
		    "-i dump inactive_list\n"
		    "-b dump bound_list\n"
		    "-u dump unbound_list\n");
		return (DCMD_USAGE);
	}

	dev_priv = mdb_alloc(sizeof (struct drm_i915_private), UM_SLEEP);
	ret = get_i915_private(dev_priv);
	if (ret != DCMD_OK) {
		goto err;
	}

	mdb_printf("%u objects, 0x%lx bytes\n",
	    dev_priv->mm.object_count, dev_priv->mm.object_memory);

	if (list_flag == 0) {
		int mdb_track = 0;
		if (mdb_readvar(&mdb_track, "mdb_track_enable") == -1) {
			mdb_warn("failed to read mdb_track");
			mdb_track = 0;
		}

		if (mdb_track == 0) {
			mdb_printf("mdb_track is not enabled. Please enable "
			    "it by set drm:mdb_track_enable=1");
			goto err;
		}

		/* dump whole gem objects list */
		struct drm_device *drm_dev;
		struct list_head *head;
		drm_dev = mdb_alloc(sizeof (struct drm_device), UM_SLEEP);
		ret = get_drm_dev(drm_dev);
		if (ret != DCMD_OK)
			goto err2;

		head = mdb_alloc(sizeof (struct list_head), UM_SLEEP);
		if (mdb_vread(head, sizeof (struct list_head),
		    (uintptr_t)drm_dev->gem_objects_list.next) == -1) {
			mdb_warn("failed to read whole gem list");
			ret = DCMD_ERR;
			goto err1;
		}

		mdb_printf("Dump %s List\n", "Whole gem objects");
		mdb_printf("%s %20s %14s %9s %23s\n", "obj", "size",
		    "gtt_off", "kaddr", "pfn_array");

		if (mdb_pwalk_dcmd("head_list", "i915_obj_list_node",
		    0, NULL, (uintptr_t)head->prev) == -1) {
			mdb_warn("failed to walk head_list");
			ret = DCMD_ERR;
			goto err;
		}
err1:
		mdb_free(head, sizeof (struct list_head));
err2:
		mdb_free(drm_dev, sizeof (struct drm_device));
		goto err;
	}
	if (list_flag & ACTIVE_LIST) {
		size = count = mappable_size = mappable_count = 0;
		ret = obj_walk_list((uintptr_t)dev_priv->mm.active_list.next,
		    "Activate");
		if (ret != DCMD_OK)
			goto err;
		mdb_printf("  %u [%u] active objects, 0x%lx [0x%lx] bytes\n",
		    count, mappable_count, size, mappable_size);

	}

	if (list_flag & INACTIVE_LIST) {
		size = count = mappable_size = mappable_count = 0;
		ret = obj_walk_list((uintptr_t)dev_priv->mm.inactive_list.next,
		    "Inactivate");
		if (ret != DCMD_OK)
			goto err;
		mdb_printf("  %u [%u] inactive objects, 0x%lx [0x%lx] bytes\n",
		    count, mappable_count, size, mappable_size);
	}

	if (list_flag & BOUND_LIST) {
		size = count = mappable_size = mappable_count = 0;
		ret = obj_walk_list((uintptr_t)dev_priv->mm.bound_list.next,
		    "Bound");
		if (ret != DCMD_OK)
			goto err;
		mdb_printf("%u [%u] objects, 0x%lx [0x%lx] bytes in gtt\n",
		    count, mappable_count, size, mappable_size);

	}

	if (list_flag & UNBOUND_LIST) {
		size = count = purgeable_size = purgeable_count = 0;
		ret = obj_walk_list((uintptr_t)dev_priv->mm.unbound_list.next,
		    "Unbound");
		if (ret != DCMD_OK)
			goto err;
		mdb_printf("%u unbound objects, 0x%lx bytes\n", count, size);
	}

err:
	mdb_free(dev_priv, sizeof (struct drm_i915_private));
	return (ret);
}

void
i915_ringbuffer_info_help(void)
{
	mdb_printf("Print ring object information\n"
	"Fields printed:\n"
	"       mmio_base:\tMMIO base address\n"
	"       obj:\tpointer to ring object's drm_i915_gem_object structure\n"
	"Options:\n"
	"       -l flag:\tprint only BLT ring information with flag set\n"
	"       -r flag:\tprint only RENDER ring information with flag set\n"
	"       -s flag:\tprint only BSD ring information with flag set\n"
	"Without the option given, print information about all rings.\n");
}

/* ARGSUSED */
static int
i915_ringbuffer_info(uintptr_t addr, uint_t flags, int argc,
    const mdb_arg_t *argv)
{
	struct drm_i915_private *dev_priv;
	uint_t  ring_flag = 0;
	int ret = DCMD_OK;

	if (flags & DCMD_ADDRSPEC) {
		mdb_printf("don't need to set address 0x%lx, just ignore\n",
		    addr);
	}

	if (mdb_getopts(argc, argv,
	    'l', MDB_OPT_SETBITS, BLT_RING, &ring_flag,
	    'r', MDB_OPT_SETBITS, RENDER_RING, &ring_flag,
	    's', MDB_OPT_SETBITS, BSD_RING, &ring_flag, NULL) != argc) {
		mdb_printf("\nUsage:\n"
		    "-l blt ring information\n"
		    "-r render ring information\n"
		    "-s bsd ring information\n");
		return (DCMD_USAGE);
	}

	dev_priv = mdb_alloc(sizeof (struct drm_i915_private), UM_SLEEP);
	ret = get_i915_private(dev_priv);
		if (ret != DCMD_OK) {
		goto err;
	}

	if (ring_flag == 0)
		ring_flag = 0xff;

	if (ring_flag & RENDER_RING) {
		mdb_printf("Render ring mmio_base 0x%lx obj 0x%lx\n",
		    dev_priv->ring[0].mmio_base,
		    dev_priv->ring[0].obj);
	}

	if (ring_flag & BLT_RING) {
		mdb_printf("BLT ring mmio_base 0x%lx obj 0x%lx\n",
		    dev_priv->ring[2].mmio_base,
		    dev_priv->ring[2].obj);
	}

	if (ring_flag & BSD_RING) {
		mdb_printf("BSD ring mmio_base 0x%lx obj 0x%lx\n",
		    dev_priv->ring[1].mmio_base,
		    dev_priv->ring[1].obj);
	}

err:
	mdb_free(dev_priv, sizeof (struct drm_i915_private));
	return (ret);
}

void
i915_gtt_dump_help(void)
{
	mdb_printf("Print the address of gtt_dump\n"
	    "\ngtt_dump is a snapshot of whole GTT table when GPU hang "
	    "happened.\n"
	    "Please make sure gpu_dump is enabled in i915 driver before "
	    "using it.\n"
	    "\nSee also: \"::help i915_error_reg_dump\"\n");
}

/* ARGSUSED */
static int
i915_gtt_dump(uintptr_t addr, uint_t flags, int argc, const mdb_arg_t *argv)
{
	struct drm_device *drm_dev;
	int ret = DCMD_OK;

	drm_dev = mdb_alloc(sizeof (struct drm_device), UM_SLEEP);
	ret = get_drm_dev(drm_dev);
	if (ret != DCMD_OK) {
		goto err;
	}

	if (drm_dev->gtt_dump != 0)
		mdb_printf("gtt_dump address 0x%lx\n", drm_dev->gtt_dump);
	else
		mdb_printf("There is no gtt_dump");

err:
	mdb_free(drm_dev, sizeof (struct drm_device));
	return (ret);
}

static uint32_t
i915_read(struct drm_i915_private *dev_priv, uintptr_t addr, uint32_t *val)
{
	struct drm_local_map regs;
	int ret = DCMD_OK;

	if (mdb_vread(&regs, sizeof (struct drm_local_map),
	    (intptr_t)dev_priv->regs) == -1) {
		mdb_warn("Failed to read dev_priv->regs\n");
		ret = DCMD_ERR;
		return (ret);
	}

	if (mdb_pread(val, sizeof (uint32_t),
	    (intptr_t)regs.offset + addr) == -1) {
		mdb_warn("Failed to read register 0x%x\n", addr);
		ret = DCMD_ERR;
		return (ret);
	}

	return (ret);

}

void
i915_register_read_help(void)
{
	mdb_printf("Print register value for a given register offset\n");
}

/* ARGSUSED */
static int
i915_register_read(uintptr_t addr, uint_t flags, int argc,
    const mdb_arg_t *argv)
{
	struct drm_i915_private *dev_priv;
	int ret = DCMD_OK;
	uint32_t val;

	if (!(flags & DCMD_ADDRSPEC)) {
		return (DCMD_USAGE);
	}

	dev_priv = mdb_alloc(sizeof (struct drm_i915_private), UM_SLEEP);
	ret = get_i915_private(dev_priv);
	if (ret != DCMD_OK) {
		goto err;
	}
	ret = i915_read(dev_priv, addr, &val);
	if (ret == DCMD_ERR) {
		goto err;
	}

	mdb_printf("Register [0x%x]: 0x%x\n", addr, val);
err:
	mdb_free(dev_priv, sizeof (struct drm_i915_private));
	return (ret);
}

void
i915_error_reg_dump_help(void)
{
	mdb_printf("Print debug register information\n"
	"Registers printed:\n"
	"       PGTBL_ER:\tPage Table Errors Register\n"
	"       INSTPM:\tCommand Parser Mode Register\n"
	"       EIR:\tError Identity Register\n"
	"       EHR:\tError Header Register\n"
	"       INSTDONE:\tInstruction Stream Interface Done Register\n"
	"       INSTDONE1:\tInstruction Stream Interface Done 1\n"
	"       INSTPS:\tInstruction Parser State Register\n"
	"       ACTHD:\tActive Head Pointer Register\n"
	"       DMA_FADD_P:\tPrimary DMA Engine Fetch Address Register\n"
	"\ngtt_dump is a snapshot of whole GTT table when GPU hang happened.\n"
	"\nSee also: \"::help i915_gtt_dump\"\n");
}

/* ARGSUSED */
static int
i915_error_reg_dump(uintptr_t addr, uint_t flags, int argc,
    const mdb_arg_t *argv)
{
	struct drm_device *dev;
	struct drm_i915_private *dev_priv;
	int ret = DCMD_OK;
	uint32_t val;

	if (flags & DCMD_ADDRSPEC) {
		mdb_printf("don't need to set address 0x%lx\n", addr);
		return (DCMD_OK);
	}

	dev = mdb_alloc(sizeof (struct drm_device), UM_SLEEP);
	ret = get_drm_dev(dev);
	if (ret == DCMD_ERR)
		goto err1;

	dev_priv = mdb_alloc(sizeof (struct drm_i915_private), UM_SLEEP);
	ret = get_i915_private(dev_priv);
	if (ret != DCMD_OK) {
		goto err2;
	}

	ret = i915_read(dev_priv, (uintptr_t)PGTBL_ER, &val);
	if (ret == DCMD_OK)
		mdb_printf("PGTBL_ER: 0x%lx\n", val);

	ret = i915_read(dev_priv, (uintptr_t)INSTPM, &val);
	if (ret == DCMD_OK)
		mdb_printf("INSTPM: 0x%lx\n", val);

	ret = i915_read(dev_priv, (uintptr_t)EIR, &val);
	if (ret == DCMD_OK)
		mdb_printf("EIR: 0x%lx\n", val);

	ret = i915_read(dev_priv, (uintptr_t)ERROR_GEN6, &val);
	if (ret == DCMD_OK)
		mdb_printf("ERROR_GEN6: 0x%lx\n", val);

		mdb_printf("\nBlitter command stream:\n");
	ret = i915_read(dev_priv, (uintptr_t)0x22064, &val);
	if (ret == DCMD_OK)
		mdb_printf("  BLT EIR: 0x%08x\n", val);

	ret = i915_read(dev_priv, (uintptr_t)0x22068, &val);
	if (ret == DCMD_OK)
		mdb_printf("  BLT EHR: 0x%08x\n", val);

	ret = i915_read(dev_priv, (uintptr_t)0x2206C, &val);
	if (ret == DCMD_OK)
		mdb_printf("  INSTDONE: 0x%08x\n", val);

	ret = i915_read(dev_priv, (uintptr_t)0x22074, &val);
	if (ret == DCMD_OK)
		mdb_printf("  ACTHD: 0x%08x\n", val);


	mdb_printf("\nRender command stream:\n");
	ret = i915_read(dev_priv, (uintptr_t)IPEIR_I965, &val);
	if (ret == DCMD_OK)
		mdb_printf("  RENDER EIR: 0x%08x\n", val);

	ret = i915_read(dev_priv, (uintptr_t)IPEHR_I965, &val);
	if (ret == DCMD_OK)
		mdb_printf("  RENDER EHR: 0x%08x\n", val);

	ret = i915_read(dev_priv, (uintptr_t)INSTDONE_I965, &val);
	if (ret == DCMD_OK)
		mdb_printf("  INSTDONE: 0x%08x\n", val);

	ret = i915_read(dev_priv, (uintptr_t)INSTPS, &val);
	if (ret == DCMD_OK)
		mdb_printf("  INSTPS: 0x%08x\n", val);

	ret = i915_read(dev_priv, (uintptr_t)INSTDONE1, &val);
	if (ret == DCMD_OK)
		mdb_printf("  INSTDONE1: 0x%08x\n", val);

	ret = i915_read(dev_priv, (uintptr_t)ACTHD_I965, &val);
	if (ret == DCMD_OK)
		mdb_printf("  ACTHD: 0x%08x\n", val);

	ret = i915_read(dev_priv, (uintptr_t)0x2078, &val);
	if (ret == DCMD_OK)
		mdb_printf("  DMA_FADD_P: 0x%08x\n", val);

	ret = i915_read(dev_priv, (uintptr_t)0x04094, &val);
	if (ret == DCMD_OK)
		mdb_printf("\nGraphics Engine Fault 0x%lx\n", val);

	ret = i915_read(dev_priv, (uintptr_t)0x04194, &val);
	if (ret == DCMD_OK)
		mdb_printf("Media Engine Fault 0x%lx\n", val);

	ret = i915_read(dev_priv, (uintptr_t)0x04294, &val);
	if (ret == DCMD_OK)
		mdb_printf("Blitter  Engine Fault 0x%lx\n", val);

	if (dev->gtt_dump != NULL)
		mdb_printf("gtt dump to %p\n", dev->gtt_dump);
	else
		mdb_printf("no gtt dump\n");
err2:
	mdb_free(dev_priv, sizeof (struct drm_i915_private));
err1:
	mdb_free(dev, sizeof (struct drm_device));

	return (ret);

}

void
i915_obj_history_help(void)
{
	mdb_printf("Print object history information for a given "
	    "drm_i915_gem_object pointer\n"
	    "Fields printed:\n"
	    "       event:\tOperation name\n"
	    "       cur_seq:\tCurrent system SeqNO\n"
	    "       last_seq:\tLast SeqNO has been processed\n"
	    "       ring addr:\tPoint to intel_ring_buffer structure\n"
	    "\nNOTE: Please make sure mdb_track is enabled in i915 driver "
	    "by setting mdb_track_enable\n");
}

/* ARGSUSED */
static int
i915_obj_history(uintptr_t addr, uint_t flags, int argc, const mdb_arg_t *argv)
{
	struct drm_gem_object obj;
	struct list_head node;
	uintptr_t temp;
	struct drm_history_list history_node;
	int ret = DCMD_OK;
	int condition = 1;
	int mdb_track = 0;

	if (!(flags & DCMD_ADDRSPEC)) {
		return (DCMD_USAGE);
	}

	if (mdb_vread(&obj, sizeof (struct drm_gem_object), addr) == -1) {
		mdb_warn("failed to read gem object infor");
		ret = DCMD_ERR;
		goto err;
	}

	if (mdb_readvar(&mdb_track, "mdb_track_enable") == -1) {
		mdb_warn("failed to read mdb_track");
		mdb_track = 0;
	}

	if (mdb_track == 0) {
		mdb_printf("mdb_track is not enabled. Please enable it "
		    "by set drm:mdb_track_enable=1");
		goto err;
	}

	mdb_printf("Dump obj history\n");
	mdb_printf("%s %20s %10s %10s\n", "event", "cur_seq", "last_seq",
	    "ring addr");
	temp = (uintptr_t)obj.his_list.next;
	while (condition) {
		if (mdb_vread(&node, sizeof (struct list_head), temp) == -1) {
			mdb_warn("failed to read his_list node");
			ret = DCMD_ERR;
			goto err;
		}

		if (node.contain_ptr == NULL)
			break;

		if (mdb_vread(&history_node, sizeof (struct drm_history_list),
		    (uintptr_t)node.contain_ptr) == -1) {
			mdb_warn("failed to read history node");
			ret = DCMD_ERR;
			goto err;
		}

		mdb_printf("%s %-8d %-8d 0x%lx\n", history_node.info,
		    history_node.cur_seq, history_node.last_seq,
		    history_node.ring_ptr);

		temp = (uintptr_t)node.next;
	}

err:
	return (ret);
}

void
i915_batch_history_help(void)
{
	mdb_printf("Print batchbuffer information\n"
	    "\nAll batchbuffers' information is printed one by one "
	    "from the latest one to the oldest one.\n"
	    "The information includes objects number, assigned SeqNO. "
	    "and objects list.\n"
	    "\nNOTE: Please make sure mdb_track is enabled in i915 "
	    "driver by setting mdb_track_enable\n");

}

/* ARGSUSED */
static int
i915_batch_history(uintptr_t addr, uint_t flags, int argc,
    const mdb_arg_t *argv)
{
	struct list_head node;
	uintptr_t temp;
	struct batch_info_list batch_node;
	caddr_t *obj_list;
	int ret, i;
	struct drm_i915_private *dev_priv;
	int condition = 1;
	int mdb_track = 0;

	dev_priv = mdb_alloc(sizeof (struct drm_i915_private), UM_SLEEP);

	ret = get_i915_private(dev_priv);
	if (ret != DCMD_OK) {
		mdb_warn("failed to read history node");
		goto err;
	}

	if (mdb_readvar(&mdb_track, "mdb_track_enable") == -1) {
		mdb_warn("failed to read mdb_track");
		mdb_track = 0;
	}
	if (mdb_track == 0) {
		mdb_printf("mdb_track is not enabled. Please enable it by "
		    "set drm:mdb_track_enable=1");
		goto err;
	}

	mdb_printf("Dump batchbuffer history\n");
	temp = (uintptr_t)dev_priv->batch_list.next;
	while (condition) {

		if (mdb_vread(&node, sizeof (struct list_head), temp) == -1) {
			mdb_warn("failed to read his_list node");
			ret = DCMD_ERR;
			goto err;
		}

		if (node.contain_ptr == NULL)
			break;

		if (mdb_vread(&batch_node, sizeof (struct batch_info_list),
		    (uintptr_t)node.contain_ptr) == -1) {
			mdb_warn("failed to read batch node");
			ret = DCMD_ERR;
			goto err;
		}

		mdb_printf("batch buffer includes %d objects, seqno 0x%x\n",
		    batch_node.num, batch_node.seqno);

		obj_list = mdb_alloc(batch_node.num * sizeof (caddr_t),
		    UM_SLEEP);
		if (mdb_vread(obj_list, batch_node.num * sizeof (caddr_t),
		    (uintptr_t)batch_node.obj_list) == -1) {
			mdb_warn("failed to read batch object list");
			ret = DCMD_ERR;
			goto err;
		}


		for (i = 0; i < batch_node.num; i++) {
			mdb_printf("obj: 0x%lx\n", obj_list[i]);
		}

		mdb_free(obj_list, batch_node.num * sizeof (caddr_t));

		temp = (uintptr_t)node.next;
	}

err:
	mdb_free(dev_priv, sizeof (struct drm_i915_private));
	return (ret);
}

static const char *yesno(int v)
{
	return (v ? "yes" : "no");
}

void
i915_capabilities_help(void)
{
	mdb_printf("Print capability information for Intel graphics card\n"
	    "Fields printed:\n"
	    "	is_mobile:\tMobile Platform\n"
	    "       is_i85x:\tIntel I85x series graphics card\n"
	    "       is_i915g:\tIntel I915g series graphics card\n"
	    "       is_i945gm:\tIntel I945gm series graphics card\n"
	    "       is_g33:\tIntel G33 series graphics card\n"
	    "       need_gfx_hws:\tNeed setup graphics hardware status page\n"
	    "       is_g4x:\tIntel G4x series graphics card\n"
	    "       is_pineview:\tIntel Pineview series graphics card\n"
	    "       is_broadwater:\tIntel Broadwater series graphics card\n"
	    "       is_crestline:\tIntel Crestline series graphics card\n"
	    "       is_ivybridge:\tIntel Ivybridge series graphics card\n"
	    "       is_valleyview:\tIntel Valleyview series graphics card\n"
	    "       has_force_wake:\tHas force awake\n"
	    "       is_haswell:\tIntel Haswell series graphics card\n"
	    "       has_fbc:\tHas Framebuffer compression\n"
	    "       has_pipe_cxsr:\tHas CxSR\n"
	    "       has_hotplug:\tHas output hotplug\n"
	    "       cursor_needs_physical:\tHas physical cursor object\n"
	    "       has_overlay:\tHas Overlay\n"
	    "       overlay_needs_physical:\tHas physical overlay object\n"
	    "       supports_tv:\tSupport TV output\n"
	    "       has_bsd_ring:\tHas BSD ring\n"
	    "       has_blt_ring:\tHas BLT ring\n"
	    "       has_llc:\tHas last level cache\n");
}

/* ARGSUSED */
static int
i915_capabilities(uintptr_t addr, uint_t flags, int argc, const mdb_arg_t *argv)
{
	int ret;
	struct drm_device *drm_dev;
	struct drm_i915_private *dev_priv;
	struct intel_device_info info;

	if (flags & DCMD_ADDRSPEC) {
		mdb_printf("don't need to set address 0x%lx\n", addr);
		return (DCMD_OK);
	}

	drm_dev = mdb_alloc(sizeof (struct drm_device), UM_SLEEP);

	ret = get_drm_dev(drm_dev);
	if (ret == DCMD_ERR)
		goto err1;

	dev_priv = mdb_alloc(sizeof (struct drm_i915_private), UM_SLEEP);
	ret = get_i915_private(dev_priv);
	if (ret != DCMD_OK) {
		goto err2;
	}

	if (mdb_vread(&info, sizeof (struct intel_device_info),
	    (uintptr_t)dev_priv->info) == -1) {
		mdb_warn("failed to read i915 chip info");
		ret = DCMD_ERR;
		goto err2;
	}

	mdb_printf("gen: %d\n", info.gen);
	mdb_printf("pch: %d\n", dev_priv->pch_type);


/* BEGIN CSTYLED */
#define	SEP_SEMICOLON	;
#define	DEFINE_FLAG(x)	mdb_printf(#x ": %s\n", yesno(info.x))
	DEV_INFO_FOR_EACH_FLAG(DEFINE_FLAG, SEP_SEMICOLON);
#undef	DEFINE_FLAG
#undef	SEP_SEMICOLON
/* END CSTYLED */

err2:
	mdb_free(dev_priv, sizeof (struct drm_i915_private));
err1:
	mdb_free(drm_dev, sizeof (struct drm_device));
	return (ret);
}

void
i915_request_list_node_help(void)
{
	mdb_printf("Print request list information for a given list pointer\n"
	    "The information includes request, SeqNO. and timestamp.\n");
}

/* ARGSUSED */
static int
i915_request_list_node(uintptr_t addr, uint_t flags, int argc,
    const mdb_arg_t *argv)
{
	int ret = DCMD_OK;
	struct list_head list;
	struct drm_i915_gem_request *request;

	if (!(flags & DCMD_ADDRSPEC))
		return (DCMD_USAGE);

	if (mdb_vread(&list, sizeof (struct list), addr) == -1) {
		mdb_warn("failed to read list");
		return (DCMD_ERR);
	}

	if (list.contain_ptr == 0) {
		mdb_warn("no request!");
		return (DCMD_ERR);
	}

	request = mdb_alloc(sizeof (struct drm_i915_gem_request), UM_SLEEP);
	if (mdb_vread(request, sizeof (struct drm_i915_gem_request),
	    (uintptr_t)list.contain_ptr) == -1) {
		mdb_warn("failed to read request infor");
		ret = DCMD_ERR;
		goto err;
	}

	mdb_printf("0x%lx ", list.contain_ptr);
	mdb_printf("    %d @ %ld\n", request->seqno, request->emitted_jiffies);

err:
	mdb_free(request, sizeof (struct drm_i915_gem_request));
	return (ret);
}

static int
request_walk_list(uintptr_t addr, const char *str)
{
	struct list_head *head;
	int ret = DCMD_OK;

	mdb_printf("Dump %s ring request List %p\n", str, addr);

	head = mdb_alloc(sizeof (struct list_head), UM_SLEEP);
	if (mdb_vread(head, sizeof (struct list_head), addr) == -1) {
		mdb_warn("failed to render ring request list");
		ret = DCMD_ERR;
		goto err;
	}

	if (mdb_pwalk_dcmd("head_list", "i915_request_list_node",
	    0, NULL, (uintptr_t)head->prev) == -1) {
		mdb_warn("failed to walk request head_list");
		ret = DCMD_ERR;
		goto err;
	}

err:
	mdb_free(head, sizeof (struct list_head));
	return (ret);

}

void
i915_gem_request_info_help(void)
{
	mdb_printf("Print request list for each ring buffer\n"
	    "\nSee also: \"::help i915_request_list_node\"\n");
}

/* ARGSUSED */
static int
i915_gem_request_info(uintptr_t addr, uint_t flags, int argc,
    const mdb_arg_t *argv)
{
	struct drm_i915_private *dev_priv;
	int ret = DCMD_OK;

	if (flags & DCMD_ADDRSPEC) {
		mdb_printf("don't need to set address 0x%lx, just ignore\n",
		    addr);
	}

	dev_priv = mdb_alloc(sizeof (struct drm_i915_private), UM_SLEEP);
	ret = get_i915_private(dev_priv);
	if (ret != DCMD_OK) {
		goto err;
	}

	ret = request_walk_list((uintptr_t)dev_priv->ring[0].request_list.next,
	    "RENDER");
	if (ret != DCMD_OK) {
		goto err;
	}
	ret = request_walk_list((uintptr_t)dev_priv->ring[1].request_list.next,
	    "BSD");
	if (ret != DCMD_OK) {
		goto err;
	}
	ret = request_walk_list((uintptr_t)dev_priv->ring[2].request_list.next,
	    "BLT");
	if (ret != DCMD_OK) {
		goto err;
	}

err:
	mdb_free(dev_priv, sizeof (struct drm_i915_private));
	return (ret);
}

static int
get_hws_info(uintptr_t addr, const char *str, int index)
{
	u32 *regs;
	int i, ret = DCMD_OK;

	regs = mdb_alloc(0x4000, UM_SLEEP);
	if (mdb_vread(regs, 0x4000,
	    addr) == -1) {
		mdb_warn("failed to read hardware status page");
		ret = DCMD_ERR;
		goto err;
	}

	if (index < 0) {
		for (i = 0; i < 4096 / sizeof (u32) / 4; i += 4) {
			mdb_printf("0x%08x: 0x%08x 0x%08x 0x%08x 0x%08x\n",
			    i * 4, regs[i], regs[i + 1], regs[i + 2],
			    regs[i + 3]);
		}
	} else
		mdb_printf("%s ring seqno %d \n", str, regs[index]);
err:
	mdb_free(regs, 0x4000);
return (ret);

}

void
i915_ring_seqno_info_help(void)
{
	mdb_printf("Print current SeqNO. for each ring buffer\n");
}

/* ARGSUSED */
static int
i915_ring_seqno_info(uintptr_t addr, uint_t flags, int argc,
    const mdb_arg_t *argv)
{
	struct drm_i915_private *dev_priv;
	int ret = DCMD_OK;

	if (flags & DCMD_ADDRSPEC) {
		mdb_printf("don't need to set address 0x%lx\n", addr);
		return (DCMD_OK);
	}

	dev_priv = mdb_alloc(sizeof (struct drm_i915_private), UM_SLEEP);
	ret = get_i915_private(dev_priv);
	if (ret != DCMD_OK) {
		goto err;
	}

	ret = get_hws_info((uintptr_t)dev_priv->ring[0].status_page.page_addr,
	    "RENDER", I915_GEM_HWS_INDEX);
	if (ret != DCMD_OK) {
		goto err;
	}
	ret = get_hws_info((uintptr_t)dev_priv->ring[1].status_page.page_addr,
	    "BSD", I915_GEM_HWS_INDEX);
	if (ret != DCMD_OK) {
		goto err;
	}
	ret = get_hws_info((uintptr_t)dev_priv->ring[2].status_page.page_addr,
	    "BLT", I915_GEM_HWS_INDEX);
	if (ret != DCMD_OK) {
		goto err;
	}


err:
	mdb_free(dev_priv, sizeof (struct drm_i915_private));
	return (ret);

}

void
i915_gem_fence_regs_info_help(void)
{
	mdb_printf("Print current Fence registers information\n"
	"The information includes object address, user pin flag, tiling mode,\n"
	"size, read domain, write domain, read SeqNO, write SeqNO, fence "
	"SeqNo,\n"
	"catch level, dirty info, object name, pin count, fence reg number,\n"
	"GTT offset, pin mappable and fault mappable.\n");
}

/* ARGSUSED */
static int
i915_gem_fence_regs_info(uintptr_t addr, uint_t flags, int argc,
    const mdb_arg_t *argv)
{
	struct drm_i915_private *dev_priv;
	int i, ret = DCMD_OK;
	struct drm_i915_gem_object obj;

	if (flags & DCMD_ADDRSPEC) {
		mdb_printf("don't need to set address 0x%lx\n", addr);
		return (DCMD_OK);
	}

	dev_priv = mdb_alloc(sizeof (struct drm_i915_private), UM_SLEEP);
	ret = get_i915_private(dev_priv);
	if (ret != DCMD_OK) {
		goto err;
	}

	mdb_printf("Reserved fences start = %d\n", dev_priv->fence_reg_start);
	mdb_printf("Total fences = %d\n", dev_priv->num_fence_regs);

	for (i = 0; i < dev_priv->num_fence_regs; i++) {

		mdb_printf("Fence %d, pin count = %d, object = ",
		    i, dev_priv->fence_regs[i].pin_count);

		if (dev_priv->fence_regs[i].obj != NULL) {
			mdb_vread(&obj, sizeof (struct drm_i915_gem_object),
			    (uintptr_t)dev_priv->fence_regs[i].obj);
			describe_obj(&obj);
		} else {
			mdb_printf("unused");
		}
		mdb_printf("\n");
	}

err:
	mdb_free(dev_priv, sizeof (struct drm_i915_private));
	return (ret);

}

void
i915_interrupt_info_help(void)
{
	mdb_printf("Print debug register information\n"
	    "Registers printed:\n"
	    "       IER:\tInterrupt Enable Register\n"
	    "       IIR:\tInterrupt Identity Register\n"
	    "       IMR:\tInterrupt Mask Register\n"
	    "       ISR:\tInterrupt Status Register\n");
}

/* ARGSUSED */
static int
i915_interrupt_info(uintptr_t addr, uint_t flags, int argc,
    const mdb_arg_t *argv)
{
	struct drm_device *dev;
	struct drm_i915_private *dev_priv;
	struct intel_device_info info;
	int pipe, ret = DCMD_OK;
	uint32_t val;

	if (flags & DCMD_ADDRSPEC) {
		mdb_printf("don't need to set address 0x%lx\n", addr);
		return (DCMD_OK);
	}

	dev = mdb_alloc(sizeof (struct drm_device), UM_SLEEP);
	ret = get_drm_dev(dev);
	if (ret == DCMD_ERR)
		goto err1;

	dev_priv = mdb_alloc(sizeof (struct drm_i915_private), UM_SLEEP);
	ret = get_i915_private(dev_priv);
	if (ret != DCMD_OK) {
		goto err2;
	}

	if (mdb_vread(&info, sizeof (struct intel_device_info),
	    (uintptr_t)dev_priv->info) == -1) {
		mdb_warn("failed to read i915 chip info");
		ret = DCMD_ERR;
		goto err2;
	}

	if (info.is_valleyview) {
		ret = i915_read(dev_priv, (uintptr_t)VLV_IER, &val);
		if (ret == DCMD_OK)
			mdb_printf("Display IER:\t%08x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)VLV_IIR, &val);
		if (ret == DCMD_OK)
			mdb_printf("Display IIR:\t%08x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)VLV_IIR_RW, &val);
		if (ret == DCMD_OK)
			mdb_printf("Display IIR_RW:\t%08x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)VLV_IMR, &val);
		if (ret == DCMD_OK)
			mdb_printf("Display IMR:\t%08x\n", val);

		for_each_pipe(pipe) {
			ret = i915_read(dev_priv, PIPESTAT(pipe), &val);
			if (ret == DCMD_OK)
				mdb_printf("Pipe %c stat:\t%08x\n",
				    pipe_name(pipe), val);
		}
		ret = i915_read(dev_priv, (uintptr_t)VLV_MASTER_IER, &val);
		if (ret == DCMD_OK)
			mdb_printf("Master IER:\t%08x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)GTIER, &val);
		if (ret == DCMD_OK)
			mdb_printf("Render IER:\t%08x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)GTIIR, &val);
		if (ret == DCMD_OK)
			mdb_printf("Render IIR:\t%08x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)GTIMR, &val);
		if (ret == DCMD_OK)
			mdb_printf("Render IMR:\t%08x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)GEN6_PMIER, &val);
		if (ret == DCMD_OK)
			mdb_printf("PM IER:\t\t%08x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)GEN6_PMIIR, &val);
		if (ret == DCMD_OK)
			mdb_printf("PM IIR:\t\t%08x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)GEN6_PMIMR, &val);
		if (ret == DCMD_OK)
			mdb_printf("PM IMR:\t\t%08x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)PORT_HOTPLUG_EN, &val);
		if (ret == DCMD_OK)
			mdb_printf("Port hotplug:\t%08x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)VLV_DPFLIPSTAT, &val);
		if (ret == DCMD_OK)
			mdb_printf("DPFLIPSTAT:\t%08x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)DPINVGTT, &val);
		if (ret == DCMD_OK)
			mdb_printf("DPINVGTT:\t%08x\n", val);
	} else if (dev_priv->pch_type == PCH_NONE) {
		ret = i915_read(dev_priv, (uintptr_t)IER, &val);
		if (ret == DCMD_OK)
			mdb_printf("Interrupt enable:    %08x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)IIR, &val);
		if (ret == DCMD_OK)
			mdb_printf("Interrupt identity:  %08x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)IMR, &val);
		if (ret == DCMD_OK)
			mdb_printf("Interrupt mask:      %08x\n", val);

		for_each_pipe(pipe) {
			ret = i915_read(dev_priv, (uintptr_t)PIPESTAT(pipe),
			    &val);
			if (ret == DCMD_OK)
				mdb_printf("Pipe %c stat:         %08x\n",
				    pipe_name(pipe), val);
		}
	} else {
		ret = i915_read(dev_priv, (uintptr_t)DEIER, &val);
		if (ret == DCMD_OK)
			mdb_printf(
			    "North Display Interrupt enable:		%08x\n",
			    val);

		ret = i915_read(dev_priv, (uintptr_t)DEIIR, &val);
		if (ret == DCMD_OK)
			mdb_printf(
			    "North Display Interrupt identity:	%08x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)DEIMR, &val);
		if (ret == DCMD_OK)
			mdb_printf(
			    "North Display Interrupt mask:		%08x\n",
			    val);

		ret = i915_read(dev_priv, (uintptr_t)SDEIER, &val);
		if (ret == DCMD_OK)
			mdb_printf(
			    "South Display Interrupt enable:		%08x\n",
			    val);

		ret = i915_read(dev_priv, (uintptr_t)SDEIIR, &val);
		if (ret == DCMD_OK)
			mdb_printf(
			    "South Display Interrupt identity:	%08x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)SDEIMR, &val);
		if (ret == DCMD_OK)
			mdb_printf(
			    "South Display Interrupt mask:		%08x\n",
			    val);

		ret = i915_read(dev_priv, (uintptr_t)GTIER, &val);
		if (ret == DCMD_OK)
			mdb_printf(
			    "Graphics Interrupt enable:		%08x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)GTIIR, &val);
		if (ret == DCMD_OK)
			mdb_printf(
			    "Graphics Interrupt identity:		%08x\n",
			    val);

		ret = i915_read(dev_priv, (uintptr_t)GTIMR, &val);
		if (ret == DCMD_OK)
			mdb_printf(
			    "Graphics Interrupt mask:		%08x\n", val);
	}
	mdb_printf("Interrupts received: %d\n", dev_priv->irq_received);

err2:
	mdb_free(dev_priv, sizeof (struct drm_i915_private));
err1:
	mdb_free(dev, sizeof (struct drm_device));

	return (ret);

}

void
i915_hws_info_help(void)
{
	mdb_printf("Print hardware status page for each RING\n");
}

/* ARGSUSED */
static int
i915_hws_info(uintptr_t addr, uint_t flags, int argc, const mdb_arg_t *argv)
{
	struct drm_i915_private *dev_priv;
	int ret = DCMD_OK;

	if (flags & DCMD_ADDRSPEC) {
		mdb_printf("don't need to set address 0x%lx\n", addr);
		return (DCMD_OK);
	}

	dev_priv = mdb_alloc(sizeof (struct drm_i915_private), UM_SLEEP);
	ret = get_i915_private(dev_priv);
	if (ret != DCMD_OK) {
		goto err;
	}

	mdb_printf("Hardware status page for %s\n", "RENDER");
	ret = get_hws_info((uintptr_t)dev_priv->ring[0].status_page.page_addr,
	    "RENDER", -1);
	if (ret != DCMD_OK) {
		goto err;
	}

	mdb_printf("Hardware status page for %s\n", "BSD");
	ret = get_hws_info((uintptr_t)dev_priv->ring[1].status_page.page_addr,
	    "BSD", -1);
	if (ret != DCMD_OK) {
		goto err;
	}

	mdb_printf("Hardware status page for %s\n", "BLT");
	ret = get_hws_info((uintptr_t)dev_priv->ring[2].status_page.page_addr,
	    "BLT", -1);
	if (ret != DCMD_OK) {
		goto err;
	}

err:
	mdb_free(dev_priv, sizeof (struct drm_i915_private));
	return (ret);

}

void
i915_fbc_status_help(void)
{
	mdb_printf("Print the status and reason for Framebuffer Compression "
	    "Enabling\n");
}

/* ARGSUSED */
static int
i915_fbc_status(uintptr_t addr, uint_t flags, int argc, const mdb_arg_t *argv)
{
	struct drm_device *dev;
	struct drm_i915_private *dev_priv;
	struct intel_device_info info;
	int ret = DCMD_OK;
	uint32_t val;

	if (flags & DCMD_ADDRSPEC) {
		mdb_printf("don't need to set address 0x%lx\n", addr);
		return (DCMD_OK);
	}

	dev = mdb_alloc(sizeof (struct drm_device), UM_SLEEP);
	ret = get_drm_dev(dev);
	if (ret == DCMD_ERR)
		goto err1;

	dev_priv = mdb_alloc(sizeof (struct drm_i915_private), UM_SLEEP);
	ret = get_i915_private(dev_priv);
	if (ret != DCMD_OK) {
		goto err2;
	}

	if (mdb_vread(&info, sizeof (struct intel_device_info),
	    (uintptr_t)dev_priv->info) == -1) {
		mdb_warn("failed to read i915 chip info");
		ret = DCMD_ERR;
		goto err2;
	}

	if (!info.has_fbc) {
		mdb_printf("FBC unsupported on this chipset\n");
		goto err2;
	}

	if (dev_priv->pch_type != PCH_NONE) {
		ret = i915_read(dev_priv, (uintptr_t)ILK_DPFC_CONTROL, &val);
		if (ret == DCMD_OK) {
			val &= DPFC_CTL_EN;
		} else {
			mdb_printf("Failed to read FBC register\n");
			goto err2;
		}
	} else if (IS_GM45(dev)) {
		ret = i915_read(dev_priv, (uintptr_t)DPFC_CONTROL, &val);
		if (ret == DCMD_OK) {
			val &= DPFC_CTL_EN;
		} else {
			mdb_printf("Failed to read FBC register\n");
			goto err2;
		}
	} else if (info.is_crestline) {
		ret = i915_read(dev_priv, (uintptr_t)FBC_CONTROL, &val);
		if (ret == DCMD_OK) {
			val &= FBC_CTL_EN;
		} else {
			mdb_printf("Failed to read FBC register\n");
			goto err2;
		}
	}

	if (val) {
		mdb_printf("FBC enabled\n");
	} else {
		mdb_printf("FBC disabled: ");
		switch (dev_priv->no_fbc_reason) {
		case FBC_NO_OUTPUT:
			mdb_printf("no outputs");
			break;
		case FBC_STOLEN_TOO_SMALL:
			mdb_printf("not enough stolen memory");
			break;
		case FBC_UNSUPPORTED_MODE:
			mdb_printf("mode not supported");
			break;
		case FBC_MODE_TOO_LARGE:
			mdb_printf("mode too large");
			break;
		case FBC_BAD_PLANE:
			mdb_printf("FBC unsupported on plane");
			break;
		case FBC_NOT_TILED:
			mdb_printf("scanout buffer not tiled");
			break;
		case FBC_MULTIPLE_PIPES:
			mdb_printf("multiple pipes are enabled");
			break;
		case FBC_MODULE_PARAM:
			mdb_printf("disabled per module param (default off)");
			break;
		default:
			mdb_printf("unknown reason");
		}
		mdb_printf("\n");
	}

err2:
	mdb_free(dev_priv, sizeof (struct drm_i915_private));
err1:
	mdb_free(dev, sizeof (struct drm_device));

	return (ret);
}

/* ARGSUSED */
static int
i915_sr_status(uintptr_t addr, uint_t flags, int argc, const mdb_arg_t *argv)
{
	struct drm_device *dev;
	struct drm_i915_private *dev_priv;
	struct intel_device_info info;
	int ret = DCMD_OK;
	uint32_t val = 0;

	if (flags & DCMD_ADDRSPEC) {
		mdb_printf("don't need to set address 0x%lx\n", addr);
		return (DCMD_OK);
	}

	dev = mdb_alloc(sizeof (struct drm_device), UM_SLEEP);
	ret = get_drm_dev(dev);
	if (ret == DCMD_ERR)
		goto err1;

	dev_priv = mdb_alloc(sizeof (struct drm_i915_private), UM_SLEEP);
	ret = get_i915_private(dev_priv);
	if (ret != DCMD_OK) {
		goto err2;
	}

	if (mdb_vread(&info, sizeof (struct intel_device_info),
	    (uintptr_t)dev_priv->info) == -1) {
		mdb_warn("failed to read i915 chip info");
		ret = DCMD_ERR;
		goto err2;
	}

	if (dev_priv->pch_type != PCH_NONE) {
		ret = i915_read(dev_priv, (uintptr_t)WM1_LP_ILK, &val);
		if (ret == DCMD_OK) {
			val &= WM1_LP_SR_EN;
		} else {
			mdb_printf("Failed to read sr register\n");
			goto err2;
		}
	} else if (info.is_crestline || IS_I945G(dev) || info.is_i945gm) {
		ret = i915_read(dev_priv, (uintptr_t)FW_BLC_SELF, &val);
		if (ret == DCMD_OK) {
			val &= FW_BLC_SELF_EN;
		} else {
			mdb_printf("Failed to read sr register\n");
			goto err2;
		}
	} else if (IS_I915GM(dev)) {
		ret = i915_read(dev_priv, (uintptr_t)INSTPM, &val);
		if (ret == DCMD_OK) {
			val &= INSTPM_SELF_EN;
		} else {
			mdb_printf("Failed to read sr register\n");
			goto err2;
		}
	} else if (info.is_pineview) {
		ret = i915_read(dev_priv, (uintptr_t)DSPFW3, &val);
		if (ret == DCMD_OK) {
			val &= PINEVIEW_SELF_REFRESH_EN;
		} else {
			mdb_printf("Failed to read sr register\n");
			goto err2;
		}
	}

	mdb_printf("self-refresh: %s\n",
	    val ? "enabled" : "disabled");

err2:
	mdb_free(dev_priv, sizeof (struct drm_i915_private));
err1:
	mdb_free(dev, sizeof (struct drm_device));

	return (ret);
}

void
i915_gem_framebuffer_info_help(void)
{
	mdb_printf("Print console framebuffer information\n"
	    "The information includes width, height, depth,\n"
	    "bits_per_pixel and object structure address\n");
}

/* ARGSUSED */
static int
i915_gem_framebuffer_info(uintptr_t addr, uint_t flags, int argc,
    const mdb_arg_t *argv)
{
	struct drm_device *dev;
	struct drm_i915_private *dev_priv;
	struct intel_fbdev fbdev;
	struct drm_framebuffer fb;
	int ret = DCMD_OK;

	if (flags & DCMD_ADDRSPEC) {
		mdb_printf("don't need to set address 0x%lx\n", addr);
		return (DCMD_OK);
	}

	dev = mdb_alloc(sizeof (struct drm_device), UM_SLEEP);
	ret = get_drm_dev(dev);
	if (ret == DCMD_ERR)
		goto err1;

	dev_priv = mdb_alloc(sizeof (struct drm_i915_private), UM_SLEEP);
	ret = get_i915_private(dev_priv);
	if (ret != DCMD_OK) {
		goto err2;
	}

	if (mdb_vread(&fbdev, sizeof (struct intel_fbdev),
	    (uintptr_t)dev_priv->fbdev) == -1) {
		mdb_warn("failed to read intel_fbdev info");
		ret = DCMD_ERR;
		goto err2;
	}

	if (mdb_vread(&fb, sizeof (struct drm_framebuffer),
	    (uintptr_t)fbdev.helper.fb) == -1) {
		mdb_warn("failed to read framebuffer info");
		ret = DCMD_ERR;
		goto err2;
	}

	mdb_printf("fbcon size: %d x %d, depth %d, %d bpp, obj %p",
	    fb.width,
	    fb.height,
	    fb.depth,
	    fb.bits_per_pixel,
	    fb.base);
	mdb_printf("\n");

err2:
	mdb_free(dev_priv, sizeof (struct drm_i915_private));
err1:
	mdb_free(dev, sizeof (struct drm_device));

	return (ret);
}

/* ARGSUSED */
static int
i915_gen6_forcewake_count_info(uintptr_t addr, uint_t flags, int argc,
    const mdb_arg_t *argv)
{
	struct drm_i915_private *dev_priv;
	int ret = DCMD_OK;
	unsigned forcewake_count;

	if (flags & DCMD_ADDRSPEC) {
		mdb_printf("don't need to set address 0x%lx\n", addr);
		return (DCMD_OK);
	}

	dev_priv = mdb_alloc(sizeof (struct drm_i915_private), UM_SLEEP);
	ret = get_i915_private(dev_priv);
	if (ret != DCMD_OK) {
		goto err;
	}

	forcewake_count = dev_priv->forcewake_count;

	mdb_printf("forcewake count = %u\n", forcewake_count);

err:
	mdb_free(dev_priv, sizeof (struct drm_i915_private));

	return (ret);
}

static const char *swizzle_string(unsigned swizzle)
{
	switch (swizzle) {
	case I915_BIT_6_SWIZZLE_NONE:
		return ("none");
	case I915_BIT_6_SWIZZLE_9:
		return ("bit9");
	case I915_BIT_6_SWIZZLE_9_10:
		return ("bit9/bit10");
	case I915_BIT_6_SWIZZLE_9_11:
		return ("bit9/bit11");
	case I915_BIT_6_SWIZZLE_9_10_11:
		return ("bit9/bit10/bit11");
	case I915_BIT_6_SWIZZLE_9_17:
		return ("bit9/bit17");
	case I915_BIT_6_SWIZZLE_9_10_17:
		return ("bit9/bit10/bit17");
	case I915_BIT_6_SWIZZLE_UNKNOWN:
		return ("unkown");
	}

	return ("bug");
}

void
i915_swizzle_info_help(void)
{
	mdb_printf("Print object swizzle information\n"
	    "Registers printed:\n"
	    "       TILECTL:\tTile Control\n"
	    "       ARB_MODE:\tArbiter Mode Control Register\n"
	    "       DISP_ARB_CTL:\tDisplay Arbiter Control\n");

}

/* ARGSUSED */
static int
i915_swizzle_info(uintptr_t addr, uint_t flags, int argc, const mdb_arg_t *argv)
{
	struct drm_device *dev;
	struct drm_i915_private *dev_priv;
	struct intel_device_info info;
	int ret = DCMD_OK;
	uint32_t val = 0;

	if (flags & DCMD_ADDRSPEC) {
		mdb_printf("don't need to set address 0x%lx\n", addr);
		return (DCMD_OK);
	}

	dev = mdb_alloc(sizeof (struct drm_device), UM_SLEEP);
	ret = get_drm_dev(dev);
	if (ret == DCMD_ERR)
		goto err1;

	dev_priv = mdb_alloc(sizeof (struct drm_i915_private), UM_SLEEP);
	ret = get_i915_private(dev_priv);
	if (ret != DCMD_OK) {
		goto err2;
	}

	if (mdb_vread(&info, sizeof (struct intel_device_info),
	    (uintptr_t)dev_priv->info) == -1) {
		mdb_warn("failed to read i915 chip info");
		ret = DCMD_ERR;
		goto err2;
	}

	mdb_printf("bit6 swizzle for X-tiling = %s\n",
	    swizzle_string(dev_priv->mm.bit_6_swizzle_x));
	mdb_printf("bit6 swizzle for Y-tiling = %s\n",
	    swizzle_string(dev_priv->mm.bit_6_swizzle_y));

	if ((info.gen == 3) || (info.gen == 4)) {
		ret = i915_read(dev_priv, (uintptr_t)DCC, &val);
		if (ret == DCMD_OK)
			mdb_printf("DDC = 0x%08x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)C0DRB3, &val);
		if (ret == DCMD_OK)
			mdb_printf("C0DRB3 = 0x%04x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)C1DRB3, &val);
		if (ret == DCMD_OK)
			mdb_printf("C1DRB3 = 0x%04x\n", val);

	} else if ((info.gen == 6) || (info.gen == 7)) {
		ret = i915_read(dev_priv, (uintptr_t)MAD_DIMM_C0, &val);
		if (ret == DCMD_OK)
			mdb_printf("MAD_DIMM_C0 = 0x%08x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)MAD_DIMM_C1, &val);
		if (ret == DCMD_OK)
			mdb_printf("MAD_DIMM_C1 = 0x%08x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)MAD_DIMM_C2, &val);
		if (ret == DCMD_OK)
			mdb_printf("MAD_DIMM_C2 = 0x%08x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)TILECTL, &val);
		if (ret == DCMD_OK)
			mdb_printf("TILECTL = 0x%08x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)ARB_MODE, &val);
		if (ret == DCMD_OK)
			mdb_printf("ARB_MODE = 0x%08x\n", val);

		ret = i915_read(dev_priv, (uintptr_t)DISP_ARB_CTL, &val);
		if (ret == DCMD_OK)
			mdb_printf("DISP_ARB_CTL = 0x%08x\n", val);

	}

err2:
	mdb_free(dev_priv, sizeof (struct drm_i915_private));
err1:
	mdb_free(dev, sizeof (struct drm_device));

	return (ret);
}

void
i915_ppgtt_info_help(void)
{
	mdb_printf("Print Per-Process GTT (PPGTT) information\n"
	    "Registers printed:\n"
	    "       GFX_MODE:\tGraphics Mode Register\n"
	    "       PP_DIR_BASE:\tPage Directory Base Register\n"
	    "       ECOCHK:\tMain Graphic Arbiter Misc Register\n");
}

/* ARGSUSED */
static int
i915_ppgtt_info(uintptr_t addr, uint_t flags, int argc, const mdb_arg_t *argv)
{
	struct drm_device *dev;
	struct drm_i915_private *dev_priv;
	struct intel_device_info info;
	int i, ret = DCMD_OK;
	uint32_t val = 0;

	if (flags & DCMD_ADDRSPEC) {
		mdb_printf("don't need to set address 0x%lx\n", addr);
		return (DCMD_OK);
	}

	dev = mdb_alloc(sizeof (struct drm_device), UM_SLEEP);
	ret = get_drm_dev(dev);
	if (ret == DCMD_ERR)
		goto err1;

	dev_priv = mdb_alloc(sizeof (struct drm_i915_private), UM_SLEEP);
	ret = get_i915_private(dev_priv);
	if (ret != DCMD_OK) {
		goto err2;
	}

	if (mdb_vread(&info, sizeof (struct intel_device_info),
	    (uintptr_t)dev_priv->info) == -1) {
		mdb_warn("failed to read i915 chip info");
		ret = DCMD_ERR;
		goto err2;
	}

	if (info.gen == 6) {
		ret = i915_read(dev_priv, (uintptr_t)GFX_MODE, &val);
		if (ret == DCMD_OK)
			mdb_printf("GFX_MODE: 0x%08x\n", val);
	}

	for (i = 0; i < 3; i ++) {
		mdb_printf("RING %d\n", i);
		if (info.gen == 7) {
			ret = i915_read(dev_priv,
			    (uintptr_t)(dev_priv->ring[i].mmio_base + 0x29c),
			    &val);
			if (ret == DCMD_OK)
				mdb_printf("GFX_MODE: 0x%08x\n", val);
		}
		ret = i915_read(dev_priv,
		    (uintptr_t)(dev_priv->ring[i].mmio_base + 0x228), &val);
		if (ret == DCMD_OK)
			mdb_printf("PP_DIR_BASE: 0x%08x\n", val);

		ret = i915_read(dev_priv,
		    (uintptr_t)(dev_priv->ring[i].mmio_base + 0x518), &val);
		if (ret == DCMD_OK)
			mdb_printf("PP_DIR_BASE_READ: 0x%08x\n", val);

		ret = i915_read(dev_priv,
		    (uintptr_t)(dev_priv->ring[i].mmio_base + 0x220), &val);
		if (ret == DCMD_OK)
			mdb_printf("PP_DIR_DCLV: 0x%08x\n", val);
	}

	if (dev_priv->mm.aliasing_ppgtt) {
		struct i915_hw_ppgtt ppgtt;
		if (mdb_vread(&ppgtt, sizeof (struct i915_hw_ppgtt),
		    (uintptr_t)dev_priv->mm.aliasing_ppgtt) == -1) {
			mdb_warn("failed to read aliasing_ppgtt info");
			ret = DCMD_ERR;
			goto err2;
		}

		mdb_printf("aliasing PPGTT:\n");
		mdb_printf("pd gtt offset: 0x%08x\n", ppgtt.pd_offset);
	}

	ret = i915_read(dev_priv, (uintptr_t)GAM_ECOCHK, &val);
	if (ret == DCMD_OK)
		mdb_printf("ECOCHK: 0x%08x\n", val);

err2:
	mdb_free(dev_priv, sizeof (struct drm_i915_private));
err1:
	mdb_free(dev, sizeof (struct drm_device));

	return (ret);
}

/*
 * MDB module linkage information:
 *
 * We declare a list of structures describing our dcmds, a list of structures
 * describing our walkers, and a function named _mdb_init to return a pointer
 * to our module information.
 */

static const mdb_dcmd_t dcmds[] = {
	{
		"i915_pciid",
		"?",
		"pciid information",
		i915_pciid,
		i915_pciid_help
	},
	{
		"i915_gtt_total",
		"?",
		"get gtt total size",
		i915_gtt_total,
		i915_gtt_total_help
	},
	{
		"i915_obj_list",
		"[-aibu]",
		"i915 objects list information",
		i915_obj_list,
		i915_obj_list_help
	},
	{
		"i915_obj_list_node",
		":",
		"i915 objects list node information",
		i915_obj_list_node,
		i915_obj_list_node_help
	},
	{
		"i915_ringbuffer_info",
		"[-lrs]",
		"i915 ring buffer information",
		i915_ringbuffer_info,
		i915_ringbuffer_info_help
	},
	{
		"i915_gtt_dump",
		"?",
		"dump gtt_dump_add address",
		i915_gtt_dump,
		i915_gtt_dump_help
	},
	{
		"i915_register_read",
		":",
		"read i915 register",
		i915_register_read,
		i915_register_read_help
	},
	{
		"i915_error_reg_dump",
		"?",
		"i915 error registers dump",
		i915_error_reg_dump,
		i915_error_reg_dump_help
	},
	{
		"i915_obj_history",
		":",
		"i915 objects track information",
		i915_obj_history,
		i915_obj_history_help
	},
	{
		"i915_batch_history",
		"?",
		"i915 objects track information",
		i915_batch_history,
		i915_batch_history_help
	},
	{
		"i915_capabilities",
		"?",
		"i915 capabilities information",
		i915_capabilities,
		i915_capabilities_help
	},
	{
		"i915_request_list_node",
		":",
		"i915 request list node information",
		i915_request_list_node,
		i915_request_list_node_help
	},
	{
		"i915_gem_request",
		"?",
		"i915 gem request information",
		i915_gem_request_info,
		i915_gem_request_info_help
	},
	{
		"i915_ring_seqno",
		"?",
		"ring seqno information",
		i915_ring_seqno_info,
		i915_ring_seqno_info_help
	},
	{
		"i915_gem_fence_regs",
		"?",
		"fence register information",
		i915_gem_fence_regs_info,
		i915_gem_fence_regs_info_help
	},
	{
		"i915_interrupt",
		"?",
		"interrupt information",
		i915_interrupt_info,
		i915_interrupt_info_help
	},
	{
		"i915_gem_hws",
		"?",
		"hardware status page",
		i915_hws_info,
		i915_hws_info_help
	},
	{
		"i915_fbc_status",
		"?",
		"framebuffer compression information",
		i915_fbc_status,
		i915_fbc_status_help
	},
	{
		"i915_sr_status",
		"?",
		"Print self-refresh status",
		i915_sr_status,
		NULL
	},
	{
		"i915_gem_framebuffer",
		"?",
		"Print framebuffer information",
		i915_gem_framebuffer_info,
		i915_gem_framebuffer_info_help
	},
	{
		"i915_gen6_forcewake_count",
		"?",
		"Print forcewake count",
		i915_gen6_forcewake_count_info,
		NULL
	},
	{
		"i915_swizzle",
		"?",
		"Print swizzle information",
		i915_swizzle_info,
		i915_swizzle_info_help
	},
	{
		"i915_ppgtt",
		"?",
		"Print ppgtt information",
		i915_ppgtt_info,
		i915_ppgtt_info_help
	},

	{ NULL }
};

static const mdb_walker_t walkers[] = {
	{
		"head_list",
		"walk head list",
		head_list_walk_init,
		head_list_walk_step,
		head_list_walk_fini
	},
	{ NULL }
};

static const mdb_modinfo_t modinfo = {
	MDB_API_VERSION, dcmds, walkers
};

const mdb_modinfo_t *
_mdb_init(void)
{
	return (&modinfo);
}
