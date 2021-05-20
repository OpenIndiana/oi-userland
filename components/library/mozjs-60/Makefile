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
# Copyright (c) 2020, 2021, Oracle and/or its affiliates.
# Copyright 2021 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
#

BUILD_BITS = 64

include ../../../make-rules/shared-macros.mk

GCC_VERSION= 10
GNU_ARCH= x86_64-sun-solaris

COMPONENT_NAME=		mozjs
COMPONENT_VERSION=	60.8.0
COMPONENT_PROJECT_URL=	https://developer.mozilla.org/en-US/docs/Mozilla/Projects/SpiderMonkey
COMPONENT_SRC=          mozjs-60.8.0
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
	sha256:697331336c3d65b80ded9ca87b4a8ceb804e5342b476eaa133ac638102a9dc5d
COMPONENT_ARCHIVE_URL=  http://ftp.gnome.org/pub/gnome/teams/releng/tarballs-needing-help/mozjs/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= library/mozjs-60
COMPONENT_SUMMARY= Javascript engine
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_LICENSE= MPL v2.0
COMPONENT_LICENSE_FILE= mozjs.license

CXXFLAGS += -std=c++11

# Only used during build process.
PYTHON_VERSIONS= 2.7
PYTHON= $(PYTHON.2.7.$(BITS))

# Tests hook up need work
TEST_TARGET = $(SKIP_TEST)

include $(WS_MAKE_RULES)/common.mk

xCOMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_PRE_CONFIGURE_ACTION += ( \
  cd $(COMPONENT_NAME)-$(COMPONENT_VERSION); \
  cd js/src; \
  autoconf-2.13 --localdir=. old-configure.in; \
  touch configure; \
  );

# configure script is not at root of source tree.
CONFIGURE_SCRIPT= $(SOURCE_DIR)/js/src/configure

CONFIGURE_ENV += PYTHON="$(PYTHON)"
CONFIGURE_ENV += LDSHARED="$(CC) -shared"
CONFIGURE_ENV += NSPR_CONFIG=/usr/bin/amd64/nspr-config

# detection of ARCH by config.guess depends on the compiler (e.g. gcc > 8)
CONFIGURE_OPTIONS += --target=$(GNU_ARCH)
CONFIGURE_OPTIONS += --disable-tests
CONFIGURE_OPTIONS += --enable-optimize
CONFIGURE_OPTIONS += --enable-readline
CONFIGURE_OPTIONS += --enable-shared-js
CONFIGURE_OPTIONS += --enable-threadsafe
CONFIGURE_OPTIONS += --with-intl-api
CONFIGURE_OPTIONS += --with-system-zlib
CONFIGURE_OPTIONS += --with-x
CONFIGURE_OPTIONS += --with-system-nspr

COMPONENT_BUILD_ARGS += $(JOBS:%=-j%)

COMPONENT_POST_INSTALL_ACTION  = \
    for file in `find $(PROTO_DIR)$(CONFIGURE_LIBDIR.$(BITS)) -name "*.so"`; do \
        /usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$(GCC_LIBDIR):/usr/lib/mps/amd64"' $$file ; \
        /usr/bin/elfedit -e 'dyn:value -s  RPATH   "$(GCC_LIBDIR):/usr/lib/mps/amd64"' $$file ; \
    done ; \
    for file in `find $(PROTO_DIR)$(USRBINDIR) -name "js60"`; do \
        /usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$(GCC_LIBDIR):/usr/lib/mps/amd64"' $$file ; \
        /usr/bin/elfedit -e 'dyn:value -s  RPATH   "$(GCC_LIBDIR):/usr/lib/mps/amd64"' $$file ; \
    done ;

# js coredumps on sparc - see bug 24935318
ifeq ($(MACH), sparc)
LD_EXEC_OPTIONS.64 += -M $(WS_COMPONENTS)/desktop/polkit/mapfile
COMPONENT_BUILD_ENV.64 += LD_EXEC_OPTIONS="$(LD_EXEC_OPTIONS.64)"
COMPONENT_INSTALL_ENV.64 += LD_EXEC_OPTIONS="$(LD_EXEC_OPTIONS.64)"
endif

unexport SHELLOPTS
COMPONENT_TEST_ARGS =   -k -i
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/TOTAL:/p" ' \
        '-e "/SKIP:/p" ' \
        '-e "/PASS:/p" ' \
        '-e "/FAIL:/p" ' \
        '-e "/ERROR:/p" '

# Build dependencies
REQUIRED_PACKAGES += developer/build/autoconf-213
REQUIRED_PACKAGES += developer/gcc-10

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/nspr
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
