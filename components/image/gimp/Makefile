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
# Copyright (c) 2017 Alexander Pyhalov
# Copyright (c) 2019 Tim Mooney
#

BUILD_STYLE = meson
USE_DEFAULT_TEST_TRANSFORMS= yes
USE_PARALLEL_BUILD= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gimp
COMPONENT_VERSION=	3.2.0
COMPONENT_SUMMARY=	Gimp - The Free & Open Source Image Editor
COMPONENT_PROJECT_URL=	https://www.gimp.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:2618391416e51be3c693df9ef90e3860ed72ab3d36363ea1f196e30b75b2e083
COMPONENT_ARCHIVE_URL=	https://download.gimp.org/gimp/v3.2/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		image/editor/gimp
COMPONENT_CLASSIFICATION=	Applications/Graphics and Imaging
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

LDFLAGS += -lsocket -lnsl

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)

CONFIGURE_ENV += PYTHON=$(PYTHON)

# Tell g-ir-scanner not to cache results in homedir of user running the build
COMPONENT_BUILD_ENV += GI_SCANNER_DISABLE_CACHE=""

# Replace "#!/usr/bin/env ..." shebang lines with properly versioned ones.
COMPONENT_POST_INSTALL_ACTION+= \
	/usr/bin/find $(PROTO_DIR) -name *.py \
		-exec $(GSED) -i -e '1s|env python.*|python$(PYTHON_VERSION)|' "{}" \; ;

COMPONENT_POST_INSTALL_ACTION+= \
	/usr/bin/find $(PROTO_DIR) -name *.scm \
		-exec $(GSED) -i -e '1s|env gimp-script-fu-interpreter|gimp-script-fu-interpreter|' "{}" \; ;

# Build dependencies
REQUIRED_PACKAGES += developer/vala

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += desktop/appstream
REQUIRED_PACKAGES += image/graphviz
REQUIRED_PACKAGES += image/library/babl
REQUIRED_PACKAGES += image/library/gegl
REQUIRED_PACKAGES += image/library/gexiv2
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += image/library/openjpeg
REQUIRED_PACKAGES += library/aalib
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/graphics/libmng
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/libmypaint
REQUIRED_PACKAGES += library/libpoppler
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/mypaint-brushes
REQUIRED_PACKAGES += library/openexr
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += print/filter/ghostscript
REQUIRED_PACKAGES += system/font/truetype/noto-emoji
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/libxpm
