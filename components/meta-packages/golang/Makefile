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

COMPONENT_NAME =		golang
COMPONENT_VERSION =		1.20.4
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		The Go Programming Language
COMPONENT_PROJECT_URL =		https://go.dev/
COMPONENT_FMRI =		developer/golang
COMPONENT_CLASSIFICATION =	Development/Other Languages

include $(WS_MAKE_RULES)/common.mk

PKG_MACROS += GOV=$(shell echo $(COMPONENT_VERSION) | $(GSED) -e 's/\(\.[^.]*\)\..*/\1/' | tr -d .)

# Auto-generated dependencies
