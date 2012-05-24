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

import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.swing.model.SimpleModelControl;
import com.oracle.solaris.vp.util.swing.SettingsPanel;

public class SimpleWizardModelControl<M extends Model,
    P extends PanelDescriptor, V extends SettingsPanel & View<M>>
    extends SimpleModelControl<M, P, V> {

    //
    // Constructors
    //

    public SimpleWizardModelControl(String id, String name,
	P descriptor, M model, V view) {

	super(id, name, descriptor, model, view);
    }

    //
    // SwingControl methods
    //

    @Override
    protected void initModel() {
	if (!getModel().isInitialized())
	    getModel().init();
    }

    @Override
    protected void saveModel() throws ActionFailedException,
	ActionUnauthorizedException {

	// Validate but don't save yet - that's done at the end of the wizard
	getModel().validate();
    }

    /*
     * Static methods
     */

    /**
     * Convenience factory method that spares the consumer the tedium of
     * specifying the type of the instance.
     */
    public static <M extends Model, P extends PanelDescriptor,
	V extends SettingsPanel & View<M>> SimpleWizardModelControl<M, P, V>
	createControl(String id, String name, P descriptor, M model, V view)
    {
	return (new SimpleWizardModelControl<M, P, V>(id, name, descriptor,
	    model, view));
    }
}
