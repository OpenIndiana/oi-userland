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

import javax.swing.*;

@SuppressWarnings({"serial"})
public class DateSpinner extends TimeSpinner {
    //
    // Constructors
    //

    /**
     * Constructs a {@code DateSpinner} with the specified {@link
     * TimeSpinnerModel}.
     */
    public DateSpinner(TimeSpinnerModel model) {
	super(model);
    }

    /**
     * Constructs a {@code DateSpinner} with a default {@link TimeSpinnerModel};
     */
    public DateSpinner() {
	this(new TimeSpinnerModel());
    }

    //
    // JSpinner methods
    //

    @Override
    protected JComponent createEditor(SpinnerModel model) {
	if (model instanceof TimeSpinnerModel) {
	    return new DateSpinnerEditor(this);
	}
	return super.createEditor(model);
    }
}
