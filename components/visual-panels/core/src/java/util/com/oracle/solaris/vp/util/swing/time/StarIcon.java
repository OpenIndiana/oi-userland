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

package com.oracle.solaris.vp.util.swing.time;

import java.awt.*;
import java.awt.geom.*;
import javax.swing.*;
import com.oracle.solaris.vp.util.swing.*;

@SuppressWarnings({"serial"})
public class StarIcon extends SquareCachedIcon {
    //
    // Static data
    //

    public static final int DEFAULT_DIAMETER = 100;
    public static final int DEFAULT_POINT_COUNT = 5;

    /**
     * {@code Color.white}
     */
    public static final Color DEFAULT_COLOR = Color.white;

    //
    // Instance data
    //

    private int nPoints = DEFAULT_POINT_COUNT;
    private Color color = DEFAULT_COLOR;

    //
    // Constructors
    //

    /**
     * Constructs a {@code StarIcon} with the given diameter.
     */
    public StarIcon(int diameter) {
	super(diameter);
    }

    /**
     * Constructs a {@code StarIcon} with the diameter {@link
     * #DEFAULT_DIAMETER}.
     */
    public StarIcon() {
	this(DEFAULT_DIAMETER);
    }

    //
    // CachedIcon methods
    //

    @Override
    public void paintIcon(Graphics2D g) {
	int diameter = getDiameter();
	float radius = diameter / 2f;

	g.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
	    RenderingHints.VALUE_ANTIALIAS_ON);

	float angle = 2 * (float)Math.PI / nPoints;
	Point2D.Float[] points = new Point2D.Float[nPoints];
	for (int i = 0; i < nPoints; i++) {
	    float pAngle = i * angle;
	    points[i] = new Point2D.Float(
		radius + radius * (float)Math.cos(pAngle),
		radius - radius * (float)Math.sin(pAngle));
	}

	boolean[] visited = new boolean[nPoints];
	GeneralPath path = new GeneralPath();

	Point2D.Float last = null;
	int i = 0;
	while (!visited[i]) {
	    visited[i] = true;
	    i = (i + (nPoints - 1) / 2) % nPoints;

	    Point2D.Float next = points[i];
	    if (last == null) {
		path.moveTo(next.x, next.y);
	    } else {
		path.lineTo(next.x, next.y);
	    }

	    last = next;

	    if (visited[i]) {
		path.closePath();
		i = (i + 1) % nPoints;
		last = null;
	    }
	}

	float[] fractions = {0, 1f};
	Color[] colors = {color, ColorUtil.alpha(color, 0)};
	Paint paint = new RadialGradientPaint(
	    radius, radius, radius, fractions, colors,
	    MultipleGradientPaint.CycleMethod.NO_CYCLE);
	g.setPaint(paint);

	g.fill(path);
    }

    //
    // StarIcon methods
    //

    /**
     * Gets the color of the star.
     *
     * @see	    #DEFAULT_COLOR
     */
    public Color getColor() {
	return color;
    }

    /**
     * Gets the number of points on the star.
     *
     * @see	    #DEFAULT_POINT_COUNT
     */
    public int getPointCount() {
	return nPoints;
    }

    /**
     * Sets the color of the star.
     *
     * @see	    #DEFAULT_COLOR
     */
    public void setColor(Color color) {
	if (!this.color.equals(color)) {
	    this.color = color;
	    invalidateCachedImage();
	}
    }

    /**
     * Sets the number of points on the star.
     *
     * @see	    #DEFAULT_POINT_COUNT
     */
    public void setPointCount(int nPoints) {
	if (this.nPoints != nPoints) {
	    this.nPoints = nPoints;
	    invalidateCachedImage();
	}
    }

    //
    // Static methods
    //

    public static void main(String args[]) {
	Color light = new Color(148, 188, 246);
	Color dark = new Color(0, 0, 78);

	GradientPanel p = new GradientPanel(light, dark);
	p.setLayout(new GridLayout(0, 4));

	for (int i = 1; i <= 20; i++) {
	    StarIcon starIcon = new StarIcon(100);
	    starIcon.setPointCount(i);
	    JLabel star = new JLabel(starIcon);
	    star.setForeground(Color.white);
	    star.setText(Integer.toString(i));
	    p.add(star);
	}

	JFrame frame = new JFrame();
	Container cont = frame.getContentPane();
	cont.setLayout(new BorderLayout());
	cont.add(p, BorderLayout.CENTER);
	frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	frame.pack();
	frame.setVisible(true);
    }
}
