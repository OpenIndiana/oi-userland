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
# Copyright 2023 Carsten Grzemba
# Copyright 2024 Goetz Fischer, R-A-C. All rights reserved.
#

USE_PARALLEL_BUILD= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= erlang
COMPONENT_VERSION= 27.1.2
COMPONENT_VERSION_SHORT= $(shell echo $(COMPONENT_VERSION) | cut -d'.' -f1-2)
COMPONENT_SUMMARY= Erlang programming language and OTP libraries
COMPONENT_PROJECT_URL= https://erlang.org/
COMPONENT_SRC_NAME= otp_src
COMPONENT_SRC= $(COMPONENT_SRC_NAME)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= ${COMPONENT_SRC}.tar.gz
COMPONENT_ARCHIVE_HASH= sha256:1772e9fa07b2b020ed5911d6ce78b251dfb6ed8509ed7de9d372e96b87251d14
COMPONENT_ARCHIVE_URL= https://github.com/erlang/otp/releases/download/OTP-${COMPONENT_VERSION}/${COMPONENT_ARCHIVE}
COMPONENT_FMRI= runtime/erlang
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_LICENSE= Apache-2.0
COMPONENT_LICENSE_FILE= LICENSE.txt

# manpages
COMPONENT_NAME_1= otp_doc_man
COMPONENT_SRC_1= $(COMPONENT_NAME_1)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_1= $(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= sha256:76f01e6833d841e614929a2b7426b0b08b32daae985ee3e81f2dedb17d367048
COMPONENT_ARCHIVE_URL_1= https://github.com/erlang/otp/releases/download/OTP-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE_1)
UNPACK_ARGS_1= -r $(COMPONENT_SRC_1)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_UNPACK_ACTION= ( $(RM) -r $(COMPONENT_SRC)/lib/wx )

# Fix 64-bit linking.
LDFLAGS += $(CC_BITS)

# testing these with gcc 13. can safely be omitted in doubt.
CFLAGS += -finline-functions -funroll-loops
CXXFLAGS += -finline-functions -funroll-loops -fno-exceptions -fno-rtti

CONFIGURE_OPTIONS += --enable-smp-support
CONFIGURE_OPTIONS += --enable-threads
CONFIGURE_OPTIONS += --with-ssl=$(OPENSSL_PREFIX)
CONFIGURE_OPTIONS += --with-ssl-lib-subdir=/amd64
CONFIGURE_OPTIONS += --enable-dynamic-ssl-lib
CONFIGURE_OPTIONS += --disable-silent-rules
CONFIGURE_OPTIONS += --without-javac

# The HiPE portion is a bit sensitive, and only seems to work 64-bit on
# amd64 (thus the variant.arch tagging in erlang.p5m). erts/config.log
# can be very interesting if issues occur.
CONFIGURE_OPTIONS.i386  = --enable-hipe
CONFIGURE_OPTIONS.sparc = --disable-hipe
# Disable kernel poll on sparc to avoid hangs in erl_child_setup (bug 31443512).
CONFIGURE_OPTIONS.sparc += --disable-kernel-poll
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(MACH))

# Erlang doesn't appear to like ASLR: it uses mmap() with MAP_FIXED, and
# makes assumptions about memory layout that aren't true on Solaris x86,
# leading to segmentation faults in erlc.
ASLR_MODE =	$(ASLR_DISABLE)

COMPONENT_PRE_CONFIGURE_ACTION= ( CLONEY_MODE=copy $(CLONEY) $(SOURCE_DIR)/. $(@D) )

CONFIGURE_SCRIPT = $(@D)/configure

# fix build on jenkins
COMPONENT_BUILD_ENV += HOME=/tmp
COMPONENT_INSTALL_ENV += HOME=/tmp
COMPONENT_INSTALL_ARGS += INSTALL_PREFIX=$(PROTO_DIR)
COMPONENT_TEST_ENV += HOME=/tmp
COMPONENT_TEST_ENV += ERL_TOP=$(BUILD_DIR_64)
# Run Erlang release tests; it takes many hours...
COMPONENT_TEST_DIR = $(COMPONENT_DIR)
COMPONENT_TEST_CMD = $(SHELL)
COMPONENT_TEST_TARGETS = run_erlang_tests.sh $(BUILD_DIR_64)
COMPONENT_TEST_TRANSFORMS += '-e "/^gmake.*release_tests_spec/d" '
COMPONENT_TEST_TRANSFORMS += '-e "/^run_erlang_tests.sh/d" '

# remove INSTALL_PREFIX from path
COMPONENT_POST_INSTALL_ACTION += \
	$(PERL) -pi -e "s|$(PROTO_DIR)||g" \
		$(PROTOUSRLIBDIR64)/erlang/bin/erl \
		$(PROTOUSRLIBDIR64)/erlang/releases/RELEASES ;
COMPONENT_POST_INSTALL_ACTION += ( $(MKDIR) $(PROTO_DIR)/usr/share ) ;
COMPONENT_POST_INSTALL_ACTION += ( $(MV) $(COMPONENT_SRC_1)/man $(PROTO_DIR)/usr/share/ )

# common targets
build:    $(BUILD_64)
install:  $(INSTALL_64)
test:     $(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
