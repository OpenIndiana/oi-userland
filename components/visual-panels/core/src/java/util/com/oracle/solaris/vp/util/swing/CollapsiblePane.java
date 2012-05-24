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
import java.awt.event.*;
import javax.swing.*;
import org.jdesktop.animation.timing.*;

@SuppressWarnings({"serial"})
public class CollapsiblePane extends JViewport implements TimingTarget {
    //
    // Enums
    //

    public enum Direction {
	NORTH, SOUTH, EAST, WEST
    }

    //
    // Static data
    //

    public static final Direction _DIRECTION = Direction.NORTH;

    //
    // Instance data
    //

    private AnimatedBooleanProperty collapsed =
	new AnimatedBooleanProperty(300, this);

    private Direction direction;

    //
    // Constructors
    //

    public CollapsiblePane(Direction direction) {
	this.direction = direction;
    }

    public CollapsiblePane(Component c, Direction direction) {
	this(direction);
	setView(c);
    }

    public CollapsiblePane() {
	this(_DIRECTION);
    }

    public CollapsiblePane(Component c) {
	this(c, _DIRECTION);
    }

    //
    // TimingTarget methods
    //

    @Override
    public void begin() {
	// No implementation here -- setup should occur before the animator is
	// started since the clock is ticking at this point.  A design flaw in
	// the timing framework?  Perhaps.
    }

    @Override
    public void end() {
    }

    @Override
    public void repeat() {
    }

    @Override
    public void timingEvent(float fraction) {
	fraction = 1f - fraction;
	Direction direction = getDirection();
	Dimension d = null;

	// If the pane is completely collapsed, mark the view as invisible
	Component view = getView();
	view.setVisible(fraction != 0f);

	if (fraction != 1f) {
	    d = view.getPreferredSize();

	    switch (getDirection()) {
		case NORTH:
		    int vHeight = d.height;
		    d.height *= fraction;
		    setViewPosition(new Point(0, vHeight));
		    break;

		case SOUTH:
		    d.height *= fraction;
		    break;

		case WEST:
		    int vWidth = d.width;
		    d.width *= fraction;
		    setViewPosition(new Point(vWidth, 0));
		    break;

		case EAST:
		    d.width *= fraction;
		    break;
	    }
	}

	// d must be null when fully expanded (fraction == 1) so that if the
	// view resizes at some point, this CollapsiblePane automatically
	// resizes with it
	setPreferredSize(d);

	revalidate();
	repaint();
    }

    //
    // CollapsiblePane methods
    //

    public Animator getAnimator() {
	return collapsed.getAnimator();
    }

    public boolean isCollapsed() {
	return collapsed.getValue();
    }

    public void setCollapsed(boolean value) {
	collapsed.setValue(value, isShowing());
    }

    public void setCollapsed(boolean value, boolean animated) {
	collapsed.setValue(value, animated);
    }

    public Direction getDirection() {
	return direction;
    }

    //
    // Static methods
    //

    // XXX Unit test - remove
    public static void main(String args[]) {
	JButton big = new JButton("big");
	big.setPreferredSize(new Dimension(500, 500));

	final CollapsiblePane cPane = new CollapsiblePane(big, Direction.NORTH);

	JButton b = new JButton("collapse");
	b.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    boolean collapsed = cPane.isCollapsed();
		    cPane.setCollapsed(!collapsed);
		}
	    });

	ExtFrame frame = new ExtFrame();
	frame.setAutoResizeEnabled(true);
	Container c = frame.getContentPane();
	c.setLayout(new BorderLayout());
	c.add(cPane, BorderLayout.NORTH);
	c.add(b, BorderLayout.SOUTH);
	frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	frame.pack();
	frame.setVisible(true);
    }
}
