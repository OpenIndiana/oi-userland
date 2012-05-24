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
import javax.swing.*;

/**
 * The {@code ExtRootPane} class, when {@link #validate validated}, can
 * optionally:
 * <ol>
 *   <li>
 *     {@link #setAutoResizeEnabled automatically} resize its enclosing {@code
 *     Window} to it's preferred size
 *   </li>
 *   <li>
 *     {@link #setAutoMinSizeEnabled automatically} set its enclosing {@code
 *     Window}'s minimum size to it's preferred size
 *   </li>
 * </ol>
 *
 * Additionally, the {@code ExtRootPane} takes any visible glass pane into
 * account when calculating its preferred size.
 *
 * @see         ExtDialog
 * @see         ExtFrame
 */
@SuppressWarnings({"serial"})
public class ExtRootPane extends JRootPane {
    //
    // Instance data
    //

    private boolean doingValidate;
    private boolean autoResizeEnabled = true;
    private boolean autoMinSizeEnabled = true;

    //
    // Component methods
    //

    @Override
    public void validate() {
	if (!doingValidate && (autoResizeEnabled || autoMinSizeEnabled)) {
	    doingValidate = true;
	    try {
		Window window = SwingUtilities.getWindowAncestor(this);
		if (window != null) {
		    if (autoResizeEnabled) {
			window.pack();
		    }
		    if (autoMinSizeEnabled) {
			window.setMinimumSize(window.getPreferredSize());
		    }
		}
	    } finally {
		doingValidate = false;
	    }
	}
	super.validate();
    }

    @Override
    public Dimension getPreferredSize() {
        Dimension size = super.getPreferredSize();
	if (isPreferredSizeSet()) {
	    return size;
	}

        Component glass = getGlassPane();

        // Resize for glass pane
        if (glass.isVisible()) {
            Dimension gSize = glass.getPreferredSize();
	    if (gSize.width > size.width) {
		size.width = gSize.width;
	    }
	    if (gSize.height > size.height) {
		size.height = gSize.height;
	    }
	}

        return size;
    }

    //
    // ExtRootPane methods
    //

    /**
     * Gets whether auto-minimum size is enabled.
     */
    public boolean isAutoMinSizeEnabled() {
	return autoMinSizeEnabled;
    }

    /**
     * Gets whether auto-resize is enabled.
     */
    public boolean isAutoResizeEnabled() {
	return autoResizeEnabled;
    }

    /**
     * Sets whether auto-minimum size is enabled.
     */
    public void setAutoMinSizeEnabled(boolean autoMinSizeEnabled) {
	this.autoMinSizeEnabled = autoMinSizeEnabled;
    }

    /**
     * Sets whether auto-resize is enabled.
     */
    public void setAutoResizeEnabled(boolean autoResizeEnabled) {
	this.autoResizeEnabled = autoResizeEnabled;
    }
}
