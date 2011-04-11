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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		emacs
COMPONENT_VERSION=	23.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha1:5f2d5dfcc17e7627ea752f675c605fe37c9c145c
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/emacs/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# Some of the GNU COPYING (GPL licence) files are delivered to the end
# user by the emacs packages, so add the disclaimer text to all such
# files as part of the prep. Copy one of these files into the component
# directory to serve as emacs.license
COMPONENT_PREP_ACTION = \
	for F in `find $(@D) -name COPYING`; do \
		mv $$F $$F.orig; \
		cat augment/disclaimer $$F.orig > $$F; \
	done; \
	cp $(@D)/COPYING emacs.license

# we build three different variants of emacs for our users. As Solaris
# always has a 64-bit kernel, and 64-bit emacs can handle larger files,
# we only build and deliver 64-bit binaries.
VARIANTS =	nox x gtk

BUILD_64 = $(VARIANTS:%=$(BUILD_DIR)/$(MACH64)-%/.built)
INSTALL_64 = $(VARIANTS:%=$(BUILD_DIR)/$(MACH64)-%/.installed)

# emacs creates a directory in usr/lib/emacs/$(COMPONENT_VERSION) that
# contains the platform name. Although the name is platform dependent,
# the files inside it are the same on all platforms. By adding this
# to the pkgmogrify macros, we can write our manifests in a portable way.
EMACS_ULEV_PFX = $(MACH:sparc=sparc-sun)
EMACS_ULEVDIR =	 $(EMACS_ULEV_PFX:i386=x86_64-pc)-solaris$(SOLARIS_VERSION)
PKG_MACROS +=	EMACS_ULEVDIR=$(EMACS_ULEVDIR)

# LD_OPTIONS is defined to apply desirable link-editor options to Userland
# components. Non-executable stack and data break sparc emacs.
#
LD_MAP_NOEXSTK.sparc=
LD_MAP_NOEXDATA.sparc=

# This code is built with gcc. The primary reason for this is that the
# configure script has problems using a non-GNU cpp. I am not aware of
# any reason Sun Studio could not be made to work, but simply made a
# cost/benefit decision not to pursue it at this time
COMPILER =	gcc

# Uncomment this for debugging only. It configures emacs to run from the
# local proto instead of from its final installed location.
#CONFIGURE_PREFIX =	$(PROTO_DIR)/usr

# configure options common to all variants of emacs that we want to build.
CONFIGURE_OPTIONS +=	CC="gcc -m64"
CONFIGURE_OPTIONS +=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS +=	--datarootdir=$(CONFIGURE_PREFIX)/share
CONFIGURE_OPTIONS +=	--libexecdir=$(CONFIGURE_PREFIX)/lib
CONFIGURE_OPTIONS +=	--with-gif=no
CONFIGURE_OPTIONS +=	ac_cv_sys_long_file_names=yes

# variant specific configure options
$(BUILD_DIR)/%-nox/.configured: CONFIGURE_OPTIONS +=	--without-x
$(BUILD_DIR)/%-x/.configured:    CONFIGURE_OPTIONS +=	--with-x-toolkit=lucid
$(BUILD_DIR)/%-gtk/.configured:  CONFIGURE_OPTIONS +=	--with-x-toolkit=gtk

# we need to build all variants, but only have to install one in order
# to get the common files shared by all. We use COMPONENT_POST_INSTALL_ACTION
# to remove unwanted files, copy the emacs binaries from the other tookit
# builds into place, and install the additional files we provide.
#
# Note that this tweaking is not required, as the proto need not match
# the packaging. However, doing it this way allows us to examine the proto
# as a finished and complete product, simplifies debugging emacs, and
# facilitates the use of 'gmake sample-manifest'.
PBIN=		$(PROTO_DIR)/usr/bin
PETC=		$(PROTO_DIR)/usr/share/emacs/$(COMPONENT_VERSION)/etc
PGBIN=		$(PROTO_DIR)/usr/gnu/bin
PGSHAREMAN1=	$(PROTO_DIR)/usr/gnu/share/man/man1
PSHAREMAN1=	$(PROTO_DIR)/usr/share/man/man1
PVAR=		$(PROTO_DIR)/var

# Remove emacs existing emacs executables/script from usr/bin
COMPONENT_POST_INSTALL_ACTION += rm -f $(PBIN)/emacs $(PBIN)/emacs-* ;

# GTK binaries
COMPONENT_POST_INSTALL_ACTION += cp $(BUILD_DIR)/$(MACH64)-gtk/src/emacs \
					$(PBIN)/emacs-gtk ;
COMPONENT_POST_INSTALL_ACTION += ln $(PBIN)/emacs-gtk \
					$(PBIN)/emacs-gtk-$(COMPONENT_VERSION) ;

# Non-X11 binaries
COMPONENT_POST_INSTALL_ACTION += cp $(BUILD_DIR)/$(MACH64)-nox/src/emacs \
					$(PBIN)/emacs-nox ;
