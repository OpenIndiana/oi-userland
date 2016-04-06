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
COMPONENT_VERSION=	340.93
IPS_COMPONENT_VERSION=	0.$(COMPONENT_VERSION)
COMPONENT_SRC=		NVIDIA-Solaris-x86-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).run
COMPONENT_ARCHIVE_HASH= \
	sha256:aaee5171d71fa74807960f9ccc65dbc09bfe77bc469c060b768b4293645ea9b7
#COMPONENT_ARCHIVE_URL=	http://uk.download.nvidia.com/solaris/$(COMPONENT_VERSION)/NVIDIA-Solaris-x86-$(COMPONENT_VERSION).run
#COMPONENT_ARCHIVE_URL=	ftp://download.nvidia.com/solaris/$(COMPONENT_VERSION)/NVIDIA-Solaris-x86-$(COMPONENT_VERSION).run
#COMPONENT_ARCHIVE_URL=	http://download.nvidia.com/solaris/$(COMPONENT_VERSION)/NVIDIA-Solaris-x86-$(COMPONENT_VERSION).run
COMPONENT_ARCHIVE_URL=	http://us.download.nvidia.com/solaris/$(COMPONENT_VERSION)/NVIDIA-Solaris-x86-$(COMPONENT_VERSION).run

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
	for i in kernel/drv/amd64/nvidia kernel/drv/nvidia kernel/drv/nvidia.conf; do \
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
