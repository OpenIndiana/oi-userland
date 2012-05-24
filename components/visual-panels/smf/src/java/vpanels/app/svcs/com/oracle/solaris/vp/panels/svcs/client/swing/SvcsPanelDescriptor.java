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

package com.oracle.solaris.vp.panels.svcs.client.swing;

import java.beans.PropertyChangeListener;
import java.io.IOException;
import java.util.*;
import javax.management.InstanceNotFoundException;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.panel.swing.control.PanelFrameControl;
import com.oracle.solaris.vp.panel.swing.model.SwingPanelDescriptor;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.predicate.TruePredicate;

/**
 * Panel descriptor for the Swing SMF panel
 */
public class SvcsPanelDescriptor
    extends AbstractPanelDescriptor<InstanceManagedObject>
    implements SwingPanelDescriptor<InstanceManagedObject> {

    private DefaultControl control_;

    private List<InstanceFilter> filterList_ = new LinkedList<InstanceFilter>();
    private RepoManagedObject repo_;

    private InstanceStatistics stats_;
    final PropertyChangeListener statusListener_ =
	new PropertyChangeForwarder(this);

    @SuppressWarnings({"unchecked"})
    public SvcsPanelDescriptor(String id, ClientContext context)
	throws InstanceNotFoundException, IOException, TrackerException {

	super(id, context);

	repo_ = new RepoManagedObject("repo", context);
	stats_ = new InstanceStatistics(repo_);
	stats_.addPropertyChangeListener(statusListener_);

	filterList_.add(new InstanceFilter("all", repo_,
	    Finder.getString("smf.instances.selection.all"),
	    TruePredicate.getInstance()));
	filterList_.add(new InstanceFilter("enabled", repo_,
	    Finder.getString("smf.instances.selection.enabled"),
	    new EnabledInstancePredicate()));
	filterList_.add(new InstanceFilter("unhealthy", repo_,
	    Finder.getString("smf.instances.selection.unhealthy"),
	    new UnhealthyInstancePredicate()));

	control_ = new PanelFrameControl<SvcsPanelDescriptor>(this);
	control_.addChildren(new SvcsControl(this));
    }

    //
    // ManagedObject methods
    //

    @Override
    public void dispose() {
	repo_.dispose();
	super.dispose();
    }

    @Override
    public String getName()
    {
	return (Finder.getString("smf.panel.name"));
    }

    @Override
    public String getStatusText()
    {
	return (stats_.getStatusText());
    }

    @Override
    public ManagedObjectStatus getStatus()
    {
	return (stats_.getStatus());
    }

    //
    // PanelDescriptor methods
    //

    @Override
    public Control getControl() {
	return control_;
    }

    @Override
    public boolean getHasFullPrivileges()
    {
	return (getClientContext().getConnectionInfo().getUser().
	    equals("root"));
    }

    //
    // SvcsPanelDescriptor methods
    //

    public ManagedObject<InstanceManagedObject> getInstances()
    {
	return repo_;
    }

    public SmfManagedObject getSMO(String fmri)
    {
	return (repo_.getSMO(fmri));
    }


    boolean hasInstance(String service)
    {
	return (repo_.hasInstance(service));
    }

    public InstanceFilter getFilter(String filterName)
    {
	for (InstanceFilter f : filterList_)
	    if (f.getId().equals(filterName))
		return (f);

	return (null);
    }

    public List<InstanceFilter> getFilters()
    {
	return (filterList_);
    }
}
