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
# Copyright 2022 Niklas Poslovski
#

include $(WS_MAKE_RULES)/makemaker.mk

# Configure
CONFIGURE_SCRIPT = Build.PL
CONFIGURE_OPTIONS += --installdirs=vendor

# Build
COMPONENT_BUILD_CMD = ./Build

# Install
COMPONENT_INSTALL_CMD = ./Build
COMPONENT_INSTALL_ARGS =
COMPONENT_INSTALL_TARGETS = install
COMPONENT_INSTALL_TARGETS += --destdir="$(PROTO_DIR)"

# Test
COMPONENT_TEST_CMD = ./Build

# Workaround for https://github.com/Perl-Toolchain-Gang/Module-Build/issues/91.
# Without the workaround we would need to add library/perl-5/module-build as a
# required package manually to all Perl components with the modulebuild build
# style.  We do not need the library/perl-5/module-build package to bootstrap
# the Module::Build module itself.
ifneq ($(strip $(COMPONENT_PERL_MODULE)),Module::Build)
USERLAND_REQUIRED_PACKAGES.perl += library/perl-5/module-build
endif
