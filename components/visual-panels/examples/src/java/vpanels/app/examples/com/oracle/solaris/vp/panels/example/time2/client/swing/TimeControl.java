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

package com.oracle.solaris.vp.panels.example.time2.client.swing;

import java.util.Date;
import com.oracle.solaris.rad.ObjectException;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.swing.control.SettingsControl;

public class TimeControl
    extends SettingsControl<TimePanelDescriptor, TimePanel> {

    //
    // Instance data
    //

    private Date date;

    //
    // Constructors
    //

    public TimeControl(TimePanelDescriptor descriptor) {
	super(descriptor.getId(), descriptor.getName(), descriptor);
    }

    //
    // Control methods
    //

    @Override
    protected void save() throws ActionAbortedException, ActionFailedException,
	ActionUnauthorizedException {

	Date newDate = (Date)getComponent().getSpinnerDateModel().getValue();

	if (!newDate.equals(date)) {
	    long time = date.getTime();
	    try {
		getPanelDescriptor().getTimeBean().settime(time);
	    } catch (ObjectException e) {
		throw new ActionFailedException(e);
	    } catch (SecurityException e) {
		throw new ActionUnauthorizedException(e);
	    }
	}
    }

    //
    // SwingControl methods
    //

    @Override
    protected void configComponent(TimePanel panel) {
	super.configComponent(panel);
	addDefaultApplyAction();
	addDefaultCancelAction(true);
	addDefaultOkayAction(true);
    }

    @Override
    protected TimePanel createComponent() {
	return new TimePanel();
    }

    @Override
    protected void initComponent() {
	try {
	    long time = getPanelDescriptor().getTimeBean().gettime();
	    date = new Date(time);
	} catch (ObjectException e) {
	    /* Shouldn't happen */
	    date = new Date();
	}
	getComponent().getSpinnerDateModel().setValue(date);
    }
}
