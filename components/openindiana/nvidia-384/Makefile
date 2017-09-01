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
# Copyright 2017, Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		driver-graphics-nvidia
COMPONENT_VERSION=	384.69
IPS_COMPONENT_VERSION=	0.$(COMPONENT_VERSION)
COMPONENT_SRC=		NVIDIA-Solaris-x86-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).run
COMPONENT_ARCHIVE_HASH= \
	sha256:8d6d61c132fd20956d4e025bbaba40d780d438514ad2a845e1b4d1c12d655f7b
#COMPONENT_ARCHIVE_URL=	http://uk.download.nvidia.com/solaris/$(COMPONENT_VERSION)/NVIDIA-Solaris-x86-$(COMPONENT_VERSION).run
#COMPONENT_ARCHIVE_URL=	ftp://download.nvidia.com/solaris/$(COMPONENT_VERSION)/NVIDIA-Solaris-x86-$(COMPONENT_VERSION).run
#COMPONENT_ARCHIVE_URL=	http://download.nvidia.com/solaris/$(COMPONENT_VERSION)/NVIDIA-Solaris-x86-$(COMPONENT_VERSION).run
COMPONENT_ARCHIVE_URL=	http://us.download.nvidia.com/solaris/$(COMPONENT_VERSION)/NVIDIA-Solaris-x86-$(COMPONENT_VERSION).run
COMPONENT_PROJECT_URL=	http://www.nvidia.com/object/solaris-display-archive.html

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

$(SOURCE_DIR)/.unpacked: download Makefile $(PATCHES)
	$(RM) -r $(SOURCE_DIR)
	$(SHELL) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE) -x
	$(TOUCH) $@

$(BUILD_32):	$(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(TOUCH) $@

$(INSTALL_32): 	$(BUILD_32)
	[ -d $(PROTO_DIR)/kernel/drv/amd64 ] || mkdir -p $(PROTO_DIR)/kernel/drv/amd64
	for i in \
	    kernel/drv/amd64/nvidia kernel/drv/nvidia kernel/drv/nvidia.conf \
	    kernel/drv/amd64/nvidia_modeset kernel/drv/nvidia_modeset kernel/drv/nvidia_modeset.conf \
	 ; do \
	    cp $(SOURCE_DIR)/NVDAgraphicsr/reloc/$$i $(PROTO_DIR)/$$i \
	 ; done
	[ -d $(PROTO_DIR)/kernel/misc/amd64 ] || mkdir -p $(PROTO_DIR)/kernel/misc/amd64
	cp $(SOURCE_DIR)/gfx_private/SunOS-5.11/gfx_private $(PROTO_DIR)/kernel/misc/
	cp $(SOURCE_DIR)/gfx_private/SunOS-5.11/amd64/gfx_private $(PROTO_DIR)/kernel/misc/amd64/
	[ -n "$(PROTO_DIR)" ] && rm -fr $(PROTO_DIR)/usr
	cp -a $(SOURCE_DIR)/NVDAgraphics/reloc $(PROTO_DIR)/usr
	$(TOUCH) $@

build: $(BUILD_32)

install: $(INSTALL_32)

clean::
	if [ -d $(BUILD_DIR) ] ;  then \
	  rm -rf $(BUILD_DIR) ; \
	fi

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/gcc-4-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/compatibility/links-xorg
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
