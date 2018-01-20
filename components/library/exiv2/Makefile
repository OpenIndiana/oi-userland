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
# Copyright 2017 Carsten Grzemba
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= exiv2
COMPONENT_VERSION= 0.25
COMPONENT_REVISION = 2
COMPONENT_SUMMARY= Image metadata library and tools
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:c80bfc778a15fdb06f71265db2c3d49d8493c382e516cb99b8c9f9cbde36efa4
COMPONENT_ARCHIVE_URL= \
  http://www.exiv2.org/$(COMPONENT_ARCHIVE)

COMPONENT_PROJECT_URL = http://www.exiv2.org
COMPONENT_FMRI = image/library/exiv2
COMPONENT_LICENSE = GPLv2
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_CLASSIFICATION = System/Multimedia Libraries

CONFIGURE_FIX_LIBTOOL_RPATH = no

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = (cd $(@D)/config && libtoolize -f && autoconf -o ../configure)

COMPONENT_PRE_CONFIGURE_ACTION = \
     $(CLONEY) $(SOURCE_DIR) $(@D)

CONFIGURE_OPTIONS += --disable-rpath
CONFIGURE_ENV.64 += LT_SYS_LIBRARY_PATH="/lib/$(MACH64):/usr/lib/$(MACH64)"
CONFIGURE_ENV.64 += lt_cv_sys_lib_dlsearch_path_spec="/lib/$(MACH64) /usr/lib/$(MACH64)"

# mkdir option '-v' is used
PATH=$(PATH.gnu)

LDFLAGS += -lnsl -lsocket 

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/gcc-6-runtime
REQUIRED_PACKAGES += system/library/math
