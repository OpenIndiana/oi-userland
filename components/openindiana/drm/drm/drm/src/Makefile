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
#  This Makefile actually builds the drm misc module.
#
###############################################################################

#TOP:sh	= hg root
#
#       Include kernel rules.
#
include $(TOP)/Makefile.inc

include $(TOP)/Makefile.rules

C_SRCS = ati_pcigart.c \
	drm_agpsupport.c \
	drm_auth.c \
	drm_bufs.c \
	drm_cache.c \
	drm_context.c \
	drm_crtc.c \
	drm_crtc_helper.c \
	drm_dma.c \
	drm_dp_helper.c \
	drm_dp_i2c_helper.c \
	drm_drv.c \
	drm_edid.c \
	drm_fb_helper.c \
	drm_fops.c \
	drm_gem.c \
	drm_io32.c \
	drm_ioctl.c \
	drm_irq.c \
	drm_kstat.c \
	drm_linux.c \
	drm_lock.c \
	drm_memory.c \
	drm_mm.c \
	drm_modes.c \
	drm_msg.c \
	drm_pci.c \
	drm_rect.c \
	drm_scatter.c \
	drm_stub.c \
	drm_sun_i2c.c \
	drm_sun_idr.c \
	drm_sun_pci.c \
	drm_sun_timer.c \
	drm_sun_workqueue.c \
	drm_sunmod.c \
	drm_sysfs.c

# Include kernel common rules

MODULE		= drm
OBJECTS		= $(C_SRCS:%.c=%.o)
LINTS		= $(OBJECTS:%.o=%.ln)

#
#	Define targets
# Leftovers from the ON move.  They still have some value here.
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
# And the %p issue in 4994570 that is currently resolved in this source
# LINTTAGS += -erroff=E_BAD_FORMAT_ARG_TYPE2

#
#	Default build targets.
#
.KEEP_STATE_FILE: .make.state.$(MACH)
# .SUFFIXES:
# .DEFAULT:	$(MODULE)

all:		$(MODULE)

%.o:	%.c
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
		@print Installing $(MODULE) in $(DESTDIR)/$(PREFIX)
		@mkdir -p $(DESTDIR)/$(PREFIX)
		@$(INSTALL) -m 555 $(MODULE) $(DESTDIR)/$(PREFIX)
