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

#
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

PATH=$(SPRO_VROOT)/bin:$(JAVA_HOME)/bin:/usr/bin

COMPONENT_NAME=		otp_src
COMPONENT_VERSION_MAJOR=	12
COMPONENT_VERSION_MINOR=	B
COMPONENT_VERSION_MICRO=	5
# IPS_COMPONENT_VERSION needs update whenever this is changed
COMPONENT_VERSION=	R$(COMPONENT_VERSION_MAJOR)$(COMPONENT_VERSION_MINOR)-$(COMPONENT_VERSION_MICRO)
COMPONENT_PROJECT_URL=	http://www.erlang.org/
COMPONENT_SRC=		$(COMPONENT_NAME)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:6c45509acf70d35d5def2cbefd86ada093c1ac3a
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE)

# manpages
COMPONENT_NAME_1=	otp_doc_man
COMPONENT_SRC_1=	$(COMPONENT_NAME_1)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1=	sha1:ae7036bd2afc9d1fca97f0de2eca84f56656def8
COMPONENT_ARCHIVE_URL_1=	$(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE_1)

# HTML documentation
COMPONENT_NAME_2=	otp_doc_html
COMPONENT_SRC_2=	$(COMPONENT_NAME_2)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_2=	$(COMPONENT_SRC_2).tar.gz
COMPONENT_ARCHIVE_HASH_2=	sha1:0bd369d02051e01bac58c9b8665bd3538e116f51
COMPONENT_ARCHIVE_URL_2=	$(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE_2)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# IPS_COMPONENT_VERSION is by default set to $(COMPONENT_VERSION) but it is not
# enough for us. We need to include the $(COMPONENT_SUBVERSION) somehow.
# Because the IPS_COMPONENT_VERSION cannot contain letters we use mapping:
# R(major)(minor)-(micro) - (major).(minor as number).(micro)
IPS_COMPONENT_VERSION=  $(COMPONENT_VERSION_MAJOR).2.$(COMPONENT_VERSION_MICRO)

# Built in SFW with gcc and builds cleanly now only with gcc
COMPILER = gcc

CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += CPPFLAGS="$(CPPFLAGS) -I/usr/include/gd2"
CONFIGURE_OPTIONS += --enable-smp-support
CONFIGURE_OPTIONS += --enable-threads
CONFIGURE_OPTIONS += --enable-hipe
CONFIGURE_OPTIONS += --with-ssl
CONFIGURE_OPTIONS += --enable-dynamic-ssl-lib

CONFIGURE_OPTIONS.64 += LDFLAGS="$(LDFLAGS) -m64"
CONFIGURE_OPTIONS.64 += LIBS="-m64"

# Use cp(1) instead of cloney because erlang's 'install' target uses 'tar'
# to copy files and our tar doesn't handle long links by default.  Between
# the use of 'tar' and 'ld', a path adjustment wasn't an option due to the
# need for /usr/bin/ld and /usr/gnu/bin/tar.  Perhaps this can be looked
# at when we upgrade to a more current version.
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CP) -rp $(SOURCE_DIR)/. $(@D))
CONFIGURE_SCRIPT =	$(@D)/configure

COMPONENT_INSTALL_ARGS += INSTALL_PREFIX=$(PROTO_DIR)

# common targets
build:	$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)
	# Undelivered useless files:
	#    erlang/lib/crypto-*/priv/obj
	#    erlang/lib/ssl-*/priv/obj
	#    erlang/Install
	#    erlang/misc
	#    erlang/*/*.bat
	#    manpages: start.1 werl.1
	$(RM) -r documentation
	$(MKDIR) documentation && cd documentation && \
	$(UNPACK) $(UNPACK_ARGS) ../$(COMPONENT_ARCHIVE_1) && \
	$(UNPACK) $(UNPACK_ARGS) ../$(COMPONENT_ARCHIVE_2)
	# remove INSTALL_PREFIX from path
	$(PERL) -pi -e "s|$(PROTO_DIR)||g" $(PROTO_DIR)/usr/lib/erlang/bin/erl \
		$(PROTO_DIR)/usr/lib/$(MACH64)/erlang/bin/erl \
		$(PROTO_DIR)/usr/lib/erlang/releases/RELEASES \
		$(PROTO_DIR)/usr/lib/$(MACH64)/erlang/releases/RELEASES

clean::
	$(RM) -r documentation

test:	$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
