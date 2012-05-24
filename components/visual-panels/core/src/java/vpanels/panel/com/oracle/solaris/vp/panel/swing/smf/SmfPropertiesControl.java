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
import com.oracle.solaris.vp.panel.common.smf.HasSmfManagedObject;
import com.oracle.solaris.vp.panel.swing.control.SwingControl;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class SmfPropertiesControl<P extends PanelDescriptor>
    extends SwingControl<P, SmfPropertiesPanel> {

    //
    // Static data
    //

    private static final String ID = "properties";

    private static final String NAME =
	Finder.getString("service.properties.name");

    //
    // Instance data
    //

    private HasSmfManagedObject hasSmfMo;

    //
    // Constructors
    //

    public SmfPropertiesControl(P descriptor, HasSmfManagedObject hasSmfMo) {
	super(ID, NAME, descriptor);
	this.hasSmfMo = hasSmfMo;
    }

    //
    // Control methods
    //

//  @Override
//  protected void save() throws ActionFailedException {
//	List<Changeable> changeables =
//	    getComponent().getChangeableAggregator().getChangeables();
//
//	for (Changeable changeable : changeables) {
//	    if (changeable instanceof SmfMutableProperty &&
//		changeable.isChanged()) {
//
//		try {
//		    ((SmfMutableProperty)changeable).saveToRepo();
//		} catch (ScfException e) {
//		    throw new ActionFailedException(e);
//		}
//	    }
//	}
//  }

    //
    // SwingControl methods
    //

    @Override
    protected SmfPropertiesPanel createComponent() {
	return new SmfPropertiesPanel();
    }

    @Override
    protected void deinitComponent() {
	getComponent().init(null);
    }

    @Override
    protected void initComponent() {
	getComponent().init(hasSmfMo.getSmfManagedObject());
    }
}
