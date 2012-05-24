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

import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.Timer;
import com.oracle.solaris.rad.ObjectException;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.swing.control.*;
import com.oracle.solaris.vp.panel.swing.timezone.TimeZoneModel;
import com.oracle.solaris.vp.panel.swing.view.*;
import com.oracle.solaris.vp.util.misc.ChangeableAggregator;
import com.oracle.solaris.vp.util.swing.SimpleCellRenderer;
import com.oracle.solaris.vp.util.swing.time.*;

public class MainControl extends ChildControlListSelectorControl<
    TimePanelDescriptor, ListSelectorPanel, IncestuousManagedObject> {

    //
    // Static data
    //

    public static final String ID = "main";

    //
    // Instance data
    //

    private TimeModel timeModel_;
    private TimeZoneModel tzModel_;
    private TimeObject timeObject_;

    Runnable refresh = new Runnable() {
	public void run() {
	    timeModel_.load();
	    tzModel_.load();
	    for (IncestuousManagedObject o : objects_)
		o.updateDisplay();
	}
    };

    // Repaint the time list cell every second to account for time changes
    private Timer timer = new Timer(1000,
	new ActionListener() {
	    private int count = 0;
	    @Override
	    public void actionPerformed(ActionEvent e) {
		if (count++ > 60) {
		    count = 0;
		    refresh.run();
		} else {
		    timeObject_.updateDisplay();
		}
	    }
	});

    //
    // Constructors
    //

    public MainControl(TimePanelDescriptor descriptor) {
	super(ID, null, descriptor);
    }

    @Override
    public String getHelpMapID() {
	return "time-overview";
    }

    //
    // Control methods
    //

    @Override
    public void descendantStarted(Control[] path) {
	super.descendantStarted(path);

	// Allow our ChangeableAggregator, which indirectly controls the enabled
	// state of the Apply/Okay/Reset buttons, to track outstanding changes
	// in running descendants.
	Control control = path[path.length - 1];
	if (control instanceof SwingControl) {
	    ChangeableAggregator aggregator =
		((SwingControl)control).getChangeableAggregator();

	    if (aggregator != null) {
		getComponent().getChangeableAggregator().addChangeables(
		    aggregator);
	    }
	}
    }

    @Override
    public void descendantStopped(Control[] path) {
	super.descendantStopped(path);

	// Stop monitoring stopped descendant for changes
	Control control = path[path.length - 1];
	if (control instanceof SwingControl) {
	    ChangeableAggregator aggregator =
		((SwingControl)control).getChangeableAggregator();

	    if (aggregator != null) {
		getComponent().getChangeableAggregator().removeChangeable(
		    aggregator);
	    }
	}
    }

    @Override
    public Navigable[] getForwardingPath(boolean childStopped) {
	return new Navigable[] {
	    new SimpleNavigable(TimeControl.ID, null)
	};
    }

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	setPropertyChangeSource(getPanelDescriptor());
	super.start(navigator, parameters);
    }

    //
    // DefaultControl methods
    //

    @Override
    protected void ensureChildrenCreated() {
	if (children.size() == 0) {
	    TimePanelDescriptor descriptor = getPanelDescriptor();

	    /*
	     * The time and timezone displays need each other's configuration.
	     * Create them in common here.
	     */
	    timeModel_ = new TimeModel(descriptor);
	    tzModel_ = new TimeZoneModel(descriptor);
	    timeModel_.load();
	    tzModel_.load();

	    SimpleTimeModel model = new SimpleTimeModel();

	    String zoneId;
	    try {
		zoneId = descriptor.getTimeMXBean().getdefaultTimeZone();
	    } catch (ObjectException e) {
		zoneId = "UTC";
	    }
	    TimeZone zone = TimeZone.getTimeZone(zoneId);
	    model.setTimeZone(zone);

	    TimeModelUpdater updater = new TimeModelUpdater(model);
	    updater.start();

	    timeObject_ = new TimeObject(descriptor, refresh, model, tzModel_,
		timeModel_);
	    addChild(timeObject_);
	    addChild(new TimeZoneObject(descriptor, refresh, model, tzModel_,
		timeModel_));
	    addChild(new NTPObject(descriptor, refresh));
	}
    }

    //
    // SwingControl methods
    //

    @Override
    protected void configComponent(ListSelectorPanel panel) {
	super.configComponent(panel);
	addDefaultApplyAction();
	addDefaultCancelAction(true);
	addDefaultOkayAction(true);
	addDefaultHelpAction();
    }

    @Override
    protected ListSelectorPanel createComponent() {
	ListSelectorPanel panel = new ListSelectorPanel();

	JList list = panel.getSelectionComponent();
	list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

	SimpleCellRenderer renderer =
	    new ManagedObjectCellRenderer<ControlManagedObject>();
	renderer.configureFor(list);
	list.setCellRenderer(renderer);

	panel.getChangeableAggregator().addChangeables(
	    getPanelDescriptor().getChangeableAggregator());

	return panel;
    }

    @Override
    protected void deinitComponent() {
	timer.stop();
    }

    @Override
    protected void initComponent() {
	timer.start();
    }
}
