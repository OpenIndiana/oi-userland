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

public class UniformLayout extends AbstractLayout {
    //
    // Enums
    //

    public enum Orientation {
	HORIZONTAL,
	VERTICAL,
    }

    public enum FillPolicy {
	RESIZE_COMPONENTS,
	RESIZE_GAPS,
    }

    //
    // Instance data
    //

    private int gap;
    private Orientation o;
    private FillPolicy policy;

    //
    // Constructors
    //

    /**
     * Constructs a {@code UniformLayout} with the given orientation, gap,
     * and fill policy.
     *
     * @param	    o
     *		    the orientation to use when positioning Components
     *
     * @param	    gap
     *		    the gap between each Component
     *
     * @param	    policy
     *		    the fill policy, if the Container is longer than necessary
     */
    public UniformLayout(Orientation o, int gap, FillPolicy policy) {
	this.o = o;
	this.gap = gap;
	this.policy = policy;
    }

    /**
     * Constructs a {@code UniformLayout} with the given orientation and
     * gap, and the default fill policy (FillPolicy.RESIZE_COMPONENTS).
     *
     * @param	    o
     *		    the orientation to use when positioning Components
     *
     * @param	    gap
     *		    the gap between each Component
     */
    public UniformLayout(Orientation o, int gap) {
	this(o, gap, FillPolicy.RESIZE_COMPONENTS);
    }

    /**
     * Constructs a {@code UniformLayout} with the given orientation and
     * the default gap (0) and fill policy (FillPolicy.RESIZE_COMPONENTS).
     *
     * @param	    o
     *		    the orientation to use when positioning Components
     */
    public UniformLayout(Orientation o) {
	this(o, 0);
    }

    /**
     * Constructs a {@code UniformLayout} with the default orientation
     * (Orientation.HORIZONTAL), gap (0), and fill policy
     * (FillPolicy.RESIZE_COMPONENTS).
     */
    public UniformLayout() {
	this(Orientation.HORIZONTAL);
    }

    /**
     * Constructs a {@code UniformLayout} with the given gap, and the default
     * orientation (Orientation.HORIZONTAL) and fill policy
     * (FillPolicy.RESIZE_COMPONENTS).
     */
    public UniformLayout(int gap) {
	this(Orientation.HORIZONTAL, gap);
    }

    //
    // LayoutManager methods
    //

    @Override
    public void layoutContainer(Container container) {
	Insets insets = translate(container.getInsets());
	Dimension cSize = translate(container.getSize());

	// The amount of space we have to work with
	int cWidth = cSize.width - insets.left - insets.right;
	int cHeight = cSize.height - insets.top - insets.bottom;

	// Weed out invisible Components
	Component[] comps = getLayoutComponents(container.getComponents());

	// Preferred size of each Component
	Dimension pSize = translate(getComponentSize(comps, true));

	FillPolicy policy = getFillPolicy();

	int gap = getGap();
	int[] widths = new int[comps.length];
	int[] gaps = new int[comps.length];

	// Total width
	int tWidth = 0;
	for (int i = 0; i < comps.length; i++) {
	    widths[i] = pSize.width;
	    gaps[i] = i == 0 ? 0 : gap;
	    tWidth += widths[i] + gaps[i];
	}

	// Excess/insufficient space
	int extra = cWidth - tWidth;
	if (extra != 0) {
	    if (extra < 0) {
		distributeSpace(extra, widths, null);
	    } else {
		switch (policy) {
		    default:
		    case RESIZE_COMPONENTS:
			distributeSpace(extra, widths, null);
			break;

		    case RESIZE_GAPS:
			float[] weights = new float[gaps.length];
			for (int i = 1; i < comps.length; i++) {
			    weights[i] = 1;
			}
			distributeSpace(extra, gaps, weights);
			break;
		}
	    }
	}

	int left = insets.left;

	// Lay out components
	for (int i = 0; i < comps.length; i++) {
	    left += gaps[i];

	    comps[i].setBounds(translate(new Rectangle(
		left, 0, widths[i], cHeight)));
	    left += widths[i];
	}
    }

