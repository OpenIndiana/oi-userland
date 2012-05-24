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

package com.oracle.solaris.vp.panel.common.smf;

import java.beans.*;
import java.io.IOException;
import java.util.*;
import java.util.logging.*;
import javax.management.*;
import com.oracle.solaris.adr.Stability;
import com.oracle.solaris.rad.ObjectException;
import com.oracle.solaris.rad.jmx.RadNotification;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.api.panel.MBeanUtil;
import com.oracle.solaris.vp.panel.common.api.file.*;
import com.oracle.solaris.vp.panel.common.api.smf_old.*;
import com.oracle.solaris.vp.panel.common.model.*;

public class RepoManagedObject
    extends AbstractManagedObject<InstanceManagedObject> {

    //
    // Static data
    //

    private static final String DOMAIN = MBeanUtil.VP_DOMAIN + ".smf_old";
    private static final ObjectName oName =
	MBeanUtil.makeObjectName(DOMAIN, "Aggregator");

    //
    // Instance data
    //

    private Set<Service> services;
    private Set<Instance> instances;
    private Map<ObjectName, SmfManagedObject> objects;
    private AbstractManagedObject<ServiceManagedObject> serviceMo;

    private MXBeanTracker<AggregatorMXBean> beanTracker;
    private MXBeanTracker<FileBrowserMXBean> filebeanTracker;

    private NotificationListener stateListener =
	new NotificationListener() {
	    @Override
	    public void handleNotification(Notification notification,
		Object handback) {

		StateChange sc = ((RadNotification)notification).getPayload(
		    StateChange.class);
		stateChanged(sc);
	    }
	};

    private PropertyChangeListener beanListener =
	new PropertyChangeListener() {
	    @Override
	    public void propertyChange(PropertyChangeEvent event) {
		beanChanged();
	    }
	};

    //
    // Constructors
    //

    public RepoManagedObject(String id, ClientContext context)
	throws InstanceNotFoundException, IOException, TrackerException {

	super(id);

	beanTracker = new MXBeanTracker<AggregatorMXBean>(
	    oName, AggregatorMXBean.class, Stability.PRIVATE, context);

	beanTracker.addNotificationListener(stateListener,
	    SmfUtil.NOTIFY_FILTER_STATE_CHANGE, null);

	beanTracker.addPropertyChangeListener(
	    MXBeanTracker.PROPERTY_BEAN, beanListener);

	filebeanTracker = new MXBeanTracker<FileBrowserMXBean>(
            FileBrowserUtil.OBJECT_NAME, FileBrowserMXBean.class,
            Stability.PRIVATE, context);

	objects = Collections.emptyMap();
	serviceMo = new AbstractManagedObject<ServiceManagedObject>() {};

	beanChanged();
    }

    //
    // ManagedObject methods
    //

    /**
     * Stops monitoring the connection to the remote host.
     */
    @Override
    public void dispose() {
	beanTracker.dispose();
	filebeanTracker.dispose();
	super.dispose();
    }

    //
    // RepoManagedObject methods
    //

    public boolean hasInstance(String service) {
	ObjectName pattern;

	try {
	    pattern = ServiceUtil.getServiceObjectName(service, "*");
	} catch (MalformedObjectNameException ex) {
	    return false;
	}

	for (Instance instance : instances)
	    if (pattern.apply(instance.getObjectName())) {
		return true;
	    }

	return false;
    }

    public ConnectionTracker getConnectionTracker() {
	return beanTracker;
    }

    public ManagedObject<ServiceManagedObject> getServices() {
	return serviceMo;
    }

    public SmfManagedObject getSMO(String fmri) {
	for (SmfManagedObject smo : children)
	    if (smo.getId().equals(fmri)) {
		return smo;
	    }

	return null;
    }

    public SmfManagedObject getServiceSMO(String fmri) {
	for (SmfManagedObject smo : serviceMo.getChildren())
	    if (smo.getId().equals(fmri)) {
		return smo;
	    }

	return null;
    }

    public boolean fileExists(String filename) {
	try {
	    return filebeanTracker.getBean().getFile(filename).isExists();
	} catch (ObjectException e) {
	}
	return false;
    }

    //
    // Private methods
    //

    private void beanChanged() {
	services = Collections.emptySet();
	instances = Collections.emptySet();

	AggregatorMXBean bean = beanTracker.getBean();
	if (bean != null) {
	    try {
		services = new HashSet<Service>(bean.getservices());
		instances = new HashSet<Instance>(bean.getinstances());
	    } catch (ObjectException e) {
		Logger.getLogger(getClass().getName()).log(Level.SEVERE,
		    "could not retrieve smf services/instances", e);
	    }
	}

	/*
	 * Ideally, this would preserve those children that remain after a
	 * relogin, and throw away children after a host change.
	 *
	 * Right now, it preserves objects but not the child list on both
	 * relogin and host changes.
	 */

	clearChildren();
	serviceMo.clearChildren();
	Map<ObjectName, SmfManagedObject> oldObjects = objects;
	objects = new HashMap<ObjectName, SmfManagedObject>(objects);

	for (Service svc : services) {
	    ObjectName oName = svc.getObjectName();
            ServiceManagedObject smo =
		(ServiceManagedObject)oldObjects.get(oName);
	    if (smo == null) {
		try {
		    smo = new ServiceManagedObject(this,
			beanTracker.getClientContext(), svc);
		} catch (TrackerException e) {
		    smo = null;
		}
	    } else {
		oldObjects.remove(oName);
	    }

	    if (smo != null) {
		objects.put(oName, smo);
		serviceMo.addChildren(smo);
	    }
	}

	for (Instance inst : instances) {
	    ObjectName oName = inst.getObjectName();
	    InstanceManagedObject imo =
		(InstanceManagedObject)oldObjects.get(oName);
	    if (imo == null) {
		try {
		    imo = new InstanceManagedObject(
			beanTracker.getClientContext(), inst);
		} catch (TrackerException e) {
		    imo = null;
		}
	    } else {
		oldObjects.remove(oName);
	    }

	    if (imo != null) {
		objects.put(oName, imo);
		addChildren(imo);
	    }
	}

	// Ensure that any SmfManagedObjects for now-non-existent services are
	// prepared for garbage collection
	for (SmfManagedObject smo : oldObjects.values()) {
	    smo.dispose();
	}
    }

    private void stateChanged(StateChange sc) {
	SmfManagedObject smo = objects.get(sc.getSource());
	if (smo != null && smo instanceof InstanceManagedObject) {
	    InstanceManagedObject imo = (InstanceManagedObject)smo;
	    imo.handleStateChange(sc);
	}
    }
}
