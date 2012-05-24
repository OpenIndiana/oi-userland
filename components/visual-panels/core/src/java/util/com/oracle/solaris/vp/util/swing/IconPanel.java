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

@SuppressWarnings({"serial"})
public class IconPanel extends JPanel {
    //
    // Private methods
    //

    private Icon icon;

    //
    // Constructors
    //

    public IconPanel(Icon icon) {
	setIcon(icon);
    }

    public IconPanel() {
	this(null);
    }

    //
    // Component methods
    //

    @Override
    public Dimension getPreferredSize() {
	Icon icon = getIcon();
	if (icon == null) {
	    return new Dimension(0, 0);
	}

	return new Dimension(icon.getIconWidth(), icon.getIconHeight());
    }

    //
    // JComponent methods
    //

    @Override
    protected void paintComponent(Graphics g) {
	super.paintComponent(g);
	Icon icon = getIcon();

	if (icon != null) {
	    icon.paintIcon(this, g, 0, 0);
	}
    }

    //
    // IconPanel methods
    //

    public Icon getIcon() {
	return icon;
    }

    public void setIcon(Icon icon) {
	this.icon = icon;
    }
}
