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
# Copyright 2018 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		contextlib2
COMPONENT_VERSION=	0.5.5
COMPONEENT_REVISION=	2
COMPONENT_SUMMARY=	'A backport of the standard library contextlib module to earlier Python versions'
COMPONENT_PROJECT_URL=	https://github.com/cherrypy/contextlib2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:509f9419ee91cdd00ba34443217d5ca51f5a364a404e1dce9e8979cea969ca48
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	library/python/contextlib2
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	PSFv2
COMPONENT_LICENSE_FILE=	LICENSE.txt

# contextlib2 isn't necessary on newer versions of python 3, but some things
# in their current versions use it rather than the builtin 'contextlib' anyway
PYTHON_VERSIONS=	$(PYTHON_VERSIONS_ALL)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:           $(NO_TEST)
