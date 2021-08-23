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

#
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
# Copyright 2021 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
#
# Built in SFW with gcc and builds cleanly now only with gcc

BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

PATH=$(JAVA_HOME)/bin:$(USRBINDIR)

COMPONENT_FMRI=           runtime/erlang
COMPONENT_NAME=     erlang
COMPONENT_VERSION=    22.2.8
COMPONENT_PROJECT_URL=  http://www.erlang.org/
COMPONENT_SRC_NAME= otp_src
COMPONENT_SRC=    $(COMPONENT_SRC_NAME)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= OTP-${COMPONENT_VERSION}.tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:71f73ddd59db521928a0f6c8d4354d6f4e9f4bfbd0b40d321cd5253a6c79b095
COMPONENT_ARCHIVE_URL=  https://github.com/erlang/otp/archive/${COMPONENT_ARCHIVE}
COMPONENT_POST_UNPACK_ACTION= ( $(MV) otp-OTP-$(COMPONENT_VERSION) $(COMPONENT_SRC))
COMPONENT_PREP_ACTION = (cd $(@D); ./otp_build autoconf)
COMPONENT_VERSION_SHORT= $(shell echo $(COMPONENT_VERSION) | cut -d'.' -f1-2)
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_LICENSE=        Apache-2.0
COMPONENT_LICENSE_FILE=   LICENSE.txt
COMPONENT_SUMMARY= Erlang/OTP
COMPONENT_DESCRIPTION= Erlang programming language and OTP libraries

# manpages
COMPONENT_NAME_1= otp_doc_man
COMPONENT_SRC_1=  $(COMPONENT_NAME_1)_$(COMPONENT_VERSION_SHORT)
COMPONENT_ARCHIVE_1=  $(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:aad7e3795a44091aa33a460e3fdc94efe8757639caeba0b5ba7d79bd91c972b3
COMPONENT_ARCHIVE_URL_1=  $(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE_1)
UNPACK_ARGS_1=  -r $(COMPONENT_SRC_1)
PKG_PROTO_DIRS += $(COMPONENT_SRC_1)

# HTML documentation
COMPONENT_NAME_2= otp_doc_html
COMPONENT_SRC_2=  $(COMPONENT_NAME_2)_$(COMPONENT_VERSION_SHORT)
COMPONENT_ARCHIVE_2=  $(COMPONENT_SRC_2).tar.gz
COMPONENT_ARCHIVE_HASH_2= \
    sha256:09d41810d79fafde293feb48ebb249940eca6f9f5733abb235e37d06b8f482e3
COMPONENT_ARCHIVE_URL_2=  $(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE_2)
UNPACK_ARGS_2=  -r $(COMPONENT_SRC_2)
PKG_PROTO_DIRS += $(COMPONENT_SRC_2)

include $(WS_MAKE_RULES)/common.mk

SYSTEM_TEST_TARGET= configure $(SYSTEM_TEST_64)

CFLAGS += -std=gnu99 -D_XOPEN_SOURCE=600 -D__EXTENSIONS__

# Fix 64-bit linking.
LDFLAGS += $(CC_BITS)

CXXFLAGS += -std=c++11

CONFIGURE_OPTIONS.64 += --with-wx-config=/usr/bin/$(MACH64)/wx-config
CONFIGURE_OPTIONS += CPPFLAGS="$(CPPFLAGS) -I/usr/include/gd2"
CONFIGURE_OPTIONS += --enable-smp-support
CONFIGURE_OPTIONS += --enable-threads
CONFIGURE_OPTIONS += --with-ssl
CONFIGURE_OPTIONS += --enable-fips
CONFIGURE_OPTIONS += --enable-dynamic-ssl-lib

# The HiPE portion is a bit sensitive, and only seems to work 64-bit on
# amd64 (thus the variant.arch tagging in erlang.p5m). erts/config.log
# can be very interesting if issues occur.
CONFIGURE_OPTIONS.i386  = --enable-hipe
CONFIGURE_OPTIONS.sparc = --disable-hipe
# Disable kernel poll on sparc to avoid hangs in erl_child_setup (bug 31443512).
CONFIGURE_OPTIONS.sparc += --disable-kernel-poll

# Erlang doesn't appear to like ASLR: it uses mmap() with MAP_FIXED, and
# makes assumptions about memory layout that aren't true on Solaris x86,
# leading to segmentation faults in erlc.
ASLR_MODE =	$(ASLR_DISABLE)

# Use cp(1) instead of cloney because erlang's 'install' target uses 'tar'
# to copy files and our tar doesn't handle long links by default.  Between
# the use of 'tar' and 'ld', a path adjustment wasn't an option due to the
# need for /usr/bin/ld and /usr/gnu/bin/tar.  This is still the case with
# erlang version 17.5.
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CP) -rp $(SOURCE_DIR)/. $(@D))
CONFIGURE_SCRIPT =		$(@D)/configure

# We need to re-run the nested configure script for the wx sub-component so
# that it will properly detect wxWidgets support by adding -std=c++11 to $(CXX)
# (workaround for the configure script ignoring CXXFLAGS) and with ERL_TOP set
# so that the wx component knows we're building inside the erlang source tree.
COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(@D)/lib/wx; $(ENV) $(CONFIGURE_ENV) \
		CXX="$(CXX) -std=c++11" \
		ERL_TOP="$(@D)" \
		$(CONFIG_SHELL) \
		./configure $(CONFIGURE_OPTIONS))

# Always show the build and link lines for easier debugging.
COMPONENT_BUILD_ARGS +=	V=1

# fix build on jenkins
COMPONENT_BUILD_ENV += HOME=/tmp
COMPONENT_INSTALL_ENV += HOME=/tmp
COMPONENT_TEST_ENV += HOME=/tmp

COMPONENT_INSTALL_ARGS += INSTALL_PREFIX=$(PROTO_DIR)

COMPONENT_TEST_ENV +=		ERL_TOP=$(BUILD_DIR_64)
COMPONENT_TEST_TARGETS =	tests

COMPONENT_SYSTEM_TEST_ENV +=	ERL_TOP=$(BUILD_DIR_64)
COMPONENT_SYSTEM_TEST_TARGETS =	tests

COMPONENT_TEST_TRANSFORMS += \
	'-e "/^gmake.*release_tests_spec/d" '

# remove INSTALL_PREFIX from path
COMPONENT_POST_INSTALL_ACTION += \
	$(PERL) -pi -e "s|$(PROTO_DIR)||g" \
		$(PROTOUSRLIBDIR64)/erlang/bin/erl \
		$(PROTOUSRLIBDIR64)/erlang/releases/RELEASES

# common targets
build:    $(BUILD_64)

install:  $(INSTALL_64)

test:     $(TEST_64)

# manually added
REQUIRED_PACKAGES += runtime/java/openjdk8

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/graphics/wxwidgets
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/glu
