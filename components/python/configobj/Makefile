#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Alexander Pyhalov
#

BUILD_STYLE= setup.py
BUILD_BITS= NO_ARCH
include ../../../make-rules/shared-macros.mk

PATH=/usr/bin:/usr/gnu/bin:/usr/sbin

COMPONENT_NAME=		configobj
COMPONENT_VERSION=	5.0.6
COMPONENT_REVISION=	2
COMPONENT_PROJECT_URL=	https://github.com/DiffSK/configobj
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:a2f5650770e1c87fb335af19a9b7eb73fc05ccf22144eb68db7d00cd2bcb0902
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/source/c/configobj/$(COMPONENT_ARCHIVE)

PYTHON_VERSIONS=	2.7 3.5

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk
