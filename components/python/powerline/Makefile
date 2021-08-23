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
# Copyright 2019 Michal Nowak
# Copyright 2021 Nona Hansel
#

BUILD_BITS=		64
BUILD_STYLE=		setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		powerline
COMPONENT_VERSION=	2.8.2
COMPONENT_SUMMARY=	'The ultimate statusline/prompt utility'
COMPONENT_PROJECT_URL=	https://github.com/powerline/powerline/
COMPONENT_FMRI=		python/powerline
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/powerline/powerline/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:ea4ca0df45b8ea3870ff135cd3c4623ba4b785630be81db7f13bf5e94b3753c7
COMPONENT_LICENSE=	MIT

CFLAGS += -lsocket

PYTHON_VERSION=		3.9
PYTHON_VERSIONS=	3.9

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION= \
	$(GSED) -i -e "/TMUX_CONFIG_DIRECTORY/ s@BINDINGS_DIRECTORY@'/usr/share/powerline'@" $(SOURCE_DIR)/powerline/config.py

PROTOUSRLIBPOWERLINE=		$(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages/powerline
PROTOUSRSHAREPOWERLINEDIR=	$(PROTOUSRSHAREDIR)/powerline/
PROTOUSRSHAREVIM=		$(PROTOUSRSHAREDIR)/vim/vimfiles/powerline/
COMPONENT_POST_INSTALL_ACTION= \
	$(MKDIR) $(PROTOUSRSHAREPOWERLINEDIR){,awesome,bash,fish,shell,tcsh,tmux,zsh} ; \
	for file in awesome/powerline.lua \
		bash/powerline.sh \
		fish/powerline-setup.fish \
		shell/powerline.sh \
		tcsh/powerline.tcsh \
		tmux/powerline-base.conf \
		tmux/powerline.conf \
		tmux/powerline_tmux_1.7_plus.conf \
		tmux/powerline_tmux_1.8.conf \
		tmux/powerline_tmux_1.8_minus.conf \
		tmux/powerline_tmux_1.8_plus.conf \
		tmux/powerline_tmux_1.9_plus.conf \
		tmux/powerline_tmux_2.1_plus.conf \
		zsh/powerline.zsh; \
		do \
			$(MV) $(PROTOUSRLIBPOWERLINE)/bindings/$$file $(PROTOUSRSHAREPOWERLINEDIR)/$$file; \
	done ; \
	$(MKDIR) $(PROTOUSRSHAREVIM) ; \
	$(MV) $(PROTOUSRLIBPOWERLINE)/bindings/vim/autoload/powerline/debug.vim $(PROTOUSRSHAREVIM) ; \
	$(MV) $(PROTOUSRLIBPOWERLINE)/bindings/vim/plugin/powerline.vim $(PROTOUSRSHAREVIM) ; \
	find $(PROTO_DIR) -name '*.~*~' -exec rm -f {} \; ;

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += system/library
