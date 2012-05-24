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

package com.oracle.solaris.vp.panels.example.time1.client.swing;

import java.awt.Component;
import java.util.Date;
import com.oracle.solaris.vp.panel.swing.control.SwingControl;

public class TimeControl extends SwingControl<TimePanelDescriptor, TimePanel> {
    //
    // Constructors
    //

    public TimeControl(TimePanelDescriptor descriptor) {
	super(descriptor.getId(), descriptor.getName(), descriptor);
    }

    //
    // SwingControl methods
    //

    @Override
    protected TimePanel createComponent() {
	return new TimePanel();
    }

    @Override
    protected void initComponent() {
	Date date = new Date();
	getComponent().getSpinnerDateModel().setValue(date);
    }
}
