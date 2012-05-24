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

package com.oracle.solaris.scf.common;

import java.net.URI;
import java.net.URISyntaxException;
import java.beans.ConstructorProperties;
import java.util.Map;
import java.util.EnumMap;
import javax.management.openmbean.*;

/**
 * A basic FMRI class.  Probably should be named "SmfFMRI", as
 * legacy-run services aren't an SCF concept.
 */
public class FMRI implements Comparable<FMRI>, CompositeDataView
{
	/*
	 * Static data
	 */
	public static final String SCF_SCOPE_LOCAL = "localhost";
	private static final String FORMAT =
	    "([A-Za-z][_A-Za-z0-9.-]*,)?[_A-Za-z0-9-]*";
	private static final Map<FMRIScheme, String> scheme_strings =
	    new EnumMap<FMRIScheme, String>(FMRIScheme.class);

	static {
		scheme_strings.put(FMRIScheme.FILE, "file");
		scheme_strings.put(FMRIScheme.LEGACY, "lrc");
		scheme_strings.put(FMRIScheme.SERVICE, "svc");
	}

	/*
	 * FMRI components
	 */
	private FMRIScheme scheme_;
	private String scope_ = null;
	private String service_ = null;
	private String instance_ = null;
	private String pg_ = null;
	private String property_ = null;
	private String name_ = null;

	/*
	 * Derivative information
	 */
	private FMRIType svctype_;
	private String canonicalStr_;

	/**
	 * Creates an FMRI from a URI.
	 */
	public FMRI(URI uri) throws URISyntaxException
	{
		if (!uri.isAbsolute() || uri.isOpaque())
			throw (new URISyntaxException(uri.toString(),
			    "Bad FMRI"));

		String scheme = uri.getScheme();
		scope_ = uri.getAuthority();
		if (scope_ == null || scope_.isEmpty() ||
		    scope_.equals(SCF_SCOPE_LOCAL))
			scope_ = null;
		canonicalStr_ = new URI(uri.getScheme(), scope_, uri.getPath(),
		    null, null).toString();

		if (scheme.equals("svc")) {
			scheme_ = FMRIScheme.SERVICE;
			svctype_ = FMRIType.SCOPE;

			String[] top = uri.getPath().split("/:properties/", 2);

			String[] next = top[0].split(":", 2);
			/*
			 * We can assume the path starts with a slash
			 * because we reject relative URIs above.
			 */
			service_ = next[0].substring(1);
			svctype_ = FMRIType.SERVICE;
			if (next.length == 2) {
				instance_ = next[1];
				if (!instance_.matches(FORMAT))
					throw (new URISyntaxException(
					    uri.toString(),
					    "Invalid instance: " + instance_));
				svctype_ = FMRIType.INSTANCE;
			}

			if (top.length == 2) {
				next = top[1].split("/", 2);
				pg_ = next[0];
				if (!pg_.matches(FORMAT))
					throw (new URISyntaxException(
					    uri.toString(),
					    "Invalid property group: " + pg_));
				svctype_ = FMRIType.PGROUP;
				if (next.length == 2) {
					property_ = next[1];
					if (!property_.matches(FORMAT))
						throw (new URISyntaxException(
						    uri.toString(),
						    "Invalid property: " +
						    property_));
					svctype_ = FMRIType.PROPERTY;
				}
			}
		} else if (scheme.equals("file")) {
			scheme_ = FMRIScheme.FILE;
			name_ = uri.getPath();
		} else if (scheme.equals("lrc")) {
			scheme_ = FMRIScheme.LEGACY;
			name_ = uri.getPath();
		} else {
			throw (new URISyntaxException(uri.toString(),
			    "Invalid FMRI scheme: " + scheme));
		}
	}

	/**
	 * Creates an FMRI from a string.
	 */
	public FMRI(String fmri) throws URISyntaxException
	{
		/* Work around bug 6504439 in scf_scope_to_fmri */
		this(new URI(fmri.equals("svc:") ? "svc:///" : fmri));
	}

	/**
	 * Constucts an FMRI from its attributes.  Needed for the class to be
	 * reconstructable.
	 */
	@SuppressWarnings({"fallthrough"})
	@ConstructorProperties({"scheme", "svcType", "scope", "name", "service",
	    "instance", "propertyGroup", "property"})
	public FMRI(FMRIScheme scheme, FMRIType type, String scope, String name,
	    String service, String instance, String pg, String property)
	{
		scheme_ = scheme;

		scope_ = scope;
		if (scope_ == null || scope_.isEmpty() ||
		    scope_.equals(SCF_SCOPE_LOCAL))
			scope_ = null;

		String path;
		if (scheme != FMRIScheme.SERVICE) {
			svctype_ = FMRIType.NONE;
			path = name_ = name;
		} else {
			svctype_ = type;
			name_ = null;

			path = "";
			switch (svctype_) {
			case PROPERTY:
			    property_ = property;
			    path = "/" + property + path;
			case PGROUP:
			    pg_ = pg;
			    path = "/:properties/" + pg + path;
			case INSTANCE:
			    instance_ = instance;
			    path = ":" + instance + path;
			case SERVICE:
			    service_ = service;
			    path = "/" + service + path;
			}
		}

		try {
			URI uri = new URI(scheme_strings.get(scheme), scope_,
			    path, null, null);
			canonicalStr_ = uri.toString();
		} catch (URISyntaxException ex) {
			canonicalStr_ = null;
		}
	}

	/**
	 * Returns the FMRI's type (scheme).
	 */
	public FMRIScheme getScheme()
	{
		return (scheme_);
	}

	/**
	 * Returns a svc: FMRI's type.
	 */
	public FMRIType getSvcType()
	{
		if (scheme_ != FMRIScheme.SERVICE)
			throw (new FMRIException(this, "not a service FMRI"));
		return (svctype_);
	}

