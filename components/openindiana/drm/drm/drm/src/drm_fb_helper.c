/*
 * Copyright (c) 2012, 2013, Oracle and/or its affiliates. All rights reserved.
 * Copyright (c) 2015, 2016 Intel-DRM/KMS Backport to OpenSolaris by Martin Bochnig opensxce@gmx.org
 */

/*
 * Copyright (c) 2006-2009 Red Hat Inc.
 * Copyright (c) 2006-2008, 2013, Intel Corporation
 * Copyright (c) 2007 Dave Airlie <airlied@linux.ie>
 *
 * DRM framebuffer helper functions
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 *
 * Authors:
 *      Dave Airlie <airlied@linux.ie>
 *      Jesse Barnes <jesse.barnes@intel.com>
 */
#include "drmP.h"
#include "drm_crtc.h"
#include "drm_fb_helper.h"
#include "drm_crtc_helper.h"


struct list_head kernel_fb_helper_list;
/**
 * DOC: fbdev helpers
 *
 * The fb helper functions are useful to provide an fbdev on top of a drm kernel
 * mode setting driver. They can be used mostly independantely from the crtc
 * helper functions used by many drivers to implement the kernel mode setting
 * interfaces.
 *
 * Initialization is done as a three-step process with drm_fb_helper_init(),
 * drm_fb_helper_single_add_all_connectors() and drm_fb_helper_initial_config().
 * Drivers with fancier requirements than the default beheviour can override the
 * second step with their own code.  Teardown is done with drm_fb_helper_fini().
 *
 * At runtime drivers should restore the fbdev console by calling
 * drm_fb_helper_restore_fbdev_mode() from their ->lastclose callback. They
 * should also notify the fb helper code from updates to the output
 * configuration by calling drm_fb_helper_hotplug_event(). For easier
 * integration with the output polling code in drm_crtc_helper.c the modeset
 * code proves a ->output_poll_changed callback.
 *
 * All other functions exported by the fb helper library can be used to
 * implement the fbdev driver interface by the driver.
 */

/* simple single crtc case helper function
 * drm_fb_helper_single_add_all_connectors() - add all connectors to fbdev
 * 					       emulation helper
 * @fb_helper: fbdev initialized with drm_fb_helper_init
 *
 * This functions adds all the available connectors for use with the given
 * fb_helper. This is a separate step to allow drivers to freely assign
 * connectors to the fbdev, e.g. if some are reserved for special purposes or
 * not adequate to be used for the fbcon.
 *
 * Since this is part of the initial setup before the fbdev is published, no
 * locking is required.
 */
int drm_fb_helper_single_add_all_connectors(struct drm_fb_helper *fb_helper)
{
	struct drm_device *dev = fb_helper->dev;
	struct drm_connector *connector;
	int i;

	list_for_each_entry(connector, struct drm_connector, &dev->mode_config.connector_list, head) {
		struct drm_fb_helper_connector *fb_helper_connector;

		fb_helper_connector = kzalloc(sizeof(struct drm_fb_helper_connector), GFP_KERNEL);
		if (!fb_helper_connector)
			goto fail;

		fb_helper_connector->connector = connector;
		fb_helper->connector_info[fb_helper->connector_count++] = fb_helper_connector;
	}
	return 0;
fail:
	for (i = 0; i < fb_helper->connector_count; i++) {
		kfree(fb_helper->connector_info[i], sizeof(struct drm_fb_helper_connector));
		fb_helper->connector_info[i] = NULL;
	}
	fb_helper->connector_count = 0;
	return -ENOMEM;
}

static int drm_fb_helper_parse_command_line(struct drm_fb_helper *fb_helper)
{
	struct drm_device *dev = fb_helper->dev;
	struct drm_fb_helper_connector *fb_helper_conn;
	// struct gfxp_bm_fb_info fb_info;
	struct gfxp_bm_fb_info fb_info = { 1024, 768, 32, 24 };
	int i;

	// gfxp_bm_getfb_info(dev->vgatext->private, &fb_info);
	for (i = 0; i < fb_helper->connector_count; i++) {

		fb_helper_conn = fb_helper->connector_info[i];

		struct drm_cmdline_mode *cmdline_mode;
		cmdline_mode = &fb_helper_conn->cmdline_mode;
		cmdline_mode->specified = true;
		cmdline_mode->xres = fb_info.xres;
		cmdline_mode->yres = fb_info.yres;
		cmdline_mode->refresh_specified = true;
		cmdline_mode->refresh = 60;
		cmdline_mode->bpp_specified = true;
		cmdline_mode->bpp = fb_info.depth;
	}
	return 0;
}