COMPONENT_POST_INSTALL_ACTION += ln $(PBIN)/emacs-nox \
					$(PBIN)/emacs-nox-$(COMPONENT_VERSION) ;

# X11 (Athena) binaries
COMPONENT_POST_INSTALL_ACTION += cp $(BUILD_DIR)/$(MACH64)-x/src/emacs \
					$(PBIN)/emacs-x ;
COMPONENT_POST_INSTALL_ACTION += ln $(PBIN)/emacs-x \
					$(PBIN)/emacs-x-$(COMPONENT_VERSION) ;

# Emacs shell script that picks the right variant at runtime
COMPONENT_POST_INSTALL_ACTION += cp augment/emacs $(PBIN) ;
COMPONENT_POST_INSTALL_ACTION += chmod +x $(PBIN)/emacs ;

# ctags and etags go in /usr/gnu/bin instead of /usr/bin
COMPONENT_POST_INSTALL_ACTION += mkdir -p $(PGBIN) ;
COMPONENT_POST_INSTALL_ACTION += mv $(PBIN)/ctags $(PBIN)/etags $(PGBIN) ;

# We do not install the files under /var/games/emacs. The reason for
# this is that we do not install update-game-score as setuid, and
# therefore the game files are not usable. This the same decision made
# by Debian, among others.
COMPONENT_POST_INSTALL_ACTION += rm -rf $(PVAR) ;

# Odd thing: The file usr/share/emacs/23.1/etc/DOC-23.1.1 needed by
# emacs gets installed as usr/share/emacs/23.1/etc/DOC-23.1.2. Correct it.
COMPONENT_POST_INSTALL_ACTION += mv $(PETC)/DOC-$(COMPONENT_VERSION).2 \
					$(PETC)/DOC-$(COMPONENT_VERSION).1 ;

# Throw away the manpages that were installed, and generate them again, using
# sed to bolt on an ATTRIBUTES section. ctags is special in that it simply
# inlines etags.1, and should not pass through solman.pl.
SOLMAN=perl tools/solman.pl
SOLMAN_CORE= $(SOLMAN) editor/gnu-emacs
MAN_DIST_PCORE= $(SOLMAN_CORE) < $(COMPONENT_SRC)/doc/man/XXX \
	> $(PSHAREMAN1)/XXX

COMPONENT_POST_INSTALL_ACTION += rm $(PSHAREMAN1)/* ;
COMPONENT_POST_INSTALL_ACTION += $(MAN_DIST_PCORE:XXX=b2m.1) ;
COMPONENT_POST_INSTALL_ACTION += $(MAN_DIST_PCORE:XXX=ebrowse.1) ;
COMPONENT_POST_INSTALL_ACTION += $(MAN_DIST_PCORE:XXX=emacs.1) ;
COMPONENT_POST_INSTALL_ACTION += $(MAN_DIST_PCORE:XXX=emacsclient.1) ;
COMPONENT_POST_INSTALL_ACTION += $(MAN_DIST_PCORE:XXX=grep-changelog.1) ;
COMPONENT_POST_INSTALL_ACTION += $(MAN_DIST_PCORE:XXX=rcs-checkin.1) ;

COMPONENT_POST_INSTALL_ACTION += $(SOLMAN) editor/gnu-emacs/gnu-emacs-gtk \
	< augment/man/man1/emacs-gtk.1 > $(PSHAREMAN1)/emacs-gtk.1 ;
COMPONENT_POST_INSTALL_ACTION += $(SOLMAN) editor/gnu-emacs/gnu-emacs-no-x11 \
	< augment/man/man1/emacs-nox.1 > $(PSHAREMAN1)/emacs-nox.1 ;
COMPONENT_POST_INSTALL_ACTION += $(SOLMAN) editor/gnu-emacs/gnu-emacs-x11 \
	< augment/man/man1/emacs-x.1 > $(PSHAREMAN1)/emacs-x.1 ;

COMPONENT_POST_INSTALL_ACTION += mkdir -p $(PGSHAREMAN1) ;
COMPONENT_POST_INSTALL_ACTION += cp $(COMPONENT_SRC)/doc/man/ctags.1 \
					$(PGSHAREMAN1)/ctags.1 ;
COMPONENT_POST_INSTALL_ACTION += $(SOLMAN_CORE) \
	< $(COMPONENT_SRC)/doc/man/etags.1 > $(PGSHAREMAN1)/etags.1 ;

# Throw away usr/share/info/dir. This file is the topmost node of the Info
# hierarchy. Emacs builds it, as presumably do all GNU packages, but on
# Solaris, it is delivered by system/prerequisite/gnu.
COMPONENT_POST_INSTALL_ACTION += rm $(PROTO_DIR)/usr/share/info/dir ;


# common targets
build:          $(BUILD_64)

install:	$(BUILD_64) $(BUILD_DIR)/$(MACH64)-x/.installed 

CLEAN_PATHS +=	emacs.license

test:
	@echo "no tests available"

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
