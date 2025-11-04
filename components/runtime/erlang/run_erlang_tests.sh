#!/bin/sh
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

#
# Copyright (c) 2020, 2021, Oracle and/or its affiliates.
#

if [ $# -ne 1 ]; then
  echo "Please specify the path to Erlang source directory!"
  exit 1
fi

SOURCE_DIR="$(realpath $1)"
if [ ! -e "${SOURCE_DIR}/bin/erl" ]; then
  echo "Please build Erlang first by using './otp_build setup -a' command!"
  exit 2
fi

export ERL_TOP="${SOURCE_DIR}"
export TESTROOT="${SOURCE_DIR}/tests"
# to get stable sorting
export LC_ALL=C

# Build the release tests.
cd "${SOURCE_DIR}"
gmake release_tests > /dev/null 2>&1;
if [ $? -ne 0 ]; then
  echo "Failed to build Erlang release tests!"
  exit 3
fi

# Remove the previous logs.
gfind . -name 'suite.log' -delete 2>/dev/null

# Execute the Erlang tests (it takes many hours).
cd "${TESTROOT}/test_server"
rm -f ${SOURCE_DIR}/progress.log
"${SOURCE_DIR}/bin/erl" -s ts install -s init stop > ${SOURCE_DIR}/progress.log 2>&1
for group in $(ls .. | grep _test\$ | sed s@_test\$@@); do
  for i in `ls ../${group}_test/|grep _SUITE.erl|sed s@\.erl@@`; do
    echo "Running group $group suite $i" >> ${SOURCE_DIR}/progress.log 2>&1
    # emulator/trace_local seems to get stuck
    # mnesia_test takes over 1 hour to finish
    timeout -k 30s 10800s "${SOURCE_DIR}/bin/erl" -pa ebin -eval "ts:run($group, $i, [batch]), init:stop()." >> ${SOURCE_DIR}/progress.log 2>&1
    [ "$?" = "124" ] && echo "Test $group $i was killed"
  done
done

# Find the generated logs for Erlang modules.
cd "${SOURCE_DIR}"
ok=0 skipped=0 failed=0 total=0
SUITE_LOGS=$(find . -name 'suite.log' 2>/dev/null | grep -v 'log_private' | gsort)

for LOG_PATH in $(echo "${SUITE_LOGS}"); do
  # Extract the name of the tested module from the path.
  MODULE=$(echo "${LOG_PATH}" | gcut -d'/' -f5 | gcut -d'.' -f2)
  echo "***** Results for ${MODULE} *****"

  # Filter the relevant results from the log file and ensure reproducibility.
  FILTER_REGEXP="^(=case|=result|=== TEST COMPLETE,|=== EXIT,)[[:space:]]"
  ggrep -E "${FILTER_REGEXP}" "${LOG_PATH}" | perl -pe "s/$(hostname)/HOSTNAME/g" | \
    perl -pe "s|${SOURCE_DIR}|BUILD_DIR|" | perl -pe 'if(/^=result/) { $_ =~ s/\d*\.?\d+/NUMBER/g; }'

  # Count the overall statistics to print it after the test logs are processed.
  results=$(grep '=== TEST COMPLETE' "${LOG_PATH}")
  if [ -n "${results}" ]; then
    suite_ok=$(echo "${results}" | perl -ne 'if(/([\d]+) ok/) { print $1 } else { print 0 }')
    suite_failed=$(echo "${results}" | perl -ne 'if(/([\d]+) failed/) { print $1 } else { print 0 }')
    suite_skipped=$(echo "${results}" | perl -ne 'if(/([\d]+) skipped/) { print $1 } else { print 0 }')
    suite_total=$(echo "${results}" | perl -ne 'if(/of ([\d]+) test cases/) { print $1 } else { print 0 }')
    ok=$((ok+${suite_ok}))
    failed=$((failed+${suite_failed}))
    skipped=$((skipped+${suite_skipped}))
    total=$((total+${suite_total}))
  else
    echo "Cannot find the result line for ${MODULE}!"
  fi

  echo ""
done

echo "##### RESULTS SUMMARY #####"
echo "ok: ${ok} cases"
echo "skipped: ${skipped} cases"
echo "failed: ${failed} cases"
echo "total: ${total} cases"

exit 0
