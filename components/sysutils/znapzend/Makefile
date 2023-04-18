#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016-2018 Jim Klimov
# Copyright 2021 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
#

BUILD_BITS = NO_ARCH

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		znapzend
COMPONENT_VERSION =		0.21.2
COMPONENT_SUMMARY =		zfs backup with remote capabilities and mbuffer integration
COMPONENT_DESCRIPTION =		ZnapZend is a ZFS centric backup tool. It relies on snapshot,\
 send and receive to do its work. It has the built-in ability to manage both local\
 snapshots as well as remote copies by thining them out as time progresses.\
 The ZnapZend configuration is stored as properties in the ZFS filesystem itself,\
 see znapzendzetup to get started.
COMPONENT_SRC =			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:c3753d663c2f4d87f87da0191441c5cd2cb32aca7ded913d97565472413e3823
COMPONENT_ARCHIVE_URL =		\
	https://github.com/oetiker/$(COMPONENT_NAME)/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL =		https://github.com/oetiker/$(COMPONENT_NAME)
COMPONENT_FMRI =		backup/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION =	Applications/System Utilities
COMPONENT_LICENSE =		GPL-3.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_LIBDIR.32 = $(CONFIGURE_PREFIX)/lib/znapzend
CONFIGURE_OPTIONS += --enable-svcinstall=/lib/svc/manifest/system
CONFIGURE_OPTIONS += --with-svcname-smf=system/filesystem/zfs/znapzend

# Force SUBDIRS=lib to skip thirdparty subdir.  We do not need thirdparty perl
# modules because we use system provided library/perl-5/* packages to satisfy
# our dependencies.
COMPONENT_BUILD_ARGS += SUBDIRS=lib
COMPONENT_INSTALL_ARGS += SUBDIRS=lib
COMPONENT_TEST_ARGS += SUBDIRS=lib

COMPONENT_TEST_TRANSFORMS += -n
COMPONENT_TEST_TRANSFORMS += "-e '/\<ok\>/p'"

# We are not able to detect these dependencies automatically.
# The list is based on $(SOURCE_DIR)/cpanfile.
REQUIRED_PACKAGES += library/perl-5/mojolicious
REQUIRED_PACKAGES += library/perl-5/mojo-log-clearable

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += runtime/perl
