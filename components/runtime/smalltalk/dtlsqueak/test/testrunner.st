| file result testRunner |
Utilities setAuthorInitials:'hipster'.
testRunner _ TestRunner new runAll.
result _ testRunner result.
file _ StandardFileStream fileNamed:'results-32.vm'.
file nextPutAll: 'SUnit Results'; lf.
file nextPutAll: Smalltalk version; lf.
file nextPutAll: Smalltalk osVersion; lf.
file nextPutAll: Smalltalk vmVersion; lf.
file nextPutAll: 'Failed Tests'; lf.
testRunner failedList do:
		[ : each | each printOn:file.  file lf ].
file nextPutAll: 'Errors'; lf.
testRunner errorList do:
		[ : each | each printOn:file.  file lf ].
file nextPutAll: 'Total Number of Passed Tests: '.
result passedCount printOn:file.
file lf.
file nextPutAll: 'Total Number of Failures: '.
result failureCount printOn:file.
file lf.
file nextPutAll: 'Total Number of Errors: '.
result errorCount printOn:file.
file lf.
file close.
Smalltalk quitPrimitive.

