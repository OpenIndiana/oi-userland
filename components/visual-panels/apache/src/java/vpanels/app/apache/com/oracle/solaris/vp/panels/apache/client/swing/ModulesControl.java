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
import com.oracle.solaris.vp.panel.swing.control.*;
import com.oracle.solaris.vp.panel.swing.view.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;

public class ModulesControl extends ListSelectorControl<ApachePanelDescriptor,
    ListSelectorPanel, Module> implements HasIcons {

    //
    // Static data
    //

    public static final String ID = "modules";
    public static final String NAME = Finder.getString("modules.title");

    //
    // Instance data
    //

    private HasModules parent;

    //
    // Constructors
    //

    public ModulesControl(ApachePanelDescriptor descriptor,
	HasModules parent) {

	super(ID, NAME, descriptor);
	this.parent = parent;
    }

    //
    // HasIcons methods
    //

    @Override
    public List<? extends Icon> getIcons() {
	return Module.icons;
    }

    //
    // Control methods
    //

    @Override
    public Navigable[] getForwardingPath(boolean childStopped) {
	List<Module> modules = parent.getModules().getChildren();
	if (!modules.isEmpty()) {

	    Module module = modules.get(0);

	    return new Navigable[] {
		new SimpleNavigable(ModuleControl.ID, null,
		    ModuleControl.PARAM_MODULE, module.getId())
	    };
	}

	return null;
    }

    @Override
    public String getHelpMapID() {
	return "apache-modules";
    }

    //
    // DefaultControl methods
    //

    @Override
    protected void ensureChildrenCreated() {
	if (children.size() == 0) {
	    ApachePanelDescriptor descriptor = getPanelDescriptor();
	    SwingControl child = new ModuleControl(descriptor, this);
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
	panel.setSelectionTitle(Finder.getString("modules.list.title"));

	JList list = panel.getSelectionComponent();
	SimpleCellRenderer renderer = new ManagedObjectCellRenderer<Module>();
	renderer.configureFor(list);
	list.setCellRenderer(renderer);

	addAction(panel, new CreateModuleAction(this), true, true);
	addAction(panel, new DeleteModuleAction(this), true, true);

	setDefaultContentView(new NoModulePanel());

	return panel;
    }

    //
    // ListSelectorControl methods
    //

    @Override
    protected int getListIndexOf(Control child) {
	Module module = ((ModuleControl)child).getModule();
	int index = parent.getModules().indexOf(module);
	assert module == getComponent().getSelectionComponent().getModel().
	    getElementAt(index);
	return index;
    }

    @Override
    protected ListModel getListModel() {
	return new ManagedObjectTableModel<Module>(parent.getModules());
    }

    @Override
    protected Navigable[] getPathForSelection(List<Module> selection) {
	if (selection.size() != 1) {
	    return null;
	}

	Module selected = selection.get(0);

	return new Navigable[] {
	    new SimpleNavigable(ModuleControl.ID, selected.getName(),
		ModuleControl.PARAM_MODULE, selected.getId())
	};
    }

    //
    // ModulesControl methods
    //

    public HasModules getHasModules() {
	return parent;
    }
}
