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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2013  Erol Zavidic. All rights reserved.
# Copyright (c) 2024  Friedrich Kink. All rights reserved.
#

BUILD_STYLE=	cmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libmemcached
COMPONENT_MAJOR_VERSION=	1.1
COMPONENT_VERSION=      $(COMPONENT_MAJOR_VERSION).4
COMPONENT_SUMMARY=	libmemcached-awesome is an open source C/C++ client library and tools for the memcached server
COMPONENT_FMRI=		library/$(COMPONENT_NAME)
COMPONENT_DESCRIPTION=	It has been designed to be light on memory usage, thread safe, and provide full access to server side methods.
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:c477e1f6510e1dc698e84f3717ce690a8f65b94c616ecaa62306cce0f5e3116a
COMPONENT_ARCHIVE_URL=	https://github.com/awesomized/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz 
COMPONENT_PROJECT_URL=  https://awesomized.github.io/libmemcached
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	BSD-3-Clause
COMPONENT_LICENSE_FILE= LICENSE.HEADER

include $(WS_MAKE_RULES)/common.mk

LDFLAGS  += -lsocket -lnsl

CMAKE_OPTIONS += -DBUILD_SHARED_LIBS=ON
CMAKE_OPTIONS += -DBUILD_DOCS_MAN=ON
CMAKE_OPTIONS += -DBUILD_TESTING=ON
CMAKE_OPTIONS += -DENABLE_MEMASLAP=ON
CMAKE_OPTIONS += -DENABLE_HASH_HSIEH=ON
CMAKE_OPTIONS += -DENABLE_HASH_FNV64=ON
CMAKE_OPTIONS += -DENABLE_HASH_MURMUR=ON
CMAKE_OPTIONS += -DENABLE_SASL=OFF
CMAKE_OPTIONS += -DENABLE_DTRACE=OFF
CMAKE_OPTIONS += -DENABLE_OPENSSL_CRYPTO=OFF

# need some files in $(SOURCE_DIR)/docs during build
COMPONENT_PRE_CONFIGURE_ACTION = \
    ($(CLONEY) $(SOURCE_DIR) $(@D))

ASLR_MODE = $(ASLR_ENABLE)

COMPONENT_TEST_TRANSFORMS = \
        '-n ' \
        '-e "s/Passed.*$$/Passed/p" ' \
        '-e "s/Failed .*$$/Failed/p" '

COMPONENT_TEST_ARGS += -k -i

COMPONENT_POST_INSTALL_ACTION  = \
    for file in `find $(PROTO_DIR)$(USRLIBDIR64) -name "*.so.*"`; do \
        /usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$(GCC_LIBDIR)"' $$file ; \
        /usr/bin/elfedit -e 'dyn:value -s  RPATH   "$(GCC_LIBDIR)"' $$file ; \
    done ; \
    for file in `find $(PROTO_DIR)$(USRBINDIR) -name "mem*"`; do \
        /usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$(GCC_LIBDIR)"' $$file ; \
        /usr/bin/elfedit -e 'dyn:value -s  RPATH   "$(GCC_LIBDIR)"' $$file ; \
    done ;

# Manually added dependencies
REQUIRED_PACKAGES += service/memcached

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/libevent2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
