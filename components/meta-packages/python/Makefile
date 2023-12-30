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
# Copyright 2023 Marcel Telka
#

BUILD_STYLE = pkg

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		python
COMPONENT_VERSION =		$(PYTHON_VERSION)
COMPONENT_SUMMARY =		Python - Interpreted, interactive, object-oriented programming language
COMPONENT_PROJECT_URL =		https://www.python.org/
COMPONENT_FMRI =		runtime/python
COMPONENT_CLASSIFICATION =	Development/Python

# This needs to be done before the common.mk include because here we still do
# have the full list of Python versions in PYTHON_VERSIONS.
ifeq ($(PYTHON_VERSION),$(lastword $(PYTHON_VERSIONS)))
PKG_MACROS += VENDOR_MEDIATOR=\#
else
PKG_MACROS += VENDOR_MEDIATOR=
endif

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
