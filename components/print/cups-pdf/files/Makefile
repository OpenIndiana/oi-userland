all: cups-pdf CUPS-PDF.ppd

cups-pdf: src/cups-pdf.c src/cups-pdf.h
	$(CC) $(CFLAGS) src/cups-pdf.c -lcups -o $@

CUPS-PDF.ppd: extra/CUPS-PDF_opt.ppd
	cp extra/CUPS-PDF_opt.ppd $@

clean:
	rm -f cups-pdf

install: all
	mkdir -p $(DESTDIR)/usr/lib/cups/backend
	mkdir -p $(DESTDIR)/usr/share/cups/model
	mkdir -p $(DESTDIR)/etc/cups
	rm -f $(DESTDIR)/usr/lib/cups/backend/cups-pdf
	rm -f $(DESTDIR)/usr/share/cups/model/CUPS-PDF.ppd
	install -m 500 cups-pdf $(DESTDIR)/usr/lib/cups/backend
	install -m 444 CUPS-PDF.ppd $(DESTDIR)/usr/share/cups/model
	mkdir -p $(DESTDIR)/var/spool/cups-pdf
	mkdir -p $(DESTDIR)/var/spool/cups-pdf/SPOOL
	cp extra/cups-pdf.conf $(DESTDIR)/etc/cups/
