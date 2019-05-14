# Reserved UIDs and GIDs

These UIDs and GIDs are used by delivered software.

When reserving new id, be careful to avoid conflicts with other software from oi-userland or illumos-gate.
IDs from 0 to 99 are reserved for system purposes. 

## UIDs

UID   | User name
----- | ---------
0     | root
1     | daemon
2     | bin
3     | sys
4     | adm
5     | uucp
9     | nuucp
15    | dladm
16    | netadm
17    | netcfg
18    | dhcpserv
21    | ftp
22    | sshd
25    | smmsp
27    | postfix
37    | listen
40    | puppet
50    | gdm
51    | zfssnap
52    | upnp
53    | named
54    | lightdm
55    | mongodb
56    | couchdb
57    | elasticsearch
58    | redis
60    | xvm
61    | zabbix
62    | dnscrypt
63    | clamav
64    | slurm
65    | \_polkitd
66    | hacluster
67    | jenkins
68    | zookeeper
69    | hadoop
70    | mysql
71    | lp
72    | dovecot
73    | dovenull
75    | openldap
76    | p0f
77    | nut
78    | haproxy
79    | sslh
80    | webservd
81    | udpxy
82    | asterisk
88    | powerdns
90    | postgres
91    | barman
92    | bacula
95    | svctag
96    | unknown
97    | pkg5srv
60001 | nobody
60002 | noaccess
65534 | nobody4

## GIDs

GID   | Group name
----- | ----------
0     | root
1     | other
2     | bin
3     | sys
4     | adm
5     | uucp
6     | mail
7     | tty
8     | lp
9     | nuucp
10    | staff
12    | daemon
14    | sysadmin
20    | games
21    | ftp
22    | sshd
25    | smmsp
27    | postfix
28    | postdrop
40    | puppet
50    | gdm
52    | upnp
53    | named
54    | lightdm
55    | mongodb
56    | couchdb
57    | elasticsearch
58    | redis
59    | vboxsf
60    | xvm
61    | zabbix
62    | dnscrypt
63    | clamav
64    | slurm
65    | netadm
66    | haclient
67    | jenkins
68    | zookeeper
69    | hadoop
70    | mysql
72    | dovecot
75    | openldap
76    | p0f
77    | nut
78    | haproxy
79    | sslh
80    | webservd
81    | udpxy
82    | asterisk
88    | powerdns
90    | postgres
91    | barman
92    | bacula
95    | mlocate
96    | unknown
97    | pkg5srv
60001 | nobody
60002 | noaccess
65534 | nogroup
