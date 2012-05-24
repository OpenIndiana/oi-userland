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

package com.oracle.solaris.vp.panels.apache.client.swing;

@SuppressWarnings({"serial"})
public class VirtualHostSSLValidationException
    extends VirtualHostValidationException {

    //
    // Constructors
    //

    public VirtualHostSSLValidationException(String id) {
	super(id);
    }

    public VirtualHostSSLValidationException(String id, String message) {
	super(id, message);
    }

    public VirtualHostSSLValidationException(String id, Throwable cause) {
	super(id, cause);
    }

    public VirtualHostSSLValidationException(String id, String message,
	Throwable cause) {
	super(id, message, cause);
    }
}
