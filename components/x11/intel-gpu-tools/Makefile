###############################################################################
#
# intel-gpu-tools - Intel graphics driver debug tools
#
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME = intel-gpu-tools
COMPONENT_SRC = $(COMPONENT_NAME)
COMPONENT_VERSION = 1.13
COMPONENT_REVISION = $(shell cd $(COMPONENT_SRC); git rev-list HEAD --count)
COMPONENT_SUMMARY = Intel graphics driver debug tools
COMPONENT_PROJECT_URL = http://xorg.freedesktop.org
COMPONENT_ARCHIVE_URL = https://cgit.freedesktop.org/xorg/app/intel-gpu-tools/
COMPONENT_FMRI = x11/diagnostic/$(COMPONENT_NAME)
# COMPONENT_LICENSE = MIT
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_CLASSIFICATION = Applications/System Utilities
COMPONENT_AUTOGEN_MANIFEST = yes

GIT=git
GIT_REPO=http://anongit.freedesktop.org/git/xorg/app/intel-gpu-tools
GIT_BRANCH=master
GIT_CHANGESET=HEAD


include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk

publish: update-publish

include $(WS_TOP)/make-rules/ips.mk

$(SOURCE_DIR)/.downloaded: $(ARCHIVES:%=$(USERLAND_ARCHIVES)%)
	[ -d $(SOURCE_DIR) ] || \
	$(GIT) clone -b $(GIT_BRANCH) $(GIT_REPO) $(SOURCE_DIR)
	cd $(SOURCE_DIR) ; $(GIT) checkout $(GIT_BRANCH) ; $(GIT) pull \
	$(GIT_REPO) ; $(GIT) log -1 --format=%H > .downloaded

update-publish:
	@[ -d $(SOURCE_DIR) ] || \
	$(GIT) clone -b $(GIT_BRANCH) $(GIT_REPO) $(SOURCE_DIR)
	cd $(SOURCE_DIR) ; $(GIT) pull $(GIT_REPO) ; \
		[ "$$($(GIT) log -1 --format=%H)" == "$$(cat .downloaded)" ] || \
		( $(GIT) log -1 --format=%H > .downloaded && $(MAKE) -C $$OLDPWD publish )

CONFIGURE_DEFAULT_DIRS = no

PATCH_LEVEL = 1

COMPONENT_PREP_ACTION =        ( cd $(@D) && \
	if ! type gtkdocize > /dev/null 2>&1; then \
		echo "EXTRA_DIST =" > gtk-doc.make; \
		echo "CLEANFILES =" >> gtk-doc.make; \
	else \
		gtkdocize || exit $?; \
	fi; \
                                        libtoolize --automake --copy --force && \
                                        aclocal -Im4 && \
                                        autoheader && \
                                        automake -a -f -c &&\
                                        autoconf )

# Command line options to GNU autoconf configure script
# CPPFLAGS  += -g
CONFIGURE_ENV+= CPPFLAGS="$(CPPFLAGS)"

LIBEXECSUBDIR.64 = /$(MACH64)
LIBEXECSUBDIR = $(LIBEXECSUBDIR.$(BITS))
# BENCHLIBEXECDIR = /usr/libexec/$(COMPONENT_NAME)/benchmarks/$(LIBEXECSUBDIR)
# COMPONENT_COMMON_ARGS =  gem_exec_tracer_ladir='$(BENCHLIBEXECDIR)'

CONFIGURE_OPTIONS += --without-libunwind
CONFIGURE_OPTIONS += --disable-tests
CONFIGURE_OPTIONS += --libexecdir=/usr/libexec$(LIBEXECSUBDIR)

COMPONENT_BUILD_TARGETS = all

$(SOURCE_DIR)/.prep: $(SOURCE_DIR)/.downloaded Makefile

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

download:: $(SOURCE_DIR)/.downloaded
