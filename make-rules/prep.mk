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
# Copyright (c) 2010, Oracle and/or it's affiliates.  All rights reserved.
#

UNPACK =	$(TOOLS)/unpack.py
FETCH =		$(TOOLS)/fetch.py

ARCHIVES += $(COMPONENT_ARCHIVE)
CLEAN_PATHS += $(COMPONENT_SRC)
CLOBBER_PATHS += $(COMPONENT_ARCHIVE)

PATCHES =	$(shell find . -type f -name '*.patch' | \
			 sed -e 's;^\./;;' | grep -v $(COMPONENT_SRC) | sort)
STAMPS =	$(PATCHES:%=$(COMPONENT_SRC)/.%ed)

$(COMPONENT_SRC)/.%ed:	%
	$(GPATCH) -d $(@D) $(GPATCH_FLAGS) < $<
	$(TOUCH) $@

$(COMPONENT_ARCHIVE):
	$(FETCH) --file $@ \
		$(COMPONENT_ARCHIVE_URL:%=--url %) \
		$(COMPONENT_ARCHIVE_HASH:%=--hash %)

$(COMPONENT_SRC)/.unpacked:	$(COMPONENT_ARCHIVE)
	$(UNPACK) $(UNPACK_ARGS) $(COMPONENT_ARCHIVE)
	$(TOUCH) $@

$(COMPONENT_SRC)/.patched:	$(COMPONENT_SRC)/.unpacked $(STAMPS)
	$(TOUCH) $@

$(COMPONENT_SRC)/.prep:	$(COMPONENT_SRC)/.patched
	$(COMPONENT_PREP_ACTION)
	$(TOUCH) $@

prep::	$(COMPONENT_SRC)/.prep

download::	$(COMPONENT_ARCHIVE)

clean::
	$(RM) -r $(CLEAN_PATHS)

clobber::	clean
	$(RM) -r $(CLOBBER_PATHS)

