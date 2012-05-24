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

package com.oracle.solaris.vp.util.misc;

import java.awt.*;
import java.util.*;
import java.util.List;
import com.oracle.solaris.vp.util.misc.converter.*;

@SuppressWarnings({"serial"})
public class TypedPropertiesWrapper {
    //
    // Instance data
    //

    private List<Properties> pList = new ArrayList<Properties>();

    //
    // Constructors
    //

    public TypedPropertiesWrapper(Properties... properties) {
	for (Properties p : properties) {
	    pList.add(p);
	}
    }

    //
    // TypedPropertiesWrapper methods
    //

    /**
     * Retrieves the first property of the given key from the given list and
     * converts it to a {@code boolean}.
     *
     * @param	    key
     *		    the property key
     *
     * @return	    a {@code boolean}
     *
     * @exception   NoSuchElementException
     *		    if none of the given {@code Properties} objects contains a
     *		    property of the given key
     */
    public boolean getBoolean(String key) {
	return getValue(key, BooleanStringConverter.INSTANCE);
    }

    /**
     * Retrieves the first property of the given key from the given list and
     * converts it to a {@code byte}.
     *
     * @param	    key
     *		    the property key
     *
     * @return	    a {@code byte}
     *
     * @exception   NoSuchElementException
     *		    if none of the given {@code Properties} objects contains a
     *		    property of the given key
     *
     * @exception   NumberFormatException
     *		    thrown by {@link ByteStringConverter#convert}.
     */
    public byte getByte(String key) {
	return getValue(key, ByteStringConverter.INSTANCE);
    }

    /**
     * Retrieves the first property of the given key from the given list and
     * converts it to a {@code char}.
     *
     * @param	    key
     *		    the property key
     *
     * @return	    a {@code char}
     *
     * @exception   NoSuchElementException
     *		    if none of the given {@code Properties} objects contains a
     *		    property of the given key
     *
     * @exception   IndexOutOfBoundsException
     *		    thrown by {@link CharacterStringConverter#convert}.
     *
     * @exception   NumberFormatException
     *		    thrown by {@link CharacterStringConverter#convert}.
     */
    public char getChar(String key) {
	return getValue(key, CharacterStringConverter.INSTANCE);
    }

    /**
     * Retrieves the first property of the given key from the given list and
     * converts it to a {@code Color}.
     *
     * @param	    key
     *		    the property key
     *
     * @return	    a {@code Color}
     *
     * @exception   NoSuchElementException
     *		    if none of the given {@code Properties} objects contains a
     *		    property of the given key
     *
     * @exception   IllegalArgumentException
     *		    thrown by {@link ColorStringConverter#convert}.
     */
    public Color getColor(String key) {
	return getValue(key, ColorStringConverter.INSTANCE);
    }

    /**
     * Retrieves the first property of the given key from the given list and
     * converts it to a {@code Dimension}.
     *
     * @param	    key
     *		    the property key
     *
     * @return	    a {@code Dimension}
     *
     * @exception   NoSuchElementException
     *		    if none of the given {@code Properties} objects contains a
     *		    property of the given key
     *
     * @exception   IllegalArgumentException
     *		    thrown by {@link DimensionStringConverter#convert}.
     */
    public Dimension getDimension(String key) {
	return getValue(key, DimensionStringConverter.INSTANCE);
    }

    /**
     * Retrieves the first property of the given key from the given list and
     * converts it to a {@code double}.
     *
     * @param	    key
     *		    the property key
     *
     * @return	    a {@code double}
     *
     * @exception   NoSuchElementException
     *		    if none of the given {@code Properties} objects contains a
     *		    property of the given key
     *
     * @exception   NumberFormatException
     *		    thrown by {@link DoubleStringConverter#convert}.
     */
    public double getDouble(String key) {
	return getValue(key, DoubleStringConverter.INSTANCE);
    }

