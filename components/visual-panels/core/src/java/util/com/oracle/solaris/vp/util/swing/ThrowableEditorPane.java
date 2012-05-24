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

package com.oracle.solaris.vp.util.swing;

import javax.swing.JEditorPane;
import com.oracle.solaris.vp.util.misc.*;

@SuppressWarnings({"serial"})
public class ThrowableEditorPane extends JEditorPane {
    //
    // Instance data
    //

    private Throwable throwable;

    //
    // Constructors
    //

    public ThrowableEditorPane() {
	setContentType("text/html");
	setEditable(false);
    }

    public ThrowableEditorPane(Throwable throwable) {
	this();
	setThrowable(throwable);
    }

    //
    // JTextComponent methods
    //

    @Override
    public void setText(String text) {
	super.setText(text);

	// Scroll to top
	setCaretPosition(0);
    }

    //
    // ThrowableEditorPane methods
    //

    public Throwable getThrowable() {
	return throwable;
    }

    /**
     * Sets the {@code Throwable} to display in this {@code
     * ThrowableEditorPane}.
     *
     * @param	    throwable
     *		    the {@code Throwable} object to display in this {@code
     *		    ThrowableEditorPane}
     */
    public void setThrowable(Throwable throwable) {
	this.throwable = throwable;

	StringBuilder buffer = new StringBuilder();

	while (throwable != null) {
	    buffer.append("<b>").append(
		TextUtil.escapeHTMLChars(throwable.getClass().getName())).
		append("</b><br/><table><tr><td>&nbsp;&nbsp</td><td>");

	    String m = ThrowableUtil.getTrueMessage(throwable);
	    if (m != null) {
		buffer.append(TextUtil.escapeHTMLChars(m));
	    }

	    buffer.append("</td></tr></table>");

	    throwable = throwable.getCause();
	    if (throwable != null) {
		buffer.append("<br/>");
	    }
	}

	setText(buffer.toString());
    }
}
