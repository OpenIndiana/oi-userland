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
#   $WS_TOOLS/python-integrate-project -d multimedia/youtube-dl youtube_dl
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		youtube_dl
HUMAN_VERSION =			2021.12.17
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		youtube_dl - YouTube video downloader
COMPONENT_PROJECT_URL =		https://github.com/ytdl-org/youtube-dl
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/01/4f/ab0d0806f4d818168d0ec833df14078c9d1ddddb5c42fa7bfb6f15ecbfa7/youtube_dl-2021.12.17.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:bc59e86c5d15d887ac590454511f08ce2c47698d5a82c27bfe27b5d814bbaed2
COMPONENT_LICENSE =		Unlicense
COMPONENT_LICENSE_FILE =	LICENSE

COMPONENT_FMRI =		multimedia/youtube-dl
COMPONENT_CLASSIFICATION =	Applications/Sound and Video

# This is a standalone application.  Since no other Python project depends on
# it we just provide single unversioned package.
SINGLE_PYTHON_VERSION = yes

# Tests needs internet access
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
