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

package com.oracle.solaris.vp.panel.common;

import java.beans.*;
import java.io.IOException;
import java.util.*;
import java.util.logging.*;
import javax.management.*;
import com.oracle.solaris.vp.util.misc.ObjectUtil;
import com.oracle.solaris.vp.util.misc.event.PropertyChangeListeners;

/**
 * The {@code ConnectionTracker} class manages listeners that depend on
 * connections.
 * </p>
 * {@code ConnectionListener}s that depend on a {@link ClientContext} are
 * automatically removed/added when the tracked {@code ClientContext}
 * fails/changes.
 * </p>
 * {@code NotificationListener}s that depend on an {@code MBeanServerConnection}
 * are automatically removed/added when the tracked {@code
 * MBeanServerConnection} or {@code ObjectName} changes.
 * </p>
 * Property change notifications are sent out when the tracked {@code
 * ClientContext}, {@code ConnectionInfo}, {@code MBeanServerConnection}, or
 * {@code ObjectName} changes.
 */
public class ConnectionTracker implements ConnectionListener {
    //
    // Inner classes
    //

    private abstract class NotifyParams<O> {
	private O listener;
	private NotificationFilter filter;
	private Object handback;

	//
	// Constructors
	//

	public NotifyParams(O listener, NotificationFilter filter,
	    Object handback) {

	    this.listener = listener;
	    this.filter = filter;
	    this.handback = handback;
	}

	//
	// NotifyParams methods
	//

	public boolean equals(Object listener) {
	    return ObjectUtil.equals(this.listener, listener);
	}

	public boolean equals(Object listener, NotificationFilter filter,
	    Object handback) {

	    return ObjectUtil.equals(this.listener, listener) &&
		ObjectUtil.equals(this.filter, filter) &&
		ObjectUtil.equals(this.handback, handback);
	}

	public O getListener() {
	    return listener;
	}

	public NotificationFilter getFilter() {
	    return filter;
	}

	public Object getHandback() {
	    return handback;
	}

	public abstract void add()
	    throws InstanceNotFoundException, IOException;

	public abstract void remove()
	    throws InstanceNotFoundException, IOException;
    }

    private class ListenerNotifyParams
	extends NotifyParams<NotificationListener> {
	//
	// Constructors
	//

	public ListenerNotifyParams(NotificationListener listener,
	    NotificationFilter filter, Object handback) {
	    super(listener, filter, handback);
	}

	//
	// ListenerNotifyParams methods
	//

	@Override
	public void add() throws InstanceNotFoundException, IOException {
	    if (mbsc != null && oName != null) {
		mbsc.addNotificationListener(oName, getListener(), getFilter(),
		    getHandback());
	    }
	}

	@Override
	public void remove() throws InstanceNotFoundException,
	    IOException {

	    if (mbsc != null && oName != null) {
		try {
		    mbsc.removeNotificationListener(oName, getListener(),
			getFilter(), getHandback());
		} catch (ListenerNotFoundException ignore) {
		}
	    }
	}
    }

    private class ObjectNameNotifyParams extends NotifyParams<ObjectName> {
	//
	// Constructors
	//

	public ObjectNameNotifyParams(ObjectName listener,
	    NotificationFilter filter, Object handback) {
	    super(listener, filter, handback);
	}

	//
	// ObjectNameNotifyParams methods
	//

	@Override
	public void add() throws InstanceNotFoundException, IOException {
	    if (mbsc != null && oName != null) {
		mbsc.addNotificationListener(oName, getListener(), getFilter(),
		    getHandback());
	    }
	}

	@Override
	public void remove() throws InstanceNotFoundException,
	    IOException {

	    if (mbsc != null && oName != null) {
		try {
		    mbsc.removeNotificationListener(oName, getListener(),
			getFilter(), getHandback());
		} catch (ListenerNotFoundException ignore) {
		}
	    }
	}
    }

    //
    // Static data
    //

    /**
     * The name of the property that changes with {@link #setClientContext}.
     */
    public static final String PROPERTY_CONTEXT = "context";

    /**
     * The name of the property that changes with {@link #setConnectionInfo}.
     */
    public static final String PROPERTY_INFO = "info";

