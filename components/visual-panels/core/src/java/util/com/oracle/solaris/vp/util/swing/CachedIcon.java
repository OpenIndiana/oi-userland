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
import javax.swing.Icon;

@SuppressWarnings({"serial"})
public abstract class CachedIcon implements Icon {
    //
    // Instance data
    //

    private BufferedImage cachedImage;

    //
    // Icon methods
    //

    @Override
    public void paintIcon(Component c, Graphics g1, int xOffset, int yOffset) {
	Graphics2D g = (Graphics2D)g1;

	if (cachedImage == null) {
	    cachedImage = new BufferedImage(getIconWidth(), getIconHeight(),
		BufferedImage.TYPE_INT_ARGB);
	    Graphics2D bG = cachedImage.createGraphics();
	    paintIcon(bG);
	}

	g.drawImage(cachedImage, xOffset, yOffset, null);
    }

    //
    // CachedIcon methods
    //

    protected void invalidateCachedImage() {
	cachedImage = null;
    }

    protected abstract void paintIcon(Graphics2D g);
}
