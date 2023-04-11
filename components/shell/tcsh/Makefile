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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tcsh
COMPONENT_VERSION=	6.24.8
HUMAN_VERSION=		6.24.08
COMPONENT_SUMMARY=	Tenex C-shell (tcsh)
COMPONENT_DESCRIPTION=	C shell with file name completion and command line editing
COMPONENT_PROJECT_URL=	https://github.com/tcsh-org/tcsh
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:d07f1bc164faa6faf63dcf4f30d73eb8149df6de6f9ebfe7b47256234a6366ab
COMPONENT_ARCHIVE_URL=	https://astron.com/pub/tcsh/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		shell/tcsh
COMPONENT_CLASSIFICATION= System/Shells
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	Copyright

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_TEST_TRANSFORMS = \
	' -n "/^\s*[0-9]/p" '

# configure needs gencat
REQUIRED_PACKAGES += text/locale

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
