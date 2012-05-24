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

public class DottedBorder implements Border {
    //
    // Instance data
    //

    private int width;
    private Color color;

    //
    // Constructors
    //

    /**
     * Constructs a {@code DottedBorder} with the given color and width.
     *
     * @param	    color
     *		    the color to paint the border, or {@code null} to use the
     *		    foreground color of the {@code Component}
     *
     * @param	    width
     *		    the width of the border
     */
    public DottedBorder(Color color, int width) {
	this.color = color;
	this.width = width;
    }

    /**
     * Constructs a {@code DottedBorder} with the given color and default width
     * (1).
     *
     * @param	    color
     *		    the color to paint the border, or {@code null} to use the
     *		    foreground color of the {@code Component}
     */
    public DottedBorder(Color color) {
	this(color, 1);
    }

    /**
     * Constructs a {@code DottedBorder} with a {@code null} color and given
     * width.
     *
     * @param	    width
     *		    the width of the border
     */
    public DottedBorder(int width) {
	this(null, width);
    }

    /**
     * Constructs a {@code DottedBorder} with a {@code null} color and default
     * width (1).
     */
    public DottedBorder() {
	this(null);
    }

    //
    // Border methods
    //

    @Override
    public Insets getBorderInsets(Component c) {
	int width = getWidth();
	return new Insets(width, width, width, width);
    }

    @Override
    public boolean isBorderOpaque() {
	return false;
    }

    @Override
    public void paintBorder(Component c, Graphics g, int x, int y, int w,
	int h) {

	Color color = getColor();
	if (color == null) {
	    color = c.getForeground();
	}

	g.setColor(color);

	int width2 = width << 1;

	for (int xOff = width2; xOff < w; xOff += width2) {
	    // Top
	    g.fillRect(x + xOff, y, width, width);

	    // Bottom
	    g.fillRect(x + w - width - xOff, y + h - width, width, width);
	}

	for (int yOff = width2; yOff < h; yOff += width2) {
	    // Left
	    g.fillRect(x + w - width, y + yOff, width, width);

	    // Right
	    g.fillRect(x, y + h - width - yOff, width, width);
	}
    }

    //
    // DottedBorder methods
    //

    public int getWidth() {
	return width;
    }

    public Color getColor() {
	return color;
    }
}
