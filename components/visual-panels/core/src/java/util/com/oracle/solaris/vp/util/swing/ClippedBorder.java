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
import javax.swing.*;
import javax.swing.border.Border;

/**
 * A {@code ClippedBorder} clips one or more sides off an existing {@code
 * Border}.  The resulting {@code Border} has insets of zero on the sides that
 * are clipped.
 */
@SuppressWarnings({"serial"})
public class ClippedBorder implements Border {
    //
    // Instance data
    //

    protected Border border;
    private boolean top;
    private boolean left;
    private boolean bottom;
    private boolean right;

    //
    // Constructors
    //

    /**
     * Constructs a {@code ClippedBorder} with the given side mask.
     *
     * @param	    border
     *		    the {@code Border} to clip
     *
     * @param	    top
     *		    {@code true} to include the top side of {@code border} in
     *		    this {@code ClippedBorder}, {@code false} to exclude it
     *
     * @param	    left
     *		    {@code true} to include the left side of {@code border} in
     *		    this {@code ClippedBorder}, {@code false} to exclude it
     *
     * @param	    bottom
     *		    {@code true} to include the bottom side of {@code border} in
     *		    this {@code ClippedBorder}, {@code false} to exclude it
     *
     * @param	    right
     *		    {@code true} to include the right side of {@code border} in
     *		    this {@code ClippedBorder}, {@code false} to exclude it
     */
    public ClippedBorder(Border border, boolean top, boolean left,
	boolean bottom, boolean right) {

	assert border != null;

	this.border = border;
	this.top = top;
	this.left = left;
	this.bottom = bottom;
	this.right = right;
    }

    //
    // Border methods
    //

    @Override
    public Insets getBorderInsets(Component c) {
	Insets i = border.getBorderInsets(c);

	int top = this.top ? i.top : 0;
	int left = this.left ? i.left : 0;
	int bottom = this.bottom ? i.bottom : 0;
	int right = this.right ? i.right : 0;

	return new Insets(top, left, bottom, right);
    }

    @Override
    public boolean isBorderOpaque() {
	return border.isBorderOpaque();
    }

    @Override
    public void paintBorder(Component c, Graphics g, int x, int y, int width,
	int height) {

//	g.setClip(x, y, width, height);

	Insets i = border.getBorderInsets(c);

	if (!top) {
	    y -= i.top;
	    height += i.top;
	}

	if (!bottom) {
	    height += i.bottom;
	}

	if (!left) {
	    x -= i.left;
	    width += i.left;
	}

	if (!right) {
	    width += i.right;
	}

	border.paintBorder(c, g, x, y, width, height);
    }

    //
    // ClippedBorder methods
    //

    public Border getBorder() {
	return border;
    }

    public boolean getIncludeBottom() {
	return bottom;
    }

    public boolean getIncludeLeft() {
	return left;
    }

    public boolean getIncludeRight() {
	return right;
    }

    public boolean getIncludeTop() {
	return top;
    }

    //
    // Static methods
    //

    // XXX Unit test - Remove
    public static void main(String[] args) {
	Border etched = BorderFactory.createLineBorder(Color.black);
	Border clipped = new ClippedBorder(
	    etched, false, true, false, true);
	Border empty = BorderFactory.createEmptyBorder(15, 15, 15, 15);

	Border mainBorder = BorderFactory.createCompoundBorder(clipped, empty);
	Border cornerBorder =
	    BorderFactory.createCompoundBorder(etched, empty);

	JLabel label = new JLabel("Hello");
	label.setHorizontalAlignment(SwingConstants.CENTER);
	label.setBackground(label.getBackground().darker());
	label.setOpaque(true);
	label.setPreferredSize(new Dimension(300, 200));
	label.setBorder(clipped);

	JPanel mainPanel = new JPanel(new GridBagLayout());
	mainPanel.setPreferredSize(new Dimension(600, 600));
	mainPanel.add(label);

	JFrame frame = new JFrame();
	Container c = frame.getContentPane();
	c.setLayout(new BorderLayout());
	c.add(mainPanel, BorderLayout.CENTER);
	frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	frame.pack();
	frame.setVisible(true);
    }
}
