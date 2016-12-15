/*
 * Copyright (c) 2006, 2013, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * i915_drv.c -- Intel i915 driver -*- linux-c -*-
 * Created: Wed Feb 14 17:10:04 2001 by gareth@valinux.com
 */

/*
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.
 * Copyright 2003 Tungsten Graphics, Inc., Cedar Park, Texas.
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
 *    Gareth Hughes <gareth@valinux.com>
 *
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
 */

#include "drmP.h"
#include "i915_drm.h"
#include "i915_drv.h"
#include "drm_crtc_helper.h"
#include "intel_drv.h"

static int i915_modeset = -1;
unsigned int i915_fbpercrtc = 0;
int i915_panel_ignore_lid = 1;
unsigned int i915_powersave = 1;

int i915_semaphores = 1;

int i915_enable_rc6 = 1;
int i915_enable_fbc = 1;

unsigned int i915_lvds_downclock = 0;
int i915_lvds_channel_mode;

int i915_panel_use_ssc = -1;
int i915_vbt_sdvo_panel_type = -1;

bool i915_try_reset = true;
bool i915_enable_hangcheck = true;
int i915_enable_ppgtt = 1;

int i915_disable_power_well = 1;
int i915_enable_ips = 1;

static void *i915_statep;

static int i915_info(dev_info_t *, ddi_info_cmd_t, void *, void **);
static int i915_attach(dev_info_t *, ddi_attach_cmd_t);
static int i915_detach(dev_info_t *, ddi_detach_cmd_t);
static int i915_quiesce(dev_info_t *);

extern struct cb_ops drm_cb_ops;
extern int intel_agp_enabled;

static struct dev_ops i915_dev_ops = {
	DEVO_REV,		/* devo_rev */
	0,			/* devo_refcnt */
	i915_info,		/* devo_getinfo */
	nulldev,		/* devo_identify */
	nulldev,		/* devo_probe */
	i915_attach,		/* devo_attach */
	i915_detach,		/* devo_detach */
	nodev,			/* devo_reset */
	&drm_cb_ops,		/* devo_cb_ops */
	NULL,			/* devo_bus_ops */
	NULL,			/* power */
	i915_quiesce,		/* devo_quiesce */
};

static struct modldrv modldrv = {
	&mod_driverops,		/* drv_modops */
	"I915 DRM driver",	/* drv_linkinfo */
	&i915_dev_ops,		/* drv_dev_ops */
};

static struct modlinkage modlinkage = {
	MODREV_1, (void *) &modldrv, NULL
};

#define INTEL_VGA_DEVICE(id, info) {		\
	.vendor = 0x8086,			\
	.device = id,				\
	.driver_data = (unsigned long) info }

static const struct intel_device_info intel_i830_info = {
	.gen = 2, .is_mobile = 1, .cursor_needs_physical = 1, .num_pipes = 2,
	.has_overlay = 1, .overlay_needs_physical = 1,
};

static const struct intel_device_info intel_845g_info = {
	.gen = 2, .num_pipes = 1,
	.has_overlay = 1, .overlay_needs_physical = 1,
};

static const struct intel_device_info intel_i85x_info = {
	.gen = 2, .is_i85x = 1, .is_mobile = 1, .num_pipes = 2,
	.cursor_needs_physical = 1,
	.has_overlay = 1, .overlay_needs_physical = 1,
};

static const struct intel_device_info intel_i865g_info = {
	.gen = 2, .num_pipes = 1,
	.has_overlay = 1, .overlay_needs_physical = 1,
};

static const struct intel_device_info intel_i915g_info = {
	.gen = 3, .is_i915g = 1, .cursor_needs_physical = 1, .num_pipes = 2,
	.has_overlay = 1, .overlay_needs_physical = 1,
};
static const struct intel_device_info intel_i915gm_info = {
	.gen = 3, .is_mobile = 1, .num_pipes = 2,
	.cursor_needs_physical = 1,
	.has_overlay = 1, .overlay_needs_physical = 1,
	.supports_tv = 1,
};
static const struct intel_device_info intel_i945g_info = {
	.gen = 3, .has_hotplug = 1, .cursor_needs_physical = 1, .num_pipes = 2,
	.has_overlay = 1, .overlay_needs_physical = 1,
};
static const struct intel_device_info intel_i945gm_info = {
	.gen = 3, .is_i945gm = 1, .is_mobile = 1, .num_pipes = 2,
	.has_hotplug = 1, .cursor_needs_physical = 1,
	.has_overlay = 1, .overlay_needs_physical = 1,
	.supports_tv = 1,
};

static const struct intel_device_info intel_i965g_info = {
	.gen = 4, .is_broadwater = 1, .num_pipes = 2,
	.has_hotplug = 1,
	.has_overlay = 1,
};

static const struct intel_device_info intel_i965gm_info = {
	.gen = 4, .is_crestline = 1, .num_pipes = 2,
	.is_mobile = 1, .has_fbc = 1, .has_hotplug = 1,
	.has_overlay = 1,
	.supports_tv = 1,
};

static const struct intel_device_info intel_g33_info = {
	.gen = 3, .is_g33 = 1, .num_pipes = 2,
	.need_gfx_hws = 1, .has_hotplug = 1,
	.has_overlay = 1,
};

static const struct intel_device_info intel_g45_info = {
	.gen = 4, .is_g4x = 1, .need_gfx_hws = 1, .num_pipes = 2,
	.has_pipe_cxsr = 1, .has_hotplug = 1,
	.has_bsd_ring = 1,
};

static const struct intel_device_info intel_gm45_info = {
	.gen = 4, .is_g4x = 1, .num_pipes = 2,
	.is_mobile = 1, .need_gfx_hws = 1, .has_fbc = 1,
	.has_pipe_cxsr = 1, .has_hotplug = 1,
	.supports_tv = 1,
	.has_bsd_ring = 1,
};

static const struct intel_device_info intel_pineview_info = {
	.gen = 3, .is_g33 = 1, .is_pineview = 1, .is_mobile = 1, .num_pipes = 2,
	.need_gfx_hws = 1, .has_hotplug = 1,
	.has_overlay = 1,
};

static const struct intel_device_info intel_ironlake_d_info = {
	.gen = 5, .num_pipes = 2,
	.need_gfx_hws = 1, .has_hotplug = 1,
	.has_bsd_ring = 1,
};

static const struct intel_device_info intel_ironlake_m_info = {
	.gen = 5, .is_mobile = 1, .num_pipes = 2,
	.need_gfx_hws = 1, .has_hotplug = 1,
	.has_fbc = 1,
	.has_bsd_ring = 1,
};

static const struct intel_device_info intel_sandybridge_d_info = {
	.gen = 6, .num_pipes = 2,
	.need_gfx_hws = 1, .has_hotplug = 1,
	.has_bsd_ring = 1,
	.has_blt_ring = 1,
	.has_llc = 1,
	.has_force_wake = 1,
};

