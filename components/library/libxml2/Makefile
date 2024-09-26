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
# Copyright (c) 2013  Erol Zavidic. All rights reserved.
# Copyright (c) 2022  Friedrich Kink. All rights reserved.
#

BUILD_BITS= 64_and_32
USE_COMMON_TEST_MASTER=	no
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libxml2
HUMAN_VERSION=		2.13.4
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=	Libxml2 is the XML C parser and toolkit developed for the Gnome project
COMPONENT_ARCHIVE_HASH=	sha256:65d042e1c8010243e617efb02afda20b85c2160acdbfbcb5b26b80cec6515650
COMPONENT_FMRI=		library/libxml2
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	Copyright

COMPONENT_FMRI.libxml2-32=	$(COMPONENT_FMRI)/32

# W3C XML Conformance Test Suites
COMPONENT_ARCHIVE_1= xmlts20130923.tar.gz
COMPONENT_ARCHIVE_HASH_1= sha256:9b61db9f5dbffa545f4b8d78422167083a8568c59bd1129f94138f936cf6fc1f
COMPONENT_ARCHIVE_URL_1= https://www.w3.org/XML/Test/$(COMPONENT_ARCHIVE_1)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

CFLAGS += $(CPP_LARGEFILES)
CFLAGS += $(XPG7MODE)

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --localstatedir="$(VARDIR)"
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --with-icu
CONFIGURE_OPTIONS += --with-ftp
CONFIGURE_OPTIONS += --with-xptr-locs
CONFIGURE_OPTIONS += --with-history
CONFIGURE_OPTIONS += --with-legacy
CONFIGURE_OPTIONS.32 += --with-python=no

CONFIGURE_ENV.64     += PYTHON=$(PYTHON)
CONFIGURE_ENV.64     += am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_ENV.64     += am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)

COMPONENT_PREP_ACTION += (cd $(@D) ; cp ../mapfile libxml2.syms ; PATH="$(PATH)" autoreconf -if )

# After we have built/installed libxml2, build/install the python
# support for python (only 64 bit is available)
COMPONENT_POST_INSTALL_ACTION.64 = ( \
	cd $(@D)/python; \
	$(GMAKE) pythondir=$(PYTHON_VENDOR_PACKAGES) \
		pyexecdir=$(PYTHON_VENDOR_PACKAGES) \
		DESTDIR=$(PROTO_DIR) \
		install ; \
	$(MV) $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES)/libxml2mod.so $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES)/libxml2mod.cpython-$(subst .,,$(PYTHON_VERSION)).so; \
	$(PYTHON) -m compileall $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES); \
);

# It's nice to test also python modules (LC_ALL is set to avoid test failure).
COMPONENT_POST_TEST_ACTION.64 = \
    cd $(@D)/python; \
    LC_ALL=en_US.UTF-8 $(GMAKE) $(COMPONENT_TEST_ARGS) check

COMPONENT_PRE_TEST_ACTION.64 += \
    (cd $(@D) ; gtar xf $(USERLAND_ARCHIVES)/$(COMPONENT_ARCHIVE_1));

COMPONENT_TEST_TRANSFORMS = \
	'-e "s/^make\[.*$$/[EnD]/" ' \
	'-e "/^\#\# XML regression tests/,/^\[EnD\]/p" ' \
	'-e "/^\#\# running Python regression tests/,/^\[EnD\]/p" ' \
	'-e "/.*/d" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(ICU_LIBRARY_PKG)
REQUIRED_PACKAGES += $(ICU_LIBRARY_PKG)/32
REQUIRED_PACKAGES += $(READLINE_PKG)
REQUIRED_PACKAGES += $(READLINE_PKG)/32
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
