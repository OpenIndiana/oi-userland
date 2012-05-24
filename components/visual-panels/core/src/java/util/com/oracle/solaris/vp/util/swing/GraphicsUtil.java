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
import java.awt.image.*;
import javax.swing.*;

public class GraphicsUtil {
    //
    // Static methods
    //

    public static BufferedImage createDropShadow(
	BufferedImage image, int size, float opacity) {

	int width = image.getWidth() + size * 2;
	int height = image.getHeight() + size * 2;

	BufferedImage mask = new BufferedImage(
	    width, height, BufferedImage.TYPE_INT_ARGB);

	Graphics2D g2 = mask.createGraphics();
	g2.drawImage(image, size, size, null);
	g2.setComposite(AlphaComposite.getInstance(
	    AlphaComposite.SRC_IN, opacity));
	g2.setColor(Color.BLACK);
	g2.fillRect(0, 0, width, height);
	g2.dispose();

	BufferedImage shadow = createBlurOp(size).filter(mask, null);
	g2 = shadow.createGraphics();
	g2.dispose();

	return shadow;
    }

//  public static BufferedImage addDropShadow(BufferedImage image, int size,
//	int xOffset, int yOffset, float opacity) {
//
//	BufferedImage shadow = createDropShadow(image, size, opacity);
//
//	int width = image.getWidth() + size / 2 +
//	    Math.max(Math.abs(xOffset), size - (size / 2));;
//	int height = image.getHeight() + size / 2 +
//	    Math.max(Math.abs(yOffset), size - (size / 2));;
//
//	BufferedImage combo = new BufferedImage(
//	    width, height, BufferedImage.TYPE_INT_ARGB);
//
//	Graphics2D g2 = combo.createGraphics();
//	int offset = size / 2;
//	g2.drawImage(shadow, -offset, -offset, null);
//	g2.drawImage(image, xOffset, yOffset, null);
//
//	return combo;
//  }

    public static BufferedImage combineBufferedImages(BufferedImage... images) {
	int height = 0;
	int width = 0;
	for (BufferedImage image : images) {
	    height = Math.max(height, image.getHeight());
	    width += image.getWidth();
	}

	BufferedImage combo = new BufferedImage(
	    width, height, BufferedImage.TYPE_INT_ARGB);

	Graphics2D g2 = combo.createGraphics();

	int x = 0;
	for (BufferedImage image : images) {
	    int y = (height - image.getHeight()) / 2;
	    g2.drawImage(image, x, y, null);
	}

	return combo;
    }

    public static BufferedImage iconToImage(Icon icon, Component comp) {
	int width = icon.getIconWidth();
	int height = icon.getIconHeight();

	if (width <= 0 || height <= 0) {
	    return null;
	}

//	BufferedImage image =
//	    comp.getGraphicsConfiguration().createCompatibleImage(
//	    width, height, Transparency.TRANSLUCENT);

	BufferedImage image = new BufferedImage(
	    width, height, BufferedImage.TYPE_INT_ARGB);

	Graphics2D g = image.createGraphics();

	icon.paintIcon(comp, g, 0, 0);

	g.dispose();

	return image;
    }

    public static BufferedImage paintToImage(Component comp) {
	int width = comp.getWidth();
	int height = comp.getHeight();

	if (width <= 0 || height <= 0) {
	    return null;
	}

//	BufferedImage image =
//	    comp.getGraphicsConfiguration().createCompatibleImage(
//	    width, height, Transparency.TRANSLUCENT);

	BufferedImage image = new BufferedImage(
	    width, height, BufferedImage.TYPE_INT_ARGB);

	Graphics2D g = image.createGraphics();


	// For unknown reasons, painting to images occasionally requires
	// disabling double-buffering :P
	RepaintManager manager = RepaintManager.currentManager(comp);
	boolean dbEnabled = manager.isDoubleBufferingEnabled();
	if (dbEnabled) {
	    manager.setDoubleBufferingEnabled(false);
	}

	comp.paint(g);

	if (dbEnabled) {
	    manager.setDoubleBufferingEnabled(true);
	}

	g.dispose();

	return image;
    }

    //
    // Private static methods
    //

    private static ConvolveOp createBlurOp(int size) {
	float[] data = new float[size * size];
	float value = 1f / (float)(size * size);
	for (int i = 0; i < data.length; i++) {
	    data[i] = value;
	}
	return new ConvolveOp(new Kernel(size, size, data),
	    ConvolveOp.EDGE_NO_OP, null);
    }
}
