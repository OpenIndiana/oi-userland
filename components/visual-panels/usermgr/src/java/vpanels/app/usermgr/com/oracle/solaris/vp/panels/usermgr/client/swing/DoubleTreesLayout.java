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
 * Copyright (c) 2004, 2012, Oracle and/or its affiliates. All rights reserved.
 */


package com.oracle.solaris.vp.panels.usermgr.client.swing;

import java.awt.*;
import javax.swing.*;
import java.util.*;

import com.oracle.solaris.vp.util.misc.finder.Finder;

/**
 * SMC code adapted for Visual Panels
 *
 * This class provides the <code>DoubleTreesLayout</code> manager used
 * by the <code>DoubleTrees</code> component. The layout manager assumes
 * that the <code>DoubleTrees</code> component contains the following
 * interior components.
 * <br>
 * <code>
 * +---------------------------------------------------+
 * |  LEFT_LABEL                          RIGHT_LABEL  |
 * |  +----------------+           +----------------+  |
 * |  |LEFT_SCROLLPANE |           |RIGHT_SCROLLPANE|  |
 * |  |                | +-------+ |                |  |
 * |  |                | |BUTTONS| |                |  |
 * |  |                | |       | |                |  |
 * |  |                | |       | |                |  |
 * |  |                | +-------+ |                |  |
 * |  |                |           |                |  |
 * |  +----------------+           +----------------+  |
 * |                                                   |
 * +---------------------------------------------------+
 * </code>
 * <br>
 * Each component is laid out and sized with respect to its own
 * <code>DoubleTreesConstraints</code> object.
 *
 */
public class DoubleTreesLayout implements LayoutManager2, java.io.Serializable {

    protected final static Dimension ZERO_SIZE = new Dimension(0, 0);
    protected final static Dimension MAXIMUM_SIZE =
			new Dimension(Integer.MAX_VALUE, Integer.MAX_VALUE);

    protected Dimension size;
    protected Dimension minimumSize = new Dimension(400, 250);
    protected Dimension preferredSize = minimumSize;
    protected Dimension maximumSize;
    protected DoubleTreesConstraints defaultConstraints;

    /**
     * Constraints location to component map. Location key is wrapped in an
     * <code>Integer</code>.
     */
    protected HashMap<Integer, Component> componentsMap;

    /**
     * Component to constraints map.
     */
    protected HashMap<Component, DoubleTreesConstraints> constraintsMap;

// ----------------------------------------------------------------------

    /**
     * Construct a <code>DoubleTreesLayout<code> manager with default values.
     */
    public DoubleTreesLayout() {
	size = ZERO_SIZE;
	maximumSize = MAXIMUM_SIZE;
	defaultConstraints = new DoubleTreesConstraints();
	componentsMap = new HashMap<Integer, Component>();
	constraintsMap = new HashMap<Component, DoubleTreesConstraints>();
    }

// ----------------------------------------------------------------------

    /**
     * Set the constraints for a given component. If the component has
     * not previously been added to the layout, setting the components
     * constraints will add the component to the layout.
     *
     * @param component
     *	Component.
     * @param constraints
     *	Components constraints.
     */
    public void setConstraints(
	    Component component,
	    DoubleTreesConstraints constraints) {
	addLayoutComponent(component, constraints);
    }

    /**
     * Get the constraints for a given component. If the component has
     * not had previously added to the layout the default constraints
     * are returned.
     *
     * @param component
     *	Component.
     * @param constraints
     *	Components constraints.
     */
    public DoubleTreesConstraints getConstraints(Component component) {
	if (constraintsMap.containsKey(component)) {
	    return constraintsMap.get(component);
	} else {
	    return defaultConstraints;
	}
    }

    public void addLayoutComponent(String name, Component component) {
	// Copied from GridBayLayout.
	throw new RuntimeException("Not used by this layout manager");
    }

    public void addLayoutComponent(Component component, Object object) {
	if (object == null) {
	    if (!constraintsMap.containsKey(component)) {
		// No constraints for component.
		object = defaultConstraints;
	    } else {
		// Don't add again.
		return;
	    }
	}

	// Can only deal with our own constraints objects.
	if (!(object instanceof DoubleTreesConstraints)) {
	    throw new RuntimeException(
		    "Constraints not sub class of DoubleTreesConstraints");
	}

	/**
	 * Clone constraints in case caller is re-using the same constraints
	 * object.
	 */
	DoubleTreesConstraints constraints =
	    (DoubleTreesConstraints) ((DoubleTreesConstraints) object).clone();

	// Update maps.
	componentsMap.put(new Integer(constraints.location), component);
	constraintsMap.put(component, constraints);

    }