    /**
     * Retrieves the first property of the given key from the given list and
     * converts it to a {@code float}.
     *
     * @param	    key
     *		    the property key
     *
     * @return	    a {@code float}
     *
     * @exception   NoSuchElementException
     *		    if none of the given {@code Properties} objects contains a
     *		    property of the given key
     *
     * @exception   NumberFormatException
     *		    thrown by {@link FloatStringConverter#convert}.
     */
    public float getFloat(String key) {
	return getValue(key, FloatStringConverter.INSTANCE);
    }

    /**
     * Retrieves the first property of the given key from the given list and
     * converts it to a {@code int}.
     *
     * @param	    key
     *		    the property key
     *
     * @return	    a {@code int}
     *
     * @exception   NoSuchElementException
     *		    if none of the given {@code Properties} objects contains a
     *		    property of the given key
     *
     * @exception   NumberFormatException
     *		    thrown by {@link IntegerStringConverter#convert}.
     */
    public int getInt(String key) {
	return getValue(key, IntegerStringConverter.INSTANCE);
    }

    /**
     * Retrieves the first property of the given key from the given list and
     * converts it to a {@code long}.
     *
     * @param	    key
     *		    the property key
     *
     * @return	    a {@code long}
     *
     * @exception   NoSuchElementException
     *		    if none of the given {@code Properties} objects contains a
     *		    property of the given key
     *
     * @exception   NumberFormatException
     *		    thrown by {@link LongStringConverter#convert}.
     */
    public long getLong(String key) {
	return getValue(key, LongStringConverter.INSTANCE);
    }

    /**
     * Gets the top-most {@code Properties} in the list.
     */
    public Properties getProperties() {
	return pList.get(pList.size() - 1);
    }

    /**
     * Gets the list of {@code Properties}, which are searched in <b>reverse</b>
     * order by the various <i>getXXX</i> methods.  Access to this list is not
     * thread safe; users are responsible for synchronization if it is required.
     */
    public List<Properties> getPropertiesList() {
	return pList;
    }

    /**
     * Retrieves the first property of the given key from the given list and
     * converts it to a {@code short}.
     *
     * @param	    key
     *		    the property key
     *
     * @return	    a {@code short}
     *
     * @exception   NoSuchElementException
     *		    if none of the given {@code Properties} objects contains a
     *		    property of the given key
     *
     * @exception   NumberFormatException
     *		    thrown by {@link ShortStringConverter#convert}.
     */
    public short getShort(String key) {
	return getValue(key, ShortStringConverter.INSTANCE);
    }

    /**
     * Sets the given property in the top-most {@code Properties} in the list.
     *
     * @param	    key
     *		    the property key
     *
     * @param	    value
     *		    the property value
     *
     * @exception   NullPointerException
     *		    if {@code key} is {@code null}
     *
     * @exception   IndexOutOfBoundsException
     *		    if the {@code Properties} list is empty
     */
    public void setBoolean(String key, boolean value) {
	setValue(key, value, BooleanStringConverter.INSTANCE);
    }

    /**
     * Sets the given property in the top-most {@code Properties} in the list.
     *
     * @param	    key
     *		    the property key
     *
     * @param	    value
     *		    the property value
     *
     * @exception   NullPointerException
     *		    if {@code key} is {@code null}
     *
     * @exception   IndexOutOfBoundsException
     *		    if the {@code Properties} list is empty
     */
    public void setByte(String key, byte value) {
	setValue(key, value, ByteStringConverter.INSTANCE);
    }

    /**
     * Sets the given property in the top-most {@code Properties} in the list.
     *
     * @param	    key
     *		    the property key
     *
     * @param	    value
     *		    the property value
     *
     * @exception   NullPointerException
     *		    if {@code key} is {@code null}
     *
     * @exception   IndexOutOfBoundsException
     *		    if the {@code Properties} list is empty
     */
    public void setChar(String key, char value) {
	setValue(key, value, CharacterStringConverter.INSTANCE);
    }

