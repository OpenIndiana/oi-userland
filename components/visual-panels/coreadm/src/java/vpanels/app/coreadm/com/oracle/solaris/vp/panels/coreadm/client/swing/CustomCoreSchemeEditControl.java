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

import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.smf.SmfUtil;
import com.oracle.solaris.vp.panel.swing.control.SettingsControl;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.MutableProperty;

public class CustomCoreSchemeEditControl extends
    SettingsControl<CoreAdmPanelDescriptor, CustomCoreSchemeEditPanel> {

    //
    // Static data
    //

    public static final String ID = "custom";
    public static final String NAME = Finder.getString(
	"settings.scheme.custom.title");

    //
    // Instance data
    //

    private MutableProperty<CoreConfig> configProperty;

    //
    // Constructors
    //

    public CustomCoreSchemeEditControl(CoreAdmPanelDescriptor descriptor,
        MutableProperty<CoreConfig> configProperty) {

	super(ID, NAME, descriptor);
	this.configProperty = configProperty;
    }

    //
    // Control methods
    //

    @Override
    public String getHelpMapID() {
	return "coreadm-custom";
    }

    @Override
    protected void save() throws ActionAbortedException, ActionFailedException,
	ActionUnauthorizedException {

	CoreConfig value = getComponent().getConfig();
	CoreAdmPanelDescriptor descriptor = getPanelDescriptor();

	try {
	    value.write(descriptor.getService());
	} catch (ScfException e) {
	    SmfUtil.throwActionException(e);
	} catch (SecurityException e) {
	    throw new ActionUnauthorizedException(e);
	}

	configProperty.setValue(getComponent().getConfig());
	if (configProperty.isChanged()) {
	    configProperty.save();
	}
	super.save();

	descriptor.setCoreConfig(value);
    }

    //
    // SwingControl methods
    //

    @Override
    protected void configComponent(CustomCoreSchemeEditPanel panel) {
	super.configComponent(panel);
	addDefaultCancelAction(false);
	addDefaultOkayAction(false);
	addDefaultHelpAction();
    }

    @Override
    protected CustomCoreSchemeEditPanel createComponent() {
	return new CustomCoreSchemeEditPanel();
    }

    @Override
    protected void initComponent() {
	getComponent().init(configProperty.getSavedValue(),
	    configProperty.getValue());
    }
}