static const struct intel_device_info intel_sandybridge_m_info = {
	.gen = 6, .is_mobile = 1, .num_pipes = 2,
	.need_gfx_hws = 1, .has_hotplug = 1,
	.has_fbc = 1,
	.has_bsd_ring = 1,
	.has_blt_ring = 1,
	.has_llc = 1,
	.has_force_wake = 1,
};

#define GEN7_FEATURES  \
	.gen = 7, .num_pipes = 3, \
	.need_gfx_hws = 1, .has_hotplug = 1, \
	.has_bsd_ring = 1, \
	.has_blt_ring = 1, \
	.has_llc = 1, \
	.has_force_wake = 1

static const struct intel_device_info intel_ivybridge_d_info = {
	GEN7_FEATURES,
	.is_ivybridge = 1,
};

static const struct intel_device_info intel_ivybridge_m_info = {
	GEN7_FEATURES,
	.is_ivybridge = 1,
	.is_mobile = 1,
	.has_fbc = 1,
};

static const struct intel_device_info intel_ivybridge_q_info = {
	GEN7_FEATURES,
	.is_ivybridge = 1,
	.num_pipes = 0, /* legal, last one wins */
};

static const struct intel_device_info intel_valleyview_m_info = {
	GEN7_FEATURES,
	.is_mobile = 1,
	.num_pipes = 2,
	.is_valleyview = 1,
	.display_mmio_offset = VLV_DISPLAY_BASE,
	.has_llc = 0, /* legal, last one wins */
};

static const struct intel_device_info intel_valleyview_d_info = {
	GEN7_FEATURES,
	.num_pipes = 2,
	.is_valleyview = 1,
	.display_mmio_offset = VLV_DISPLAY_BASE,
	.has_llc = 0, /* legal, last one wins */
};

static const struct intel_device_info intel_haswell_d_info = {
	GEN7_FEATURES,
	.is_haswell = 1,
	.has_ddi = 1,
	.has_fpga_dbg = 1,
	.has_vebox_ring = 1,
};

