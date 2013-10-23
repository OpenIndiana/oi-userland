#! /bin/sh

for test in \
    test_docs \
    test_tzinfo \
    ; do
	${PYTHON} pytz/tests/${test}.py
done