static void drm_fb_helper_save_lut_atomic(struct drm_crtc *crtc, struct drm_fb_helper *helper)
{
	uint16_t *r_base, *g_base, *b_base;
	int i;

	if (helper->funcs->gamma_get == NULL)
		return;

	r_base = crtc->gamma_store;
	g_base = r_base + crtc->gamma_size;
	b_base = g_base + crtc->gamma_size;

	for (i = 0; i < crtc->gamma_size; i++)
		helper->funcs->gamma_get(crtc, &r_base[i], &g_base[i], &b_base[i], i);
}

static void drm_fb_helper_restore_lut_atomic(struct drm_crtc *crtc)
{
	uint16_t *r_base, *g_base, *b_base;

	if (crtc->funcs->gamma_set == NULL)
		return;

	r_base = crtc->gamma_store;
	g_base = r_base + crtc->gamma_size;
	b_base = g_base + crtc->gamma_size;

	crtc->funcs->gamma_set(crtc, r_base, g_base, b_base, 0, crtc->gamma_size);
}

/* Find the real fb for a given fb helper CRTC */
static struct drm_framebuffer *drm_mode_config_fb(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct drm_crtc *c;

	list_for_each_entry(c, struct drm_crtc, &dev->mode_config.crtc_list, head) {
		if (crtc->base.id == c->base.id)
			return c->fb;
	}

	return NULL;
}

bool drm_fb_helper_restore_fbdev_mode(struct drm_fb_helper *fb_helper)
{
	struct drm_device *dev;
	struct drm_plane *plane;
	bool error = false;
	int i;

	if (fb_helper == NULL)
		return error;

	dev = fb_helper->dev;

	list_for_each_entry(plane, struct drm_plane, &dev->mode_config.plane_list, head)
		drm_plane_force_disable(plane);

	for (i = 0; i < fb_helper->crtc_count; i++) {
		struct drm_mode_set *mode_set = &fb_helper->crtc_info[i].mode_set;
		struct drm_crtc *crtc = mode_set->crtc;
		int ret;

		if (crtc->funcs->cursor_set) {
			ret = crtc->funcs->cursor_set(crtc, NULL, 0, 0, 0);
			if (ret)
				error = true;
		}

		ret = drm_mode_set_config_internal(mode_set);
		if (ret)
			error = true;
	}
	return error;
}

bool drm_fb_helper_force_kernel_mode(void)
{
	bool ret, error = false;
	struct drm_fb_helper *helper;

	if (list_empty(&kernel_fb_helper_list))
		return false;

	list_for_each_entry(helper, struct drm_fb_helper, &kernel_fb_helper_list, kernel_fb_list) {
		if (helper->dev->switch_power_state == DRM_SWITCH_POWER_OFF)
			continue;

		ret = drm_fb_helper_restore_fbdev_mode(helper);
		if (ret)
			error = true;
	}
	return error;
}

static bool drm_fb_helper_is_bound(struct drm_fb_helper *fb_helper)
{
	struct drm_device *dev = fb_helper->dev;
	struct drm_crtc *crtc;
	int bound = 0, crtcs_bound = 0;

	list_for_each_entry(crtc, struct drm_crtc, &dev->mode_config.crtc_list, head) {
		if (crtc->fb)
			crtcs_bound++;
		if (crtc->fb == fb_helper->fb)
			bound++;
	}

	if (bound < crtcs_bound)
		return false;
	return true;
}

/* maximum connectors per crtcs in the mode set */
#define INTELFB_CONN_LIMIT 4

