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

import java.net.URISyntaxException;
import java.util.*;
import java.util.logging.*;
import javax.management.ObjectName;
import javax.swing.*;
import com.oracle.solaris.scf.common.*;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.api.smf_old.Dependency;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.panel.common.smf.depend.DepManagedObject;
import com.oracle.solaris.vp.util.misc.IconUtil;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.HasIcon;

public abstract class SmfManagedObject extends DepManagedObject<ManagedObject>
    implements HasService, HasIcon, Comparable<SmfManagedObject> {

    //
    // Static data
    //

    public static final List<ImageIcon> icons =
	Collections.unmodifiableList(Finder.getIcons(
	"images/smf-32.png",
	"images/smf-48.png",
	"images/smf-96.png",
	"images/smf-192.png"));

    //
    // Instance data
    //

    private ServiceTracker tracker;
    private ObjectName on;
    private FMRI fmri;
    private String name;
    private String desc;
    private Map<String, Dependency> dependencies;
    private String serviceName;
    private PropertyGroupsManagedObject properties;

    //
    // Constructors
    //

    public SmfManagedObject(ClientContext context, String fmri, ObjectName on)
	throws TrackerException {

	tracker = new ServiceTracker(on, context);
	try {
	    this.fmri = new FMRI(fmri);
	} catch (URISyntaxException e) {
	    this.fmri = null;
	}
	this.on = on;
	serviceName = ServiceUtil.toService(on);
    }

    //
    // Comparable methods
    //

    @Override
    public int compareTo(SmfManagedObject o) {
	return fmri.compareTo(o.fmri);
    }

    //
    // HasIcon methods
    //

    @Override
    public Icon getIcon(int height) {
	return IconUtil.getClosestIcon(icons, height);
    }

    //
    // HasId methods
    //

    @Override
    public String getId() {
	return fmri.toString();
    }

    //
    // HasService methods
    //

    @Override
    public AggregatedRefreshService getService() {
	return tracker.getService();
    }

    //
    // ManagedObject methods
    //

    @Override
    public void dispose() {
	tracker.dispose();
	super.dispose();
    }

    @Override
    public String getName() {
	return fmri.toString();
    }

    //
    // DepManagedObject methods
    //

    @Override
    public String getDepName() {
	return getSMFFmri().toString();
    }

    //
    // SmfManagedObject methods
    //

    public PropertyGroupsManagedObject getPropertyGroups() {
	if (properties == null) {
	    try {
		properties = new PropertyGroupsManagedObject(tracker);
		addChildren(properties);
	    } catch (ScfException e) {
		Logger log = Logger.getLogger(getClass().getName());
		log.log(Level.WARNING, "error gathering SMF property info", e);
	    }
	}
	return properties;
    }

    public ServiceTracker getServiceTracker() {
	return tracker;
    }

    public FMRI getSMFFmri() {
	return fmri;
    }

    public String getSMFName() {
	synchronized (this) {
	    if (name != null) {
		return name;
	    }

	    try {
		name = getService().getCommonName(
		    Locale.getDefault().getLanguage());
	    } catch (ScfException e) {
	    }
	    return name;
	}
    }

    public String getSMFDesc() {
	synchronized (this) {
	    if (desc != null) {
		return desc;
	    }

	    try {
		desc = getService().getCommonName(
		    Locale.getDefault().getLanguage());
	    } catch (ScfException e) {
	    }
	    return desc;
	}
    }

    public Collection<Dependency> getDependencies() {
	synchronized (this) {
	    if (dependencies != null) {
		return dependencies.values();
	    }

	    try {
		dependencies = new HashMap<String, Dependency>();
		ServiceMXBean service = getService();
		List<String> deps = service.getDependencyNames();
		for (String dep : deps) {
		    dependencies.put(dep, service.getDependency(dep));
		}
	    } catch (ScfException e) {
	    }

	    return dependencies.values();
	}
    }

    public ObjectName getObjectName() {
	return on;
    }
}
