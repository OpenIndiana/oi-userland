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
# Copyright (c) 2010, 2011, Oracle and/or its affiliates. All rights reserved.
#

UNPACK =	$(WS_TOOLS)/userland-unpack
FETCH =		$(WS_TOOLS)/userland-fetch

ARCHIVES += $(COMPONENT_ARCHIVE)
CLEAN_PATHS += $(SOURCE_DIR)
CLOBBER_PATHS += $(COMPONENT_ARCHIVE)

PATCHES =	$(shell find . -type f -name '*.patch' | \
			 sed -e 's;^\./;;' | grep -v $(SOURCE_DIR) | sort)
STAMPS =	$(PATCHES:%=$(SOURCE_DIR)/.%ed)

$(SOURCE_DIR)/.%ed:	%
	$(GPATCH) -d $(@D) $(GPATCH_FLAGS) < $<
	$(TOUCH) $@

$(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE):	Makefile
	$(FETCH) --file $@ \
		$(COMPONENT_ARCHIVE_URL:%=--url %) \
		$(COMPONENT_ARCHIVE_HASH:%=--hash %)
	$(TOUCH) $@

$(SOURCE_DIR)/.unpacked:	$(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE) Makefile $(PATCHES)
	$(RM) -r $(SOURCE_DIR)
	$(UNPACK) $(UNPACK_ARGS) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE)
	$(TOUCH) $@

$(SOURCE_DIR)/.patched:	$(SOURCE_DIR)/.unpacked $(STAMPS)
	$(TOUCH) $@

$(SOURCE_DIR)/.prep:	$(SOURCE_DIR)/.patched
	$(COMPONENT_PREP_ACTION)
	$(TOUCH) $@

prep::	$(SOURCE_DIR)/.prep

download::	$(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE)

clean::
	$(RM) -r $(CLEAN_PATHS)

clobber::	clean
	$(RM) -r $(CLOBBER_PATHS)

