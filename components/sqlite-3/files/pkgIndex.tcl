package ifneeded sqlite3 3.6 [list load [file join $dir [expr $::tcl_platform(wordSize) * 8] libtclsqlite3.so] sqlite3]
