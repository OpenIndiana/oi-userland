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
# Copyright (c) 2023 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		hunspell-pl
COMPONENT_VERSION=	2023.6.1
HUMAN_VERSION=		20230601
COMPONENT_PROJECT_URL=	https://sjp.pl/slownik/en/
COMPONENT_SUMMARY=	Myspell and Hunspell spell dictionary files for Polish
COMPONENT_LICENSE=	MPL1.1
COMPONENT_FMRI=		library/myspell/dictionary/pl
COMPONENT_CLASSIFICATION= System/Localizations
COMPONENT_SRC=			sjp-myspell-pl-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH=	sha256:5c1a4422622fb594754423dc9dbd8c413f1657780720a7564c94b5f6345d9807
COMPONENT_ARCHIVE_URL=	https://sjp.pl/slownik/ort/$(COMPONENT_ARCHIVE)
UNPACK_ARGS+=	-r $(COMPONENT_SRC)

COMPONENT_POST_UNPACK_ACTION= unzip $(SOURCE_DIR)/pl_PL.zip -d $(SOURCE_DIR)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

DESTDIR=/usr/share/spell/hunspell
LINKDIR=/usr/share/spell/myspell
FFDIR=/usr/lib/firefox/dictionaries
TBDIR=/usr/lib/thunderbird/dictionaries

$(SOURCE_DIR)/.installed:	$(SOURCE_DIR)/.prep
	[ -d $(PROTO_DIR)$(DESTDIR) ] || mkdir -p $(PROTO_DIR)$(DESTDIR)
	[ -d $(PROTO_DIR)$(LINKDIR) ] || mkdir -p $(PROTO_DIR)$(LINKDIR)
	[ -d $(PROTO_DIR)$(FFDIR) ] || mkdir -p $(PROTO_DIR)$(FFDIR)
	[ -d $(PROTO_DIR)$(TBDIR) ] || mkdir -p $(PROTO_DIR)$(TBDIR)
	cp $(COMPONENT_SRC)/pl_PL.dic $(PROTO_DIR)$(DESTDIR)
	cp $(COMPONENT_SRC)/pl_PL.aff $(PROTO_DIR)$(DESTDIR)
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

# Build dependencies
REQUIRED_PACKAGES+= text/aspell
