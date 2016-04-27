#
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

all:
	$(CP) ftp_provider_impl.h $(BD)/modules
	/usr/sbin/dtrace -xnolibs -C -h -s ftp_provider.d \
		-o $(BD)/modules/ftp_provider.h
	$(CC) -m$(BITS) -c ftp_provider_impl.c -I $(BD)/modules \
		-o $(BD)/modules/ftp_provider_impl.o
	/usr/sbin/dtrace -G -$(BITS) -xnolibs -C -s ftp_provider.d \
		-o "$(BD)"/modules/ftp_provider.o \
		$(BD)/modules/ftp_provider_impl.o
	echo "modules/ftp_provider_impl.o" >> $(BD)/module-libs.txt
	echo "modules/ftp_provider.o" >> $(BD)/module-libs.txt
