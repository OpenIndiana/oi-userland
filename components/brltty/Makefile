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
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= brltty
COMPONENT_VERSION= 4.4
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= Braille support
COMPONENT_FMRI= library/accessibility/brltty
COMPONENT_CLASSIFICATION= Applications/Universal Access
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:8d53756cbc6368bd0bfcbc27162edebdba49d9cb12ac73220c22f4e1f3413ab6
COMPONENT_ARCHIVE_URL= \
  http://www.mielke.cc/brltty/archive/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.mielke.cc/brltty/

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/bin:/usr/gnu/bin

COMPONENT_PREP_ACTION =        ( cd $(@D) && \
                                        autoconf -f )

# Missing files on install without this
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))


ICU_CONFIG.32=/usr/bin/icu-config
ICU_CONFIG.64=/usr/bin/$(MACH64)/icu-config

CONFIGURE_LOCALSTATEDIR=/var/lib

CONFIGURE_OPTIONS += --disable-tcl-bindings
CONFIGURE_OPTIONS += --disable-speech-support

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV += PYTHON="$(PYTHON)"
CONFIGURE_ENV += ICU_CONFIG="$(ICU_CONFIG.$(BITS))"

COMPONENT_BUILD_ENV.64 = LDFLAGS=-m64
COMPONENT_BUILD_ENV += $(COMPONENT_BUILD_ENV.$(BITS))

COMPONENT_INSTALL_ARGS += INSTALL_ROOT=$(PROTO_DIR)
COMPONENT_INSTALL_ARGS += sysconfdir=$(PROTO_DIR)/etc

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)
