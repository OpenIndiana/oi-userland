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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
# Copyright 2026 Klaus Ziegler
#

# If you submit new obsolete packages using this history file, please only
# add new ones at the end of this file, because the sed statement below
# will only build added ones.
# If you need to delete packages from the history file, feel free to do so,
# but don't expect that removed packages will disappear right away from the
# OpenIndiana distribution. Old obsolete packages which are removed from
# the histroy file will only disappear during a general overhaul of the
# IPS repository.

BUILD_STYLE = pkg

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		history

_GENERATE_HISTORY := $(shell \
	$(GIT) log -1 -p -- $(COMPONENT_DIR)/history | $(GSED) \
		-e "/^---/d" -e "/^+++/d" -e "/^\ /d" -e "/^commit/d" \
		-e "/^Author:/d" -e "/^Date:/d" -e "/^\$$/d" -e "/^diff /d" \
		-e "/^index /d" -e "/^@@/d" -e "s@^+@@g" > $(COMPONENT_DIR)/history.work && \
	mv $(COMPONENT_DIR)/history.work $(COMPONENT_DIR)/history \
)

include $(WS_MAKE_RULES)/common.mk

publish:
	$(GIT) restore $(COMPONENT_DIR)/history

clobber::
	$(GIT) restore $(COMPONENT_DIR)/history
	@rm -f $(COMPONENT_DIR)/history.work

# Auto-generated dependencies