    public void removeLayoutComponent(Component component) {
	DoubleTreesConstraints constraints =
	    constraintsMap.get(component);

	if (constraints != null) {
	    componentsMap.remove(new Integer(constraints.location));
	}

	constraintsMap.remove(component);
    }

    public Dimension preferredLayoutSize(Container parent) {
	return preferredSize;
    }

    public Dimension minimumLayoutSize(Container parent) {
	return minimumSize;
    }

    public Dimension maximumLayoutSize(Container parent) {
	return maximumSize;
    }

    public float getLayoutAlignmentX(Container parent) {
	return 0.5f;
    }

    public float getLayoutAlignmentY(Container parent) {
	return 0.5f;
    }

    public void invalidateLayout(Container target) {
    }

    public void layoutContainer(Container parent) {
	synchronized (parent.getTreeLock()) {
	    doLayoutContainer(parent);
	}
    }

    /**
     * Layout the components.
     *
     * @param parent
     *	Container component where the <code>DoubleTrees</code> component
     *  resides.
     */
    private void doLayoutContainer(Container parent) {
	size = parent.getSize();

	JComponent ll = (JComponent) componentsMap.get(
		new Integer(DoubleTreesConstraints.LEFT_LABEL));
	DoubleTreesConstraints llc =
	    constraintsMap.get(ll);

	JComponent rl = (JComponent) componentsMap.get(
		new Integer(DoubleTreesConstraints.RIGHT_LABEL));
	DoubleTreesConstraints rlc = constraintsMap.get(rl);

	Component b = componentsMap.get(
		new Integer(DoubleTreesConstraints.BUTTONS));
	DoubleTreesConstraints bc = constraintsMap.get(b);

	Component ls = componentsMap.get(
		new Integer(DoubleTreesConstraints.LEFT_SCROLLPANE));
	DoubleTreesConstraints lsc = constraintsMap.get(ls);

	Component rs = componentsMap.get(
		new Integer(DoubleTreesConstraints.RIGHT_SCROLLPANE));
	DoubleTreesConstraints rsc = constraintsMap.get(rs);

	double pw = parent.getSize().getWidth();
	double ph = parent.getSize().getHeight();

	double llw = ll.getPreferredSize().getWidth();
	double llh = ll.getPreferredSize().getHeight();

	double lsw = ls.getPreferredSize().getWidth();
	double lsh = ls.getPreferredSize().getHeight();

	double rlw = rl.getPreferredSize().getWidth();
	double rlh = rl.getPreferredSize().getHeight();

	double rsw = rs.getPreferredSize().getWidth();
	double rsh = rs.getPreferredSize().getHeight();

	double bw = b.getPreferredSize().getWidth();
	double bh = b.getPreferredSize().getHeight();

	// button w and h inc. insets

	bw += bc.insets.left + bc.insets.right;
	bh += bc.insets.top + bc.insets.bottom;

	// leave button w fixed, give rest of parent w to scroll panes

	lsw = rsw = (pw - bw) / 2.0;

	// left label w must not exceed left scroll pane w

	ls.setSize(new Dimension((int) lsw, (int) lsh));

	ll.setMaximumSize(setDimensionAxis(ll.getMaximumSize(), lsw, true));

	llw = lsw - llc.insets.left - llc.insets.right;

	ll.setSize(setDimensionAxis(ll.getSize(), llw, true));

	llw = ll.getPreferredSize().getWidth();
	llh = ll.getPreferredSize().getHeight();

	// right label w must not exceed right scroll pane w

	rs.setSize(new Dimension((int) rsw, (int) rsh));

	rl.setMaximumSize(setDimensionAxis(ll.getMaximumSize(), rsw, true));

	llw = lsw - llc.insets.left - llc.insets.right;

	rl.setSize(setDimensionAxis(rl.getSize(), rlw, true));

	rlw = rl.getPreferredSize().getWidth();
	rlh = rl.getPreferredSize().getHeight();

	// both label h must be equal and accomodate both labels

	double lh = Math.max(
		llh + llc.insets.top + llc.insets.bottom,
		rlh + rlc.insets.top + rlc.insets.bottom);

	ll.setSize(new Dimension((int) lsw, (int) lh));

	rl.setSize(new Dimension((int) rsw, (int) lh));

	// both label w must not exceed scroll pane w

	llw = lsw;
	rlw = rsw;

	// scroll pane h gets rest of parent h after label h allocated

	lsh = rsh = ph - lh;

	ls.setSize(new Dimension((int) lsw, (int) lsh));
	rs.setSize(new Dimension((int) rsw, (int) rsh));
	b.setSize(new Dimension((int) bw, (int) bh));

	// see if we have a preferred size > minimum size

	if (preferredSize == minimumSize) {
	    int w = (int) (lsw + bw + rsw);
	    int h = (int) (lh + lsh);

	    w = Math.max(w, (int) minimumSize.getWidth());
	    h = Math.max(h, (int) minimumSize.getHeight());

	    preferredSize = new Dimension(w, h);
	}

	// set locations for labels, scroll panes and buttons

	int llx = 0;
	int lly = 0;

	int lsx = 0;
	int lsy = lly + (int) lh;

	int bx = lsx + (int) lsw;
	int by = (int) (lh + (lsh - bh) / 2);

	int rlx = bx + (int) bw;
	int rly = 0;

	int rsx = bx + (int) bw;
	int rsy = rly + (int) lh;

	ll.setLocation(llx, lly);
	ls.setLocation(lsx, lsy);
	rs.setLocation(rsx, rsy);
	rl.setLocation(rlx, rly);
	b.setLocation(bx, by);

	// adjust size and locations to accomodate insets

	includeInsets(ll, llc.insets);
	includeInsets(rl, rlc.insets);
	includeInsets(ls, lsc.insets);
	includeInsets(rs, rsc.insets);
	includeInsets(b, bc.insets);
    }