    /**
     * Sets the given property in the top-most {@code Properties} in the list.
     *
     * @param	    key
     *		    the property key
     *
     * @param	    value
     *		    the property value
     *
     * @exception   NullPointerException
     *		    if {@code key} or {@code value} is {@code null}
     *
     * @exception   IndexOutOfBoundsException
     *		    if the {@code Properties} list is empty
     */
    public void setColor(String key, Color value) {
	setValue(key, value, ColorStringConverter.INSTANCE);
    }

    /**
     * Sets the given property in the top-most {@code Properties} in the list.
     *
     * @param	    key
     *		    the property key
     *
     * @param	    value
     *		    the property value
     *
     * @exception   NullPointerException
     *		    if {@code key} or {@code value} is {@code null}
     *
     * @exception   IndexOutOfBoundsException
     *		    if the {@code Properties} list is empty
     */
    public void setDimension(String key, Dimension value) {
	setValue(key, value, DimensionStringConverter.INSTANCE);
    }

    /**
     * Sets the given property in the top-most {@code Properties} in the list.
     *
     * @param	    key
     *		    the property key
     *
     * @param	    value
     *		    the property value
     *
     * @exception   NullPointerException
     *		    if {@code key} is {@code null}
     *
     * @exception   IndexOutOfBoundsException
     *		    if the {@code Properties} list is empty
     */
    public void setDouble(String key, double value) {
	setValue(key, value, DoubleStringConverter.INSTANCE);
    }

    /**
     * Sets the given property in the top-most {@code Properties} in the list.
     *
     * @param	    key
     *		    the property key
     *
     * @param	    value
     *		    the property value
     *
     * @exception   NullPointerException
     *		    if {@code key} is {@code null}
     *
     * @exception   IndexOutOfBoundsException
     *		    if the {@code Properties} list is empty
     */
    public void setFloat(String key, float value) {
	setValue(key, value, FloatStringConverter.INSTANCE);
    }

    /**
     * Sets the given property in the top-most {@code Properties} in the list.
     *
     * @param	    key
     *		    the property key
     *
     * @param	    value
     *		    the property value
     *
     * @exception   NullPointerException
     *		    if {@code key} is {@code null}
     *
     * @exception   IndexOutOfBoundsException
     *		    if the {@code Properties} list is empty
     */
    public void setInt(String key, int value) {
	setValue(key, value, IntegerStringConverter.INSTANCE);
    }

    /**
     * Sets the given property in the top-most {@code Properties} in the list.
     *
     * @param	    key
     *		    the property key
     *
     * @param	    value
     *		    the property value
     *
     * @exception   NullPointerException
     *		    if {@code key} is {@code null}
     *
     * @exception   IndexOutOfBoundsException
     *		    if the {@code Properties} list is empty
     */
    public void setLong(String key, long value) {
	setValue(key, value, LongStringConverter.INSTANCE);
    }

    /**
     * Sets the given property in the top-most {@code Properties} in the list.
     *
     * @param	    key
     *		    the property key
     *
     * @param	    value
     *		    the property value
     *
     * @exception   NullPointerException
     *		    if {@code key} is {@code null}
     *
     * @exception   IndexOutOfBoundsException
     *		    if the {@code Properties} list is empty
     */
    public void setShort(String key, short value) {
	setValue(key, value, ShortStringConverter.INSTANCE);
    }

    //
    // Private methods
    //

    private <T> T getValue(String key, StringConverter<T> converter) {
	for (int i = pList.size() - 1; i >= 0; i--) {
	    Properties p = pList.get(i);
	    if (p != null) {
		String sValue = p.getProperty(key);
		if (sValue != null) {
		    return converter.convert(sValue);
		}
	    }
	}
	throw new NoSuchElementException(key);
    }

    private <T> void setValue(String key, T value,
	StringConverter<T> converter) {

	String sValue = converter.revert(value);
	getProperties().put(key, sValue);
    }
}