    //
    // AbstractLayout methods
    //

    @Override
    protected Dimension getLayoutSize(Container container, boolean preferred) {
	Component[] components = getLayoutComponents(container.getComponents());
	Insets insets = container.getInsets();

	int width = insets.left + insets.right;
	int height = insets.top + insets.bottom;

	Dimension size = getComponentSize(components, preferred);

	switch (getOrientation()) {
	    default:
	    case HORIZONTAL:
		width += components.length * size.width +
		    (components.length - 1) * getGap();
		height += size.height;
		break;

	    case VERTICAL:
		height += components.length * size.height +
		    (components.length - 1) * getGap();
		width += size.width;
		break;
	}

	return new Dimension(width, height);
    }

    @Override
    protected boolean needsLayout(Component c) {
	return c != null && c.isVisible();
    }

    //
    // UniformLayout methods
    //

    public int getGap() {
	return gap;
    }

    public FillPolicy getFillPolicy() {
	return policy;
    }

    public Orientation getOrientation() {
	return o;
    }

    //
    // Private methods
    //

    private Dimension getComponentSize(Component[] components,
	boolean preferred) {

	int width = 0;
	int height = 0;
	for (int i = 0; i < components.length; i++) {
	    if (components[i].isVisible()) {
		Dimension s = preferred ?
		    components[i].getPreferredSize() :
		    components[i].getMinimumSize();
		width = Math.max(width, s.width);
		height = Math.max(height, s.height);
	    }
	}
	return new Dimension(width, height);
    }

    private Dimension translate(Dimension d) {
	switch (getOrientation()) {
	    default:
	    case HORIZONTAL:
		return d;

	    case VERTICAL:
		return new Dimension(d.height, d.width);
	}
    }

    private Insets translate(Insets i) {
	switch (getOrientation()) {
	    default:
	    case HORIZONTAL:
		return i;

	    case VERTICAL:
		return new Insets(i.left, i.top, i.right, i.bottom);
	}
    }

    private Rectangle translate(Rectangle r) {
	switch (getOrientation()) {
	    default:
	    case HORIZONTAL:
		return r;

	    case VERTICAL:
		return new Rectangle(r.y, r.x, r.height, r.width);
	}
    }

    //
    // Static methods
    //

    /**
     * Unit test/example usage.
     */
    public static void main(String[] args) {
	Orientation[] orients = {
	    Orientation.HORIZONTAL,
	    Orientation.VERTICAL,
	};

	FillPolicy[] policies = {
	    FillPolicy.RESIZE_COMPONENTS,
	    FillPolicy.RESIZE_GAPS,
	};

	JFrame frame = new JFrame();
	Container contentPane = frame.getContentPane();
	contentPane.setBackground(new Color(
	    (int)(Math.random() * 256),
	    (int)(Math.random() * 256),
	    (int)(Math.random() * 256)));
	frame.setLayout(
	    new GridLayout(orients.length, policies.length, 15, 15));

	for (int i = 0; i < orients.length; i++) {
	    for (int j = 0; j < policies.length; j++) {
		UniformLayout layout =
		    new UniformLayout(orients[i], 0, policies[j]);

		JPanel p = new JPanel(layout);
		p.setBackground(new Color(
		    (int)(Math.random() * 256),
		    (int)(Math.random() * 256),
		    (int)(Math.random() * 256)));

		char[] c = new char[] {'a', 'b', 'c', 'd'};
		String text = "";
		for (int k = 0; k < c.length; k++) {
		    if (k != 0) {
			text += "\n";
		    }
		    for (int l = 0; l < k; l++) {
			text += c[l];
		    }
		    JComponent comp = new JTextArea(text);
		    comp.setBorder(new LineBorder(Color.black, 1));
		    p.add(comp);
		}

		contentPane.add(p);
	    }
	}

//	frame.pack();
	GraphicsEnvironment env =
	    GraphicsEnvironment.getLocalGraphicsEnvironment();
	Rectangle bounds = env.getMaximumWindowBounds();
	frame.setSize(bounds.width, bounds.height);
	frame.setVisible(true);
    }
}
