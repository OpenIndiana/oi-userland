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

import java.math.BigInteger;
import java.util.*;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.api.smf_old.*;

/**
 * The {@code AggregatedRefreshService} class is a wrapper around another {@link
 * ServiceMXBean} that aggregates calls to {@link #refresh} to minimize the
 * churn in the SMF repository and the risk of incomplete data.  Use of this
 * class should generally follow this pattern:
 * <br/>
 * 1. Prevent refreshes of the wrapped service by calling {@link #pause}.
 * <br/>
 * 2. Use this class with one or more classes that operate on a {@link
 *    ServiceMXBean} (like {@link BasicSmfMutableProperty}).  These classes may
 *    call {@link #refresh} repeatedly.
 * <br/>
 * 3. Flush the pending refresh requests with {@link #unpause}.
 * <br/>
 * Users of this class must take care to invoke step 3 even if step 2 results in
 * an exception.
 */
public class AggregatedRefreshService implements ServiceMXBean {
    //
    // Instance data
    //

    private ServiceMXBean service;
    private boolean paused;
    private boolean refreshNeeded;
    private Boolean instance = null;

    //
    // Constructors
    //

    public AggregatedRefreshService() {
    }

    public AggregatedRefreshService(ServiceMXBean service) {
	setService(service);
    }

    //
    // ServiceMXBean methods
    //

    @Override
    public String getFmri() throws ScfException {
	return service.getFmri();
    }

    @Override
    public List<String> getMethodNames() throws ScfException {
	return service.getMethodNames();
    }

    @Override
    public List<String> getDependencyNames() throws ScfException {
	return service.getDependencyNames();
    }

    @Override
    public Dependency getDependency(String name) throws ScfException {
	return service.getDependency(name);
    }

    @Override
    public List<String> getPropertyNames(String name) throws ScfException {
	return service.getPropertyNames(name);
    }

    @Override
    public PropertyType getPropertyType(String pg_name, String prop_name)
	throws ScfException {
	return service.getPropertyType(pg_name, prop_name);
    }

    @Override
    public List<String> getPropertyValues(String pg_name, String prop_name)
	throws ScfException {
	return service.getPropertyValues(pg_name, prop_name);
    }

    @Override
    public List<String> getSnapshotPropertyValues(String snap_name,
	String pg_name, String prop_name) throws ScfException {
	return service.getSnapshotPropertyValues(snap_name, pg_name, prop_name);
    }

    @Override
    public void setPropertyValues(String pg_name, String prop_name,
	List<String> values) throws ScfException {
	service.setPropertyValues(pg_name, prop_name, values);
    }

    @Override
    public void createPropertyGroup(String pg_name, String prop_name)
	throws ScfException {
	service.createPropertyGroup(pg_name, prop_name);
    }

    @Override
    public void deletePropertyGroup(String pg_name) throws ScfException {
	service.deletePropertyGroup(pg_name);
    }

    @Override
    public void createProperty(String pg_name, String prop_name,
	PropertyType type) throws ScfException {
	service.createProperty(pg_name, prop_name, type);
    }

    @Override
    public void deleteProperty(String pg_name, String prop_name)
	throws ScfException {
	service.deleteProperty(pg_name, prop_name);
    }

    @Override
    public List<PropertyGroup> getPropertyGroups() throws ScfException {
	return service.getPropertyGroups();
    }

    @Override
    public Template getPropertyTemplate(String pg_name, String prop_name,
	String locale) throws ScfException {
	return service.getPropertyTemplate(pg_name, prop_name, locale);
    }

    @Override
    public String getCommonName(String locale) throws ScfException {
	return service.getCommonName(locale);
    }

    @Override
    public String getDescription(String locale) throws ScfException {
	return service.getDescription(locale);
    }

    @Override
    public LogInfo getLogInfo(int max_size) throws ScfException {
	return service.getLogInfo(max_size);
    }

