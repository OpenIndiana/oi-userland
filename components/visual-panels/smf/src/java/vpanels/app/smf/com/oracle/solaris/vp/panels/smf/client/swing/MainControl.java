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

package com.oracle.solaris.vp.panels.smf.client.swing;

import java.awt.Component;
import java.util.*;
import javax.swing.*;
import javax.swing.border.Border;
import com.oracle.solaris.scf.common.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.FilterManagedObject;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.panel.swing.control.*;
import com.oracle.solaris.vp.panel.swing.smf.EnableServiceAction;
import com.oracle.solaris.vp.panel.swing.view.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.predicate.Predicate;
import com.oracle.solaris.vp.util.swing.ClippedBorder;

public class MainControl extends ListSelectorControl<SmfPanelDescriptor,
    ListSelectorPanel, SmfManagedObject>
    implements HasSmfManagedObject<ServiceManagedObject> {

    //
    // Inner classes
    //

    /**
     * Cell renderer for {@code SmfManagedObject}s that displays only
     * the service or instance part of a service or instance name,
     * respectively.
     *
     * XXX: Should use different icons.  As it stands, nothing
     * distinguishes the two other than position in the list and the
     * presence/absence of status text.
     */
    private static class SmfCellRenderer
	extends ManagedObjectCellRenderer<SmfManagedObject> {
	@Override
	public String getText(Component comp, SmfManagedObject obj,
	    boolean isSelected, boolean hasFocus) {

	    FMRI fmri = obj.getSMFFmri();
	    return (fmri.getSvcType() == FMRIType.INSTANCE ?
		fmri.getInstance() : fmri.getService());
	}
    }

    /**
     * A predicate that matches instances that belong to the current
     * service.
     */
    private class MatchingInstancePredicate
	implements Predicate<InstanceManagedObject> {
	@Override
	public boolean test(InstanceManagedObject o) {
	    return o.getServiceFmri().equals(service.getSMFFmri());
	}
    }

    //
    // Static data
    //

    public static final String ID = "svc";
    public static final String PARAM_SERVICE = "service";

    //
    // Instance data
    //

    private InstanceStatistics stats = new InstanceStatistics();
    private ServiceManagedObject service;

    private MainListModel model;
    private FilterManagedObject<InstanceManagedObject> fRepo;
    private MatchingInstancePredicate pred = new MatchingInstancePredicate();

    //
    // Constructors
    //

    public MainControl(SmfPanelDescriptor descriptor) {
	super(ID, null, descriptor);
    }

    //
    // HasSmfManagedObject methods
    //

    @Override
    public ServiceManagedObject getSmfManagedObject() {
	return service;
    }

    //
    // Control methods
    //

    @Override
    public Navigable[] getForwardingPath(boolean childStopped) {
	return new Navigable[] { ServiceTabbedControl.NAVIGABLE };
    }

    @Override
    public boolean isBrowsable() {
	// This Control requires init parameters
	return false;
    }

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	String param = getParameter(parameters, PARAM_SERVICE);

	FMRI fmri = new FMRI(FMRIScheme.SERVICE, FMRIType.SERVICE, null, null,
	    param, null, null, null);

	RepoManagedObject repo = getPanelDescriptor().getRepo();
	SmfManagedObject smo = repo.getServiceSMO(fmri.toString());
	if (smo == null || !(smo instanceof ServiceManagedObject)) {
	    throw new InvalidParameterException(getId(), PARAM_SERVICE, param);
	}

	setService((ServiceManagedObject)smo);

	fRepo = new FilterManagedObject<InstanceManagedObject>(repo, pred);
	stats.setManagedObject(fRepo);

	super.start(navigator, parameters);
    }

    @Override
    public void stop(boolean isCancel) throws NavigationAbortedException {
	super.stop(isCancel);

	// Remove reference so it can be garbage collected if deleted
	setService(null);

	stats.setManagedObject(null);
    }

    //
    // DefaultControl methods
    //

    @Override
    protected void ensureChildrenCreated() {
	if (children.size() == 0) {
	    SmfPanelDescriptor descriptor = getPanelDescriptor();

	    ServiceTabbedControl service =
		new ServiceTabbedControl(descriptor, this);

	    InstanceTabbedControl instance =
		new InstanceTabbedControl(descriptor, this);

	    addChildren(service, instance);
	    addToLayout(service, instance);
	}
    }

    //
    // SwingControl methods
    //

    @Override
    protected void configComponent(ListSelectorPanel comp) {
	super.configComponent(comp);

	addDefaultCloseAction(true);

	getComponent().getSelectionComponent().setSelectionMode(
	    ListSelectionModel.SINGLE_SELECTION);
    }

    @Override
    protected ListSelectorPanel createComponent() {
	ListSelectorPanel panel = new ListSelectorPanel();
	panel.setSelectionTitle(Finder.getString("smf.sidebar.title"));

	Border border = panel.getBorder();
	panel.setBorder(new ClippedBorder(border, false, true, true, true));

	final JList list = panel.getSelectionComponent();
	SmfCellRenderer renderer = new SmfCellRenderer();
	list.setCellRenderer(renderer);
	renderer.configureFor(list);

	addAction(panel, new EnableServiceAction(this, true), false, true);
	addAction(panel, new EnableServiceAction(this, false), false, true);

	return panel;
    }

    //
    // SelectorControl methods
    //

    @Override
    protected Navigable[] getPathForSelection(List<SmfManagedObject> selection)
    {
	if (selection.size() != 1) {
	    return null;
	}

	SmfManagedObject selected = selection.get(0);
	Navigable navigable;

	if (selected instanceof ServiceManagedObject) {
	    navigable = ServiceTabbedControl.NAVIGABLE;
	} else {
	    navigable = new SimpleNavigable(InstanceTabbedControl.ID,
		selected.getName(), InstanceTabbedControl.PARAM_INSTANCE,
		selected.getSMFFmri().getInstance());
	}

	return new Navigable[] { navigable };
    }

    //
    // ListSelectorControl methods
    //

    @Override
    protected int getListIndexOf(Control child) {
	if (child instanceof ServiceTabbedControl) {
	    return 0;
	}

        InstanceManagedObject instance =
	    ((InstanceTabbedControl)child).getSmfManagedObject();

	return model.indexOf(instance);
    }

    @Override
    protected ListModel getListModel() {
	if (model == null) {
	    model = new MainListModel(service, fRepo);
	}

	return model;
    }

    //
    // MainControl methods
    //

    public InstanceStatistics getStats() {
	return stats;
    }

    //
    // Private methods
    //

    private void setService(ServiceManagedObject service) {
	this.service = service;
	setName(service == null ? null : service.getName());
    }
}
