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
# Copyright 2024 Marcel Telka
#

BUILD_STYLE = pkg

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		automake
HUMAN_VERSION =			1.16
# When we upgrade to new major version (e.g. 1.17) the COMPONENT_VERSION should
# be removed.
COMPONENT_VERSION =		1.16.5
COMPONENT_REVISION=		2
COMPONENT_SUMMARY =		A Makefile generator
COMPONENT_PROJECT_URL =		https://www.gnu.org/software/automake/
COMPONENT_FMRI =		developer/build/automake
COMPONENT_CLASSIFICATION =	Development/GNU

include $(WS_MAKE_RULES)/common.mk

PKG_MACROS += AMV=$(subst .,,$(HUMAN_VERSION))

# Auto-generated dependencies
