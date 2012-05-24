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
import javax.swing.Icon;

public class CroppedPaddedIcon implements Icon {
    //
    // Instance data
    //

    private Icon icon;
    private int height = -1;
    private int width = -1;

    //
    // Constructors
    //

    public CroppedPaddedIcon(Icon icon) {
	setIcon(icon);
    }

    public CroppedPaddedIcon(Icon icon, int width, int height) {
	this(icon);
	setIconWidth(width);
	setIconHeight(height);
    }

    //
    // Icon methods
    //

    @Override
    public int getIconHeight() {
	if (height >= 0) {
	    return height;
	}
	Icon icon = getIcon();
	return icon == null ? 0 : getIcon().getIconHeight();
    }

    @Override
    public int getIconWidth() {
	if (width >= 0) {
	    return width;
	}
	Icon icon = getIcon();
	return icon == null ? 0 : getIcon().getIconWidth();
    }

    @Override
    public void paintIcon(Component c, Graphics g, int x, int y) {
	Icon icon = getIcon();
	if (icon != null) {
	    g.translate(x, y);

	    int width = getIconWidth();
	    int height = getIconHeight();
	    int iWidth = icon.getIconWidth();
	    int iHeight = icon.getIconHeight();

	    int newX = (width - iWidth) / 2;
	    int newY = (height - iHeight) / 2;

	    Shape clip = g.getClip();
	    g.setClip(0, 0, width, height);

	    icon.paintIcon(c, g, newX, newY);

	    g.setClip(clip);
	    g.translate(-x, -y);
	}
    }

    //
    // CroppedPaddedIcon methods
    //

    public Icon getIcon() {
	return icon;
    }

    public void setIcon(Icon icon) {
	this.icon = icon;
    }

    public void setIconHeight(int height) {
	this.height = height;
    }

    public void setIconWidth(int width) {
	this.width = width;
    }
}
