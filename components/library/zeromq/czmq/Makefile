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

COMPONENT_NAME= czmq

# See configure.ac for ABI version mapping to software version
COMPONENT_VERSION_ABI= 3
COMPONENT_VERSION= 3.0.2
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= C bindings for 0MQ
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:8bca39ab69375fa4e981daf87b3feae85384d5b40cef6adbe9d5eb063357699a
COMPONENT_ARCHIVE_URL= \
  http://download.zeromq.org/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= http://zeromq.org/
# Two licenses in tarball, LGPLv3+ is referenced in their spec-file
COMPONENT_LICENSE_FILE= LICENSE
COMPONENT_LICENSE= MPLv2
COMPONENT_CLASSIFICATION= System/Libraries

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

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

CXXFLAGS+=$(CXXFLAGS.$(BITS))
CFLAGS += $(CFLAGS.$(BITS))

CXXFLAGS += -D_POSIX_PTHREAD_SEMANTICS
CFLAGS += -D_POSIX_PTHREAD_SEMANTICS

CONFIGURE_OPTIONS +=	--enable-static=no

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

# test_shutdown_stress fails
test: $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/c++/zeromq-3.2
REQUIRED_PACKAGES += system/library
