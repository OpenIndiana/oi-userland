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

COMPONENT_NAME=		hunspell-pt_br
COMPONENT_VERSION=	3.2.15
COMPONENT_PROJECT_URL=	https://pt-br.libreoffice.org/projetos/vero
COMPONENT_SUMMARY=	Myspell and Hunspell spell dictionary files for Portugese Brazilian
COMPONENT_LICENSE=	MPL1.1
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_FMRI=	library/myspell/dictionary/pt_br
COMPONENT_CLASSIFICATION	= System/Localizations

COMPONENT_SRC=            VeroptBR3215AOC
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).oxt
COMPONENT_ARCHIVE_HASH=        \
    sha256:7571a3d8aaa0d5699f8b572d2fc613189876fa4fa87dcbda9a99bd63500210ee
COMPONENT_ARCHIVE_URL=   https://pt-br.libreoffice.org/assets/Uploads/PT-BR-Documents/VERO/$(COMPONENT_ARCHIVE)
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
	cp $(COMPONENT_SRC)/pt_BR.dic $(PROTO_DIR)$(DESTDIR)
	cp $(COMPONENT_SRC)/pt_BR.aff $(PROTO_DIR)$(DESTDIR)
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
