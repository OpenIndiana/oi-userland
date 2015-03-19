#! /bin/sh

for test in \
    test_api \
    test_normalizers \
    test_unicode_support \
    test_uri \
    ; do
	${PYTHON} tests/${test}.py
done
