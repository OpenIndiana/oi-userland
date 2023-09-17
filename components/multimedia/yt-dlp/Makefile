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
# Copyright 2023 Niklas Poslovski
#

BUILD_BITS=		NO_ARCH
BUILD_STYLE=		setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		yt-dlp
COMPONENT_VERSION=	2023.7.6
HUMAN_VERSION=		2023.07.06
COMPONENT_SUMMARY=	A youtube-dl fork with additional features and fixes
COMPONENT_PROJECT_URL=	https://github.com/yt-dlp/yt-dlp
COMPONENT_FMRI=		multimedia/yt-dlp
COMPONENT_CLASSIFICATION= Applications/Sound and Video
COMPONENT_SRC=          $(COMPONENT_NAME)
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/yt-dlp/yt-dlp/releases/download/$(HUMAN_VERSION)/$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:6d2115b84b6c11867f92cf4c23705b536bfa0ba9d538b1885f52da6756f8c980
COMPONENT_LICENSE=	Unlicense
COMPONENT_LICENSE_FILE=	LICENSE

SINGLE_PYTHON_VERSION=	yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/certifi
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/pycryptodomex
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
