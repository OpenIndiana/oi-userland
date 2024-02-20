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

BUILD_BITS= 64
USE_OPENSSL31= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_FMRI= runtime/erlang
COMPONENT_NAME= erlang
COMPONENT_VERSION= 26.2.2
COMPONENT_PROJECT_URL= https://erlang.org/
COMPONENT_SRC_NAME= otp_src
COMPONENT_SRC= $(COMPONENT_SRC_NAME)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= ${COMPONENT_SRC}.tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:d537ff4ac5d8c1cb507aedaf7198fc1f155ea8aa65a8d83edb35c2802763cc28
COMPONENT_ARCHIVE_URL= https://github.com/erlang/otp/releases/download/OTP-${COMPONENT_VERSION}/${COMPONENT_ARCHIVE}
COMPONENT_POST_UNPACK_ACTION= ( $(RM) -r $(COMPONENT_SRC)/lib/wx )
COMPONENT_VERSION_SHORT= 26.2
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_LICENSE= Apache-2.0
COMPONENT_LICENSE_FILE= LICENSE.txt
COMPONENT_SUMMARY= Erlang/OTP
COMPONENT_DESCRIPTION= Erlang programming language and OTP libraries

# manpages
# no 26.2 available as of 16.02.2024. hence using 26.1.
COMPONENT_NAME_1= otp_doc_man
COMPONENT_SRC_1= $(COMPONENT_NAME_1)_26.1
COMPONENT_ARCHIVE_1= $(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:2320a0af58119497bc3c0e6d8f08fbb0c6db5778a841b96a7f984e40c321b3ee
COMPONENT_ARCHIVE_URL_1= $(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE_1)
UNPACK_ARGS_1= -r $(COMPONENT_SRC_1)

include $(WS_MAKE_RULES)/common.mk

SYSTEM_TEST_TARGET= configure $(SYSTEM_TEST_64)

# Fix 64-bit linking.
LDFLAGS += $(CC_BITS)
CFLAGS += -finline-functions -funroll-loops
CXXFLAGS += -finline-functions -funroll-loops -fno-exceptions -fno-rtti

CONFIGURE_OPTIONS += --enable-smp-support
CONFIGURE_OPTIONS += --enable-threads
CONFIGURE_OPTIONS += --with-ssl=$(OPENSSL_PREFIX)
CONFIGURE_OPTIONS += --with-ssl-lib-subdir=/amd64
CONFIGURE_OPTIONS += --enable-fips
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

# Use cp(1) instead of cloney because erlang's 'install' target uses 'tar'
# to copy files and our tar doesn't handle long links by default.  Between
# the use of 'tar' and 'ld', a path adjustment wasn't an option due to the
# need for /usr/bin/ld and /usr/gnu/bin/tar.  This is still the case with
# erlang version 17.5.
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CP) -rp $(SOURCE_DIR)/. $(@D))
CONFIGURE_SCRIPT = $(@D)/configure

# fix build on jenkins
COMPONENT_BUILD_ENV += HOME=/tmp
COMPONENT_INSTALL_ENV += HOME=/tmp
COMPONENT_TEST_ENV += HOME=/tmp
COMPONENT_INSTALL_ARGS += INSTALL_PREFIX=$(PROTO_DIR)
COMPONENT_TEST_ENV += ERL_TOP=$(BUILD_DIR_64)
COMPONENT_TEST_TARGETS = tests
COMPONENT_SYSTEM_TEST_ENV += ERL_TOP=$(BUILD_DIR_64)
COMPONENT_SYSTEM_TEST_TARGETS =	tests
COMPONENT_TEST_TRANSFORMS += \
	'-e "/^gmake.*release_tests_spec/d" '

# remove INSTALL_PREFIX from path
COMPONENT_POST_INSTALL_ACTION += \
	$(PERL) -pi -e "s|$(PROTO_DIR)||g" \
		$(PROTOUSRLIBDIR64)/erlang/bin/erl \
		$(PROTOUSRLIBDIR64)/erlang/releases/RELEASES
COMPONENT_POST_INSTALL_ACTION += ;( $(MV) $(COMPONENT_SRC_1)/man $(PROTO_DIR)/usr/ )

# common targets
build:    $(BUILD_64)
install:  $(INSTALL_64)
test:     $(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/security/openssl-31
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
