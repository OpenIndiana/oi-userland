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

import java.awt.Component;
import javax.swing.*;

/**
 * The {@code LayeredGlassPane} allows multiple glass panes to be displayed at
 * once using an {@code OverlayLayout}.  Calls to {@link #setVisible} are
 * propagated to each child glass pane to initialize just as it would if it were
 * the sole glass pane.
 */
@SuppressWarnings({"serial"})
public class LayeredGlassPane extends JPanel {
    //
    // Constructors
    //

    public LayeredGlassPane() {
	setOpaque(false);
	setLayout(new OverlayLayout(this));
    }

    //
    // Component methods
    //

    /**
     * Propagates this {@link #setVisible} call onto each child {@code
     * Component}, allowing it to initialize just as it would if it were the
     * sole glass pane.
     */
    @Override
    public void setVisible(boolean visible) {
	for (Component comp : getComponents()) {
	    comp.setVisible(visible);
	}
	super.setVisible(visible);
    }
}
