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
public class SunIcon extends SquareCachedIcon {
    //
    // Static data
    //

    public static final int DEFAULT_DIAMETER = 100;
    public static final int DEFAULT_RAY_COUNT = 20;
    public static final float DEFAULT_ORB_SIZE_PERCENTAGE = .6f;
    private static final Color COLOR_FOCUS = new Color(254, 247, 1);
    private static final Color COLOR_MAIN = new Color(235, 148, 1);
    private static final Color COLOR_EDGE = new Color(221, 119, 0);

    //
    // Instance data
    //

    private int nRays = DEFAULT_RAY_COUNT;
    private float orbSizePct = DEFAULT_ORB_SIZE_PERCENTAGE;

    //
    // Constructors
    //

    /**
     * Constructs a {@code SunIcon} with the given diameter.
     */
    public SunIcon(int diameter) {
	super(diameter);
    }

    /**
     * Constructs a {@code SunIcon} with the diameter {@link
     * #DEFAULT_DIAMETER}.
     */
    public SunIcon() {
	this(100);
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

	// Draw rays

	float[] pctFromCtr = {
	    orbSizePct, 1f, orbSizePct
	};

	float[] fractions = {orbSizePct, 1f};
	Color[] colors = {COLOR_EDGE, COLOR_MAIN};
	Paint paint = new RadialGradientPaint(
	    radius, radius, radius, fractions, colors,
	    MultipleGradientPaint.CycleMethod.NO_CYCLE);
	g.setPaint(paint);

	float radsPerRay = (float)(2 * Math.PI / nRays);
	for (int j = 0; j < nRays; j++) {
	    float deltaRads = j * radsPerRay;
	    float[] angles = {
		-(float)Math.PI / nRays + deltaRads,
		(float)Math.toRadians(-5) + deltaRads,
		(float)Math.PI / nRays + deltaRads,
	    };

	    Point2D.Float[] points = new Point2D.Float[angles.length];

	    for (int i = 0; i < angles.length; i++) {
		float distFromCtr = radius * pctFromCtr[i];
		float x = radius + distFromCtr * (float)Math.cos(angles[i]);
		float y = radius - distFromCtr * (float)Math.sin(angles[i]);
		points[i] = new Point2D.Float(x, y);
	    }

	    GeneralPath path = new GeneralPath();
	    path.moveTo(points[0].x, points[0].y);

	    Point2D.Float[] controls = {
		new Point2D.Float(),
		new Point2D.Float(),
	    };

	    // 1st path component (points[0] -> [1]) is a cubic Bezier curve

	    Point2D.Float midPoint = new Point2D.Float(
		(points[0].x + points[1].x) / 2,
		(points[0].y + points[1].y) / 2);

	    // Ratio of distance between controls to distance between points
	    float factor = .75f;
	    float xDelta = factor * (points[1].x - midPoint.x) / 2;
	    float yDelta = factor * (points[1].y - midPoint.y) / 2;
	    controls[0].x = midPoint.x - yDelta;
	    controls[0].y = midPoint.y + xDelta;
	    controls[1].x = midPoint.x + yDelta;
	    controls[1].y = midPoint.y - xDelta;

	    path.curveTo(controls[0].x, controls[0].y, controls[1].x,
		controls[1].y, points[1].x, points[1].y);

	    // 2nd path component (points[1] -> [2]) is a quadratic Bezier curve

	    midPoint = new Point2D.Float(
		(points[1].x + points[2].x) / 2,
		(points[1].y + points[2].y) / 2);

	    factor = .7f;
	    xDelta = factor * (points[1].x - midPoint.x) / 2;
	    yDelta = factor * (points[1].y - midPoint.y) / 2;
	    controls[0].x = midPoint.x + yDelta;
	    controls[0].y = midPoint.y - xDelta;

	    path.quadTo(controls[0].x, controls[0].y, points[2].x, points[2].y);

	    path.closePath();
	    g.fill(path);
	}

	// Draw orb

	float innerDiam = diameter * pctFromCtr[0];
	float innerRad = innerDiam / 2f;
	float offset = (diameter - innerDiam) / 2f;

	fractions = new float[] {0f, 1f};
	colors = new Color[] {COLOR_FOCUS, COLOR_MAIN};
	paint = new RadialGradientPaint(
	    innerRad + offset, innerRad + offset, innerRad,
	    innerRad + offset, innerRad / 2f + offset, fractions, colors,
	    MultipleGradientPaint.CycleMethod.NO_CYCLE);

	g.setPaint(paint);

	Ellipse2D.Float orb = new Ellipse2D.Float(offset, offset, innerDiam,
	    innerDiam);

	g.fill(orb);

	// Draw reflection

	float yMargin = innerDiam * .04f;
	float yStart = offset + yMargin;
	float yEnd = offset + innerDiam * .5f;

	paint = new GradientPaint(0, yStart, Color.white, 0, yEnd,
	    ColorUtil.alpha(Color.white, 0));

	float xMargin = innerDiam * .15f;
	float xStart = offset + xMargin;
	float width = innerDiam - 2 * xMargin;
	float height = innerDiam * .5f - yMargin;

	Ellipse2D.Float reflection = new Ellipse2D.Float(xStart, yStart, width,
	    height);

	g.setPaint(paint);
	g.fill(reflection);
    }

    //
    // SunIcon methods
    //

    /**
     * Gets the size of the main orb of the sun, relative to the overall
     * diameter.
     *
     * @see	    #DEFAULT_ORB_SIZE_PERCENTAGE
     */
    public float getOrbSizePercentage() {
	return orbSizePct;
    }

    /**
     * Sets the number of rays on the sun.
     *
     * @see	    #DEFAULT_RAY_COUNT
     */
    public int getRayCount() {
	return nRays;
    }

    /**
     * Sets the size of the main orb of the sun, relative to the overall
     * diameter.
     *
     * @see	    #DEFAULT_ORB_SIZE_PERCENTAGE
     */
    public void setOrbSizePercentage(float orbSizePct) {
	if (this.orbSizePct != orbSizePct) {
	    this.orbSizePct = orbSizePct;
	    invalidateCachedImage();
	}
    }

    /**
     * Sets the number of rays on the sun.
     *
     * @see	    #DEFAULT_RAY_COUNT
     */
    public void setRayCount(int nRays) {
	if (this.nRays != nRays) {
	    this.nRays = nRays;
	    invalidateCachedImage();
	}
    }

    //
    // Static methods
    //

    public static void main(String args[]) {
	Color light = new Color(148, 188, 246);
	Color dark = new Color(0, 0, 78);

	int diameter = 301;
	SunIcon sunIcon = new SunIcon(diameter);
	JLabel sun = new JLabel(sunIcon);

	MoonIcon moonIcon = new MoonIcon((int)
	    (sunIcon.getDiameter() * sunIcon.getOrbSizePercentage()));
	JLabel moon = new JLabel(moonIcon);

	StarIcon starIcon = new StarIcon(diameter);
	starIcon.setDiameter((int)(moonIcon.getDiameter() * .5f));
	JLabel star = new JLabel(starIcon);

	GradientPanel p = new GradientPanel(light, dark);
	p.setLayout(new BorderLayout());
	p.add(sun, BorderLayout.NORTH);
	p.add(star, BorderLayout.CENTER);
	p.add(moon, BorderLayout.SOUTH);

	JFrame frame = new JFrame();
	Container cont = frame.getContentPane();
	cont.setLayout(new BorderLayout());
	cont.add(p, BorderLayout.CENTER);
	frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	frame.pack();
	frame.setVisible(true);
    }
}
