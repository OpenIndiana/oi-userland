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
 * Copyright (c) 2008, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panel.common.smf;

@SuppressWarnings({"serial"})
public class InvalidScfDataException extends Exception {
    //
    // Instance data
    //

    private String name;
    private String value;

    //
    // Constructors
    //

    public InvalidScfDataException(String name, String value) {
	init(name, value);
    }

    public InvalidScfDataException(String name, String value, String message) {
	super(message);
	init(name, value);
    }

    public InvalidScfDataException(String name, String value, Throwable cause) {
	super(cause);
	init(name, value);
    }

    public InvalidScfDataException(String name, String value, String message,
	Throwable cause) {

	super(message, cause);
	init(name, value);
    }

    //
    // InvalidScfDataException methods
    //

    public String getName() {
	return name;
    }

    public String getValue() {
	return value;
    }

    //
    // Private methods
    //

    private void init(String name, String value) {
	this.name = name;
	this.value = value;
    }
}
