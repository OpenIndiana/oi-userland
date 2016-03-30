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
# Copyright 2016 Jim Klimov
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME= malamute

# See configure.ac for ABI version mapping to software version
# NOTE: This requires functionality currently only offered by libzmq-4.2.0
# which is a `git HEAD` (no tarballs officially released yet) and which
# claims ABI version 5 (same as libzmq-4.1.4, the latest official release)
# although libzmq-4.1.4's ABIv5 is not sufficient to build malamute broker :(
COMPONENT_VERSION_ABI= 1
COMPONENT_VERSION= 1.0
COMPONENT_SUMMARY= Malamute - a message broker based on 0MQ
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:91b509c1e892a39a2f88df0c0df4d955ffb1360229f9e0b2a7c3eda44bba22be
COMPONENT_ARCHIVE_URL= \
  https://github.com/zeromq/$(COMPONENT_NAME)/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL= http://zeromq.org/
# Two licenses in tarball, LGPLv3+ is referenced in their spec-file
COMPONENT_LICENSE_FILE= LICENSE
COMPONENT_LICENSE= MPLv2
COMPONENT_CLASSIFICATION= System/Libraries

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PKG_OPTIONS +=	-D COMPONENT_VERSION_ABI="$(COMPONENT_VERSION_ABI)"

COMPONENT_PREP_ACTION =	\
	( cd $(@D) && \
	  libtoolize --copy --force && \
	  aclocal -I m4 && \
	  autoheader && \
	  automake -c -f -a && \
	  autoconf )

COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

CXXFLAGS.32=-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE
CFLAGS.32=-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE

# Deprecated header file warnings break build
CPPFLAGS += -Wno-error=cpp
CXXFLAGS += -Wno-error=cpp
CFLAGS   += -Wno-error=cpp

CXXFLAGS += $(CXXFLAGS.$(BITS))
CFLAGS   += $(CFLAGS.$(BITS))

CXXFLAGS += -D_POSIX_PTHREAD_SEMANTICS
CFLAGS   += -D_POSIX_PTHREAD_SEMANTICS

# Note: there's a bug in malamute v1.0 build system, so the
# mlm_proto_t is marked as draft API, but the MLM_BUILD_DRAFT_API
# macro may be not defined with --enable-drafts as documented.
# One needs to BOTH add --enable-drafts and define the macro to be sure.
CXXFLAGS += -DMLM_BUILD_DRAFT_API
CFLAGS   += -DMLM_BUILD_DRAFT_API

CXXFLAGS += -I$(SOURCE_DIR)/include
CFLAGS   += -I$(SOURCE_DIR)/include
CXXFLAGS += -I$(SOURCE_DIR)/src
CFLAGS   += -I$(SOURCE_DIR)/src

CONFIGURE_OPTIONS +=	--enable-static=no
CONFIGURE_OPTIONS +=	--enable-drafts=yes
CONFIGURE_OPTIONS +=	--with-docs=yes

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
