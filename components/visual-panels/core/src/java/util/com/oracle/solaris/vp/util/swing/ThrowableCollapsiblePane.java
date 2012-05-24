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
 * Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.util.swing;

import java.awt.*;
import javax.swing.JScrollPane;
import com.oracle.solaris.vp.util.misc.finder.Finder;

/**
 * The {@code ThrowableCollapsiblePane} class displays a {@code Throwable}
 * within a {@link CollapsiblePane}.
 */
@SuppressWarnings({"serial"})
public class ThrowableCollapsiblePane extends LinkCollapsiblePane {
    //
    // Instance data
    //

    private ThrowableEditorPane tPane;

    //
    // Constructors
    //

    public ThrowableCollapsiblePane() {
	tPane = new ThrowableEditorPane() {
	    @Override
	    public Dimension getPreferredScrollableViewportSize() {
		FontMetrics metrics = getFontMetrics(
		    getFont().deriveFont(Font.BOLD));
		Dimension d = super.getPreferredScrollableViewportSize();

		// Set scroll pane size (3 lines heigh, 20 characters wide)
		d.height = Math.min(3 * metrics.getHeight(), d.height);
		d.width = Math.min(20 * metrics.charWidth('e'), d.width);

		return d;
	    }

	    @Override
	    public boolean getScrollableTracksViewportWidth() {
		return true;
	    }
	};
	tPane.setOpaque(false);

	JScrollPane scroll = new ExtScrollPane(tPane);
	getContentPane().add(scroll);
    }

    public ThrowableCollapsiblePane(Throwable t) {
	this();
	tPane.setThrowable(t);
    }

    //
    // Component methods
    //

    @Override
    public void setVisible(boolean visible) {
	super.setVisible(visible);
	if (!visible) {
	    setCollapsed(true);
	}
    }

    //
    // LinkCollapsiblePane methods
    //

    @Override
    public String getLinkText(boolean collapsed) {
	return Finder.getString(collapsed ?
	    "error.details.show" : "error.details.hide");
    }

    //
    // ThrowableCollapsiblePane methods
    //

    public ThrowableEditorPane getThrowablePane() {
	return tPane;
    }
}
