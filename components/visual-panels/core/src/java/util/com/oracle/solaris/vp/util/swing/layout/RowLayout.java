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

package com.oracle.solaris.vp.util.swing.layout;

import java.awt.*;
import javax.swing.*;
import javax.swing.border.LineBorder;
import com.oracle.solaris.vp.util.swing.ColorUtil;

public class RowLayout extends AbstractTableLayout<RowLayoutConstraint> {
    //
    // Static data
    //

    // Defaults, if not specified
    protected static final HorizontalAnchor DEFAULT_ANCHOR =
	HorizontalAnchor.LEFT;
    protected static final RowLayoutConstraint DEFAULT_CONSTRAINT =
	new RowLayoutConstraint();

    //
    // Instance data
    //

    private HorizontalAnchor hAnchor;

    //
    // Constructors
    //

    /**
     * Constructs a {@code RowLayout} with the given horizontal
     * anchor.
     *
     * @param	    hAnchor
     *		    the horizontal anchor to use when positioning components
     *		    in a container with extra space.
     */
    public RowLayout(HorizontalAnchor hAnchor) {
	super(hAnchor, VerticalAnchor.FILL, DEFAULT_CONSTRAINT);
	setHorizontalAnchor(hAnchor);
    }

    /**
     * Constructs a {@code RowLayout} with the default horizontal
     * anchor ({@code HorizontalAnchor.LEFT}).
     */
    public RowLayout() {
	this(DEFAULT_ANCHOR);
    }

    //
    // ConstrainedLayout methods
    //

    @Override
    public RowLayoutConstraint cloneConstraint(
	RowLayoutConstraint constraint) {

	return constraint.clone();
    }

    //
    // AbstractTableLayout methods
    //

    @Override
    protected AbstractTableConstraint getColumnConstraint(
	Container container, int col) {

	Component[] comps = getLayoutComponents(container.getComponents());
	return compToConst.get(comps[col]);
    }

    @Override
    protected AbstractTableConstraint getRowConstraint(
	Container container, int row) {

	return new SimpleTableConstraint();
    }

    @Override
    protected int getColumnCount(Container container) {
	Component[] comps = getLayoutComponents(container.getComponents());
	return comps.length;
    }

    //
    // Static methods
    //

    /**
     * Unit test/example usage.
     */
    public static void main(String[] args) {
	JFrame frame = new JFrame();
	Container contentPane = frame.getContentPane();
	contentPane.setBackground(ColorUtil.getRandomColor());

	HorizontalAnchor[] allHAnchors = HorizontalAnchor.values();
	VerticalAnchor[] allVAnchors = VerticalAnchor.values();

	frame.setLayout(new GridLayout(
	    allHAnchors.length + allVAnchors.length - 1, 1, 15, 15));

	for (HorizontalAnchor rowAnchor : allHAnchors) {

	    HorizontalAnchor[] hAnchors = rowAnchor == HorizontalAnchor.FILL ?
		allHAnchors : new HorizontalAnchor[] { HorizontalAnchor.FILL };

	    for (HorizontalAnchor hAnchor : hAnchors) {
		RowLayout layout = new RowLayout(rowAnchor);

		JPanel p = new JPanel(layout);
		p.setBackground(ColorUtil.getRandomColor());

		int gap = 0;
		int weight = 0;
		for (VerticalAnchor vAnchor : allVAnchors) {

		    RowLayoutConstraint constraint =
			new RowLayoutConstraint(hAnchor, vAnchor, gap, weight);
		    gap += 5;
		    weight++;

		    JComponent c = new JTextArea(String.format(
			"Row: %s\n" +
			"Element (h, v): %s, %s\n" +
			"Weight: %f, Gap: %d",
			rowAnchor, constraint.getHorizontalAnchor(),
			constraint.getVerticalAnchor(), constraint.getWeight(),
			constraint.getGap()));

		    c.setBorder(new LineBorder(Color.black, 1));

		    p.add(c, constraint);
		}

		contentPane.add(p);
	    }
	}

	GraphicsEnvironment env =
	    GraphicsEnvironment.getLocalGraphicsEnvironment();
	Rectangle bounds = env.getMaximumWindowBounds();
	frame.setSize(bounds.width, bounds.height);
	frame.setVisible(true);
    }
}
