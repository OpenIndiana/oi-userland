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
#   $WS_TOOLS/python-integrate-project pyperclip
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pyperclip
HUMAN_VERSION =			1.9.0
COMPONENT_SUMMARY =		A cross-platform clipboard module for Python. (Only handles plain text for now.)
COMPONENT_PROJECT_URL =		https://github.com/asweigart/pyperclip
COMPONENT_ARCHIVE_HASH =	\
	sha256:b7de0142ddc81bfc5c7507eea19da920b92252b548b96186caf94a5e2527d310
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Testing needs an X server
TEST_REQUIRED_PACKAGES += x11/server/xvfb
COMPONENT_PRE_TEST_ACTION += /usr/bin/Xvfb :0 >/dev/null 2>&1 &
COMPONENT_TEST_ENV += DISPLAY=:0
COMPONENT_POST_TEST_ACTION += /usr/bin/pkill -x Xvfb ;

# Testing needs the XDG_RUNTIME_DIR variable pointing to own runtime directory
# with permissions 0700
COMPONENT_PRE_TEST_ACTION += $(MKDIR) $(COMPONENT_TEST_BUILD_DIR)/runtime ;
COMPONENT_PRE_TEST_ACTION += $(CHMOD) 0700 $(COMPONENT_TEST_BUILD_DIR)/runtime ;
COMPONENT_TEST_ENV += XDG_RUNTIME_DIR=$(COMPONENT_TEST_BUILD_DIR)/runtime
COMPONENT_POST_TEST_ACTION += $(RM) -r $(COMPONENT_TEST_BUILD_DIR)/runtime ;

# https://github.com/asweigart/pyperclip/issues/246
COMPONENT_TEST_TRANSFORMS += "-e 's/TEST//g'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
