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
# Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.
#

PREFERRED_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		idnkit
COMPONENT_VERSION=	2.3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_PROJECT_URL=  https://jprs.co.jp/idn
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:26d07117650042ab4693f0e00960275d58a1be773e6d13c503ba384710f3e97e
COMPONENT_ARCHIVE_URL=  https://jprs.co.jp/idn/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)

CFLAGS += -DSUN_CHANGE

CONFIGURE_OPTIONS += --with-iconv=no

COMPONENT_BUILD_TARGETS = all info

# Note a few tests fail or are skipped since they expect the config files to
# be installed in /etc
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_PRE_TEST_ACTION = (cp $(SOURCE_DIR)/test/normalization/*.conf \
	$(BUILD_DIR_$(BITS))/test/normalization/ && \
	cp $(SOURCE_DIR)/test/loadconf/no-newline.conf \
	$(BUILD_DIR_$(BITS))/test/loadconf )


COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/^PASS/p" ' \
	'-e "/^All/p" ' \
	'-e "/^SKIP/p" ' \
	'-e "/FAIL:/p" ' \
	'-e "/ERROR:/p" '


# common targets
build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(TEST_32_and_64)
