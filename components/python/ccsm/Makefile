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
# Copyright 2018 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ccsm
COMPONENT_VERSION=	0.8.14
COMPONENT_PROJECT_URL=	http://www.northfield.ws
COMPONENT_SUMMARY=	ccsm settings manager for the CompizConfig system
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f2f23068706f52b8d9d0a06520b09070cfc9b5e5bbac82b71ee7f30ce39f872c
COMPONENT_ARCHIVE_URL=	http://www.northfield.ws/projects/compiz/releases/$(COMPONENT_VERSION)/$(COMPONENT_SRC).tar.xz
COMPONENT_FMRI=		desktop/compiz/ccsm

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

# compizconfig-python is Python 2.7 only
PYTHON_VERSIONS = 2.7

PATH=$(PATH.gnu)

COMPONENT_BUILD_ARGS += --prefix=/usr

COMPONENT_INSTALL_ARGS =	--prefix=/usr
COMPONENT_INSTALL_ARGS +=	--root=$(PROTO_DIR)
COMPONENT_INSTALL_ARGS +=	--install-lib=$(PYTHON_LIB)
COMPONENT_INSTALL_ARGS +=	--install-purelib=$(PYTHON_LIB)
COMPONENT_INSTALL_ARGS +=	--install-platlib=$(PYTHON_LIB)
COMPONENT_INSTALL_ARGS +=	--force

COMPONENT_POST_BUILD_ACTION = \
		(cd $(SOURCE_DIR);\
		$(GSED) -i -e '1 i\#!$(PYTHON)' ccm/*.py{,.in} )

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += library/python/pygtk2-27
REQUIRED_PACKAGES += library/python/python-dbus-27
REQUIRED_PACKAGES += library/python/python-sexy-27

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/pycairo-27
REQUIRED_PACKAGES += library/python/pygobject-3-27
REQUIRED_PACKAGES += library/python/python-compizconfig-27
REQUIRED_PACKAGES += runtime/python-27
