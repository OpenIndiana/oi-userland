/*
 * Copyright (c) 2009, 2015, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * We seem currently unable to depend properly on existing D libraries (like
 * ftp.d). But the definitions for conninfo_t and ftpinfo_t are stored there
 * (and have to be, since that's where the real translators live). So we're
 * forced to define something here to satisfy dtrace(1M), but none of the
 * definitions or translators here are actually used.
 */
typedef struct ftpinfo {
	int dummy;
} ftpinfo_t;

typedef struct ftpproto {
	int dummy;
} ftpproto_t;

typedef struct conninfo {
	int dummy;
} conninfo_t;

translator conninfo_t <ftpproto_t *dp> {
	dummy = 0;
};

translator ftpinfo_t <ftpproto_t *dp> {
	dummy = 0;
};

provider ftp {
	probe transfer__start(ftpproto_t *p) :
	    (conninfo_t *p, ftpinfo_t *p);
	probe transfer__done(ftpproto_t *p) :
	    (conninfo_t *p, ftpinfo_t *p);
};

#pragma D attributes Evolving/Evolving/ISA provider ftp provider
#pragma D attributes Private/Private/Unknown provider ftp module
#pragma D attributes Private/Private/Unknown provider ftp function
#pragma D attributes Private/Private/ISA provider ftp name
#pragma D attributes Evolving/Evolving/ISA provider ftp args
