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

public class ArrowIcon implements Icon {
    //
    // Enums
    //

    public enum Direction {
	UP, DOWN, LEFT, RIGHT
    };

    //
    // Static data
    //

    public static final ArrowIcon UP = new ArrowIcon(Direction.UP);
    public static final ArrowIcon DOWN = new ArrowIcon(Direction.DOWN);
    public static final ArrowIcon LEFT = new ArrowIcon(Direction.LEFT);
    public static final ArrowIcon RIGHT = new ArrowIcon(Direction.RIGHT);

    public static final int _SIZE = 7;

    private static final Color COLOR_DISABLED =
	UIManager.getColor("controlShadow");

    private static final Color COLOR_ENABLED =
	UIManager.getColor("controlDkShadow");

    //
    // Instance data
    //

    private Direction direction;
    private int size;
    private Color color;

    //
    // Constructors
    //

    public ArrowIcon(Direction direction, int size, Color color) {
	this.direction = direction;
	this.size = size;
	this.color = color;
    }

    public ArrowIcon(Direction direction, int size) {
	this(direction, size, null);
    }

    public ArrowIcon(Direction direction) {
	this(direction, _SIZE);
    }

    //
    // Icon methods
    //

    public void paintIcon(Component c, Graphics g, int xTran, int yTran) {
	g.translate(xTran, yTran);

	Color color = getColor();
	g.setColor(color != null ? color :
	    (c.isEnabled() ? COLOR_ENABLED : COLOR_DISABLED));

	int size = getSize();
	for (int x = 0; x < (size + 1) / 2; x++) {
	    drawLine(g, x, x, x, size - x - 1);
	}

	g.translate(-xTran, -yTran);
    }

    public int getIconWidth() {
	switch (getDirection()) {
	    case LEFT:
	    case RIGHT:
	    return (size + 1) / 2;
	}
	return size;
    }

    public int getIconHeight() {
	switch (getDirection()) {
	    case LEFT:
	    case RIGHT:
	    return size;
	}
	return (size + 1) / 2;
    }

    //
    // ArrowIcon methods
    //

    public Color getColor() {
	return color;
    }

    public Direction getDirection() {
	return direction;
    }

    public int getSize() {
	return size;
    }

    //
    // Private methods
    //

    private void drawLine(Graphics g, int x1, int y1, int x2, int y2) {
	int size = (getSize() + 1) / 2;

	// Rotate coordinates as appropriate
	switch (direction) {
	    case LEFT:
		x1 = size - x1 - 1;
		x2 = size - x2 - 1;
	    break;

	    case DOWN:
		int tmp1 = y1;
		int tmp2 = y2;
		y1 = x1;
		y2 = x2;
		x1 = tmp1;
		x2 = tmp2;
	    break;

	    case UP:
		tmp1 = y1;
		tmp2 = y2;
		y1 = size - x1 - 1;
		y2 = size - x2 - 1;
		x1 = tmp1;
		x2 = tmp2;
	    break;
	}

	g.drawLine(x1, y1, x2, y2);
    }

    //
    // Static methods
    //

    /**
     * Unit test.
     */
    public static void main(String args[]) {
	JFrame frame = new JFrame();

	boolean raised[] = {true, false};
	boolean active[] = {true, false};

	int rows = Direction.values().length;
	int columns = 1;
	JPanel p = new JPanel(new FlowLayout(15));
	p.setBorder(BorderFactory.createEmptyBorder(15, 15, 15, 15));

	for (Direction d : Direction.values()) {
	    ArrowIcon icon = new ArrowIcon(d, 41);
	    System.out.printf("%s: %s, %s\n", d, icon.getIconWidth(),
		icon.getIconHeight());
	    JLabel l = new JLabel(icon);
	    l.setDisabledIcon(icon);
	    l.setText(d.toString());
	    l.setEnabled(true);
	    l.setBackground(Color.green);
	    l.setOpaque(true);
	    p.add(l);
	}

	Container c = frame.getContentPane();
	c.setLayout(new BorderLayout());
	c.add(p, BorderLayout.CENTER);
	frame.pack();
	frame.setVisible(true);
    }
}
