#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2020 Nona Hansel
#

BUILD_BITS=		NO_ARCH
BUILD_STYLE=		setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		youtube-dl
COMPONENT_VERSION=	2020.3.8
COMPONENT_TMP_VERSION=	2020.03.08
COMPONENT_SUMMARY=	Command-line program to download videos from YouTube.com and other video sites
COMPONENT_PROJECT_URL=	https://youtube-dl.org/
COMPONENT_FMRI=		multimedia/youtube-dl	
COMPONENT_CLASSIFICATION= Applications/Sound and Video
COMPONENT_SRC=          $(COMPONENT_NAME)
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_TMP_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/downloads/latest/$(COMPONENT_ARCHIVE)	
COMPONENT_ARCHIVE_HASH= \
	sha256:76114c82015386eda24fe110e2c24a35f0551ce298b915e1c48c2acb495073f5
COMPONENT_LICENSE=	Unlicense
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET=		$(NO_TESTS)
PYTHON_VERSIONS=	3.5

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += runtime/python-35