	/**
	 * Returns the FMRI's scope.
	 */
	public String getScope()
	{
		return (scope_ == null ? SCF_SCOPE_LOCAL : scope_);
	}

	/**
	 * Returns the name of a legacy-run or file FMRI.
	 */
	public String getName()
	{
		if (scheme_ == FMRIScheme.SERVICE)
			throw (new FMRIException(this,
			    "not a file or legacy FMRI"));
		return (name_);
	}

	/**
	 * Throws an FMRIException from a function which may only be
	 * called on a svc: FMRI.  Takes the FMRIType required by the
	 * caller.
	 */
	private void checktype(FMRIType svctype)
	{
		String prefix = "unable to read " + svctype;
		if (scheme_ != FMRIScheme.SERVICE)
			throw (new FMRIException(this, prefix +
			    " from non-service FMRI"));
		if (svctype_.compareTo(svctype) < 0)
			throw (new FMRIException(this, prefix +
			    " from " + svctype_ + "FMRI"));
	}

	/**
	 * Returns the service component of a service FMRI.
	 */
	public String getService()
	{
		checktype(FMRIType.SERVICE);
		return (service_);
	}

	/**
	 * Returns the instance component of a service FMRI, or {@code
	 * null} if there is none.
	 */
	public String getInstance()
	{
		checktype(FMRIType.INSTANCE);
		return (instance_);
	}

	/**
	 * Returns the property group component of a service FMRI.
	 */
	public String getPropertyGroup()
	{
		checktype(FMRIType.PGROUP);
		return (pg_);
	}

	/**
	 * Returns the property component of a service FMRI.
	 */
	public String getProperty()
	{
		checktype(FMRIType.PROPERTY);
		return (property_);
	}

	public FMRI toServiceFMRI()
	{
		checktype(FMRIType.SERVICE);
		if (svctype_ == FMRIType.SERVICE)
			return this;
		return (new FMRI(scheme_, FMRIType.SERVICE, scope_, null,
		    service_, null, null, null));
	}

	public FMRI toInstanceFMRI()
	{
		checktype(FMRIType.INSTANCE);
		if (svctype_ == FMRIType.INSTANCE)
			return this;
		return (new FMRI(scheme_, FMRIType.INSTANCE, scope_, null,
		    service_, instance_, null, null));
	}

	public FMRI toInstanceFMRI(String instanceName)
	{
		checktype(FMRIType.SERVICE);
		return (new FMRI(scheme_, FMRIType.INSTANCE, scope_, null,
		    service_, instanceName, null, null));
	}


	/*
	 * CompositeDataView methods
	 */

	private static final String[] itemNames = new String[] { "scheme",
	    "svcType", "scope", "name", "service", "instance", "propertyGroup",
	    "property" };

	/*
	 * Manually convert the FMRI to its automatically-determined
	 * CompositeType.  This conversion is normally performed by the
	 * MXBean implementation, but the automatic conversion uses our
	 * accessors to inspect the object.  Performing the conversion
	 * manually permits us to circumvent the run-time checking
	 * performed by our accessors (or to put it differently, permits
	 * us to leave the run-time checking in place).
	 */
	public CompositeData toCompositeData(CompositeType ct)
	{
		Object[] itemValues = new Object[] { scheme_.name(),
		    svctype_.name(), scope_, name_, service_, instance_, pg_,
		    property_ };
		try {
			return (new CompositeDataSupport(ct, itemNames,
			    itemValues));
		} catch (OpenDataException ex) {
			throw (new RuntimeException(ex));
		}
	}

	// Comparable methods

	private static int strcmp(String a, String b)
	{
		if (a == null)
			return (b == null ? 0 : 1);
		if (b == null)
			return (-1);
		return (a.compareTo(b));
	}

	public int compareTo(FMRI f)
	{
		int result = scheme_.compareTo(f.scheme_);

		if (result == 0)
			result = strcmp(scope_, f.scope_);
		if (scheme_ != FMRIScheme.SERVICE)
			result = strcmp(name_, f.name_);
		else {
			if (result == 0)
				result = strcmp(service_, f.service_);
			if (result == 0)
				result = strcmp(instance_, f.instance_);
			if (result == 0)
				result = strcmp(pg_, f.pg_);
			if (result == 0)
				result = strcmp(property_, f.property_);
		}

		return (result);
	}

	/*
	 * Object methods
	 */

	/**
	 * Returns the FMRI as a string.
	 */
	@Override
	public String toString()
	{
		return (canonicalStr_);
	}

	@Override
	public boolean equals(Object o)
	{
		if (o == null)
			return (false);

		FMRI f;
		try {
			f = (FMRI)o;
		} catch (ClassCastException e) {
			return (false);
		}

		return (compareTo(f) == 0);
	}

	@Override
	public int hashCode()
	{
		int hash = 7;
		hash = 79 * hash +
		    (this.scope_ != null ? this.scope_.hashCode() : 0);
		hash = 79 * hash +
		    (this.service_ != null ? this.service_.hashCode() : 0);
		hash = 79 * hash +
		    (this.instance_ != null ? this.instance_.hashCode() : 0);
		hash = 79 * hash +
		    (this.pg_ != null ? this.pg_.hashCode() : 0);
		hash = 79 * hash +
		    (this.property_ != null ? this.property_.hashCode() : 0);
		hash = 79 * hash +
		    (this.name_ != null ? this.name_.hashCode() : 0);
		hash = 79 * hash +
		    (this.scheme_ != null ? this.scheme_.hashCode() : 0);
		hash = 79 * hash +
		    (this.svctype_ != null ? this.svctype_.hashCode() : 0);
		return hash;
	}
}
