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
import java.awt.event.*;
import javax.swing.*;

@SuppressWarnings({"serial"})
public class GradientPanel extends JPanel {
    //
    // Enums
    //

    public enum Direction {
	NORTHWEST, NORTH, NORTHEAST, EAST,
	SOUTHEAST, SOUTH, SOUTHWEST, WEST,
    }

    //
    // Static methods
    //

    private static final Direction _DIRECTION = Direction.SOUTH;

    //
    // Instance data
    //

    private Direction direction;
    private Color startColor;
    private Color endColor;

    //
    // Constructors
    //

    public GradientPanel(Direction direction, Color startColor,
	Color endColor) {
	this.direction = direction;
	this.startColor = startColor;
	this.endColor = endColor;
    }

    public GradientPanel(Color startColor, Color endColor) {
	this(_DIRECTION, startColor, endColor);
    }

    public GradientPanel() {
	this(_DIRECTION, null, null);
    }

    //
    // GradientPanel methods
    //

    public Direction getDirection() {
	return direction;
    }

    public Color getStartColor() {
	return startColor;
    }

    public Color getEndColor() {
	return endColor;
    }

    public void setDirection(Direction direction) {
	this.direction = direction;
	repaint();
    }

    public void setStartColor(Color startColor) {
	this.startColor = startColor;
	repaint();
    }

    public void setEndColor(Color endColor) {
	this.endColor = endColor;
	repaint();
    }

    //
    // JComponent methods
    //

    @Override
    protected void paintComponent(Graphics g) {
	Color startColor = getStartColor();
	Color endColor = getEndColor();

	if (startColor == null) {
	    startColor = getBackground();
	}

	if (endColor == null) {
	    endColor = getBackground();
	}

	Graphics2D g2 = (Graphics2D)g;

	int w = getWidth();
	int h = getHeight();

	int startX, startY, endX, endY;

	switch (getDirection()) {
	    case NORTHWEST:
		startX = w;
		startY = h;
		endX = 0;
		endY = 0;
		break;

	    case NORTH:
		startX = 0;
		startY = h;
		endX = 0;
		endY = 0;
		break;

	    case NORTHEAST:
		startX = 0;
		startY = h;
		endX = w;
		endY = 0;
		break;

	    case EAST:
		startX = 0;
		startY = 0;
		endX = w;
		endY = 0;
		break;

	    case SOUTHWEST:
		startX = w;
		startY = 0;
		endX = 0;
		endY = h;
		break;

	    default:
	    case SOUTH:
		startX = 0;
		startY = 0;
		endX = 0;
		endY = h;
		break;

	    case SOUTHEAST:
		startX = 0;
		startY = 0;
		endX = w;
		endY = h;
		break;

	    case WEST:
		startX = w;
		startY = 0;
		endX = 0;
		endY = 0;
		break;
	}

	GradientPaint gradient = new GradientPaint(
	    startX, startY, startColor, endX, endY, endColor, true);

	g2.setPaint(gradient);
	g2.fillRect(0, 0, w, h);
    }

    //
    // Static methods
    //

    /**
     * Unit test/example.
     */
    public static void main(String[] args) {

	Color start = new Color(112, 130, 144);
	Color end = new Color(64, 82, 101);
	final GradientPanel panel = new GradientPanel(start, end);
	ItemListener listener = new ItemListener() {
	    @Override
	    public void itemStateChanged(ItemEvent e) {
		int change = e.getStateChange();
		if (change == ItemEvent.SELECTED) {
		    panel.setDirection((Direction)e.getItem());
		}
	    }
	};

	JComboBox combo = new JComboBox(Direction.values());
	combo.addItemListener(listener);
	combo.setSelectedIndex(-1);
	combo.setSelectedIndex(0);

	JFrame f = new JFrame();
	panel.add(combo);
	Container c = f.getContentPane();
	c.setLayout(new BorderLayout());
	c.add(panel, BorderLayout.CENTER);

//	f.pack();
	f.setSize(300, 300);
	f.setVisible(true);
    }
}