static void drm_fb_helper_crtc_free(struct drm_fb_helper *helper)
{
	int i;
	struct drm_device *dev = helper->dev;

	kfree(helper->connector_info, dev->mode_config.num_connector * sizeof(struct drm_fb_helper_connector *));
	for (i = 0; i < helper->crtc_count; i++) {
		kfree(helper->crtc_info[i].mode_set.connectors, INTELFB_CONN_LIMIT * sizeof(struct drm_connector *));
		if (helper->crtc_info[i].mode_set.mode)
			drm_mode_destroy(helper->dev, helper->crtc_info[i].mode_set.mode);
	}
	kfree(helper->crtc_info, helper->crtc_count * sizeof(struct drm_fb_helper_crtc));
}

int drm_fb_helper_init(struct drm_device *dev,
		       struct drm_fb_helper *fb_helper,
		       int crtc_count, int max_conn_count)
{
	struct drm_crtc *crtc;
	int i;

	fb_helper->dev = dev;

	INIT_LIST_HEAD(&kernel_fb_helper_list);
	INIT_LIST_HEAD(&fb_helper->kernel_fb_list);

	fb_helper->crtc_info = kcalloc(crtc_count, sizeof(struct drm_fb_helper_crtc), GFP_KERNEL);
	if (!fb_helper->crtc_info)
		return -ENOMEM;

	fb_helper->crtc_count = crtc_count;
	fb_helper->connector_info = kcalloc(dev->mode_config.num_connector, sizeof(struct drm_fb_helper_connector *), GFP_KERNEL);
	if (!fb_helper->connector_info) {
		kfree(fb_helper->crtc_info, sizeof(struct drm_fb_helper_crtc));
		return -ENOMEM;
	}
	fb_helper->connector_count = 0;

	for (i = 0; i < crtc_count; i++) {
		fb_helper->crtc_info[i].mode_set.connectors =
			kcalloc(max_conn_count,
				sizeof(struct drm_connector *),
				GFP_KERNEL);

		if (!fb_helper->crtc_info[i].mode_set.connectors)
			goto out_free;
		fb_helper->crtc_info[i].mode_set.num_connectors = 0;
	}

	i = 0;
	list_for_each_entry(crtc, struct drm_crtc, &dev->mode_config.crtc_list, head) {
		fb_helper->crtc_info[i].mode_set.crtc = crtc;
		i++;
	}

	return 0;
out_free:
	drm_fb_helper_crtc_free(fb_helper);
	return -ENOMEM;
}

void drm_fb_helper_fini(struct drm_fb_helper *fb_helper)
{
	if (!list_empty(&fb_helper->kernel_fb_list)) {
		list_del(&fb_helper->kernel_fb_list);
		if (list_empty(&kernel_fb_helper_list)) {
			DRM_INFO("drm: unregistered panic notifier");
		}
	}

	drm_fb_helper_crtc_free(fb_helper);

}

