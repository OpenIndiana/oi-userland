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

package com.oracle.solaris.vp.panels.apache.client.swing;

import java.io.IOException;
import java.util.*;
import javax.management.InstanceNotFoundException;
import javax.swing.*;
import javax.swing.filechooser.FileSystemView;
import com.oracle.solaris.adr.Stability;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.api.network.*;
import com.oracle.solaris.vp.panel.common.api.file.RemoteFileSystemView;
import com.oracle.solaris.vp.panel.common.api.smf_old.PropertyGroup;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.panel.swing.control.PanelFrameControl;
import com.oracle.solaris.vp.panel.swing.model.SwingPanelDescriptor;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.HasIcons;

@SuppressWarnings({"serial"})
public class ApachePanelDescriptor
    extends ServicePanelDescriptor<VirtualHost>
    implements SwingPanelDescriptor<VirtualHost>, ApacheInfo, HasIcons {

    //
    // Static data
    //

    // XXX More sizes should be provided
    protected static final List<ImageIcon> icons = Finder.getIcons(
	"images/apache-32.png");

    public static final String SMF_GROUP = "httpd";

    public static final String PROPERTY_CUSTOM_ENABLED = "custom_conf";
    public static final String PROPERTY_CUSTOM_FILE = "custom_file";
    public static final String PROPERTY_ADDED = "added vhosts";
    public static final String PROPERTY_REMOVED = "removed vhosts";

    private static final String SERVICE = "network/vpanels-http";
    private static final String INSTANCE = "apache2";

    // Sort based on domain, then ID
    private static final Comparator<VirtualHost> COMPARATOR =
	new Comparator<VirtualHost>() {
	    @Override
	    public int compare(VirtualHost o1, VirtualHost o2) {
		int result = ObjectUtil.compare(
		    o1.getDomainProperty().getFirstValue(),
		    o2.getDomainProperty().getFirstValue());

		if (result != 0) {
		    return result;
		}

		return ObjectUtil.compare(o1.getId(), o2.getId());
	    }
	};

    //
    // Instance data
    //

    private DefaultControl control;
    private RemoteFileSystemView fsView;
    private MXBeanTracker<NetworkMXBean> networkBeanTracker;

    private BasicSmfMutableProperty<Boolean> customEnabledProperty =
	new BooleanSmfProperty(PROPERTY_CUSTOM_ENABLED, this);

    private BasicSmfMutableProperty<String> customFileProperty =
	new StringSmfProperty(PROPERTY_CUSTOM_FILE, this);

    private BasicMutableProperty<Integer> addedProperty =
	new IntegerProperty(PROPERTY_ADDED);

    private BasicMutableProperty<Integer> removedProperty =
	new IntegerProperty(PROPERTY_REMOVED);

    private MimeTypes mimeTypes;
    private Modules modules;
    private PropertyGroupNamePool vHostNamePool;
    private List<VirtualHost> removed = new ArrayList<VirtualHost>();

    //
    // Constructors
    //

    public ApachePanelDescriptor(String id, ClientContext context)
	throws IOException, ScfException, InvalidScfDataException,
	MissingScfDataException, InstanceNotFoundException,
	TrackerException {

	super(id, context, SERVICE, INSTANCE);

	fsView = new RemoteFileSystemView(context);

	networkBeanTracker = new MXBeanTracker<NetworkMXBean>(
	    NetworkUtil.OBJECT_NAME, NetworkMXBean.class, Stability.PRIVATE,
	    context);

	vHostNamePool = new PropertyGroupNamePool(getService(),
	    VirtualHost.SMF_GROUP_PREFIX);

	customEnabledProperty.setFirstValue(false);
	addProperties(customEnabledProperty);

	customFileProperty.setFirstValue("");
	addProperties(customFileProperty);

	addProperties(getEnabledProperty());

	addedProperty.update(0, true);
	addProperties(addedProperty);

	removedProperty.update(0, true);
	addProperties(removedProperty);

	setComparator(COMPARATOR);

	ChangeableAggregator aggregator = getChangeableAggregator();

	mimeTypes = new MimeTypes(this);
	aggregator.addChangeables(mimeTypes.getChangeableAggregator());

	modules = new Modules(this);
	aggregator.addChangeables(modules.getChangeableAggregator());

	refresh(true);
	control = new PanelFrameControl<ApachePanelDescriptor>(this);
	control.addChildren(new MainControl(this));
    }

    //
    // HasIcons methods
    //

    @Override
    public List<? extends Icon> getIcons() {
	return icons;
    }

    //
    // SmfPropertyGroupInfo methods
    //

    @Override
    public String getPropertyGroupName() {
	return SMF_GROUP;
    }

    //
    // SmfPropertyInfo methods
    //

    @Override
    public String getPropertyName() {
	// Use the default property names
	return null;
    }

    //
    // ApacheInfo methods
    //

    @Override
    public ApachePanelDescriptor getPanelDescriptor() {
	return this;
    }

    //
    // ManagedObject methods
    //

    @Override
    public void dispose() {
	super.dispose();
	networkBeanTracker.dispose();
	fsView.dispose();
    }

    //
    // PanelDescriptor methods
    //

    @Override
    public Control getControl() {
	return control;
    }

    //
    // AbstractManagedObject methods
    //

    @Override
    public void addChildren(VirtualHost... toAdd) {
	super.addChildren(toAdd);

	ChangeableAggregator aggregator = getChangeableAggregator();
	for (VirtualHost vHost : toAdd) {
	    if (!vHost.isInRepo()) {
		addedProperty.setValue(addedProperty.getValue() + 1);
	    }
	    aggregator.addChangeables(vHost.getChangeableAggregator());
	}
    }

    @Override
    public void removeChildren(VirtualHost... toRemove) {
	super.removeChildren(toRemove);

	ChangeableAggregator aggregator = getChangeableAggregator();
	for (VirtualHost vHost : toRemove) {
	    if (!vHost.isInRepo()) {
		addedProperty.setValue(addedProperty.getValue() - 1);
	    }
	    aggregator.removeChangeable(vHost.getChangeableAggregator());
	}
    }

    //
    // ServicePanelDescriptor methods
    //

    @Override
    public void refresh(boolean force) throws ScfException,
	InvalidScfDataException, MissingScfDataException {

	super.refresh(force);

	for (MutableProperty<?> property : getProperties()) {
	    if (property instanceof SmfMutableProperty) {
		((SmfMutableProperty)property).updateFromRepo(force);
	    }
	}

	// Build list of names of virtual host property groups
	List<String> groups = new ArrayList<String>();
	for (PropertyGroup pg : getService().getPropertyGroups()) {
	    String group = pg.getName();
	    if (group.startsWith(VirtualHost.SMF_GROUP_PREFIX)) {
		groups.add(group);
	    }
	}
	Collections.sort(groups);

	// Remove names of groups that are pending removal on client
	for (Iterator<VirtualHost> i = removed.iterator(); i.hasNext(); ) {
	    VirtualHost vHost = i.next();
	    String group = vHost.getPropertyGroupName();
	    if (groups.remove(group)) {
		// Pending removal on client, still exists on server
	    } else {
		// Pending removal on client, but already removed on server
		i.remove();
		int n = removed.size();
		assert n == removedProperty.getValue() - 1;
		removedProperty.setValue(n);
	    }
	}

	// Remove names of groups already created on the client
	List<VirtualHost> children = new ArrayList<VirtualHost>(getChildren());
	for (VirtualHost vHost : children) {
	    if (vHost.isInRepo()) {
		String group = vHost.getPropertyGroupName();
		if (groups.remove(group)) {
		    // Exists on server, already exists on client
		    vHost.refresh(force);
		} else {
		    // Deleted on server, now must be deleted on client
		    removeChildren(vHost);
		}
	    }
	}

	// The list now contains only groups that have been created on the
	// server but don't yet exist on the client
	for (String group : groups) {
	    VirtualHost vHost = new VirtualHost(this, group);
	    addChildren(vHost);
	}

	mimeTypes.refresh(force);
	modules.refresh(force);
    }

    //
    // ApachePanelDescriptor methods
    //

    public BasicSmfMutableProperty<Boolean> getCustomEnabledProperty() {
	return customEnabledProperty;
    }

    public BasicSmfMutableProperty<String> getCustomFileProperty() {
	return customFileProperty;
    }

    public FileSystemView getFileSystemView() {
	return fsView;
    }

    public MimeTypes getMimeTypes() {
	return mimeTypes;
    }

    public Modules getModules() {
	return modules;
    }

    public VirtualHost getVirtualHost(String id) {
	synchronized (children) {
	    for (VirtualHost vHost : children) {
		if (vHost.getId().equals(id)) {
		    return vHost;
		}
	    }
	    return null;
	}
    }

    /**
     * Gets the first virtual host with the given domain.
     */
    public VirtualHost getVirtualHostByDomain(String domain) {
	synchronized (children) {
	    for (VirtualHost vHost : children) {
		if (vHost.getDomainProperty().getFirstValue().equals(domain)) {
		    return vHost;
		}
	    }
	    return null;
	}
    }

    protected PropertyGroupNamePool getVirtualHostNamePool() {
	return vHostNamePool;
    }

    public void scheduleRemove(VirtualHost... vHosts) {
	for (VirtualHost vHost : vHosts) {
	    if (getChildren().contains(vHost)) {
		removeChildren(vHost);

		if (vHost.isInRepo()) {
		    removed.add(vHost);
		    int n = removed.size();
		    assert n == removedProperty.getValue() + 1;
		    removedProperty.setValue(n);
		}
	    }
	}
    }

    public void saveToRepo() throws ScfException {
	ApacheUtil.saveToRepo(getService(),
	    new ScfRunnable() {
		@Override
		public void run() throws ScfException {
		    for (VirtualHost vHost : getChildren()) {
			vHost.saveToRepo();
		    }
		    addedProperty.setValue(0);

		    for (Iterator<VirtualHost> i = removed.iterator();
			i.hasNext(); ) {

			VirtualHost vHost = i.next();
			vHost.removeFromRepo();
			i.remove();
			int n = removed.size();
			assert n == removedProperty.getValue() - 1;
			removedProperty.setValue(n);
		    }

		    for (MutableProperty<?> property : getProperties()) {
			if (property.isChanged()) {
			    if (property instanceof SmfMutableProperty) {
				((SmfMutableProperty)property).saveToRepo();
			    } else {
				property.save();
			    }
			}
		    }

		    mimeTypes.saveToRepo();
		    modules.saveToRepo();
		}
	    });
    }

    protected void validate() throws GlobalValidationException,
        VirtualHostGeneralValidationException,
	VirtualHostSSLValidationException {

	validateCustomFile();
	for (VirtualHost vHost : getChildren()) {
	    vHost.validate();
	}
    }

    //
    // Private methods
    //

    private void validateCustomFile()
	throws GlobalValidationException {

	if (customEnabledProperty.getFirstValue() &&
	   (customEnabledProperty.isChanged() ||
	    customFileProperty.isChanged()) &&
	    customFileProperty.getFirstValue().isEmpty()) {
	    throw new GlobalValidationException(
		Finder.getString("global.error.customfile.empty"));
	}
    }

    //
    // ApachePanelDescriptor classes
    //

    public NetworkMXBean getNetworkMXBean() {
        return networkBeanTracker.getBean();
    }
}
