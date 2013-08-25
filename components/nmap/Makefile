
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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=         nmap
COMPONENT_VERSION=      6.25
COMPONENT_PROJECT_URL=	http://nmap.org/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH= \
    sha256:42c54fd5cc5f05e5df909757d62307102a8ff1dfaf5c2626b1cb5f2ecd009e57
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)dist/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/nmap

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# Can't use the Studio compilers as they don't support the GNU 
# __attribute__ extension
COMPILER =	gcc

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D) && \
	  cd $(@D)/libdnet-stripped && autoconf )

CONFIGURE_OPTIONS  +=   CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS  +=   LIBS="-lsocket -lnsl"
CONFIGURE_OPTIONS  +=   PYTHON="$(PYTHON)"
CONFIGURE_OPTIONS  +=   --srcdir=$(BUILD_DIR_32)
CONFIGURE_OPTIONS  +=   --localstatedir=/var 
CONFIGURE_OPTIONS  +=   --without-localdirs 
CONFIGURE_OPTIONS  +=   --with-zenmap 
CONFIGURE_OPTIONS  +=   --with-openssl
CONFIGURE_OPTIONS  +=   --with-libpcap
CONFIGURE_OPTIONS  +=   --with-libpcre
CONFIGURE_OPTIONS  +=   --with-liblua 
CONFIGURE_OPTIONS  +=   --with-ncat 
CONFIGURE_OPTIONS  +=   --with-ndiff

# pkgdepend doesn't like the first line of a Python script to be:
# '#!/usr/bin/env python' so turn it into '#!/usr/bin/python2.6'
COMPONENT_POST_INSTALL_ACTION += \
        $(GSED) -i -e 's?env python?python2.6?' \
                $(PROTOUSRBINDIR)/uninstall_zenmap

# common targets
build:		$(BUILD_32)
		
install:	$(INSTALL_32) 

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
