#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright (c) 2010, 2016, Oracle and/or its affiliates. All rights reserved.
#

#
# The Python build infrastructure in setup.py.mk and pyproject.mk files uses
# several Python projects to work properly.  Since we cannot use these projects
# until they are actually built and installed we need to bootstrap.
#
# We do have several sequential bootstrap checkpoints during the process:
#
# (0)	Nothing works yet.
#
# 	Just core Python runtime is available (with no additional projects).
# 	While here almost nothing works.  We cannot do following tasks with
# 	regular Python projects:
# 		- detect their requirements,
# 		- build and publish them,
# 		- test them.
#
# (1) 	The bootstrapper is ready.
#
# 	The bootstrapper is special tool that requires just core Python with no
# 	dependency on other Python projects and it is able to build and publish
# 	itself and other Python projects.
#
# 	For projects using the 'setup.py' build style we do not need any
# 	special bootstrapper because such projects are built using their own
# 	'setup.py' script.  The only issue with the 'setup.py' build style
# 	projects is that their 'setup.py' script usually depends on some other
# 	projects (typically setuptools) to get successfully built.
#
# 	For 'pyproject'-style projects we use pyproject_installer as the
# 	bootstrapper.
#
# 	To achieve this checkpoint we just need to build pyproject_installer
# 	using pyproject_installer without detecting its requirements (they are
# 	none anyway) and without testing it (since no testing infrastructure is
# 	ready yet).
#
# (2)	The python-requires script works.
#
# 	Once the python-requires script works we can start to detect runtime
# 	dependencie of other Python projects automatically.
#
# 	To achieve this checkpoint we need to build the packaging project
# 	(directly needed by the python-requires script) and all projects
# 	required by packaging.  During this all projects' dependencies needs to
# 	be manually evaluated to make sure they are correct.
#
# (3)	The build infrastructure is fully working.
#
#	Once we are here we can build any Python project, but we cannot test it
#	yet.
#
# 	For projects using the 'setup.py' build style we do not need any
# 	special build infrastructure.  See checkpoint (1) above for detialed
# 	discussion about 'setup.py' build style projects.
#
# 	For 'pyproject'-style projects we need to build both 'build' and
# 	'installer' projects and all projects they depends on.
#
# (4)	The testing infrastructure is fully working.
#
# 	Once we are here we can finally use all features of the Python build
# 	framework.  Including testing.
#
# 	To achieve this we need to build tox, tox-current-env, and pytest
# 	projects together with their dependencies.
#
# All projects needed to achieve checkpoints (1), (2), and (3) should set
# PYTHON_BOOTSTRAP to 'yes' in their Makefile to make sure the regular build
# infrastructure is not used for them and special set of build rules is applied
# instead.
#
# All projects needed to go from checkpoint (3) to checkpoint (4) should set
# PYTHON_TEST_BOOTSTRAP to 'yes' in their Makefile to let the build
# infrastructure know that testing for such projects might not work properly.
#
# The PYTHON_BOOTSTRAP set to 'yes' implies PYTHON_TEST_BOOTSTRAP set to 'yes'
# too.
#
ifeq ($(strip $(PYTHON_BOOTSTRAP)),yes)
PYTHON_TEST_BOOTSTRAP = yes
endif

#
# Lists of Python projects needed to achieve particular bootstrap checkpoint.
# Indentation shows project dependencies (e.g. packaging requires flit_core).
#
PYTHON_BOOTSTRAP_CHECKPOINT_1 +=	pyproject_installer
#
PYTHON_BOOTSTRAP_CHECKPOINT_2 +=	$(PYTHON_BOOTSTRAP_CHECKPOINT_1)
PYTHON_BOOTSTRAP_CHECKPOINT_2 +=	packaging
PYTHON_BOOTSTRAP_CHECKPOINT_2 +=		flit_core

# Particular python runtime is always required (at least to run setup.py)
PYTHON_REQUIRED_PACKAGES += runtime/python

