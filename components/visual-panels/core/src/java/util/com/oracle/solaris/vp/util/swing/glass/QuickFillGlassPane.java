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

import java.awt.*;
import javax.swing.JPanel;

@SuppressWarnings({"serial"})
public class QuickFillGlassPane extends JPanel {
    //
    // Static data
    //

    private static final Color _BACKGROUND = new Color(0f, 0f, 0f, .5f);

    //
    // Constructors
    //

    public QuickFillGlassPane(Color color) {
	setBackground(color);
    }

    public QuickFillGlassPane() {
	this(_BACKGROUND);
    }

    //
    // JComponent methods
    //

    @Override
    protected void paintComponent(Graphics g) {
	g.setColor(getBackground());
	g.fillRect(0, 0, getWidth(), getHeight());
    }
}
