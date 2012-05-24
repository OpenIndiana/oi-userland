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

package com.oracle.solaris.vp.panel.common.smf;

import java.beans.*;
import java.io.IOException;
import java.util.Locale;
import java.util.logging.Level;
import javax.management.*;
import com.oracle.solaris.rad.jmx.RadNotification;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.api.smf_old.*;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.util.misc.Enableable;
import com.oracle.solaris.vp.util.misc.finder.Finder;

@SuppressWarnings({"serial"})
public abstract class ServicePanelDescriptor<C extends ManagedObject>
    extends AbstractPanelDescriptor<C> implements HasService, HasServiceTracker,
    Enableable {

    //
    // Static data
    //

    public static final String PROPERTY_STATE = "state";

    //
    // Instance data
    //

    private ServiceTracker tracker;
    private String serviceName;
    private String instanceName;

    private SmfEnabledProperty enabledProperty =
	new SmfEnabledProperty(PROPERTY_ENABLED, this);

    private PropertyChangeListener serviceListener =
	new PropertyChangeListener() {
	    @Override
	    public void propertyChange(PropertyChangeEvent event) {
		serviceChanged();
	    }
	};

    /**
     * Handles changes to this {@code ServicePanelDescriptor}'s service.
     * This implementation listens only for {@code StateChangeNotification}s and
     * fires a {@code PropertyChangeEvent} to registered {@code
     * PropertyChangeEvent}s.  Subclasses with {@code ManagedObject} children
     * may wish to override/extend this implementation.
     */
    private NotificationListener notifyListener =
	new NotificationListener() {
	    @Override
	    public void handleNotification(Notification n, Object h) {
		StateChange sc = ((RadNotification)n).getPayload(
		    StateChange.class);

		firePropertyChange(PROPERTY_STATE, null, sc.getState());
		setStatus();
		setStatusText();
		try {
		    refresh(false);
		} catch (Exception e) {
		    getLog().log(Level.SEVERE, Finder.getString(
			"error.repository.read"), e);
		}
	    }
	};

    //
    // Constructors
    //

    public ServicePanelDescriptor(String id, ClientContext context,
	String serviceName, String instanceName) throws IOException,
	InstanceNotFoundException, TrackerException {

	super(id, context);

	this.serviceName = serviceName;
	this.instanceName = instanceName;

	tracker = new ServiceTracker(serviceName, instanceName, context);
	tracker.addNotificationListener(notifyListener,
	    SmfUtil.NOTIFY_FILTER_STATE_CHANGE, null);
	tracker.addPropertyChangeListener(ServiceTracker.PROPERTY_SERVICE,
	    serviceListener);

	serviceChanged();
	setName();
    }

    //
    // ManagedObject methods
    //

    /**
     * Stops monitoring the connection to the remote host.
     */
    @Override
    public void dispose() {
	tracker.dispose();
	super.dispose();
    }

    /**
     * Default implementation that returns {@code null}.
     */
    @Override
    public String getDescription() {
	String locale = Locale.getDefault().getLanguage();

	try {
	    return getService().getDescription(locale);
	} catch (ScfException e) {
	    getLog().log(Level.SEVERE, Finder.getString("error.scf.general"),
		 e);
	}

	return null;
    }

    //
    // PanelDescriptor methods
    //

    @Override
    public boolean getHasFullPrivileges() {
	ConnectionInfo info = getClientContext().getConnectionInfo();
	String user = info.getRole();
	if (user == null) {
	    user = info.getUser();
	}

	// XXX Provide a better diagnostic
	return "root".equals(user);
    }

    //
    // HasService methods
    //

    @Override
    public AggregatedRefreshService getService() {
	// This may be called indirectly by the superclass before tracker has
	// been instantiated
	return tracker == null ? null : tracker.getService();
    }

    //
    // HasServiceTracker methods
    //

    @Override
    public ServiceTracker getServiceTracker() {
	return tracker;
    }

    //
    // Enableable methods
    //

    /**
     * Gets the enabled status from the {@link #getEnabledProperty enabled
     * property}.
     *
     * @return	    {@code true} if enabled, {@code false} if not enabled or if
     *		    the {@link #getEnabledProperty enabled property} has not
     *		    been initialized
     *
     * @see	    #refresh
     */
    @Override
    public boolean isEnabled() {
	Boolean enabled = enabledProperty.getSavedValue();
	return enabled == null ? false : enabled;
    }

    //
    // AbstractManagedObject methods
    //

    /**
     * Downgrades this {@code PanelDescriptor}'s state if the underlying service
     * is degraded.
     */
    @Override
    protected ManagedObjectStatus getCalculatedStatus() {
	ManagedObjectStatus status = super.getCalculatedStatus();

	ServiceMXBean service = getService();
	if (service != null) {
	    ManagedObjectStatus sStatus = null;

	    try {
		SmfState state = service.getState();
		sStatus = ServiceUtil.getPanelStatus(state);
	    } catch (ScfException e) {
		getLog().log(Level.SEVERE, Finder.getString(
		    "error.scf.general"), e);
		sStatus = ManagedObjectStatus.ERROR;
	    }

	    status = status.compareTo(sStatus) > 0 ? status : sStatus;
	}

	return status;
    }

    @Override
    protected String getCalculatedStatusText() {
	SmfState state = null;
	SmfState nextState = null;
	ServiceMXBean service = getService();

	try {
	    state = service.getState();
	    nextState = service.getNextState();
	} catch (ScfException e) {
	    getLog().log(Level.SEVERE, Finder.getString("error.scf.general"),
		 e);
	}

	// Can handle null states
	return ServiceUtil.getStateSynopsis(state, nextState);
    }

    //
    // ServicePanelDescriptor methods
    //

    public SmfEnabledProperty getEnabledProperty() {
	return enabledProperty;
    }

    public String getInstanceName() {
	return instanceName;
    }

    public String getServiceName() {
	return serviceName;
    }

    /**
     * Updates this {@code PanelDescriptor} with service/repository data.  This
     * default implementation updates the {@link #getEnabledProperty enabled
     * property} of this object.
     *
     * @param	    force
     *		    {@code true} to override any values that have been changed
     *		    but not yet saved, {@code false} otherwise
     *
     * @exception   ScfException
     *		    if an error occurs while accessing the SMF repository
     *
     * @exception   InvalidScfDataException
     *		    if data in the repository is invalid
     *
     * @exception   MissingScfDataException
     *		    if data in the repository is missing
     */
    public void refresh(boolean force) throws ScfException,
	InvalidScfDataException, MissingScfDataException {

	enabledProperty.updateFromRepo(force);
    }

    /**
     * Sets the name of this {@code ServicePanelDescriptor}.
     */
    protected void setName() {
	String name = null;
	String locale = Locale.getDefault().getLanguage();

	try {
	    name = getService().getCommonName(locale);
	} catch (ScfException e) {
	    getLog().log(Level.SEVERE, Finder.getString("error.scf.general"),
		 e);
	}

	if (name == null) {
	    name = serviceName.substring(serviceName.indexOf('/') + 1);
	}

	setName(name);
    }

    //
    // Private methods
    //

    private void serviceChanged() {
	setStatus();
	setStatusText();
    }
}