static const struct intel_device_info intel_haswell_m_info = {
	GEN7_FEATURES,
	.is_haswell = 1,
	.is_mobile = 1,
	.has_ddi = 1,
	.has_fpga_dbg = 1,
	.has_fbc = 1,
	.has_vebox_ring = 1,
};
static struct drm_pci_id_list pciidlist[] = {
	INTEL_VGA_DEVICE(0x3577, &intel_i830_info),
	INTEL_VGA_DEVICE(0x2562, &intel_845g_info),
	INTEL_VGA_DEVICE(0x3582, &intel_i85x_info),
	INTEL_VGA_DEVICE(0x358e, &intel_i85x_info),
	INTEL_VGA_DEVICE(0x2572, &intel_i865g_info),
	INTEL_VGA_DEVICE(0x2582, &intel_i915g_info),
	INTEL_VGA_DEVICE(0x258a, &intel_i915g_info),
	INTEL_VGA_DEVICE(0x2592, &intel_i915gm_info),
	INTEL_VGA_DEVICE(0x2772, &intel_i945g_info),
	INTEL_VGA_DEVICE(0x27a2, &intel_i945gm_info),
	INTEL_VGA_DEVICE(0x27ae, &intel_i945gm_info),
	INTEL_VGA_DEVICE(0x2972, &intel_i965g_info),
	INTEL_VGA_DEVICE(0x2982, &intel_i965g_info),
	INTEL_VGA_DEVICE(0x2992, &intel_i965g_info),
	INTEL_VGA_DEVICE(0x29a2, &intel_i965g_info),
	INTEL_VGA_DEVICE(0x29b2, &intel_g33_info),
	INTEL_VGA_DEVICE(0x29c2, &intel_g33_info),
	INTEL_VGA_DEVICE(0x29d2, &intel_g33_info),
	INTEL_VGA_DEVICE(0x2a02, &intel_i965gm_info),
	INTEL_VGA_DEVICE(0x2a12, &intel_i965gm_info),
	INTEL_VGA_DEVICE(0x2a42, &intel_gm45_info),
	INTEL_VGA_DEVICE(0x2e02, &intel_g45_info),
	INTEL_VGA_DEVICE(0x2e12, &intel_g45_info),
	INTEL_VGA_DEVICE(0x2e22, &intel_g45_info),
	INTEL_VGA_DEVICE(0x2e32, &intel_g45_info),
	INTEL_VGA_DEVICE(0x2e42, &intel_g45_info),
	INTEL_VGA_DEVICE(0x2e92, &intel_g45_info),		/* B43_G.1 */
	INTEL_VGA_DEVICE(0xa001, &intel_pineview_info),
	INTEL_VGA_DEVICE(0xa011, &intel_pineview_info),
	INTEL_VGA_DEVICE(0x0042, &intel_ironlake_d_info),
	INTEL_VGA_DEVICE(0x0046, &intel_ironlake_m_info),
	INTEL_VGA_DEVICE(0x0102, &intel_sandybridge_d_info),
	INTEL_VGA_DEVICE(0x0112, &intel_sandybridge_d_info),
	INTEL_VGA_DEVICE(0x0122, &intel_sandybridge_d_info),
	INTEL_VGA_DEVICE(0x0106, &intel_sandybridge_m_info),
	INTEL_VGA_DEVICE(0x0116, &intel_sandybridge_m_info),
	INTEL_VGA_DEVICE(0x0126, &intel_sandybridge_m_info),
	INTEL_VGA_DEVICE(0x010A, &intel_sandybridge_d_info),
	INTEL_VGA_DEVICE(0x0156, &intel_ivybridge_m_info), /* GT1 mobile */
	INTEL_VGA_DEVICE(0x0166, &intel_ivybridge_m_info), /* GT2 mobile */
	INTEL_VGA_DEVICE(0x0152, &intel_ivybridge_d_info), /* GT1 desktop */
	INTEL_VGA_DEVICE(0x0162, &intel_ivybridge_d_info), /* GT2 desktop */
	INTEL_VGA_DEVICE(0x015a, &intel_ivybridge_d_info), /* GT1 server */
	INTEL_VGA_DEVICE(0x016a, &intel_ivybridge_d_info), /* GT2 server */
	INTEL_VGA_DEVICE(0x0402, &intel_haswell_d_info), /* GT1 desktop */
	INTEL_VGA_DEVICE(0x0412, &intel_haswell_d_info), /* GT2 desktop */
	INTEL_VGA_DEVICE(0x0422, &intel_haswell_d_info), /* GT3 desktop */
	INTEL_VGA_DEVICE(0x040a, &intel_haswell_d_info), /* GT1 server */
	INTEL_VGA_DEVICE(0x041a, &intel_haswell_d_info), /* GT2 server */
	INTEL_VGA_DEVICE(0x042a, &intel_haswell_d_info), /* GT3 server */
	INTEL_VGA_DEVICE(0x0406, &intel_haswell_m_info), /* GT1 mobile */
	INTEL_VGA_DEVICE(0x0416, &intel_haswell_m_info), /* GT2 mobile */
	INTEL_VGA_DEVICE(0x0426, &intel_haswell_m_info), /* GT3 mobile */
	INTEL_VGA_DEVICE(0x040B, &intel_haswell_d_info), /* GT1 reserved */
	INTEL_VGA_DEVICE(0x041B, &intel_haswell_d_info), /* GT2 reserved */
	INTEL_VGA_DEVICE(0x042B, &intel_haswell_d_info), /* GT3 reserved */
	INTEL_VGA_DEVICE(0x040E, &intel_haswell_d_info), /* GT1 reserved */
	INTEL_VGA_DEVICE(0x041E, &intel_haswell_d_info), /* GT2 reserved */
	INTEL_VGA_DEVICE(0x042E, &intel_haswell_d_info), /* GT3 reserved */
	INTEL_VGA_DEVICE(0x0C02, &intel_haswell_d_info), /* SDV GT1 desktop */
	INTEL_VGA_DEVICE(0x0C12, &intel_haswell_d_info), /* SDV GT2 desktop */
	INTEL_VGA_DEVICE(0x0C22, &intel_haswell_d_info), /* SDV GT3 desktop */
	INTEL_VGA_DEVICE(0x0C0A, &intel_haswell_d_info), /* SDV GT1 server */
	INTEL_VGA_DEVICE(0x0C1A, &intel_haswell_d_info), /* SDV GT2 server */
	INTEL_VGA_DEVICE(0x0C2A, &intel_haswell_d_info), /* SDV GT3 server */
	INTEL_VGA_DEVICE(0x0C06, &intel_haswell_m_info), /* SDV GT1 mobile */
	INTEL_VGA_DEVICE(0x0C16, &intel_haswell_m_info), /* SDV GT2 mobile */
	INTEL_VGA_DEVICE(0x0C26, &intel_haswell_m_info), /* SDV GT3 mobile */
	INTEL_VGA_DEVICE(0x0C0B, &intel_haswell_d_info), /* SDV GT1 reserved */
	INTEL_VGA_DEVICE(0x0C1B, &intel_haswell_d_info), /* SDV GT2 reserved */
	INTEL_VGA_DEVICE(0x0C2B, &intel_haswell_d_info), /* SDV GT3 reserved */
	INTEL_VGA_DEVICE(0x0C0E, &intel_haswell_d_info), /* SDV GT1 reserved */
	INTEL_VGA_DEVICE(0x0C1E, &intel_haswell_d_info), /* SDV GT2 reserved */
	INTEL_VGA_DEVICE(0x0C2E, &intel_haswell_d_info), /* SDV GT3 reserved */
	INTEL_VGA_DEVICE(0x0A02, &intel_haswell_d_info), /* ULT GT1 desktop */
	INTEL_VGA_DEVICE(0x0A12, &intel_haswell_d_info), /* ULT GT2 desktop */
	INTEL_VGA_DEVICE(0x0A22, &intel_haswell_d_info), /* ULT GT3 desktop */
	INTEL_VGA_DEVICE(0x0A0A, &intel_haswell_d_info), /* ULT GT1 server */
	INTEL_VGA_DEVICE(0x0A1A, &intel_haswell_d_info), /* ULT GT2 server */
	INTEL_VGA_DEVICE(0x0A2A, &intel_haswell_d_info), /* ULT GT3 server */
	INTEL_VGA_DEVICE(0x0A06, &intel_haswell_m_info), /* ULT GT1 mobile */
	INTEL_VGA_DEVICE(0x0A16, &intel_haswell_m_info), /* ULT GT2 mobile */
	INTEL_VGA_DEVICE(0x0A26, &intel_haswell_m_info), /* ULT GT3 mobile */
	INTEL_VGA_DEVICE(0x0A0B, &intel_haswell_d_info), /* ULT GT1 reserved */
	INTEL_VGA_DEVICE(0x0A1B, &intel_haswell_d_info), /* ULT GT2 reserved */
	INTEL_VGA_DEVICE(0x0A2B, &intel_haswell_d_info), /* ULT GT3 reserved */
	INTEL_VGA_DEVICE(0x0A0E, &intel_haswell_m_info), /* ULT GT1 reserved */
	INTEL_VGA_DEVICE(0x0A1E, &intel_haswell_m_info), /* ULT GT2 reserved */
	INTEL_VGA_DEVICE(0x0A2E, &intel_haswell_m_info), /* ULT GT3 reserved */
	INTEL_VGA_DEVICE(0x0D02, &intel_haswell_d_info), /* CRW GT1 desktop */
	INTEL_VGA_DEVICE(0x0D12, &intel_haswell_d_info), /* CRW GT2 desktop */
	INTEL_VGA_DEVICE(0x0D22, &intel_haswell_d_info), /* CRW GT3 desktop */
	INTEL_VGA_DEVICE(0x0D0A, &intel_haswell_d_info), /* CRW GT1 server */
	INTEL_VGA_DEVICE(0x0D1A, &intel_haswell_d_info), /* CRW GT2 server */
	INTEL_VGA_DEVICE(0x0D2A, &intel_haswell_d_info), /* CRW GT3 server */
	INTEL_VGA_DEVICE(0x0D06, &intel_haswell_m_info), /* CRW GT1 mobile */
	INTEL_VGA_DEVICE(0x0D16, &intel_haswell_m_info), /* CRW GT2 mobile */
	INTEL_VGA_DEVICE(0x0D26, &intel_haswell_m_info), /* CRW GT3 mobile */
	INTEL_VGA_DEVICE(0x0D0B, &intel_haswell_d_info), /* CRW GT1 reserved */
	INTEL_VGA_DEVICE(0x0D1B, &intel_haswell_d_info), /* CRW GT2 reserved */
	INTEL_VGA_DEVICE(0x0D2B, &intel_haswell_d_info), /* CRW GT3 reserved */
	INTEL_VGA_DEVICE(0x0D0E, &intel_haswell_d_info), /* CRW GT1 reserved */
	INTEL_VGA_DEVICE(0x0D1E, &intel_haswell_d_info), /* CRW GT2 reserved */
	INTEL_VGA_DEVICE(0x0D2E, &intel_haswell_d_info), /* CRW GT3 reserved */
	INTEL_VGA_DEVICE(0x0f30, &intel_valleyview_m_info),
	INTEL_VGA_DEVICE(0x0f31, &intel_valleyview_m_info),
	INTEL_VGA_DEVICE(0x0f32, &intel_valleyview_m_info),
	INTEL_VGA_DEVICE(0x0f33, &intel_valleyview_m_info),
	INTEL_VGA_DEVICE(0x0157, &intel_valleyview_m_info),
	INTEL_VGA_DEVICE(0x0155, &intel_valleyview_d_info),
	{0, 0, 0}
};

#define PCI_VENDOR_ID_INTEL		0x8086

