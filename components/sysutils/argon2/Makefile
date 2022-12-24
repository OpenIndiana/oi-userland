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
# Copyright 2022 Carsten Grzemba
#

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		argon2
COMPONENT_VERSION=	20190702
COMPONENT_REVISION=	1
COMPONENT_SUMMARY= 	Argon2 is a password-hashing function that can be used to hash passwords for credential storage, key derivation, or other applications
COMPONENT_PROJECT_URL=	https://github.com/P-H-C/phc-winner-argon2
COMPONENT_SRC=		phc-winner-$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/P-H-C/phc-winner-argon2/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:daf972a89577f8772602bf2eb38b6a3dd3d922bf5724d45e7f9589b5e830442c
COMPONENT_FMRI= security/argon2
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_LICENSE=	Apache2
COMPONENT_LICENSE_FILE=LICENSE

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_TARGETS= test

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
