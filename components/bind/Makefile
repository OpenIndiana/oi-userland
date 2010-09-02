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

COMPONENT_NAME=		bind
COMPONENT_VERSION=	9.7.0-P2
IPS_PKG_NAME =		network/dns/bind
COMPONENT_CLASSIFICATION="Applications/Internet utility"
COMPONENT_DESCRIPTION=	"Berkeley Internet Name Domain server and utilities"
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL =	http://www.isc.org/software/bind
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:4b805d4a66075a88c93c5b852b928da96467aa2d
COMPONENT_ARCHIVE_URL=	http://ftp.isc.org/isc/bind9/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS +=	--with-libtool
CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--localstatedir=/var
CONFIGURE_OPTIONS +=	--with-openssl
CONFIGURE_OPTIONS +=	--enable-threads=yes
CONFIGURE_OPTIONS +=	--enable-devpoll=yes
CONFIGURE_OPTIONS +=	--disable-openssl-version-check
CONFIGURE_OPTIONS +=	--enable-fixed-rrset
CONFIGURE_OPTIONS +=	--disable-getifaddrs

# because IPS doesn't deal with -P2 in the version string
IPS_COMPONENT_VERSION=	9.7.0

PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/archive-libraries-drop
PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/libtool-drop
PKGMOGRIFY_TRANSFORMS +=	manifest-drop

PKG_HARDLINKS +=	usr/sbin/named
PKG_HARDLINKS +=	usr/share/man/man3/lwres_addr_parse.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_buffer.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_conf_clear.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_context.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_endhostent.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_freeaddrinfo.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_freehostent.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_gabn.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_gnba.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_herror.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_inetntop.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_lwpacket_parseheader.3
PKG_HARDLINKS +=	usr/share/man/man3/lwres_noop.3

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

REQUIRED_TOOL +=	/sbin/uname
REQUIRED_TOOL +=	/usr/bin/ar
REQUIRED_TOOL +=	/usr/bin/arch
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
REQUIRED_TOOL +=	/usr/bin/getconf
REQUIRED_TOOL +=	/usr/bin/ggrep
REQUIRED_TOOL +=	/usr/bin/gmake
REQUIRED_TOOL +=	/usr/bin/grep
REQUIRED_TOOL +=	/usr/bin/gsed
REQUIRED_TOOL +=	/usr/bin/gtar
REQUIRED_TOOL +=	/usr/bin/gzip
REQUIRED_TOOL +=	/usr/bin/hostname
REQUIRED_TOOL +=	/usr/bin/ksh93
REQUIRED_TOOL +=	/usr/bin/ld
REQUIRED_TOOL +=	/usr/bin/ln
REQUIRED_TOOL +=	/usr/bin/ls
REQUIRED_TOOL +=	/usr/bin/make
REQUIRED_TOOL +=	/usr/bin/mkdir
REQUIRED_TOOL +=	/usr/bin/mv
REQUIRED_TOOL +=	/usr/bin/nm
REQUIRED_TOOL +=	/usr/bin/ranlib
REQUIRED_TOOL +=	/usr/bin/rm
REQUIRED_TOOL +=	/usr/bin/rmdir
REQUIRED_TOOL +=	/usr/bin/sed
REQUIRED_TOOL +=	/usr/bin/sort
REQUIRED_TOOL +=	/usr/bin/strip
REQUIRED_TOOL +=	/usr/bin/touch
REQUIRED_TOOL +=	/usr/bin/tr
REQUIRED_TOOL +=	/usr/bin/xml2-config
REQUIRED_TOOL +=	/usr/gnu/bin/as
REQUIRED_TOOL +=	/usr/gnu/bin/echo
REQUIRED_TOOL +=	/usr/gnu/bin/etags
REQUIRED_TOOL +=	$(SPRO_ROOT)/bin/cc
REQUIRED_TOOL +=	$(SPRO_ROOT)/bin/CC

