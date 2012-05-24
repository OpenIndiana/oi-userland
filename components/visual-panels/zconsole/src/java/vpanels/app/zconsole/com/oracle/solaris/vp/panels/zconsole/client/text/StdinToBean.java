/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panels.zconsole.client.text;

import java.io.*;
import java.util.logging.Level;
import com.oracle.solaris.rad.ObjectException;
import com.oracle.solaris.rad.zonesbridge.IOMXBean;
import com.oracle.solaris.vp.util.misc.*;

public abstract class StdinToBean extends ZoneIOThread {
    //
    // Static data
    //

    public static final byte _ESCAPE = (byte)'~';
    public static final byte ESCAPE_DISCONNECT = (byte)'.';

    private static final byte[] ESCAPES = {
	ESCAPE_DISCONNECT,
    };

    //
    // Instance data
    //

    private byte escape;
    private boolean noext;

    //
    // Constructors
    //

    public StdinToBean(IOMXBean bean, long token, byte escape, boolean noext) {
	super(bean, token);
	this.escape = escape;
	this.noext = noext;
    }

    //
    // Runnable methods
    //

    @Override
    public void run() {
	boolean success = true;
	IOMXBean bean = getBean();
	long token = getToken();

	try {
	    InputStream in = TermUtil.getStdIn();

	    // Bytes to write to the bean
	    ByteArrayOutputStream bout =
		new ByteArrayOutputStream(BLOCKSIZE);

	    // The number of bytes at the end of the previous read,
	    // unwritten because they could be the start of an escape
	    // sequence
	    //	0 - newline (written)
	    //	1 - newline (written), escape byte (not written)
	    // -1 - otherwise
	    // When first starting, pretend we just saw a newline
	    int nPending = 0;

	    byte[] bytes = new byte[BLOCKSIZE];
	    int n;
	    OUTER: while ((n = in.read(bytes)) != -1) {
		int i = 0;
		while (i < n) {
		    bout.reset();

		    // The escaped byte, or null if none found
		    Byte escapedByte = null;

		    for (; i < n && escapedByte == null; i++) {
			byte b = bytes[i];
			if (nPending == 0) {
			    if (!noext && b == escape) {
				nPending++;
			    } else {
				nPending = -1;
			    }
			} else if (nPending == 1) {
			    nPending = -1;
			    if (ArrayUtil.contains(ESCAPES, b)) {
				escapedByte = b;
				continue;
			    }

			    // Two escapes == literal escape byte
			    if (b != escape) {
				bout.write(escape);
			    }
			}

			if (nPending == -1) {
			    bout.write(b);
			    // Newline must precede escape sequence but is
			    // not part of it
			    if (b == (byte)'\n' || b == (byte)'\r') {
				nPending++;
			    }
			}
		    }

		    if (bout.size() != 0) {
			byte[] write = bout.toByteArray();
			bout.reset();
			bean.write(token, write);
		    }

		    if (escapedByte != null) {
			switch (escapedByte) {
			case ESCAPE_DISCONNECT:
			    break OUTER;
			default:
			    assert (false);
			}
		    }
		}
	    }
	} catch (InterruptedIOException e) {
	    // Not an error!

	} catch (IOException e) {
	    getLog().log(Level.SEVERE, "unable to read from stdin", e);
	    success = false;

	} catch (ObjectException e) {
	    getLog().log(Level.SEVERE, "unable to write to console", e);
	    success = false;
	}

	done(success);
    }
}
