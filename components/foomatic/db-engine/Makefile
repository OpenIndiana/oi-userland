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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		foomatic-db-engine
COMPONENT_VERSION=	3.0-20080903
COMPONENT_REVISION=	1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:668f2020eb136359523090cc17151e6aad0c56bce0e4ae91217a9eba19eec917
COMPONENT_ARCHIVE_URL=	http://dlc.openindiana.org/oi-build/source-archives/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.linuxfoundation.org/collaborate/workgroups/openprinting/database/foomatic/
COMPONENT_BUGDB=	utility/foomatic

include ../../../make-rules/prep.mk
include ../../../make-rules/configure.mk
include ../../../make-rules/ips.mk

CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)" 
CONFIGURE_OPTIONS +=	PERL=$(PERL)
CONFIGURE_OPTIONS +=	FILEUTIL=/bin/true
CONFIGURE_OPTIONS +=    --sysconfdir=$(ETCDIR)/gnu

# the build system does not support building outside of the source tree
COMPONENT_PRE_CONFIGURE_ACTION = $(CLONEY) $(SOURCE_DIR) $(@D) ;

# setup perl build
COMPONENT_PRE_CONFIGURE_ACTION += cd $(@D)/lib ; $(PERL) Makefile.PL

# install perl modules
COMPONENT_PRE_INSTALL_ACTION = \
 ( cd $(@D)/lib ; $(GMAKE) install_vendor DESTDIR=$(PROTO_DIR) )

# the perl .packlist contains the path to the file as built rather than
# as installed. Fix to be installed path, ie remove PROTO_DIR.
VENDORARCH= $(shell $(PERL) -e 'use Config; print $$Config{vendorarch}')
PACKLIST=   $(VENDORARCH)/auto/Foomatic/.packlist
COMPONENT_POST_INSTALL_ACTION = \
 sed -e "s/$(subst /,\\/,$(PROTO_DIR))//g" $(PROTO_DIR)/$(PACKLIST) \
     >> $(PROTO_DIR)/$(PACKLIST).fixed ; \
 $(MV) $(PROTO_DIR)/$(PACKLIST).fixed $(PROTO_DIR)/$(PACKLIST)


# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
