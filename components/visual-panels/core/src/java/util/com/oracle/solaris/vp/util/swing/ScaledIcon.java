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
import java.awt.image.BufferedImage;
import java.util.*;
import javax.swing.Icon;

public class ScaledIcon implements Icon {
    //
    // Instance data
    //

    private Icon icon;
    private BufferedImage scaledImage;
    private Component comp;
    private int height = -1;
    private int width = -1;
    private Map<RenderingHints.Key, Object> hints =
	new HashMap<RenderingHints.Key, Object>();

    //
    // Constructors
    //

    public ScaledIcon(Icon icon) {
	setIcon(icon);

	hints.put(RenderingHints.KEY_RENDERING,
	    RenderingHints.VALUE_RENDER_QUALITY);
    }

    public ScaledIcon(Icon icon, int width, int height) {
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
    public void paintIcon(Component comp, Graphics g, int x, int y) {
	setComponent(comp);

	if (scaledImage == null) {
	    createScaledImage();
	}

	if (scaledImage != null) {
	    g.translate(x, y);
	    g.drawImage(scaledImage, 0, 0, null);
	    g.translate(-x, -y);
	}
    }

    //
    // ScaledIcon methods
    //

    public Map<RenderingHints.Key, Object> getRenderingHints() {
	return hints;
    }

    public Icon getIcon() {
	return icon;
    }

    public void setComponent(Component comp) {
	if (this.comp != comp) {
	    this.comp = comp;
	    scaledImage = null;
	}
    }

    public void setIconHeight(int height) {
	if (this.height != height) {
	    this.height = height;
	    scaledImage = null;
	}
    }

    public void setIcon(Icon icon) {
	if (this.icon != icon) {
	    this.icon = icon;
	    scaledImage = null;
	}
    }

    public void setIconWidth(int width) {
	if (this.width != width) {
	    this.width = width;
	    scaledImage = null;
	}
    }

    //
    // Private methods
    //

    private void createScaledImage() {
	Icon icon = getIcon();
	if (icon != null) {
	    int width = getIconWidth();
	    int height = getIconHeight();
	    int iWidth = icon.getIconWidth();
	    int iHeight = icon.getIconHeight();

	    BufferedImage bImage = new BufferedImage(
		iWidth, iHeight, BufferedImage.TYPE_INT_ARGB);

	    Graphics bG = bImage.getGraphics();
	    icon.paintIcon(comp, bG, 0, 0);

	    scaledImage = new BufferedImage(
		width, height, BufferedImage.TYPE_INT_ARGB);

	    Graphics g = scaledImage.getGraphics();

	    ((Graphics2D)g).addRenderingHints(hints);

	    g.drawImage(bImage, 0, 0, width, height, null);
	}
    }
}
