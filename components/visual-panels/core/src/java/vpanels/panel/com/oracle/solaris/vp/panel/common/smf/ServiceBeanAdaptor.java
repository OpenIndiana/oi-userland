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

package com.oracle.solaris.vp.panel.common.smf;

import java.math.BigInteger;
import java.util.*;
import com.oracle.solaris.rad.client.RadObjectException;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.api.smf_old.*;

/**
 * ServiceBeanAdaptor wraps a ServiceInfoBean and provides an
 * old-style ServiceBean interface.  Because the use of the
 * ServiceBean interface and the ScfExceptions is so widespread,
 * it is simpler to make the bridge from ObjectExceptions here
 * rather than at the site of each use.
 * <br/>
 * For classloading reasons this mapping can never be completely
 * automatic.  It might prove fruitful to create an generic wrapper
 * using {@code Proxy}, though.
 */
public class ServiceBeanAdaptor implements ServiceBean {

    ServiceInfo sibean_;

    public ServiceBeanAdaptor(ServiceInfo sibean) {
	sibean_ = sibean;
    }

    public String getFmri() throws ScfException {
	try {
	    return sibean_.getfmri();
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    public List<String> getMethodNames() throws ScfException {
	try {
	    return sibean_.getmethodNames();
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    public List<String> getDependencyNames() throws ScfException {
	try {
	    return sibean_.getdependencyNames();
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    @Override
    public Dependency getDependency(String name) throws ScfException {
	try {
	    return sibean_.getDependency(name);
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    @Override
    public List<String> getPropertyNames(String pg_name) throws ScfException {
	try {
	    return sibean_.getPropertyNames(pg_name);
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    @Override
    public PropertyType getPropertyType(String pg_name, String prop_name)
	throws ScfException {

	try {
	    return sibean_.getPropertyType(pg_name, prop_name);
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    @Override
    public List<String> getPropertyValues(String pg_name, String prop_name)
	throws ScfException {

	try {
	    return sibean_.getPropertyValues(pg_name, prop_name);
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    @Override
    public List<String> getSnapshotPropertyValues(String snap_name,
	String pg_name, String prop_name) throws ScfException {

	try {
	    return sibean_.getSnapshotPropertyValues(snap_name, pg_name,
		prop_name);
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    @Override
    public void setPropertyValues(String pg_name, String prop_name,
	List<String> values) throws ScfException {

	try {
	    sibean_.setPropertyValues(pg_name, prop_name, values);
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    @Override
    public void createPropertyGroup(String pg_name, String pg_type)
	throws ScfException {

	try {
	    sibean_.createPropertyGroup(pg_name, pg_type);
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    @Override
    public void deletePropertyGroup(String pg_name) throws ScfException {
	try {
	    sibean_.deletePropertyGroup(pg_name);
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    @Override
    public void createProperty(String pg_name, String prop_name,
	PropertyType type) throws ScfException {

	try {
	    sibean_.createProperty(pg_name, prop_name, type);
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    @Override
    public void deleteProperty(String pg_name, String prop_name)
	throws ScfException {

	try {
	    sibean_.deleteProperty(pg_name, prop_name);
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    public List<PropertyGroup> getPropertyGroups() throws ScfException {
	try {
	    return sibean_.getpropertyGroups();
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    @Override
    public Template getPropertyTemplate(String pg_name, String prop_name,
	String locale) throws ScfException {

	try {
	    return sibean_.getPropertyTemplate(pg_name, prop_name, locale);
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    @Override
    public String getCommonName(String locale) throws ScfException {
	try {
	    return sibean_.getCommonName(locale);
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    @Override
    public String getDescription(String locale) throws ScfException {
	try {
	    return sibean_.getDescription(locale);
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    @Override
    public LogInfo getLogInfo(int max_size) throws ScfException {
	try {
	    return sibean_.getLogInfo(max_size);
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    public List<Manpage> getManpages() throws ScfException {
	try {
	    return sibean_.getmanpages();
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    public List<String> getDoclinks() throws ScfException {
	try {
	    return sibean_.getdoclinks();
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    @Override
    public void maintain(boolean immediate) throws ScfException {
	try {
	    sibean_.maintain(immediate);
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    @Override
    public void clear() throws ScfException {
	try {
	    sibean_.clear();
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    @Override
    public void degrade(boolean immediate) throws ScfException {
	try {
	    sibean_.degrade(immediate);
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    @Override
    public void restart() throws ScfException {
	try {
	    sibean_.restart();
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    @Override
    public void refresh() throws ScfException {
	try {
	    sibean_.refresh();
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    public boolean isPersistentlyEnabled() throws ScfException {
	try {
	    return sibean_.ispersistentlyEnabled();
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    public void setPersistentlyEnabled(boolean enabled) throws ScfException {
	try {
	    sibean_.setpersistentlyEnabled(enabled);
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    public boolean isTemporarilyEnabled() throws ScfException {
	try {
	    return sibean_.istemporarilyEnabled();
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    public boolean isEnabled() throws ScfException {
	try {
	    return sibean_.isenabled();
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    public boolean isInstance() throws ScfException {
	try {
	    return sibean_.isinstance();
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    public String getRestarter() throws ScfException {
	try {
	    return sibean_.getrestarter();
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    public SmfState getState() throws ScfException {
	try {
	    return sibean_.getstate();
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    public SmfState getNextState() throws ScfException {
	try {
	    return sibean_.getnextState();
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    public Date getSTime() throws ScfException {
	try {
	    return sibean_.getstime();
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    public BigInteger getContractID() throws ScfException {
	try {
	    return BigInteger.valueOf(sibean_.getcontractID());
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    public String getAuxiliaryState() throws ScfException {
	try {
	    return sibean_.getauxiliaryState();
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }

    public String getReason() throws ScfException {
	try {
	    return sibean_.getreason();
	} catch (RadObjectException e) {
	    throw new ScfException(e);
	}
    }
}
