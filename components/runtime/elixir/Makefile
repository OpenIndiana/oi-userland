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
# Copyright (c) 2018, 2021, Oracle and/or its affiliates.
#

# Only executable scripts and bytecode files.
BUILD_BITS= NO_ARCH
BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		elixir
COMPONENT_VERSION=	1.20.4
COMPONENT_SUMMARY= Elixir is a functional programming language for building highly scalable and maintainable applications.
COMPONENT_PROJECT_URL=	https://elixir-lang.org/
COMPONENT_ARCHIVE_HASH=	sha256:2f87be1702583ecbeee82c0ad4d6353de96463cfa0fa6e7557e05f68d90da869
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= ${COMPONENT_SRC}.tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/elixir-lang/$(COMPONENT_NAME)/archive/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		runtime/elixir
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_LICENSE=	Apache-2.0
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Elixir does not like cloney, so a simple copy is used instead.
CLONEY_MODE = copy

# Required to avoid possible malfunctions.
COMPONENT_BUILD_ENV += LC_ALL=en_US.UTF-8
COMPONENT_BUILD_ENV += HOME=/tmp

COMPONENT_INSTALL_ENV += PREFIX=$(USRDIR)
COMPONENT_INSTALL_ENV += HOME=/tmp

COMPONENT_TEST_CMD = /usr/bin/gmake test
COMPONENT_TEST_ENV += LC_ALL=en_US.UTF-8
COMPONENT_TEST_ENV += HOME=/tmp

# Remove progress dots, make output, all empty lines, and git lines.
COMPONENT_TEST_TRANSFORMS += '-e "/\.\./d" -e "/^make/d" -e "/^$$/d" -e "/git_repo/d"'
# Ignore runtime statistics and random seeds used for the elixir testing.
COMPONENT_TEST_TRANSFORMS += '-e "/^Finished in/d" -e "/^Randomized with seed/d" -e "/^hint:/d" '
# Ignore the spurious error message (see issue #8183 on elixir github).
COMPONENT_TEST_TRANSFORMS += '-e "/resides in sticky dir/d" -e "/^gmake/d"'
# the hint isn't printed when gmake test is run the second time
COMPONENT_TEST_TRANSFORMS += '-e "/^hint/d"'
# there's a difference between i386 and sparc
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH).master

# Manually added build dependencies
REQUIRED_PACKAGES += runtime/erlang

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/ksh93
