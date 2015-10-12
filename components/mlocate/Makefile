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
# Copyright (c) 2013, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=         mlocate
COMPONENT_VERSION=      0.25
COMPONENT_PROJECT_URL=  https://fedorahosted.org/mlocate
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:ab95c111f9dba35b5690896180dd0a7639dbf07d70b862fcb0731264d9273951
COMPONENT_ARCHIVE_URL=  https://fedorahosted.org/releases/m/l/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/mlocate

TPNO=			10233

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS.64 +=    CC="$(CC) -m64"
CONFIGURE_OPTIONS += --localstatedir="/var/cache"
CONFIGURE_OPTIONS += --sysconfdir="/etc"

COMPONENT_PREP_ACTION = (cd $(@D) ; autoreconf -f && automake)
COMPONENT_POST_INSTALL_ACTION= \
    @$(MKDIR) -p $(PROTO_DIR)/etc/; \
    $(CP) files/updatedb.conf $(PROTO_DIR)/etc/

COMPONENT_TEST_TRANSFORMS += \
	'-e "s|^make.*: Leaving directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^make.*: Entering directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^make.*: Nothing to be.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^/usr/gnu/bin/make.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "/^XXX_REMOVE_XXX$$/d" '

# Test 41 needs to be able to open at least 950 fds. Bump up the limit.
COMPONENT_TEST_ENV_CMD =	ulimit -n 1000; env

# Need /usr/gnu/bin before /usr/bin for GNU diff.
COMPONENT_TEST_ENV +=	PATH="$(@D)/src:$(GNUBIN):$(USRBINDIR):$(USRSBINDIR)"

COMPONENT_TEST_CMD =	$(SOURCE_DIR)/tests/testsuite
COMPONENT_TEST_TARGETS =

COMPONENT_SYSTEM_TEST_ENV_CMD =	ulimit -n 1000; env
COMPONENT_SYSTEM_TEST_ENV +=	PATH="$(GNUBIN):$(USRBINDIR):$(USRSBINDIR)"
COMPONENT_SYSTEM_TEST_CMD =	$(SHELL) $(SOURCE_DIR)/tests/testsuite
COMPONENT_SYSTEM_TEST_ARGS =	AUTOTEST_PATH=$(GNUBIN):$(USRBINDIR):$(USRSBINDIR)
COMPONENT_SYSTEM_TEST_TARGETS =

ASLR_MODE = $(ASLR_ENABLE)

configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

system-test:    configure $(SYSTEM_TEST_64)


REQUIRED_PACKAGES += system/library