    @Override
    public List<Manpage> getManpages() throws ScfException {
	return service.getManpages();
    }

    @Override
    public List<String> getDoclinks() throws ScfException {
	return service.getDoclinks();
    }

    @Override
    public void maintain(boolean immediate) throws ScfException {
	service.maintain(immediate);
    }

    @Override
    public void clear() throws ScfException {
	service.clear();
    }

    @Override
    public void degrade(boolean immediate) throws ScfException {
	service.degrade(immediate);
    }

    @Override
    public void restart() throws ScfException {
	service.restart();
    }

    @Override
    public boolean isPersistentlyEnabled() throws ScfException {
	return service.isPersistentlyEnabled();
    }

    @Override
    public void setPersistentlyEnabled(boolean enabled) throws ScfException {
	service.setPersistentlyEnabled(enabled);
    }

    @Override
    public boolean isTemporarilyEnabled() throws ScfException {
	return service.isTemporarilyEnabled();
    }

    @Override
    public boolean isEnabled() throws ScfException {
	return service.isEnabled();
    }

    @Override
    public synchronized boolean isInstance() throws ScfException {
	if (instance != null)
	    return (instance);
	return (instance = service.isInstance());
    }

    @Override
    public String getRestarter() throws ScfException {
	return service.getRestarter();
    }

    @Override
    public SmfState getState() throws ScfException {
	return service.getState();
    }

    @Override
    public SmfState getNextState() throws ScfException {
	return service.getNextState();
    }

    @Override
    public Date getSTime() throws ScfException {
	return service.getSTime();
    }

    @Override
    public BigInteger getContractID() throws ScfException {
	return service.getContractID();
    }

    @Override
    public String getAuxiliaryState() throws ScfException {
	return service.getAuxiliaryState();
    }

    @Override
    public String getReason() throws ScfException {
	return service.getReason();
    }

    @Override
    public void refresh() throws ScfException {
	setRefreshNeeded(true);
	refreshConditional();
    }

    //
    // AggregatedRefreshService methods
    //

    public boolean isPaused() {
	return paused;
    }

    public boolean getRefreshNeeded() {
	return refreshNeeded;
    }

    public ServiceMXBean getService() {
	return service;
    }

    /**
     * Calls refresh on the service if not paused and a refresh is needed.
     *
     * @exception   ScfException
     *		    thrown by {@link ServiceMXBean#refresh}
     */
    public synchronized void refreshConditional() throws ScfException {
	if (!paused && refreshNeeded) {
	    service.refresh();
	    refreshNeeded = false;
	}
    }

    public synchronized void pause() {
	paused = true;
    }

    public synchronized void unpause() throws ScfException {
	paused = false;
	refreshConditional();
    }

    public void setRefreshNeeded(boolean refreshNeeded) {
	this.refreshNeeded = refreshNeeded;
    }

    /**
     * Sets the underlying {@link ServiceMXBean} for this {@code
     * AggregatedRefreshService}.
     *
     * @param	    force
     *		    {@code true} to ignore and reset the {@link #pause paused}
     *		    and {@link #getRefreshNeeded refresh needed} states of this
     *		    {@code AggregatedRefreshService}
     *
     * @exception   IllegalStateException
     *		    if this {@code AggregatedRefreshService} is {@link #pause
     *		    paused} or {@link #getRefreshNeeded needs a refresh}
     */
    public synchronized void setService(ServiceMXBean service, boolean force) {
	if (this.service != service) {
	    if (paused && !force) {
		throw new IllegalStateException(
		    "must not change service when paused");
	    }

	    if (refreshNeeded && !force) {
		throw new IllegalStateException(
		    "must not change service with pending refresh");
	    }

	    paused = false;
	    refreshNeeded = false;
	    this.service = service;
	    this.instance = null;
	}
    }

    /**
     * Calls {@link #setService setService}{@code (service, true)}.
     */
    public void setService(ServiceMXBean service) {
	setService(service, true);
    }
}
