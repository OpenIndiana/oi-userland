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

package com.oracle.solaris.vp.panel.swing.control;

import java.util.Map;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.swing.model.SimpleModelControl;
import com.oracle.solaris.vp.util.swing.SettingsPanel;

public class WizardSummaryControl<M extends Model, P extends PanelDescriptor,
    V extends SettingsPanel & View<M>> extends SimpleModelControl<M, P, V> {

    //
    // Instance data
    //

    private boolean saved;

    //
    // Constructors
    //

    public WizardSummaryControl(String id, String name, P descriptor, M model) {
	super(id, name, descriptor, model);
    }

    //
    // SimpleModelControl methods
    //

    @Override
    protected void initModel() {
	/*
	 * Model is "initialized" by the controls that were traversed
	 * to reach us.
	 */
	assert (getModel().isInitialized());
    }

    //
    // Control methods
    //

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	super.start(navigator, parameters);
	saved = false;
    }

    @Override
    protected void reset() throws ActionAbortedException,
	ActionFailedException {

	super.reset();
	saved = true;
    }

    @Override
    protected void save() throws ActionAbortedException, ActionFailedException,
	ActionUnauthorizedException {

	super.save();
	saved = true;
    }

    @Override
    protected boolean isChanged() {
	return !saved;
    }
}
