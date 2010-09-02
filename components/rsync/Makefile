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

COMPONENT_NAME=		rsync
COMPONENT_VERSION=	3.0.7
IPS_PKG_NAME=		network/rsync
COMPONENT_DESCRIPTION=	"utility for fast incremental file transfer"
COMPONENT_CLASSIFICATION="Applications/System Utilities"
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.samba.org/rsync/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:63426a1bc71991d93159cd522521fbacdafb7a61
COMPONENT_ARCHIVE_URL=	http://www.samba.org/ftp/$(COMPONENT_NAME)/src/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS  +=		--with-included-popt
COMPONENT_BUILD_TARGETS +=	all
COMPONENT_BUILD_TARGETS +=	man

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

REQUIRED_TOOL +=	/sbin/uname
REQUIRED_TOOL +=	/usr/bin/arch
REQUIRED_TOOL +=	/usr/bin/awk
REQUIRED_TOOL +=	/usr/bin/basename
REQUIRED_TOOL +=	/usr/bin/bash
REQUIRED_TOOL +=	/usr/bin/chmod
REQUIRED_TOOL +=	/usr/bin/cp
REQUIRED_TOOL +=	/usr/bin/diff
REQUIRED_TOOL +=	/usr/bin/dirname
REQUIRED_TOOL +=	/usr/bin/echo
REQUIRED_TOOL +=	/usr/bin/env
REQUIRED_TOOL +=	/usr/bin/expr
REQUIRED_TOOL +=	/usr/bin/find
REQUIRED_TOOL +=	/usr/bin/ggrep
REQUIRED_TOOL +=	/usr/bin/ginstall
REQUIRED_TOOL +=	/usr/bin/gmake
REQUIRED_TOOL +=	/usr/bin/grep
REQUIRED_TOOL +=	/usr/bin/gtar
REQUIRED_TOOL +=	/usr/bin/gzip 
REQUIRED_TOOL +=	/usr/bin/hostname
REQUIRED_TOOL +=	/usr/bin/ksh93
REQUIRED_TOOL +=	/usr/bin/ld
REQUIRED_TOOL +=	/usr/bin/ln
REQUIRED_TOOL +=	/usr/bin/ls
REQUIRED_TOOL +=	/usr/bin/mkdir
REQUIRED_TOOL +=	/usr/bin/mv
REQUIRED_TOOL +=	/usr/bin/rm
REQUIRED_TOOL +=	/usr/bin/sed
REQUIRED_TOOL +=	/usr/bin/sort
REQUIRED_TOOL +=	/usr/bin/touch
REQUIRED_TOOL +=	/usr/bin/tr
REQUIRED_TOOL +=	/usr/perl5/bin/perl
REQUIRED_TOOL +=	$(SPRO_ROOT)/bin/cc

REQUIRED_FILE +=	/lib/libnsl.so
REQUIRED_FILE +=	/lib/libsec.so
REQUIRED_FILE +=	/lib/libsocket.so
REQUIRED_FILE +=	/usr/bin/arch
REQUIRED_FILE +=	/usr/include/alloca.h
REQUIRED_FILE +=	/usr/include/arpa/inet.h
REQUIRED_FILE +=	/usr/include/assert.h
REQUIRED_FILE +=	/usr/include/ctype.h
REQUIRED_FILE +=	/usr/include/dirent.h
REQUIRED_FILE +=	/usr/include/errno.h
REQUIRED_FILE +=	/usr/include/fcntl.h
REQUIRED_FILE +=	/usr/include/float.h
REQUIRED_FILE +=	/usr/include/grp.h
REQUIRED_FILE +=	/usr/include/iconv.h
REQUIRED_FILE +=	/usr/include/langinfo.h
REQUIRED_FILE +=	/usr/include/libintl.h
REQUIRED_FILE +=	/usr/include/limits.h
REQUIRED_FILE +=	/usr/include/locale.h
REQUIRED_FILE +=	/usr/include/malloc.h
REQUIRED_FILE +=	/usr/include/math.h
REQUIRED_FILE +=	/usr/include/netdb.h
REQUIRED_FILE +=	/usr/include/netinet/in_systm.h
REQUIRED_FILE +=	/usr/include/netinet/in.h
REQUIRED_FILE +=	/usr/include/netinet/ip.h
REQUIRED_FILE +=	/usr/include/netinet/ip6.h
REQUIRED_FILE +=	/usr/include/netinet/tcp.h
REQUIRED_FILE +=	/usr/include/popt.h
REQUIRED_FILE +=	/usr/include/pwd.h
REQUIRED_FILE +=	/usr/include/signal.h
REQUIRED_FILE +=	/usr/include/stdarg.h
REQUIRED_FILE +=	/usr/include/stdbool.h
REQUIRED_FILE +=	/usr/include/stddef.h
REQUIRED_FILE +=	/usr/include/stdio.h
REQUIRED_FILE +=	/usr/include/stdlib.h
REQUIRED_FILE +=	/usr/include/string.h
REQUIRED_FILE +=	/usr/include/strings.h
REQUIRED_FILE +=	/usr/include/sys/acl.h
REQUIRED_FILE +=	/usr/include/sys/attr.h
REQUIRED_FILE +=	/usr/include/sys/fcntl.h
REQUIRED_FILE +=	/usr/include/sys/file.h
REQUIRED_FILE +=	/usr/include/sys/filio.h
REQUIRED_FILE +=	/usr/include/sys/ioctl.h
REQUIRED_FILE +=	/usr/include/sys/mkdev.h
REQUIRED_FILE +=	/usr/include/sys/mode.h
REQUIRED_FILE +=	/usr/include/sys/param.h
REQUIRED_FILE +=	/usr/include/sys/select.h
REQUIRED_FILE +=	/usr/include/sys/socket.h
REQUIRED_FILE +=	/usr/include/sys/stat.h
REQUIRED_FILE +=	/usr/include/sys/time.h
REQUIRED_FILE +=	/usr/include/sys/types.h
REQUIRED_FILE +=	/usr/include/sys/un.h
REQUIRED_FILE +=	/usr/include/sys/wait.h
REQUIRED_FILE +=	/usr/include/syslog.h
REQUIRED_FILE +=	/usr/include/time.h
REQUIRED_FILE +=	/usr/include/unistd.h
REQUIRED_FILE +=	/usr/include/utime.h
REQUIRED_FILE +=	/usr/include/wchar.h

include ../../make-rules/depend.mk
