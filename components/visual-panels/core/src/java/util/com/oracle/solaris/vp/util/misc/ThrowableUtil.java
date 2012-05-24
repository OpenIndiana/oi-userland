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

public class ThrowableUtil {
    /**
     * Gets the "true" message of the given {@code Throwable}.  Unless a message
     * has explicitly been set in a {@code Throwable}, its message is {@code
     * getCause().toString()}, which may contain a prefix not suitable for
     * display in an error dialog.  So, dig into the {@code Throwable} cause
     * hierarchy to find a {@code Throwable} where the message has explicitly
     * been set.
     */
    public static String getTrueMessage(Throwable t) {
	while (true) {
	    String message = t.getMessage();
	    Throwable cause = t.getCause();

	    if (cause == null ||
		!ObjectUtil.equals(message, cause.toString())) {
		return message;
	    }

	    t = cause;
	}
    }

    /**
     * Appends the stack trace of the current thread to the stack trace in
     * given {@code Throwable}.
     */
    public static void appendStackTrace(Throwable t) {
	StackTraceElement[] throwableStack = t.getStackTrace();
	StackTraceElement[] threadStack =
	    Thread.currentThread().getStackTrace();

	// Strip out the call to Thread.getStackTrace and this method
	int offset = 2;

	StackTraceElement[] stack = new StackTraceElement[
	    throwableStack.length + threadStack.length - offset];

	System.arraycopy(throwableStack, 0, stack, 0, throwableStack.length);

	System.arraycopy(threadStack, offset, stack, throwableStack.length,
	    threadStack.length - offset);

	t.setStackTrace(stack);
    }
}