void intel_detect_pch (struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	dev_info_t	*isa_dip;
	int	vendor_id, device_id;
	/* LINTED */
	int	error;
	/* In all current cases, num_pipes is equivalent to the PCH_NOP setting
	 * (which really amounts to a PCH but no South Display).
	 */
	if (INTEL_INFO(dev)->num_pipes == 0) {
		dev_priv->pch_type = PCH_NOP;
		return;
	}

	/*
	 * The reason to probe ISA bridge instead of Dev31:Fun0 is to
	 * make graphics device passthrough work easy for VMM, that only
	 * need to expose ISA bridge to let driver know the real hardware
	 * underneath. This is a requirement from virtualization team.
	 */
	isa_dip = ddi_find_devinfo("isa", -1, 0);

	if (isa_dip) {
		vendor_id = ddi_prop_get_int(DDI_DEV_T_ANY, isa_dip, DDI_PROP_DONTPASS,
			"vendor-id", -1);
		DRM_DEBUG("vendor_id 0x%x", vendor_id);

		if (vendor_id == PCI_VENDOR_ID_INTEL) {
			device_id = ddi_prop_get_int(DDI_DEV_T_ANY, isa_dip, DDI_PROP_DONTPASS,
				"device-id", -1);
			DRM_DEBUG("device_id 0x%x", device_id);
			device_id &= INTEL_PCH_DEVICE_ID_MASK;
			dev_priv->pch_id = (unsigned short) device_id;
			if (device_id == INTEL_PCH_IBX_DEVICE_ID_TYPE) {
				dev_priv->pch_type = PCH_IBX;
				DRM_DEBUG_KMS("Found Ibex Peak PCH\n");
				WARN_ON(!IS_GEN5(dev));
			} else if (device_id == INTEL_PCH_CPT_DEVICE_ID_TYPE) {
				dev_priv->pch_type = PCH_CPT;
				DRM_DEBUG_KMS("Found CougarPoint PCH\n");
				WARN_ON(!(IS_GEN6(dev) || IS_IVYBRIDGE(dev)));
			} else if (device_id == INTEL_PCH_PPT_DEVICE_ID_TYPE) {
				/* PantherPoint is CPT compatible */
				dev_priv->pch_type = PCH_CPT;
				DRM_DEBUG_KMS("Found PatherPoint PCH\n");
				WARN_ON(!(IS_GEN6(dev) || IS_IVYBRIDGE(dev)));
			} else if (device_id == INTEL_PCH_LPT_DEVICE_ID_TYPE) {
				dev_priv->pch_type = PCH_LPT;
				DRM_DEBUG_KMS("Found LynxPoint PCH\n");
				WARN_ON(!IS_HASWELL(dev));
				WARN_ON(IS_ULT(dev));
			} else if (device_id == INTEL_PCH_LPT_LP_DEVICE_ID_TYPE) {
				dev_priv->pch_type = PCH_LPT;
				DRM_DEBUG_KMS("Found LynxPoint LP PCH\n");
				WARN_ON(!IS_HASWELL(dev));
				WARN_ON(!IS_ULT(dev));
			}
		}
	}
}

bool i915_semaphore_is_enabled(struct drm_device *dev)
{
	if (INTEL_INFO(dev)->gen < 6)
		return 0;

	if (i915_semaphores >= 0)
		return i915_semaphores;

#ifdef CONFIG_INTEL_IOMMU
	/* Enable semaphores on SNB when IO remapping is off */
	if (INTEL_INFO(dev)->gen == 6 && intel_iommu_gfx_mapped)
		return false;
#endif

	return 1;
}

static int i915_drm_freeze(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_crtc *crtc;

	/* ignore lid events during suspend */
	mutex_lock(&dev_priv->modeset_restore_lock);
	dev_priv->modeset_restore = MODESET_SUSPENDED;
	mutex_unlock(&dev_priv->modeset_restore_lock);

	intel_set_power_well(dev, true);

	drm_kms_helper_poll_disable(dev);

	/* XXX FIXME: pci_save_state(dev->pdev); */

	/* If KMS is active, we do the leavevt stuff here */
	if (drm_core_check_feature(dev, DRIVER_MODESET) && dev_priv->gtt.total !=0) {

		if (i915_gem_idle(dev, 0))
			DRM_ERROR("GEM idle failed, resume may fail\n");

		del_timer_sync(&dev_priv->rps.delayed_resume_timer);


		(void) drm_irq_uninstall(dev);
		dev_priv->enable_hotplug_processing = false;
		/*
		 * Disable CRTCs directly since we want to preserve sw state
		 * for _thaw.
		 */
		list_for_each_entry(crtc, struct drm_crtc, &dev->mode_config.crtc_list, head)
			dev_priv->display.crtc_disable(crtc);

		intel_modeset_suspend_hw(dev);
	}

	if (dev_priv->gtt.total !=0)
		(void) i915_save_state(dev);

	return 0;
}

int
i915_suspend(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int error;

	/*
	 * First, try to restore the "console".
	 */
	(void) drm_fb_helper_force_kernel_mode();

	if (!dev || !dev_priv) {
		DRM_ERROR("dev: %p, dev_priv: %p\n", dev, dev_priv);
		DRM_ERROR("DRM not initialized, aborting suspend.\n");
		return -ENODEV;
	}

	error = i915_drm_freeze(dev);
	if (error)
		return error;

	return 0;
}

static int
__i915_drm_thaw(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int error = 0;

	if (dev_priv->gtt.total !=0)
		(void) i915_restore_state(dev);

	/* KMS EnterVT equivalent */
	if (drm_core_check_feature(dev, DRIVER_MODESET) && dev_priv->gtt.total !=0) {
		intel_init_pch_refclk(dev);

		mutex_lock(&dev->struct_mutex);
		dev_priv->mm.suspended = 0;

		error = i915_gem_init_hw(dev);
		mutex_unlock(&dev->struct_mutex);

		/* We need working interrupts for modeset enabling ... */
		(void) drm_irq_install(dev);

		intel_modeset_init_hw(dev);
		drm_modeset_lock_all(dev);
		intel_modeset_setup_hw_state(dev, true);
		drm_modeset_unlock_all(dev);

		/*
		 * ... but also need to make sure that hotplug processing
		 * doesn't cause havoc. Like in the driver load code we don't
		 * bother with the tiny race here where we might loose hotplug
		 * notifications.
		 * */
		intel_hpd_init(dev);
		dev_priv->enable_hotplug_processing = true;
	}

	mutex_lock(&dev_priv->modeset_restore_lock);
	dev_priv->modeset_restore = MODESET_DONE;
	mutex_unlock(&dev_priv->modeset_restore_lock);

	return error;
}

static int
i915_drm_thaw(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int error = 0;

	if (dev_priv->gtt.total !=0)
		intel_gt_sanitize(dev);
	if (drm_core_check_feature(dev, DRIVER_MODESET) &&
	    dev_priv->gtt.total !=0) {
		mutex_lock(&dev->struct_mutex);
		i915_gem_restore_gtt_mappings(dev);
		mutex_unlock(&dev->struct_mutex);
	}
	__i915_drm_thaw(dev);

	return error;
}

