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
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		a2ps
COMPONENT_VERSION=	4.13
IPS_PKG_NAME=		print/lp/filter/a2ps
COMPONENT_DESCRIPTION=	"GNU Any to PostScript filter"
COMPONENT_CLASSIFICATION="System/Printing"
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://http.gnu.org/software/a2ps/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)b.tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:cfc79a3e54115e569f667fa3fd2c2ec16d22b31a
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/a2ps/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS  +=		--prefix=/usr
CONFIGURE_OPTIONS  +=		--enable-shared
CONFIGURE_OPTIONS  +=		--disable-static
CONFIGURE_OPTIONS  +=		--sysconfdir=/etc/gnu
CONFIGURE_OPTIONS  +=		--mandir=/usr/share/man
CONFIGURE_OPTIONS  +=		--infodir=/usr/share/info
CONFIGURE_OPTIONS  +=		--with-medium=letter

# because viewpathing isn't quite right in this version of a2ps
COMPONENT_PREP_ACTION = \
	(cd $(@D) ; ln -s auxdir/mkinstalldirs)
COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(@D)/doc ; \
	 ln -s ../../doc/make-authors.pl ; \
	 ln -s ../../doc/translators.txt)

PKGMOGRIFY_TRANSFORMS +=        $(WS_TOP)/transforms/libtool-drop

SFWPROGS =	a2ps card composeglyphs fixnt fixps ogonkify pdiff psmandup \
		psset texi2dvi4a2ps
PROTOSFWLINKS = $(SFWPROGS:%=$(PROTOSFWBIN)/%)

$(PROTOSFWLINKS):	$(PROTOSFWBIN)
	$(RM) $@ ; $(SYMLINK) ../../bin/$(@F) $@

PROTOETCLPFD = $(PROTO_DIR)/etc/lp/fd
FILTERDEFS =	a2ps.fd
PROTOFILTERDEFS = $(FILTERDEFS:%=$(PROTOETCLPFD)/%)

$(PROTOFILTERDEFS):	$(PROTOETCLPFD)
	$(INSTALL) -m 444 $(@F) $(@D)

