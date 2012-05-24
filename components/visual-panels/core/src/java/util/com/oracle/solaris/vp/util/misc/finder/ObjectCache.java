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

package com.oracle.solaris.vp.util.misc.finder;

import java.net.URL;
import java.util.*;
import javax.swing.*;

public class ObjectCache<K, V> extends Thread {
    //
    // Inner classes
    //

    protected static class Element<V> {
	public long date;
	public V value;
    }

    //
    // Instance data
    //

    private Map<K, Element<V>> map;

    // 30 seconds
    private long cleanInterval = 30000;

    // 5 minutes
    private long ageThreshold = 300000;

    //
    // Constructors
    //

    public ObjectCache(boolean start) {
	map = createUnderlyingMap();

	setDaemon(true);
	if (start) {
	    start();
	}
    }

    public ObjectCache() {
	this(true);
    }

    //
    // Runnable methods
    //

    @Override
    public void run() {
	while (!Thread.currentThread().interrupted()) {
	    try {
		Thread.sleep(getCleanInterval());
		synchronized (this) {
		    long oldDate = System.currentTimeMillis() -
			getAgeThreshold();

		    for (Iterator<K> i = map.keySet().iterator(); i.hasNext();)
		    {
			K key = i.next();
			Element<V> element = map.get(key);
			if (element.date < oldDate) {
			    i.remove();
			}
		    }
		}
	    } catch (InterruptedException e) {
		interrupt();
	    }
	}
    }

    //
    // ObjectCache methods
    //

    public synchronized void clear() {
	map.clear();
    }

    public synchronized boolean containsKey(K key) {
	return map.containsKey(key);
    }

    protected Map<K, Element<V>> createUnderlyingMap() {
	return new HashMap<K, Element<V>>();
    }

    public synchronized V get(K key) {
	V value = null;
	Element<V> element = map.get(key);
	if (element != null)  {
	    element.date = System.currentTimeMillis();
	    value = element.value;
	}
	return value;
    }

    /**
     * Gets the threshold to determine whether an object in the cache is old and
     * can be removed.  Objects in the cache that have not been retrieved within
     * this amount will be removed by the cleaner thread.  The default is 300000
     * (5 minutes).
     */
    public long getAgeThreshold() {
	return ageThreshold;
    }

    /**
     * Gets the number of milliseconds that the cache cleaning thread should
     * sleep between cleanings.  The default is 3000 (30 seconds).
     */
    public long getCleanInterval() {
	return cleanInterval;
    }

    public synchronized boolean isEmpty() {
	return map.isEmpty();
    }

    public synchronized V put(K key, V value) {
	Element<V> element = new Element<V>();
	element.date = System.currentTimeMillis();
	element.value = value;
	map.put(key, element);
	return value;
    }

    public synchronized V remove(K key) {
	Element<V> element = map.remove(key);
	return element == null ? null : element.value;
    }

    /**
     * Gets the threshold to determine whether an object in the cache is old and
     * can be removed.  Objects in the cache that have not been retrieved within
     * this amount will be removed by the cleaner thread.
     */
    public void setAgeThreshold(long ageThreshold) {
	this.ageThreshold = ageThreshold;
    }

    /**
     * Gets the number of milliseconds that the cache cleaning thread should
     * sleep between cleanings.
     */
    public void setCleanInterval(long cleanInterval) {
	this.cleanInterval = cleanInterval;
    }

    public synchronized int size() {
	return map.size();
    }
}
