#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2017 Aurelien Larcher.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= patchutils
COMPONENT_VERSION= 0.3.4
COMPONENT_FMRI= text/patchutils
COMPONENT_SUMMARY= patchutils - Tools for manipulating patch files
COMPONENT_PROJECT_URL= http://cyberelk.net/tim/software/patchutils/
COMPONENT_CLASSIFICATION= System/Text Tools
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:cf55d4db83ead41188f5b6be16f60f6b76a87d5db1c42f5459d596e81dabe876
COMPONENT_ARCHIVE_URL= \
  http://cyberelk.net/tim/data/patchutils/stable/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_BINDIR.64= $(CONFIGURE_BINDIR.32)

CONFIGURE_OPTIONS +=	--with-patch=gpatch
CONFIGURE_OPTIONS +=	--with-diff=gdiff

COMPONENT_PRE_TEST_ACTION = \
  ($(GSED) -i -e '1 s;/bin/sh;/bin/bash;' $(SOURCE_DIR)/tests/*/run-test; \
   chmod a+x $(@D)/scripts/*diff )

COMPONENT_TEST_ENV += LANG=C
COMPONENT_TEST_ENV += PATH=$(PROTOUSRBINDIR):$(PATH)

unexport SHELLOPTS

COMPONENT_TEST_TRANSFORMS += \
 	'-n ' \
	'-e "/TOTAL/p" ' \
	'-e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/ERROR/p" '

build: $(BUILD_64)

install: $(INSTALL_64)

test: $(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
