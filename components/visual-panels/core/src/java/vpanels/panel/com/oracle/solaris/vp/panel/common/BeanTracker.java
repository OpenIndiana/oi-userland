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

import java.beans.PropertyChangeEvent;
import java.io.IOException;
import java.util.logging.*;
import com.oracle.solaris.rad.client.ADRName;
import com.oracle.solaris.rad.client.RadException;
import com.oracle.solaris.rad.connect.Connection;
import com.oracle.solaris.vp.util.misc.ObjectUtil;
import com.oracle.solaris.vp.util.misc.event.PropertyChangeListeners;

/**
 * The {@code BeanTracker} is a {@link ConnectionTracker} that automatically
 * creates and re-creates an {@link #getBean Bean} after changes in the {@link
 * #setServerConnection ServerConnection} or {@link #setObjectName
 * ObjectName}.
 * </p>
 * A property change notification is sent out when the tracked {@code Bean}
 * changes.
 */
public class BeanTracker<T> extends ConnectionTracker {
    //
    // Static data
    //

    /**
     * The name of the property that changes with {@link #setBean}.
     */
    public static final String PROPERTY_BEAN = "bean";

    //
    // Instance data
    //

    private Class<T> clazz;
    private T bean;

    //
    // Constructors
    //

    public BeanTracker(ADRName aName, Class<T> clazz)
    {
	super(aName);
	try {
	    setClass(clazz);

	// Impossible because ServerConnection not yet set
	} catch (TrackerException impossible) {
	}
    }

    public BeanTracker(ADRName aName, Class<T> clazz,
	ClientContext context) throws TrackerException {

	this(aName, clazz);
	setClientContext(context);
    }

    //
    // ConnectionTracker methods
    //

    @Override
    public void setServerConnection(Connection conn)
	throws TrackerException {

	if (getServerConnection() != conn) {
	    super.setServerConnection(conn);
	    setBean();
	}
    }

    @Override
    public void setObjectName(ADRName aName)
	throws TrackerException {

	if (!ObjectUtil.equals(getObjectName(), aName)) {
	    super.setObjectName(aName);
	    setBean();
	}
    }

    //
    // BeanTracker methods
    //

    protected T createBean() throws RadException, IOException {

	T bean = null;
	Connection conn = getServerConnection();
	ADRName aname = getObjectName();
	if (conn != null && aname != null && clazz != null) {
		bean = conn.getObject(aname);
	}

	return bean;
    }

    public T getBean() {
	return bean;
    }

    public Class<T> getBeanClass() {
	return clazz;
    }

    public void setBean(T bean) {
	if (this.bean != bean) {
	    PropertyChangeEvent e = new PropertyChangeEvent(
		this, PROPERTY_BEAN, this.bean, bean);
	    this.bean = bean;
	    getPropertyChangeListeners().propertyChange(e);
	}
    }

    //
    // Private methods
    //

    private void setClass(Class<T> clazz)
	throws TrackerException {

	this.clazz = clazz;
	setBean();
    }

    private void setBean() throws TrackerException {
	T bean = null;
	String message = null;
	Throwable cause = null;

	try {
	    bean = createBean();
	} catch (RadException e) {
	    cause = e;
	    message = "Error getting object information for: "
		+ getObjectName();
	} catch (IOException e) {
	    cause = e;
	    message = "Error contacting server while "
		+ "creating proxy for: " + clazz.getSimpleName();
	}

	setBean(bean);

	if (cause != null) {
	    Logger.getLogger(getClass().getName()).log(
		Level.SEVERE, message, cause);
	    throw new TrackerException(cause);
	}
    }
}
