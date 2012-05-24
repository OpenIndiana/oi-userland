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

package com.oracle.solaris.vp.panels.apache.client.swing;

import java.util.List;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.view.PanelIconUtil;
import com.oracle.solaris.vp.panel.swing.control.*;
import com.oracle.solaris.vp.panel.swing.view.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;

public class MimeTypesControl extends ListSelectorControl<ApachePanelDescriptor,
    ListSelectorPanel, MimeType> implements HasIcons {

    //
    // Static data
    //

    public static final String ID = "mimetypes";
    public static final String NAME = Finder.getString("mimetypes.title");

    //
    // Instance data
    //

    private HasMimeTypes parent;

    //
    // Constructors
    //

    public MimeTypesControl(ApachePanelDescriptor descriptor,
	HasMimeTypes parent) {

	super(ID, NAME, descriptor);
	this.parent = parent;
    }

    //
    // HasIcons methods
    //

    @Override
    public List<? extends Icon> getIcons() {
	return PanelIconUtil.getGenericMimeIcons();
    }

    //
    // Control methods
    //

    @Override
    public Navigable[] getForwardingPath(boolean childStopped) {
	List<MimeType> mimeTypes = parent.getMimeTypes().getChildren();
	if (!mimeTypes.isEmpty()) {

	    MimeType mimeType = mimeTypes.get(0);

	    return new Navigable[] {
		new SimpleNavigable(MimeTypeControl.ID, null,
		    MimeTypeControl.PARAM_MIMETYPE, mimeType.getId())
	    };
	}

	return null;
    }

    @Override
    public String getHelpMapID() {
	return "apache-mimetypes";
    }

    //
    // DefaultControl methods
    //

    @Override
    protected void ensureChildrenCreated() {
	if (children.size() == 0) {
	    ApachePanelDescriptor descriptor = getPanelDescriptor();
	    SwingControl child = new MimeTypeControl(descriptor, this);
	    addChildren(child);
	    addToLayout(child);
	}
    }

    //
    // SwingControl methods
    //

    @Override
    protected void configComponent(ListSelectorPanel panel) {
	super.configComponent(panel);
	addDefaultCloseAction(false);
	addDefaultHelpAction();
    }

    @Override
    protected ListSelectorPanel createComponent() {
	ListSelectorPanel panel = new ListSelectorPanel();
	panel.setSelectionTitle(Finder.getString("mimetypes.list.title"));

	JList list = panel.getSelectionComponent();
	SimpleCellRenderer renderer = new ManagedObjectCellRenderer<MimeType>();
	renderer.configureFor(list);
	list.setCellRenderer(renderer);

	addAction(panel, new CreateMimeTypeAction(this), true, true);
	addAction(panel, new DeleteMimeTypeAction(this), true, true);

	setDefaultContentView(new NoMimeTypePanel());

	return panel;
    }

    //
    // ListSelectorControl methods
    //

    @Override
    protected int getListIndexOf(Control child) {
	MimeType mimeType = ((MimeTypeControl)child).getMimeType();
	int index = parent.getMimeTypes().indexOf(mimeType);
	assert mimeType == getComponent().getSelectionComponent().getModel().
	    getElementAt(index);
	return index;
    }

    @Override
    protected ListModel getListModel() {
	return new ManagedObjectTableModel<MimeType>(parent.getMimeTypes());
    }

    @Override
    protected Navigable[] getPathForSelection(List<MimeType> selection) {
	if (selection.size() != 1) {
	    return null;
	}

	MimeType selected = selection.get(0);

	return new Navigable[] {
	    new SimpleNavigable(MimeTypeControl.ID, selected.getName(),
		MimeTypeControl.PARAM_MIMETYPE, selected.getId())
	};
    }

    //
    // MimeTypesControl methods
    //

    public HasMimeTypes getHasMimeTypes() {
	return parent;
    }
}
