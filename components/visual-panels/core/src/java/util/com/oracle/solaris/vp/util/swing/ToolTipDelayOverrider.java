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

import java.awt.event.*;
import javax.swing.ToolTipManager;

public class ToolTipDelayOverrider extends MouseAdapter {
    //
    // Static methods
    //

    public static final ToolTipDelayOverrider IMMEDIATE =
	new ToolTipDelayOverrider(0);

    //
    // Instance data
    //

    private int savedDelay;
    private int delay;

    //
    // Constructors
    //

    public ToolTipDelayOverrider(int delay) {
	this.delay = delay;
    }

    //
    // MouseListener methods
    //

    @Override
    public void mouseEntered(MouseEvent e) {
	savedDelay = ToolTipManager.sharedInstance().getInitialDelay();
	ToolTipManager.sharedInstance().setInitialDelay(delay);
    }

    @Override
    public void mouseExited(MouseEvent e) {
	ToolTipManager.sharedInstance().setInitialDelay(savedDelay);
    }

    //
    // ToolTipDelayOverrider methods
    //

    public int getDelay() {
	return delay;
    }
}
