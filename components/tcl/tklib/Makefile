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
# Copyright (c) 2016 Sergey Avseyev
# Copyright (c) 2018 Michal Nowak
# Copyright (c) 2023 Klaus Ziegler
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tklib
COMPONENT_VERSION=	0.7
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	https://core.tcl.tk/tklib/home
COMPONENT_SUMMARY=	Collection of widgets and other packages for Tk
COMPONENT_FMRI=         tcl/tklib
COMPONENT_CLASSIFICATION=       Development/Other Languages
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:93890db81a5b0cdb62c386265ec4fcdaab60824e8e6e882c7fecc69ff49afc66
COMPONENT_ARCHIVE_URL=	https://github.com/tcltk/tklib/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	TCL
COMPONENT_LICENSE_FILE=	tklib.license

include $(WS_MAKE_RULES)/common.mk

# The unpacked sources have an uncommon name tklib-tklib-0.7 which we need to rename:
COMPONENT_POST_UNPACK_ACTION += \
	mv tklib-$(COMPONENT_SRC) $(COMPONENT_SRC)

COMPONENT_POST_INSTALL_ACTION = \
        (for i in $$(find $(PROTO_DIR)$(USRSHAREMANDIR) -name '*.n') ; do \
           mandir="$$(dirname "$$i")"; \
           manbase="$$(basename "$$i" .n)"; \
           mv "$$i" "$${mandir}/$${manbase}.1t"; \
         done)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
