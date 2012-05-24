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

package com.oracle.solaris.vp.panel.common.control;

import java.util.Arrays;
import com.oracle.solaris.vp.util.misc.ArrayIterator;

@SuppressWarnings({"serial"})
public class InvalidAddressException extends NavigationException {
    //
    // Instance data
    //

    private Navigable[] path;
    private Navigable invalid;

    //
    // Constructors
    //

    /**
     * Constructs an {@code InvalidAddressException}.
     *
     * @param	    message
     *		    a descriptive message
     *
     * @param	    path
     *		    the current (absolute) path (may be empty)
     *
     * @param	    invalid
     *		    the invalid path component
     */
    public InvalidAddressException(String message, Navigable[] path,
	Navigable invalid) {

	super(message);
	this.path = path;
	this.invalid = invalid;
    }

    public InvalidAddressException(Navigable[] path, Navigable invalid) {
	this(toPath(path, invalid), path, invalid);
    }

    //
    // InvalidAddressException methods
    //

    /**
     * Gets the current (absolute) path.
     */
    public Navigable[] getCurrentPath() {
	return path;
    }

    public Navigable getInvalidPathComponent() {
	return invalid;
    }

    public String toPath() {
	return toPath(path, invalid);
    }

    //
    // Static methods
    //

    private static String toPath(Navigable[] path, Navigable invalid) {
	Navigable[] newPath = Arrays.copyOf(path, path.length + 1);
	newPath[newPath.length - 1] = invalid;
	Iterable<Navigable> iterator = new ArrayIterator<Navigable>(newPath);
	return Navigator.getPathString(iterator);
    }
}