int
i915_resume(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int ret;
	if (dev_priv->gtt.total !=0)
		intel_gt_sanitize(dev);
	if (drm_core_check_feature(dev, DRIVER_MODESET) &&
	    dev_priv->gtt.total !=0) {
		mutex_lock(&dev->struct_mutex);
		i915_gem_restore_gtt_mappings(dev);
		mutex_unlock(&dev->struct_mutex);
	}

	ret = __i915_drm_thaw(dev);
	if (ret)
		return ret;

	drm_kms_helper_poll_enable(dev);
	return 0;
}

static int i8xx_do_reset(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (IS_I85X(dev))
		return -ENODEV;

	I915_WRITE(D_STATE, I915_READ(D_STATE) | DSTATE_GFX_RESET_I830);
	POSTING_READ(D_STATE);

	if (IS_I830(dev) || IS_845G(dev)) {
		I915_WRITE(DEBUG_RESET_I830,
			   DEBUG_RESET_DISPLAY |
			   DEBUG_RESET_RENDER |
			   DEBUG_RESET_FULL);
		POSTING_READ(DEBUG_RESET_I830);
		msleep(1);

		I915_WRITE(DEBUG_RESET_I830, 0);
		POSTING_READ(DEBUG_RESET_I830);
	}

	msleep(1);

	I915_WRITE(D_STATE, I915_READ(D_STATE) & ~DSTATE_GFX_RESET_I830);
	POSTING_READ(D_STATE);

	return 0;
}

static int i965_reset_complete(struct drm_device *dev)
{
	u8 gdrst;
	(void) pci_read_config_byte(dev->pdev, I965_GDRST, &gdrst);
	return (gdrst & GRDOM_RESET_ENABLE) == 0;
}

static int i965_do_reset(struct drm_device *dev)
{
	int ret;
	u8 gdrst;

	/*
	 * Set the domains we want to reset (GRDOM/bits 2 and 3) as
	 * well as the reset bit (GR/bit 0).  Setting the GR bit
	 * triggers the reset; when done, the hardware will clear it.
	 */
	pci_read_config_byte(dev->pdev, I965_GDRST, &gdrst);
	pci_write_config_byte(dev->pdev, I965_GDRST,
			      gdrst | GRDOM_RENDER |
			      GRDOM_RESET_ENABLE);
	ret =  wait_for(i965_reset_complete(dev), 500);
	if (ret)
		return ret;

	/* We can't reset render&media without also resetting display ... */
	pci_read_config_byte(dev->pdev, I965_GDRST, &gdrst);
	pci_write_config_byte(dev->pdev, I965_GDRST,
			      gdrst | GRDOM_MEDIA |
			      GRDOM_RESET_ENABLE);

	return wait_for(i965_reset_complete(dev), 500);
}

static int ironlake_do_reset(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 gdrst;
	int ret;

	gdrst = I915_READ(MCHBAR_MIRROR_BASE + ILK_GDSR);
	gdrst &= ~GRDOM_MASK;
	I915_WRITE(MCHBAR_MIRROR_BASE + ILK_GDSR,
		   gdrst | GRDOM_RENDER | GRDOM_RESET_ENABLE);
	ret = wait_for(I915_READ(MCHBAR_MIRROR_BASE + ILK_GDSR) & 0x1, 500);
	if (ret)
		return ret;

	/* We can't reset render&media without also resetting display ... */
	gdrst = I915_READ(MCHBAR_MIRROR_BASE + ILK_GDSR);
	gdrst &= ~GRDOM_MASK;
	I915_WRITE(MCHBAR_MIRROR_BASE + ILK_GDSR,
		   gdrst | GRDOM_MEDIA | GRDOM_RESET_ENABLE);
	return wait_for(I915_READ(MCHBAR_MIRROR_BASE + ILK_GDSR) & 0x1, 500);
}

static int gen6_do_reset(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int	ret;
	unsigned long irqflags;

	/* Hold gt_lock across reset to prevent any register access
	 * with forcewake not set correctly
	 */
	spin_lock_irqsave(&dev_priv->gt_lock, irqflags);

	/* Reset the chip */

	/* GEN6_GDRST is not in the gt power well, no need to check
	 * for fifo space for the write or forcewake the chip for
	 * the read
	 */
	I915_WRITE_NOTRACE(GEN6_GDRST, GEN6_GRDOM_FULL);

	/* Spin waiting for the device to ack the reset request */
	ret = wait_for((I915_READ_NOTRACE(GEN6_GDRST) & GEN6_GRDOM_FULL) == 0, 500);

	/* If reset with a user forcewake, try to restore, otherwise turn it off */
	if (dev_priv->forcewake_count)
		dev_priv->gt.force_wake_get(dev_priv);
	else
		dev_priv->gt.force_wake_put(dev_priv);

	/* Restore fifo count */
	dev_priv->gt_fifo_count = I915_READ_NOTRACE(GT_FIFO_FREE_ENTRIES);

	spin_unlock_irqrestore(&dev_priv->gt_lock, irqflags);
	return ret;
}

int intel_gpu_reset(struct drm_device *dev)
{
	switch (INTEL_INFO(dev)->gen) {
	case 7:
	case 6: return gen6_do_reset(dev);
	case 5: return ironlake_do_reset(dev);
	case 4: return i965_do_reset(dev);
	case 2: return i8xx_do_reset(dev);
	default: return -ENODEV;
	}
}

/**
 * i915_reset - reset chip after a hang
 * @dev: drm device to reset
 *
 * Reset the chip.  Useful if a hang is detected. Returns zero on successful
 * reset or otherwise an error code.
 *
 * Procedure is fairly simple:
 *   - reset the chip using the reset reg
 *   - re-init context state
 *   - re-init hardware status page
 *   - re-init ring buffer
 *   - re-init interrupt state
 *   - re-init display
 */
