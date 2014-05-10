#! /bin/sh

for test in \
    test_advice \
    test_document \
    test_element \
    test_odd_declarations \
    test_sorting \
    test_verify \
    ; do
	${PYTHON} src/zope/interface/tests/${test}.py
done
