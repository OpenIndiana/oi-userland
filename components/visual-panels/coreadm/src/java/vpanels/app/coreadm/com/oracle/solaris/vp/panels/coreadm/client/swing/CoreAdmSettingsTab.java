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

package com.oracle.solaris.vp.panels.coreadm.client.swing;

import java.awt.Component;
import java.awt.event.*;
import java.util.Map;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.smf.SmfUtil;
import com.oracle.solaris.vp.panel.swing.control.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.MutableProperty;
import com.oracle.solaris.vp.util.swing.ReplacingStackPanel;

public class CoreAdmSettingsTab
    extends SettingsControl<CoreAdmPanelDescriptor, CoreAdmSettingsPanel>
    implements HasTabComponent {

    //
    // Static data
    //

    private static final String ID = "settings";
    private static final String NAME = Finder.getString("settings.name");

    //
    // Instance data
    //

    private ReplacingStackPanel stack = new ReplacingStackPanel();

    //
    // Constructors
    //

    public CoreAdmSettingsTab(CoreAdmPanelDescriptor descriptor) {
	super(ID, NAME, descriptor);

	CoreAdmSettingsPanel panel = createComponent();
	setComponent(panel);

	addChildren(new CustomCoreSchemeEditControl(descriptor,
	    panel.getConfigProperty()));
    }

    //
    // HasTabComponent methods
    //

    @Override
    public Component getTabComponent() {
	return stack;
    }

    //
    // Control methods
    //

    @Override
    public String getHelpMapID() {
	return "coreadm-settings";
    }

    @Override
    protected void save() throws ActionAbortedException, ActionFailedException,
	ActionUnauthorizedException {

	MutableProperty<CoreConfig> property =
	    getComponent().getConfigProperty();

	CoreConfig value = property.getValue();
	CoreAdmPanelDescriptor descriptor = getPanelDescriptor();

	try {
	    value.write(descriptor.getService());
	} catch (ScfException e) {
	    SmfUtil.throwActionException(e);
	} catch (SecurityException e) {
	    throw new ActionUnauthorizedException(e);
	}

	if (property.isChanged())
	    property.save();
	super.save();

	descriptor.setCoreConfig(value);
    }

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	setPropertyChangeSource(getPanelDescriptor());
	super.start(navigator, parameters);
    }

    //
    // SwingControl methods
    //

    @Override
    protected void configComponent(CoreAdmSettingsPanel panel) {
	super.configComponent(panel);
	addDefaultResetAction();
	addDefaultApplyAction();
	addDefaultHelpAction();
    }

    @Override
    protected CoreAdmSettingsPanel createComponent() {
	CoreAdmSettingsPanel panel = new CoreAdmSettingsPanel();
	panel.getCustomEditButton().addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    Navigable navigable = new SimpleNavigable(
			CustomCoreSchemeEditControl.ID, null);

		    getNavigator().goToAsync(false, CoreAdmSettingsTab.this,
			navigable);
		}
	    });

	stack.push(panel);
	setComponentStack(stack);

	return panel;
    }

    @Override
    protected void initComponent() {
	getComponent().init(getPanelDescriptor());
    }
}