    /**
     * The name of the property that changes with {@link
     * #setMBeanServerConnection}.
     */
    public static final String PROPERTY_MBSC = "mbsc";

    /**
     * The name of the property that changes with {@link #setObjectName}.
     */
    public static final String PROPERTY_OBJECTNAME = "objectname";

    //
    // Instance data
    //

    private ClientContext context;
    private ConnectionInfo info;
    private MBeanServerConnection mbsc;
    private ObjectName oName;
    private PropertyChangeListeners pListeners = new PropertyChangeListeners();
    private List<NotifyParams> nListeners = new LinkedList<NotifyParams>();

    //
    // Constructors
    //

    public ConnectionTracker(ObjectName oName) {
	try {
	    setObjectName(oName);

	// Impossible because no NotificationListeners have been added yet
	} catch (TrackerException impossible) {
	}
    }

    public ConnectionTracker(ObjectName oName, ClientContext context)
	throws TrackerException {

	this(oName);
	setClientContext(context);
    }

    //
    // ConnectionListener methods
    //

    @Override
    public void connectionChanged(ConnectionEvent event) {
	ConnectionInfo info = event.getConnectionInfo();

	try {
	    setConnectionInfo(info);
	} catch (TrackerException e) {
	    Logger.getLogger(getClass().getName()).log(
		Level.SEVERE, "could not communicate with remote host", e);
	}
    }

    @Override
    public void connectionFailed(ConnectionEvent event) {
	try {
	    setConnectionInfo(null);
	} catch (Throwable ignore) {
	}
    }

    //
    // ConnectionTracker methods
    //

    public void addNotificationListener(NotificationListener listener,
	NotificationFilter filter, Object handback)
	throws InstanceNotFoundException, IOException {

	NotifyParams params = new ListenerNotifyParams(listener, filter,
	    handback);

	params.add();
	nListeners.add(params);
    }

    public void addNotificationListener(ObjectName listener,
	NotificationFilter filter, Object handback)
	throws InstanceNotFoundException, IOException {

	NotifyParams params = new ObjectNameNotifyParams(listener, filter,
	    handback);

	params.add();
	nListeners.add(params);
    }

    public void addPropertyChangeListener(String propName,
	PropertyChangeListener listener) {
	pListeners.add(propName, listener);
    }

    public void addPropertyChangeListener(PropertyChangeListener listener) {
	pListeners.add(listener);
    }

    /**
     * Sets the {@link #getClientContext ClientContext} to {@code null} and
     * removes all listeners, ignoring any exceptions along the way.
     */
    public void dispose() {
	try {
	    setClientContext(null);

	// If something prevented us from removing a notification listener, it
	// probably doesn't matter anymore.
	} catch (TrackerException ignore) {
	}

	pListeners.clear();
	nListeners.clear();
    }

    public ClientContext getClientContext() {
	return context;
    }

    public ConnectionInfo getConnectionInfo() {
	return info;
    }

    public MBeanServerConnection getMBeanServerConnection() {
	return mbsc;
    }

    public ObjectName getObjectName() {
	return oName;
    }

    protected PropertyChangeListeners getPropertyChangeListeners() {
	return pListeners;
    }

    public void removeNotificationListener(NotificationListener listener)
	throws InstanceNotFoundException, IOException {

	for (Iterator<NotifyParams> i = nListeners.iterator(); i.hasNext();) {
	    NotifyParams params = i.next();
	    if (params.equals(listener)) {
		params.remove();
		i.remove();
	    }
	}
    }

    public void removeNotificationListener(NotificationListener listener,
	NotificationFilter filter, Object handback)
	throws InstanceNotFoundException, IOException {

	for (Iterator<NotifyParams> i = nListeners.iterator(); i.hasNext();) {
	    NotifyParams params = i.next();
	    if (params.equals(listener, filter, handback)) {
		params.remove();
		i.remove();
		return;
	    }
	}
    }

