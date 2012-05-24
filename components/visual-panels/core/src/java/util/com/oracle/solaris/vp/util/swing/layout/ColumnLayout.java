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

public class ColumnLayout extends AbstractTableLayout<ColumnLayoutConstraint> {
    //
    // Static data
    //

    // Defaults, if not specified
    protected static final VerticalAnchor DEFAULT_ANCHOR =
	VerticalAnchor.TOP;
    protected static final ColumnLayoutConstraint DEFAULT_CONSTRAINT =
	new ColumnLayoutConstraint();

    //
    // Instance data
    //

    private VerticalAnchor vAnchor;

    //
    // Constructors
    //

    /**
     * Constructs a {@code ColumnLayout} with the given vertical
     * anchor.
     *
     * @param	    vAnchor
     *		    the vertical anchor to use when positioning components
     *		    in a container with extra space.
     */
    public ColumnLayout(VerticalAnchor vAnchor) {
	super(HorizontalAnchor.FILL, vAnchor, DEFAULT_CONSTRAINT);
	setVerticalAnchor(vAnchor);
    }

    /**
     * Constructs a {@code ColumnLayout} with the default vertical
     * anchor ({@code VerticalAnchor.TOP}).
     */
    public ColumnLayout() {
	this(DEFAULT_ANCHOR);
    }

    //
    // ConstrainedLayout methods
    //

    @Override
    public ColumnLayoutConstraint cloneConstraint(
	ColumnLayoutConstraint constraint) {

	return constraint.clone();
    }

    //
    // AbstractTableLayout methods
    //

    @Override
    protected AbstractTableConstraint getRowConstraint(
	Container container, int row) {

	Component[] comps = getLayoutComponents(container.getComponents());
	return compToConst.get(comps[row]);
    }

    @Override
    protected AbstractTableConstraint getColumnConstraint(
	Container container, int col) {

	return new SimpleTableConstraint();
    }

    @Override
    protected int getColumnCount(Container container) {
	return 1;
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
	    1, allHAnchors.length + allVAnchors.length - 1, 15, 15));

	for (VerticalAnchor colAnchor : allVAnchors) {

	    VerticalAnchor[] vAnchors = colAnchor == VerticalAnchor.FILL ?
		allVAnchors : new VerticalAnchor[] { VerticalAnchor.FILL };

	    for (VerticalAnchor vAnchor : vAnchors) {
		ColumnLayout layout = new ColumnLayout(colAnchor);

		JPanel p = new JPanel(layout);
		p.setBackground(ColorUtil.getRandomColor());

		int gap = 0;
		int weight = 0;
		for (HorizontalAnchor hAnchor : allHAnchors) {

		    ColumnLayoutConstraint constraint =
			new ColumnLayoutConstraint(
			hAnchor, vAnchor, gap, weight);
		    gap += 5;
		    weight++;

		    JComponent c = new JTextArea(String.format(
			"Column: %s\n" +
			"Element (h, v): %s, %s\n" +
			"Weight: %f, Gap: %d",
			colAnchor, constraint.getHorizontalAnchor(),
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
