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
# Copyright 2016 Alexander Pyhalov
# Copyright 2019 Michal Nowak
# Copyright 2021 Till Wegmueller
# Copyright 2022 David Stes
#

BUILD_STYLE = archive
BUILD_BITS = NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ca-certificates
COMPONENT_VERSION_MAJOR= 3
COMPONENT_VERSION_MINOR= 89
COMPONENT_VERSION=	$(COMPONENT_VERSION_MAJOR).$(COMPONENT_VERSION_MINOR)
HUMAN_VERSION= 20230311
COMPONENT_SUMMARY=	Common CA certificates
COMPONENT_SRC=		nss-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:55c37a3f4da010d0574fb8b39264cb1e7b4ce9e6c2954c1c7ecf9f41ee00bed5
COMPONENT_ARCHIVE_URL=	https://ftp.mozilla.org/pub/security/nss/releases/NSS_$(COMPONENT_VERSION_MAJOR)_$(COMPONENT_VERSION_MINOR)_RTM/src/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://developer.mozilla.org/en-US/docs/Mozilla/Projects/NSS
COMPONENT_FMRI=		crypto/ca-certificates
COMPONENT_LICENSE=	MPLv2.0
COMPONENT_LICENSE_FILE=	nss/COPYING

BUILD_TARGET = $(BUILD_$(MK_BITS))
INSTALL_TARGET = $(INSTALL_$(MK_BITS))

include $(WS_MAKE_RULES)/common.mk

PKG_OPTIONS += -I $(COMPONENT_DIR)

CLEAN_PATHS += $(BUILD_DIR) $(PROTO_DIR)

$(BUILD_$(MK_BITS)): $(BUILD_DIR_$(MK_BITS))/.certs_renamed

# some filenames are UTF-8 not 7bit ASCII because 
# certdata.txt has CKA_LABEL UTF8 entries that are not 7bit ASCII
# for example NetLock_Arany_(Class_Gold)_Ftanstvny.pem has a small letter o
# which uses the Hungarian small latin o with double acute (U + 0151)
# to avoid packaging UTF-8 non-ASCII paths in /etc, process by iconv
# see Illumos bug #14510 and bug #11625

$(BUILD_DIR_$(MK_BITS))/.certs_renamed: $(BUILD_DIR_$(MK_BITS))/.certs_extracted
	for i in $(@D)/xx*; do \
		FILE_LEN=$$(wc -l  "$$i" |awk ' { print $$1; }' ); \
		BEGIN=$$(grep -n "BEGIN CERT" "$$i" |cut -d : -f 1); \
		TAIL=$$(($$FILE_LEN-$$BEGIN+1)); \
		NAME=$$(head -1 "$$i" | tr ' ' '_' | \
			iconv -c -f UTF-8 -t ASCII | \
			tr -d '?' | tr -d '(' | tr -d ')' \
		); \
		tail -n $$TAIL  "$$i" > $(@D)/$${NAME}.pem ;\
	done
	$(TOUCH) $@

$(BUILD_DIR_$(MK_BITS))/.certs_extracted: $(BUILD_DIR_$(MK_BITS))/ca-bundle.processed
	cd $(@D) &&\
	NUM=$$(awk '/BEGIN/{n++} END{print n-2}' $(@D)/ca-bundle.processed) &&\
	csplit -s -n 3 $(@D)/ca-bundle.processed '/END CERT/1' "{$$NUM}"
	$(TOUCH) $@

$(BUILD_DIR_$(MK_BITS))/ca-bundle.processed: $(BUILD_DIR_$(MK_BITS))/ca-bundle.crt
	grep -v '^#' $(@D)/ca-bundle.crt | grep -v '^$$' > $@

$(BUILD_DIR_$(MK_BITS))/ca-bundle.crt: $(BUILD_DIR_$(MK_BITS))/certdata.txt
	cd $(@D) && $(PERL) $(COMPONENT_DIR)/files/mk-ca-bundle.pl -n
	

$(BUILD_DIR_$(MK_BITS))/certdata.txt: $(SOURCE_DIR)/nss/lib/ckfw/builtins/certdata.txt
	$(MKDIR) $(@D)
	$(CP) $(SOURCE_DIR)/nss/lib/ckfw/builtins/certdata.txt $@

$(SOURCE_DIR)/nss/lib/ckfw/builtins/certdata.txt: $(SOURCE_DIR)/.prep

$(INSTALL_$(MK_BITS)):	$(BUILD_$(MK_BITS))
	$(MKDIR) $(PROTO_DIR)/etc/certs/CA $(PROTO_DIR)/etc/openssl/certs
	$(CP) $(@D)/*.pem $(PROTO_DIR)/etc/certs/CA/
	cd $(PROTO_DIR)/etc/certs/CA &&\
	for i in *.pem ; do  \
	   HASH=$$(openssl x509 -noout -hash -in $$i); \
           ln -fs ../../certs/CA/$${i} ../../openssl/certs/$${HASH}.0; \
	done; 
	touch $@
	
REQUIRED_PACKAGES += file/gnu-coreutils
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += library/perl-5/libwww-perl
REQUIRED_PACKAGES += text/gawk
REQUIRED_PACKAGES += text/gnu-grep
REQUIRED_PACKAGES += system/library/iconv/utf-8
# Auto-generated dependencies
REQUIRED_PACKAGES += system/ca-certificates
