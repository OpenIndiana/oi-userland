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

package com.oracle.solaris.vp.panel.swing.model;

import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.swing.control.SettingsControl;
import com.oracle.solaris.vp.util.swing.SettingsPanel;

/**
 * A basic control that loads a view with a model on start and saves the
 * view's settings to the model on save.
 * <br>
 * Separates out the initialization of the model so that subclasses (e.g.
 * wizard controls) can provide alternate implementations.
 */
public class SimpleModelControl<M extends Model,
    P extends PanelDescriptor, V extends SettingsPanel & View<M>>
    extends SettingsControl<P, V> {

    //
    // Instance data
    //

    private M model_;
    private String helpMapID;

    //
    // Constructors
    //

    /**
     * Constructor for subclasses that override (@code createComponent}.
     */
    protected SimpleModelControl(String id, String name, P descriptor, M model)
    {
	super(id, name, descriptor);
	model_ = model;
    }

    public SimpleModelControl(String id, String name, P descriptor, M model,
	V view) {

	this(id, name, descriptor, model);
	setComponent(view);
    }

    //
    // Control methods
    //

    @Override
    public String getHelpMapID() {
	return helpMapID;
    }

    //
    // SwingControl methods
    //

    @Override
    protected V createComponent() {
	throw new UnsupportedOperationException("Not implemented.");
    }

    @Override
    protected void initComponent() {
	initModel();
	getComponent().modelToView(model_);
    }

    @Override
    protected void save() throws ActionAbortedException, ActionFailedException,
	ActionUnauthorizedException {

	getComponent().viewToModel(model_);
	saveModel();
	super.save();
    }

    //
    // SimpleModelControl methods
    //

    public M getModel() {
	return model_;
    }

    /**
     * Called when component is initialized.
     */
    protected void initModel() {
	model_.load();
    }

    /**
     * Called from {@link #save}, once the model has been populated from the UI.
     */
    protected void saveModel() throws ActionFailedException,
	ActionUnauthorizedException {

	model_.save();
    }

    public void setHelpMapID(String helpMapID) {
	this.helpMapID = helpMapID;
    }

    /*
     * Static methods
     */

    /**
     * Convenience factory method that spares the consumer the tedium of
     * specifying the type of the instance.
     */
    public static <M extends Model, P extends PanelDescriptor,
	V extends SettingsPanel & View<M>> SimpleModelControl<M, P, V>
	createControl(String id, String name, P descriptor, M model, V view)
    {
	return (new SimpleModelControl<M, P, V>(id, name, descriptor, model,
	    view));
    }
}
