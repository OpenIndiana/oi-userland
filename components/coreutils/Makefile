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

COMPONENT_NAME=		coreutils
COMPONENT_VERSION=	8.5
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:939144f16d05691753a87134436dd2bb8ea89851
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/coreutils/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_PREFIX	 =	/usr/gnu
CONFIGURE_OPTIONS	+=	--libdir=/usr/lib
CONFIGURE_OPTIONS	+=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS	+=	CPPFLAGS=-I/usr/include/gmp
CONFIGURE_OPTIONS	+=	CFLAGS="$(CFLAGS)"

include ../../make-rules/shared-targets.mk

# common targets
build:		$(BUILD_32)

CMDS_NONCONFLICTING=\[ base64 dir dircolors md5sum nproc pinky \
printenv ptx readlink seq sha1sum sha224sum sha256sum sha384sum sha512sum \
shred shuf stat stdbuf tac timeout truncate users vdir whoami

MANS_NONCONFLICTING=base64.1 dir.1 dircolors.1 md5sum.1 nproc.1 pinky.1 \
printenv.1 ptx.1 readlink.1 seq.1 sha1sum.1 sha224sum.1 sha256sum.1 \
sha384sum.1 sha512sum.1 shred.1 shuf.1 stat.1 stdbuf.1 tac.1 \
timeout.1 truncate.1 users.1 vdir.1 whoami.1

NEEDMV=if [ -e $(1) ]; then $(RM) $(2); /usr/bin/mv $(1) $(2); fi
RMDIR=/usr/bin/rmdir

install:	$(PROTOUSRBINDIR) $(PROTOUSRSHAREMAN1DIR) $(INSTALL_32)
	for command in $(CMDS_NONCONFLICTING); do \
		$(call NEEDMV,$(PROTOGNUBIN)/$$command,\
			$(PROTOUSRBINDIR)/$$command) \
	done
	for manpage in $(COMPONENT_SRC)/man/*.1; do \
		sed -f oracleman-stability $$manpage > \
			$(PROTO_DIR)/$(GNUSHAREMAN1)/`basename $$manpage`; \
	done
	for manpage in $(MANS_NONCONFLICTING); do \
		$(call NEEDMV,$(PROTOGNUSHAREMAN1)/$$manpage,\
			$(PROTOUSRSHAREMAN1DIR)/$$manpage); \
	done
	#
	# whoami is in both /usr/bin and /usr/gnu/bin; mistake?
	#
	$(CP) $(PROTOUSRBINDIR)/whoami $(PROTOGNUBIN)/whoami
	$(CP) $(PROTOUSRSHAREMAN1DIR)/whoami.1 $(PROTOGNUSHAREMAN1)/whoami.1
	$(call NEEDMV,$(PROTOGNUBIN)/install,$(PROTOUSRBINDIR)/ginstall)
	$(call NEEDMV,$(PROTOGNUSHAREMAN1)/install.1,\
		$(PROTOUSRSHAREMAN1DIR)/ginstall.1)
	$(call NEEDMV,$(PROTOUSRLIBDIR)/coreutils/libstdbuf.so,\
		$(PROTOUSRLIBDIR)/libstdbuf.so)
	-$(RMDIR) $(PROTOUSRLIBDIR)/coreutils
	$(RM) $(PROTOGNUBIN)/chcon
	$(RM) $(PROTOGNUBIN)/runcon
	$(RM) $(PROTOGNUSHAREMAN1)/chcon.1
	$(RM) $(PROTOGNUSHAREMAN1)/runcon.1
	$(RM) $(PROTOUSRLIBDIR)/charset.alias

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

test: build
	@cd $(BUILD_DIR_32); $(MAKE) check

include ../../make-rules/depend.mk
