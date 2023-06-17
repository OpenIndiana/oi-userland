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
# Copyright 2020-2021 Nona Hansel
# Copyright 2023 Niklas Poslovski
#

BUILD_BITS=		NO_ARCH
BUILD_STYLE=		setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		youtube-dl
COMPONENT_VERSION=	2021.12.17
#COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Command-line program to download videos from YouTube.com and other video sites
COMPONENT_PROJECT_URL=	https://youtube-dl.org/
COMPONENT_FMRI=		multimedia/youtube-dl	
COMPONENT_CLASSIFICATION= Applications/Sound and Video
COMPONENT_SRC=          $(COMPONENT_NAME)
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/downloads/latest/$(COMPONENT_ARCHIVE)	
COMPONENT_ARCHIVE_HASH= \
	sha256:9f3b99c8b778455165b4525f21505e86c7ff565f3ac319e19733d810194135df
COMPONENT_LICENSE=	Unlicense
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET=		$(NO_TESTS)
SINGLE_PYTHON_VERSION=	yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
