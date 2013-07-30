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
 * Copyright (c) 2009, 2013, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panels.firewall.client.swing;

import java.beans.PropertyChangeEvent;
import java.io.IOException;
import java.net.UnknownHostException;
import java.util.*;
import java.util.logging.Level;
import javax.swing.*;
import com.oracle.solaris.rad.client.ADRName;
import com.oracle.solaris.rad.client.RadException;
import com.oracle.solaris.rad.client.Version;
import com.oracle.solaris.rad.connect.Connection;
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
    implements HasIcon, HasAccessPolicy, ConnectionListener {

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
    private Connection conn;
    private AggregatedRefreshService bean;
    private SimpleSmfPropertyGroupInfo pgInfo;
    private ADRName aname;
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
	Connection conn, Instance inst) throws IOException,
	ScfException, InvalidScfDataException,
	MissingScfDataException {

	this.descriptor = descriptor;
	aname = inst.getObjectName();
	svcName = ServiceUtil.toService(aname);
	id = ServiceUtil.toFMRI(aname);

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
	    getLog().log(Level.SEVERE, Finder.getString("error.server.general"),
		e);
	}
    }

    @Override
    public void connectionFailed(ConnectionEvent event) {
	if (conn != null) {
	    conn = null;
	}
    }

    //
    // ServiceManagedObject methods
    //

    protected void connectionUpdate(ConnectionInfo info)
	throws IOException, RadException {

	if (conn != null) {
	    conn = null;
	}

	try {
	    conn = info.getConnection();
	    bean.setService(new ServiceBeanAdaptor(
		(ServiceInfo)conn.getObject(aname)));
	} catch (RadException e) {
	    getLog().log(Level.SEVERE,
		Finder.getString("error.server.object.missing", aname), e);
	    throw e;
	} catch (IOException e) {
	    getLog().log(Level.WARNING,
		Finder.getString("error.server.proxy.general"), e);
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
