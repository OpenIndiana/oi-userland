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

import java.io.IOException;
import java.util.List;
import javax.management.*;
import javax.swing.*;
import com.oracle.solaris.adr.Stability;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.api.panel.MBeanUtil;
import com.oracle.solaris.vp.panel.common.api.smf_old.SmfState;
import com.oracle.solaris.vp.panel.common.api.time.HasTimeMXBean;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.panel.swing.control.PanelFrameControl;
import com.oracle.solaris.vp.panel.swing.model.SwingPanelDescriptor;
import com.oracle.solaris.vp.panels.time.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.HasIcons;

@SuppressWarnings({"serial"})
public class TimePanelDescriptor
    extends ServicePanelDescriptor<ManagedObject>
    implements SwingPanelDescriptor<ManagedObject>, HasIcons, HasTimeMXBean {

    //
    // Static data
    //

    private static final String SERVICE = "network/ntp";
    private static final String INSTANCE = "default";

    protected static final List<ImageIcon> icons = Finder.getIcons(
	"images/time-16.png",
	"images/time-24.png",
	"images/time-48.png",
	"images/time-192.png");

    //
    // Instance data
    //

    private DefaultControl control;
    private MXBeanTracker<TimeMXBean> beanTracker;
    private boolean hasFullPrivs;

    //
    // Constructors
    //

    public TimePanelDescriptor(String id, ClientContext context)
	throws IOException, InstanceNotFoundException, ScfException,
	InvalidScfDataException, MissingScfDataException,
	TrackerException {

	super(id, context, SERVICE, INSTANCE);

	ObjectName oName = MBeanUtil.makeObjectName(
	    MBeanUtil.VP_PANEL_DOMAIN + ".time", "Time");
	beanTracker = new MXBeanTracker<TimeMXBean>(
	    oName, TimeMXBean.class, Stability.PRIVATE, context);

	hasFullPrivs = getTimeMXBean().issufficientlyPrivileged();

	refresh(true);
	control = new PanelFrameControl<TimePanelDescriptor>(this);
	control.addChildren(new MainControl(this));
    }

    //
    // HasIcons methods
    //

    @Override
    public List<? extends Icon> getIcons() {
	return icons;
    }

    //
    // HasTimeMXBean methods
    //

    @Override
    public TimeMXBean getTimeMXBean() {
	return beanTracker.getBean();
    }

    //
    // ManagedObject methods
    //

    /**
     * Stops monitoring the connection to the remote host.
     */
    @Override
    public void dispose() {
	beanTracker.dispose();
	super.dispose();
    }

    @Override
    public String getName() {
	return Finder.getString("panel.time.name");
    }

    //
    // PanelDescriptor methods
    //

    @Override
    public Control getControl() {
	return control;
    }

    @Override
    public boolean getHasFullPrivileges() {
	return hasFullPrivs;
    }

    //
    // ServicePanelDescriptor methods
    //

    @Override
    protected String getCalculatedStatusText() {
	String resource = "panel.status.manual";

	try {
	    if (getService().getState() == SmfState.ONLINE) {
		resource = "panel.status.ntp";
	    }
	} catch (ScfException e) {
	}
	return Finder.getString(resource);
    }
}
