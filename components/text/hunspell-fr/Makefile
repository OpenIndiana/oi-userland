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

COMPONENT_NAME=		hunspell-fr
COMPONENT_VERSION=	6.3
COMPONENT_PROJECT_URL=	http://www.dicollecte.org/
COMPONENT_SUMMARY=	Myspell and Hunspell spell dictionary files for French
COMPONENT_LICENSE=	MPLv2.0
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_FMRI=	library/myspell/dictionary/fr
COMPONENT_CLASSIFICATION	= System/Localizations

COMPONENT_SRC=            hunspell-french-dictionaries-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH=        \
       sha256:cc6c2d15073659d221487b45245e9eee9a4ed66c30c6dcf784326bab063c5266
COMPONENT_ARCHIVE_URL=   http://www.dicollecte.org/download/fr/$(COMPONENT_ARCHIVE)
UNPACK_ARGS+=-r $(COMPONENT_SRC)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

DESTDIR=/usr/share/spell/hunspell
LINKDIR=/usr/share/spell/myspell
FFDIR=/usr/lib/firefox/dictionaries
TBDIR=/usr/lib/thunderbird/dictionaries

FRALIASES = fr_BE fr_CA fr_CH fr_LU

$(SOURCE_DIR)/.installed:	$(SOURCE_DIR)/.prep
	[ -d $(PROTO_DIR)$(DESTDIR) ] || mkdir -p $(PROTO_DIR)$(DESTDIR)
	[ -d $(PROTO_DIR)$(LINKDIR) ] || mkdir -p $(PROTO_DIR)$(LINKDIR)
	[ -d $(PROTO_DIR)$(FFDIR) ] || mkdir -p $(PROTO_DIR)$(FFDIR)
	[ -d $(PROTO_DIR)$(TBDIR) ] || mkdir -p $(PROTO_DIR)$(TBDIR)
	cp $(COMPONENT_SRC)/fr-moderne.aff $(PROTO_DIR)$(DESTDIR)/fr_FR.aff
	cp $(COMPONENT_SRC)/fr-moderne.dic $(PROTO_DIR)$(DESTDIR)/fr_FR.dic
	for alias in $(FRALIASES); do\
		ln -fs fr_FR.aff $(PROTO_DIR)$(DESTDIR)/$$alias.aff; \
		ln -fs fr_FR.dic $(PROTO_DIR)$(DESTDIR)/$$alias.dic; \
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

# Build dependencies
REQUIRED_PACKAGES+= text/aspell