    /**
     * Adjust components size and location to accomodate an <code>Inset</code>.
     *
     * @param component
     *	Component to be resized and relocated.
     * @param insets
     *	Inserts that must surround the component.
     */
    private void includeInsets(Component component, Insets insets) {
	Point location = component.getLocation();
	Dimension size = component.getSize();

	double x = location.getX();
	double y = location.getY();
	double width = size.getWidth();
	double height = size.getHeight();

	component.setLocation(
		(int) (x + insets.left),
		(int) (y + insets.top));
	component.setSize(
		(int) (width - insets.left - insets.right),
		(int) (height - insets.top - insets.bottom));
    }

// ----------------------------------------------------------------------

    /**
     * Get axis of a <code>Dimension</code>.
     *
     * @param dimension
     *	<code>Dimension</code> being inspected.
     * @param xAxis
     *	True if the width (X axis) is required, otherwise false if the
     *  height (Y axis) is required.
     * @return
     *	Required axis value.
     */
    private double getDimensionAxis(Dimension dimension, boolean xAxis) {
	if (xAxis) {
	    return dimension.getWidth();
	} else {
	    return dimension.getHeight();
	}
    }

    /**
     * Set axis of a <code>Dimension</code>.
     *
     * @param dimension
     *	<code>Dimension</code> being modified.
     * @param value
     *	New axis value.
     * @param xAxis
     *	True if the width (X axis) is required, otherwise false if the
     *  height (Y axis) is required.
     * @return
     *	The modified <code>Dimension</code>.
     */
    private Dimension setDimensionAxis(
	    Dimension dimension,
	    double value,
	    boolean xAxis) {
	if (xAxis) {
	    dimension.setSize(value, dimension.getHeight());
	} else {
	    dimension.setSize(dimension.getWidth(), value);
	}

	return dimension;
    }

    /**
     * Set axis of a <code>Dimension</code>.
     *
     * @param dimension
     *	<code>Dimension</code> being modified.
     * @param value
     *	New axis value.
     * @param xAxis
     *	True if the width (X axis) is required, otherwise false if the
     *  height (Y axis) is required.
     * @return
     *	The modified <code>Dimension</code>.
     */
    private Dimension setDimensionAxis(
	    Dimension dimension,
	    int value,
	    boolean xAxis) {
	return setDimensionAxis(dimension, (double) value, xAxis);
    }

}
