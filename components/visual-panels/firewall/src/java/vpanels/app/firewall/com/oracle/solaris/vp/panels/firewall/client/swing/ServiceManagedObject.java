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
import java.util.logging.Level;
import javax.management.*;
import javax.swing.*;
import com.oracle.solaris.adr.Stability;
import com.oracle.solaris.rad.jmx.IncompatibleVersionException;
import com.oracle.solaris.rad.jmx.RadJMX;
import com.oracle.solaris.rad.jmx.RadNotification;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.action.ActionFailedException;
import com.oracle.solaris.vp.panel.common.api.smf_old.*;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.panels.firewall.client.swing.AccessPolicy.Type;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.HasIcon;

@SuppressWarnings({"serial"})
public class ServiceManagedObject
    extends AbstractManagedObject<ManagedObject>
    implements HasIcon, HasAccessPolicy, ConnectionListener,
    NotificationListener {

    //
    // Static data
    //

    // XXX Placeholder for future support of service enabling if we
    // we choose to do so. It may makes sense to support enabling
    // but the semantics varies for different ServiceManageObjects(SMO)
    // - standalone instance, ssh:default, simply enable the instance
    // - service with several instances, network/login, enable all or
    //   provide mechanism to select individual instances?
    // - abstract service, Nfs server, enable nfs/server which would
    //   enable necessary services
    //
    // If we decide not to support enabling, remove all related code.
    //
    public static final String PROPERTY_ENABLED = "enabled";

    protected static final List<ImageIcon> icons = Finder.getIcons(
	"images/service-16.png",
	"images/service-24.png",
	"images/service-32.png");

    public static final String STATE_ENABLED = Finder.getString(
	"service.state.enabled");
    public static final String STATE_DISABLED = Finder.getString(
	"service.state.disabled");

    //
    // Instance data
    //

    private FirewallPanelDescriptor descriptor;
    private MBeanServerConnection mbsc;
    private AggregatedRefreshService bean;
    private SimpleSmfPropertyGroupInfo pgInfo;
    private ObjectName oName;
    private String svcName;
    private String id;

    private AccessPolicy policy;
    private boolean enabled;

    private boolean firewallSupport;
    private Type tempType = Type.NONE;

    //
    // Constructors
    //

    public ServiceManagedObject(FirewallPanelDescriptor descriptor,
	MBeanServerConnection mbsc, Instance inst)
	throws IOException, MalformedObjectNameException, ScfException,
	InvalidScfDataException, MissingScfDataException,
	InstanceNotFoundException, IncompatibleVersionException, JMException {

	this.descriptor = descriptor;
	oName = inst.getObjectName();
	svcName = ServiceUtil.toService(oName);
	id = ServiceUtil.toFMRI(oName);

	bean = new AggregatedRefreshService();
	connectionUpdate(descriptor.getClientContext().getConnectionInfo());
	pgInfo = new SimpleSmfPropertyGroupInfo(bean,
	    SimpleAccessPolicy.FW_CONFIG_PG);

	descriptor.getClientContext().addConnectionListener(this);
	init();

	String name = bean.getCommonName(Locale.getDefault().getLanguage());
	if (name != null) {
	    setName(name);
	}
    }

    //
    // ManagedObject methods
    //

    @Override
    public String getId() {
	return id;
    }

    //
    // HasIcon methods
    //

    @Override
    public Icon getIcon(int height) {
	return IconUtil.getClosestIcon(icons, height);
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
    // ConnectionListener methods
    //

    @Override
    public void connectionChanged(ConnectionEvent event) {
	ConnectionInfo info = event.getConnectionInfo();

	try {
	    connectionUpdate(info);
	} catch (IOException e) {
	    getLog().log(Level.SEVERE, Finder.getString("error.jmx.general"),
		e);
	} catch (JMException e) {
	    // Message logged, ignore.
	}
    }

    @Override
    public void connectionFailed(ConnectionEvent event) {
	if (mbsc != null) {
	    try {
		mbsc.removeNotificationListener(oName, this);

	    // The connection is likely already closed
	    } catch (Throwable ignore) {
	    }

	    mbsc = null;
	}
    }

    //
    // NotificationListener methods
    //

    /**
     * Handles changes to this {@code ServiceManagedObject}.
     * This implementation listens only for {@code StateChangeNotification}s and
     * fires a {@code PropertyChangeEvent} to registered {@code
     * PropertyChangeEvent}s.
     */
    @Override
    public void handleNotification(Notification n, Object h) {
	boolean success = false;

	if (n instanceof RadNotification && n.getType().equals("statechange")) {
	    try {
		refresh();
		success = true;
	    } catch (ScfException e) {
		getLog().log(Level.SEVERE,
		    Finder.getString("error.io.repository"), e);
	    }
	}

	if (success) {
	    PropertyChangeEvent event = new PropertyChangeEvent(
		this, null, null, null);
	    firePropertyChange(event);
	}
    }

    //
    // ServiceManagedObject methods
    //

    protected void connectionUpdate(ConnectionInfo info)
	throws IOException, InstanceNotFoundException, JMException {

	if (mbsc != null) {
	    try {
		mbsc.removeNotificationListener(oName, this);

	    // If something prevented us from removing ourselves as a
	    // notification listener, it probably doesn't matter anymore.
	    } catch (Throwable ignore) {
	    }
	    mbsc = null;
	}

	try {
	    mbsc = info.getConnector().getMBeanServerConnection();
	    mbsc.addNotificationListener(oName, this, null, null);
	    bean.setService(new ServiceMXBeanAdaptor(
		RadJMX.newMXBeanProxy(mbsc, oName,
		ServiceInfoMXBean.class, Stability.PRIVATE)));
	} catch (InstanceNotFoundException e) {
	    getLog().log(Level.SEVERE,
		Finder.getString("error.jmx.mxbean.missing", oName), e);
	    throw e;
	} catch (IncompatibleVersionException e) {
	    getLog().log(Level.SEVERE,
		Finder.getString("error.jmx.proxy.version"), e);
	    throw e;
	} catch (JMException e) {
	    getLog().log(Level.WARNING,
		Finder.getString("error.jmx.proxy.general"), e);
	    throw e;
	}
    }

    public boolean isFirewallSupported() {
	return firewallSupport;
    }

    public FirewallPanelDescriptor getPanelDescriptor() {
	return descriptor;
    }

    public boolean isEnabled() {
	return enabled;
    }

    /**
     * Sets policy and enabled state for this object
     */
    public void refresh() throws ScfException {
	setAccessPolicy(new SimpleAccessPolicy(pgInfo));
	enabled = bean.isEnabled();
	setStatusText(policy.getType());
    }

    /**
     * Set enabled state and whether service support firewall capability
     */
    public void init() throws ScfException {
	enabled = bean.isEnabled();

	BasicSmfMutableProperty<String> policy = new StringSmfProperty(
	    SimpleAccessPolicy.POLICY_PROP, new SimpleSmfPropertyInfo(bean,
	    pgInfo.getPropertyGroupName(), SimpleAccessPolicy.POLICY_PROP));

	if ((firewallSupport = policy.getExistsInRepo())) {
	    tempType = AccessPolicyUtil.toType(policy.getFirstRepoValue());
	    setStatusText(tempType);
	}
    }

    public boolean isDefaultPolicy() {
	return (tempType == Type.USE_GLOBAL);
    }

    public void setEnabled(boolean enabled) {
	if (this.enabled != enabled) {
	    PropertyChangeEvent event = new PropertyChangeEvent(
		this, PROPERTY_ENABLED, this.enabled, enabled);

	    this.enabled = enabled;
	    firePropertyChange(event);
	}
    }

    /**
     * Commit changes and update current policy
     */
    public void setModelAccessPolicy(AccessPolicy policy)
	throws ScfException, MissingScfDataException, ActionFailedException,
	InvalidScfDataException, UnknownHostException {

	if (ObjectUtil.equals(this.policy, policy))
	    return;

	((SimpleAccessPolicy) policy).setPgInfo(pgInfo);
	((SimpleAccessPolicy) policy).setRepoValue();

	PropertyChangeEvent e = new PropertyChangeEvent(this,
	    SimpleAccessPolicy.POLICY_PROP, this.policy, policy);

	this.policy = policy;
	firePropertyChange(e);
    }

    /**
     * Sets the status text based on the state of the underlying service.
     */
    private void setStatusText(Type type) {
        switch (type) {
        case NONE:
            super.setStatusText(Finder.getString("policy.description.none"));
            break;
        case ALLOW:
            super.setStatusText(Finder.getString("policy.description.allow"));
            break;
        case DENY:
            super.setStatusText(Finder.getString("policy.description.deny"));
            break;
        case USE_GLOBAL:
            super.setStatusText(
		Finder.getString("policy.description.useglobal"));
            break;
	}
    }
}
