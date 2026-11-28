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
# Copyright 2026 isoriano1968
#

BUILD_STYLE=		meson

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		showtime
HUMAN_VERSION=		48.1
COMPONENT_SUMMARY=	Showtime - GNOME video player
COMPONENT_ARCHIVE_HASH=	\
	sha256:1b22202dbe540440797d5a065030c29c242b210e3d4ec5ceb42e320ecc544ab9
COMPONENT_FMRI=		media/showtime
COMPONENT_CLASSIFICATION=	Applications/Sound and Video
COMPONENT_LICENSE=	GPL-3.0-or-later
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is expected
PATH=			$(PATH.gnu)

# OI's PyGObject is for Python 3.9
PYTHON_SCRIPTS +=	usr/bin/showtime

CONFIGURE_OPTIONS +=	-Dpython.purelibdir=$(PYTHON_VENDOR_PACKAGES)

# Do not create gpatch backup files because they pollute the generated manifest
GPATCH_BACKUP =

# meson installs the modules without byte-compiling them
COMPONENT_POST_INSTALL_ACTION += \
	$(PYTHON) -m compileall -q -s $(PROTO_DIR) -p / $(PROTOPYTHONVENDORDIR)/showtime;

# the blueprint UI files
REQUIRED_PACKAGES += developer/blueprint-compiler

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/pygobject
REQUIRED_PACKAGES.python += runtime/python
