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
 * Copyright (c) 2009, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.util.misc;

import java.io.*;
import com.oracle.solaris.vp.util.misc.exception.CommandFailedException;

public class ProcessUtil {
    //
    // Static methods
    //

    /**
     * Runs the given command and waits for it to complete.
     *
     * @param	    command
     *		    the command array
     *
     * @return	    the result of the command
     *
     * @exception   IOException
     *		    if an I/O error occurs
     *
     * @exception   InterruptedException
     *		    if the current thread is interrupted while
     *		    waiting for the process to finish
     */
    public static ProcessResult exec(String... command) throws IOException,
	InterruptedException {

	Process p = Runtime.getRuntime().exec(command);
	p.waitFor();

	int exitValue = p.exitValue();
	byte[] stdout = getBytes(p.getInputStream());
	byte[] stderr = getBytes(p.getErrorStream());

	return new ProcessResult(command, exitValue, stdout, stderr);
    }

    /**
     * Runs the given command and waits for it to complete.
     *
     * @param	    expExitValue
     *		    the expected exit value of the command
     *
     * @param	    command
     *		    the command array
     *
     * @return	    the result of the command
     *
     * @exception   IOException
     *		    if an I/O error occurs
     *
     * @exception   InterruptedException
     *		    if the current thread is interrupted while
     *		    waiting for the process to finish
     *
     * @exception   CommandFailedException
     *		    if the command exits with a result other than {@code
     *		    expExitValue}
     */
    public static ProcessResult exec(int expExitValue, String... command)
	throws IOException, InterruptedException, CommandFailedException {

	ProcessResult result = exec(command);
	if (result.getExitValue() != expExitValue) {
	    throw new CommandFailedException(result);
	}

	return result;
    }

    //
    // Private static methods
    //

    private static byte[] getBytes(InputStream in) {
	ByteArrayOutputStream out = new ByteArrayOutputStream();
	byte[] b = new byte[1024];
	int n;
	try {
	    while ((n = in.read(b)) != -1) {
		out.write(b, 0, n);
	    }
	} catch (IOException unlikely) {
	}
	return out.toByteArray();
    }
}
