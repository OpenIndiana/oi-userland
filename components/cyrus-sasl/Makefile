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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

PATH=/usr/gnu/bin:$(SPRO_VROOT)/bin:/usr/bin

ifeq   ($(strip $(PARFAIT_BUILD)),yes)
PATH=$(PARFAIT_TOOLS):/usr/gnu/bin:$(SPRO_VROOT)/bin:/usr/bin
endif

COMPONENT_NAME=		cyrus-sasl


#
# If you update the COMPONENT_VERSION, you should make a corresponding change
# in the dependency at the bottom of the openldap/openldap.p5m file.
#
COMPONENT_VERSION=	2.1.26
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL= ftp://ftp.cyrusimap.org/cyrus-sasl
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:8fbc5136512b59bb793657f36fadda6359cae3b08f01fd16b3d406f1345b7bc3
COMPONENT_ARCHIVE_URL= $(COMPONENT_PROJECT_URL)/$(COMPONENT_ARCHIVE)

# Check DONOTUSE items when updating the version and hash
DONOTUSE= $(SOURCE_DIR)/mac  $(SOURCE_DIR)/dlcompat-20010505

COMPONENT_BUGDB=	library/libsasl

TPNO=			21351

CC += $(CC_BITS)

SASL2.32 = $(USRLIBDIR)/sasl2
SASL2.64 = $(USRLIBDIR)/sasl2/$(MACH64)
SASL_CONFDIR = /etc/sasl
PROTO_CONFDIR = $(PROTO_DIR)$(SASL_CONFDIR)

include $(WS_TOP)/make-rules/prep.mk
CONFIGURE_DEFAULT_DIRS=no
include $(WS_TOP)/make-rules/configure.mk

# Migrated from ON in S12, including stuff from system/header, so this
# cannot be installed on an S11 box.
ifeq ($(BUILD_TYPE), evaluation)
PUBLISH_STAMP=
endif

include $(WS_TOP)/make-rules/ips.mk
include $(WS_TOP)/make-rules/lint-libraries.mk

CONFIGURE_ENV +=  "CPPFLAGS=$(CPPFLAGS) -I/usr/include/openldap"
CONFIGURE_OPTIONS += --with-cflags="$(CFLAGS)"
CONFIGURE_OPTIONS += LDFLAGS="$(LDFLAGS) -lbsm -lscf -lresolv"
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --enable-auth-sasldb=yes
CONFIGURE_OPTIONS += --with-dblib=berkeley
CONFIGURE_OPTIONS += --with-saslauthd=$(USRSBINDIR)/saslauthd
CONFIGURE_OPTIONS += --with-gss_impl=seam
CONFIGURE_OPTIONS += --with-gnu-ld=no
CONFIGURE_OPTIONS.32 += --with-plugindir=$(SASL2.32)
CONFIGURE_OPTIONS.64 += --with-plugindir=$(SASL2.64)
CONFIGURE_OPTIONS.32 += --with-sasldir=$(SASL2.32)
CONFIGURE_OPTIONS.64 += --with-sasldir=$(SASL2.64)
CONFIGURE_OPTIONS += --with-ipctype=doors
CONFIGURE_OPTIONS += --with-ldap=$(USRDIR)
CONFIGURE_OPTIONS += --enable-sample=yes
CONFIGURE_OPTIONS += --with-configdir=$(ETCDIR)/sasl

PKG_PROTO_DIRS += $(SOURCE_DIR)/doc $(COMPONENT_DIR)/Solaris

# TODO -- make these work or rule them out in Phase II, second integration
#CONFIGURE_OPTIONS += --with-dbpath=$(SASL_CONFDIR)/sasl2db
#CONFIGURE_OPTIONS += --with-mysql=$?????
#CONFIGURE_OPTIONS += --enable-sql=yes
#CONFIGURE_OPTIONS += --enable-ldapdb=yes
# postfix or AD might need --enable-login and --enable-ntlm
#CONFIGURE_OPTIONS += --enable-login=yes
#CONFIGURE_OPTIONS += --enable-ntlm=yes
# test xalias levels:
#CFLAGS += -xalias_level=strict

LINTINCDIR= $(SOURCE_DIR)/include/sasl

INCLIST= hmac-md5.h \
	md5.h \
	md5global.h \
	prop.h \
	sasl.h \
	saslplug.h \
	saslutil.h

CFG_COMPILE=/usr/share/automake-1.15

COMPONENT_PREP_ACTION = ( cd $(@D) &&  \
		( cd config && ln -s $(CFG_COMPILE)/compile . ) ; \
		( cd saslauthd/config && ln -s $(CFG_COMPILE)/compile . ); \
		$(AUTORECONF) -d -m --force -v \
		-I $(COMPONENT_DIR)/m4   \
		-I $(SOURCE_DIR)/cmulocal \
		-I $(SOURCE_DIR)/config ; \
	    )

# Remove some things we don't use and aren't in the TPNO
# Make an include/sasl directory to make llib-lsasl2 match llib-lsasl2.ln
COMPONENT_PRE_CONFIGURE_ACTION = \
	-$(RM) -r $(DONOTUSE) ; \
	$(MKDIR) $(LINTINCDIR) ; \
	( cd $(LINTINCDIR) && \
	    ( for i in $(INCLIST) ; do \
	    	ln -s ../$$i $$i  ; \
	    done ) \
	)

INSTALL_32 +=	$(PROTOUSRLIBDIR)/libsasl.so.1
INSTALL_64 +=	$(PROTOUSRLIBDIR64)/libsasl.so.1


# common targets
build:		$(BUILD_32_and_64)
configure:      $(BUILD_DIR_32)/.configured $(BUILD_DIR_64)/.configured
install:	build $(INSTALL_32_and_64)
publish:	install
test:		$(NO_TESTS)
system-test:	$(SYSTEM_TESTS_NOT_IMPLEMENTED)

$(BUILD_32):  	COMPONENT_POST_BUILD_ACTION = \
    $(LD) -F libsasl2.so.3 -o $(BUILD_DIR)/$(MACH32)/lib/.libs/libsasl.so.1 \
    -G -hlibsasl.so.1 -Bdirect -z defs -M$(COMPONENT_DIR)/mapfile 

$(BUILD_64):	COMPONENT_POST_BUILD_ACTION = \
     $(LD) -F libsasl2.so.3 -64 -G \
    -o $(BUILD_DIR)/$(MACH64)/lib/.libs/libsasl.so.1 \
    -hlibsasl.so.1 -Bdirect -Wl,-zdefs -Wl,-M$(COMPONENT_DIR)/mapfile

$(PROTOUSRLIBDIR)/libsasl.so.1:	$(BUILD_DIR)/$(MACH32)/lib/.libs/libsasl.so.1	
	$(CP) $< $@

$(PROTOUSRLIBDIR64)/libsasl.so.1:	$(BUILD_DIR)/$(MACH64)/lib/.libs/libsasl.so.1	
	$(CP) $< $@

ASLR_MODE = $(ASLR_ENABLE)
BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += developer/build/automake-115
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += security/kerberos-5
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/gss
