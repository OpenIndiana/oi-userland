#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright 2026 Carsten Grzemba
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		texlive
COMPONENT_VERSION=	20260301
COMPONENT_SUMMARY=	typesetting system created by Donald Knuth and released in 1978
COMPONENT_PROJECT_URL=	https://www.tug.org
COMPONENT_ARCHIVE_SRV=	https://texlive.info/historic/systems/$(COMPONENT_NAME)/$(shell echo "$(COMPONENT_VERSION)" | cut -c1-4)
#	https://mirrors.ctan.org/systems/texlive/tlnet/archive/german.tar.xz
COMPONENT_CTAN_URL=	https://mirrors.ctan.org/systems/texlive/tlnet/archive

# source
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-source
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:cb120d314d3ceb23ac608af17ddd2c623afcf02331f400a0f25eead5b8ac1d70
COMPONENT_ARCHIVE_URL=	$(COMPONENT_ARCHIVE_SRV)/$(COMPONENT_ARCHIVE)

# extra
# COMPONENT_SRC_1=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-extra
# COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.xz
# COMPONENT_ARCHIVE_HASH_1= \
# 			  sha256:68d78428d012bce8c2ffaf7027c701a66c51039a16059d33f30980330033a5d0
# COMPONENT_ARCHIVE_URL_1=	$(COMPONENT_ARCHIVE_SRV)/$(COMPONENT_ARCHIVE_1)

COMPONENT_FMRI=		text/texlive
COMPONENT_CLASSIFICATION=	System/Text Tools
COMPONENT_LICENSE= BSD-like
COMPONENT_LICENSE_FILE= LICENSE.TL

# texmf
COMPONENT_SRC_2=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-texmf
COMPONENT_ARCHIVE_2=	$(COMPONENT_SRC_2).tar.xz
COMPONENT_ARCHIVE_HASH_2= \
			  sha256:349eb7c5c2c15333d77490a52934b053c6dcb88834f2224978f7a4edf67940e7
COMPONENT_ARCHIVE_URL_2=	$(COMPONENT_ARCHIVE_SRV)/$(COMPONENT_ARCHIVE_2)

# tex-ini-files
COMPONENT_SRC_3=	tex-ini-files
COMPONENT_ARCHIVE_3=	$(COMPONENT_SRC_3).tar.xz
COMPONENT_ARCHIVE_HASH_3= \
			  sha256:d42eae30f6636140f32330c773f89cc16a6fd28607fe747be629ce71706b99f5
COMPONENT_ARCHIVE_URL_3=	$(COMPONENT_CTAN_URL)/$(COMPONENT_ARCHIVE_3)
UNPACK_ARGS_3= --relocate-to=$(COMPONENT_SRC_3)

# a4wide
COMPONENT_SRC_4=	a4wide
COMPONENT_ARCHIVE_4=	$(COMPONENT_SRC_4).tar.xz
COMPONENT_ARCHIVE_HASH_4= \
			  sha256:65bc8092f21ae346714c8fd4b566571b3b1b10846a046cc4cb602e0d20494e01
COMPONENT_ARCHIVE_URL_4=	$(COMPONENT_CTAN_URL)/$(COMPONENT_ARCHIVE_4)
UNPACK_ARGS_4= --relocate-to=$(COMPONENT_SRC_4)

# german
COMPONENT_SRC_5=	german
COMPONENT_ARCHIVE_5=	$(COMPONENT_SRC_5).tar.xz
COMPONENT_ARCHIVE_HASH_5= \
			  sha256:a98c9e88f70671407093feec8c048a5740f0a53e2b3e05410aaeb7df2577cde4
COMPONENT_ARCHIVE_URL_5=	$(COMPONENT_CTAN_URL)/$(COMPONENT_ARCHIVE_5)
UNPACK_ARGS_5= --relocate-to=$(COMPONENT_SRC_5)

# dinbrief
COMPONENT_SRC_6=	dinbrief
COMPONENT_ARCHIVE_6=	$(COMPONENT_SRC_6).tar.xz
COMPONENT_ARCHIVE_HASH_6= \
			  sha256:5c646d7a05718e129f4876c6b85d38836b94726c66506377238f76084afaa4f3
COMPONENT_ARCHIVE_URL_6=	$(COMPONENT_CTAN_URL)/$(COMPONENT_ARCHIVE_6)
UNPACK_ARGS_6= --relocate-to=$(COMPONENT_SRC_6)

include $(WS_MAKE_RULES)/common.mk

CPPFLAGS += -I/usr/include/poppler

