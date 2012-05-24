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
import com.oracle.solaris.vp.util.swing.ColorUtil;

@SuppressWarnings({"serial"})
public class MoonIcon extends SquareCachedIcon {
    //
    // Static data
    //

    public static final int DEFAULT_DIAMETER = 100;
    public static final boolean DEFAULT_FULL = false;
    private static final Color COLOR_FOCUS = Color.white;
    private static final Color COLOR_MAIN = new Color(136, 135, 131);
    private static final Color COLOR_EDGE = new Color(43, 45, 44);

    //
    // Instance data
    //

    private boolean isFull = DEFAULT_FULL;

    //
    // Constructors
    //

    /**
     * Constructs a {@code MoonIcon} with the given diameter.
     */
    public MoonIcon(int diameter) {
	super(diameter);
    }

    /**
     * Constructs a {@code MoonIcon} with the diameter {@link
     * #DEFAULT_DIAMETER}.
     */
    public MoonIcon() {
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

	float shadowPct = .06f;

	float pctFull = .2f;
	float shadowOffset = diameter * pctFull;
	float shadowRad = radius * 1.05f;
	Shape clip = g.getClip();

	if (!isFull()) {
	    // Clip most of shadow

	    float clipRad = shadowRad * (1 - shadowPct);

	    Shape shadow = new Ellipse2D.Float(
		shadowOffset + shadowPct * shadowRad,
		-shadowOffset + shadowPct * shadowRad,
		clipRad * 2f, clipRad * 2f);

	    Area area = new Area(clip != null ? clip :
		new Rectangle(getIconWidth(), getIconHeight()));
	    area.subtract(new Area(shadow));
	    g.setClip(area);
	}

	// Draw orb

	float[] fractions = {0f, 1 - shadowPct, 1f};
	Color[] colors = {COLOR_FOCUS, COLOR_MAIN, COLOR_EDGE};
	Paint paint = new RadialGradientPaint(
	    radius, radius, radius, radius, radius / 2f, fractions, colors,
	    MultipleGradientPaint.CycleMethod.NO_CYCLE);

	g.setPaint(paint);
	g.fillOval(0, 0, diameter, diameter);

	// Draw reflection

	float yMargin = diameter * .04f;
	float yStart = yMargin;
	float yEnd = diameter * .5f;

	paint = new GradientPaint(0, yStart, Color.white, 0, yEnd,
	    ColorUtil.alpha(Color.white, 0));

	float xMargin = diameter * .15f;
	float xStart = xMargin;
	float width = diameter - 2 * xMargin;
	float height = diameter * .5f - yMargin;

	Ellipse2D.Float reflection = new Ellipse2D.Float(xStart, yStart, width,
	    height);

	g.setPaint(paint);
	g.fill(reflection);

	if (!isFull()) {
	    // Draw shadow

	    Color dark = COLOR_EDGE;
	    Color alpha = ColorUtil.alpha(dark, 0f);
	    fractions = new float[] {0f, 1 - shadowPct, 1f};
	    colors = new Color[] {dark, dark, alpha};
	    paint = new RadialGradientPaint(
		shadowRad + shadowOffset, shadowRad - shadowOffset, shadowRad,
		fractions, colors);

	    g.setPaint(paint);
	    g.fillOval(0, 0, diameter, diameter);
	    g.setClip(clip);
	}
    }

    //
    // MoonIcon methods
    //

    /**
     * Gets whether the moon is full or a crescent.
     *
     * @see	    #DEFAULT_FULL
     */
    public boolean isFull() {
	return isFull;
    }

    /**
     * Sets whether the moon is full or a crescent.
     *
     * @see	    #DEFAULT_FULL
     */
    public void setFull(boolean isFull) {
	if (this.isFull != isFull) {
	    this.isFull = isFull;
	    invalidateCachedImage();
	}
    }
}