int drm_fb_helper_single_fb_probe(struct drm_fb_helper *fb_helper,
				  int preferred_bpp)
{
	int ret = 0;
	int crtc_count = 0;
	int i;
	struct drm_fb_helper_surface_size sizes;
	int gamma_size = 0;

	(void) memset(&sizes, 0, sizeof(struct drm_fb_helper_surface_size));
	sizes.surface_depth = 24;
	sizes.surface_bpp = 32;
	sizes.fb_width = (unsigned)-1;
	sizes.fb_height = (unsigned)-1;

	/* if driver picks 8 or 16 by default use that
	   for both depth/bpp */
	if (preferred_bpp != sizes.surface_bpp)
		sizes.surface_depth = sizes.surface_bpp = preferred_bpp;

	/* first up get a count of crtcs now in use and new min/maxes width/heights */
	for (i = 0; i < fb_helper->connector_count; i++) {
		struct drm_fb_helper_connector *fb_helper_conn = fb_helper->connector_info[i];
		struct drm_cmdline_mode *cmdline_mode;

		cmdline_mode = &fb_helper_conn->cmdline_mode;

		if (cmdline_mode->bpp_specified) {
			switch (cmdline_mode->bpp) {
			case 8:
				sizes.surface_depth = sizes.surface_bpp = 8;
				break;
			case 15:
				sizes.surface_depth = 15;
				sizes.surface_bpp = 16;
				break;
			case 16:
				sizes.surface_depth = sizes.surface_bpp = 16;
				break;
			case 24:
				sizes.surface_depth = sizes.surface_bpp = 24;
				break;
			case 32:
				sizes.surface_depth = 24;
				sizes.surface_bpp = 32;
				break;
			}
			break;
		}
	}

	crtc_count = 0;
	for (i = 0; i < fb_helper->crtc_count; i++) {
		struct drm_display_mode *desired_mode;
		desired_mode = fb_helper->crtc_info[i].desired_mode;

		if (desired_mode) {
			if (gamma_size == 0)
				gamma_size = fb_helper->crtc_info[i].mode_set.crtc->gamma_size;
			if (desired_mode->hdisplay < sizes.fb_width)
				sizes.fb_width = desired_mode->hdisplay;
			if (desired_mode->vdisplay < sizes.fb_height)
				sizes.fb_height = desired_mode->vdisplay;
			if (desired_mode->hdisplay > sizes.surface_width)
				sizes.surface_width = desired_mode->hdisplay;
			if (desired_mode->vdisplay > sizes.surface_height)
				sizes.surface_height = desired_mode->vdisplay;
			crtc_count++;
		}
	}

	if (crtc_count == 0 || sizes.fb_width == (unsigned)-1 || sizes.fb_height == (unsigned)-1) {
		/* hmm everyone went away - assume VGA cable just fell out
		   and will come back later. */
		DRM_INFO("Cannot find any crtc or sizes - going 1024x768\n");
		sizes.fb_width = sizes.surface_width = 1024;
		sizes.fb_height = sizes.surface_height = 768;
	}

	/* push down into drivers */
	ret = (*fb_helper->funcs->fb_probe)(fb_helper, &sizes);
	if (ret < 0)
		return ret;

	/*
	 * Set the fb pointer - usually drm_setup_crtcs does this for hotplug
	 * events, but at init time drm_setup_crtcs needs to be called before
	 * the fb is allocated (since we need to figure out the desired size of
	 * the fb before we can allocate it ...). Hence we need to fix things up
	 * here again.
	 */
	for (i = 0; i < fb_helper->crtc_count; i++)
		if (fb_helper->crtc_info[i].mode_set.num_connectors)
			fb_helper->crtc_info[i].mode_set.fb = fb_helper->fb;


	/* Switch back to kernel console on panic */
	/* multi card linked list maybe */
	if (list_empty(&kernel_fb_helper_list)) {
		DRM_INFO("registered panic notifier");
	}

	list_add(&fb_helper->kernel_fb_list, &kernel_fb_helper_list, (caddr_t)fb_helper);

	return 0;
}

static int drm_fb_helper_probe_connector_modes(struct drm_fb_helper *fb_helper,
					       uint32_t maxX,
					       uint32_t maxY)
{
	struct drm_connector *connector;
	int count = 0;
	int i;

	for (i = 0; i < fb_helper->connector_count; i++) {
		connector = fb_helper->connector_info[i]->connector;
		count += connector->funcs->fill_modes(connector, maxX, maxY);
	}

	return count;
}

static struct drm_display_mode *drm_has_preferred_mode(struct drm_fb_helper_connector *fb_connector, int width, int height)
{
	struct drm_display_mode *mode;

	list_for_each_entry(mode, struct drm_display_mode, &fb_connector->connector->modes, head) {
		if (drm_mode_width(mode) > width ||
		    drm_mode_height(mode) > height)
			continue;
		if (mode->type & DRM_MODE_TYPE_PREFERRED)
			return mode;
	}
	return NULL;
}

static bool drm_has_cmdline_mode(struct drm_fb_helper_connector *fb_connector)
{
	struct drm_cmdline_mode *cmdline_mode;
	cmdline_mode = &fb_connector->cmdline_mode;
	return cmdline_mode->specified;
}

