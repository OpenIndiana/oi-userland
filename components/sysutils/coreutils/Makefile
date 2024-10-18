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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
# Copyright 2017 Gary Mills
# Copyright 2017 Aurelien Larcher
# Copyright 2019 Michal Nowak
# Copyright 2020-2021 Nona Hansel
#

BUILD_BITS= 64_and_32
USE_PARALLEL_BUILD= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
USE_COMMON_TEST_MASTER= no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         coreutils
COMPONENT_VERSION=      9.5
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=		GNU Core Utilities are the basic file, shell and text manipulation utilities
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/coreutils/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:cd328edeac92f6a665de9f323c93b712af1858bc2e0d88f3f7100469470a1b8a
COMPONENT_ARCHIVE_URL=  https://ftp.gnu.org/gnu/coreutils/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         file/gnu-coreutils	
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_LICENSE=	GPL-3.0-only
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

gcc_OPT.sparc.32 = -O1

CFLAGS += $(CPP_LARGEFILES)

CONFIGURE_PREFIX	 =	$(GNUDIR)
CONFIGURE_BINDIR.64	 =	$(GNUBIN)
CONFIGURE_OPTIONS	+=	CPPFLAGS=" -I$(USRINCDIR)/gmp"
CONFIGURE_OPTIONS	+=	--libdir=$(USRLIBDIR.$(BITS))
# Put libstdbuf in the library directory
CONFIGURE_OPTIONS	+=	--libexecdir=$(USRLIBDIR.$(BITS))
CONFIGURE_OPTIONS.32 +=	--disable-year2038
# chcon and runcon are linux only
CONFIGURE_OPTIONS += --enable-no-install-program=chcon,runcon

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

# OS as reported by `uname -o`
CONFIGURE_ENV += gl_cv_host_operating_system=illumos

# Drop 32-bit binaries
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOGNUBIN32) ;
# Drop info files installed for 32-bit build
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOUSRSHAREDIR)/info ;
# Drop man pages installed for 32-bit build
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOGNUSHAREMAN) ;
# Drop locale installed for 32-bit build
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOGNUSHARE)/locale ;

# We do not want the info index file
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRSHAREDIR)/info/dir ;

# Move some non-conflicting binaries and their manpages to default location
# /usr/bin or /usr/share/man respectively.
COMPONENT_POST_INSTALL_ACTION.64 += \
	$(MKDIR) $(PROTOUSRBINDIR) ; \
	$(MKDIR) $(PROTOUSRSHAREMAN1DIR) ; \
	for f in b2sum base32 base64 dir dircolors md5sum pinky printenv ptx \
	    readlink realpath seq sha1sum sha224sum sha256sum sha384sum sha512sum \
	    shred shuf stat stdbuf tac timeout truncate vdir whoami ; do \
		$(MV) $(PROTOGNUBIN)/$$f $(PROTOUSRBINDIR) ; \
		$(MV) $(PROTOGNUSHAREMAN1)/$$f.1 $(PROTOUSRSHAREMAN1DIR) ; \
	done ;

# Compatibility symlinks for binaries and their manpages
COMPONENT_POST_INSTALL_ACTION.64 += \
	for f in $$(ls $(PROTOGNUBIN)) ; do \
		[ "$$f" == "[" ] && continue ; \
		[ "$$f" == "nproc" ] && continue ; \
		[ "$$f" == "numfmt" ] && continue ; \
		[ "$$f" == "users" ] && continue ; \
		$(SYMLINK) ../gnu/bin/$$f $(PROTOUSRBINDIR)/g$$f ; \
		$(SYMLINK) ../../../gnu/share/man/man1/$$f.1 $(PROTOUSRSHAREMAN1DIR)/g$$f.1 ; \
	done ;

# We want the libstdbuf.so library at default location
COMPONENT_POST_INSTALL_ACTION += $(MV) $(PROTOUSRLIBDIR.$(BITS))/coreutils/libstdbuf.so $(PROTOUSRLIBDIR.$(BITS)) ;

# Get the binaries to test from the component proto area.
COMPONENT_TEST_ENV += PATH=$(PROTOGNUBIN):$(USRBINDIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += system/library