$(PROTOSFWBIN) $(PROTOETCLPFD):	$(INSTALL_32)
	$(MKDIR) $@

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32) $(PROTOFILTERDEFS) $(PROTOSFWLINKS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

REQUIRED_TOOL +=	$(CCC)
REQUIRED_TOOL +=	$(CC)
REQUIRED_TOOL +=	/sbin/uname
REQUIRED_TOOL +=	/usr/bin/$(MACH64)/ld
REQUIRED_TOOL +=	/usr/bin/$(MACH64)/nm
REQUIRED_TOOL +=	/usr/bin/$(MACH64)/sort
REQUIRED_TOOL +=	/usr/bin/basename
REQUIRED_TOOL +=	/usr/bin/bash
REQUIRED_TOOL +=	/usr/bin/cat
REQUIRED_TOOL +=	/usr/bin/chmod
REQUIRED_TOOL +=	/usr/bin/cmp
REQUIRED_TOOL +=	/usr/bin/cp
REQUIRED_TOOL +=	/usr/bin/date
REQUIRED_TOOL +=	/usr/bin/echo
REQUIRED_TOOL +=	/usr/bin/egrep
REQUIRED_TOOL +=	/usr/bin/emacs
REQUIRED_TOOL +=	/usr/bin/env
REQUIRED_TOOL +=	/usr/bin/expr
REQUIRED_TOOL +=	/usr/bin/fgrep
REQUIRED_TOOL +=	/usr/bin/file
REQUIRED_TOOL +=	/usr/bin/flex
REQUIRED_TOOL +=	/usr/bin/gfind
REQUIRED_TOOL +=	/usr/bin/ggrep
REQUIRED_TOOL +=	/usr/bin/ginstall
REQUIRED_TOOL +=	/usr/bin/gmake
REQUIRED_TOOL +=	/usr/bin/gpatch
REQUIRED_TOOL +=	/usr/bin/grep
REQUIRED_TOOL +=	/usr/bin/gsed
REQUIRED_TOOL +=	/usr/bin/gtar
REQUIRED_TOOL +=	/usr/bin/gzip
REQUIRED_TOOL +=	/usr/bin/hostname
REQUIRED_TOOL +=	/usr/bin/ksh93
REQUIRED_TOOL +=	/usr/bin/imake
REQUIRED_TOOL +=	/usr/bin/install-info
REQUIRED_TOOL +=	/usr/bin/ld
REQUIRED_TOOL +=	/usr/bin/ln
REQUIRED_TOOL +=	/usr/bin/ls
REQUIRED_TOOL +=	/usr/bin/make
REQUIRED_TOOL +=	/usr/bin/mkdir
REQUIRED_TOOL +=	/usr/bin/msgfmt
REQUIRED_TOOL +=	/usr/bin/mv
REQUIRED_TOOL +=	/usr/bin/nm
REQUIRED_TOOL +=	/usr/bin/psselect
REQUIRED_TOOL +=	/usr/bin/rm
REQUIRED_TOOL +=	/usr/bin/sed
REQUIRED_TOOL +=	/usr/bin/sleep
REQUIRED_TOOL +=	/usr/bin/sort
REQUIRED_TOOL +=	/usr/bin/touch
REQUIRED_TOOL +=	/usr/bin/tr
REQUIRED_TOOL +=	/usr/bin/uniq
REQUIRED_TOOL +=	/usr/bin/xgettext
REQUIRED_TOOL +=	/usr/bin/xmkmf
REQUIRED_TOOL +=	/usr/gnu/bin/echo
REQUIRED_TOOL +=	/usr/gnu/bin/m4
REQUIRED_TOOL +=	/usr/gnu/bin/pwd
REQUIRED_TOOL +=	/usr/gnu/bin/sort
REQUIRED_TOOL +=	/usr/gnu/bin/uname
REQUIRED_TOOL +=	/usr/lib/cpp
REQUIRED_TOOL +=	/usr/perl5/bin/perl

REQUIRED_FILE +=	/lib/libc.so
REQUIRED_FILE +=	/lib/libm.so
REQUIRED_FILE +=	/usr/include/alloca.h
REQUIRED_FILE +=	/usr/include/assert.h
REQUIRED_FILE +=	/usr/include/ctype.h
REQUIRED_FILE +=	/usr/include/dirent.h
REQUIRED_FILE +=	/usr/include/errno.h
REQUIRED_FILE +=	/usr/include/fcntl.h
REQUIRED_FILE +=	/usr/include/fnmatch.h
REQUIRED_FILE +=	/usr/include/inttypes.h
REQUIRED_FILE +=	/usr/include/libintl.h
REQUIRED_FILE +=	/usr/include/limits.h
REQUIRED_FILE +=	/usr/include/locale.h
REQUIRED_FILE +=	/usr/include/malloc.h
REQUIRED_FILE +=	/usr/include/math.h
REQUIRED_FILE +=	/usr/include/memory.h
REQUIRED_FILE +=	/usr/include/nl_types.h
REQUIRED_FILE +=	/usr/include/pwd.h
REQUIRED_FILE +=	/usr/include/signal.h
REQUIRED_FILE +=	/usr/include/stdarg.h
REQUIRED_FILE +=	/usr/include/stdbool.h
REQUIRED_FILE +=	/usr/include/stddef.h
REQUIRED_FILE +=	/usr/include/stdio.h
REQUIRED_FILE +=	/usr/include/stdlib.h
REQUIRED_FILE +=	/usr/include/string.h
REQUIRED_FILE +=	/usr/include/strings.h
REQUIRED_FILE +=	/usr/include/sys/ioctl.h
REQUIRED_FILE +=	/usr/include/sys/mman.h
REQUIRED_FILE +=	/usr/include/sys/param.h
REQUIRED_FILE +=	/usr/include/sys/stat.h
REQUIRED_FILE +=	/usr/include/sys/time.h
REQUIRED_FILE +=	/usr/include/sys/types.h
REQUIRED_FILE +=	/usr/include/sys/wait.h
REQUIRED_FILE +=	/usr/include/termios.h
REQUIRED_FILE +=	/usr/include/time.h
REQUIRED_FILE +=	/usr/include/unistd.h
REQUIRED_FILE +=	/usr/include/varargs.h
REQUIRED_FILE +=	/usr/include/wchar.h
REQUIRED_FILE +=	/usr/share/lib/make

include ../../make-rules/depend.mk