define python-rule
$(BUILD_DIR)/%-$(1)/.built:		PYTHON_VERSION=$(1)
$(BUILD_DIR)/%-$(1)/.installed:		PYTHON_VERSION=$(1)
$(BUILD_DIR)/%-$(1)/.tested:		PYTHON_VERSION=$(1)
$(BUILD_DIR)/%-$(1)/.tested-and-compared:	PYTHON_VERSION=$(1)
endef

$(foreach pyver, $(PYTHON_VERSIONS), $(eval $(call python-rule,$(pyver))))

$(BUILD_DIR)/$(MACH32)-%/.built:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.built:	BITS=64
$(BUILD_DIR)/$(MACH32)-%/.installed:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.installed:	BITS=64
$(BUILD_DIR)/$(MACH32)-%/.tested:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.tested:	BITS=64
$(BUILD_DIR)/$(MACH32)-%/.tested-and-compared:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.tested-and-compared:	BITS=64

PYTHON_32_VERSIONS = $(filter-out $(PYTHON_64_ONLY_VERSIONS), $(PYTHON_VERSIONS))

BUILD_32 = $(PYTHON_32_VERSIONS:%=$(BUILD_DIR)/$(MACH32)-%/.built)
BUILD_64 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.built)
BUILD_NO_ARCH = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH)-%/.built)

ifeq ($(filter-out $(PYTHON_64_ONLY_VERSIONS), $(PYTHON_VERSION)),)
BUILD_32_and_64 = $(BUILD_64)
endif

INSTALL_32 = $(PYTHON_32_VERSIONS:%=$(BUILD_DIR)/$(MACH32)-%/.installed)
INSTALL_64 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.installed)
INSTALL_NO_ARCH = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH)-%/.installed)

PYTHON_ENV =	CC="$(CC)"
PYTHON_ENV +=	CFLAGS="$(CFLAGS)"
PYTHON_ENV +=	CXX="$(CXX)"
PYTHON_ENV +=	CXXFLAGS="$(CXXFLAGS)"
PYTHON_ENV +=	PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"

COMPONENT_BUILD_ENV += $(PYTHON_ENV)
# We need to set GIT_DIR to workaround the nasty poetry bug:
# https://github.com/python-poetry/poetry/issues/5547.  Technically, we should
# set this on per-project basis, but we would need to check every newly
# integrated project to see if it is build by poetry backend or not.  We would
# also need to do similar check on every version bump, because any project
# could switch to poetry anytime.  Since this would be a lot of work we simply
# opted to set GIT_DIR for every python project.
COMPONENT_BUILD_ENV += GIT_DIR=$(BUILD_DIR)
COMPONENT_INSTALL_ENV += $(PYTHON_ENV)
COMPONENT_TEST_ENV += $(PYTHON_ENV)

# Set CARGO_HOME to make sure projects built using rust (for example via
# setuptools-rust) do not pollute user's home directory with cargo bits.
COMPONENT_BUILD_ENV += CARGO_HOME=$(@D)/.cargo

# Make sure the default Python version is installed last and so is the
# canonical version.  This is needed for components that keep PYTHON_VERSIONS
# set to more than single value, but deliver unversioned binaries in usr/bin or
# other overlapping files.
define python-order-rule
$(BUILD_DIR)/%-$(PYTHON_VERSION)/.installed:	$(BUILD_DIR)/%-$(1)/.installed
endef
$(foreach pyver,$(filter-out $(PYTHON_VERSION),$(PYTHON_VERSIONS)),$(eval $(call python-order-rule,$(pyver))))

# We need to copy the source dir to avoid its modification by install target
# where egg-info is re-generated
CLONEY_ARGS = CLONEY_MODE="copy"

COMPONENT_BUILD_CMD = $(PYTHON) setup.py --no-user-cfg build $(COMPONENT_BUILD_SETUP_PY_ARGS)

