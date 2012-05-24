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

package com.oracle.solaris.vp.panel.swing.smf;

import com.oracle.solaris.vp.panel.common.model.PanelDescriptor;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.panel.swing.control.SwingControl;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class SmfDependenciesControl<P extends PanelDescriptor,
    S extends SmfManagedObject>
    extends SwingControl<P, SmfDependenciesPanel> {

    //
    // Static data
    //

    public static final String ID = "dependencies";

    private static final String NAME =
	Finder.getString("service.dependencies.name");

    //
    // Instance data
    //

    private HasSmfManagedObject<S> parent;
    private RepoManagedObject repo;

    //
    // Constructors
    //

    public SmfDependenciesControl(P descriptor, HasSmfManagedObject<S> parent,
	RepoManagedObject repo) {

	super(ID, NAME, descriptor);
	this.parent = parent;
	this.repo = repo;
    }

    //
    // SwingControl methods
    //

    @Override
    protected SmfDependenciesPanel createComponent() {
	return new SmfDependenciesPanel(repo);
    }

    @Override
    protected void deinitComponent() {
	getComponent().init(null);
    }

    @Override
    protected void initComponent() {
	getComponent().init(parent.getSmfManagedObject());
    }
}