static struct drm_display_mode *drm_pick_cmdline_mode(struct drm_fb_helper_connector *fb_helper_conn,
					/* LINTED E_FUNC_ARG_UNUSED */
						      int width, int height)
{
	struct drm_cmdline_mode *cmdline_mode;
	struct drm_display_mode *mode = NULL;

	cmdline_mode = &fb_helper_conn->cmdline_mode;
	if (cmdline_mode->specified == false)
		return mode;

	/* attempt to find a matching mode in the list of modes
	 *  we have gotten so far, if not add a CVT mode that conforms
	 */
	if (cmdline_mode->rb || cmdline_mode->margins)
		goto create_mode;

	list_for_each_entry(mode, struct drm_display_mode, &fb_helper_conn->connector->modes, head) {
		/* check width/height */
		if (mode->hdisplay != cmdline_mode->xres ||
		    mode->vdisplay != cmdline_mode->yres)
			continue;

		if (cmdline_mode->refresh_specified) {
			if (mode->vrefresh != cmdline_mode->refresh)
				continue;
		}

		if (cmdline_mode->interlace) {
			if (!(mode->flags & DRM_MODE_FLAG_INTERLACE))
				continue;
		}
		return mode;
	}

create_mode:
	mode = drm_mode_create_from_cmdline_mode(fb_helper_conn->connector->dev,
						 cmdline_mode);
	if (mode)
		list_add(&mode->head, &fb_helper_conn->connector->modes,
		    (caddr_t)mode);
	return mode;
}

static bool drm_connector_enabled(struct drm_connector *connector, bool strict)
{
	bool enable;

	if (strict)
		enable = connector->status == connector_status_connected;
	else
		enable = connector->status != connector_status_disconnected;

	return enable;
}

static void drm_enable_connectors(struct drm_fb_helper *fb_helper,
				  bool *enabled)
{
	bool any_enabled = false;
	struct drm_connector *connector;
	int i = 0;

	for (i = 0; i < fb_helper->connector_count; i++) {
		connector = fb_helper->connector_info[i]->connector;
		enabled[i] = drm_connector_enabled(connector, true);
		DRM_DEBUG_KMS("connector %d enabled? %s\n", connector->base.id,
			  enabled[i] ? "yes" : "no");
		any_enabled |= enabled[i];
	}

	if (any_enabled)
		return;

	for (i = 0; i < fb_helper->connector_count; i++) {
		connector = fb_helper->connector_info[i]->connector;
		enabled[i] = drm_connector_enabled(connector, false);
	}
}

static bool drm_target_cloned(struct drm_fb_helper *fb_helper,
			      struct drm_display_mode **modes,
			      bool *enabled, int width, int height)
{
	int count, i, j;
	bool can_clone = false;
	struct drm_fb_helper_connector *fb_helper_conn;
	struct drm_display_mode *dmt_mode, *mode;

	/* only contemplate cloning in the single crtc case */
	if (fb_helper->crtc_count > 1)
		return false;

	count = 0;
	for (i = 0; i < fb_helper->connector_count; i++) {
		if (enabled[i])
			count++;
	}

	/* only contemplate cloning if more than one connector is enabled */
	if (count <= 1)
		return false;

	/* check the command line or if nothing common pick 1024x768 */
	can_clone = true;
	for (i = 0; i < fb_helper->connector_count; i++) {
		if (!enabled[i])
			continue;
		fb_helper_conn = fb_helper->connector_info[i];
		modes[i] = drm_pick_cmdline_mode(fb_helper_conn, width, height);
		if (!modes[i]) {
			can_clone = false;
			break;
		}
		for (j = 0; j < i; j++) {
			if (!enabled[j])
				continue;
			if (!drm_mode_equal(modes[j], modes[i]))
				can_clone = false;
		}
	}

	if (can_clone) {
		DRM_DEBUG_KMS("can clone using command line\n");
		return true;
	}

	/* try and find a 1024x768 mode on each connector */
	can_clone = true;
	dmt_mode = drm_mode_find_dmt(fb_helper->dev, 1024, 768, 60, false);

	for (i = 0; i < fb_helper->connector_count; i++) {

		if (!enabled[i])
			continue;

		fb_helper_conn = fb_helper->connector_info[i];
		list_for_each_entry(mode, struct drm_display_mode, &fb_helper_conn->connector->modes, head) {
			if (drm_mode_equal(mode, dmt_mode))
				modes[i] = mode;
		}
		if (!modes[i])
			can_clone = false;
	}

	if (can_clone) {
		DRM_DEBUG_KMS("can clone using 1024x768\n");
		return true;
	}
	DRM_INFO("kms: can't enable cloning when we probably wanted to.\n");
	return false;
}

