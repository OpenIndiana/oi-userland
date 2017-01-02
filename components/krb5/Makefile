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
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		Kerberos
# Encoding rule for MAJOR: MIT KerberosV5 x.y[.z] => MAJOR x
# Encoding rule for MINOR: MIT KerberosV5 x.y[.z] => MINOR $MAJOR.y
# Encoding rule for MICRO: MIT KerberosV5 x.y[.z] => MICRO $MINOR[.z]
COMPONENT_MAJOR=	1
COMPONENT_MINOR=	$(COMPONENT_MAJOR).14
COMPONENT_MICRO=	$(COMPONENT_MINOR).4

COMPONENT_VERSION=		$(COMPONENT_MICRO)
IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION).0

COMPONENT_PROJECT_URL=	http://web.mit.edu/kerberos/
COMPONENT_SRC=		krb5-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_HASH=	\
	sha256:03a61a4280c9161771fb39019085dbe6a57aa602080515ff93b43cd6137e0b95
COMPONENT_ARCHIVE_URL=	\
	$(COMPONENT_PROJECT_URL)dist/krb5/$(COMPONENT_MINOR)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/kerberos

TPNO=		31744

# Depends on S12-only header file in ON.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/common.mk

LINT_FLAGS += -I$(PROTOUSRINCDIR) -I$(PROTOUSRINCDIR)/kerberosv5 -I$(COMPONENT_DIR)/Solaris

# The configure script is not at the top of the source directory.
CONFIGURE_SCRIPT=	$(SOURCE_DIR)/src/configure

# We need to enable large file support and build PIC for our shared libraries
CFLAGS += $(CPP_LARGEFILES) $(CC_PIC)
CFLAGS += -errtags=yes -errwarn=%all
CFLAGS += -errwarn=no%E_STATEMENT_NOT_REACHED
CFLAGS += -errwarn=no%E_NO_IMPLICIT_DECL_ALLOWED
CFLAGS += -errwarn=no%E_EMPTY_TRANSLATION_UNIT
CFLAGS += -errwarn=no%E_EMPTY_INITIALIZER
CFLAGS += -errwarn=no%E_EMPTY_DECLARATION
CFLAGS += -errwarn=no%E_ENUM_VAL_OVERFLOWS_INT_MAX
CFLAGS += -errwarn=no%E_DEPRECATED_ATT
CFLAGS += -errwarn=no%E_INIT_SIGN_EXTEND
# XXX really E_ASSIGNMENT_TYPE_MISMATCH should not be treated as a warning but
# making this an error would require patching MIT code which I do not want to
# do at this moment.  Making this an error should be revisited after rebasing
# to MIT v1.15.
CFLAGS += -errwarn=no%E_ASSIGNMENT_TYPE_MISMATCH

# Include openldap headers instead of obsolete mozilla ldap headers.
CPPFLAGS += -I$(USRINCDIR)/openldap

# Temporary solution until we can fix this upstream with MIT, which currently
# depends on implicit binding of libc.  Here we explicitly link with libc to
# satisfy this dependency.
# If you make changes to LDFLAGS, check krb5-config and 052-krb5-config.patch.
LDFLAGS += -lc $(LD_Z_DEFS)

CONFIGURE_ENV += DEFKTNAME="FILE:$(ETCDIR)/krb5/krb5.keytab"
CONFIGURE_ENV += DEFCKTNAME="FILE:/var/user/%{username}/client.keytab"

# Other CONFIGURE_OPTIONS assignments coming from make-rules/configure.mk
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS.32 += --libexecdir=$(USRLIBDIR)
CONFIGURE_OPTIONS.64 += --libexecdir=$(USRLIBDIR)/$(MACH64)
CONFIGURE_OPTIONS += --includedir=$(USRINCDIR)/kerberosv5
CONFIGURE_OPTIONS += --with-crypto-impl=openssl
CONFIGURE_OPTIONS += --with-ldap
CONFIGURE_OPTIONS += --with-prng-alg=os
CONFIGURE_OPTIONS += --with-tcl=$(USRDIR)
CONFIGURE_OPTIONS += --without-system-verto
# Documented as with-audit-plugin, but it's really enable-audit-plugin
CONFIGURE_OPTIONS += --enable-audit-plugin=solaris

