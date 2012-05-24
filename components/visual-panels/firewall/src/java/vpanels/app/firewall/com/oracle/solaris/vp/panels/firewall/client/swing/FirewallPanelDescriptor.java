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

package com.oracle.solaris.vp.panels.firewall.client.swing;

import java.beans.PropertyChangeEvent;
import java.io.IOException;
import java.net.UnknownHostException;
import java.util.*;
import javax.management.*;
import javax.management.remote.JMXConnector;
import javax.swing.*;
import javax.swing.filechooser.FileSystemView;
import com.oracle.solaris.adr.Stability;
import com.oracle.solaris.rad.ObjectException;
import com.oracle.solaris.rad.jmx.RadJMX;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.api.network.*;
import com.oracle.solaris.vp.panel.common.api.file.RemoteFileSystemView;
import com.oracle.solaris.vp.panel.common.api.smf_old.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.panel.swing.control.PanelFrameControl;
import com.oracle.solaris.vp.panel.swing.model.SwingPanelDescriptor;
import com.oracle.solaris.vp.util.misc.SimpleHasId;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.HasIcons;

@SuppressWarnings({"serial"})
public class FirewallPanelDescriptor
    extends ServicePanelDescriptor<ServiceManagedObject>
    implements SwingPanelDescriptor<ServiceManagedObject>, HasIcons,
    HasAccessPolicy {

    //
    // Static data
    //

    protected static final List<ImageIcon> icons = Finder.getIcons(
	"images/global-16.png",
	"images/global-24.png",
	"images/global-32.png");

    public static final String PROPERTY_ACCESS_POLICY = "access policy";

    private static final String SERVICE = "network/ipfilter";
    private static final String INSTANCE = "default";

    public static final String FW_GLOBAL_DEF_PG = "firewall_config_default";
    public static final String FW_GLOBAL_OVR_PG = "firewall_config_override";

    //
    // Instance data
    //

    public AccessPolicy policy = new SimpleAccessPolicy(AccessPolicy.Type.NONE);
    public AccessPolicy ovrPolicy = new SimpleAccessPolicy(
	AccessPolicy.Type.NONE);

    private DefaultControl control;
    private RemoteFileSystemView fsView;
    private MXBeanTracker<NetworkMXBean> networkBeanTracker;
    private SimpleHasId tmpHasId = new SimpleHasId();

    private SimpleSmfPropertyGroupInfo defaultPgInfo;
    private SimpleSmfPropertyGroupInfo overridePgInfo;

    private List<ServiceManagedObject> services =
	new LinkedList<ServiceManagedObject>();
    private List<ServiceManagedObject> roServices =
	Collections.unmodifiableList(services);

    //
    // Constructors
    //

    public FirewallPanelDescriptor(String id,
	ClientContext context) throws InstanceNotFoundException, IOException,
	ScfException, InvalidScfDataException, MissingScfDataException,
	JMException, TrackerException {

	super(id, context, SERVICE, INSTANCE);

	fsView = new RemoteFileSystemView(context);

	networkBeanTracker = new MXBeanTracker<NetworkMXBean>(
	    NetworkUtil.OBJECT_NAME, NetworkMXBean.class, Stability.PRIVATE,
	    context);

	setComparator(SimpleHasId.COMPARATOR);

	defaultPgInfo = new SimpleSmfPropertyGroupInfo(
	    getService(), FW_GLOBAL_DEF_PG);
	overridePgInfo = new SimpleSmfPropertyGroupInfo(
	    getService(), FW_GLOBAL_OVR_PG);

	((SimpleAccessPolicy) policy).setPgInfo(defaultPgInfo);
	((SimpleAccessPolicy) ovrPolicy).setPgInfo(overridePgInfo);
	refresh(true);

	// populate managed services
	populateServiceList();

	control = new PanelFrameControl<FirewallPanelDescriptor>(this);
	control.addChildren(new MainControl(this));
    }

    //
    // HasIcon methods
    //

    @Override
    public List<? extends Icon> getIcons() {
	return icons;
    }

    //
    // HasAccessPolicy methods
    //

    @Override
    public AccessPolicy getAccessPolicy() {
	return policy;
    }

    @Override
    public void setAccessPolicy(AccessPolicy policy) {
	this.policy = policy;
    }

    //
    // ManagedObject methods
    //

    /**
     * Stops monitoring the connection to the remote host.
     */
    @Override
    public void dispose() {
	networkBeanTracker.dispose();
	fsView.dispose();
	super.dispose();
    }

    @Override
    public String getName() {
	return Finder.getString("panel.firewall.name");
    }

    //
    // AbstractManagedObject methods
    //

    @Override
    public void addChildren(ServiceManagedObject... toAdd) {
	super.addChildren(toAdd);
	for (ServiceManagedObject c : toAdd) {
	    int index = Collections.binarySearch(services, c, getComparator());
	    services.remove(index);
	}
    }

    @Override
    public void removeChildren(ServiceManagedObject... toRemove) {
	super.removeChildren(toRemove);
	addManagedServices(toRemove);
    }

    //
    // PanelDescriptor methods
    //

    @Override
    public Control getControl() {
	return control;
    }

    //
    // ServicePanelDescriptor methods
    //

    @Override
    public void refresh(boolean force) throws ScfException,
	InvalidScfDataException, MissingScfDataException {
	super.refresh(force);

	((SimpleAccessPolicy) policy).initFromRepo();
	((SimpleAccessPolicy) ovrPolicy).initFromRepo();
    }

    //
    // FirewallPanelDescriptor methods
    //

    public List<String> getOpenPorts() {
	return policy.getOpenPortList();
    }

    public AccessPolicy getOvrAccessPolicy() {
	return ovrPolicy;
    }

    public void setOvrAccessPolicy(AccessPolicy policy) {
	ovrPolicy = policy;
    }

    public FileSystemView getFileSystemView() {
	return fsView;
    }

    public List<ServiceManagedObject> getAllServices() {
	return roServices;
    }

    public ServiceManagedObject getManagedService(String id) {
	synchronized (children) {
	    tmpHasId.setId(id);
	    int index = Collections.binarySearch(children, tmpHasId,
		SimpleHasId.COMPARATOR);

	    if (index >= 0) {
		return children.get(index);
	    }

	    return null;
	}
    }

    //
    // Set open_port values which update default policy.
    //
    public void updateOpenPorts(List<String> portList) {
	((SimpleAccessPolicy) policy).setPortList(portList);
    }

    //
    // Update all AccessPolicy values but open_port.
    //
    public void updateAccessPolicy(AccessPolicy p) {
	((SimpleAccessPolicy) policy).update(p.getType(), p.getCustomFile(),
	    p.getApplyToList(), p.getExceptionsList(),
	    new ArrayList<String>(policy.getOpenPortList()));
    }

    //
    // Update OvrAccessPolicy values
    //
    public void updateOvrAccessPolicy(AccessPolicy policy) {
	((SimpleAccessPolicy) ovrPolicy).update(policy.getType(),
	    policy.getCustomFile(), policy.getApplyToList(),
	    policy.getExceptionsList(), null);
    }

    public void saveToRepo() throws ScfException, UnknownHostException {
	synchronized (getService()) {
	    getService().pause();
	    try {
		((SimpleAccessPolicy) policy).setRepoValue();
		((SimpleAccessPolicy) ovrPolicy).setRepoValue();

		if (getEnabledProperty().isChanged())
		    getEnabledProperty().saveToRepo();
	    } finally {
		getService().unpause();
	    }
	}

	PropertyChangeEvent e = new PropertyChangeEvent(this,
	    PROPERTY_ACCESS_POLICY, policy, policy);
	firePropertyChange(e);

	e = new PropertyChangeEvent(this, PROPERTY_ACCESS_POLICY,
	    ovrPolicy, ovrPolicy);
	firePropertyChange(e);
    }

    public void resetPolicies() {
	SimpleAccessPolicy p = (SimpleAccessPolicy) policy;
	p.update(p.getSavedType(), p.getSavedCustomFile(),
	    p.getSavedApplyToList(), p.getSavedExceptionsList(),
	    p.getSavedOpenPortList());

	p = (SimpleAccessPolicy) ovrPolicy;
	p.update(p.getSavedType(), p.getSavedCustomFile(),
	    p.getSavedApplyToList(), p.getSavedExceptionsList(),
	    p.getSavedOpenPortList());

	if (getEnabledProperty().isChanged())
	    getEnabledProperty().reset();
    }

    public NetworkMXBean getNetworkMXBean() {
	return networkBeanTracker.getBean();
    }

    //
    // Private methods
    //

    private void addManagedServices(ServiceManagedObject ...svcs) {
	for (ServiceManagedObject s : svcs) {
	    int index = Collections.binarySearch(services, s, getComparator());
	    if (index < 0)
		services.add(-index - 1, s);
	}
    }

    private void populateServiceList() throws ScfException,
	InvalidScfDataException, MissingScfDataException, JMException {

	ConnectionInfo cinfo = getClientContext().getConnectionInfo();
	JMXConnector jmxc = cinfo.getConnector();

	Set<Instance> instances = null;
	MBeanServerConnection mbsc = null;
	AggregatorMXBean aggbean = null;

	try {
	    ObjectName on =
		new ObjectName("com.oracle.solaris.vp.panel.common.api.smf_old"
		    + ":type=Aggregator");
	    mbsc = jmxc.getMBeanServerConnection();
	    aggbean = RadJMX.newMXBeanProxy(mbsc, on,
		AggregatorMXBean.class, Stability.PRIVATE);
	    instances = new HashSet<Instance>(aggbean.getinstances());

	    for (Instance inst : instances) {
		ServiceManagedObject sobj = new ServiceManagedObject(this,
		    mbsc, inst);

		if (!sobj.isFirewallSupported())
		    continue;

		//
		// Mark service inactive if it has default policy
		// else mark it active and add to children list
		//
		if (sobj.isDefaultPolicy()) {
		    addManagedServices(sobj);
		} else {
		    super.addChildren(sobj);
		}
	    }
	} catch (ObjectException e) {
	} catch (IOException e) {
	} catch (MalformedObjectNameException e) {
	} catch (InstanceNotFoundException e) {
	} catch (JMException e) {
	    throw e; // Propagate proxy creation exception
	}

	Collections.sort(services, SimpleHasId.COMPARATOR);
    }
}
