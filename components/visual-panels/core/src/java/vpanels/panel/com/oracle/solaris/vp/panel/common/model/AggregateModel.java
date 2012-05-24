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

package com.oracle.solaris.vp.panel.common.model;

import com.oracle.solaris.vp.panel.common.action.*;

public class AggregateModel implements Model {
    //
    // Instance data
    //

    private Model[] models;

    //
    // Constructors
    //

    public AggregateModel(Model... models) {
	this.models = models;
    }

    //
    // Model methods
    //

    public void init() {
	for (Model model : models) {
	    if (!model.isInitialized())
		model.init();
	}
    }

    public void load()
    {
	throw new UnsupportedOperationException(
	    "Cannot load aggregate models.");
    }

    @Override
    public void save() throws ActionFailedException,
	ActionUnauthorizedException {

	validate();
	for (Model model : models) {
	    model.save();
	}
    }

    @Override
    public boolean isInitialized() {
	for (Model model : models)
	    if (!model.isInitialized())
		return false;
	return true;
    }

    @Override
    public void validate() throws ActionFailedException {
	for (Model model : models) {
	    model.validate();
	}
    }

    //
    // AggregateModel methods
    //

    public Model[] getModels() {
	return models;
    }
}
