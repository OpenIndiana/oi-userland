#
# Poormans Makefile
#
CFLAGS+= -I. -fPIC
MACH64=amd64
HDRS=synctex_parser.h synctex_parser_utils.h synctex_version.h
SRCS=synctex_parser_utils.c synctex_parser.c
OBJS=$(SRCS:.c=.o)

libsynctex.so.2.0.0: $(OBJS)
	$(CC) $(LDFLAGS) -shared -o $@ $(OBJS) -lz

install: libsynctex.so.2.0.0
	mkdir -p $(DESTDIR)//usr/include/synctex
	cp $(HDRS) $(DESTDIR)/usr/include/synctex
	mkdir -p $(DESTDIR)//usr/lib/$(MACH64)
	cp libsynctex.so.2.0.0 $(DESTDIR)/usr/lib/$(MACH64)
	ln -s libsynctex.so.2.0.0 $(DESTDIR)/usr/lib/$(MACH64)/libsynctex.so.2
	ln -s libsynctex.so.2 $(DESTDIR)/usr/lib/$(MACH64)/libsynctex.so
	mkdir $(DESTDIR)/usr/lib/$(MACH64)/pkgconfig
	cp synctex.pc $(DESTDIR)/usr/lib/$(MACH64)/pkgconfig

clean:
	rm $(OBJS) libsynctex.so.2.0.0
