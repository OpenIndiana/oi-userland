#
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
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
###############################################################################
#
#  This Makefile drives the production of the DRM (Direct Rendering
#  Manager) common misc module.
#
###############################################################################

#TOP:sh	= hg root

#
# X-consolidation defines:
#
# Module core info
#
MODULE			= i915

# MODULE_NAME - the package this module is installed in
MODULE_NAME		= $(MODULE)

# This is the package this module should be installed into
MODULE_PKGTAIL		= kms
MODULE_PKGTAIL_SET	= yes

# Where are the local sources relative to the build dir
REL_SOURCE_DIR		= ../src

# Where do we install the driver.
MODULE_PREFIX		= kernel/drv/$(MACH64_i386)
MODULE_PREFIX_SET	= yes

# No upstream sources for these files, since they're Solaris-specific
SOURCE_TARBALL_NAME	= NONE
SOURCE_TARBALL_NAME_SET	= yes
SOURCE_TARGETS		=
SOURCE_TARGETS_SET	= yes

# No configure script, so pass usual environment to build/install instead
CONFIGURE_TARGETS	= $(BUILD_DIR)
CONFIGURE_TARGETS_SET	= yes

MODULE_MAKEFLAGS	= VPATH=$(REL_SOURCE_DIR) -f $(REL_SOURCE_DIR)/Makefile
MODULE_BUILD_ENV	= $(CONFIG_ENV) PREFIX=$(MODULE_PREFIX)
MODULE_LDFLAGS		= -dy -r -Nmisc/kms

#
# License info
#
MODULE_LICENSE		= Intel license
MODULE_LICENSE_SET	= yes
MODULE_DESC		= the Intel i915 KMS driver
MODULE_VERSION		= 2013Q3
ORACLE_TPNO		= 5800
LICENSE_FILE		= license_i915
LICENSE_FILE_SET	= yes

#
#	Include kernel rules.
#
include $(TOP)/Makefile.inc
include $(TOP)/Makefile.rules

SUBDIRS 		= src

clean all install lint:
	for dir in $(SUBDIRS); do \
	        $(MAKE) -C $$dir $(PASSDOWN_VARS) $(@); \
	done
