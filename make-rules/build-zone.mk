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
# Copyright (c) 2010, Oracle and/or it's affiliates.  All rights reserved.
#

#
# Rules and Macros for creating a template build zone from the installed system
# and a set of build zones that are clones of the template build zone.
#
# To use these rules to create a template build zone
#  $ gmake -f make-rules/build-zone.mk template-build-zone
#
# To use these rules to clone the template zone
#  $ gmake -f make-rules/build-zone.mk build-zone-[1-9]
# or
#  $ gmake -f make-rules/build-zone.mk \
#		/rpool/zones/build-zone-{*}/root/etc/sysidcfg
#
# Before you create any cloned build zones, it is recommended that you create
# the template build zone, boot it, and make any customizations to it first.
# The act of booting the template zone will cause it to perform any "first boot"
# tasks that might othwise slow down the initial boot of a new build zone.
# Also, all customizations of the template zone will only propagate to the build
# zones when they are created.
#

ZONECFG =		/usr/sbin/zonecfg
ZONEADM =		/usr/sbin/zoneadm
TZ=			$(shell sed -e '/^TZ=/!d' -e 's;TZ=;;' /etc/default/init)

ZONESCFG_DIR =		/etc/zones
BUILD_ZONE_SPACE =	/rpool/zones

TOUCH =			/usr/bin/touch

SYSIDCFG =		root/etc/sysidcfg
ZI_TAG =		root/.installed

# the name of the template build zone
TMPL_ZONE_NAME =	template-build-zone

#
# The template build zone will start with 'entire' installed.  We include
# additional packages to make the build zones more closely match most
# components' build requirements.  This makes build zone preparation quicker.
#
#TMPL_ZONE_TOOLS +=	developer/gcc-3
#TMPL_ZONE_TOOLS +=	developer/gnu-binutils
#TMPL_ZONE_TOOLS +=	developer/sunstudio12u1
TMPL_ZONE_TOOLS +=	archiver/gnu-tar
TMPL_ZONE_TOOLS +=	compress/p7zip
TMPL_ZONE_TOOLS +=	compress/unzip
TMPL_ZONE_TOOLS +=	developer/build/ant
TMPL_ZONE_TOOLS +=	developer/build/autoconf
TMPL_ZONE_TOOLS +=	developer/build/automake-110
TMPL_ZONE_TOOLS +=	developer/build/gnu-make
TMPL_ZONE_TOOLS +=	developer/build/libtool
TMPL_ZONE_TOOLS +=	developer/build/make
TMPL_ZONE_TOOLS +=	developer/gnome/gettext
TMPL_ZONE_TOOLS +=	developer/java/jdk
TMPL_ZONE_TOOLS +=	developer/lexer/flex
TMPL_ZONE_TOOLS +=	developer/macro/cpp
TMPL_ZONE_TOOLS +=	developer/macro/gnu-m4
TMPL_ZONE_TOOLS +=	developer/object-file
TMPL_ZONE_TOOLS +=	developer/parser/bison
TMPL_ZONE_TOOLS +=	file/gnu-coreutils
TMPL_ZONE_TOOLS +=	file/gnu-findutils
TMPL_ZONE_TOOLS +=	library/libxslt
TMPL_ZONE_TOOLS +=	library/pcre
TMPL_ZONE_TOOLS +=	text/gawk
TMPL_ZONE_TOOLS +=	text/gnu-diffutils
TMPL_ZONE_TOOLS +=	text/gnu-gettext
TMPL_ZONE_TOOLS +=	text/gnu-grep
TMPL_ZONE_TOOLS +=	text/gnu-patch
TMPL_ZONE_TOOLS +=	text/gnu-sed
TMPL_ZONE_TOOLS +=	text/groff
TMPL_ZONE_TOOLS +=	text/texinfo

TMPL_ZONE_PKGS =	$(TMPL_ZONE_TOOLS)

template-build-zone:	$(BUILD_ZONE_SPACE)/$(TMPL_ZONE_NAME)/$(SYSIDCFG)
build-zone-1:		$(BUILD_ZONE_SPACE)/build-zone-1/$(SYSIDCFG)
build-zone-2:		$(BUILD_ZONE_SPACE)/build-zone-2/$(SYSIDCFG)
build-zone-3:		$(BUILD_ZONE_SPACE)/build-zone-3/$(SYSIDCFG)
build-zone-4:		$(BUILD_ZONE_SPACE)/build-zone-4/$(SYSIDCFG)
build-zone-5:		$(BUILD_ZONE_SPACE)/build-zone-5/$(SYSIDCFG)
build-zone-6:		$(BUILD_ZONE_SPACE)/build-zone-6/$(SYSIDCFG)
build-zone-7:		$(BUILD_ZONE_SPACE)/build-zone-7/$(SYSIDCFG)
build-zone-8:		$(BUILD_ZONE_SPACE)/build-zone-8/$(SYSIDCFG)
build-zone-9:		$(BUILD_ZONE_SPACE)/build-zone-9/$(SYSIDCFG)

# zone install options.  The template zone uses "install", while the build
# zones "clone" the template zone.
ZI_OPT =				clone $(TMPL_ZONE_NAME)
$(BUILD_ZONE_SPACE)/$(TMPL_ZONE_NAME)/$(ZI_TAG): \
	ZI_OPT = 			install $(TMPL_ZONE_PKGS:%=-e %)

$(BUILD_ZONE_SPACE):
	$(MKDIR) $@

# configure a zone
$(ZONECFG_DIR)/%.xml:	$(BUILD_ZONE_SPACE)
	( echo "create -b"; \
	  echo "set zonepath=$(BUILD_ZONE_SPACE)/$(@:$(ZONECFG_DIR)/%.xml=%)"; \
	  echo "set brand=ipkg"; \
	  echo "set autoboot=false"; \
	  echo "verify"; \
	  echo "commit" ) | $(ZONECFG) -z $(@:$(ZONECFG_DIR)/%.xml=%)

# install a zone
$(BUILD_ZONE_SPACE)/%/$(ZI_TAG):	$(ZONECFG_DIR)/%.xml
	$(ZONEADM) -z $(@:$(BUILD_ZONE_SPACE)/%/$(ZI_TAG)=%) $(ZI_OPT)

$(BUILD_ZONE_SPACE)/%/$(SYSIDCFG):	$(BUILD_ZONE_SPACE)/%/$(ZI_TAG)
	( echo "system_locale=C"; \
	  echo "timezone=$(TZ)"; \
	  echo "terminal=xterms"; \
	  echo "security_policy=NONE"; \
	  echo "timeserver=localhost"; \
	  echo "name_service=NONE"; \
	  echo "network_interface=none {"; \
	  echo "    hostname=$(@:$(BUILD_ZONE_SPACE)/%/$(SYSIDCFG)=%)"; \
	  echo "}"; \
	  echo "nfs4_domain=dynamic"; \
	  echo "root_password=NP" ) > $@
