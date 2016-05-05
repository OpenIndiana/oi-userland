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
# Copyright 2016 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		  slurm
COMPONENT_VERSION=	  16.05.8
IPS_COMPONENT_VERSION=	  16.5.8
COMPONENT_SUMMARY=	  Slurm Workload Manager
COMPONENT_PROJECT_URL=	  http://slurm.schedmd.com/
COMPONENT_FMRI=		  system/slurm
COMPONENT_CLASSIFICATION= System/Services
COMPONENT_SRC=		  $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL= \
    http://www.schedmd.com/download/latest/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
    sha256:449ffbfe4098405743f073445a3344c8d083960d8e4bff959d9bc5224b475a97
COMPONENT_LICENSE=        GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CFLAGS+= -std=gnu99 -D_XOPEN_SOURCE=600 -D__EXTENSIONS__
CFLAGS+= -I/usr/mariadb/10.1/include 
CONFIGURE_OPTIONS+= --sysconfdir=$(ETCDIR)/slurm
CONFIGURE_OPTIONS+= --disable-largefile
CONFIGURE_OPTIONS+= --with-hdf5=no
CONFIGURE_OPTIONS+= --with-mysql_config=/usr/mariadb/10.1/bin/mysql_config

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/json-c
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/management/freeipmi
REQUIRED_PACKAGES += web/curl
