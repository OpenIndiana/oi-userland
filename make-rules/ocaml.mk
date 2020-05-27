# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2020, Aurelien Larcher. All rights reserved.
#

OCAML_ETCDIR = $(ETCDIR)/ocaml
OCAML_LIBDIR = $(USRLIBDIR64)/ocaml

# Select preferred Python version
OCAML_PYTHON_VERSION = 3.5
PYTHON_VERSION = $(OCAML_PYTHON_VERSION)
