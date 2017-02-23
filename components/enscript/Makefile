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
# Copyright (c) 2013, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		enscript
COMPONENT_VERSION=	1.6.6
COMPONENT_ARCHIVE_HASH=	\
    sha256:6d56bada6934d055b34b6c90399aa85975e66457ac5bf513427ae7fc77f5c0bb
COMPONENT_ANITYA_ID=	699

# Ruby enscript support
COMPONENT_ARCHIVE_1=    ruby-enscript.tar.gz
COMPONENT_ARCHIVE_HASH_1=       \
    sha256:29c87c4cd5d36b221fd50ad0b2e35a2cc0e1422519bb7f41d400c61db117cff7
COMPONENT_ARCHIVE_URL_1= http://neugierig.org/software/ruby/ruby-enscript.tar.gz

# PHP enscript support
COMPONENT_ARCHIVE_2=    php.st
COMPONENT_ARCHIVE_HASH_2=	\
    sha256:3224ca9e1a9707f5a1dba2688a639c13494a805642f102279b3431214801814c
COMPONENT_ARCHIVE_URL_2= http://ez.lbm-services.de/content/download/1631/7197/file/php.st

TPNO=			29959

include $(WS_MAKE_RULES)/gnu-component.mk

# Get just the ruby enscript support file out of the downloaded tarball, and
# move ruby.st and php.st into the correct directory for "gmake install".
COMPONENT_PREP_ACTION = \
	/usr/bin/tar xvf $(COMPONENT_ARCHIVE_1) ruby.st ; \
	$(MV) php.st ruby.st $(SOURCE_DIR)/states/hl ;

# There are patches that change a Makefile.am and configure.in
# This version of enscript needs an older automake to reconfigure.  When
# we upgrade enscript, we can use the newer version.
COMPONENT_PREP_ACTION +=(cd $(@D); ACLOCAL=aclocal-1.11 AUTOMAKE=automake-1.11 \
				   autoreconf -fiv);

# Needed so that enscript can find the enscript.cfg file.
CONFIGURE_OPTIONS +=    --sysconfdir=$(ETCDIR)

CONFIGURE_OPTIONS +=	--with-media=Letter

# Needed so that the StatesBinary parameter in /etc/enscript.cfg 
# will be /usr/bin/states on sparc.
CONFIGURE_OPTIONS +=	--bindir=/usr/bin

COMPONENT_POST_INSTALL_ACTION = \
	$(LN) $(PROTOUSRBINDIR)/enscript \
		$(PROTOUSRBINDIR)/nenscript

# Adjust '#!/usr/bin/perl'
PERL_SCRIPTS = \
	$(PROTOUSRBINDIR)/diffpp \
	$(PROTOUSRBINDIR)/sliceprint

REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/math
