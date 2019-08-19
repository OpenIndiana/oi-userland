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
# Copyright 2019 Michal Nowak
#

BUILD_STYLE=		justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		splix
COMPONENT_VERSION=	2.0.0
COMPONENT_SUMMARY=	Driver for QPDL/SPL2 printers (Samsung and Xerox printers)
COMPONENT_PROJECT_URL=	http://splix.sourceforge.net
COMPONENT_FMRI=		print/splix
COMPONENT_CLASSIFICATION=	System/Printing
SVN_HASH=		sha256:8bf5043925c895348b9152568bcbc7a72794456bb75af2539c09f5e849b6c419
COMPONENT_LICENSE=	GPLv2.0
COMPONENT_LICENSE_FILE=	splix-315/splix/COPYING

SVN_REPO=		https://svn.code.sf.net/p/splix/code/
SVN_REV=		315

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_BUILD_ENV = \
	CXXFLAGS="$(CXXFLAGS) -fno-strict-aliasing" \
	rastertoqpdl_CXXFLAGS="$(CXXFLAGS)" \
	pstoqpdl_CXXFLAGS="$(CXXFLAGS)"

COMPONENT_PRE_BUILD_ACTION = \
	cd $(@D)/splix; \
	$(MV) *.ppd ppd/ ;

COMPONENT_BUILD_ACTION = \
	cd $(@D)/splix; $(ENV) $(COMPONENT_BUILD_ENV) \
	$(GMAKE) $(COMPONENT_BUILD_ARGS) V=1 DISABLE_JBIG=1

COMPONENT_INSTALL_ACTION = \
	cd $(@D)/splix; \
	$(GMAKE) $(COMPONENT_INSTALL_ARGS) $(COMPONENT_INSTALL_TARGETS)

REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
# Auto-generated dependencies
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
