#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright Andreas Wacknitz
#

BUILD_STYLE = archive 
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=  	intel-one-mono
COMPONENT_VERSION=	1.0.0
COMPONENT_SUMMARY=	An expressive monospaced font family that’s built with clarity, legibility, and the needs of developers in mind
COMPONENT_SRC=  	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(HUMAN_VERSION).zip
COMPONENT_PROJECT_URL=	https://github.com/intel/intel-one-mono
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/releases/download/V$(COMPONENT_VERSION)/ttf.zip
COMPONENT_ARCHIVE_HASH=	sha256:b247044d03a788a08785f6a3f5128e1f1bc32a60bddc08fd72e74b1bb2bcddb1
COMPONENT_LICENSE=      SIL OPEN FONT LICENSE Version 1.1

FONT_TYPE = TTF

include $(WS_MAKE_RULES)/font.mk

UNPACK_ARGS += -r $(COMPONENT_SRC)

COMPONENT_FONT_SRC_DIR = ttf
COMPONENT_FONT_FILES  += *.ttf

COMPONENT_FONTCONF_SRC_DIR =
COMPONENT_FONTCONF_FILES   =

# Auto-generated dependencies
