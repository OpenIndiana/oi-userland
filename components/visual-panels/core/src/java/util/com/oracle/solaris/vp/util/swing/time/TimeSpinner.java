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

package com.oracle.solaris.vp.util.swing.time;

import java.awt.*;
import javax.swing.*;

@SuppressWarnings({"serial"})
public class TimeSpinner extends JSpinner {
    //
    // Constructors
    //

    /**
     * Constructs a {@code TimeSpinner} with the specified {@link
     * TimeSpinnerModel}.
     */
    public TimeSpinner(TimeSpinnerModel model) {
	super(model);
    }

    /**
     * Constructs a {@code TimeSpinner} with a default {@link TimeSpinnerModel};
     */
    public TimeSpinner() {
	this(new TimeSpinnerModel());
    }

    //
    // JSpinner methods
    //

    @Override
    protected JComponent createEditor(SpinnerModel model) {
	if (model instanceof TimeSpinnerModel) {
	    return new TimeSpinnerEditor(this);
	}
	return super.createEditor(model);
    }

    @Override
    public TimeSpinnerModel getModel() {
	return (TimeSpinnerModel)super.getModel();
    }

    @Override
    public void setModel(SpinnerModel model) {
	if (!(model instanceof TimeSpinnerModel)) {
	    throw new IllegalArgumentException(
		"model is not a TimeSpinnerModel");
	}
	super.setModel(model);
    }

    //
    // Static methods
    //

    public static void main(String args[]) {
	SimpleTimeModel model = new SimpleTimeModel();

	AnalogClock clock = new AnalogClock(model);
	clock.setInteractive(true);
	clock.setPreferredDiameter(300);

	TimeSpinnerModel spinModel = new TimeSpinnerModel(model);
	spinModel.setTimeSelectionModel(clock.getTimeSelectionModel());
	TimeSpinner spinner = new TimeSpinner(spinModel);

	TimeModelUpdater updater = new TimeModelUpdater(model);
	updater.start();

	JFrame frame = new JFrame();
	Container cont = frame.getContentPane();
	cont.setLayout(new FlowLayout());
	cont.add(spinner);
	cont.add(clock);

	frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	frame.pack();
	frame.setVisible(true);
    }
}
