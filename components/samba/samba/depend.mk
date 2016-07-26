# only one of samba or samba30 can concurrently try to build mozldap, so
# we let samba30 run first.
samba/samba:	samba/mozldap samba/samba30
