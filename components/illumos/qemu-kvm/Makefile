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
# Copyright 2011 EveryCity Ltd. All rights reserved.
# Copyright 2012, Piotr Jasiukajtis
#

include ../../../make-rules/shared-macros.mk

PATH=	/opt/onbld/bin/i386:/usr/bin:/usr/sbin:/sbin:/usr/gnu/bin
COMPONENT_NAME=		illumos-kvm-cmd
COMPONENT_VERSION=	1c6181b
IPS_COMPONENT_VERSION=	0.0.1.20131024
COMPONENT_SRC=		illumos-kvm-cmd-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:1664981d73d4a17e3271f167a15b20601f3c5a9cbb500db9ebe6dfa58d37f87a
COMPONENT_ARCHIVE_URL=	https://codeload.github.com/joyent/illumos-kvm-cmd/tar.gz/$(COMPONENT_VERSION)

ifeq ($(MACH), sparc)
PUBLISH_STAMP=
endif

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CC=/opt/gcc/4.4.4/bin/gcc

COMPONENT_BUILD_ARGS=

COMPONENT_PREP_ACTION = \
	($(MKDIR) $(SOURCE_DIR)/kvm/include/sys; \
	$(LN) $(COMPONENT_DIR)/illumos-kvm/*.h $(SOURCE_DIR)/kvm/include/sys; )

COMPONENT_PRE_CONFIGURE_ACTION = \
	$(CLONEY) $(SOURCE_DIR) $(@D)

CONFIGURE_ENV += PATH=$(PATH):/usr/sbin

CONFIGURE_OPTIONS = --cc=$(CC)
CONFIGURE_OPTIONS += --extra-cflags="-fno-builtin"
CONFIGURE_OPTIONS += --extra-ldflags="-nodefaultlibs -lz -lm -lc"
CONFIGURE_OPTIONS += --prefix=/usr
CONFIGURE_OPTIONS += --mandir=/usr/share/man
CONFIGURE_OPTIONS += --bindir=/usr/bin/amd64
CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-kvm
CONFIGURE_OPTIONS += --enable-kvm-pit
CONFIGURE_OPTIONS += --enable-vnc-png
CONFIGURE_OPTIONS += --disable-kvm-device-assignment
CONFIGURE_OPTIONS += --enable-trace-backend=dtrace
CONFIGURE_OPTIONS += --target-list="i386-softmmu x86_64-softmmu"
CONFIGURE_OPTIONS += --enable-debug

COMPONENT_BUILD_ENV += PATH=$(PATH):/usr/sbin CTFCONVERT=/opt/onbld/bin/i386/ctfconvert CTFMERGE=/opt/onbld/bin/i386/ctfmerge

COMPONENT_INSTALL_ENV += PATH=$(PATH):/usr/sbin CTFCONVERT=/opt/onbld/bin/i386/ctfconvert CTFMERGE=/opt/onbld/bin/i386/ctfmerge

build_sparc:
	@echo "Not available."

build_i386:	$(BUILD_64)

build:		build_$(MACH)

install_sparc:
	@echo "Not available."

install_i386:	$(INSTALL_64)

install:	install_$(MACH)
