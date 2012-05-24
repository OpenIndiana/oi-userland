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

package com.oracle.solaris.vp.panels.time.client.swing;

import java.text.DateFormat;
import java.util.TimeZone;
import javax.swing.Icon;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.swing.timezone.TimeZoneModel;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.time.SimpleTimeModel;

public class TimeObject extends IncestuousManagedObject<TimeControl> {

    private static final Icon ICON = Finder.getIcon("images/time-24.png");

    private TimeModel timeModel_;
    private TimeZoneModel tzModel_;

    public int count = 0;

    public TimeObject(TimePanelDescriptor descriptor, final Runnable onsave,
	SimpleTimeModel updateModel, TimeZoneModel tzModel,
	TimeModel timeModel) {

	super(TimeControl.ID, ICON);

	tzModel_ = tzModel;
	timeModel_ = timeModel;
	setStatusText();

	TimeModel dataModel = new TimeModel(descriptor) {
	    @Override
	    public void save() throws ActionFailedException,
		ActionUnauthorizedException {

		super.save();
		onsave.run();
	    }
	};

	setControl(new TimeControl(descriptor, dataModel, updateModel));
    }

    @Override
    public String getCalculatedStatusText() {
	TimeZone timeZone = TimeZone.getTimeZone(tzModel_.getTimeZone());

	DateFormat format = DateFormat.getDateTimeInstance(
	    DateFormat.SHORT, DateFormat.SHORT);

	format.setTimeZone(timeZone);
	return format.format(System.currentTimeMillis() +
	    timeModel_.getOffset());
    }
}
