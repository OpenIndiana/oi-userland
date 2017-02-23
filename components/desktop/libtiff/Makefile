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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libtiff
COMPONENT_VERSION=	4.0.7
COMPONENT_PROJECT_URL=	http://www.simplesystems.org/libtiff/ 
COMPONENT_SRC=		tiff-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:9f43a2cfb9589e5cecaa66e16bf87f814c945f22df7ba600d63aac4632c4f019
COMPONENT_ARCHIVE_URL=	http://download.osgeo.org/libtiff/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libtiff
COMPONENT_ANITYA_ID=	1738

TPNO=			32732

# Added to find the *.3tiff that go into /usr/share/man/man3tiff
PKG_PROTO_DIRS += $(COMPONENT_SRC)/man

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CC 			+= $(CC_BITS)

# Only build C library, not C++ library
CONFIGURE_OPTIONS       += --disable-cxx
# Only build shared library, not static libraries
CONFIGURE_OPTIONS       += --enable-shared --disable-static
# Don't build tiffgt utility which drags in a pile of OpenGL dependencies
CONFIGURE_OPTIONS       += ax_cv_check_gl_libgl="no"

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_ARGS =   -k -i
COMPONENT_TEST_TARGETS	= check
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/result_count/d" ' \
        '-e "/TOTAL:/p" ' \
        '-e "/SKIP:/p" ' \
        '-e "/PASS:/p" ' \
        '-e "/FAIL:/p" ' \
        '-e "/ERROR:/p" '

configure:	$(CONFIGURE_32_and_64)

build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64) $(BUILD_DIR)/.merged-header

test:           $(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

$(BUILD_DIR)/.merged-header: $(BUILD_DIR_32)/.installed $(BUILD_DIR_64)/.installed
	-$(RM) $(PROTO_DIR)/usr/include/tiffconf.h
	$(GDIFF) -D _LP64 \
            $(BUILD_DIR_32)/libtiff/tiffconf.h $(BUILD_DIR_64)/libtiff/tiffconf.h \
            > $(PROTO_DIR)/usr/include/tiffconf.h; \
	diffstatus=$$? ; \
	if (( $$diffstatus != 1 )) ; then exit $$diffstatus ; fi

REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math

