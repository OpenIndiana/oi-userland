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

COMPONENT_NAME=		hunspell-it
COMPONENT_VERSION=	2016.2.13
COMPONENT_PROJECT_URL=	http://extensions.services.openoffice.org/
COMPONENT_SUMMARY=	Myspell and Hunspell spell dictionary files for Italian
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	legacy/it_IT_COPYING
COMPONENT_FMRI=	library/myspell/dictionary/it
COMPONENT_CLASSIFICATION	= System/Localizations

COMPONENT_SRC=            dict-it
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).oxt
COMPONENT_ARCHIVE_HASH=        \
    sha256:74d24b4c11709111053860d825286c4f11436d5265756f6882a62170ec771941
COMPONENT_ARCHIVE_URL=   https://sourceforge.net/projects/aoo-extensions/files/1204/14/$(COMPONENT_ARCHIVE)
UNPACK_ARGS+=	-r $(COMPONENT_SRC)


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
	cp $(COMPONENT_SRC)/dictionaries/it_IT.aff $(PROTO_DIR)$(DESTDIR)
	cp $(COMPONENT_SRC)/dictionaries/it_IT.dic $(PROTO_DIR)$(DESTDIR)
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