int i915_reset(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct timeval cur_time;
	bool simulated;
	int ret;

	if (!i915_try_reset)
		return 0;

	mutex_lock(&dev->struct_mutex);

	i915_gem_reset(dev);

	simulated = dev_priv->gpu_error.stop_rings != 0;

	do_gettimeofday(&cur_time);
	if (!simulated && cur_time.tv_sec - dev_priv->gpu_error.last_reset < 5) {
		ret = -ENODEV;
		DRM_ERROR("GPU hanging too fast, wait 5 secons for another reset");
		mutex_unlock(&dev->struct_mutex);
		return ret;
	} else {
		ret = intel_gpu_reset(dev);

		/* Also reset the gpu hangman. */
		if (simulated) {
			DRM_INFO("Simulated gpu hang, resetting stop_rings\n");
			dev_priv->gpu_error.stop_rings = 0;
			if (ret == -ENODEV) {
				DRM_ERROR("Reset not implemented, but ignoring "
					  "error for simulated gpu hangs\n");
				ret = 0;
			}
		} else {
			do_gettimeofday(&cur_time);
			dev_priv->gpu_error.last_reset = cur_time.tv_sec;
		}
	}
	if (ret) {
		DRM_ERROR("Failed to reset chip.\n");
		mutex_unlock(&dev->struct_mutex);
		return ret;
	}

	/* Ok, now get things going again... */

	/*
	 * Everything depends on having the GTT running, so we need to start
	 * there.  Fortunately we don't need to do this unless we reset the
	 * chip at a PCI level.
	 *
	 * Next we need to restore the context, but we don't use those
	 * yet either...
	 *
	 * Ring buffer needs to be re-initialized in the KMS case, or if X
	 * was running at the time of the reset (i.e. we weren't VT
	 * switched away).
	 */
	if (drm_core_check_feature(dev, DRIVER_MODESET) ||
	    !dev_priv->mm.suspended) {
		struct intel_ring_buffer *ring;
		int i;

		dev_priv->mm.suspended = 0;

		i915_gem_init_swizzling(dev);

		for_each_ring(ring, dev_priv, i)
			ring->init(ring);

		i915_gem_context_init(dev);
		if (dev_priv->mm.aliasing_ppgtt) {
			ret = dev_priv->mm.aliasing_ppgtt->enable(dev);
			if (ret)
				i915_gem_cleanup_aliasing_ppgtt(dev);
		}

		/*
		 * It would make sense to re-init all the other hw state, at
		 * least the rps/rc6/emon init done within modeset_init_hw. For
		 * some unknown reason, this blows up my ilk, so don't.
		 */

		mutex_unlock(&dev->struct_mutex);

		(void) drm_irq_uninstall(dev);
		if (drm_irq_install(dev)) {
			DRM_ERROR("Could not install irq for driver.\n");
			return -EIO;
		}
		intel_hpd_init(dev);
	} else {
		mutex_unlock(&dev->struct_mutex);
	}

	return 0;
}

static struct drm_driver driver = {
	/* don't use mtrr's here, the Xserver or user space app should
	 * deal with them for intel hardware.
	 */
	.driver_features =
	    DRIVER_USE_AGP | DRIVER_REQUIRE_AGP | /* DRIVER_USE_MTRR |*/
	    DRIVER_HAVE_IRQ | DRIVER_IRQ_SHARED | DRIVER_GEM,
	.load = i915_driver_load,
	.unload = i915_driver_unload,
	.firstopen = i915_driver_firstopen,
	.open = i915_driver_open,
	.lastclose = i915_driver_lastclose,
	.preclose = i915_driver_preclose,
	.postclose = i915_driver_postclose,

	/* Used in place of i915_pm_ops for non-DRIVER_MODESET */
	.device_is_agp = i915_driver_device_is_agp,
	.master_create = i915_master_create,
	.master_destroy = i915_master_destroy,
	/* OSOL begin */
	.entervt = i915_driver_entervt,
	.leavevt = i915_driver_leavevt,
	.agp_support_detect = i915_driver_agp_support_detect,
	/* OSOL end */
#if defined(CONFIG_DEBUG_FS)
	.debugfs_init = i915_debugfs_init,
	.debugfs_cleanup = i915_debugfs_cleanup,
#endif
	.gem_init_object = i915_gem_init_object,
	.gem_free_object = i915_gem_free_object,
	/*.gem_vm_ops = &i915_gem_vm_ops,*/
	.gem_fault = i915_gem_fault,
	.ioctls = i915_ioctls,

	.id_table = pciidlist,

	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = DRIVER_MAJOR,
	.minor = DRIVER_MINOR,
	.patchlevel = DRIVER_PATCHLEVEL,
};

static int
i915_attach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	struct drm_device *dev;
	int ret, item;

	item = ddi_get_instance(dip);

	switch (cmd) {
	case DDI_ATTACH:
		if (ddi_soft_state_zalloc(i915_statep, item) != DDI_SUCCESS) {
			DRM_ERROR("failed to alloc softstate, item = %d", item);
			return (DDI_FAILURE);
		}

		dev = ddi_get_soft_state(i915_statep, item);
		if (!dev) {
			DRM_ERROR("cannot get soft state");
			return (DDI_FAILURE);
		}

		dev->devinfo = dip;

		if (!(driver.driver_features & DRIVER_MODESET))
			driver.get_vblank_timestamp = NULL;

		ret = drm_init(dev, &driver);
		if (ret != DDI_SUCCESS)
			(void) ddi_soft_state_free(i915_statep, item);

		return (ret);

	case DDI_RESUME:
		dev = ddi_get_soft_state(i915_statep, item);
		if (!dev) {
			DRM_ERROR("cannot get soft state");
			return (DDI_FAILURE);
		}

		return (i915_resume(dev));
	}

	DRM_ERROR("only supports attach or resume");
	return (DDI_FAILURE);
}

static int
i915_detach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
	struct drm_device *dev;
	int item;

	item = ddi_get_instance(dip);
	dev = ddi_get_soft_state(i915_statep, item);
	if (!dev) {
		DRM_ERROR("cannot get soft state");
		return (DDI_FAILURE);
	}

	switch (cmd) {
	case DDI_DETACH:
		drm_exit(dev);
		(void) ddi_soft_state_free(i915_statep, item);
		return (DDI_SUCCESS);

	case DDI_SUSPEND:
		return (i915_suspend(dev));
	}

	DRM_ERROR("only supports detach or suspend");
	return (DDI_FAILURE);
}

static int
/* LINTED */
i915_info(dev_info_t *dip, ddi_info_cmd_t infocmd, void *arg, void **result)
{
	struct drm_minor *minor;

	minor = idr_find(&drm_minors_idr, DRM_DEV2MINOR((dev_t)arg));
	if (!minor)
		return (DDI_FAILURE);
	if (!minor->dev || !minor->dev->devinfo)
		return (DDI_FAILURE);

	switch (infocmd) {
	case DDI_INFO_DEVT2DEVINFO:
		*result = (void *)minor->dev->devinfo;
		return (DDI_SUCCESS);

	case DDI_INFO_DEVT2INSTANCE:
		*result = (void *)(uintptr_t)ddi_get_instance(minor->dev->devinfo);
		return (DDI_SUCCESS);
	}

	return (DDI_FAILURE);
}

