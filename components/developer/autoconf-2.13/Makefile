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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2014 David Mackay. All rights reserved.
#

BUILD_BITS = NO_ARCH

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		autoconf
COMPONENT_VERSION=	2.13
COMPONENT_REVISION =	2
COMPONENT_SUMMARY =	GNU autoconf utility, legacy version
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/autoconf/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f0611136bee505811e9ca11ca7ac188ef5323a8e2ef19cffd3edb3cf08fd791e
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/autoconf/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI =		developer/build/autoconf-213
COMPONENT_CLASSIFICATION =	Development/GNU
COMPONENT_LICENSE =		GPLv3, FDLv1.3
COMPONENT_LICENSE_FILE =	autoconf.license

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

# CONFIGURE_OPTIONS and CONFIGURE_ENV are reset because
# autoconf 2.13 doesn't like the defaults (in any case,
# autoconf is but a set of scripts and needn't be compiled)
CONFIGURE_OPTIONS   =		--prefix=$(USRDIR)
CONFIGURE_OPTIONS  +=		--srcdir=.
CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		--program-suffix=-2.13

CONFIGURE_ENV =

COMPONENT_TEST_ENV += F77="$(F77)"
COMPONENT_TEST_ENV += CC="$(CC)"
COMPONENT_TEST_ENV += CONFIG_SHELL="$(CONFIG_SHELL)"

COMPONENT_TEST_TRANSFORMS += '-e "/^make\[/d"'			# delete make logs
COMPONENT_TEST_TRANSFORMS += '-e "/^Test run by /d"'		# delete line with timestamp and username
COMPONENT_TEST_TRANSFORMS += '-e "/^Making a new site\.exp file\.\.\.$$/d"'	# delete optional line

# Auto-generated dependencies
REQUIRED_PACKAGES += developer/macro/gnu-m4
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/ksh93
