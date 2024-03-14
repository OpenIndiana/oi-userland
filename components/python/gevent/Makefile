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
#   $WS_TOOLS/python-integrate-project gevent
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		gevent
HUMAN_VERSION =			22.10.2
COMPONENT_SUMMARY =		gevent - Coroutine-based network library
COMPONENT_PROJECT_URL =		http://www.gevent.org/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/9f/4a/e9e57cb9495f0c7943b1d5965c4bdd0d78bc4a433a7c96ee034b16c01520/gevent-22.10.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:1ca01da176ee37b3527a2702f7d40dbc9ffb8cfc7be5a03bfa4f9eec45e55c46
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Do not use test concurrency to get predictable order of test results
COMPONENT_TEST_ENV += NWORKERS=1

# Normalize test results
COMPONENT_TEST_TRANSFORMS += "-e 's/\x1b\[[0-9;]*m//g'"										# remove colors
COMPONENT_TEST_TRANSFORMS += "-e '/^Running tests in parallel with concurrency/d'"						# drop concurrency report
COMPONENT_TEST_TRANSFORMS += "-e 's/0x[0-9a-f]\{12,\}/\$$(POINTER)/g'"								# pointers
COMPONENT_TEST_TRANSFORMS += "-e 's/\(thread_ident=\)0x[0-9a-f]\{1,\}/\1\$$(ID)/g'"						# thread_ident
COMPONENT_TEST_TRANSFORMS += "-e 's/[0-9]\{4\}-[0-9][0-9]-[0-9][0-9]T[0-9][0-9]:[0-9][0-9]:[0-9][0-9]Z/\$$(TIMESTAMP)/g'"	# timestamps
COMPONENT_TEST_TRANSFORMS += "-e 's/\[[0-9]\{4\}-[0-9][0-9]-[0-9][0-9] [0-9][0-9]:[0-9][0-9]:[0-9][0-9]\]/[\$$(TIMESTAMP)]/g'"	# timestamps
COMPONENT_TEST_TRANSFORMS += "-e 's/\(Ran [0-9]\{1,\} tests\{0,1\}\) in [\.0-9]\{1,\}s/\1/'"					# timing
COMPONENT_TEST_TRANSFORMS += "-e 's/^\(Ran [0-9]\{1,\} tests\{0,1\}.* in [0-9]\{1,\} files\{0,1\}\) in .*\$$/\1/'"		# timing
COMPONENT_TEST_TRANSFORMS += "-e 's/\(GET .* HTTP.*\) [\.0-9]\{1,\}\$$/\1/'"							# timing
COMPONENT_TEST_TRANSFORMS += "-e 's/\(reacted\) after [\.0-9]\{1,\} seconds/\1/'"						# timing
COMPONENT_TEST_TRANSFORMS += "-e 's/ \[took [\.0-9]\{1,\}s\]//'"								# timing
COMPONENT_TEST_TRANSFORMS += "-e 's/ \[took [\.0-9]\{1,\}s \([^]]*\)\]/ [\1]/'"							# timing
COMPONENT_TEST_TRANSFORMS += "-e 's/^\(  127\.0\.0\.1:\)[0-9]\{1,\}\([ -]\)/\1\$$(PORT)\2/'"					# source port changes
COMPONENT_TEST_TRANSFORMS += "-e '/New connection from 127\.0\.0\.1:/d'"							# could be out of order
COMPONENT_TEST_TRANSFORMS += "-e '/echoed b/d'"											# could be out of order
COMPONENT_TEST_TRANSFORMS += "-e '/^Longest-running tests:/,/^\$$/d'"								# list changes with every run

# This project uses both cpython and abi3 ABI depending on particular library.
# To deal with this we need to disable automatic ABI library name transforms.
PY3_CPYTHON_NAMING=\#

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/cffi
PYTHON_REQUIRED_PACKAGES += library/python/cython
PYTHON_REQUIRED_PACKAGES += library/python/greenlet
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += library/python/zope-event
PYTHON_REQUIRED_PACKAGES += library/python/zope-interface
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/cffi
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/coveralls
TEST_REQUIRED_PACKAGES.python += library/python/dnspython
TEST_REQUIRED_PACKAGES.python += library/python/idna
TEST_REQUIRED_PACKAGES.python += library/python/objgraph
TEST_REQUIRED_PACKAGES.python += library/python/psutil
TEST_REQUIRED_PACKAGES.python += library/python/requests
