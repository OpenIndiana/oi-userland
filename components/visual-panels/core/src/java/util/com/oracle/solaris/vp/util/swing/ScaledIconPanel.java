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
import com.oracle.solaris.vp.util.misc.finder.Finder;

@SuppressWarnings({"serial"})
public class ScaledIconPanel extends JPanel {
    //
    // Private methods
    //

    private ScaledIcon sIcon;
    private boolean presAspectRatio;
    private int hAlign;
    private int vAlign;

    //
    // Constructors
    //

    public ScaledIconPanel(Icon icon, boolean presAspectRatio, int hAlign,
	int vAlign) {

	sIcon = new ScaledIcon(icon);
	setPreserveAspectRatio(presAspectRatio);
	setHorizontalAlignment(hAlign);
	setVerticalAlignment(vAlign);
    }

    public ScaledIconPanel(Icon icon, boolean presAspectRatio) {
	this(icon, presAspectRatio, SwingConstants.CENTER,
	    SwingConstants.CENTER);
    }

    public ScaledIconPanel(Icon icon) {
	this(icon, false);
    }

    public ScaledIconPanel() {
	this(null);
    }

    //
    // Component methods
    //

    @Override
    public Dimension getPreferredSize() {
	if (isPreferredSizeSet()) {
	    return super.getPreferredSize();
	}

	Insets insets = getInsets();
	Icon icon = sIcon.getIcon();
	int width = icon.getIconWidth() + insets.left + insets.right;
	int height = icon.getIconHeight() + insets.top + insets.bottom;

	return new Dimension(width, height);
    }

    //
    // JComponent methods
    //

    @Override
    protected void paintComponent(Graphics g) {
	super.paintComponent(g);

	Insets insets = getInsets();
	int width = getWidth() - insets.left - insets.right;
	int height = getHeight() - insets.top - insets.bottom;

	int iWidth = width;
	int iHeight = height;

	int x = insets.left;
	int y = insets.top;

	if (getPreserveAspectRatio()) {
	    Icon icon = sIcon.getIcon();
	    float ratio = (float)icon.getIconWidth() / icon.getIconHeight();
	    float curRatio = (float)iWidth / iHeight;

	    if (ratio > curRatio) {
		iHeight = (int)(iWidth / ratio);
	    } else {
		iWidth = (int)(iHeight * ratio);
	    }

	    switch (getHorizontalAlignment()) {
		case SwingConstants.LEFT:
		    // Do nothing
		break;

		case SwingConstants.RIGHT:
		    x += (width - iWidth);
		break;

		default:
		case SwingConstants.CENTER:
		    x += (width - iWidth) / 2;
		break;
	    }

	    switch (getVerticalAlignment()) {
		case SwingConstants.TOP:
		    // Do nothing
		break;

		case SwingConstants.BOTTOM:
		    y += (height - iHeight);
		break;

		default:
		case SwingConstants.CENTER:
		    y += (height - iHeight) / 2;
		break;
	    }
	}

	sIcon.setIconWidth(iWidth);
	sIcon.setIconHeight(iHeight);
	sIcon.paintIcon(this, g, x, y);
    }

    //
    // ScaledIconPanel methods
    //

    public int getHorizontalAlignment() {
	return hAlign;
    }

    public boolean getPreserveAspectRatio() {
	return presAspectRatio;
    }

    public ScaledIcon getScaledIcon() {
	return sIcon;
    }

    public int getVerticalAlignment() {
	return vAlign;
    }

    public void setHorizontalAlignment(int hAlign) {
	this.hAlign = hAlign;
    }

    public void setIcon(Icon icon) {
	sIcon.setIcon(icon);
    }

    public void setPreserveAspectRatio(boolean presAspectRatio) {
	this.presAspectRatio = presAspectRatio;
    }

    public void setVerticalAlignment(int vAlign) {
	this.vAlign = vAlign;
    }

    //
    // Static methods
    //

    /**
     * Unit test.
     */
    public static void main(String[] args) {
	Icon icon = Finder.getIcon("images/dialog/dialog-error.png");

	ScaledIconPanel panel = new ScaledIconPanel(icon, true);
	panel.setBorder(GUIUtil.getEmptyBorder());

	JFrame frame = new JFrame();
	Container c = frame.getContentPane();
	c.setLayout(new BorderLayout());
	c.add(panel, BorderLayout.CENTER);
	frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	frame.pack();
	frame.setVisible(true);
    }
}
