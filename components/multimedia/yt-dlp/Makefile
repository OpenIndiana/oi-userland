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
# This file was automatically generated using the following command:
#   $WS_TOOLS/python-integrate-project -d multimedia/yt-dlp yt_dlp
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		yt_dlp
HUMAN_VERSION =			2025.9.26
COMPONENT_SUMMARY =		A feature-rich command-line audio/video downloader
COMPONENT_ARCHIVE_HASH =	\
	sha256:c148ae8233ac4ce6c5fbf6f70fcc390f13a00f59da3776d373cf88c5370bda86
COMPONENT_LICENSE =		Unlicense
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

COMPONENT_FMRI =		multimedia/yt-dlp
COMPONENT_CLASSIFICATION =	Applications/Sound and Video

# This is a standalone application.  Since no other Python project depends on
# it we just provide single unversioned package.
SINGLE_PYTHON_VERSION = yes

include $(WS_MAKE_RULES)/common.mk

#
# Add optional runtime dependencies.  Technically, we do not need all of them
# because only subset is strongly recommended but it is easier to add all of
# them than to maintain the list of the strongly recommended.
#
# See also https://github.com/yt-dlp/yt-dlp/pull/11255
#
COMPONENT_POST_INSTALL_ACTION += \
	PYTHONPATH=$(PROTO_DIR)/$(PYTHON_DIR)/site-packages:$(PROTO_DIR)/$(PYTHON_LIB) \
		$(PYTHON) $(WS_TOOLS)/python-requires $(COMPONENT_NAME) default >> $(@D)/.depend-runtime ;

# avoid downloads during testing
PYTEST_ADDOPTS += -m 'not download'

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/brotli
REQUIRED_PACKAGES.python += library/python/certifi
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += library/python/mutagen
REQUIRED_PACKAGES.python += library/python/pycryptodomex
REQUIRED_PACKAGES.python += library/python/requests
REQUIRED_PACKAGES.python += library/python/urllib3
REQUIRED_PACKAGES.python += library/python/websockets
REQUIRED_PACKAGES.python += runtime/python