static int
i915_quiesce(dev_info_t *dip)
{
	struct drm_device *dev;
	struct drm_i915_private *dev_priv;
	struct drm_crtc *crtc;
	int ret = 0;

	dev = ddi_get_soft_state(i915_statep, ddi_get_instance(dip));

	if (!dev)
		return (DDI_FAILURE);

	dev_priv = dev->dev_private;

	if (dev_priv && dev_priv->gtt.total !=0) {



		(void) drm_fb_helper_force_kernel_mode();

		mutex_lock(&dev->struct_mutex);
		ret = i915_gpu_idle(dev);
		if (ret)
			DRM_ERROR("failed to idle hardware: %d\n", ret);
		i915_gem_retire_requests(dev);
		mutex_unlock(&dev->struct_mutex);

		if (dev_priv->fbcon_obj != NULL)
			intel_fbdev_fini(dev);

		drm_kms_helper_poll_fini(dev);
		mutex_lock(&dev->struct_mutex);

		list_for_each_entry(crtc, struct drm_crtc, &dev->mode_config.crtc_list, head) {
			/* Skip inactive CRTCs */
			if (!crtc->fb)
				continue;

			intel_increase_pllclock(crtc);
		}

		intel_disable_fbc(dev);

		intel_disable_gt_powersave(dev);

		ironlake_teardown_rc6(dev);

		mutex_unlock(&dev->struct_mutex);
		drm_mode_config_cleanup(dev);

		mutex_lock(&dev->struct_mutex);
		i915_gem_free_all_phys_object(dev);
		i915_gem_cleanup_ringbuffer(dev);
		i915_gem_context_fini(dev);
		mutex_unlock(&dev->struct_mutex);

		i915_gem_cleanup_aliasing_ppgtt(dev);
		i915_gem_cleanup_stolen(dev);
		drm_mm_takedown(&dev_priv->mm.stolen);
		intel_cleanup_overlay(dev);

		i915_gem_lastclose(dev);

		if (dev_priv->gtt.scratch_page)
			teardown_scratch_page(dev);

		if (MDB_TRACK_ENABLE) {
			struct batch_info_list *r_list, *list_temp;
			list_for_each_entry_safe(r_list, list_temp, struct batch_info_list, &dev_priv->batch_list, head) {
				list_del(&r_list->head);
				drm_free(r_list->obj_list, r_list->num * sizeof(caddr_t), DRM_MEM_MAPS);
				drm_free(r_list, sizeof (struct batch_info_list), DRM_MEM_MAPS);
			}
			list_del(&dev_priv->batch_list);
		}

		if (dev->old_gtt) {
			intel_rw_gtt(dev, dev->old_gtt_size,
				0, (void *) dev->old_gtt, 1);
			kmem_free(dev->old_gtt, dev->old_gtt_size);
		}
	}

	return (DDI_SUCCESS);
}

static int __init i915_init(void)
{
	driver.num_ioctls = i915_max_ioctl;

	driver.driver_features |= DRIVER_MODESET;

	return 0;
}

static void __exit i915_exit(void)
{

}

int
_init(void)
{
	int ret;

	ret = ddi_soft_state_init(&i915_statep,
	    sizeof (struct drm_device), DRM_MAX_INSTANCES);
	if (ret)
		return (ret);

	ret = i915_init();
	if (ret) {
		ddi_soft_state_fini(&i915_statep);
		return (ret);
	}

	ret = mod_install(&modlinkage);
	if (ret) {
		i915_exit();
		ddi_soft_state_fini(&i915_statep);
		return (ret);
	}

	return (ret);
}

int
_fini(void)
{
	int ret;

	ret = mod_remove(&modlinkage);
	if (ret)
		return (ret);

	i915_exit();

	ddi_soft_state_fini(&i915_statep);

	return (ret);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}

/* We give fast paths for the really cool registers */
#define NEEDS_FORCE_WAKE(dev_priv, reg) \
	((HAS_FORCE_WAKE((dev_priv)->dev)) && \
	((reg) < 0x40000) && \
	((reg) != FORCEWAKE))

static void
ilk_dummy_write(struct drm_i915_private *dev_priv)
{
	/* WaIssueDummyWriteToWakeupFromRC6: Issue a dummy write to wake up the
	 * chip from rc6 before touching it for real. MI_MODE is masked, hence
	 * harmless to write 0 into. */
	I915_WRITE_NOTRACE(MI_MODE, 0);
}

static void
hsw_unclaimed_reg_clear(struct drm_i915_private *dev_priv, u32 reg)
{
	if (HAS_FPGA_DBG_UNCLAIMED(dev_priv->dev) &&
	    (I915_READ_NOTRACE(FPGA_DBG) & FPGA_DBG_RM_NOCLAIM)) {
		DRM_INFO("Unknown unclaimed register before writing to %x\n",
			  reg);
		I915_WRITE_NOTRACE(FPGA_DBG, FPGA_DBG_RM_NOCLAIM);
	}
}

static void
hsw_unclaimed_reg_check(struct drm_i915_private *dev_priv, u32 reg)
{
	if (HAS_FPGA_DBG_UNCLAIMED(dev_priv->dev) &&
	    (I915_READ_NOTRACE(FPGA_DBG) & FPGA_DBG_RM_NOCLAIM)) {
		DRM_INFO("Unclaimed write to %x\n", reg);
		I915_WRITE_NOTRACE(FPGA_DBG, FPGA_DBG_RM_NOCLAIM);
	}
}

u8 i915_read8(struct drm_i915_private *dev_priv, u32 reg)
{
	u8 val;

	if (IS_GEN5(dev_priv->dev))
		ilk_dummy_write(dev_priv);

	if (NEEDS_FORCE_WAKE(dev_priv, reg)) {
		unsigned long irqflags;
		spin_lock_irqsave(&dev_priv->gt_lock, irqflags);
		if (dev_priv->forcewake_count == 0)
			dev_priv->gt.force_wake_get(dev_priv);
		val = DRM_READ8(dev_priv->regs, reg);
		if (dev_priv->forcewake_count == 0)
			dev_priv->gt.force_wake_put(dev_priv);
		spin_unlock_irqrestore(&dev_priv->gt_lock, irqflags);
	} else
		val = DRM_READ8(dev_priv->regs, (reg));
	return val;
}

u16 i915_read16(struct drm_i915_private *dev_priv, u32 reg)
{
	u16 val;

	if (IS_GEN5(dev_priv->dev))
		ilk_dummy_write(dev_priv);

	if (NEEDS_FORCE_WAKE(dev_priv, reg)) {
		unsigned long irqflags;
		spin_lock_irqsave(&dev_priv->gt_lock, irqflags);
		if (dev_priv->forcewake_count == 0)
			dev_priv->gt.force_wake_get(dev_priv);
		val = DRM_READ16(dev_priv->regs, reg);
		if (dev_priv->forcewake_count == 0)
			dev_priv->gt.force_wake_get(dev_priv);
		spin_unlock_irqrestore(&dev_priv->gt_lock, irqflags);
	} else
		val = DRM_READ16(dev_priv->regs, (reg));
	return val;
}