static bool drm_target_preferred(struct drm_fb_helper *fb_helper,
				 struct drm_display_mode **modes,
				 bool *enabled, int width, int height)
{
	struct drm_fb_helper_connector *fb_helper_conn;
	int i;

	for (i = 0; i < fb_helper->connector_count; i++) {
		fb_helper_conn = fb_helper->connector_info[i];

		if (enabled[i] == false)
			continue;

		DRM_DEBUG_KMS("looking for cmdline mode on connector %d\n",
			      fb_helper_conn->connector->base.id);

		/* got for command line mode first */
		modes[i] = drm_pick_cmdline_mode(fb_helper_conn, width, height);
		if (!modes[i]) {
			DRM_DEBUG_KMS("looking for preferred mode on connector %d\n",
				      fb_helper_conn->connector->base.id);
			modes[i] = drm_has_preferred_mode(fb_helper_conn, width, height);
		}
		/* No preferred modes, pick one off the list */
		if (!modes[i] && !list_empty(&fb_helper_conn->connector->modes)) {
			list_for_each_entry(modes[i], struct drm_display_mode, &fb_helper_conn->connector->modes, head)
				/* LINTED */
				{ if (1) break; }
		}
		DRM_DEBUG_KMS("found mode %s\n", modes[i] ? modes[i]->name :
			  "none");
	}
	return true;
}

static int drm_pick_crtcs(struct drm_fb_helper *fb_helper,
			  struct drm_fb_helper_crtc **best_crtcs,
			  struct drm_display_mode **modes,
			  int n, int width, int height)
{
	int c, o;
	struct drm_device *dev = fb_helper->dev;
	struct drm_connector *connector;
	struct drm_connector_helper_funcs *connector_funcs;
	struct drm_encoder *encoder;
	int my_score, best_score, score;
	struct drm_fb_helper_crtc **crtcs, *crtc;
	struct drm_fb_helper_connector *fb_helper_conn;
	int  num_connector = dev->mode_config.num_connector;

	if (n == fb_helper->connector_count)
		return 0;

	ASSERT(n <= num_connector);

	fb_helper_conn = fb_helper->connector_info[n];
	connector = fb_helper_conn->connector;

	best_crtcs[n] = NULL;
	best_score = drm_pick_crtcs(fb_helper, best_crtcs, modes, n+1, width, height);
	if (modes[n] == NULL)
		return best_score;

	crtcs = kzalloc(num_connector * sizeof(struct drm_fb_helper_crtc *),
	    GFP_KERNEL);
	if (!crtcs)
		return best_score;

	my_score = 1;
	if (connector->status == connector_status_connected)
		my_score++;
	if (drm_has_cmdline_mode(fb_helper_conn))
		my_score++;
	if (drm_has_preferred_mode(fb_helper_conn, width, height))
		my_score++;

	connector_funcs = connector->helper_private;
	encoder = connector_funcs->best_encoder(connector);
	if (!encoder)
		goto out;

	/* select a crtc for this connector and then attempt to configure
	   remaining connectors */
	for (c = 0; c < fb_helper->crtc_count; c++) {
		crtc = &fb_helper->crtc_info[c];

		if ((encoder->possible_crtcs & (1 << c)) == 0)
			continue;

		for (o = 0; o < n; o++)
			if (best_crtcs[o] == crtc)
				break;

		if (o < n) {
			/* ignore cloning unless only a single crtc */
			if (fb_helper->crtc_count > 1)
				continue;

			if (!drm_mode_equal(modes[o], modes[n]))
				continue;
		}

		crtcs[n] = crtc;
		(void) memcpy(crtcs, best_crtcs, n * sizeof(struct drm_fb_helper_crtc *));
		score = my_score + drm_pick_crtcs(fb_helper, crtcs, modes, n + 1,
						  width, height);
		if (score > best_score) {
			best_score = score;
			(void) memcpy(best_crtcs, crtcs,
			    num_connector *
			    sizeof(struct drm_fb_helper_crtc *));
		}
	}
out:
	kfree(crtcs, (num_connector * sizeof(struct drm_fb_helper_crtc *)));
	return best_score;
}

