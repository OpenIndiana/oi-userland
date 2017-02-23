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
#
# gnupth only delivers scripts that embed paths, so prefer 32-bit.
BUILD_BITS= 32_and_64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		pth
COMPONENT_VERSION=	2.0.7
COMPONENT_ARCHIVE_HASH=	\
    sha256:72353660c5a2caafd601b20e12e75d865fd88f6cf1a088b306a3963f0bc77232
COMPONENT_BUGDB=	library/pth
COMPONENT_ANITYA_ID=	3724

TPNO=			8899

include $(WS_MAKE_RULES)/gnu-component.mk

PATCH_LEVEL = 0

# Enable C99 mode + -Xc for its additional warnings.
studio_C99MODE = -Xc $(studio_C99_ENABLE)

# -xinline=%auto -- we like inlining where appropriate
CFLAGS += -xinline=%auto

# -xbuiltin=%none -- builtins have been known to be buggy
CFLAGS += -xbuiltin=%none

CFLAGS += $(CPP_LARGEFILES)
CFLAGS += $(XPG6MODE)
CFLAGS += $(CPP_POSIX)
CFLAGS += $(studio_PIC)

CPPFLAGS += $(CPP_LARGEFILES) $(CPP_POSIX)

LDFLAGS =	-lpthread -lposix4 -lrt

CONFIGURE_OPTIONS  +=	--localstatedir=$(VARDIR)
CONFIGURE_OPTIONS  +=	--with-pic

CONFIGURE_ENV += LD="$(CC) $(CFLAGS) $(LDFLAGS)"
CONFIGURE_ENV += CPP="$(CC) $(CPPFLAGS) $(CFLAGS) -E"
CONFIGURE_ENV += INSTALL="$(INSTALL)"

COMPONENT_TEST_MASTER =	$(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += \
	'-e "s|\(^Pth:\).*|\1|" '

REQUIRED_PACKAGES += shell/ksh93
