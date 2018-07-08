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
# Copyright 2016 Alexander Pyhalov
# Copyright 2018 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= yaz
COMPONENT_VERSION= 5.25.0
COMPONENT_SUMMARY= toolkit supporting the development of Z39.50/SRW/SRU clients and servers
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:980759ffeb6ccb319dfa41613c56764c18b1f02b78cb2a1ade8dee1e2ec7a183
COMPONENT_ARCHIVE_URL= \
  http://ftp.indexdata.dk/pub/yaz/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.indexdata.com/resources/software/yaz/
COMPONENT_FMRI = database/yaz
COMPONENT_CLASSIFICATION = Development/Databases
COMPONENT_LICENSE = BSD
COMPONENT_LICENSE_FILE = LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Force use of gnutls-3 pkgconfig during 2.x->3.x transition
GNUTLS_PKG_CONFIG_PATH_32 = /usr/lib/pkgconfig/gnutls-3
GNUTLS_PKG_CONFIG_PATH_64 = /usr/lib/$(MACH64)/pkgconfig/gnutls-3
PKG_CONFIG_PATH = $(GNUTLS_PKG_CONFIG_PATH_$(BITS)):$(PKG_CONFIG_PATH.$(BITS))

LD_OPTIONS.32 += -L/usr/lib/gnutls-3 -R/usr/lib/gnutls-3
LD_OPTIONS.64 += -L/usr/lib/$(MACH64)/gnutls-3 -R/usr/lib/$(MACH64)/gnutls-3
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

CONFIGURE_OPTIONS += --with-xml2
CONFIGURE_OPTIONS += --with-xslt
CONFIGURE_OPTIONS += --without-icu
CONFIGURE_OPTIONS += --disable-static

# Without this tests fail
ENV=/usr/bin/env -i
COMPONENT_TEST_ENV += LD_OPTIONS="$(LD_OPTIONS)"

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/TOTAL:/p" ' \
        '-e "/SKIP:/p" ' \
        '-e "/PASS:/p" ' \
        '-e "/FAIL:/p" ' \
        '-e "/ERROR:/p" '

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libmemcached
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
