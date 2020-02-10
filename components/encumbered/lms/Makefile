#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2017 Rouven Weiler
#

BUILD_BITS=			32
BUILD_STYLE=			archive

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		lms
COMPONENT_FMRI =		service/network/lms
COMPONENT_VERSION =		7.9.2
COMPONENT_PROJECT_URL =		https://github.org/Logitech/slimserver.git
COMPONENT_SUMMARY =		Logitech Media Server
COMPONENT_LICENSE =		GPLv2
COMPONENT_LICENSE_FILE =	$(COMPONENT_NAME).license
COMPONENT_CLASSIFICATION =	System/Media

COMPONENT_REPO_NAME =		slimserver
COMPONENT_GIT_COMMIT_HASH =	9b9f2d148bae0021913bbe9642cce8dc83a3ad00
COMPONENT_SRC =			$(COMPONENT_REPO_NAME)-$(COMPONENT_GIT_COMMIT_HASH)
COMPONENT_ARCHIVE =		$(COMPONENT_REPO_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	sha256:0e787e633ce002f5fe59da4ba71cfbfe3b43ece5a40490b58c88c2b44061fbc5
COMPONENT_ARCHIVE_URL =		https://github.com/Logitech/$(COMPONENT_REPO_NAME)/archive/$(COMPONENT_GIT_COMMIT_HASH).tar.gz

COMPONENT_REPO_NAME_1 =		slimserver-vendor
COMPONENT_GIT_COMMIT_HASH_1 =	1a6dc71ba3470c389738fc5f127ba8a17291700b
COMPONENT_SRC_1 =		$(COMPONENT_REPO_NAME_1)-$(COMPONENT_GIT_COMMIT_HASH_1)
COMPONENT_ARCHIVE_1 =		$(COMPONENT_REPO_NAME_1)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH_1 =	sha256:5e5c328ce5f6174eb847f6f833b2f7f980fae967b240d3843dd65993a0ae0db3
COMPONENT_ARCHIVE_URL_1 =	https://github.com/Logitech/$(COMPONENT_REPO_NAME_1)/archive/$(COMPONENT_GIT_COMMIT_HASH_1).tar.gz

PERL_VERSION =			5.22

BUILD_TARGET =			$(BUILD_DIR)/$(COMPONENT_NAME)/.built $(BUILD_DIR)/$(COMPONENT_NAME)-vendor/.built

INSTALL_TARGET =		$(BUILD_DIR)/$(COMPONENT_NAME)/.installed

include $(WS_MAKE_RULES)/common.mk

BUILDME_ENV +=                  MAKE=$(GMAKE)
BUILDME_ENV +=			PATH=$(dir $(CC)):$(PATH)
BUILDME_ENV +=                  LANG=""
BUILDME_ENV +=			CC="$(CC)"
BUILDME_ENV +=			LANG=""
BUILDME_ENV +=			CFLAGS="$(PERL_OPTIMIZE)"

LMS_PERL_BUILD_ARCH =		$(shell $(PERL) -MConfig -le 'print $Config{archname}')
LMS_INSTALL_DIR =		/opt/lms-$(COMPONENT_VERSION)

COMPONENT_POST_UNPACK_ACTION =	($(FIND) $(COMPONENT_DIR)/$(COMPONENT_REPO_NAME)-$(COMPONENT_GIT_COMMIT_HASH)/CPAN/arch \
                                    -mindepth 1 -maxdepth 1 ! \( -name "5." -o -name "$(PERL_VERSION)" \) -type d -exec rm -rf {} + ; \
				$(FIND) $(COMPONENT_DIR)/$(COMPONENT_REPO_NAME)-$(COMPONENT_GIT_COMMIT_HASH)/CPAN/arch \
                                    -mindepth 1 -name "*-*" -type d -exec rm -rf {} + ; \
                                $(FIND) $(COMPONENT_DIR)/$(COMPONENT_REPO_NAME)-$(COMPONENT_GIT_COMMIT_HASH)/Bin \
                                    -mindepth 1 -maxdepth 1 ! \( -name "$(PERL_BUILD_ARCH)" \) -type d -exec rm -rf {} +) 

COMPONENT_POST_INSTALL_ACTION +=	$(MKDIR) $(PROTODIR)$(VARDIR)/lmsd/log ; \
					$(MKDIR) $(PROTODIR)$(VARDIR)/lmsd/cache ; \
					$(MKDIR) $(PROTODIR)$(VARDIR)/lmsd/prefs ; \
					(sed -i "s@###LMS_INSTALL_DIR###@$(LMS_INSTALL_DIR)@g" $(PROTODIR)/lib/svc/manifest/network/lmsd.xml)

$(BUILD_DIR)/$(COMPONENT_NAME)/.built:	$(COMPONENT_DIR)/$(COMPONENT_REPO_NAME)-$(COMPONENT_GIT_COMMIT_HASH)/.prep
					$(RM) -r $(@D) ; $(MKDIR) $(@D) 
					$(CLONEY) $(COMPONENT_DIR)/$(COMPONENT_REPO_NAME)-$(COMPONENT_GIT_COMMIT_HASH) $(@D) 
					$(TOUCH) $@

$(BUILD_DIR)/$(COMPONENT_NAME)-vendor/.built:	$(COMPONENT_DIR)/$(COMPONENT_REPO_NAME_1)-$(COMPONENT_GIT_COMMIT_HASH_1)/.patched
						$(RM) -r $(@D) ; $(MKDIR) $(@D)
						$(CLONEY) $(COMPONENT_DIR)/$(COMPONENT_REPO_NAME_1)-$(COMPONENT_GIT_COMMIT_HASH_1) $(@D)
						(cd $(@D)/CPAN ; $(ENV) $(BUILDME_ENV) $(CONFIG_SHELL) \
						 ./buildme.sh -i $(BUILD_DIR)/lms -p $(PERL) ; \
						 $(ENV) $(BUILDME_ENV) $(CONFIG_SHELL) \
						 ./buildme.sh -i $(BUILD_DIR)/lms -p $(PERL) IO::Socket::SSL)
						$(TOUCH) $@

$(BUILD_DIR)/lms/.installed:	$(BUILD_DIR)/lms/.built $(BUILD_DIR)/lms-vendor/.built
				($(MKDIR) -p $(PROTO_DIR)$(LMS_INSTALL_DIR) ; \
				$(CP) -r $(BUILD_DIR)/lms/* $(PROTO_DIR)$(LMS_INSTALL_DIR))
				$(TOUCH) $@

# Set the pkg... path to search files in ./Solaris/ dir (mainly the SMF manifests are there)
PKG_PROTO_DIRS +=		$(COMPONENT_DIR)

clean::
				$(RM) -r $(BUILD_DIR) $(PROTO_DIR)

# Runtime dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += system/library/math

# Dependencies for build
REQUIRED_PACKAGES += network/rsync
