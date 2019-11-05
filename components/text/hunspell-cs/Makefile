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

COMPONENT_NAME=		hunspell-cs
COMPONENT_VERSION=	2006.10.30
COMPONENT_REVISION=     1
COMPONENT_PROJECT_URL=	http://wiki.services.openoffice.org/wiki/Dictionaries
COMPONENT_SUMMARY=	Myspell and Hunspell spell dictionary files for Czech
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_FMRI=	library/myspell/dictionary/cs
COMPONENT_CLASSIFICATION	= System/Localizations

COMPONENT_SRC=            cs_CZ
COMPONENT_ARCHIVE=        $(COMPONENT_NAME)-$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_HASH=        \
    sha256:b10c18624c2d37924f3bd8e6d7ffbd9fbb3c543c288495582d0d99dcb5cda94c
COMPONENT_ARCHIVE_URL=   http://ftp.tc.edu.tw/pub/openoffice/contrib/dictionaries/$(COMPONENT_SRC).zip
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
	for file in $(COMPONENT_SRC)/*.{aff,dic}; do \
		cp $$file $(PROTO_DIR)$(DESTDIR)/; \
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
