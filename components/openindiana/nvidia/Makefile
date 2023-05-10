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
# Copyright 2022, Andreas Wacknitz
#

BUILD_STYLE = archive
BUILD_BITS = NO_ARCH

include ../../../make-rules/shared-macros.mk

# This is latest NVIDIA Production Branch driver

COMPONENT_NAME =		nvidia
HUMAN_VERSION =			525.116.04
COMPONENT_VERSION =		$(shell echo $(HUMAN_VERSION) | $(GSED) -e 's/\.0*/./g')
COMPONENT_FMRI =		driver/graphics/nvidia
COMPONENT_SUMMARY =		NVIDIA Graphics System Software
COMPONENT_CLASSIFICATION =	Drivers/Display
COMPONENT_PROJECT_URL =		https://www.nvidia.com/en-us/drivers/unix/
COMPONENT_SRC =			NVIDIA-Solaris-x86-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).run
COMPONENT_ARCHIVE_HASH =	sha256:3ebfaa9d873b8c5ba833997b28062c15b9537c675ac8b7d68c128e960a82882f
COMPONENT_ARCHIVE_URL =		https://us.download.nvidia.com/solaris/$(HUMAN_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		NVIDIA
COMPONENT_LICENSE_FILE =	nvidia.license

BUILD_TARGET = $(BUILD_$(MK_BITS))
INSTALL_TARGET = $(INSTALL_$(MK_BITS))
TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CLEAN_PATHS += $(BUILD_DIR)

# Hack to run proper unpack command
UNPACK := $(SHELL) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE)
UNPACK_ARGS = -x
USERLAND_ARCHIVES = \#

$(BUILD_$(MK_BITS)):	$(SOURCE_DIR)/.prep
	($(RM) -rf $(@D) ; $(MKDIR) $(@D))
	$(TOUCH) $@

$(INSTALL_$(MK_BITS)):	$(BUILD_$(MK_BITS))
	$(MKDIR) $(PROTO_DIR)/kernel/drv/amd64
	for i in kernel/drv/amd64/nvidia kernel/drv/nvidia.conf kernel/drv/nvidia_modeset.conf kernel/drv/amd64/nvidia_modeset; do \
	    $(CP) $(SOURCE_DIR)/NVDAgraphicsr/reloc/$$i $(PROTO_DIR)/$$i; done
	$(RM) -r $(PROTO_DIR)/usr
	$(CP) -a $(SOURCE_DIR)/NVDAgraphics/reloc $(PROTO_DIR)/usr
	$(TOUCH) $@

GENERATE_EXTRA_CMD += | \
	$(CAT) - <( \
		eval $$($(GNU_GREP) ^A $(SOURCE_DIR)/NVDAgraphicsr/install/postinstall) ; \
		printf 'driver name=nvidia_modeset perms="* 0666 root root"\n' ; \
		printf 'driver name=nvidia perms="* 0666 root root"' ; \
		for i in $$ALIASES ; do \
			printf ' \\\n\talias=%s' "$$i" ; \
		done ; \
		printf '\n' \
	)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
