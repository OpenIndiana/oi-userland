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

import java.io.PrintWriter;
import java.util.*;
import javax.swing.event.*;
import com.oracle.solaris.vp.util.swing.event.ChangeListeners;

public class ChangeableAggregator implements Changeable, ChangeListener {
    //
    // Static data
    //

    private static boolean debug;

    //
    // Instance data
    //

    private String name;
    private final List<Changeable> changeables = new ArrayList<Changeable>();

    private List<Changeable> roChangeables =
	Collections.unmodifiableList(changeables);

    private ChangeListeners listeners = new ChangeListeners();
    private boolean changed;
    private ChangeEvent event = new ChangeEvent(this);

    //
    // Constructors
    //

    /**
     * Constructs a {@code ChangeableAggregator} with a {@code null} name.
     */
    public ChangeableAggregator() {
    }

    /**
     * Constructs a {@code ChangeableAggregator} with the given name.
     *
     * @see	    #setName
     */
    public ChangeableAggregator(String name) {
	this();
	setName(name);
    }

    //
    // Changeable methods
    //

    @Override
    public void addChangeListener(ChangeListener listener) {
	listeners.add(listener);
    }

    @Override
    public boolean isChanged() {
	return changed;
    }

    @Override
    public boolean removeChangeListener(ChangeListener listener) {
	return listeners.remove(listener);
    }

    @Override
    public void reset() {
	// Avoid thread deadlock by iterating over a copy of changeables, rather
	// than synchronzing on it
	List<Changeable> changeables = new ArrayList<Changeable>(
	    this.changeables);

	for (Changeable changeable : changeables) {
	    changeable.reset();
	}
    }

    @Override
    public void save() {
	// Avoid thread deadlock by iterating over a copy of changeables, rather
	// than synchronzing on it
	List<Changeable> changeables = new ArrayList<Changeable>(
	    this.changeables);

	for (Changeable changeable : changeables) {
	    changeable.save();
	}
    }

    //
    // ChangeListener methods
    //

    @Override
    public void stateChanged(ChangeEvent e) {
	boolean changed = false;
	synchronized (changeables) {
	    for (Changeable changeable : changeables) {
		if (changeable.isChanged()) {
		    changed = true;
		    break;
		}
	    }
	    setChanged(changed);
	}
    }

    //
    // ChangeableAggregator methods
    //

    public void addChangeables(Changeable... changeables) {
	synchronized (this.changeables) {
	    for (Changeable changeable : changeables) {
		this.changeables.add(changeable);
		changeable.addChangeListener(this);
	    }

	    // Initialize
	    stateChanged(null);
	}
    }

    public void clearChangeables() {
	synchronized (changeables) {
	    for (int i = changeables.size() - 1; i >= 0; i--) {
		removeChangeable(changeables.get(i));
	    }
	}
    }

    /**
     * Returns an unmodifiable wrapper around this {@code
     * ChangeableAggregator}'s list of {@link Changeable}s.
     */
    public List<Changeable> getChangeables() {
	synchronized (changeables) {
	    return roChangeables;
	}
    }

    /**
     * Gets this {@code ChangeableAggregator}'s name.  This field is
     * nonessential and may be used for debugging purposes.
     */
    public String getName() {
	return name;
    }

    public boolean removeChangeable(Changeable changeable) {
	synchronized (changeables) {
	    if (changeables.remove(changeable)) {
		changeable.removeChangeListener(this);

		// Re-initialize
		stateChanged(null);

		return true;
	    }
	}

	return false;
    }

    /**
     * Sets this {@code ChangeableAggregator}'s name.  This field is
     * nonessential and may be used for debugging purposes.
     */
    public void setName(String name) {
	this.name = name;
    }

    //
    // Private methods
    //

    private void setChanged(boolean changed) {
	if (this.changed != changed) {
	    this.changed = changed;
	    listeners.stateChanged(event);
	}
    }

    //
    // Static methods
    //

    /**
     * Enable debugging.  Subsequent calls to {@link DebugUtil#dump} with a
     * {@code ChangeableAggregator} as an argument will provide more meaningful
     * data.
     */
    public static void debug() {
	if (!debug) {
	    debug = true;
	    DebugUtil.DumpHandler handler = new DebugUtil.DumpHandler() {
		@Override
		public boolean dump(String prefix, Object object, int indent,
		    PrintWriter out) {

		    if (object instanceof ChangeableAggregator) {
			ChangeableAggregator aggregator =
			    (ChangeableAggregator)object;

			String name = aggregator.getName();
			boolean changed = aggregator.isChanged();

			out.printf("%s%s%s %s (%s)\n",
			    DebugUtil.indent(indent), prefix,
			    DebugUtil.toBaseName(aggregator),
			    name == null ? "(unnamed)" : ("\"" + name + "\""),
			    changed ? "changed" : "not changed");

			indent++;

			if (changed) {
			    for (Changeable changeable :
				aggregator.getChangeables()) {

				if (changeable.isChanged()) {
				    DebugUtil.dump("", changeable, indent, out);
				    break;
				}
			    }
			}

			return true;
		    }

		    return false;
		}
	    };
	    DebugUtil.handlers.add(handler);
	}
    }
}
