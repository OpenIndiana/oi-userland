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
# Copyright 2021 Gary Mills
# Copyright 2016 Alexander Pyhalov
#

BUILD_STYLE = meson
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gtk-doc
HUMAN_VERSION=		1.34.0
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	GTK+ DocBook Documentation Generator
COMPONENT_ARCHIVE_HASH=	sha256:b20b72b32a80bc18c7f975c9d4c16460c2276566a0b50f87d6852dff3aa7861c
COMPONENT_FMRI=		developer/documentation-tool/gtk-doc
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	GPL-2.0-only AND GFDL-1.1-only

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# helper target
update-license-file: patch
	( \
		printf '\n--- COPYING ---------------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING ; \
		printf '\n--- COPYING-DOCS ----------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING-DOCS \
	) > $(COMPONENT_DIR)/$(COMPONENT_LICENSE_FILE)

# GNU msgfmt is expected
PATH= $(PATH.gnu)

PYTHON_SCRIPTS += usr/bin/gtkdoc-check
PYTHON_SCRIPTS += usr/bin/gtkdoc-fixxref
PYTHON_SCRIPTS += usr/bin/gtkdoc-depscan
PYTHON_SCRIPTS += usr/bin/gtkdoc-mkdb
PYTHON_SCRIPTS += usr/bin/gtkdoc-mkhtml
PYTHON_SCRIPTS += usr/bin/gtkdoc-mkhtml2
PYTHON_SCRIPTS += usr/bin/gtkdoc-mkman
PYTHON_SCRIPTS += usr/bin/gtkdoc-mkpdf
PYTHON_SCRIPTS += usr/bin/gtkdoc-scan
PYTHON_SCRIPTS += usr/bin/gtkdoc-rebase
PYTHON_SCRIPTS += usr/bin/gtkdoc-scangobj

# Manually added build and runtime dependencies
REQUIRED_PACKAGES += text/itstool
PYTHON_REQUIRED_PACKAGES += library/python/pygments

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += shell/ksh93
