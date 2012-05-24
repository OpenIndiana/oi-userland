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

public class ColorUtil {
    //
    // Static data
    //

    /**
     * According to the java.awt.Component API, {@code null} should cause the
     * background of a {@code Component} to be transparent.  But buttons and
     * other components of some L&mp;Fs (&lt;cough&gt; metal &lt;cough&gt;)
     * paint their own background in that case.  So a completely transparent
     * color is provided here instead.
     */
    public static Color TRANSPARENT = new Color(0, 0, 0, 0);

    //
    // Static methods
    //

    /**
     * Returns a color identicial to the given color but with a new alpha.
     *
     * @param	    c
     *		    the subject color
     *
     * @param	    alpha
     *		    the alpha setting
     */
    public static Color alpha(Color c, float alpha) {
	float[] rgb = c.getRGBColorComponents(null);
	return new Color(rgb[0], rgb[1], rgb[2], alpha);
    }

    /**
     * Returns a darker version of the given color by the given factor.
     * <p>
     * Compared with {@code Color.darker()}, this method provides finer
     * control over how much to darken the given color.
     *
     * @param	    c
     *		    the subject color
     *
     * @param	    factor
     *		    a number between 0 (no change) and 1 (resulting color will
     *		    be black) inclusive
     *
     * @return	    a darker (closer to black) version of the given color
     *
     * @exception   IllegalArgumentException
     *		    if factor is not betwee 0 and 1 inclusive
     */
    public static Color darker(Color c, float factor) {
	return blend(c, Color.BLACK, factor);
    }

    public static double distance(Color c1, Color c2) {
	float[] rgb1 = c1.getRGBColorComponents(null);
	float[] rgb2 = c2.getRGBColorComponents(null);

	double x = rgb2[0] - rgb1[0];
	double y = rgb2[1] - rgb1[1];
	double z = rgb2[2] - rgb1[2];

	return Math.sqrt(x * x + y * y + z * z);
    }

    /**
     * Blends the given colors by the given factor.
     *
     * @param	    cFrom
     *		    the color to blend with cTo
     *
     * @param	    cTo
     *		    the color to blend with cFrom
     *
     * @param	    factor
     *		    a number between 0 (resulting color will be {@code cFrom})
     *		    and 1 (resulting color will be {@code cTo}) inclusive, with
     *		    .5 indicating an even blend between the two
     *
     * @return	    a blend of the given colors
     *
     * @exception   IllegalArgumentException
     *		    if factor is not betwee 0 and 1 inclusive
     */
    public static Color blend(Color cFrom, Color cTo, float factor) {
	if (factor < 0f || factor > 1f) {
	    throw new IllegalArgumentException(
		"factor not between 0 and 1: " + factor);
	}

	float[] rgbaFrom = cFrom.getRGBComponents(null);
	float[] rgbaTo = cTo.getRGBComponents(null);

	rgbaFrom[0] += (rgbaTo[0] - rgbaFrom[0]) * factor;
	rgbaFrom[1] += (rgbaTo[1] - rgbaFrom[1]) * factor;
	rgbaFrom[2] += (rgbaTo[2] - rgbaFrom[2]) * factor;

	return new Color(rgbaFrom[0], rgbaFrom[1], rgbaFrom[2], rgbaFrom[3]);
    }

    public static Color getRandomColor() {
	return new Color(
	    (int)(Math.random() * 256),
	    (int)(Math.random() * 256),
	    (int)(Math.random() * 256));
    }

    /**
     * Determines whether the given {@code Color} is more dark than light.
     */
    public static boolean isDark(Color c) {
	double whiteDist = distance(c, Color.WHITE);
	double blackDist = distance(c, Color.BLACK);

	return whiteDist > blackDist;
    }

    /**
     * Returns a lighter version of the given color by the given
     * factor.
     * <p>
     * Compared with {@code Color.brighter()}, this method provides finer
     * control over how much to lighten the given color.
     * <p>
     * Note: When {@code factor &gt; 0}, this method differs functionally from
     * {@code Color.brighter()} - repeated invocations of the former for any
     * color will eventually yield white, whereas the latter will just create a
     * brighter version of the same color.  For "pure" colors (zero r, g, or b),
     * repeated invocations of {@code Color.brighter()} will never yield white.
     *
     * @param	    c
     *		    the subject color
     *
     * @param	    factor
     *		    a number between 0 (no change) and 1 (resulting color will
     *		    be white) inclusive
     *
     * @return	    a lighter (closer to white) version of the given color
     *
     * @exception   IllegalArgumentException
     *		    if factor is not betwee 0 and 1 inclusive
     */
    public static Color lighter(Color c, float factor) {
	return blend(c, Color.WHITE, factor);
    }

    public static void main(String args[]) {
	Color color = Color.RED;
	JPanel panel = new JPanel();
	panel.setLayout(new GridLayout(0, 1, 5, 5));
	for (int i = -10; i <= 10; i++) {
	    float factor = (float)i / (float)10;
	    Color lighter = i < 0 ?
		darker(color, -factor) : lighter(color, factor);
	    JLabel l = new JLabel(factor + ": " + lighter.toString());
	    l.setBackground(lighter);
	    l.setForeground(isDark(lighter) ? Color.WHITE : Color.BLACK);
	    l.setOpaque(true);
	    panel.add(l);
	}

	JFrame frame = new JFrame();
	Container c = frame.getContentPane();
	c.setLayout(new BorderLayout());
	c.add(new JScrollPane(panel), BorderLayout.CENTER);
	frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	frame.pack();
	frame.setVisible(true);
    }
}
