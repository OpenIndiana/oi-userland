
all:
	@MSGCAT=$${MSGCAT:-msgcat}; \
	MSGCAT_VERSION=`$$MSGCAT --version | head -1 | awk '{print $$NF}'`; \
	MSGCAT_VERSION=`echo $$MSGCAT_VERSION | awk -F. '{ print $$1 * 1000 + $$2  * 100 + $$3; }'`; \
	if [ $$MSGCAT_VERSION -lt 1500 ] ; then \
	  MSGCAT=/usr/bin/msgcat; \
	  MSGCAT_VERSION=`$$MSGCAT --version | head -1 | awk '{print $$NF}'`; \
	  MSGCAT_VERSION=`echo $$MSGCAT_VERSION | awk -F. '{ print $$1 * 1000 + $$2  * 100 + $$3; }'`; \
	  if [ $$MSGCAT_VERSION -lt 1500 ] ; then \
	    printf "msgcat version 0.15 is required for msgctxt\n"; \
	    printf "rf. http://live.gnome.org/GnomeGoals/MsgctxtMigration\n"; \
	    exit 1; \
	  fi; \
	fi; \
	\
	for po_sun in $(POFILES); do \
	  po=$(PODIR)/$$po_sun; \
	  if test ! -f $$po; then \
	    continue; \
	  fi; \
	  \
	  echo "Merging $$po_sun ..."; \
	  \
	  header_community=$${po_sun}.header; \
	  I=0; \
	  exec < $$po; \
	  while read line; \
	  do \
	    is_comment=`echo $$line | grep '^#' | grep -v '^#,'`; \
	    if [ x"$$is_comment" = x ] ; then \
	      break; \
	    fi; \
	    I=`expr $$I + 1`; \
	  done; \
	  exec <&-; \
	  if [ $$I -ne 0 ] ; then \
	    sed -ne "1,$${I}p" $$po > $$header_community; \
	  fi; \
	  \
	  po_sun_no_obs=$$po_sun.no_obs; \
	  sed -e "/^#~/d" $$po_sun > $$po_sun_no_obs; \
	  \
	  if [ -f $$header_community ] ; then \
	    $$MSGCAT --use-first $$po_sun_no_obs $$po -o $$po.$$; \
	    cat $$header_community $$po.$$ > $$po; \
	    rm $$header_community $$po.$$; \
	  else \
	    $$MSGCAT --use-first $$po_sun_no_obs $$po -o $$po; \
	  fi; \
	done

top_builddir = ..
PODIR = $(top_builddir)/po
POFILES = $(wildcard *.po)

