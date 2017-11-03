global tcl_platform
if {$tcl_platform(wordSize) == 8} {
  package ifneeded Pgtcl 2.3.2  [list load [file join $dir amd64/libpgtcl2.3.2.so]]
} else {
  package ifneeded Pgtcl 2.3.2  [list load [file join $dir libpgtcl2.3.2.so]]
}
package ifneeded sc_postgres 1.2 \
    [list source [file join $dir postgres-helpers.tcl]]
