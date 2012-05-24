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

package com.oracle.solaris.sleeklock;

import java.awt.BorderLayout;
import java.awt.Container;
import javax.swing.JFrame;
import javax.swing.WindowConstants;
import com.oracle.solaris.vp.util.swing.time.AnalogClock;
import com.oracle.solaris.vp.util.swing.time.TimeModelUpdater;

public class SleeKlock
{
    public static void main(String args[]) {
	AnalogClock clock = new AnalogClock();
	clock.setInteractive(false);
	clock.setPreferredDiameter(100);

	TimeModelUpdater updater = new TimeModelUpdater(clock.getTimeModel());
	updater.start();

	JFrame frame = new JFrame("SleeKlock");
	Container c = frame.getContentPane();
	c.setLayout(new BorderLayout());
	c.add(clock, BorderLayout.CENTER);
	frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	frame.pack();
	frame.setVisible(true);
    }
}
