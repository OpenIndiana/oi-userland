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

COMPONENT_NAME=		hunspell-sv
COMPONENT_VERSION=	2.42
COMPONENT_PROJECT_URL=	https://extensions.libreoffice.org/extension-center/swedish-spelling-dictionary-den-stora-svenska-ordlistan/
COMPONENT_SUMMARY=	Myspell and Hunspell spell dictionary files for SWedish
COMPONENT_LICENSE=	LGPLv3
COMPONENT_FMRI=	library/myspell/dictionary/sv
COMPONENT_CLASSIFICATION	= System/Localizations

COMPONENT_SRC=            ooo-swedish-dict-2-42
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).oxt
COMPONENT_ARCHIVE_HASH=        \
     sha256:6f8c62461eb4c2cfe81628094c74ab6511918520047742f14e23dd440b99f45f
COMPONENT_ARCHIVE_URL=   https://extensions.libreoffice.org/assets/downloads/z/$(COMPONENT_ARCHIVE)

UNPACK_ARGS+=-r $(COMPONENT_SRC)

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
	cp $(COMPONENT_SRC)/dictionaries/sv_FI.dic $(PROTO_DIR)$(DESTDIR)
	cp $(COMPONENT_SRC)/dictionaries/sv_FI.aff $(PROTO_DIR)$(DESTDIR)
	cp $(COMPONENT_SRC)/dictionaries/sv_SE.dic $(PROTO_DIR)$(DESTDIR)
	cp $(COMPONENT_SRC)/dictionaries/sv_SE.aff $(PROTO_DIR)$(DESTDIR)
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
