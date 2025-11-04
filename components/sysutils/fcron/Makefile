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
# Copyright 2021 David Stes
#

#
# Package Makefile for "Frequency Cron" (fcron) by Thibault Godouet
# See https://github.com/yo8192/fcron and http://fcron.free.fr/
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           fcron
COMPONENT_VERSION=        3.3.3
COMPONENT_SUMMARY=        Frequency Cron
COMPONENT_PROJECT_URL=    http://fcron.free.fr
COMPONENT_SRC=		  fcron-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	  $(COMPONENT_SRC).src.tar.gz
COMPONENT_ARCHIVE_HASH=	  sha256:e5b48c9b78cb38cfb24a038dcb13a08b5121889375378f42f3c94bc250d21497
COMPONENT_ARCHIVE_URL=	  http://fcron.free.fr/archives/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=           sysutils/fcron
COMPONENT_CLASSIFICATION= System/Administration and Configuration
COMPONENT_LICENSE=        GPLv2
COMPONENT_LICENSE_FILE=   doc/en/txt/gpl.txt

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CFLAGS += $(XPG6MODE)

# a modified copy of the sysVinit-launcher script
PKG_PROTO_DIRS += $(COMPONENT_DIR)/files

CONFIGURE_OPTIONS += --with-cflags="$(CFLAGS)"
CONFIGURE_OPTIONS += --with-spooldir=/var/spool/fcron
CONFIGURE_OPTIONS += --with-piddir=/var/run
CONFIGURE_OPTIONS += --with-fifodir=/var/run

# the default username and groupname is fcron/fcron
# and the configure script+ Makefile wants to add those interactively
# this is fixed by a patch (01-user-group.patch) as option -with-answer-all
# is not skipping the actual tests

# do not install systemd/rc.d boot install scripts
# a simple legacy /etc/init.d script is provided by script/sysVinit-launcher
CONFIGURE_OPTIONS += --with-boot-install=no
# unable to get pam working 
CONFIGURE_OPTIONS += --with-pam=no

# default install is install-staged + strip + perms (perms set permissions)

COMPONENT_INSTALL_TARGETS= install-staged

# Manually added build dependencies
REQUIRED_PACKAGES += editor/vim
REQUIRED_PACKAGES += service/network/smtp/sendmail

# Auto-generated dependencies
REQUIRED_PACKAGES += $(READLINE_PKG)
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
