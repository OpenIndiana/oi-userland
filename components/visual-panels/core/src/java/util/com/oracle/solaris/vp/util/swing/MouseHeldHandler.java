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
import javax.swing.Timer;

@SuppressWarnings({"serial"})
public class MouseHeldHandler extends MouseAdapter {
    //
    // Static data
    //

    private static final int INITIAL_DELAY = 500;
    private static final int DELAY = 30;

    //
    // Instance data
    //

    private Timer timer;
    private MouseEvent event;

    //
    // Constructors
    //

    public MouseHeldHandler() {
	timer = new Timer(DELAY,
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    mouseHeld(event);
		}
	    });

	timer.setInitialDelay(INITIAL_DELAY);
    }

    //
    // MouseListener methods
    //

    @Override
    public void mousePressed(MouseEvent event) {
	this.event = event;
	mouseHeld(event);
	timer.start();
    }

    @Override
    public void mouseReleased(MouseEvent event) {
	timer.stop();
    }

    //
    // MouseHeldHandler methods
    //

    public Timer getTimer() {
	return timer;
    }

    public void mouseHeld(MouseEvent event) {
    }
}
