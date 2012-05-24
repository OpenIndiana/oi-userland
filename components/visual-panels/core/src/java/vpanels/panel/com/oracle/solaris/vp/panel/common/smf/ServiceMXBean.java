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
 * An SMF service (and instance) MXBean interface
 *
 * (This isn't actually an MXBean interface, it's a wrapper around the
 * real one.)
 */
public interface ServiceMXBean
{
	/**
	 * Get the FMRI.
	 */
	String getFmri() throws ScfException;

	/**
	 * Get method names.
	 */
	List<String> getMethodNames() throws ScfException;

	/**
	 * Get dependency names.
	 */
	List<String> getDependencyNames() throws ScfException;

	/**
	 * Get dependency properties.
	 *
	 * @param name dependency name
	 */
	Dependency getDependency(String name) throws ScfException;

	/**
	 * Get property names in a property group.
	 *
	 * @param name property group name
	 */
	List<String> getPropertyNames(String name) throws ScfException;

	/**
	 * Get type of a property.
	 *
	 * @param pg_name property group name
	 * @param prop_name property name
	 */
	PropertyType getPropertyType(String pg_name, String prop_name)
	    throws ScfException;

	/**
	 * Get values of a property.
	 *
	 * @param pg_name property group name
	 * @param prop_name property name
	 */
	List<String> getPropertyValues(String pg_name, String prop_name)
	    throws ScfException;

	/**
	 * Get values of a property in a snapshot.
	 *
	 * @param snap_name snapshot name
	 * @param pg_name property group name
	 * @param prop_name property name
	 */
	List<String> getSnapshotPropertyValues(String snap_name, String pg_name,
	    String prop_name) throws ScfException;

	/**
	 * Set the current values of a property.
	 *
	 * @param pg_name property group name
	 * @param prop_name property name
	 * @param values values
	 */
	void setPropertyValues(String pg_name, String prop_name,
	    List<String> values) throws ScfException;

	/**
	 * Create property group.
	 *
	 * @param pg_name property group name
	 * @param prop_name property type
	 */
	void createPropertyGroup(String pg_name, String prop_name)
	    throws ScfException;

	/**
	 * Delete named property group.
	 *
	 * @param pg_name property group name
	 */
	void deletePropertyGroup(String pg_name)
	    throws ScfException;

	/**
	 * Create property.
	 *
	 * @param pg_name property group name
	 * @param prop_name property name
	 * @param type property type
	 */
	void createProperty(String pg_name, String prop_name,
	    PropertyType type) throws ScfException;

	/**
	 * Delete named property.
	 *
	 * @param pg_name property group name
	 * @param prop_name property name
	 */
	void deleteProperty(String pg_name, String prop_name)
	    throws ScfException;

	/**
	 * Get property group names.
	 */
	List<PropertyGroup> getPropertyGroups() throws ScfException;

	/**
	 * Get template information for a property.
	 *
	 * @param pg_name property group name
	 * @param prop_name property name
	 * @param locale locale name
	 */
	Template getPropertyTemplate(String pg_name, String prop_name,
	    String locale) throws ScfException;

	/**
	 * Get the common name of a service.
	 *
	 * @param locale locale name
	 */
	String getCommonName(String locale) throws ScfException;

	/**
	 * Get the description of a service.
	 *
	 * @param locale locale name
	 */
	String getDescription(String locale) throws ScfException;

	/**
	 * Get the contents of the log file for this service instance.
	 *
	 * @param	    max_size
	 *		    the maximum size of the returned array (populated
	 *		    from the end of the log file), or -1 to return the
	 *		    entire file
	 */
	LogInfo getLogInfo(int max_size) throws ScfException;

	/**
	 * Get manual pages.
	 */
	List<Manpage> getManpages() throws ScfException;

	/**
	 * Get documentation links.
	 */
	List<String> getDoclinks() throws ScfException;

	/**
	 * Put into maintenance.
	 *
	 * @param immediate do immediately
	 */
	void maintain(boolean immediate) throws ScfException;

	/**
	 * Clear maintenance.
	 */
	void clear() throws ScfException;

	/**
	 * Put into degraded state.
	 *
	 * @param immediate do immediately
	 */
	void degrade(boolean immediate) throws ScfException;

	/**
	 * Restart the service.
	 */
	void restart() throws ScfException;

	/**
	 * Refresh the service.
	 */
	void refresh() throws ScfException;

	/*
	 * "Attributes"
	 */

	/**
	 * Service should run on next boot.
	 */
	boolean isPersistentlyEnabled() throws ScfException;

	/**
	 * Service should run on next boot.
	 *
	 * @param enabled service should run on next boot
	 */
	void setPersistentlyEnabled(boolean enabled) throws ScfException;

	/**
	 * Service should run until next boot.
	 */
	boolean isTemporarilyEnabled() throws ScfException;

	/**
	 * Service should run.
	 */
	boolean isEnabled() throws ScfException;

	/**
	 * Whether Service is an instance.
	 */
	boolean isInstance() throws ScfException;

	/**
	 * Restarter of service.
	 */
	String getRestarter() throws ScfException;

	/**
	 * Current state of service.
	 */
	SmfState getState() throws ScfException;

	/**
	 * Next state of service.
	 */
	SmfState getNextState() throws ScfException;

	/**
	 * Time of last state transition.
	 */
	Date getSTime() throws ScfException;

	/**
	 * Process contract of main processes.
	 */
	BigInteger getContractID() throws ScfException;

	/**
	 * Extra state information.
	 */
	String getAuxiliaryState() throws ScfException;

	/**
	 * Reason for state.
	 */
	String getReason() throws ScfException;
}
