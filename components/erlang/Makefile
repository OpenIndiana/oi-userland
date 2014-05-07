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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

PATH=$(SPRO_VROOT)/bin:$(JAVA_HOME)/bin:/usr/bin

COMPONENT_NAME=			erlang
COMPONENT_VERSION_MAJOR=	15
COMPONENT_VERSION_MINOR=	B
COMPONENT_VERSION_MICRO=	03
# IPS_COMPONENT_VERSION needs update whenever this is changed
COMPONENT_VERSION=	R$(COMPONENT_VERSION_MAJOR)$(COMPONENT_VERSION_MINOR)$(COMPONENT_VERSION_MICRO)
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.erlang.org/
COMPONENT_SRC_NAME=	otp_src
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-1.tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:4bccac86dd76aec050252e44276a0283a0df9218e6470cf042a9b9f9dfc9476c
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/erlang

# manpages
COMPONENT_NAME_1=	otp_doc_man
COMPONENT_SRC_1=	$(COMPONENT_NAME_1)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1)-1.tar.gz
COMPONENT_ARCHIVE_HASH_1=	\
    sha256:07980d8014c7cf8194b7078c137353f5083992add4663ced3dcba2ff91f228d8
COMPONENT_ARCHIVE_URL_1=	$(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE_1)

# HTML documentation
COMPONENT_NAME_2=	otp_doc_html
COMPONENT_SRC_2=	$(COMPONENT_NAME_2)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_2=	$(COMPONENT_SRC_2)-1.tar.gz
COMPONENT_ARCHIVE_HASH_2=	\
    sha256:d06f580f11d1303217a5c1cf8d68a98d7e01c535be934dcd430ecdc254f7572e
COMPONENT_ARCHIVE_URL_2=	$(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE_2)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# IPS_COMPONENT_VERSION is by default set to $(COMPONENT_VERSION) but it is not
# enough for us. We need to include the $(COMPONENT_SUBVERSION) somehow.
# Because the IPS_COMPONENT_VERSION cannot contain letters or leading zeroes
# we use mapping:
# R(major)(minor)(micro) - (major).(minor as number).(micro)
IPS_COMPONENT_VERSION=  $(COMPONENT_VERSION_MAJOR).2.3

# Built in SFW with gcc and builds cleanly now only with gcc
COMPILER = gcc

COMPONENT_BUILD_ENV +=	"HOME=/tmp"

CONFIGURE_OPTIONS += CPPFLAGS="$(CPPFLAGS) -I/usr/include/gd2"
CONFIGURE_OPTIONS += --enable-smp-support
CONFIGURE_OPTIONS += --enable-threads
# The HiPE portion is a bit sensitive, and only seems to work 64-bit on 
# amd64 (thus the variant.arch tagging in erlang.p5m). erts/config.log
# can be very interesting if issues occur. 
CONFIGURE_OPTIONS += --enable-hipe
CONFIGURE_OPTIONS += --with-ssl
CONFIGURE_OPTIONS += --enable-dynamic-ssl-lib

CONFIGURE_OPTIONS.64 += LIBS="-m64"
CONFIGURE_OPTIONS.64 += --with-wx-config=/usr/bin/$(MACH64)/wx-config

# Needed for 'set name=info.source-url' action in erlang-doc.p5m
PKG_MACROS += COMPONENT_ARCHIVE_URL_2=$(COMPONENT_ARCHIVE_URL_2) 

# Use cp(1) instead of cloney because erlang's 'install' target uses 'tar'
# to copy files and our tar doesn't handle long links by default.  Between
# the use of 'tar' and 'ld', a path adjustment wasn't an option due to the
# need for /usr/bin/ld and /usr/gnu/bin/tar.  Perhaps this can be looked
# at when we upgrade to a more current version.
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CP) -rp $(SOURCE_DIR)/. $(@D))
CONFIGURE_SCRIPT =	$(@D)/configure

COMPONENT_INSTALL_ARGS += INSTALL_PREFIX=$(PROTO_DIR)

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:	$(BUILD_32_and_64)

ifdef USERLAND_ARCHIVES
  EXTRA_ARCHIVE_PATH=$(USERLAND_ARCHIVES)
else
  EXTRA_ARCHIVE_PATH=../
endif

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
	$(UNPACK) $(UNPACK_ARGS) $(EXTRA_ARCHIVE_PATH)$(COMPONENT_ARCHIVE_1) && \
	$(UNPACK) $(UNPACK_ARGS) $(EXTRA_ARCHIVE_PATH)$(COMPONENT_ARCHIVE_2)
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
