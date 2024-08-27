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
# IPS package Copyright 2024 David Stes
#
# name and version of package same as in Debian Linux 
#
# J. E. Cremona Elliptic Curve Data for PARI/GP
# =============================================
#
# This is the PARI/GP version of J. E. Cremona Elliptic Curve Data
# <https://github.com/JohnCremona/ecdata/>
#
# This package contains elliptic curves defined over the rationals representing
# all isogeny classes for all conductor less than 500000. Theses data are needed
# by ellsearch, ellidentify and ellgenerators and require PARI/GP 2.2.11 and up.
#
# Note that the numbering of curves inside isogeny classes follows the update
# from 20/08/2019. See
# https://raw.githubusercontent.com/JohnCremona/ecdata/master/doc/release_notes.md
#
# See <http://pari.math.u-bordeaux.fr/packages.html> for other PARI/GP packages.
#
# The data is available under TheArtistic License 2.0:
# see the file LICENSE for details.
#

BUILD_STYLE= archive
BUILD_BITS = NO_ARCH

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pari-elldata	
COMPONENT_SRC=		data
COMPONENT_VERSION=	0.20210301
COMPONENT_SUMMARY=	PARI/GP Computer Algebra System elliptic curves (elldata) 
COMPONENT_PROJECT_URL=	https://pari.math.u-bordeaux.fr
COMPONENT_FMRI=		library/math/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_ARCHIVE=	elldata.tgz
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/pub/pari/packages/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
   sha256:dd551e64932d4ab27b3f2b2d1da871c2353672fc1a74705c52e3c0de84bd0cf6
COMPONENT_LICENSE=     	The Artistic License 2.0
COMPONENT_LICENSE_FILE=	LICENSE

USRSHAREPARI=/usr/share/pari
BUILD_TARGET = $(BUILD_$(MK_BITS))
INSTALL_TARGET = $(INSTALL_$(MK_BITS))

include $(WS_MAKE_RULES)/common.mk

$(BUILD_$(MK_BITS)): $(SOURCE_DIR)/.prep
	$(MKDIR) $(@D)
	$(TOUCH) $@

$(INSTALL_$(MK_BITS)): $(BUILD_$(MK_BITS))
	$(MKDIR) $(PROTO_DIR)/$(USRSHAREPARI)
	$(GTAR) cpf - -C $(SOURCE_DIR) --exclude './.*' . | $(GTAR) xpvf - -C $(PROTO_DIR)/$(USRSHAREPARI)
	$(TOUCH) $@

clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)

# Auto-generated dependencies