u32 i915_read32(struct drm_i915_private *dev_priv, u32 reg)
{
	u32 val;

	if (IS_GEN5(dev_priv->dev))
		ilk_dummy_write(dev_priv);

	if (NEEDS_FORCE_WAKE(dev_priv, reg)) {
		unsigned long irqflags;
		spin_lock_irqsave(&dev_priv->gt_lock, irqflags);
		if (dev_priv->forcewake_count == 0)
			dev_priv->gt.force_wake_get(dev_priv);
		val = DRM_READ32(dev_priv->regs, reg);
		if (dev_priv->forcewake_count == 0)
			dev_priv->gt.force_wake_get(dev_priv);
		spin_unlock_irqrestore(&dev_priv->gt_lock, irqflags);
	} else
		val = DRM_READ32(dev_priv->regs, (reg));
	return val;
}

u64 i915_read64(struct drm_i915_private *dev_priv, u32 reg)
{
	u64 val;

	if (IS_GEN5(dev_priv->dev))
		ilk_dummy_write(dev_priv);

	if (NEEDS_FORCE_WAKE(dev_priv, reg)) {
		unsigned long irqflags;
		spin_lock_irqsave(&dev_priv->gt_lock, irqflags);
		if (dev_priv->forcewake_count == 0)
			dev_priv->gt.force_wake_get(dev_priv);
		val = DRM_READ64(dev_priv->regs, reg);
		if (dev_priv->forcewake_count == 0)
			dev_priv->gt.force_wake_get(dev_priv);
		spin_unlock_irqrestore(&dev_priv->gt_lock, irqflags);
	} else
		val = DRM_READ64(dev_priv->regs, (reg));
	return val;
}

void i915_write8(struct drm_i915_private *dev_priv, u32 reg,
			u8 val)
{
	unsigned long irqflags;
	u32 __fifo_ret = 0;

	spin_lock_irqsave(&dev_priv->gt_lock, irqflags);
	if (NEEDS_FORCE_WAKE(dev_priv, reg))
		__fifo_ret = __gen6_gt_wait_for_fifo(dev_priv);

	if (IS_GEN5(dev_priv->dev))
		ilk_dummy_write(dev_priv);

	hsw_unclaimed_reg_clear(dev_priv, reg);

	DRM_WRITE8(dev_priv->regs, (reg), (val));
	if (__fifo_ret)
		gen6_gt_check_fifodbg(dev_priv);
	hsw_unclaimed_reg_check(dev_priv, reg);
	spin_unlock_irqrestore(&dev_priv->gt_lock, irqflags);
}

void i915_write16(struct drm_i915_private *dev_priv, u32 reg,
			u16 val)
{
	unsigned long irqflags;
	u32 __fifo_ret = 0;

	spin_lock_irqsave(&dev_priv->gt_lock, irqflags);
	if (NEEDS_FORCE_WAKE(dev_priv, reg))
		__fifo_ret = __gen6_gt_wait_for_fifo(dev_priv);

	if (IS_GEN5(dev_priv->dev))
		ilk_dummy_write(dev_priv);

	hsw_unclaimed_reg_clear(dev_priv, reg);

	DRM_WRITE16(dev_priv->regs, (reg), (val));
	if (__fifo_ret)
		gen6_gt_check_fifodbg(dev_priv);
	hsw_unclaimed_reg_check(dev_priv, reg);
	spin_unlock_irqrestore(&dev_priv->gt_lock, irqflags);
}

void i915_write32(struct drm_i915_private *dev_priv, u32 reg,
			u32 val)
{
	unsigned long irqflags;
	u32 __fifo_ret = 0;

	spin_lock_irqsave(&dev_priv->gt_lock, irqflags);
	if (NEEDS_FORCE_WAKE(dev_priv, reg))
		__fifo_ret = __gen6_gt_wait_for_fifo(dev_priv);

	if (IS_GEN5(dev_priv->dev))
		ilk_dummy_write(dev_priv);

	hsw_unclaimed_reg_clear(dev_priv, reg);

	DRM_WRITE32(dev_priv->regs, (reg), (val));
	if (__fifo_ret)
		gen6_gt_check_fifodbg(dev_priv);
	hsw_unclaimed_reg_check(dev_priv, reg);
	spin_unlock_irqrestore(&dev_priv->gt_lock, irqflags);
}

void i915_write64(struct drm_i915_private *dev_priv, u32 reg,
			u64 val)
{
	unsigned long irqflags;
	u32 __fifo_ret = 0;

	spin_lock_irqsave(&dev_priv->gt_lock, irqflags);
	if (NEEDS_FORCE_WAKE(dev_priv, reg))
		__fifo_ret = __gen6_gt_wait_for_fifo(dev_priv);

	if (IS_GEN5(dev_priv->dev))
		ilk_dummy_write(dev_priv);

	hsw_unclaimed_reg_clear(dev_priv, reg);

	DRM_WRITE64(dev_priv->regs, (reg), (val));
	if (__fifo_ret)
		gen6_gt_check_fifodbg(dev_priv);
	hsw_unclaimed_reg_check(dev_priv, reg);
	spin_unlock_irqrestore(&dev_priv->gt_lock, irqflags);
}

#define __i915_read(x) \
u ## x i915_read ## x(struct drm_i915_private *dev_priv, u32 reg);

__i915_read(8)
__i915_read(16)
__i915_read(32)
__i915_read(64)
#undef __i915_read

#define __i915_write(x)	\
void i915_write ## x(struct drm_i915_private *dev_priv, u32 reg,	\
				u ## x val);

__i915_write(8)
__i915_write(16)
__i915_write(32)
__i915_write(64)
#undef __i915_write

static const struct register_whitelist {
	uint64_t offset;
	uint32_t size;
	uint32_t gen_bitmask; /* support gens, 0x10 for 4, 0x30 for 4 and 5, etc. */
} whitelist[] = {
	{ RING_TIMESTAMP(RENDER_RING_BASE), 8, 0xF0 },
};

int i915_reg_read_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_i915_reg_read *reg = data;
	struct register_whitelist const *entry = whitelist;
	int i;

	for (i = 0; i < ARRAY_SIZE(whitelist); i++, entry++) {
		if (entry->offset == reg->offset &&
		    (1 << INTEL_INFO(dev)->gen & entry->gen_bitmask))
			break;
	}

	if (i == ARRAY_SIZE(whitelist))
		return -EINVAL;

	switch (entry->size) {
	case 8:
		reg->val = I915_READ64(reg->offset);
		break;
	case 4:
		reg->val = I915_READ(reg->offset);
		break;
	case 2:
		reg->val = I915_READ16(reg->offset);
		break;
	case 1:
		reg->val = I915_READ8(reg->offset);
		break;
	default:
		WARN_ON(1);
		return -EINVAL;
	}

	return 0;
}

void i915_gem_chipset_flush(struct drm_device *dev)
{
	if (INTEL_INFO(dev)->gen < 6)
		drm_agp_chipset_flush(dev);
}

void i915_driver_agp_support_detect(struct drm_device *dev, unsigned long flags)
{
	struct intel_device_info *info;
	info = (struct intel_device_info *) flags;

	/* Remove AGP support for GEN6+ platform */
	if (info->gen >= 6)
		driver.driver_features &= ~DRIVER_USE_AGP;
}
