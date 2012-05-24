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

import java.util.*;
import com.oracle.solaris.scf.common.*;
import com.oracle.solaris.vp.panel.common.api.smf_old.*;
import com.oracle.solaris.vp.util.misc.converter.*;
import com.oracle.solaris.vp.util.misc.property.BasicMutableProperty;

/**
 * The {@code BasicSmfMutableProperty} class is a {@link SmfMutableProperty} for
 * a standard SMF property within a property group.
 */
public abstract class BasicSmfMutableProperty<T>
    extends BasicMutableProperty<List<T>>
    implements SmfMutableProperty<List<T>> {

    //
    // Inner classes
    //

    private class MutablePropertyConverter
	implements DualConverter<String, List<T>> {

	//
	// Instance data
	//

	private StringArrayStringConverter sConverter =
	    new StringArrayStringConverter();

	//
	// Converter methods
	//

	@Override
	public List<T> convert(String s) {
	    String[] array = sConverter.convert(s);
	    List<T> list = new ArrayList<T>(array.length);

	    for (int i = 0; i < array.length; i++) {
		T t = converter.convert(array[i]);
		list.add(t);
	    }

	    return list;
	}

	//
	// DualConverter methods
	//

	@Override
	public String revert(List<T> t) {
	    String[] array = new String[t.size()];
	    for (int i = 0; i < array.length; i++) {
		array[i] = converter.revert(t.get(i));
	    }
	    return sConverter.revert(array);
	}
    }

    //
    // Instance data
    //

    private DualConverter<String, List<T>> pConverter =
	new MutablePropertyConverter();

    private DualConverter<String, T> converter;
    private PropertyType type;
    private SmfPropertyInfo info;
    private boolean readable_ = true;

    //
    // Constructors
    //

    /**
     * Constructs a {@code BasicSmfMutableProperty}.
     * </p>
     * Note: if {@link SmfPropertyInfo#getPropertyGroupName
     * info.getPropertyName} returns {@code null}, all read/write operations of
     * this class will use {@code name} as the SMF property name.
     *
     * @param	    name
     *		    the name of the property (may differ from the name of this
     *		    property in the SMF repository)
     *
     * @param	    converter
     *		    used to convert property elements to {@code String}s, to be
     *		    stored in the SMF repository
     *
     * @param	    type
     *		    the type of the property
     *
     * @param	    info
     *		    source of the service, property group name, and property
     *		    name
     */
    public BasicSmfMutableProperty(String name,
	DualConverter<String, T> converter, PropertyType type,
	SmfPropertyInfo info) {

	super(name);

	setPropertyConverter(converter);
	this.type = type;
	this.info = info;
    }

    //
    // SmfMutableProperty methods
    //

    @Override
    public DualConverter<String, List<T>> getConverter() {
	return pConverter;
    }

    @Override
    public List<T> getRepoValue() throws ScfException {
	List<T> values = null;
	List<String> sValues;

	try {
	    readable_ = true;
	    sValues = getValuesFromRepository();
	} catch (ScfException e) {
	    // Does property or property group not yet exist?
	    if (e.getError() == SmfErrorCode.NOT_FOUND) {
		sValues = Collections.emptyList();
	    } else if (e.getError() == SmfErrorCode.PERMISSION_DENIED) {
		readable_ = false;
		return values;
	    } else {
		throw e;
	    }
	}

	if (sValues != null) {
	    int n = sValues.size();

	    values = new ArrayList<T>(n);
	    for (int i = 0; i < n; i++) {
		String s = sValues.get(i);
		values.add(converter.convert(s));
	    }
	}

	return values;
    }

    @Override
    public void saveToRepo() throws ScfException {
	List<T> value = getValue();
	setRepoValue(value);
	save();
    }

    @Override
    public void setRepoValue(List<T> values) throws ScfException {
	List<String> array = new ArrayList<String>(values.size());
	for (T v : values)
	    array.add(converter.revert(v));

	ServiceMXBean service = info.getService();
	String group = info.getPropertyGroupName();
	String name = getSmfPropertyName();

	try {
		service.setPropertyValues(group, name, array);
	} catch (ScfException e) {
		// Does property not yet exist?
	    if (e.getError() == SmfErrorCode.NOT_FOUND) {
		    try {
			service.createProperty(group, name, type);
		} catch (ScfException e2) {
			// Does property group not yet exist?
		    if (e2.getError() == SmfErrorCode.NOT_FOUND) {
			    service.createPropertyGroup(group,
				ScfConstants.SCF_APPLICATION_PG);
		    } else {
			throw e2;
		    }

		    // Retry, now that property group is created
		    service.createProperty(group, name, type);
		}

		// Retry, now that property is created
		service.setPropertyValues(group, name, array);
	    } else {
		throw e;
	    }
	}

	if (info.getService().isInstance())
	    service.refresh();
    }

    @Override
    public void updateFromRepo(boolean force) throws ScfException {
	update(getRepoValue(), force);
    }

    //
    // BasicSmfMutableProperty methods
    //

    public abstract T getDefaultValue();

    public T getFirstRepoValue() throws ScfException {
	List<T> values = getRepoValue();
	if (values != null && values.size() != 0) {
	    return values.get(0);
	}
	return null;
    }

    public T getFirstSavedValue() {
	List<T> values = getSavedValue();
	if (values != null && values.size() != 0) {
	    return values.get(0);
	}
	return null;
    }

    public T getFirstValue() {
	List<T> values = getValue();
	if (values != null && values.size() != 0) {
	    return values.get(0);
	}
	return null;
    }

    public DualConverter<String, T> getPropertyConverter() {
	return converter;
    }

    protected String getSmfPropertyName() throws ScfException {
	String name = info.getPropertyName();
	if (name == null) {
	    name = getPropertyName();
	}
	return name;
    }

    public PropertyType getType() {
	return type;
    }

    /**
     * Determine whether property currently exists in SMF repository.
     */
    public boolean getExistsInRepo() throws ScfException {
	try {
	    getValuesFromRepository();
	    return true;
	} catch (ScfException e) {
	    // Does property or property group not yet exist?
	    if (e.getError() == SmfErrorCode.NOT_FOUND)
		return false;
	    else
		throw e;
	}
    }

    /**
     * Retrieves the property values from the SMF repository.
     */
    protected List<String> getValuesFromRepository() throws ScfException {
	List<String> values = info.getService().isInstance() ?
	    info.getService().getSnapshotPropertyValues(
	    ScfConstants.SCF_RUNNING, info.getPropertyGroupName(),
	    getSmfPropertyName()) :
	    info.getService().getPropertyValues(info.getPropertyGroupName(),
	    getSmfPropertyName());
	return values;
    }

    public void removeFromRepo() throws ScfException {
	ServiceMXBean service = info.getService();
	String group = info.getPropertyGroupName();
	String name = getSmfPropertyName();

	service.deleteProperty(group, name);
	if (info.getService().isInstance())
	    service.refresh();
    }

    public void setPropertyConverter(DualConverter<String, T> converter) {
	this.converter = converter;
    }

    public void setFirstRepoValue(T value) throws ScfException {
	List<T> list = toList(value);
	setRepoValue(list);
    }

    public void setFirstSavedValue(T value) {
	List<T> list = toList(value);
	setSavedValue(list);
    }

    public void setFirstValue(T value) {
	List<T> list = toList(value);
	setValue(list);
    }

    public void setType(PropertyType type) {
	this.type = type;
    }

    public void updateFirst(T value, boolean force) {
	List<T> list = toList(value);
	update(list, force);
    }

    public boolean isReadable() {
	return readable_;
    }

    //
    // Private methods
    //

    private List<T> toList(T value) {
	List<T> list = null;
	if (value != null) {
	    list = new ArrayList<T>(1);
	    list.add(value);
	}
	return list;
    }
}