REQUIRED_FILE +=	/lib/$(MACH64)/libc.so
REQUIRED_FILE +=	/lib/$(MACH64)/libcrypto.so
REQUIRED_FILE +=	/lib/$(MACH64)/libm.so
REQUIRED_FILE +=	/lib/$(MACH64)/libnsl.so
REQUIRED_FILE +=	/lib/$(MACH64)/libpthread.so
REQUIRED_FILE +=	/lib/$(MACH64)/libscf.so
REQUIRED_FILE +=	/lib/$(MACH64)/libsocket.so
REQUIRED_FILE +=	/lib/$(MACH64)/libthread.so
REQUIRED_FILE +=	/lib/$(MACH64)/libxml2.so
REQUIRED_FILE +=	/lib/$(MACH64)/libz.so
REQUIRED_FILE +=	/lib/libc.so
REQUIRED_FILE +=	/lib/libcrypto.so
REQUIRED_FILE +=	/lib/libm.so
REQUIRED_FILE +=	/lib/libnsl.so
REQUIRED_FILE +=	/lib/libpthread.so
REQUIRED_FILE +=	/lib/libscf.so
REQUIRED_FILE +=	/lib/libsocket.so
REQUIRED_FILE +=	/lib/libthread.so
REQUIRED_FILE +=	/lib/libxml2.so
REQUIRED_FILE +=	/lib/libz.so
REQUIRED_FILE +=	/usr/include/arpa/inet.h
REQUIRED_FILE +=	/usr/include/assert.h
REQUIRED_FILE +=	/usr/include/ctype.h
REQUIRED_FILE +=	/usr/include/dirent.h
REQUIRED_FILE +=	/usr/include/dlfcn.h
REQUIRED_FILE +=	/usr/include/errno.h
REQUIRED_FILE +=	/usr/include/execinfo.h
REQUIRED_FILE +=	/usr/include/fcntl.h
REQUIRED_FILE +=	/usr/include/float.h
REQUIRED_FILE +=	/usr/include/grp.h
REQUIRED_FILE +=	/usr/include/iconv.h
REQUIRED_FILE +=	/usr/include/inttypes.h
REQUIRED_FILE +=	/usr/include/libgen.h
REQUIRED_FILE +=	/usr/include/libintl.h
REQUIRED_FILE +=	/usr/include/libscf.h
REQUIRED_FILE +=	/usr/include/libxml2/libxml/encoding.h
REQUIRED_FILE +=	/usr/include/libxml2/libxml/xmlwriter.h
REQUIRED_FILE +=	/usr/include/limits.h
REQUIRED_FILE +=	/usr/include/locale.h
REQUIRED_FILE +=	/usr/include/memory.h
REQUIRED_FILE +=	/usr/include/net/if_dl.h
REQUIRED_FILE +=	/usr/include/net/if.h
REQUIRED_FILE +=	/usr/include/netdb.h
REQUIRED_FILE +=	/usr/include/netinet/in.h
REQUIRED_FILE +=	/usr/include/nl_types.h
REQUIRED_FILE +=	/usr/include/openssl/bn.h
REQUIRED_FILE +=	/usr/include/openssl/conf.h
REQUIRED_FILE +=	/usr/include/openssl/crypto.h
REQUIRED_FILE +=	/usr/include/openssl/dh.h
REQUIRED_FILE +=	/usr/include/openssl/dsa.h
REQUIRED_FILE +=	/usr/include/openssl/e_os2.h
REQUIRED_FILE +=	/usr/include/openssl/engine.h
REQUIRED_FILE +=	/usr/include/openssl/err.h
REQUIRED_FILE +=	/usr/include/openssl/evp.h
REQUIRED_FILE +=	/usr/include/openssl/objects.h
REQUIRED_FILE +=	/usr/include/openssl/opensslv.h
REQUIRED_FILE +=	/usr/include/openssl/rand.h
REQUIRED_FILE +=	/usr/include/openssl/rsa.h
REQUIRED_FILE +=	/usr/include/openssl/x509.h
REQUIRED_FILE +=	/usr/include/pthread.h
REQUIRED_FILE +=	/usr/include/pwd.h
REQUIRED_FILE +=	/usr/include/regex.h
REQUIRED_FILE +=	/usr/include/signal.h
REQUIRED_FILE +=	/usr/include/stdarg.h
REQUIRED_FILE +=	/usr/include/stddef.h
REQUIRED_FILE +=	/usr/include/stdint.h
REQUIRED_FILE +=	/usr/include/stdio.h
REQUIRED_FILE +=	/usr/include/stdlib.h
REQUIRED_FILE +=	/usr/include/string.h
REQUIRED_FILE +=	/usr/include/strings.h
REQUIRED_FILE +=	/usr/include/sys/ioctl.h
REQUIRED_FILE +=	/usr/include/sys/param.h
REQUIRED_FILE +=	/usr/include/sys/resource.h
REQUIRED_FILE +=	/usr/include/sys/select.h
REQUIRED_FILE +=	/usr/include/sys/socket.h
REQUIRED_FILE +=	/usr/include/sys/sockio.h
REQUIRED_FILE +=	/usr/include/sys/stat.h
REQUIRED_FILE +=	/usr/include/sys/time.h
REQUIRED_FILE +=	/usr/include/sys/types.h
REQUIRED_FILE +=	/usr/include/sys/uio.h
REQUIRED_FILE +=	/usr/include/sys/un.h
REQUIRED_FILE +=	/usr/include/sys/wait.h
REQUIRED_FILE +=	/usr/include/syslog.h
REQUIRED_FILE +=	/usr/include/termios.h
REQUIRED_FILE +=	/usr/include/time.h
REQUIRED_FILE +=	/usr/include/unistd.h

include ../../make-rules/depend.mk
