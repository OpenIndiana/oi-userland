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
 * Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.util.swing.glass;

import java.awt.BorderLayout;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import javax.swing.*;
import com.oracle.solaris.vp.util.swing.GraphicsUtil;

@SuppressWarnings({"serial"})
public class ImageCaptureGlassPane extends SimpleGlassPane {
    //
    // Instance data
    //

    private boolean refreshOnResize = true;
    private JLabel label = new JLabel();

    //
    // Constructors
    //

    public ImageCaptureGlassPane() {
	setOpaque(true);
	setLayout(new BorderLayout());
	add(label, BorderLayout.CENTER);

	addComponentListener(
	    new ComponentAdapter() {
		@Override
		public void componentResized(ComponentEvent e) {
		    if (refreshOnResize && isShowing()) {
			refresh();
		    }
		}
	    });
    }

    //
    // SimpleGlassPane methods
    //

    @Override
    public void componentHidden() {
	super.componentHidden();
	label.setIcon(null);
    }

    @Override
    public void componentToBeVisible() {
	super.componentToBeVisible();
	refresh();
    }

    //
    // ImageCaptureGlassPane methods
    //

    protected JLabel getLabel() {
	return label;
    }

    public boolean getRefreshOnResize() {
	return refreshOnResize;
    }

    public synchronized void refresh() {
	Icon icon = null;

	JRootPane rootPane = getRootPane();
	if (rootPane != null) {

	    JLayeredPane layeredPane = rootPane.getLayeredPane();
	    if (layeredPane != null) {

		BufferedImage bImage = GraphicsUtil.paintToImage(layeredPane);
		if (bImage != null) {

		    icon = new ImageIcon(bImage);
		}
	    }
	}

	label.setIcon(icon);
    }

    public void setRefreshOnResize(boolean refreshOnResize) {
	this.refreshOnResize = refreshOnResize;
    }
}
