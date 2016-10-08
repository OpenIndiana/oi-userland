#! /bin/sh

for test in \
    test_adapter \
    test_advice \
    test_declarations \
    test_document \
    test_element \
    test_exceptions \
    test_odd_declarations \
    test_registry \
    test_ro \
    test_sorting \
    test_verify \
    ; do
	${PYTHON} src/zope/interface/tests/${test}.py
done
