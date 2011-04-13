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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gzip
COMPONENT_VERSION=	1.3.5
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:843272609b9bff1bdf2770a28d498d6519901e73
COMPONENT_ARCHIVE_URL=	http://alpha.gnu.org/gnu/gzip/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS +=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)" 

# Fix references to Solaris renamed programs (z*->gz*) in man pages, info
# pages and in wrapper scripts.
COMPONENT_PRE_INSTALL_ACTION = \
	(cd $(COMPONENT_SRC) ; \
	 for file in `ls *.1 *.info z*.in` ; do \
		mv $$file $$file.tmp ; \
		sed -f $(COMPONENT_DIR)/renaming.sed $$file.tmp > $$file ; \
		$(RM) $$file.tmp ; \
	 done)

# Rename installed programs and man pages in proto dir (z*->gz*).
COMPONENT_POST_INSTALL_ACTION = \
	(for dir in $(PROTOUSRBINDIR) $(PROTOUSRSHAREMAN1DIR) ; do \
		cd $$dir; \
	 	for zfile in `ls z*`; do \
			mv $$zfile g$$zfile ; \
		done ; \
	 done)

# Provide missing man pages.
GZGREP_MAN_VARIANTS+=$(PROTOUSRSHAREMAN1DIR)/gzegrep.1
GZGREP_MAN_VARIANTS+=$(PROTOUSRSHAREMAN1DIR)/gzfgrep.1

$(GZGREP_MAN_VARIANTS):
	$(RM) $@; echo ".so man1/gzgrep.1" > $@

build:		$(BUILD_32)

install:	$(INSTALL_32) $(GZGREP_MAN_VARIANTS)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
