include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		enum34
COMPONENT_VERSION=	1.1.6
COMPONENT_PROJECT_URL=	https://bitbucket.org/stoneleaf/enum34
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	$(COMPONENT_SRC)/enum/LICENSE
COMPONENT_ARCHIVE_HASH=	\
    sha256:8ad8c4783bf61ded74527bffb48ed9b54166685e4230386a9ed9b1279e2df5b1
COMPONENT_ARCHIVE_URL=	$(call pypi_url)

PYTHON_VERSIONS=	2.7

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

build:		$(BUILD_32_and_64)
install:	$(INSTALL_32_and_64)
 
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
