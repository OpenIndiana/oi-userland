#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS= NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         desktop-cache
COMPONENT_VERSION=      0.2.9
COMPONENT_SRC=          # all files under files/
COMPONENT_BUGDB=	gnome/install

# nothing to download or build; just package
BUILD_STYLE= pkg

# Uses a feature in a gtk script not added until S12.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/common.mk

# Make sure SMF manifests are valid
ifneq ($(BUILD_TYPE), evaluation)
$(BUILD_DIR)/.validated-smf-manifests-$(MACH): $(BUILD_DIR)
	@for f in files/*.xml ; do \
	    [[ "$$f" == "files/com.oracle.solaris.gdm-temporary.xml" ]] || \
	    (set -ex ; /usr/sbin/svccfg validate "$$f") ; \
	done
	$(TOUCH) $@
endif

validate-smf:	$(BUILD_DIR)/.validated-smf-manifests-$(MACH)
build:		$(BUILD_DIR)/.validated-smf-manifests-$(MACH)

REQUIRED_PACKAGES += service/opengl/ogl-select
REQUIRED_PACKAGES += system/core-os
