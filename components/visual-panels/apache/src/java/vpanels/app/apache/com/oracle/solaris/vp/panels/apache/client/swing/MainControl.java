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

import java.awt.Component;
import java.util.List;
import javax.swing.*;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.panel.common.smf.SmfUtil;
import com.oracle.solaris.vp.panel.swing.control.*;
import com.oracle.solaris.vp.panel.swing.view.ListSelectorPanel;
import com.oracle.solaris.vp.util.misc.ChangeableAggregator;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.SimpleCellRenderer;

public class MainControl extends ListSelectorControl<ApachePanelDescriptor,
   ListSelectorPanel, ManagedObject> {

    //
    // Static data
    //

    public static final String ID = "main";

    //
    // Instance data
    //

    private ListModel model;

    //
    // Constructors
    //

    public MainControl(ApachePanelDescriptor descriptor) {
	super(ID, null, descriptor);
    }

    //
    // Control methods
    //

    @Override
    public void descendantStarted(Control[] path) {
	super.descendantStarted(path);

	// Allow our ChangeableAggregator, which indirectly controls the enabled
	// state of the Apply/Okay/Reset buttons, to track outstanding changes
	// in running descendants.
	Control control = path[path.length - 1];
	if (control instanceof SwingControl) {
	    ChangeableAggregator aggregator =
		((SwingControl)control).getChangeableAggregator();

	    if (aggregator != null) {
		getComponent().getChangeableAggregator().addChangeables(
		    aggregator);
	    }
	}
    }

    @Override
    public void descendantStopped(Control[] path) {
	super.descendantStopped(path);

	// Stop monitoring stopped descendant for changes
	Control control = path[path.length - 1];
	if (control instanceof SwingControl) {
	    ChangeableAggregator aggregator =
		((SwingControl)control).getChangeableAggregator();

	    if (aggregator != null) {
		getComponent().getChangeableAggregator().removeChangeable(
		    aggregator);
	    }
	}
    }

    @Override
    public Navigable[] getForwardingPath(boolean childStopped) {
	return new Navigable[] {
	    new SimpleNavigable(GlobalControl.ID, null)
	};
    }

    @Override
    public String getHelpMapID() {
	return "apache-overview";
    }

    @Override
    protected void save() throws ActionAbortedException, ActionFailedException,
	ActionUnauthorizedException {

	try {
	    ApachePanelDescriptor descriptor = getPanelDescriptor();
	    descriptor.validate();
	    descriptor.saveToRepo();

	} catch (GlobalValidationException e) {
	    // Schedule navigation to global settings
	    getNavigator().goToAsync(false, this,
		new SimpleNavigable(GlobalControl.ID, null));
	    throw e;

	} catch (VirtualHostGeneralValidationException e) {
	    // Schedule navigation to erred virtual host
	    getNavigator().goToAsync(false, this,
		new SimpleNavigable(VirtualHostControl.ID, null,
		    VirtualHostControl.PARAM_ID, e.getId()),
		new SimpleNavigable(VirtualHostGeneralControl.ID, null));
	    throw e;

	} catch (VirtualHostSSLValidationException e) {
	    // Schedule navigation to erred virtual host
	    getNavigator().goToAsync(false, this,
		new SimpleNavigable(VirtualHostControl.ID, null,
		    VirtualHostControl.PARAM_ID, e.getId()),
		new SimpleNavigable(VirtualHostSSLControl.ID, null));
	    throw e;

	} catch (ScfException e) {
	    SmfUtil.throwActionException(e);
	    throw new ActionFailedException(e);

	} catch (SecurityException e) {
	    throw new ActionUnauthorizedException(e);
	}

	super.save();
    }

    //
    // DefaultControl methods
    //

    @Override
    protected void ensureChildrenCreated() {
	if (children.size() == 0) {
	    ApachePanelDescriptor descriptor = getPanelDescriptor();
	    SwingControl[] controls = {
		new GlobalControl(descriptor),
		new VirtualHostControl(descriptor),
	    };

	    addChildren(controls);

	    // Add the Components of these children to the UI now, so that the
	    // UI will be sized to fit the largest Component
	    addToLayout(controls);
	}
    }

    //
    // SwingControl methods
    //

    @Override
    protected void configComponent(ListSelectorPanel panel) {
	super.configComponent(panel);
	addDefaultApplyAction();
	addDefaultCancelAction(true);
	addDefaultOkayAction(true);
	addDefaultHelpAction();
    }

    @Override
    protected ListSelectorPanel createComponent() {
	ListSelectorPanel panel = new ListSelectorPanel();
	panel.setSelectionTitle(Finder.getString("vhosts.list.title"));

	JList list = panel.getSelectionComponent();
	SimpleCellRenderer renderer = new MainListCellRenderer();
	renderer.configureFor(list);
	list.setCellRenderer(renderer);

	panel.getChangeableAggregator().addChangeables(
	    getPanelDescriptor().getChangeableAggregator());

	addAction(panel, new CreateVirtualHostAction(this), true, true);
	addAction(panel, new DeleteVirtualHostAction(this), true, true);
	addAction(panel, new EnableVirtualHostAction(this, true), false, true);
	addAction(panel, new EnableVirtualHostAction(this, false), false, true);
	addAction(panel, new CloneVirtualHostAction(this), false, true);

	return panel;
    }

    //
    // ListSelectorControl methods
    //

    @Override
    protected int getListIndexOf(Control child) {
	if (child instanceof GlobalControl) {
	    return 0;
	}

	VirtualHost vHost = ((VirtualHostControl)child).getVirtualHost();
	int index = getPanelDescriptor().indexOf(vHost) + 1;

	assert vHost == getComponent().getSelectionComponent().getModel().
	    getElementAt(index);

	return index;
    }

    @Override
    protected ListModel getListModel() {
	if (model == null) {
	    model = new MainListModel(getPanelDescriptor());
	}

	return model;
    }

    @Override
    protected Navigable[] getPathForSelection(List<ManagedObject> selection) {
	if (selection.size() != 1) {
	    return null;
	}

	ManagedObject selected = selection.get(0);
	Navigable navigable;

	if (selected instanceof ApachePanelDescriptor) {
	    navigable = new SimpleNavigable(GlobalControl.ID,
		MainListCellRenderer.TEXT_GLOBAL);
	} else {
	    VirtualHost vHost = (VirtualHost)selected;

	    navigable = new SimpleNavigable(VirtualHostControl.ID,
		vHost.getName(), VirtualHostControl.PARAM_ID, vHost.getId());
	}

	return new Navigable[] {navigable};
    }
}
