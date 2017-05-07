global tcl_platform
if {$tcl_platform(wordSize) == 8} {
  package ifneeded Pgtcl 1.9  [list load [file join $dir amd64/libpgtcl1.9.so]]
} else {
  package ifneeded Pgtcl 1.9  [list load [file join $dir libpgtcl1.9.so]]
}
