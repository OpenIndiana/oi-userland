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

import java.beans.PropertyChangeEvent;
import java.io.IOException;
import java.util.logging.*;
import javax.management.*;
import com.oracle.solaris.adr.Stability;
import com.oracle.solaris.rad.jmx.*;
import com.oracle.solaris.vp.util.misc.ObjectUtil;
import com.oracle.solaris.vp.util.misc.event.PropertyChangeListeners;

/**
 * The {@code MXBeanTracker} is a {@link ConnectionTracker} that automatically
 * creates and re-creates an {@link #getBean MXBean} after changes in the {@link
 * #setMBeanServerConnection MBeanServerConnection} or {@link #setObjectName
 * ObjectName}.
 * </p>
 * A property change notification is sent out when the tracked {@code MXBean}
 * changes.
 */
public class MXBeanTracker<T> extends ConnectionTracker {
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
    private Stability stability;

    //
    // Constructors
    //

    public MXBeanTracker(ObjectName oName, Class<T> clazz, Stability stability)
    {
	super(oName);
	try {
	    setClass(clazz, stability);

	// Impossible because mbsc not yet set
	} catch (TrackerException impossible) {
	}
    }

    public MXBeanTracker(ObjectName oName, Class<T> clazz, Stability stability,
	ClientContext context) throws TrackerException {

	this(oName, clazz, stability);
	setClientContext(context);
    }

    //
    // ConnectionTracker methods
    //

    @Override
    public void setMBeanServerConnection(MBeanServerConnection mbsc)
	throws TrackerException {

	if (getMBeanServerConnection() != mbsc) {
	    super.setMBeanServerConnection(mbsc);
	    setBean();
	}
    }

    @Override
    public void setObjectName(ObjectName oName)
	throws TrackerException {

	if (!ObjectUtil.equals(getObjectName(), oName)) {
	    super.setObjectName(oName);
	    setBean();
	}
    }

    //
    // MXBeanTracker methods
    //

    protected T createBean() throws JMException,
	IncompatibleVersionException, IOException {

	T bean = null;
	MBeanServerConnection mbsc = getMBeanServerConnection();
	ObjectName oName = getObjectName();
	if (mbsc != null && oName != null && clazz != null && stability != null)
	{
	    bean = RadJMX.newMXBeanProxy(mbsc, oName, clazz, stability);
	}

	return bean;
    }

    public T getBean() {
	return bean;
    }

    public Class<T> getBeanClass() {
	return clazz;
    }

    public Stability getStability() {
	return stability;
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

    private void setClass(Class<T> clazz, Stability stability)
	throws TrackerException {

	this.clazz = clazz;
	this.stability = stability;
	setBean();
    }

    private void setBean() throws TrackerException {
	T bean = null;
	String message = null;
	Throwable cause = null;

	try {
	    bean = createBean();

	} catch (IncompatibleVersionException e) {
	    cause = e;
	    message = "Incompatible client and server versions for: "
		+ clazz.getSimpleName();

	} catch (JMException e) {
	    cause = e;
	    message = "Error getting MBean information for: " + getObjectName();

	} catch (IOException e) {
	    cause = e;
	    message = "Error contacting MBean server while "
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
