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
# Copyright (c) 2010, 2016, Oracle and/or its affiliates. All rights reserved.
#

include $(WS_MAKE_RULES)/prep-download.mk
include $(WS_MAKE_RULES)/prep-hg.mk
include $(WS_MAKE_RULES)/prep-git.mk
include $(WS_MAKE_RULES)/prep-svn.mk
include $(WS_MAKE_RULES)/prep-unpack.mk
include $(WS_MAKE_RULES)/prep-patch.mk

# Now that the above makefiles have had a chance to assign values to
# COMPONENT_SRC and COMPONENT_ARCHIVE if they choose, we can assign some
# reasonable defaults.
COMPONENT_SRC ?=	$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE ?=	$(COMPONENT_SRC).tar.gz

$(eval $(call eval-download-rules))
$(eval $(call eval-hg-rules))
$(eval $(call eval-git-rules))
$(eval $(call eval-svn-rules))
$(eval $(call eval-unpack-rules))
$(eval $(call eval-patch-rules))

download::

unpack::	download

patch::		unpack

$(SOURCE_DIR)/.prep:	download unpack patch
	$(COMPONENT_PREP_ACTION)
	$(TOUCH) $@

prep::	$(SOURCE_DIR)/.prep

clean::
	$(PRE_CLEAN_ACTION)
	$(RM) -r $(CLEAN_PATHS)

clobber::	clean
	$(RM) -r $(CLOBBER_PATHS)

