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

public class ProcessResult {
    //
    // Instance data
    //

    private String[] command;
    private int exitValue;
    private byte[] stdout;
    private byte[] stderr;

    //
    // Constructors
    //

    public ProcessResult(String[] command, int exitValue, byte[] stdout,
	byte[] stderr) {

	this.command = command;
	this.exitValue = exitValue;
	this.stdout = stdout;
	this.stderr = stderr;
    }

    //
    // ProcessResult methods
    //

    public String[] getCommand() {
	return command;
    }

    public int getExitValue() {
	return exitValue;
    }

    public byte[] getStdout() {
	return stdout;
    }

    public String getStdoutAsString() {
	return getAsString(stdout);
    }

    public String[] getStdoutAsStrings() {
	return getAsStrings(stdout);
    }

    public byte[] getStderr() {
	return stderr;
    }

    public String getStderrAsString() {
	return getAsString(stderr);
    }

    public String[] getStderrAsStrings() {
	return getAsStrings(stderr);
    }

    //
    // Private methods
    //

    private String getAsString(byte[] b) {
	return new String(b).replaceFirst("(\r?\n)+$", "");
    }

    private String[] getAsStrings(byte[] b) {
	return new String(b).split("\r?\n", -1);
    }
}