# build the configured source
$(BUILD_DIR)/%/.built:	$(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(ENV) $(CLONEY_ARGS) $(CLONEY) $(SOURCE_DIR) $(@D)
	$(COMPONENT_PRE_BUILD_ACTION)
	(cd $(@D)$(COMPONENT_SUBDIR:%=/%) ; $(ENV) $(COMPONENT_BUILD_ENV) \
		$(COMPONENT_BUILD_CMD) $(COMPONENT_BUILD_ARGS))
	$(COMPONENT_POST_BUILD_ACTION)
	$(TOUCH) $@


COMPONENT_INSTALL_CMD = $(PYTHON) setup.py --no-user-cfg install

COMPONENT_INSTALL_ARGS +=	--root $(PROTO_DIR) 
COMPONENT_INSTALL_ARGS +=	--install-lib=$(PYTHON_LIB)
COMPONENT_INSTALL_ARGS +=	--install-data=$(PYTHON_DATA)
COMPONENT_INSTALL_ARGS +=	--skip-build
COMPONENT_INSTALL_ARGS +=	--force

# install the built source into a prototype area
$(BUILD_DIR)/%/.installed:	$(BUILD_DIR)/%/.built
	$(COMPONENT_PRE_INSTALL_ACTION)
	(cd $(@D)$(COMPONENT_SUBDIR:%=/%) ; $(ENV) $(COMPONENT_INSTALL_ENV) \
		$(COMPONENT_INSTALL_CMD) $(COMPONENT_INSTALL_ARGS))
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@

ifeq ($(strip $(SINGLE_PYTHON_VERSION)),no)
# Rename binaries in /usr/bin to contain version number
COMPONENT_POST_INSTALL_ACTION += \
	for f in $(PROTOUSRBINDIR)/* ; do \
		[[ -f $$f ]] || continue ; \
		for v in $(PYTHON_VERSIONS) ; do \
			[[ "$$f" == "$${f%%$$v}" ]] || continue 2 ; \
		done ; \
		$(MV) $$f $$f-$(PYTHON_VERSION) ; \
	done ;
endif

# Remove any previous dependency files
COMPONENT_POST_INSTALL_ACTION +=	$(RM) $(@D)/.depend-runtime $(@D)/.depend-test ;

# Define Python version specific filenames for tests.
ifeq ($(strip $(USE_COMMON_TEST_MASTER)),no)
COMPONENT_TEST_MASTER =	$(COMPONENT_TEST_RESULTS_DIR)/results-$(PYTHON_VERSION).master
endif
COMPONENT_TEST_BUILD_DIR = $(BUILD_DIR)/test-$(PYTHON_VERSION)
COMPONENT_TEST_OUTPUT =	$(COMPONENT_TEST_BUILD_DIR)/test-$(PYTHON_VERSION)-results
COMPONENT_TEST_DIFFS =	$(COMPONENT_TEST_BUILD_DIR)/test-$(PYTHON_VERSION)-diffs
COMPONENT_TEST_SNAPSHOT = $(COMPONENT_TEST_BUILD_DIR)/results-$(PYTHON_VERSION).snapshot
COMPONENT_TEST_TRANSFORM_CMD = $(COMPONENT_TEST_BUILD_DIR)/transform-$(PYTHON_VERSION)-results

# Generic transforms for Python test results.
# See below for test style specific transforms.
COMPONENT_TEST_TRANSFORMS += "-e 's|$(PYTHON_DIR)|\$$(PYTHON_DIR)|g'"

# Make sure the test environment is prepared before we start tests
COMPONENT_TEST_DEP +=	component-test-environment-prep
# Testing depends on install target because we want to test installed modules
COMPONENT_TEST_DEP +=	$(BUILD_DIR)/%/.installed
# Point Python to the proto area so it is able to find installed modules there
COMPONENT_TEST_ENV +=	PYTHONPATH=$(PROTO_DIR)/$(PYTHON_LIB)

# determine the type of tests we want to run.
ifeq ($(strip $(wildcard $(COMPONENT_TEST_RESULTS_DIR)/results-*.master)),)
TEST_32 = $(PYTHON_32_VERSIONS:%=$(BUILD_DIR)/$(MACH32)-%/.tested)
TEST_64 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.tested)
TEST_NO_ARCH = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH)-%/.tested)
else
TEST_32 = $(PYTHON_32_VERSIONS:%=$(BUILD_DIR)/$(MACH32)-%/.tested-and-compared)
TEST_64 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.tested-and-compared)
TEST_NO_ARCH = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH)-%/.tested-and-compared)
endif

#
# Testing in the Python world is complex.  Python projects usually do not
# support Makefile with common 'check' or 'test' target to get built bits
# tested.
#
# De facto standard way to test Python projects these days is tox which is
# designed and used primarily for release testing; to make sure the released
# python project runs on all supported Python versions, platforms, etc.  tox
# does so using virtualenv and creates isolated test environments where the
# tested package together with all its dependencies is automatically installed
# (using pip) and tested.  This is great for Python projects developers but it
# is hardly usable for operating system distributions like OpenIndiana.
#
# We do not need such release testing.  Instead we need something closer to
# integration testing: we need to test the built component in our real
# environment without automatic installation of any dependencies using pip.  In
# addition, we need to run tests only for Python versions we actually support
# and the component is built for.
#
# To achieve that we do few things.  First, to avoid isolated environments
# (virtualenv) we run tox with the tox-current-env plugin.  Second, to test
# only Python versions we are interested in we use -e option for tox to select
# single Python version only.  Since we run separate test target per Python
# version this will make sure we test all needed Python versions.
#
# The tox tool itself uses some other tools under the hood to run tests, for
# example pytest.  Some projects could even support pytest testing directly
# without support for tox.  For such projects we offer separate "pytest"-style
# testing.
#
# For projects that do not support testing using neither tox nor pytest we
# offer either unittest or (deprecated) "setup.py test" testing too.
#
# The TEST_STYLE variable is used to select (or force) particular test style
# for Python projects.  Valid values are:
#
# 	tox		- "tox"-style testing
# 	pytest		- "pytest"-style testing
# 	unittest	- "unittest"-style testing
# 	setup.py	- "setup.py test"-style testing
# 	none		- no testing is supported (or desired) at all
#

TEST_STYLE ?= tox
ifeq ($(strip $(TEST_STYLE)),tox)
COMPONENT_TEST_ENV +=		PATH=$(PATH)	# https://github.com/tox-dev/tox/issues/2538
COMPONENT_TEST_ENV +=		PYTEST_ADDOPTS="$(PYTEST_ADDOPTS)"
COMPONENT_TEST_ENV +=		NOSE_VERBOSE=2
COMPONENT_TEST_CMD =		$(TOX)
COMPONENT_TEST_ARGS =		--current-env --no-provision
COMPONENT_TEST_ARGS +=		--recreate
COMPONENT_TEST_ARGS +=		$(TOX_TESTENV)
COMPONENT_TEST_TARGETS =

TOX_TESTENV = -e py$(shell echo $(PYTHON_VERSION) | tr -d .)

# Make sure following tools are called indirectly to properly support tox-current-env
TOX_CALL_INDIRECTLY += py.test
TOX_CALL_INDIRECTLY += pytest
TOX_CALL_INDIRECTLY += coverage
TOX_CALL_INDIRECTLY += zope-testrunner
TOX_CALL_INDIRECTLY.zope-testrunner = zope.testrunner
TOX_CALL_INDIRECTLY += sphinx-build
TOX_CALL_INDIRECTLY.sphinx-build = sphinx.cmd.build
TOX_CALL_INDIRECTLY += nosetests
TOX_CALL_INDIRECTLY.nosetests = nose
$(foreach indirectly, $(TOX_CALL_INDIRECTLY), $(eval TOX_CALL_INDIRECTLY.$(indirectly) ?= $(indirectly)))
COMPONENT_PRE_TEST_ACTION += COMPONENT_TEST_DIR=$(COMPONENT_TEST_DIR) ;
COMPONENT_PRE_TEST_ACTION += \
	$(foreach indirectly, $(TOX_CALL_INDIRECTLY), \
		[ -f $$COMPONENT_TEST_DIR/tox.ini ] && \
			$(GSED) -i -e '/^commands *=/,/^$$/{ \
				s/^\(\(commands *=\)\{0,1\}[ \t]*\)'$(indirectly)'\([ \t]\{1,\}.*\)\{0,1\}$$/\1python -m '$(TOX_CALL_INDIRECTLY.$(indirectly))'\3/ \
			}' $$COMPONENT_TEST_DIR/tox.ini ; \
	)
COMPONENT_PRE_TEST_ACTION += true ;

# Normalize tox test results.
COMPONENT_TEST_TRANSFORMS += "-e 's/py$(shell echo $(PYTHON_VERSION) | tr -d .)/py\$$(PYV)/g'"	# normalize PYV
COMPONENT_TEST_TRANSFORMS += "-e '/^py\$$(PYV) installed:/d'"		# depends on set of installed packages
COMPONENT_TEST_TRANSFORMS += "-e '/PYTHONHASHSEED/d'"			# this is random

# Normalize zope.testrunner test results
COMPONENT_TEST_TRANSFORMS += \
	"-e 's/ in \([0-9]\{1,\} minutes \)\{0,1\}[0-9]\{1,\}\.[0-9]\{3\} seconds//'"	# timing

# Remove timing for tox 4 test results
COMPONENT_TEST_TRANSFORMS += "-e 's/^\(  py\$$(PYV): OK\) (.* seconds)$$/\1/'"
COMPONENT_TEST_TRANSFORMS += "-e 's/^\(  congratulations :)\) (.* seconds)$$/\1/'"

# sort list of Sphinx doctest results
COMPONENT_TEST_TRANSFORMS += \
	"| ( \
		$(GSED) -u -e '/^running tests\.\.\.$$/q' ; \
		$(GSED) -u -e '/^Doctest summary/Q' \
			| $(NAWK) '/^$$/{\$$0=\"\\\\n\"}1' ORS='|' \
			| $(GNU_GREP) -v '^|$$' \
			| $(SORT) \
			| tr -d '\\\\n' | tr '|' '\\\\n' \
			| $(NAWK) '{print}END{if(NR>0)printf(\"\\\\nDoctest summary\\\\n\")}' ; \
		$(CAT) \
	) | $(COMPONENT_TEST_TRANSFORMER)"

# tox package together with the tox-current-env plugin is needed
USERLAND_TEST_REQUIRED_PACKAGES += library/python/tox
USERLAND_TEST_REQUIRED_PACKAGES += library/python/tox-current-env

# Generate raw lists of test dependencies per Python version
# Please note we set PATH below four times for $(COMPONENT_TEST_CMD) (aka tox)
# to workaround https://github.com/tox-dev/tox/issues/2538
COMPONENT_POST_INSTALL_ACTION += \
	if [ -x "$(COMPONENT_TEST_CMD)" ] ; then \
		cd $(@D)$(COMPONENT_SUBDIR:%=/%) ; \
		echo "Testing dependencies:" ; \
		PATH=$(PATH) $(COMPONENT_TEST_CMD) -qq --no-provision --print-deps-to=- $(TOX_TESTENV) || exit 1 ; \
		echo "Testing extras:" ; \
		PATH=$(PATH) $(COMPONENT_TEST_CMD) -qq --no-provision --print-extras-to=- $(TOX_TESTENV) || exit 1 ; \
		( PATH=$(PATH) $(COMPONENT_TEST_CMD) -qq --no-provision --print-deps-to=- $(TOX_TESTENV) \
			| $(WS_TOOLS)/python-resolve-deps \
				PYTHONPATH=$(PROTO_DIR)/$(PYTHON_DIR)/site-packages:$(PROTO_DIR)/$(PYTHON_LIB) \
				$(PYTHON) $(WS_TOOLS)/python-requires $(COMPONENT_NAME) \
			| $(PYTHON) $(WS_TOOLS)/python-requires - ; \
		for e in $$(PATH=$(PATH) $(COMPONENT_TEST_CMD) -qq --no-provision --print-extras-to=- $(TOX_TESTENV)) ; do \
			PYTHONPATH=$(PROTO_DIR)/$(PYTHON_DIR)/site-packages:$(PROTO_DIR)/$(PYTHON_LIB) \
				$(PYTHON) $(WS_TOOLS)/python-requires $(COMPONENT_NAME) $$e ; \
		done ) | $(GSED) -e '/^tox\(-current-env\)\?$$/d' >> $(@D)/.depend-test ; \
	fi ;
else ifeq ($(strip $(TEST_STYLE)),pytest)
COMPONENT_TEST_CMD =		$(PYTHON) -m pytest
COMPONENT_TEST_ARGS =		$(PYTEST_ADDOPTS)
COMPONENT_TEST_TARGETS =

USERLAND_TEST_REQUIRED_PACKAGES += library/python/pytest
else ifeq ($(strip $(TEST_STYLE)),unittest)
COMPONENT_TEST_CMD =		$(PYTHON) -m unittest
COMPONENT_TEST_ARGS =
COMPONENT_TEST_ARGS +=		--verbose
COMPONENT_TEST_TARGETS =
else ifeq ($(strip $(TEST_STYLE)),setup.py)
# Old and deprecated "setup.py test"-style testing
COMPONENT_TEST_CMD =		$(PYTHON) setup.py
COMPONENT_TEST_ARGS =		--no-user-cfg
COMPONENT_TEST_TARGETS =	test
else ifeq ($(strip $(TEST_STYLE)),none)
TEST_TARGET = $(NO_TESTS)
endif

# Run pytest verbose to get separate line per test in results output
PYTEST_ADDOPTS += --verbose

# Force pytest to not use colored output so the results normalization is unaffected
PYTEST_ADDOPTS += --color=no

#
# Some pytest plugins are enabled automatically and could affect test results
# or test output.  In a case a component does not expect such a plugin
# installed (it is neither in REQUIRED_PACKAGES nor in TEST_REQUIRED_PACKAGES)
# we simply disable the plugin to get consistent test results.
#
define disable-pytest-plugin
PYTEST_ADDOPTS += $$(if $$(filter library/python/$(2)-$$(subst .,,$$(PYTHON_VERSION)), $$(REQUIRED_PACKAGES) $$(TEST_REQUIRED_PACKAGES)),,-p no:$(1))
endef
$(eval $(call disable-pytest-plugin,black,pytest-black))
$(eval $(call disable-pytest-plugin,checkdocs,pytest-checkdocs))
$(eval $(call disable-pytest-plugin,cov,pytest-cov))
$(eval $(call disable-pytest-plugin,flaky,flaky))
$(eval $(call disable-pytest-plugin,mypy,pytest-mypy))
$(eval $(call disable-pytest-plugin,randomly,pytest-randomly))
$(eval $(call disable-pytest-plugin,relaxed,pytest-relaxed))		# https://github.com/bitprophet/pytest-relaxed/issues/28
$(eval $(call disable-pytest-plugin,reporter,pytest-reporter))		# https://github.com/christiansandberg/pytest-reporter/issues/8

# By default we are not interested in full list of test failures so exit on
# first failure to save time.  This could be easily overridden from environment
# if needed (for example to debug test failures) or in per-component Makefile.
PYTEST_FASTFAIL = -x
PYTEST_ADDOPTS += $(PYTEST_FASTFAIL)

# Normalize pytest test results.  The pytest framework could be used either
# directly or via tox or setup.py so add these transforms for all test styles
# unconditionally.
COMPONENT_TEST_TRANSFORMS += \
	"-e 's/^\(platform sunos5 -- Python \)$(shell echo $(PYTHON_VERSION) | $(GSED) -e 's/\./\\./g')\.[0-9]\{1,\}.*\( -- .*\)/\1\$$(PYTHON_VERSION).X\2/'"
COMPONENT_TEST_TRANSFORMS += "-e '/^Using --randomly-seed=[0-9]\{1,\}$$/d'"	# this is random
COMPONENT_TEST_TRANSFORMS += "-e '/^benchmark: /d'"				# line with version details
COMPONENT_TEST_TRANSFORMS += "-e '/^plugins: /d'"				# order of listed plugins could vary
COMPONENT_TEST_TRANSFORMS += "-e '/^-\{1,\} coverage: /,/^$$/d'"		# remove coverage report
# sort list of pytest unit tests and drop percentage
COMPONENT_TEST_TRANSFORMS += \
	"| ( \
		$(GSED) -u -e '/^=\{1,\} test session starts /q' ; \
		$(GSED) -u -e '/^$$/q' ; \
		$(GSED) -u -e 's/ *\[...%\]$$//' -e '/^$$/Q' | $(SORT) | $(NAWK) '{print}END{if(NR>0)printf(\"\\\\n\")}' ; \
		$(CAT) \
	) | $(COMPONENT_TEST_TRANSFORMER)"
COMPONENT_TEST_TRANSFORMS += \
	"-e 's/^=\{1,\} \(.*\) in [0-9]\{1,\}\.[0-9]\{1,\}s \(([^)]*) \)\?=\{1,\}$$/======== \1 ========/'"	# remove timing
# Remove slowest durations report for projects that run pytest with --durations option
COMPONENT_TEST_TRANSFORMS += "-e '/^=\{1,\} slowest [0-9]\{1,\} durations =\{1,\}$$/,/^=/{/^=/!d}'"
# Remove short test summary info for projects that run pytest with -r option
COMPONENT_TEST_TRANSFORMS += "-e '/^=\{1,\} short test summary info =\{1,\}$$/,/^=/{/^=/!d}'"

# Normalize setup.py test results.  The setup.py testing could be used either
# directly or via tox so add these transforms for all test styles
# unconditionally.
COMPONENT_TEST_TRANSFORMS += "-e '/SetuptoolsDeprecationWarning:/,+1d'"		# depends on Python version and is useless
COMPONENT_TEST_TRANSFORMS += "-e 's/^\(Ran [0-9]\{1,\} tests\{0,1\}\) in .*$$/\1/'"	# delete timing from test results

COMPONENT_TEST_DIR = $(@D)$(COMPONENT_SUBDIR:%=/%)

# test the built source
$(BUILD_DIR)/%/.tested-and-compared:    $(COMPONENT_TEST_DEP)
	$(RM) -rf $(COMPONENT_TEST_BUILD_DIR)
	$(MKDIR) $(COMPONENT_TEST_BUILD_DIR)
	$(COMPONENT_PRE_TEST_ACTION)
	-(cd $(COMPONENT_TEST_DIR) ; \
		$(COMPONENT_TEST_ENV_CMD) $(COMPONENT_TEST_ENV) \
		$(COMPONENT_TEST_CMD) \
		$(COMPONENT_TEST_ARGS) $(COMPONENT_TEST_TARGETS)) \
		&> $(COMPONENT_TEST_OUTPUT)
	$(COMPONENT_POST_TEST_ACTION)
	$(COMPONENT_TEST_CREATE_TRANSFORMS)
	$(COMPONENT_TEST_PERFORM_TRANSFORM)
	$(COMPONENT_TEST_COMPARE)
	$(COMPONENT_TEST_CLEANUP)
	$(TOUCH) $@

$(BUILD_DIR)/%/.tested:    SHELLOPTS=pipefail
$(BUILD_DIR)/%/.tested:    $(COMPONENT_TEST_DEP)
	$(RM) -rf $(COMPONENT_TEST_BUILD_DIR)
	$(MKDIR) $(COMPONENT_TEST_BUILD_DIR)
	$(COMPONENT_PRE_TEST_ACTION)
	(cd $(COMPONENT_TEST_DIR) ; \
		$(COMPONENT_TEST_ENV_CMD) $(COMPONENT_TEST_ENV) \
		$(COMPONENT_TEST_CMD) \
		$(COMPONENT_TEST_ARGS) $(COMPONENT_TEST_TARGETS)) \
		|& $(TEE) $(COMPONENT_TEST_OUTPUT)
	$(COMPONENT_POST_TEST_ACTION)
	$(COMPONENT_TEST_CREATE_TRANSFORMS)
	$(COMPONENT_TEST_PERFORM_TRANSFORM)
	$(COMPONENT_TEST_CLEANUP)
	$(TOUCH) $@


ifeq ($(strip $(SINGLE_PYTHON_VERSION)),no)
# We need to add -$(PYV) to package fmri
GENERATE_EXTRA_CMD += | \
	$(GSED) -e 's/^\(set name=pkg.fmri [^@]*\)\(.*\)$$/\1-$$(PYV)\2/'
endif

# Add runtime dependencies from project metadata to generated manifest
GENERATE_EXTRA_DEPS += $(BUILD_DIR)/META.depend-runtime.res
GENERATE_EXTRA_CMD += | \
	$(CAT) - <( \
		echo "" ; \
		echo "\# python modules are unusable without python runtime binary" ; \
		echo "depend type=require fmri=__TBD pkg.debug.depend.file=python\$$(PYVER) \\" ; \
		echo "    pkg.debug.depend.path=usr/bin" ; \
		echo "" ; \
		echo "\# Automatically generated dependencies based on distribution metadata" ; \
		$(CAT) $(BUILD_DIR)/META.depend-runtime.res \
	)

# Add runtime dependencies from project metadata to REQUIRED_PACKAGES
REQUIRED_PACKAGES_RESOLVED += $(BUILD_DIR)/META.depend-runtime.res


# Generate raw lists of runtime dependencies per Python version
COMPONENT_POST_INSTALL_ACTION += \
	PYTHONPATH=$(PROTO_DIR)/$(PYTHON_DIR)/site-packages:$(PROTO_DIR)/$(PYTHON_LIB) \
		$(PYTHON) $(WS_TOOLS)/python-requires $(COMPONENT_NAME) >> $(@D)/.depend-runtime ;

# Convert raw per version lists of runtime dependencies to single resolved
# runtime dependency list.  The dependency on META.depend-test.required here is
# purely to get the file created as a side effect of this target.
$(BUILD_DIR)/META.depend-runtime.res:	$(INSTALL_$(MK_BITS)) $(BUILD_DIR)/META.depend-test.required
	$(CAT) $(INSTALL_$(MK_BITS):%.installed=%.depend-runtime) | $(SORT) -u \
		| $(GSED) -e 's/.*/depend type=require fmri=pkg:\/library\/python\/&-$$(PYV)/' > $@

# Generate raw lists of test dependencies per Python version
COMPONENT_POST_INSTALL_ACTION += \
	cd $(@D)$(COMPONENT_SUBDIR:%=/%) ; \
	for f in $(TEST_REQUIREMENTS) ; do \
		$(CAT) $$f ; \
	done | $(WS_TOOLS)/python-resolve-deps \
		PYTHONPATH=$(PROTO_DIR)/$(PYTHON_DIR)/site-packages:$(PROTO_DIR)/$(PYTHON_LIB) \
		$(PYTHON) $(WS_TOOLS)/python-requires $(COMPONENT_NAME) \
	| $(PYTHON) $(WS_TOOLS)/python-requires - >> $(@D)/.depend-test ;

# Convert raw per version lists of test dependencies to single list of
# TEST_REQUIRED_PACKAGES entries
$(BUILD_DIR)/META.depend-test.required:	$(INSTALL_$(MK_BITS))
	$(CAT) $(INSTALL_$(MK_BITS):%.installed=%.depend-test) | $(SORT) -u \
		| $(GSED) -e 's/.*/TEST_REQUIRED_PACKAGES.python += library\/python\/&/' > $@

# Add META.depend-test.required to the generated list of REQUIRED_PACKAGES
REQUIRED_PACKAGES_TRANSFORM += -e '$$r $(BUILD_DIR)/META.depend-test.required'

# The python-requires script requires packaging to provide useful output but
# packaging might be unavailable during bootstrap until we reach bootstrap
# checkpoint 2.  So require it conditionally.
ifeq ($(filter $(strip $(COMPONENT_NAME)),$(PYTHON_BOOTSTRAP_CHECKPOINT_2)),)
USERLAND_REQUIRED_PACKAGES.python += library/python/packaging
endif


clean::
	$(RM) -r $(SOURCE_DIR) $(BUILD_DIR)

# Make it easy to construct a URL for a pypi source download.
pypi_url_multi = pypi:///$(COMPONENT_NAME_$(1))==$(COMPONENT_VERSION_$(1))
pypi_url_single = pypi:///$(COMPONENT_NAME)==$(COMPONENT_VERSION)
pypi_url = $(if $(COMPONENT_NAME_$(1)),$(pypi_url_multi),$(pypi_url_single))