    public void removeNotificationListener(ObjectName listener)
	throws InstanceNotFoundException, IOException {

	for (Iterator<NotifyParams> i = nListeners.iterator(); i.hasNext();) {
	    NotifyParams params = i.next();
	    if (params.equals(listener)) {
		params.remove();
		i.remove();
	    }
	}
    }

    public void removeNotificationListener(ObjectName name, ObjectName listener,
	NotificationFilter filter, Object handback)
	throws InstanceNotFoundException, IOException {

	for (Iterator<NotifyParams> i = nListeners.iterator(); i.hasNext();) {
	    NotifyParams params = i.next();
	    if (params.equals(listener, filter, handback)) {
		params.remove();
		i.remove();
		return;
	    }
	}
    }

    public void removePropertyChangeListener(String propName,
	PropertyChangeListener listener) {
	pListeners.remove(propName, listener);
    }

    public void removePropertyChangeListener(PropertyChangeListener listener) {
	pListeners.remove(listener);
    }

    /**
     * Sets the {@code ClientContext}, then calls {@link #setConnectionInfo}.
     *
     * @exception   TrackerException
     *		    if an error occurred during initialization
     */
    public void setClientContext(ClientContext context)
	throws TrackerException {

	if (this.context != context) {
	    if (this.context != null) {
		this.context.removeConnectionListener(this);
	    }

	    PropertyChangeEvent e = new PropertyChangeEvent(
		this, PROPERTY_CONTEXT, this.context, context);
	    this.context = context;
	    pListeners.propertyChange(e);

	    setConnectionInfo(context == null ? null :
		context.getConnectionInfo());

	    if (context != null) {
		context.addConnectionListener(this);
	    }
	}
    }

    /**
     * Sets the {@code ConnectionInfo}, then calls {@link
     * #setMBeanServerConnection}.
     *
     * @exception   TrackerException
     *		    if an error occurred during initialization
     */
    public void setConnectionInfo(ConnectionInfo info)
	throws TrackerException {

	if (this.info != info) {
	    PropertyChangeEvent e = new PropertyChangeEvent(
		this, PROPERTY_INFO, this.info, info);
	    this.info = info;
	    pListeners.propertyChange(e);

	    try {
		setMBeanServerConnection(info == null ? null :
		    info.getConnector().getMBeanServerConnection());
	    } catch (IOException ex) {
		throw new TrackerException(ex);
	    }
	}
    }

    /**
     * Sets the {@code MBeanServerConnection}.
     *
     * @exception   TrackerException
     *		    if an error occurred during initialization
     */
    public void setMBeanServerConnection(MBeanServerConnection mbsc)
	throws TrackerException {

	if (this.mbsc != mbsc) {
	    removeNotificationListeners();

	    PropertyChangeEvent e = new PropertyChangeEvent(
		this, PROPERTY_MBSC, this.mbsc, mbsc);
	    this.mbsc = mbsc;
	    pListeners.propertyChange(e);

	    addNotificationListeners();
	}
    }

    /**
     * Sets the {@code ObjectName}.
     *
     * @exception   TrackerException
     *		    if an error occurred during initialization
     */
    public void setObjectName(ObjectName oName)
	throws TrackerException {

	if (!ObjectUtil.equals(this.oName, oName)) {
	    removeNotificationListeners();

	    PropertyChangeEvent e = new PropertyChangeEvent(
		this, PROPERTY_OBJECTNAME, this.oName, oName);
	    this.oName = oName;
	    pListeners.propertyChange(e);

	    addNotificationListeners();
	}
    }

    //
    // Private methods
    //

    private void addNotificationListeners()
	throws TrackerException {

	if (mbsc != null && oName != null) {
	    for (NotifyParams params : nListeners) {
		try {
		    params.add();
		} catch (InstanceNotFoundException e) {
		    throw new TrackerException(e);
		} catch (IOException e) {
		    throw new TrackerException(e);
		}
	    }
	}
    }

    private void removeNotificationListeners() {
	if (mbsc != null && oName != null) {
	    for (NotifyParams params : nListeners) {
		try {
		    params.remove();

		// If something prevented us from removing a notification
		// listener, it probably doesn't matter anymore.
		} catch (Throwable ignore) {
		}
	    }
	}
    }
}
