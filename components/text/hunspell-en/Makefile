#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		hunspell-en
COMPONENT_VERSION=	2016.01.19
IPS_COMPONENT_VERSION=	2016.1.19
COMPONENT_PROJECT_URL=	http://wordlist.aspell.net/
COMPONENT_SUMMARY=	Myspell and Hunspell spell dictionary files for English
COMPONENT_LICENSE=	BSD-like
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_FMRI=	library/myspell/dictionary/en
COMPONENT_CLASSIFICATION	= System/Localizations

PATCH_EACH_ARCHIVE=1

COMPONENT_SRC=            hunspell-en_US-large-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH=        \
    sha256:1c8a7a5a993313620a7d96e74e5c45f4df7ab9ad0141764ffeea66db9bfc089f
COMPONENT_ARCHIVE_URL=   https://sourceforge.net/projects/wordlist/files/speller/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
UNPACK_ARGS+=-r $(COMPONENT_SRC)

COMPONENT_SRC_1=            hunspell-en_GB-large-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_1=        $(COMPONENT_SRC_1).zip
COMPONENT_ARCHIVE_HASH_1=        \
    sha256:edcca9b78ae8923e6209db523355b4a91ac6d9daad94df12413498b4e5069719
COMPONENT_ARCHIVE_URL_1=   https://sourceforge.net/projects/wordlist/files/speller/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE_1)
UNPACK_ARGS_1+=-r $(COMPONENT_SRC_1)

COMPONENT_SRC_2=            hunspell-en_CA-large-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_2=        $(COMPONENT_SRC_2).zip
COMPONENT_ARCHIVE_HASH_2=        \
    sha256:04fd5dcfdca048e18640a1d420077473ab105431fc14ebe307bda452732abf6c
COMPONENT_ARCHIVE_URL_2=   https://sourceforge.net/projects/wordlist/files/speller/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE_2)
UNPACK_ARGS_2+=-r $(COMPONENT_SRC_2)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

DESTDIR=/usr/share/spell/hunspell
LINKDIR=/usr/share/spell/myspell
FFDIR=/usr/lib/firefox/dictionaries
TBDIR=/usr/lib/thunderbird/dictionaries

GBALIASES=      en_AG en_AU en_BS en_BW en_BZ en_DK en_GH en_HK en_IE en_IN \
                en_JM en_NA en_NG en_NZ en_SG en_TT en_ZA en_ZW
USALIASES=      en_PH

$(SOURCE_DIR)/.installed:	$(SOURCE_DIR)/.prep
	[ -d $(PROTO_DIR)$(DESTDIR) ] || mkdir -p $(PROTO_DIR)$(DESTDIR)
	[ -d $(PROTO_DIR)$(LINKDIR) ] || mkdir -p $(PROTO_DIR)$(LINKDIR)
	[ -d $(PROTO_DIR)$(FFDIR) ] || mkdir -p $(PROTO_DIR)$(FFDIR)
	[ -d $(PROTO_DIR)$(TBDIR) ] || mkdir -p $(PROTO_DIR)$(TBDIR)
	for file in $(COMPONENT_SRC)/*.{aff,dic} $(COMPONENT_SRC_1)/*.{aff,dic} $(COMPONENT_SRC_2)/*.{aff,dic}; do \
		newname=`basename $$(echo $$file |sed -e 's:-large::g')`;\
		cp $$file $(PROTO_DIR)$(DESTDIR)/$$newname; \
	done
	for alias in $(GBALIASES); do\
		ln -fs en_GB.aff $(PROTO_DIR)$(DESTDIR)/$$alias.aff; \
		ln -fs en_GB.dic $(PROTO_DIR)$(DESTDIR)/$$alias.dic; \
        done
	for alias in $(USALIASES); do\
		ln -fs en_US.aff $(PROTO_DIR)$(DESTDIR)/$$alias.aff; \
		ln -fs en_US.dic $(PROTO_DIR)$(DESTDIR)/$$alias.dic;\
        done
	for file in `cd $(PROTO_DIR)/$(DESTDIR)/; ls`;  do\
		ln -fs ../../../..$(DESTDIR)/$$file $(PROTO_DIR)$(LINKDIR)/$$file; \
		ln -fs ../../../..$(DESTDIR)/$$file $(PROTO_DIR)$(FFDIR)/$$file; \
		ln -fs ../../../..$(DESTDIR)/$$file $(PROTO_DIR)$(TBDIR)/$$file; \
	done
	$(TOUCH) $@

build: $(SOURCE_DIR)/.prep

install: $(SOURCE_DIR)/.installed

clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)
