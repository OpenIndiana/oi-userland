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
#   $WS_TOOLS/python-integrate-project -d multimedia/yt-dlp yt-dlp
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		yt-dlp
HUMAN_VERSION =			2023.11.16
COMPONENT_SUMMARY =		yt-dlp - A youtube-dl fork with additional features and patches
COMPONENT_PROJECT_URL =		https://github.com/yt-dlp/yt-dlp
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/93/f0/8d894dd24447945269d123f6a061520103fb790211c6846418c6ee1065ff/yt-dlp-2023.11.16.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:f0ccdaf12e08b15902601a4671c7ab12906d7b11de3ae75fa6506811c24ec5da
COMPONENT_LICENSE =		Unlicense
COMPONENT_LICENSE_FILE =	LICENSE

COMPONENT_FMRI =		multimedia/yt-dlp
COMPONENT_CLASSIFICATION =	Applications/Sound and Video

# This is a standalone application.  Since no other Python project depends on
# it we just provide single unversioned package.
SINGLE_PYTHON_VERSION = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/brotli
PYTHON_REQUIRED_PACKAGES += library/python/certifi
PYTHON_REQUIRED_PACKAGES += library/python/mutagen
PYTHON_REQUIRED_PACKAGES += library/python/pycryptodomex
PYTHON_REQUIRED_PACKAGES += library/python/requests
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/urllib3
PYTHON_REQUIRED_PACKAGES += library/python/websockets
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
