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

public class IOUtil {
    /**
     * Attempts to close the given {@code Closable}, if non-{@code null}.  Any
     * resulting {@code IOException} is ignored.
     */
    public static void closeIgnore(Closeable closable) {
	if (closable != null) {
	    try {
		closable.close();
	    } catch (IOException ignore) {
	    }
	}
    }

    public static String getFullName(File file) {
	try {
	    return file.getCanonicalPath();
	} catch (IOException e) {
	    return file.getAbsolutePath();
	}
    }
}
