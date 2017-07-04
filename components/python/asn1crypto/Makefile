include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		asn1crypto
COMPONENT_VERSION=	0.22.0
COMPONENT_PROJECT_URL=	https://github.com/wbond/asn1crypto
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_LICENSE=	MIT
COMPONENT_ARCHIVE_HASH=	\
    sha256:cbbadd640d3165ab24b06ef25d1dca09a3441611ac15f6a6b452474fdf0aed1a
COMPONENT_ARCHIVE_URL=	$(call pypi_url)

PYTHON_VERSIONS=	2.7

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

build:		$(BUILD_32_and_64)
install:	$(INSTALL_32_and_64)
 
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
