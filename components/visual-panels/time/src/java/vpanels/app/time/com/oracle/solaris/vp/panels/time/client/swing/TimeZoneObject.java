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

package com.oracle.solaris.vp.panels.time.client.swing;

import java.util.*;
import javax.swing.Icon;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.swing.model.SimpleModelControl;
import com.oracle.solaris.vp.panel.swing.timezone.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.time.SimpleTimeModel;

public class TimeZoneObject extends
    IncestuousManagedObject<SimpleModelControl<?, TimePanelDescriptor, ?>> {

    public static final String ID = "timezone";
    private static final String NAME = Finder.getString("timezone.title");
    private static final Icon ICON = Finder.getIcon("images/timezone-24.png");

    private TimeModel timeModel_;
    private TimeZoneModel tzModel_;
    private TimeZonePanel panel_;

    TimeZoneObject(TimePanelDescriptor desc, final Runnable onsave,
	SimpleTimeModel updateModel, TimeZoneModel tzModel,
	TimeModel timeModel) {

	super(ID, ICON);

	timeModel_ = timeModel;
	tzModel_ = tzModel;
	setStatusText();

	TimeZoneModel dataModel = new TimeZoneModel(desc) {
	    @Override
	    public void save() throws ActionFailedException,
		ActionUnauthorizedException {

		super.save();
		onsave.run();
	    }
	};
	panel_ = new TimeZonePanel(desc.getTimeMXBean(), updateModel);
        SimpleModelControl<?, TimePanelDescriptor, ?> control =
	    SimpleModelControl.createControl(ID, NAME, desc, dataModel, panel_);
	control.setHelpMapID("timezone");
	setControl(control);
    }

    @Override
    protected String getCalculatedStatusText() {
	TimeZone timeZone = TimeZone.getTimeZone(tzModel_.getTimeZone());
	boolean daylight = timeZone.useDaylightTime() &&
	    timeZone.inDaylightTime(new Date(System.currentTimeMillis() +
	    timeModel_.getOffset()));
	return timeZone.getDisplayName(daylight, TimeZone.LONG);
    }
}