static void drm_setup_crtcs(struct drm_fb_helper *fb_helper)
{
	struct drm_device *dev = fb_helper->dev;
	struct drm_fb_helper_crtc **crtcs;
	struct drm_display_mode **modes;
	struct drm_mode_set *modeset;
	bool *enabled;
	int width, height;
	int i, num_connector = dev->mode_config.num_connector;

	DRM_DEBUG_KMS("\n");

	width = dev->mode_config.max_width;
	height = dev->mode_config.max_height;

	if ((crtcs = kcalloc(num_connector,
	    sizeof(struct drm_fb_helper_crtc *), GFP_KERNEL)) == NULL) {
		DRM_ERROR("Memory allocation failed for crtcs\n");
		return;
	}
	if ((modes = kcalloc(num_connector,
	    sizeof(struct drm_display_mode *), GFP_KERNEL)) == NULL) {
		DRM_ERROR("Memory allocation failed for modes\n");
		goto errout1;
	}
	if ((enabled = kcalloc(num_connector,
	    sizeof(bool), GFP_KERNEL)) == NULL) {
		DRM_ERROR("Memory allocation failed for enabled\n");
		goto errout2;
	}


	drm_enable_connectors(fb_helper, enabled);

	if (!(fb_helper->funcs->initial_config &&
	      fb_helper->funcs->initial_config(fb_helper, crtcs, modes,
					       enabled, width, height))) {
		(void) memset(modes, 0, dev->mode_config.num_connector*sizeof(modes[0]));
		(void) memset(crtcs, 0, dev->mode_config.num_connector*sizeof(crtcs[0]));

		if (!drm_target_cloned(fb_helper,
				       modes, enabled, width, height) &&
		    !drm_target_preferred(fb_helper,
					  modes, enabled, width, height))
			DRM_ERROR("Unable to find initial modes\n");

		DRM_DEBUG_KMS("picking CRTCs for %dx%d config\n",
			      width, height);

		(void) drm_pick_crtcs(fb_helper, crtcs, modes, 0, width, height);
	}

	/* need to set the modesets up here for use later */
	/* fill out the connector<->crtc mappings into the modesets */
	for (i = 0; i < fb_helper->crtc_count; i++) {
		modeset = &fb_helper->crtc_info[i].mode_set;
		modeset->num_connectors = 0;
		modeset->fb = NULL;
	}

	for (i = 0; i < fb_helper->connector_count; i++) {
		struct drm_display_mode *mode = modes[i];
		struct drm_fb_helper_crtc *fb_crtc = crtcs[i];
		modeset = &fb_crtc->mode_set;

		if (mode && fb_crtc) {
			DRM_DEBUG_KMS("desired mode %s set on crtc %d\n",
				      mode->name, fb_crtc->mode_set.crtc->base.id);
			fb_crtc->desired_mode = mode;
			if (modeset->mode)
				drm_mode_destroy(dev, modeset->mode);
			modeset->mode = drm_mode_duplicate(dev,
							   fb_crtc->desired_mode);
			modeset->connectors[modeset->num_connectors++] = fb_helper->connector_info[i]->connector;
			modeset->fb = fb_helper->fb;
		}
	}

	/* Clear out any old modes if there are no more connected outputs. */
	for (i = 0; i < fb_helper->crtc_count; i++) {
		modeset = &fb_helper->crtc_info[i].mode_set;
		if (modeset->num_connectors == 0) {
			BUG_ON(modeset->fb);
			BUG_ON(modeset->num_connectors);
			if (modeset->mode)
				drm_mode_destroy(dev, modeset->mode);
			modeset->mode = NULL;
		}
	}

	kfree(enabled, num_connector * sizeof(bool));
errout2:
	kfree(modes, num_connector * sizeof(struct drm_display_mode *));
errout1:
	kfree(crtcs, num_connector * sizeof(struct drm_fb_helper_crtc *));
}

