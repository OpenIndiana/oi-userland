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
# Copyright 2017 Alexander Pyhalov
# Copyright 2023 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= w3m
COMPONENT_VERSION=  0.5.6
COMPONENT_SUMMARY= A text-based web browser
COMPONENT_SRC= $(COMPONENT_NAME)-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:8dd652cd3f31817d68c7263c34eeffb50118c80be19e1159bf8cbf763037095e
COMPONENT_ARCHIVE_URL= \
  https://git.sr.ht/~rkta/w3m/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL= https://sr.ht/~rkta/w3m/
COMPONENT_FMRI= web/browser/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Applications/Internet
COMPONENT_LICENSE= MIT

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS+= --with-browser=/usr/bin/firefox
CONFIGURE_OPTIONS+= --with-imagelib=imlib2

# Use better openssl
CFLAGS  += -I$(OPENSSL_INCDIR)
LDFLAGS += -L$(OPENSSL_LIBDIR) -R$(OPENSSL_LIBDIR)

# make gcc 14 happy
CFLAGS += -Wno-implicit-function-declaration

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += library/gc
REQUIRED_PACKAGES += library/imlib2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
