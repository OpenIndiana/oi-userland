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

package com.oracle.solaris.vp.util.misc;

import java.awt.*;
import java.util.*;
import java.util.List;
import javax.swing.*;
import com.oracle.solaris.vp.util.swing.*;

public class IconUtil {
    //
    // Static methods
    //

    /**
     * Creates, from the given icon, a new icon with the given height.	If the
     * given height is greater than the height of the given icon, the icon will
     * be padded.  If the given height is less than the height of the given
     * icon, the icon will be shrunk.
     *
     * @param	    icon
     *		    the icon to crop or pad
     *
     * @param	    height
     *		    a height to apply to the given icon, or -1 if no change
     *		    should be made to this icon's height
     *
     * @return	    a new {@code Icon}
     */
    public static Icon ensureIconHeight(Icon icon, int height) {
	if (icon != null) {
	    int iWidth = icon.getIconWidth();
	    int iHeight = icon.getIconHeight();

	    if (iHeight > height) {
		// Maintain aspect ratio
		icon = new ScaledIcon(
		    icon, (iWidth * height) / iHeight, height);
	    } else if (iHeight < height) {
		icon = new CroppedPaddedIcon(icon, iWidth, height);
	    }
	}

	return icon;
    }

    public static Icon getBadgedIcon(Icon icon, Icon badge) {
	int sHeight = badge.getIconHeight();
	int sWidth = badge.getIconWidth();

	return getBadgedIcon(icon, badge, sWidth / 2, sHeight / 2);
    }

    public static Icon getBadgedIcon(final Icon icon, final Icon badge,
	int xOffset, int yOffset) {

	// Calculate once
	final int sHeight = badge.getIconHeight();
	final int sWidth = badge.getIconWidth();
	final int height = icon.getIconHeight() + yOffset;
	final int width = icon.getIconWidth() + xOffset;

	return new Icon() {
	    public int getIconHeight() {
		return height;
	    }

	    public int getIconWidth() {
		return width;
	    }

	    public void paintIcon(Component c, Graphics g, int x, int y) {
		icon.paintIcon(c, g, x, y);
		badge.paintIcon(c, g, x + width - sWidth, y + height - sHeight);
	    }
	};
    }

    /**
     * From the given icons, chooses the icon taller than (if available) and
     * closest to the given height.
     *
     * @param	    icons
     *		    the icons to choose from
     *
     * @param	    height
     *		    the desired height of the icon
     */
    public static <I extends Icon> I getClosestIcon(Collection<I> icons,
	int height) {

	I icon = null;

	if (icons != null) {
	    int diff = 0;

	    for (I i : icons) {
		int d = i.getIconHeight() - height;
		if (d == 0) {
		    return i;
		}

		if (icon == null ||
		    (diff < 0 && d > diff) ||
		    (diff > 0 && d < diff && d >= 0)) {

		    icon = i;
		    diff = d;
		}
	    }
	}

	return icon;
    }

    /**
     * Converts the given {@code Icon}s to {@code Image}s.
     *
     * @param	    icons
     *		    a {@code List} of {@code Icon}s
     *
     * @return	    a (possibly empty) {@code List} of {@code Image}s, or {@code
     *		    null} if {@code icons} is {@code null}
     */
    public static List<Image> toImages(List<? extends Icon> icons) {
	// This simple implementation only works with ImageIcons
	List<Image> images = null;
	if (icons != null) {
	    images = new ArrayList<Image>(icons.size());
	    for (Icon icon : icons) {
		if (icon instanceof ImageIcon) {
		    Image image = ((ImageIcon)icon).getImage();
		    images.add(image);
		}
	    }
	}
	return images;
    }
}
