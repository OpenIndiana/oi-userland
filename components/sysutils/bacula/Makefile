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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= bacula

COMPONENT_VERSION= 5.2.13
COMPONENT_REVISION= 6
COMPONENT_SUMMARY= Bacula (network backup solution)
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:a4bed458bf001889bd06bf31671b5d9908055a1d1e8113fd750ae4d326607ad8
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/bacula/files/bacula/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_PROJECT_URL = http://www.bacula.org

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

LD_Z_IGNORE =
LD_B_DIRECT =
CXXFLAGS.32=-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE
CFLAGS.32=-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE

CXXFLAGS+=$(CXXFLAGS.$(BITS))
CFLAGS+=$(CFLAGS.$(BITS))

PATH=$(MYSQL_BINDIR.$(BITS)):$(PG_BINDIR.$(BITS)):/usr/bin:/usr/sbin

CONFIGURE_OPTIONS+= --sysconfdir=/etc/bacula
CONFIGURE_OPTIONS+= --with-scriptdir=/etc/bacula/scripts
CONFIGURE_OPTIONS+= --with-working-dir=/var/bacula
CONFIGURE_OPTIONS+= --sharedstatedir=/var/bacula
CONFIGURE_OPTIONS+= --localstatedir=/var/bacula
CONFIGURE_OPTIONS+= --with-logdir=/var/bacula
CONFIGURE_OPTIONS+= --with-pid-dir=/var/bacula
CONFIGURE_OPTIONS+= --with-smtp-host=localhost
CONFIGURE_OPTIONS+= --with-sqlite3
CONFIGURE_OPTIONS+= --with-postgresql
CONFIGURE_OPTIONS+= --with-mysql
CONFIGURE_OPTIONS+= --with-openssl
CONFIGURE_OPTIONS+= --with-tcp-wrappers
CONFIGURE_OPTIONS+= --with-readline=/usr/include/readline
CONFIGURE_OPTIONS+= --disable-conio
CONFIGURE_OPTIONS+= --disable-rpath
CONFIGURE_ENV    += PYTHON="$(PYTHON)"
CONFIGURE_ENV.64    += lt_cv_sys_lib_dlsearch_path_spec="/lib/$(MACH64) /usr/lib/$(MACH64)"

# don't embed 64-bit paths in scripts
$(INSTALL_32): $(INSTALL_64)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += database/mariadb-101/library
REQUIRED_PACKAGES += database/postgres-94/library
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/lzo
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
