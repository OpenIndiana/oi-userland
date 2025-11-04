#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# This file was automatically generated using the following command:
#   $WS_TOOLS/python-integrate-project powerline
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		powerline
HUMAN_VERSION =			2.8.4
COMPONENT_SUMMARY =		The ultimate statusline/prompt utility
COMPONENT_PROJECT_URL =		https://github.com/powerline/powerline/
COMPONENT_ARCHIVE_URL =		\
	https://github.com/powerline/powerline/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:9e846af9379b57e410efe264cff3a6b98eb78dd9526e83016776ae5ffc5798f4
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

COMPONENT_FMRI =	python/powerline

# Manifest options for python/powerline-vim package
COMPONENT_FMRI.powerline-vim =			$(COMPONENT_FMRI)-vim
COMPONENT_SUMMARY.powerline-vim =		$(COMPONENT_SUMMARY) - Vim editor binding
COMPONENT_CLASSIFICATION.powerline-vim =	System/Text Tools

# This is a standalone application.  Since no other Python project depends on
# it we just provide single unversioned package.
SINGLE_PYTHON_VERSION = yes

include $(WS_MAKE_RULES)/common.mk

# Needed for connect() and socket()
CFLAGS += -lsocket -lnsl

# Make sure compiled binaries are installed at proper location
PYTHON_DATA = $(USRDIR)

# Adjust powerline configuration for our location of bindings
COMPONENT_PREP_ACTION= \
	$(GSED) -i -e "/TMUX_CONFIG_DIRECTORY/ s@BINDINGS_DIRECTORY@'/usr/share/powerline'@" $(SOURCE_DIR)/powerline/config.py

# Move bindings where we want them
PROTOUSRLIBPOWERLINE=		$(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages/powerline
PROTOUSRSHAREPOWERLINEDIR=	$(PROTOUSRSHAREDIR)/powerline/
PROTOUSRSHAREVIM=		$(PROTOUSRSHAREDIR)/vim/vimfiles/powerline/
COMPONENT_POST_INSTALL_ACTION +=	\
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
	$(MV) $(PROTOUSRLIBPOWERLINE)/bindings/vim/plugin/powerline.vim $(PROTOUSRSHAREVIM) ;

# Remove files we do not need
COMPONENT_POST_INSTALL_ACTION +=	\
	( cd $(PROTOUSRLIBPOWERLINE) ; $(RM) \
		bindings/bar/powerline-bar.py \
		bindings/lemonbar/powerline-lemonbar.py \
		commands/lemonbar.py \
		dist/systemd/powerline-daemon.service \
		lemonbar.py \
		renderers/lemonbar.py \
	) ;

# Testing needs TEST_ROOT and HOME environment variables (the directory does
# not need to exist)
COMPONENT_TEST_ENV += TEST_ROOT="$(@D)/.test_home"
COMPONENT_TEST_ENV += HOME="$(@D)/.test_home"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
