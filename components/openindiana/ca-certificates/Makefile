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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ca-certificates
COMPONENT_VERSION_MAJOR=3
COMPONENT_VERSION_MINOR=45
COMPONENT_VERSION=	$(COMPONENT_VERSION_MAJOR).$(COMPONENT_VERSION_MINOR)
IPS_COMPONENT_VERSION=	1.0
COMPONENT_REVISION=	7
COMPONENT_SUMMARY=	Common CA certificates
COMPONENT_SRC=		nss-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:112f05223d1fde902c170966bfc6f011b24a838be16969b110ecf2bb7bc24e8b
COMPONENT_ARCHIVE_URL= \
	https://ftp.mozilla.org/pub/security/nss/releases/NSS_$(COMPONENT_VERSION_MAJOR)_$(COMPONENT_VERSION_MINOR)_RTM/src/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://developer.mozilla.org/en-US/docs/Mozilla/Projects/NSS
COMPONENT_FMRI=		crypto/ca-certificates
COMPONENT_LICENSE=	MPLv2.0
COMPONENT_LICENSE_FILE=	nss/COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

PKG_OPTIONS+= -I $(COMPONENT_DIR)

CLEAN_PATHS += $(BUILD_DIR) $(PROTO_DIR)

$(BUILD_32): $(BUILD_DIR_32)/.certs_renamed

$(BUILD_DIR_32)/.certs_renamed: $(BUILD_DIR_32)/.certs_extracted
	for i in $(BUILD_DIR_32)/xx*; do \
		FILE_LEN=$$(wc -l  "$$i" |awk ' { print $$1; }' ); \
		BEGIN=$$(grep -n "BEGIN CERT" "$$i" |cut -d : -f 1); \
		TAIL=$$(($$FILE_LEN-$$BEGIN+1)); \
		NAME=$$(head -1 "$$i" | tr ' ' '_'); \
		tail -n $$TAIL  "$$i" > $(BUILD_DIR_32)/$${NAME}.pem ;\
	done
	$(TOUCH) $@

$(BUILD_DIR_32)/.certs_extracted: $(BUILD_DIR_32)/ca-bundle.processed
	cd $(BUILD_DIR_32) &&\
	NUM=$$(awk '/BEGIN/{n++} END{print n-2}' $(BUILD_DIR_32)/ca-bundle.processed) &&\
	csplit -s -n 3 $(BUILD_DIR_32)/ca-bundle.processed '/END CERT/1' "{$$NUM}"
	$(TOUCH) $@

$(BUILD_DIR_32)/ca-bundle.processed: $(BUILD_DIR_32)/ca-bundle.crt
	grep -v '^#' $(BUILD_DIR_32)/ca-bundle.crt | grep -v '^$$' > $@

$(BUILD_DIR_32)/ca-bundle.crt: $(BUILD_DIR_32)/certdata.txt
	cd $(BUILD_DIR_32) && $(PERL) $(COMPONENT_DIR)/files/mk-ca-bundle.pl -n
	

$(BUILD_DIR_32)/certdata.txt: $(SOURCE_DIR)/nss/lib/ckfw/builtins/certdata.txt
	$(MKDIR)  $(BUILD_DIR_32)
	$(CP) $(SOURCE_DIR)/nss/lib/ckfw/builtins/certdata.txt $@

$(SOURCE_DIR)/nss/lib/ckfw/builtins/certdata.txt: $(SOURCE_DIR)/.prep

$(INSTALL_32):	$(BUILD_32)
	$(MKDIR) $(PROTO_DIR)/etc/certs/CA $(PROTO_DIR)/etc/openssl/certs
	$(CP) $(BUILD_DIR_32)/*.pem $(PROTO_DIR)/etc/certs/CA/
	cd $(PROTO_DIR)/etc/certs/CA &&\
	for i in *.pem ; do  \
	   HASH=$$(openssl x509 -noout -hash -in $$i); \
           ln -fs ../../certs/CA/$${i} ../../openssl/certs/$${HASH}.0; \
	done; 
	touch $@
	
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += file/gnu-coreutils
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += library/perl-5/libwww-perl-522  
REQUIRED_PACKAGES += text/gawk
REQUIRED_PACKAGES += text/gnu-grep
# Auto-generated dependencies
