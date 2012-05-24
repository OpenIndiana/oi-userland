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

package com.oracle.solaris.vp.panels.coreadm.client.swing;

import java.awt.EventQueue;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.action.ActionFailedException;
import com.oracle.solaris.vp.panel.swing.control.*;
import com.oracle.solaris.vp.panel.swing.view.ChangeIndicator;
import com.oracle.solaris.vp.util.misc.ChangeableAggregator;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.BooleanProperty;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;
import com.oracle.solaris.vp.util.swing.property.CheckBoxPropertySynchronizer;

@SuppressWarnings({"serial"})
public class CustomCoreSchemeEditPanel extends SettingsPanel {
    //
    // Instance data
    //

    private BooleanProperty sysLogProperty = new BooleanProperty();
    private CoreAdmOptionsPanel globalPanel;
    private CoreAdmOptionsPanel processPanel;

    //
    // Constructors
    //

    public CustomCoreSchemeEditPanel() {
	JPanel form = createForm();
	setContent(form, false, true);
    }

    //
    // CommonEditPanel methods
    //

    protected JPanel createForm() {
	ChangeableAggregator aggregator = getChangeableAggregator();

	JCheckBox sysLogCheckBox = new JCheckBox(Finder.getString(
	    "settings.scheme.custom.options.syslog"));
	new CheckBoxPropertySynchronizer(sysLogProperty, sysLogCheckBox);
	ChangeIndicator sysLogChange = new ChangeIndicator();
	sysLogProperty.addChangeListener(sysLogChange);
	aggregator.addChangeables(sysLogProperty);

	globalPanel = new CoreAdmOptionsPanel();
	aggregator.addChangeables(globalPanel.getChangeableAggregator());

	processPanel = new CoreAdmOptionsPanel();
	aggregator.addChangeables(processPanel.getChangeableAggregator());

	JTabbedPane tabs = new JTabbedPane();
	tabs.setTabLayoutPolicy(JTabbedPane.SCROLL_TAB_LAYOUT);
	tabs.setOpaque(false);
	SleekTabbedPaneUI tabUi = new SleekTabbedPaneUI();
	tabs.setUI(tabUi);

	String globalTitle = Finder.getString(
	    "settings.scheme.custom.options.global.title");
	JPanel globalTab = new TabbedControl.TabInsetPanel(globalPanel);
	tabs.addTab(globalTitle, globalTab);
	new ChangeIndicatorTab(globalTitle, tabs, tabs.getTabCount() - 1,
	    globalPanel.getChangeableAggregator());

	String processTitle = Finder.getString(
	    "settings.scheme.custom.options.process.title");
	JPanel processTab = new TabbedControl.TabInsetPanel(processPanel);
	tabs.addTab(processTitle, processTab);
	new ChangeIndicatorTab(processTitle, tabs, tabs.getTabCount() - 1,
	    processPanel.getChangeableAggregator());

	JPanel formPanel = new JPanel();
	formPanel.setOpaque(false);
	Form form = new Form(formPanel, VerticalAnchor.FILL);

	int gap = GUIUtil.getGap();

	ColumnLayoutConstraint c = new ColumnLayoutConstraint(
	    HorizontalAnchor.FILL, gap);

	RowLayoutConstraint r = new RowLayoutConstraint(
	    VerticalAnchor.TOP, gap);
	r.setLayoutIfInvisible(true);

	form.addRow(HorizontalAnchor.LEFT, c);
	form.add(sysLogChange, r);
	form.add(sysLogCheckBox, r);

	form.addRow(HorizontalAnchor.FILL, c.setWeight(1));
	form.add(tabs);

	return formPanel;
    }

    public void init(CoreConfig savedconfig, CoreConfig config) {
	// Sanity check -- the UI should be updated only on the event thread
	assert EventQueue.isDispatchThread();

	sysLogProperty.setValue(config.getLogging());
	sysLogProperty.setSavedValue(savedconfig.getLogging());

	globalPanel.init(savedconfig.getGlobalScope(), config.getGlobalScope());
	processPanel.init(savedconfig.getProcessScope(),
	    config.getProcessScope());
    }

    /*
     * Called by CustomCoreSchemeEditControl when saving.
     */
    public CoreConfig getConfig() throws ActionFailedException {
	return new CoreConfig(globalPanel.getConfig(true),
	    processPanel.getConfig(false), sysLogProperty.getValue());
    }
}
