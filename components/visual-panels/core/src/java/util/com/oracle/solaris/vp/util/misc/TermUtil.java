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

package com.oracle.solaris.vp.util.misc;

import java.io.*;
import java.security.*;
import com.oracle.solaris.vp.util.misc.exception.CommandFailedException;

public class TermUtil {
    //
    // Static data
    //

    private static String savedStty;
    private static Thread shutdownHook =
	new Thread() {
	    @Override
	    public void run() {
		try {
		    resetTty();
		} catch (Exception ignore) {
		}
	    }
	};

    //
    // Static methods
    //

    public static FileInputStream getStdIn() {
	return AccessController.doPrivileged(
	    new PrivilegedAction<FileInputStream>() {
		@Override
		public FileInputStream run() {
		    return new FileInputStream(FileDescriptor.in);
		}
	    });
    }

    public synchronized static void setRawTty() throws IOException,
        InterruptedException, CommandFailedException {

	if (savedStty == null) {
	    savedStty = stty("-g").getStdoutAsString();

	    AccessController.doPrivileged(
		new PrivilegedAction<Object>() {
		    @Override
		    public Object run() {
			try {
			    Runtime.getRuntime().addShutdownHook(shutdownHook);
			} catch (IllegalArgumentException ignore) {
			} catch (IllegalStateException ignore) {
			}
			return null;
		    }
		});
	}

	stty("raw -echo");
    }

    public synchronized static void resetTty() throws IOException,
        InterruptedException, CommandFailedException {

	if (savedStty != null) {
	    stty(savedStty);
	    savedStty = null;
	    AccessController.doPrivileged(
		new PrivilegedAction<Object>() {
		    @Override
		    public Object run() {
			try {
			    Runtime.getRuntime().removeShutdownHook(
				shutdownHook);
			} catch (IllegalStateException ignore) {
			}
			return null;
		    }
		});
	}
    }

    //
    // Private static methods
    //

    private static ProcessResult stty(final String args) throws IOException,
	InterruptedException, CommandFailedException {

	final IOException[] ioE = new IOException[1];
	final InterruptedException[] intE = new InterruptedException[1];
	final CommandFailedException[] comE = new CommandFailedException[1];

	ProcessResult result = AccessController.doPrivileged(
	    new PrivilegedAction<ProcessResult>() {
		@Override
		public ProcessResult run() {
		    try {
			return ProcessUtil.exec(0, "/bin/sh", "-c",
			    "/usr/bin/stty " + args + " </dev/tty");
		    } catch (IOException e) {
			ioE[0] = e;
		    } catch (InterruptedException e) {
			intE[0] = e;
		    } catch (CommandFailedException e) {
			comE[0] = e;
		    }
		    return null;
		}
	    });

	if (ioE[0] != null) {
	    throw ioE[0];
	}

	if (intE[0] != null) {
	    throw intE[0];
	}

	if (comE[0] != null) {
	    throw comE[0];
	}

	return result;
    }
}
