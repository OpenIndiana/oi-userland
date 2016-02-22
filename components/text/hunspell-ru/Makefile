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

COMPONENT_NAME=		hunspell-ru
COMPONENT_VERSION=	20131101
IPS_COMPONENT_VERSION=	2013.11.1
COMPONENT_PROJECT_URL=	https://code.google.com/archive/p/hunspell-ru/
COMPONENT_SUMMARY=	Myspell and Hunspell spell dictionary files for Russian
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_FMRI=	library/myspell/dictionary/ru
COMPONENT_CLASSIFICATION	= System/Localizations

COMPONENT_SRC=            ru_RU_UTF-8_20131101
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH=        \
    sha256:c9c30ca305705691fea4810137763f3b790676aa534a5cd6dfc9b45659aa9408
COMPONENT_ARCHIVE_URL=   https://bitbucket.org/Shaman_Alex/russian-dictionary-hunspell/downloads/$(COMPONENT_ARCHIVE)
UNPACK_ARGS+=-r $(COMPONENT_SRC)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/ips.mk

DESTDIR=/usr/share/spell/hunspell
LINKDIR=/usr/share/spell/myspell
FFDIR=/usr/lib/firefox/dictionaries
TBDIR=/usr/lib/thunderbird/dictionaries

$(SOURCE_DIR)/.installed:	$(SOURCE_DIR)/.prep
	[ -d $(PROTO_DIR)$(DESTDIR) ] || mkdir -p $(PROTO_DIR)$(DESTDIR)
	[ -d $(PROTO_DIR)$(LINKDIR) ] || mkdir -p $(PROTO_DIR)$(LINKDIR)
	[ -d $(PROTO_DIR)$(FFDIR) ] || mkdir -p $(PROTO_DIR)$(FFDIR)
	[ -d $(PROTO_DIR)$(TBDIR) ] || mkdir -p $(PROTO_DIR)$(TBDIR)
	for file in $(COMPONENT_SRC)/*.{aff,dic}; do \
		newname=`basename $$(echo $$file |sed -e 's:-large::g')`;\
		cp $$file $(PROTO_DIR)$(DESTDIR)/$$newname; \
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
