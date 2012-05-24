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

import java.awt.EventQueue;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.model.View;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.LongProperty;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;
import com.oracle.solaris.vp.util.swing.property.TimeModelPropertySynchronizer;
import com.oracle.solaris.vp.util.swing.time.*;

@SuppressWarnings({"serial"})
public class TimePanel extends SettingsPanel implements View<TimeModel> {
    //
    // Instance data
    //

    private LongProperty timeProperty = new LongProperty();
    {
	getChangeableAggregator().addChangeables(timeProperty);
    }

    //
    // Constructors
    //

    public TimePanel(SimpleTimeModel model) {
	getHelpField().setText(Finder.getString("time.help"));

	JPanel form = createForm(model);
	setContent(form, false, false);
    }

    //
    // Private methods
    //

    private JPanel createForm(SimpleTimeModel model) {
	new TimeModelPropertySynchronizer(timeProperty, model);

	int gap = GUIUtil.getGap();
	int hGap = GUIUtil.getHalfGap();

	RowLayoutConstraint r = new RowLayoutConstraint(
	    VerticalAnchor.BOTTOM, hGap);

	//
	// Date
	//

	JLabel dateLabel = new JLabel(Finder.getString("time.date"));

	CalendarBrowser calendar = new CalendarBrowser(model,
	    new MonthTableModel(), new YearTableModel(),
	    new DecadeTableModel());

	TimeSpinnerModel dateSpinModel = new TimeSpinnerModel(model);
	TimeSpinner dateSpinner = new DateSpinner(dateSpinModel);

	JPanel datePanel = new JPanel(new RowLayout());
	datePanel.setOpaque(false);
	datePanel.add(dateLabel, r);
	datePanel.add(dateSpinner, r);

	//
	// Time
	//

	JLabel timeLabel = new JLabel(Finder.getString("time.time"));

	AnalogClock clock = new AnalogClock(model);
	clock.setInteractive(true);
	clock.setUseToolTips(true);
	clock.setPreferredDiameter(calendar.getPreferredSize().height);

	TimeSpinnerModel timeSpinModel = new TimeSpinnerModel(model);
	timeSpinModel.setTimeSelectionModel(clock.getTimeSelectionModel());
	TimeSpinner timeSpinner = new TimeSpinner(timeSpinModel);

	JPanel timePanel = new JPanel(new RowLayout());
	timePanel.setOpaque(false);
	timePanel.add(timeLabel, r);
	timePanel.add(timeSpinner, r);

	//
	// Layout
	//

	JPanel formPanel = new JPanel();
	formPanel.setOpaque(false);
	Form form = new Form(formPanel, VerticalAnchor.TOP);

	ColumnLayoutConstraint c = new ColumnLayoutConstraint(
	    HorizontalAnchor.FILL, gap);

	form.addTable(2, 2 * gap, hGap, HorizontalAnchor.LEFT, c);

	SimpleHasAnchors anchor = new SimpleHasAnchors(
	    HorizontalAnchor.FILL, VerticalAnchor.BOTTOM);

	form.add(datePanel, anchor);
	form.add(timePanel, anchor);

	form.add(calendar, anchor.setVerticalAnchor(VerticalAnchor.TOP));
	form.add(clock, anchor);

	return formPanel;
    }

    public void modelToView(TimeModel model) {
	// Sanity check -- the UI should be updated only on the event thread
	assert EventQueue.isDispatchThread();

	timeProperty.update(model.getOffset(), false);
    }

    public void viewToModel(TimeModel model) {
	model.setOffset(timeProperty.getValue());
    }
}
