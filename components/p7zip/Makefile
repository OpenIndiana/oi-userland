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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin

COMPONENT_NAME=		p7zip
COMPONENT_VERSION=	9.20.1
COMPONENT_PROJECT_URL=	http://p7zip.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)_src_all.tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:49557e7ffca08100f9fc687f4dfc5aea703ca207640c76d9dee7b66f03cb4782
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/project/p7zip/p7zip/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

COMPONENT_PREP_ACTION = (cd $(@D); cp ../makefile.solaris makefile.machine)
COMPONENT_BUILD_TARGETS = all3
COMPONENT_INSTALL_ARGS += DEST_HOME=/usr DEST_DIR=$(PROTO_DIR)

$(SOURCE_DIR)/DOCS/copying.txt $(SOURCE_DIR)/DOCS/unRarLicense.txt: prep

$(BUILD_DIR)/%: $(SOURCE_DIR)/DOCS/%
	$(CP) $< $@

$(BUILD_DIR)/copying.txt: $(SOURCE_DIR)/DOCS/copying.txt gpl_disclaimer
	$(CP) gpl_disclaimer $@
	echo "================================================================================" >> $@
	cat $(SOURCE_DIR)/DOCS/copying.txt >> $@

# common targets
build:		$(BUILD_32)

EXTRATARGETS = \
	$(BUILD_DIR)/copying.txt $(BUILD_DIR)/unRarLicense.txt

install:	build $(INSTALL_32) $(EXTRATARGETS)

# When p7zip's install target is run, it creates all its directories mode 555,
# so they're impossible to remove without adding the write bit first.
COMPONENT_POST_INSTALL_ACTION += $(CHMOD) -R u+w $(PROTO_DIR)

# build does this always
test:	$(BUILD_32)
	cd $(BUILD_DIR_32) && $(MAKE) -e test P7ZIP_HOME_DIR=$(BUILD_DIR_32)/bin
	cd $(BUILD_DIR_32) && $(MAKE) -e test_7z P7ZIP_HOME_DIR=$(BUILD_DIR_32)/bin
	cd $(BUILD_DIR_32) && $(MAKE) -e test_7zr P7ZIP_HOME_DIR=$(BUILD_DIR_32)/bin


BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
