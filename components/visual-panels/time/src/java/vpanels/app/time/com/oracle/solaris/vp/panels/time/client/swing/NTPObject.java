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

import javax.swing.Icon;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.api.smf_old.SmfState;
import com.oracle.solaris.vp.panel.common.smf.ServiceUtil;
import com.oracle.solaris.vp.panel.swing.model.SimpleModelControl;
import com.oracle.solaris.vp.panels.time.ServerInfo;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class NTPObject extends IncestuousManagedObject<
    SimpleModelControl<?, TimePanelDescriptor, ?>> {

    public static final String ID = "ntp";
    private static final String NAME = Finder.getString("ntp.title");
    private static final Icon ICON = Finder.getIcon("images/ntp-24.png");

    private NTPModel displayModel_;

    public NTPObject(TimePanelDescriptor descriptor, final Runnable onsave) {
	super(ID, ICON);

	displayModel_ = new NTPModel(descriptor);
	displayModel_.load();
	setStatusText();

	NTPModel dataModel = new NTPModel(descriptor) {
	    @Override
	    public void save() throws ActionFailedException,
		ActionUnauthorizedException {

		super.save();
		onsave.run();
	    }
	};

	SimpleModelControl<?, TimePanelDescriptor, ?> control =
	    SimpleModelControl.createControl(ID, NAME, descriptor,
	    dataModel, new NTPPanel());
	control.setHelpMapID("time-network");
	setControl(control);
    }

    @Override
    public String getCalculatedStatusText() {

	if (displayModel_.isEnabled()) {
	    for (ServerInfo server : displayModel_.getServers()) {
		if (server.isEnabled()) {
		    return server.getServer();
		}
	    }

	    // Not quite what it was meant for, but it will do for now.
	    return Finder.getString("ntp.table.enabled");
	}

	return ServiceUtil.getStateSynopsis(SmfState.DISABLED, SmfState.NONE);
    }

    @Override
    public void updateDisplay() {
	displayModel_.load();
	super.updateDisplay();
    }
}
