#
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice (including the next
# paragraph) shall be included in all copies or substantial portions of the
# Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
#
#
###############################################################################
#
#  This Makefile actually builds the i915 framebuffer driver
#
###############################################################################

#TOP:sh	= hg root

C_SRCS = dvo_ch7017.c \
	dvo_ch7xxx.c \
	dvo_ivch.c \
	dvo_ns2501.c \
	dvo_sil164.c \
	dvo_tfp410.c \
	i915_dma.c \
	i915_drv.c \
	i915_gem.c \
	i915_gem_context.c \
	i915_gem_debug.c \
	i915_gem_evict.c \
	i915_gem_execbuffer.c \
	i915_gem_gtt.c \
	i915_gem_stolen.c \
	i915_gem_tiling.c \
	i915_io32.c \
	i915_irq.c \
	i915_suspend.c \
	i915_ums.c \
	intel_bios.c \
	intel_crt.c \
	intel_ddi.c \
	intel_display.c \
	intel_dp.c \
	intel_dvo.c \
	intel_fb.c \
	intel_hdmi.c \
	intel_i2c.c \
	intel_lvds.c \
	intel_modes.c \
	intel_overlay.c \
	intel_panel.c \
	intel_pm.c \
	intel_ringbuffer.c \
	intel_sdvo.c \
	intel_sideband.c \
	intel_sprite.c \
	intel_tv.c

MANPAGES	= i915.4d
MANSECTION	= man4d
MANSOURCE	= ../manpages

# Include kernel common rules
include $(TOP)/Makefile.rules

MODULE		= i915
OBJECTS		= $(C_SRCS:%.c=%.o)
LINTS		= $(OBJECTS:%.o=%.ln)

#
#	Define targets
#
ALL_TARGET	= $(BINARY)
LINT_TARGET	= $(MODULE).lint
INSTALL_TARGET	= $(BINARY) $(ROOTMODULE)

#
# Lint errors that are not clean
#
LINTTAGS += -erroff=E_STATIC_UNUSED

#
# Lint clean in current code, but might not be in updated code
#
# LINTTAGS += -erroff=E_FUNC_ARG_UNUSED
# LINTTAGS += -erroff=E_CONST_EXPR
# LINTTAGS += -erroff=E_TRUE_LOGICAL_EXPR
# LINTTAGS += -erroff=E_FALSE_LOGICAL_EXPR
#
# And the %p issue in 15196627 that is currently resolved in this source
# LINTTAGS += -erroff=E_BAD_FORMAT_ARG_TYPE2

#
#	Default build targets.
#
.KEEP_STATE_FILE: .make.state.$(MACH)
# .SUFFIXES:
# .DEFAULT:	$(MODULE)

all:		$(MODULE)

$(OBJECTS):
		$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
		$(CTFCONVERT) $(CTFCVTFLAGS) $@

$(MODULE):	$(OBJECTS)
		$(LD) -o $@ $(LDFLAGS) $(OBJECTS)
		$(CTFMERGE) $(CTFMERGE_LABEL) -o $@ $(OBJECTS)

def:		$(DEF_DEPS)

clean:		$(CLEAN_DEPS)
		$(RM) $(OBJECTS)

clobber:	clean
		$(RM) *.bc
		$(RM) $(MODULE)

lint:		$(LINT_DEPS)

modlintlib:	$(MODLINTLIB_DEPS)

clean.lint:	$(CLEAN_LINT_DEPS)

install:	$(INSTALL_DEPS)
		@print Installing $(MODULE) in $(PROTODIR)/$(PREFIX)
		@mkdir -p $(PROTODIR)/$(PREFIX)
		@$(INSTALL) -m 555 $(MODULE) $(PROTODIR)/$(PREFIX)
		@print Installing $(MANSOURCE)/$(MANPAGES) in $(PROTODIR)$(MANTARGET)
		@mkdir -p $(PROTODIR)$(ROOT_MAN_DIR)/$(MANSECTION)
		@$(INSTALL) -m 644 $(MANSOURCE)/$(MANPAGES) $(PROTODIR)$(MANTARGET)
