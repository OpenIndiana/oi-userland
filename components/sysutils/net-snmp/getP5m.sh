#!/bin/bash

# helper script to construct lines to include in net-base-snmp.p5m and net-snmp-documentation.p5m

N='-not -type d'
L='\\\n\t'
cd build/i86/
print '## net-snmp-base.p5m'
S=local/mib2c-conf.d/; D=etc/net-snmp/snmp/mib2c-data/;    find ${S} $N                       -printf "file ${S}%P $L path=${D}%P \n"
S=local/; D=etc/net-snmp/snmp/;                            find ${S} $N -iname 'mib2c.*.conf' -printf "file ${S}%P $L path=${D}%P \n"                  
S=mibs/;  D=etc/net-snmp/snmp/mibs/;                       find ${S} $N -iname '*.txt'        -printf "file ${S}%P $L path=${D}%P \n"                   
S=apps/;  D=etc/net-snmp/snmp/;                            find ${S} $N -iname '*.pl'         -printf "file ${S}%P $L path=${D}%P \n"              
S=local/snmpconf.dir/snmp-data/; D=etc/net-snmp/snmp/snmpconf-data/snmp-data/;           find ${S} $N -printf "file ${S}%P $L path=${D}%P \n"
S=local/snmpconf.dir/snmptrapd-data/; D=etc/net-snmp/snmp/snmpconf-data/snmptrapd-data/; find ${S} $N -printf "file ${S}%P $L path=${D}%P \n"
print '## net-snmp-documentation.p5m'
S=sun/sdk/demo/;  D=usr/demo/net-snmp/;           find ${S} $N -printf "file build/\$(MACH32)/${S}%P $L path=${D}%P \n"
S=docs/html/;     D=usr/share/doc/net-snmp/html/; find ${S} $N -printf "file build/\$(MACH32)/${S}%P $L path=${D}%P \n"
