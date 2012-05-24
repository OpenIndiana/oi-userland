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
 * Copyright (c) 1999, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panels.usermgr.client.swing;

import java.lang.*;
import java.io.*;
import java.util.*;

/**
 * SMC code adapted for Visual Panels
 *
 * The AttrObj class implements a generic attribute key/value set.
 * The set has a single key name and zero or more string values.
 *
 */

@SuppressWarnings("unchecked")
public class AttrObj extends Object implements Cloneable {

    // Private attributes backstopped by persistent storage
    protected Vector<String> vector = null;	// Vector of values for key
    private String key = null;		// keyword for attribute

    /**
     * Constructor takes the set key name.
     *
     * @param keyword	A key name
     *
     */
    public AttrObj(String keyword) {

	super();
	key = keyword;
	vector = new Vector<String>(10);

    }

    /**
     * Return an array of string values for the set.
     *
     * @return An array of string values
     *
     */
    public String [] get() {

	String [] attrArray = new String[vector.size()];
	vector.copyInto(attrArray);
	return (attrArray);

    }

    /**
     * Return a vector of string values for the set.
     *
     * @return A vector of string values
     *
     */
    public Vector getVector() {

	return ((Vector)vector.clone());

    }

    /**
     * Return the first string value in the set.
     *
     * @return A string value
     *
     */
    public String getString() {

	return (vector.elementAt(0));

    }

    /**
     * Return true if the set contains the specified key name.
     *
     * @param key	The key name
     * @return True if the set contains the key name
     *
     */
    public boolean contains(String key) {

	return (vector.contains(key));

    }

    /**
     * Return the key name for the set.
     *
     * @return A key name
     *
     */
    public String getKey() {

	return (key);

    }

    /**
     * Set the specified string value as the values for the set.
     * Replaces any existing values.
     *
     * @param string	A string value
     *
     */
    public void set(String string) {
	vector.removeAllElements();
	vector.addElement(string);
    }

    /**
     * Set the specified string values as the values for the set.
     * Replaces any existing values.
     *
     * @param array	An array of string values
     *
     */
    public void set(String [] array) {

	vector.removeAllElements();
	for (int i = 0; i < array.length; i++) {
	    vector.addElement(array[i]);
	}

    }

    /**
     * Set the specified int value as the values for the set.
     * Replaces any existing values.
     *
     * @param value	An integer value
     *
     */
    public void set(int value) {

	vector.removeAllElements();
	vector.addElement(Integer.toString(value));

    }

    /**
     * Set the specified string values as the values for the set.
     * Replaces any existing values.
     *
     * @param newVec	A vector of string values
     *
     */
    public void set(Vector newVec) {

	vector.removeAllElements();
	vector = (Vector) newVec.clone();

    }

    /**
     * Add the specified string value to the set.
     * Duplicates are removed.
     *
     * @param string	A string value
     *
     */
    public void add(String string) {
	if (! vector.contains(string))
	vector.addElement(string);
    }

    /**
     * Add the specified string values to the set.
     * Duplicates are removed.
     *
     * @param array	An array of string values
     *
     */
    public void add(String [] array) {

	for (int i = 0; i < array.length; i++) {
	if (! vector.contains(array[i]))
	    vector.addElement(array[i]);
	}

    }

    /**
     * Add the specified string values to the set.
     * Duplicates are removed.
     *
     * @param newVec	A vector of string values
     *
     */
    public void add(Vector newVec) {

	Enumeration v1 = newVec.elements();
	while (v1.hasMoreElements()) {
	String string = (String) v1.nextElement();
	if (! vector.contains(string))
	    vector.addElement(string);
	}

    }

    /**
     * Remove the specified string value from the set.
     *
     * @param string	A string value
     *
     */
    public void del(String string) {

	vector.removeElement(string);

    }

    /**
     * Remove the specified string values from the set.
     *
     * @param array	An array of string values
     *
     */
    public void del(String [] array) {

	for (int i = 0; i < array.length; i++) {
	vector.removeElement(array[i]);
	}

    }

    /**
     * Remove the specified string values from the set.
     *
     * @param oldVec	A vector of string values
     *
     */
    public void del(Vector oldVec) {

	Enumeration v1 = oldVec.elements();
	while (v1.hasMoreElements()) {
	String string = (String) v1.nextElement();
	if (vector.contains(string))
	    vector.removeElement(string);
	}

    }

    /**
     * The equals method checks that all attributes of this user
     * authorization attributes object equal the corresponding
     * attributes of the specified user attributes object.
     * If so, true is returned; otherwise, false is returned.
     *
     * @param	userAttr    Specified user attr object to be compared
     *
     * @return	true if the specified object is identical
     *
     */
    public boolean equals(AttrObj newAttrObj) {

	String s1, s2;

	// Number and instances of attributes must be the same
	if (vector.size() != newAttrObj.vector.size())
	    return (false);
	Enumeration v1 = vector.elements();
	Enumeration v2 = newAttrObj.vector.elements();

	while (v1.hasMoreElements()) {
	    s1 = (String) v1.nextElement();
	    s2 = (String) v2.nextElement();
	    if (! s1.equals(s2))
		return (false);
	}
	// Everything matches, must be equal
	return (true);

    }

    /**
     * Display the contents of the set to sysout for debugging purposes.
     *
     */
    public void debugPrint() {

	String strlist = new String("");
	String sep = "	";
	if (vector != null) {
	    Enumeration attrs = vector.elements();
	    while (attrs.hasMoreElements()) {
		strlist = strlist + sep + (String)attrs.nextElement();
		sep = ", ";
	    }
	}
    }

}
