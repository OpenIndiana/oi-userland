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

import java.awt.Component;
import javax.swing.JScrollPane;
import com.oracle.solaris.vp.panel.common.ClientContext;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.swing.model.ManagedObjectPropInfo;
import com.oracle.solaris.vp.panel.swing.view.*;
import com.oracle.solaris.vp.util.common.propinfo.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.ExtScrollPane;

public class DebugObjectsTab extends SwingControl<PanelDescriptor, JScrollPane>
{
    //
    // Inner classes
    //

    public static class ClassPropInfo
	extends AbstractPropInfo<ManagedObject, String> {

	//
	// Static data
	//

	private static final String LABEL =
	    Finder.getString("property.label.class");

	private static final String DESCRIPTION =
	    Finder.getString("property.description.class");

	/**
	 * Available instance to mitigate object creation
	 */
	public static final ClassPropInfo instance = new ClassPropInfo();

	//
	// Constructors
	//

	public ClassPropInfo() {
	    super(LABEL, DESCRIPTION, true, false);
	}

	//
	// PropInfo methods
	//

	@Override
	public String getValue(ManagedObject o) {
	    return o.getClass().getName();
	}
    }

    //
    // Static data
    //

    private static final String ID = "objects-debug";

    private static final String ID_LABEL =
	Finder.getString("property.label.id");

    private static final String ID_DESCRIPTION =
	Finder.getString("property.description.id");

    @SuppressWarnings({"unchecked"})
    protected static final PropInfo<ManagedObject, ?>[]
	PROPERTIES = new PropInfo[] {
	    ManagedObjectPropInfo.instance,
	    new ReflectionPropInfo(ID_LABEL, ID_DESCRIPTION, true, false, "id"),
	    ClassPropInfo.instance,
	};

    //
    // Instance data
    //

    private ManagedObject pObject;
    private ManagedObjectTreeTable table;

    //
    // Constructors
    //

    public DebugObjectsTab(ClientContext context, ManagedObject pObject) {
	super(ID, pObject.getName(), context);
	this.pObject = pObject;
    }

    public DebugObjectsTab(PanelDescriptor descriptor) {
	super(ID, descriptor.getName(), descriptor);
	this.pObject = descriptor;
    }

    //
    // SwingControl methods
    //

    @Override
    protected JScrollPane createComponent() {
	ManagedObjectTreeTableModel model =
	    new ManagedObjectTreeTableModel(pObject, PROPERTIES);

	table = new ManagedObjectTreeTable(model, null, null);
	return new ExtScrollPane(table);
    }

    //
    // DebugObjectsTab methods
    //

    public ManagedObjectTreeTable getTable() {
	return table;
    }
}
