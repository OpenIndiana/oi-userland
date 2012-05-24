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

import java.awt.*;
import javax.swing.border.Border;

@SuppressWarnings({"serial"})
public class FocusBorder implements Border {
    //
    // Instance data
    //

    private Border focusBorder;
    private Border noFocusBorder;

    //
    // Constructors
    //

    /**
     * Constructs a {@code FocusBorder} with the given wrapped borders.
     *
     * @param	    focusBorder
     *		    the {@code Border} to paint when the {@code Component} has
     *		    focus, or {@code null} to paint no border in this case
     *
     * @param	    noFocusBorder
     *		    the {@code Border} to paint when the {@code Component} does
     *		    not have focus, or {@code null} to paint no border in this
     *		    case
     */
    public FocusBorder(Border focusBorder, Border noFocusBorder) {
	this.focusBorder = focusBorder;
	this.noFocusBorder = noFocusBorder;
    }

    /**
     * Constructs a {@code FocusBorder} with the given focus border, and no
     * no-focus border.
     */
    public FocusBorder(Border focusBorder) {
	this(focusBorder, null);
    }

    /**
     * Constructs a {@code FocusBorder} with a {@link DottedBorder} focus
     * border, and no no-focus border.
     */
    public FocusBorder() {
	this(new DottedBorder());
    }

    //
    // Border methods
    //

    @Override
    public Insets getBorderInsets(Component c) {
	return focusBorder.getBorderInsets(c);
    }

    /**
     * Returns {@code false} if any wrapped border is non-opaque, {@code true}
     * otherwise.
     */
    @Override
    public boolean isBorderOpaque() {
	if ((focusBorder != null && !focusBorder.isBorderOpaque()) ||
	    (noFocusBorder != null && !noFocusBorder.isBorderOpaque())) {
	    return false;
	}

	return true;
    }

    @Override
    public void paintBorder(Component c, Graphics g, int x, int y,
	int width, int height) {

	if (c.isFocusOwner()) {
	    if (focusBorder != null) {
		focusBorder.paintBorder(c, g, x, y, width, height);
	    }
	} else {
	    if (noFocusBorder != null) {
		noFocusBorder.paintBorder(c, g, x, y, width, height);
	    }
	}
    }

    //
    // FocusBorder methods
    //

    public Border getFocusBorder() {
	return focusBorder;
    }

    public Border getNoFocusBorder() {
	return noFocusBorder;
    }
}