/**
 * drm_helper_initial_config - setup a sane initial connector configuration
 * @dev: DRM device
 *
 *
 * Scan the CRTCs and connectors and try to put together an initial setup.
 * At the moment, this is a cloned configuration across all heads with
 * a new framebuffer object as the backing store.
 *
 * Note that this also registers the fbdev and so allows userspace to call into
 * the driver through the fbdev interfaces.
 *
 * This function will call down into the ->fb_probe callback to let
 * the driver allocate and initialize the fbdev info structure and the drm
 * framebuffer used to back the fbdev. drm_fb_helper_fill_var() and
 * drm_fb_helper_fill_fix() are provided as helpers to setup simple default
 * values for the fbdev info structure.
 *
 * RETURNS:
 * Zero if everything went ok, nonzero otherwise.
 */
bool drm_fb_helper_initial_config(struct drm_fb_helper *fb_helper, int bpp_sel)
{
	struct drm_device *dev = fb_helper->dev;
	int count = 0;

	(void) drm_fb_helper_parse_command_line(fb_helper);

	count = drm_fb_helper_probe_connector_modes(fb_helper,
						    dev->mode_config.max_width,
						    dev->mode_config.max_height);
	/*
	 * we shouldn't end up with no modes here.
	 */
	if (count == 0) {
		DRM_INFO("No connectors reported connected with modes");
	}
	drm_setup_crtcs(fb_helper);

	return drm_fb_helper_single_fb_probe(fb_helper, bpp_sel);
}


/**
 * drm_fb_helper_hotplug_event - respond to a hotplug notification by
 *                               probing all the outputs attached to the fb.
 * @fb_helper: the drm_fb_helper
 *
 * Scan the connectors attached to the fb_helper and try to put together a
 * setup after *notification of a change in output configuration.
 *
 * Called at runtime, takes the mode config locks to be able to check/change the
 * modeset configuration. Must be run from process context (which usually means
 * either the output polling work or a work item launched from the driver's
 * hotplug interrupt).
 *
 * Scan the connectors attached to the fb_helper and try to put together a
 * setup after *notification of a change in output configuration.
 *
 * RETURNS:
 * 0 on success and a non-zero error code otherwise.
 */
int drm_fb_helper_hotplug_event(struct drm_fb_helper *fb_helper)
{
	struct drm_device *dev = fb_helper->dev;
	u32 max_width, max_height, bpp_sel;

	if (!fb_helper->fb)
		return 0;

	mutex_lock(&fb_helper->dev->mode_config.mutex);
	if (!drm_fb_helper_is_bound(fb_helper)) {
		fb_helper->delayed_hotplug = true;
		mutex_unlock(&fb_helper->dev->mode_config.mutex);
		return 0;
	}
	DRM_DEBUG_KMS("\n");

	max_width = fb_helper->fb->width;
	max_height = fb_helper->fb->height;
	bpp_sel = fb_helper->fb->bits_per_pixel;

	(void) drm_fb_helper_probe_connector_modes(fb_helper, max_width,
						    max_height);
	mutex_unlock(&fb_helper->dev->mode_config.mutex);

	drm_modeset_lock_all(dev);
	drm_setup_crtcs(fb_helper);
	drm_modeset_unlock_all(dev);

	return drm_fb_helper_single_fb_probe(fb_helper, bpp_sel);
}

int drm_gfxp_setmode(int mode)
{
		bool ret = 0;
        if (mode == 0) {
                ret = drm_fb_helper_force_kernel_mode();
		if (ret == true)
			DRM_ERROR("Failed to restore crtc configuration\n");
	}
        if (mode == 1)
                DRM_DEBUG_KMS("do nothing in entervt");
        return ret;
}

//struct gfxp_blt_ops drm_gfxp_ops = {
//        NULL,   /* blt */
//        NULL,   /* copy */
//        NULL,   /* clear */
//        drm_gfxp_setmode, /* setmode */
//};

void drm_register_fbops(struct drm_device *dev)
{
	; // gfxp_bm_register_fbops(dev->vgatext->private, &drm_gfxp_ops);
}

int drm_getfb_size(struct drm_device *dev)
{
	struct gfxp_bm_fb_info fb_info = { 1024, 768, 32, 24 };
	int size, pitch;
        // gfxp_bm_getfb_info(dev->vgatext->private, &fb_info);
        pitch = ALIGN(fb_info.xres * ((fb_info.depth + 7) / 8), 64);
        size = ALIGN(pitch *fb_info.yres, PAGE_SIZE);
	return size;
}