COMPONENT_PRE_CONFIGURE_ACTION = \
	cd $(SOURCE_DIR)/src/ && $(SOURCE_DIR)/src/util/reconf

PROTOULD = $(PROTOUSRLIBDIR)

COMPONENT_TEST_ARGS += LD_LIBRARY_PATH="$(PROTOULD):$(PROTOULD)/$(MACH64):"

# MIT's test suite is not well suited for master results processing/filtering
# but since the test implementation will return failure to the uland build,
# this is good enough.  The following disables master results processing.
COMPONENT_TEST_CREATE_TRANSFORMS=
COMPONENT_TEST_PERFORM_TRANSFORM=
COMPONENT_TEST_COMPARE=

# Audit plugin directory for Solaris
AUDIT_DIR = $(SOURCE_DIR)/src/plugins/audit/solaris

# We don't ship Solaris specific files as patches to ease maintenance.
# We rather copy the files to the right directories.
COMPONENT_PREP_ACTION= \
	$(CP) Solaris/getuid.c $(SOURCE_DIR)/src/lib/krb5/os/; \
	$(CP) Solaris/g_utils.c $(SOURCE_DIR)/src/lib/gssapi/mechglue/; \
	$(CP) Solaris/kadm_host_srv_names.c $(SOURCE_DIR)/src/lib/kadm5/; \
	$(CP) Solaris/kt_findrealm.c $(SOURCE_DIR)/src/lib/krb5/keytab/; \
	$(CP) Solaris/kt_solaris.c $(SOURCE_DIR)/src/lib/krb5/keytab/; \
	$(CP) Solaris/private/krb5/keytab/kt_solaris.h $(SOURCE_DIR)/src/lib/krb5/keytab/; \
	$(CP) Solaris/libgss_stubs.c $(SOURCE_DIR)/src/lib/gssapi/mechglue/; \
	$(CP) Solaris/missing_interfaces.c $(SOURCE_DIR)/src/lib/krb5/; \
	$(CP) Solaris/privacy_allowed.c $(SOURCE_DIR)/src/lib/krb5/; \
	$(CP) Solaris/prof_solaris.c $(SOURCE_DIR)/src/lib/krb5/; \
	$(CP) Solaris/private/krb5/prof_solaris.h $(SOURCE_DIR)/src/lib/krb5/; \
	$(CP) Solaris/rc_mem.c $(SOURCE_DIR)/src/lib/krb5/rcache; \
	$(CP) Solaris/rc_mem.h $(SOURCE_DIR)/src/lib/krb5/rcache; \
	$(CP) Solaris/safechown.c $(SOURCE_DIR)/src/lib/krb5/os; \
	$(CP) Solaris/util_ordering.c $(SOURCE_DIR)/src/lib/gssapi/generic; \
	$(MKDIR) -p $(AUDIT_DIR); $(CP) Solaris/audit/* $(AUDIT_DIR); \
	$(CP) Solaris/audit/kadmind_audit.* $(SOURCE_DIR)/src/kadmin/server;

# We move xdr_alloc.c and supporting dyn code from libgssrpc directly
# into libkadm5srv_mit. kadmind is the only consumer anyway.
SRCLIB=$(SOURCE_DIR)/src/lib
COMPONENT_PREP_ACTION += \
	$(CP) $(SRCLIB)/rpc/xdr_alloc.c $(SRCLIB)/kadm5/srv/; \
	$(CP) $(SRCLIB)/rpc/dyn.c $(SRCLIB)/kadm5/srv/; \
	$(CP) $(SRCLIB)/rpc/dyn.h $(SRCLIB)/kadm5/srv/; \
	$(CP) $(SRCLIB)/rpc/dynP.h $(SRCLIB)/kadm5/srv/; \
	$(CP) $(SRCLIB)/rpc/dyntest.c $(SRCLIB)/kadm5/srv/; \

# Common flags used to create the filter libs below
FILTLIBFLAGS = -G $(LD_B_DIRECT) $(LD_Z_DEFS) $(LD_Z_TEXT)

$(BUILD_32): COMPONENT_POST_BUILD_ACTION= \
	$(CC) -m32 -o $(BUILD_DIR)/$(MACH32)/lib/libgss.so.1 \
	    -hlibgss.so.1 $(FILTLIBFLAGS) -lc \
	    -M$(COMPONENT_DIR)/Solaris/libgss.mapfile-vers \
	    -z discard-unused=dependencies \
	    -L $(BUILD_DIR)/$(MACH32)/lib -lkrb5support \
	    $(BUILD_DIR)/$(MACH32)/lib/gssapi/mechglue/libgss_stubs.o && \
	$(CC) -m32 -o $(BUILD_DIR)/$(MACH32)/lib/libkrb5.so.1 \
	    -hlibkrb5.so.1 $(FILTLIBFLAGS) \
	    -M$(COMPONENT_DIR)/Solaris/libkrb5.mapfile-vers \
	    $(BUILD_DIR)/$(MACH32)/lib/krb5/missing_interfaces.o \
	    $(BUILD_DIR)/$(MACH32)/lib/krb5/privacy_allowed.o && \
	$(LD) -m32 -o $(BUILD_DIR)/$(MACH32)/lib/libkadm5clnt.so.1 \
	    -hlibkadm5clnt.so.1 $(FILTLIBFLAGS) \
	    -M$(COMPONENT_DIR)/Solaris/libkadm5clnt.mapfile-vers;

$(BUILD_64): COMPONENT_POST_BUILD_ACTION= \
	$(CC) -m64 -o $(BUILD_DIR)/$(MACH64)/lib/libgss.so.1 \
	    -hlibgss.so.1 $(FILTLIBFLAGS) -lc \
	    -M$(COMPONENT_DIR)/Solaris/libgss.mapfile-vers \
	    -z discard-unused=dependencies \
	    -L $(BUILD_DIR)/$(MACH64)/lib -lkrb5support \
	    $(BUILD_DIR)/$(MACH64)/lib/gssapi/mechglue/libgss_stubs.o && \
	$(CC) -m64 -o $(BUILD_DIR)/$(MACH64)/lib/libkrb5.so.1 \
	    -hlibkrb5.so.1 $(FILTLIBFLAGS) \
	    -M$(COMPONENT_DIR)/Solaris/libkrb5.mapfile-vers \
	    $(BUILD_DIR)/$(MACH64)/lib/krb5/missing_interfaces.o \
	    $(BUILD_DIR)/$(MACH64)/lib/krb5/privacy_allowed.o && \
	$(LD) -m64 -o $(BUILD_DIR)/$(MACH64)/lib/libkadm5clnt.so.1 \
	    -hlibkadm5clnt.so.1 $(FILTLIBFLAGS) \
	    -M$(COMPONENT_DIR)/Solaris/libkadm5clnt.mapfile-vers;

$(INSTALL_32): COMPONENT_POST_INSTALL_ACTION= \
	$(CP) $(BUILD_DIR)/$(MACH32)/lib/libgss.so.1 \
		$(PROTO_DIR)$(USRLIBDIR); \
	$(CP) $(BUILD_DIR)/$(MACH32)/lib/libkrb5.so.1 \
		$(PROTO_DIR)$(USRLIBDIR); \
	$(CP) $(BUILD_DIR)/$(MACH32)/lib/libkadm5clnt.so.1 \
		$(PROTO_DIR)$(USRLIBDIR);

$(INSTALL_64): COMPONENT_POST_INSTALL_ACTION= \
	$(MKDIR) -p $(PROTO_DIR)$(USRLIBDIR)/$(MACH64); \
	$(CP) $(BUILD_DIR)/$(MACH64)/lib/libgss.so.1 \
		$(PROTO_DIR)$(USRLIBDIR)/$(MACH64); \
	$(CP) $(BUILD_DIR)/$(MACH64)/lib/libkrb5.so.1 \
		$(PROTO_DIR)$(USRLIBDIR)/$(MACH64); \
	$(CP) $(BUILD_DIR)/$(MACH64)/lib/libkadm5clnt.so.1 \
		$(PROTO_DIR)$(USRLIBDIR)/$(MACH64);

REQUIRED_PACKAGES += developer/test/dejagnu
REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += network/dns/bind
REQUIRED_PACKAGES += service/network/ldap/openldap
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/gss
REQUIRED_PACKAGES += system/library/security/sasl/digestmd5
REQUIRED_PACKAGES += system/network/ldap/openldap
