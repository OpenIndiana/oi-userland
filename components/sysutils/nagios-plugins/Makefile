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
# Copyright 2023 Marcel Telka
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		nagios-plugins
COMPONENT_VERSION =		2.4.11
COMPONENT_SUMMARY =		Nagios Plugins
COMPONENT_PROJECT_URL =		https://github.com/nagios-plugins/nagios-plugins
COMPONENT_FMRI =		system/management/nagios/plugins
COMPONENT_CLASSIFICATION =	System/Enterprise Management
COMPONENT_SRC =			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL =		\
	$(COMPONENT_PROJECT_URL)/releases/download/release-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH =	\
	sha256:1a68356c8a0d16f393857eba3256e3928d043a9ae2a4ad839bd4681771fe1c1a
COMPONENT_LICENSE =		GPL-3.0-only
COMPONENT_LICENSE_FILE =	COPYING

include $(WS_MAKE_RULES)/common.mk

# This is needed to be able to run tests
COMPONENT_PRE_CONFIGURE_ACTION += ( $(CLONEY) $(SOURCE_DIR) $(@D) )

# force needed rpath
LD_OPTIONS += -R$(PG_LIBDIR)
LD_OPTIONS += -R$(MYSQL_LIBDIR)

# specify where to find openssl
CFLAGS  += -I$(OPENSSL_INCDIR)
LDFLAGS += -L$(OPENSSL_LIBDIR)

CONFIGURE_OPTIONS +=	--libexecdir=$(CONFIGURE_PREFIX)/libexec/nagios-plugins
CONFIGURE_OPTIONS +=	--enable-libtap
CONFIGURE_OPTIONS +=	--with-pgsql=$(PG_HOME)
CONFIGURE_OPTIONS +=	--with-mysql=$(MYSQL_HOME)
CONFIGURE_OPTIONS +=	--without-dbi
CONFIGURE_OPTIONS +=	--without-radius
CONFIGURE_OPTIONS +=	--without-smbclient-command
CONFIGURE_OPTIONS +=	--without-qmail-qstat-command
CONFIGURE_OPTIONS +=	--without-smtpctl-command

# pst3 needs to be manually installed
COMPONENT_POST_INSTALL_ACTION += $(CP) $(@D)/plugins-root/pst3 $(PROTOUSRDIR)/libexec/nagios-plugins ;

# charset.alias is provided by library/glib2/charset-alias package
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRLIBDIR.$(BITS))/charset.alias ;

#
# To run tests successfully you need to fulfil these prerequisites:
#
# 1) run tests as regular (non-root) user with the net_icmpaccess additional privileges:
# 	usermod -K defaultpriv=basic,net_icmpaccess USERNAME
# 2) the machine must be connected to internet
# 3) there should be no 10.0.0.1 host reachable
# 4) sshd must be running on localhost:22 (service svc:/network/ssh:default must be online)
# 5) you must be able to ssh to localhost using a key in ~/.ssh/id_dsa:
#	- create the key (without password):
#		ssh-keygen -q -t ed25519 -N "" -f ~/.ssh/id_dsa
#	- add the key to your ~/.ssh/authorized_keys:
#		chmod +w ~/.ssh/authorized_keys
#		cat ~/.ssh/id_dsa.pub >> ~/.ssh/authorized_keys
#		chmod -w ~/.ssh/authorized_keys
#	- add the key to your authentication agent:
#		ssh-add ~/.ssh/id_dsa
#	- disable host authentication for localhost:
#		echo 'NoHostAuthenticationForLocalhost yes' > ~/.ssh/config
# 6) prepare two filesystems with different free space (run following as root):
#	mkdir /tmp/nagios-plugins-test
#	cd /tmp/nagios-plugins-test
#	mkfile 100m f1 f2
#	lofiadm -a f1 /dev/lofi/101
#	lofiadm -a f2 /dev/lofi/102
#	mkfs -F ufs -onbpi=65536 /dev/rlofi/101 204600
#	mkfs -F ufs -onbpi=65536 /dev/rlofi/102 204600
#	mkdir 1 2
#	mount /dev/lofi/101 1
#	mount /dev/lofi/102 2
#	mkfile 10m 1/{a..e}
#	touch 1/{1..1000}
# 7) mariadb server must be running on localhost (service svc:/application/database/mariadb:version_106 must be online)
# 8) grant the SLAVE MONITOR rights (run following as root):
# 	mysql -e 'GRANT SLAVE MONITOR ON *.* TO ""@localhost' mysql
# 9) NTP service must be fully working on localhost (service svc:/network/ntp:default must be online)
# 10) SNMP service must be running on localhost (service svc:/application/management/net-snmp:default must be online)
#
COMPONENT_TEST_TARGETS = test

# Make sure we test with the well known configuration
COMPONENT_TEST_ENV += NPTEST_CACHE=$(COMPONENT_DIR)/files/NPTest.cache

# Normalize test results
COMPONENT_TEST_TRANSFORMS += "-e 's/,  *[0-9]* wallclock.*//'"	# delete timings
COMPONENT_TEST_TRANSFORMS += "-e '/^make\[/d'"			# delete make logs

# Manually added dependencies
REQUIRED_PACKAGES += $(MYSQL_CLIENT_PKG)
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)
REQUIRED_PACKAGES += diagnostic/fping
TEST_REQUIRED_PACKAGES.perl += library/perl-5/crypt-x509
TEST_REQUIRED_PACKAGES.perl += library/perl-5/libwww-perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/text-glob
TEST_REQUIRED_PACKAGES.perl += library/perl-5/timedate

# Auto-generated dependencies
REQUIRED_PACKAGES += $(MYSQL_LIBRARY_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
