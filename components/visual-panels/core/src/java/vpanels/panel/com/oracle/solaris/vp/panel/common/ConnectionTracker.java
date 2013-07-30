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
 * Copyright (c) 2010, 2013, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panel.common;

import java.beans.*;
import java.io.IOException;
import java.util.*;
import java.util.logging.*;
import com.oracle.solaris.rad.client.ADRName;
import com.oracle.solaris.rad.connect.Connection;
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
 * {@code NotificationListener}s that depend on a {@code Connection}
 * are automatically removed/added when the tracked {@code
 * Connection} or {@code ObjectName} changes.
 * </p>
 * Property change notifications are sent out when the tracked {@code
 * ClientContext}, {@code ConnectionInfo}, {@code Connection}, or
 * {@code ObjectName} changes.
 */
public class ConnectionTracker implements ConnectionListener {
    //
    // Inner classes
    //

    private abstract class NotifyParams<O> {
	private O listener;
	private Object handback;

	//
	// Constructors
	//

	public NotifyParams(O listener, Object handback) {

	    this.listener = listener;
	    this.handback = handback;
	}

	//
	// NotifyParams methods
	//

	public boolean equals(Object listener) {
	    return ObjectUtil.equals(this.listener, listener);
	}

	public boolean equals(Object listener, Object handback) {

	    return ObjectUtil.equals(this.listener, listener) &&
		ObjectUtil.equals(this.handback, handback);
	}

	public O getListener() {
	    return listener;
	}

	public Object getHandback() {
	    return handback;
	}

	public abstract void add()
	    throws IOException;

	public abstract void remove()
	    throws IOException;
    }

    private class ObjectNameNotifyParams extends NotifyParams<ADRName> {
	//
	// Constructors
	//

	public ObjectNameNotifyParams(ADRName listener,
	    Object handback) {
	    super(listener, handback);
	}
	//
	// ObjectNameNotifyParams methods
	//

	@Override
	public void add() throws IOException {
	}

	@Override
	public void remove() throws IOException {
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
     * #setServerConnection}.
     */
    public static final String PROPERTY_SCONN = "sconn";

    /**
     * The name of the property that changes with {@link #setObjectName}.
     */
    public static final String PROPERTY_OBJECTNAME = "objectname";

    //
    // Instance data
    //

    private ClientContext context;
    private ConnectionInfo info;
    private Connection conn;
    private ADRName aname;
    private PropertyChangeListeners pListeners = new PropertyChangeListeners();
    private List<NotifyParams> nListeners = new LinkedList<NotifyParams>();

    //
    // Constructors
    //

    public ConnectionTracker(ADRName aname) {
	try {
	    setObjectName(aname);

	// Impossible because no NotificationListeners have been added yet
	} catch (TrackerException impossible) {
	}
    }

    public ConnectionTracker(ADRName aname, ClientContext context)
	throws TrackerException {

	this(aname);
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

    public void addNotificationListener(ADRName listener, Object handback)
	throws IOException {

	NotifyParams params = new ObjectNameNotifyParams(listener, handback);

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

    public Connection getServerConnection() {
	return conn;
    }

    public ADRName getObjectName() {
	return aname;
    }

    protected PropertyChangeListeners getPropertyChangeListeners() {
	return pListeners;
    }

    public void removeNotificationListener(ADRName listener)
	throws IOException {

	for (Iterator<NotifyParams> i = nListeners.iterator(); i.hasNext(); ) {
	    NotifyParams params = i.next();
	    if (params.equals(listener)) {
		params.remove();
		i.remove();
	    }
	}
    }

    public void removeNotificationListener(ADRName name, ADRName listener,
	Object handback)
	throws IOException {

	for (Iterator<NotifyParams> i = nListeners.iterator(); i.hasNext(); ) {
	    NotifyParams params = i.next();
	    if (params.equals(listener, handback)) {
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
     * #setServerConnection}.
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

	    setServerConnection(info == null ? null :
		info.getConnection());
	}
    }

    /**
     * Sets the {@code ServerConnection}.
     *
     * @exception   TrackerException
     *		    if an error occurred during initialization
     */
    public void setServerConnection(Connection conn)
	throws TrackerException {

	if (this.conn != conn) {
	    removeNotificationListeners();

	    PropertyChangeEvent e = new PropertyChangeEvent(
		this, PROPERTY_SCONN, this.conn, conn);
	    this.conn = conn;
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
    public void setObjectName(ADRName aname)
	throws TrackerException {

	if (!ObjectUtil.equals(this.aname, aname)) {
	    removeNotificationListeners();

	    PropertyChangeEvent e = new PropertyChangeEvent(
		this, PROPERTY_OBJECTNAME, this.aname, aname);
	    this.aname = aname;
	    pListeners.propertyChange(e);

	    addNotificationListeners();
	}
    }

    //
    // Private methods
    //

    private void addNotificationListeners()
	throws TrackerException {

	if (conn != null && aname != null) {
	    for (NotifyParams params : nListeners) {
		try {
		    params.add();
		} catch (IOException e) {
		    throw new TrackerException(e);
		}
	    }
	}
    }

    private void removeNotificationListeners() {
	if (conn != null && aname != null) {
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
