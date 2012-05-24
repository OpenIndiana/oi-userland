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
import javax.swing.JPanel;
import javax.swing.border.Border;
import org.jdesktop.swingx.border.DropShadowBorder;
import org.jdesktop.swingx.graphics.*;

@SuppressWarnings({"serial"})
public class ShadowPanel extends JPanel {
    //
    // Static data
    //

    public static final ShadowRenderer SHADOW_RENDERER =
	new ShadowRenderer(3, .35f, Color.BLACK);

    public static final Border BORDER_SHADOW = new DropShadowBorder(
	Color.BLACK, 10, .5f, 12, false, false, true, true);

    //
    // Instance data
    //

    private boolean enabled = true;
    private int xOffset = 0;
    private int yOffset = 0;
    private ShadowRenderer shadowRenderer = SHADOW_RENDERER;
    private BufferedImage shadow;

    //
    // Constructors
    //

    public ShadowPanel() {
    }

    public ShadowPanel(LayoutManager layout) {
	super(layout);
    }

    //
    // Component methods
    //

    @Override
    public void paint(Graphics g) {
	if (enabled) {
	    if (shadow == null) {
		BufferedImage buffer =
		    GraphicsUtilities.createCompatibleTranslucentImage(
		    getWidth(), getHeight());

		Graphics2D g2 = buffer.createGraphics();
		super.paint(g2);

		shadow = shadowRenderer.createShadow(buffer);
		g2.dispose();
		g.drawImage(shadow, xOffset, yOffset, null);
		g.drawImage(buffer, 0, 0, null);
	    } else {
		g.drawImage(shadow, xOffset, yOffset, null);
		super.paint(g);
	    }
	} else {
	    super.paint(g);
	}
    }

    //
    // Container methods
    //

    @Override
    public void doLayout() {
	super.doLayout();
	shadow = null;
    }

    //
    // ShadowPanel methods
    //

    public ShadowRenderer getShadowRenderer() {
	return shadowRenderer;
    }

    public int getXOffset() {
	return xOffset;
    }

    public int getYOffset() {
	return yOffset;
    }

    public boolean isShadowEnabled() {
	return enabled;
    }

    public void setOffsets(int xOffset, int yOffset) {
	setXOffset(xOffset);
	setYOffset(yOffset);
    }

    public void setShadowEnabled(boolean enabled) {
	if (this.enabled != enabled) {
	    this.enabled = enabled;
	    repaint();
	}
    }

    public void setShadowRenderer(ShadowRenderer shadowRenderer) {
	this.shadowRenderer = shadowRenderer;
    }

    public void setXOffset(int xOffset) {
	this.xOffset = xOffset;
    }

    public void setYOffset(int yOffset) {
	this.yOffset = yOffset;
    }
}
