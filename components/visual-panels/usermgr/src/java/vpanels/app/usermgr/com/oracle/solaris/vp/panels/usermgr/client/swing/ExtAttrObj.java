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
 * The ExtAttrObj class is the base class for all RBAC attribute objects
 * stored in the RBAC "_attr" table data stores in a name service.
 * It contains convenience methods for manipulating key/value sets;
 * a comma separated set of string values with a specific keyword.
 * All key/value sets are maintained in a hash table in this superclass.
 *
 */


public class ExtAttrObj extends Object implements Cloneable {

    // Private attributes backstopped by persistent storage

    public Hashtable<String, AttrObj> attrSet;	    // Key-Value Attributes

    /**
     *	Null constructor creates an empty has table of key/values.
     *
     */
    public ExtAttrObj() {

	attrSet = new Hashtable<String, AttrObj>();

    }

    /**
     * Return the values for a specified key name.
     *
     * @param A key name
     *
     * @return A vector of string values
     *
     */
    public Vector getAttribute(String keyName) {

        if (!attrSet.containsKey(keyName)) {
	    return (null);
        } else {
            AttrObj attr = locate(keyName);
            return (attr.getVector());
        }

    }

    /**
     * Set the value for a specified key name.  Any existing values
     * for that key are replaced.
     *
     * @param A key name
     * @param A string value
     *
     */
    public void setAttribute(String keyName, String value) {

	AttrObj attr = locate(keyName);
	attr.set(value);

    }

    /**
     * Set one or more values for a specified key name.
     * Any existing values for that key are replaced.
     *
     * @param A key name
     * @param A vector of string values
     *
     */
    public void setAttribute(String keyName, Vector values) {

	AttrObj attr = locate(keyName);
	attr.set(values);

    }

    /**
     * Return an array of string values for a specified key name.
     *
     * @param A key name
     *
     * @return An array of string values
     *
     */
    public String [] getAttributeArray(String keyName) {

        if (! attrSet.containsKey(keyName)) {
	    return (null);
        } else {
	    AttrObj attr = locate(keyName);
	    Vector v = attr.getVector();
	    String [] star = new String[v.size()];
	    v.copyInto(star);
	    return (star);
        }

    }

    /**
     * Set one or more values for a specified key name.
     * Any existing values for that key are replaced.
     *
     * @param A key name
     * @param An array of string values
     *
     */
    public void setAttribute(String keyName, String [] values) {

	AttrObj attr = locate(keyName);
	attr.set(values);

    }

    /**
     * Add a string value to the set of values for a key name.
     *
     * @param A key name
     * @param A string value
     *
     */
    public void addAttribute(String keyName, String value) {

        AttrObj attr = locate(keyName);
        attr.add(value);

    }

    /**
     * Add one or more string values to the set of values for a key name.
     *
     * @param A key name
     * @param A vector of string values
     *
     */
    public void addAttribute(String keyName, Vector values) {

	AttrObj attr = locate(keyName);
	attr.add(values);

    }

    /**
     * Add one or more string values to the set of values for a key name.
     *
     * @param A key name
     * @param An array of string values
     *
     */
    public void addAttribute(String keyName, String [] values) {

	AttrObj attr = locate(keyName);
	attr.add(values);

    }

    /**
     * Remove a string value from the set of values for a key name.
     *
     * @param A key name
     * @param A string value
     *
     */
    public void delAttribute(String keyName, String value) {

	AttrObj attr = locate(keyName);
	attr.del(value);

    }

    /**
     * Remove one or more string values from the set of values
     * for a key name.
     *
     * @param A key name
     * @param A vector of string values
     *
     */
    public void delAttribute(String keyName, Vector values) {

	AttrObj attr = locate(keyName);
	attr.del(values);

    }

    /**
     * Remove one or more string values from the set of values
     * for a key name.
     *
     * @param A key name
     * @param An array of string values
     *
     */
    public void delAttribute(String keyName, String [] values) {

	AttrObj attr = locate(keyName);
	attr.del(values);

    }
    /**
     * Remove a key name and all its values.
     *
     * @param A key name
     *
     */
    public void clearAttribute(String keyName) {

	// Because KeyValue will do a merge, cannot remove the
	// key/value from the hash table.  Rather, set its value
	// to empty.
	AttrObj attr = locate(keyName);
	attr.set("");

    }

    /**
     * Remove all key name and all their values; that is,
     * reset the key/values attributes to a null set.
     *
     */
    public void clearAttributes() {

	// Because KeyValue will do a merge, cannot remove the
	// key/values from the hash table.  Rather, set the values
	// for all keys to empty.
	Enumeration values = attrSet.elements();
	while (values.hasMoreElements()) {
	    AttrObj attr = (AttrObj) values.nextElement();
	    attr.set("");
	}

    }

    /**
     * Update the key/value attributes from this object into
     * another attribute object (clone the attributes).
     *
     * @param An attribute object
     *
     */
    public void clone(ExtAttrObj newExtAttrObj) {

	Enumeration values = attrSet.elements();
	while (values.hasMoreElements()) {
	    AttrObj attrObj = (AttrObj) values.nextElement();
	    String key = attrObj.getKey();
	    AttrObj newAttrObj = newExtAttrObj.locate(key);
	    newAttrObj.set((attrObj.getVector()));
	}

    }

    /**
     * Find the attributes for a key name.  If not found, create
     * a new key/value attribute with null values.
     *
     * @param A key name
     *
     */
    public AttrObj locate(String key) {

	AttrObj attrObj;
	if (attrSet.containsKey(key)) {
	    attrObj = attrSet.get(key);
	} else {
	    attrObj = new AttrObj(key);
	    attrSet.put(key, attrObj);
	}
	return attrObj;

    }

    /**
     * The equals method checks that all attributes of this user
     * authorization attributes object equal the corresponding
     * attributes of the specified user attributes object.
     * If so, true is returned; otherwise, false is returned.
     *
     * @param	extAttr Specified user attr object to be compared
     *
     * @return	true if the specified object is identical
     *
     */
    public boolean equals(ExtAttrObj extAttr) {

	String [] s2;
	String ts;
	int i, j, k;

	if (! (attrSet.size() == extAttr.attrSet.size()))
	    return (false);

	Enumeration values = attrSet.elements();
	while (values.hasMoreElements()) {
	    AttrObj attrObj = (AttrObj) values.nextElement();
	    String key = attrObj.getKey();
	    if (! (extAttr.attrSet.containsKey(key)))
		return (false);

	    AttrObj newAttrObj = extAttr.locate(key);

	    if (! (attrObj.equals(newAttrObj)))
		return (false);
	}

	// Everything matches, must be equal
	return (true);

    }

    /**
     * Display the contents of the key/values of this attribute
     * object to sysout for debugging purposes.
     *
     */
    public void debugPrint() {

	Enumeration values = attrSet.elements();
	while (values.hasMoreElements()) {
	    AttrObj attrObj = (AttrObj) values.nextElement();
	    attrObj.debugPrint();
	}
    }

}
