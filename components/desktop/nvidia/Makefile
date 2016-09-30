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
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		driver-graphics-nvidia
COMPONENT_VERSION=	367.35
IPS_COMPONENT_VERSION=	0.$(COMPONENT_VERSION)
COMPONENT_SRC=		NVIDIA-Solaris-x86-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).run
COMPONENT_ARCHIVE_HASH= \
	sha256:3bd29965fc51ebb1697075b16b9367b370760a41a1c08a84ea9d5e8c88bd8e4c
#COMPONENT_ARCHIVE_URL=	http://uk.download.nvidia.com/solaris/$(COMPONENT_VERSION)/NVIDIA-Solaris-x86-$(COMPONENT_VERSION).run
#COMPONENT_ARCHIVE_URL=	ftp://download.nvidia.com/solaris/$(COMPONENT_VERSION)/NVIDIA-Solaris-x86-$(COMPONENT_VERSION).run
#COMPONENT_ARCHIVE_URL=	http://download.nvidia.com/solaris/$(COMPONENT_VERSION)/NVIDIA-Solaris-x86-$(COMPONENT_VERSION).run
COMPONENT_ARCHIVE_URL=	http://us.download.nvidia.com/solaris/$(COMPONENT_VERSION)/NVIDIA-Solaris-x86-$(COMPONENT_VERSION).run

PKG_PROTO_DIRS += $(COMPONENT_SRC)/NVDAgraphics/
PKG_PROTO_DIRS += $(COMPONENT_SRC)/NVDAgraphicsr/

include ../../make-rules/prep.mk
include ../../make-rules/ips.mk

$(SOURCE_DIR)/.unpacked: download Makefile $(PATCHES)
	$(RM) -r $(SOURCE_DIR)
	$(SHELL) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE) -x
	$(TOUCH) $@

$(BUILD_32):	$(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(TOUCH) $@

$(INSTALL_32): 	$(BUILD_32)
	[ -d $(PROTO_DIR)/kernel/drv/amd64 ] || mkdir -p $(PROTO_DIR)/kernel/drv/amd64
	for i in kernel/drv/amd64/nvidia kernel/drv/amd64/nvidia_modeset kernel/drv/nvidia kernel/drv/nvidia_modeset kernel/drv/nvidia.conf kernel/drv/nvidia_modeset.conf; do \
	    cp $(SOURCE_DIR)/NVDAgraphicsr/reloc/$$i $(PROTO_DIR)/$$i; done
	[ -h $(PROTO_DIR)/usr ] && rm $(PROTO_DIR)/usr || true
	ln -sf $(SOURCE_DIR)/NVDAgraphics/reloc $(PROTO_DIR)/usr
	$(TOUCH) $@

build: $(BUILD_32)

install: $(INSTALL_32)

clean::
	if [ -d $(BUILD_DIR) ] ;  then \
	  rm -rf $(BUILD_DIR) ; \
	fi
