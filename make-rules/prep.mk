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
# Copyright (c) 2010, 2015, Oracle and/or its affiliates. All rights reserved.
#

#
# We set PREFERRED_BITS to 32 here for legacy components that DO NOT include
# common.mk.  Such components do not set BUILD_BITS in their Makefile but they
# silently expects that 32-bit build is preferred (similarly as if BUILD_BITS
# is set to 32 or 32_and_64).  Since this is not the case by default we need to
# enforce preference of 32-bit build for them.  COMMON_INCLUDED is set in
# common.mk.
#
# Once all components are converted to include common.mk this conditional
# setting could be safely removed.
#
ifneq ($(strip $(COMMON_INCLUDED)),yes)
PREFERRED_BITS = 32
endif

include $(WS_MAKE_RULES)/prep-download.mk

include $(WS_MAKE_RULES)/prep-hg.mk
include $(WS_MAKE_RULES)/prep-git.mk
include $(WS_MAKE_RULES)/prep-svn.mk
include $(WS_MAKE_RULES)/prep-unpack.mk
include $(WS_MAKE_RULES)/prep-patch.mk

download::

unpack::	download

patch::		unpack

$(SOURCE_DIR)/.prep:	component-environment-prep download unpack patch
	$(COMPONENT_PREP_ACTION)
	$(TOUCH) $@

prep::	$(SOURCE_DIR)/.prep

clean::
	$(PRE_CLEAN_ACTION)
	$(RM) -r $(CLEAN_PATHS)

clobber::	clean
	$(RM) -r $(CLOBBER_PATHS)
