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
# Copyright 2023 erwinlem
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		moosefs
COMPONENT_VERSION=	3.0.116
COMPONENT_SUMMARY=	Open Source, Petabyte, Fault-Tolerant, Highly Performing, Scalable Network Distributed File System (Software-Defined Storage)
COMPONENT_PROJECT_URL=	https://moosefs.com/
COMPONENT_FMRI=		network/${COMPONENT_NAME}
COMPONENT_CLASSIFICATION=System/File System
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://codeload.github.com/moosefs/moosefs/tar.gz/refs/tags/v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_HASH=	sha256:3b70dd4551db282e6e9b9c8ecdb5f2ec5ed98b644dc06e2006cd0deaa84f6c9c
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=$(NO_TESTS) # if no testsuite enabled
include $(WS_MAKE_RULES)/common.mk

# needs a buildnumer
COMPONENT_PRE_CONFIGURE_ACTION	+= (echo "0" > $(@D)/buildno.txt) ;

# we need to generate the makefiles because we patches Makefile.am 
COMPONENT_PREP_ACTION= ( cd $(@D) && \
		       aclocal -I. && \
		       automake -a -f -c && \
		       autoconf )

# pkgdepend does not like only the major version, replace with a specific python versien 
COMPONENT_POST_INSTALL_ACTION += $(GSED) -i -e 's?env python3?python$(PYTHON_VERSION)?' $(PROTOUSRBINDIR)/mfscli ;
COMPONENT_POST_INSTALL_ACTION += $(GSED) -i -e 's?env python3?python$(PYTHON_VERSION)?' $(PROTOUSRSBINDIR)/mfscgiserv ;
COMPONENT_POST_INSTALL_ACTION += $(GSED) -i -e 's?env python3?python$(PYTHON_VERSION)?' $(PROTOUSRSHAREDIR)/mfscgi/mfs.cgi ;

CONFIGURE_OPTIONS+= --localstatedir=/var
CONFIGURE_OPTIONS+= --sysconfdir=/etc

# Build dependencies

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libfuse
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libpcap
REQUIRED_PACKAGES += system/library/math
