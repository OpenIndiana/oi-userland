include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ipaddress
COMPONENT_VERSION=	1.0.18
COMPONENT_PROJECT_URL=	https://github.com/phihag/ipaddress
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_LICENSE=	PSF
COMPONENT_LICENSE_FILE=	$(COMPONENT_SRC)/LICENSE
COMPONENT_ARCHIVE_HASH=	\
    sha256:5d8534c8e185f2d8a1fda1ef73f2c8f4b23264e8e30063feeb9511d492a413e1
COMPONENT_ARCHIVE_URL=	$(call pypi_url)

PYTHON_VERSIONS=	2.7

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

build:		$(BUILD_32_and_64)
install:	$(INSTALL_32_and_64)
 
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
