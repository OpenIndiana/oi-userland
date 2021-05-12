#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2012, Andrzej Szeszo 
# Copyright 2019, Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		driver-graphics-nvidia-390
COMPONENT_VERSION=	390.143
IPS_COMPONENT_VERSION=	0.$(COMPONENT_VERSION)
COMPONENT_FMRI=		driver/graphics/nvidia-390
COMPONENT_SUMMARY=	NVIDIA Graphics System Software
COMPONENT_CLASSIFICATION=Drivers/Display
COMPONENT_PROJECT_URL=	https://www.nvidia.com/en-us/drivers/unix/
COMPONENT_SRC=		NVIDIA-Solaris-x86-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).run
COMPONENT_ARCHIVE_HASH= sha256:8ec5cca23a326060ed99807a88387ed9cd04ee9128f17cd2cdaf010214965925
COMPONENT_ARCHIVE_URL=	https://us.download.nvidia.com/solaris/$(COMPONENT_VERSION)/NVIDIA-Solaris-x86-$(COMPONENT_VERSION).run
COMPONENT_LICENSE=	NVIDIA
COMPONENT_LICENSE_FILE=	driver-graphics-nvidia.license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_POST_INSTALL_ACTION = ( \
	$(CHMOD) u+w $(PROTO_DIR)/usr/X11/lib/modules/NVIDIA/libnvidia-wfb.so.1 ; \
	$(CHMOD) u+w $(PROTO_DIR)/usr/X11/lib/modules/NVIDIA/$(MACH64)/libnvidia-wfb.so.1 ; \
	/usr/bin/elfedit -e "dyn:rpath $(GCC_ROOT)/lib:/lib:/usr/lib" \
		$(PROTO_DIR)/usr/X11/lib/modules/NVIDIA/libnvidia-wfb.so.1 ; \
	/usr/bin/elfedit -e "dyn:rpath $(GCC_ROOT)/lib/$(MACH64):/lib/$(MACH64):/usr/lib/$(MACH64)"\
		$(PROTO_DIR)/usr/X11/lib/modules/NVIDIA/$(MACH64)/libnvidia-wfb.so.1 ; )

$(SOURCE_DIR)/.unpacked: download Makefile $(PATCHES)
	$(RM) -r $(SOURCE_DIR)
	$(SHELL) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE) -x
	$(TOUCH) $@

$(BUILD_32):	$(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(TOUCH) $@

$(INSTALL_32): 	$(BUILD_32)
	[ -d $(PROTO_DIR)/kernel/drv/amd64 ] || mkdir -p $(PROTO_DIR)/kernel/drv/amd64
	for i in kernel/drv/amd64/nvidia kernel/drv/nvidia.conf kernel/drv/nvidia_modeset.conf kernel/drv/amd64/nvidia_modeset; do \
	    cp $(SOURCE_DIR)/NVDAgraphicsr/reloc/$$i $(PROTO_DIR)/$$i; done
	rm -fr $(PROTO_DIR)/usr
	cp -a $(SOURCE_DIR)/NVDAgraphics/reloc $(PROTO_DIR)/usr
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

clean::
	if [ -d $(BUILD_DIR) ] ;  then \
	  rm -rf $(BUILD_DIR) ; \
	fi

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/compatibility/links-xorg
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
