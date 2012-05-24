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

package com.oracle.solaris.vp.panel.common.control;

@SuppressWarnings({"serial"})
public class InvalidParameterException extends NavigationException {
    //
    // Instance data
    //

    private String id;
    private String parameter;
    private String value;

    //
    // Constructors
    //

    public InvalidParameterException(String id, String parameter, String value,
	Throwable cause) {

	super(String.format("invalid parameter \"%s\" for Control \"%s\": %s",
	    id, parameter, value), cause);

	this.id = id;
	this.parameter = parameter;
	this.value = value;
    }

    public InvalidParameterException(String id, String parameter,
	String value) {

	this(id, parameter, value, null);
    }

    public InvalidParameterException(String id, String parameter) {
	this(id, parameter, null);
    }

    //
    // InvalidParameterException methods
    //

    public String getControlId() {
	return id;
    }

    public String getParameter() {
	return parameter;
    }

    public String getValue() {
	return value;
    }
}
