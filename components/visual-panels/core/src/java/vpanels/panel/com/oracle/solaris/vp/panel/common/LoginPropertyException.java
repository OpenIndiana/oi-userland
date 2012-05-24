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

package com.oracle.solaris.vp.panel.common;

import javax.swing.JOptionPane;
import com.oracle.solaris.vp.util.misc.DialogMessage;

public class LoginPropertyException extends Exception {
    //
    // Instance data
    //

    private DialogMessage message;
    private boolean fatal;

    //
    // Constructors
    //

    public LoginPropertyException(DialogMessage message, boolean fatal) {
	super(message.getText());
	this.message = message;
	this.fatal = fatal;
    }

    public LoginPropertyException(String message, boolean fatal) {
	this(new DialogMessage(message, JOptionPane.ERROR_MESSAGE), fatal);
    }

    //
    // LoginPropertyException methods
    //

    public DialogMessage getDialogMessage() {
	return message;
    }

    public boolean isFatal() {
	return fatal;
    }
}