CONFIGURE_OPTIONS	+=	--disable-debug
CONFIGURE_OPTIONS	+=	--disable-devnag
CONFIGURE_OPTIONS	+=	--disable-libtool-hack
CONFIGURE_OPTIONS	+=	--disable-missing
CONFIGURE_OPTIONS	+=	--disable-multiplatform
CONFIGURE_OPTIONS	+=	--disable-native-texlive-build
CONFIGURE_OPTIONS	+=	--disable-pmx
CONFIGURE_OPTIONS	+=	--disable-ps2eps
CONFIGURE_OPTIONS	+=	--disable-psutils
CONFIGURE_OPTIONS	+=	--enable-ipc
CONFIGURE_OPTIONS	+=	--enable-shared
CONFIGURE_OPTIONS	+=	--disable-xindy
# CONFIGURE_OPTIONS	+=	--enable-xindy
# CONFIGURE_OPTIONS	+=	--enable-xindy-docs
# CONFIGURE_OPTIONS	+=	--enable-xindy-rules
CONFIGURE_OPTIONS	+=	--with-banner-add='/OpenIndiana'
CONFIGURE_OPTIONS	+=	--with-freetype2-include=$(includedir)/freetype2
CONFIGURE_OPTIONS	+=	--with-mf-x-toolkit
CONFIGURE_OPTIONS	+=	--with-system-freetype2
CONFIGURE_OPTIONS	+=	--with-system-gd
CONFIGURE_OPTIONS	+=	--with-gd-includes=/usr/include/gd2
CONFIGURE_OPTIONS	+=	--with-system-icu
CONFIGURE_OPTIONS	+=	--with-system-libgs
CONFIGURE_OPTIONS	+=	--with-system-libpng
CONFIGURE_OPTIONS	+=	--with-system-poppler
CONFIGURE_OPTIONS	+=	--with-system-t1lib
CONFIGURE_OPTIONS	+=	--with-system-zlib
CONFIGURE_OPTIONS	+=	--with-system-zzlib
CONFIGURE_OPTIONS	+=	--with-system-harfbuzz
CONFIGURE_OPTIONS	+=	--with-system-synctex
CONFIGURE_OPTIONS	+=	--with-x
CONFIGURE_OPTIONS	+=	--with-xdvi-x-toolkit=xaw

CONFIGURE_ENV += XPDF_INCLUDES="-std=c++20 -I/usr/include/poppler"

COMPONENT_POST_INSTALL_ACTION +=    $(RM) $(PROTOUSRSHAREDIR)/info/dir;
COMPONENT_POST_INSTALL_ACTION +=    $(MKDIR) -p $(PROTOUSRSHAREDIR)/texlive/texmf-local/web2c;
COMPONENT_POST_INSTALL_ACTION +=    $(MV) $(PROTOUSRSHAREDIR)/texmf-dist/* $(PROTOUSRSHAREDIR)/texlive/texmf-dist/;
COMPONENT_POST_INSTALL_ACTION +=    CLONEY_MODE=hardlink $(CLONEY) $(COMPONENT_DIR)/$(COMPONENT_SRC_2) $(PROTOUSRSHAREDIR)/texlive;
COMPONENT_POST_INSTALL_ACTION +=    CLONEY_MODE=hardlink $(CLONEY) $(COMPONENT_DIR)/$(COMPONENT_SRC_4)/tex $(PROTOUSRSHAREDIR)/texlive/texmf-dist/tex;
COMPONENT_POST_INSTALL_ACTION +=    CLONEY_MODE=hardlink $(CLONEY) $(COMPONENT_DIR)/$(COMPONENT_SRC_5)/tex $(PROTOUSRSHAREDIR)/texlive/texmf-dist/tex;
COMPONENT_POST_INSTALL_ACTION +=    CLONEY_MODE=hardlink $(CLONEY) $(COMPONENT_DIR)/$(COMPONENT_SRC_6)/tex $(PROTOUSRSHAREDIR)/texlive/texmf-dist/tex;
COMPONENT_POST_INSTALL_ACTION +=    $(INSTALL) -m 0444 \
	$(COMPONENT_DIR)/$(COMPONENT_SRC_3)/tex/latex/tex-ini-files/latex.ini \
       	$(PROTOUSRSHAREDIR)/texlive/texmf-dist/tex/latex/latexconfig;
COMPONENT_POST_INSTALL_ACTION +=    $(RM) $(PROTOUSRSHAREDIR)/texlive/texmf-dist/tex/generic/config/language.dat;
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -m 0444 \
	$(PROTOUSRSHAREDIR)/texlive/texmf-dist/tex/generic/config/language.us \
       	$(PROTOUSRSHAREDIR)/texlive/texmf-dist/tex/generic/config/language.dat;
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -m 0444 \
	$(PROTOUSRSHAREDIR)/texlive/texmf-dist/web2c/fmtutil.cnf \
       	$(PROTOUSRSHAREDIR)/texlive/texmf-dist/tex/generic/config/fmtutil.cnf;
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -D -m 0444 \
	$(PROTOUSRSHAREDIR)/texlive/texmf-dist/web2c/fmtutil.cnf \
       	$(PROTOUSRSHAREDIR)/texlive/texmf-local/tex/generic/config/fmtutil.cnf;
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -d -m 0755 $(PROTOUSRSHAREDIR)/texlive/texmf-var;
COMPONENT_POST_INSTALL_ACTION +=   $(PYTHON_SCRIPTS_PROCESS)
#
PYTHON_SCRIPTS += usr/share/texlive/texmf-dist/scripts/memoize/memoize-extract.py
PYTHON_SCRIPTS += usr/share/texlive/texmf-dist/scripts/minted/latexminted.py
PYTHON_SCRIPTS += usr/share/texlive/texmf-dist/scripts/pdfbook2/pdfbook2
PYTHON_SCRIPTS += usr/share/texlive/texmf-dist/scripts/spix/spix.py
PYTHON_SCRIPTS += usr/share/texlive/texmf-dist/scripts/webquiz/webquiz.py
PYTHON_SCRIPTS += usr/share/texlive/texmf-dist/scripts/dviasm/dviasm.py
PYTHON_SCRIPTS += usr/share/texlive/texmf-dist/scripts/latex-papersize/latex-papersize.py
# 
# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(ICU_LIBRARY_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/c++/graphite2
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/gd
REQUIRED_PACKAGES += library/libsynctex
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += print/filter/ghostscript
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/libxpm
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
REQUIRED_PACKAGES.python += runtime/python
