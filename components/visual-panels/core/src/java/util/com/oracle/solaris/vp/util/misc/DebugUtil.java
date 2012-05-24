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
import java.awt.event.*;
import java.beans.*;
import java.io.PrintWriter;
import java.util.*;
import java.util.List;

public class DebugUtil {
    //
    // Inner classes
    //

    public static interface ComponentHandler {
	void handle(Component comp);
    }

    public static interface DumpHandler {
	/**
	 * Dumps some text representation of the given object to the given
	 * {@code PrintWriter}.
	 *
	 * @param	object
	 *		the object to dump
	 *
	 * @param	indent
	 *		the indent to use when writing to the given {@code
	 *		PrintWriter}
	 *
	 * @param	title
	 *		the String prefix to prepend to the output
	 *
	 * @param	out
	 *		the {@code PrintWriter} to which to write
	 *
	 * @return	{@code true} if this {@code DumpHandler} successfully
	 *		handled the given object, {@code false} otherwise
	 */
	boolean dump(String title, Object object, int indent, PrintWriter out);
    }

    //
    // Static data
    //

    public static final DumpHandler defaultHandler =
	new DumpHandler() {
	    @Override
	    public boolean dump(String title, Object object, int indent,
		PrintWriter out) {

		out.printf("%s%s%s\n", indent(indent), title, object);
		return true;
	    }
	};

    public static final DumpHandler collectionHandler =
	new DumpHandler() {
	    @Override
	    public boolean dump(String title, Object object, int indent,
		PrintWriter out) {

		if (object instanceof Collection) {
		    Collection collection = (Collection)object;
		    out.printf("%s%s%s (%d elements)\n", indent(indent),
			title, toBaseName(object), collection.size());

		    indent++;

		    int i = 0;
		    for (Object value : collection) {
			String subPrefix = String.format("%d. ", i++);
			DebugUtil.dump(subPrefix, value, indent, out);
		    }
		    return true;
		}

		return false;
	    }
	};

    public static final DumpHandler mapHandler =
	new DumpHandler() {
	    @Override
	    public boolean dump(String title, Object object, int indent,
		PrintWriter out) {

		if (object instanceof Map) {
		    Map map = (Map)object;
		    out.printf("%s%s%s (%d elements)\n", indent(indent),
			title, toBaseName(object), map.size());

		    indent++;

		    int i = 0;
		    for (Object key : map.keySet()) {
			Object value = map.get(key);
			String subPrefix = String.format("%d. %s = ", i++, key);
			DebugUtil.dump(subPrefix, value, indent, out);
		    }
		    return true;
		}

		return false;
	    }
	};

    public static final DumpHandler componentHandler =
	new DumpHandler() {
	    @Override
	    public boolean dump(String title, Object object, int indent,
		PrintWriter out) {

		if (object instanceof Component) {
		    Component comp = (Component)object;
		    String text = getText(comp);
		    text = text == null ? "" : (": \"" + text + "\"");

		    out.printf("%s%s%s%s\n", indent(indent), title,
			toBaseName(object), text);

		    return true;
		}

		return false;
	    }

	    //
	    // Private methods
	    //

	    private String getText(Component comp) {
		try {
		    return (String)comp.getClass().getMethod("getText").invoke(
			comp);
		} catch (Throwable e) {
		}
		return null;
	    }
	};

    public static final List<DumpHandler> handlers =
	new ArrayList<DumpHandler>();

    static {
	handlers.add(defaultHandler);
	handlers.add(collectionHandler);
	handlers.add(mapHandler);
	handlers.add(componentHandler);
    }

    private static final int _INDENTSIZE = 2;

    //
    // Static methods
    //

    public static void addComponentHandler(
	Component comp, final ComponentHandler handler) {

	AWTEventListener listener =
	    new AWTEventListener() {
		@Override
		public void eventDispatched(AWTEvent event) {
		    MouseEvent e = (MouseEvent)event;
		    if (e.getID() == MouseEvent.MOUSE_CLICKED &&
			e.getButton() == 2 && e.getClickCount() == 1) {
			handler.handle((Component)e.getSource());
		    }
		}
	    };
	Toolkit.getDefaultToolkit().addAWTEventListener(
	    listener, AWTEvent.MOUSE_EVENT_MASK);
    }

    public static void dump(Object object) {
	dump("", object);
    }

    public static void dump(String title, Object object) {
	dump(title, object, 0);
    }

    public static void dump(String title, Object object, int indent) {
	dump(title, object, indent, new PrintWriter(System.out, true));
    }

    public static void dump(String title, Object object, int indent,
	PrintWriter out) {

	synchronized (handlers) {
	    for (int i = handlers.size() - 1; i >= 0; i--) {
		if (handlers.get(i).dump(title, object, indent, out)) {
		    return;
		}
	    }

	    out.printf("%sCould not dump %s",
		indent(indent), toBaseName(object));
	}
    }

    public static String indent(int indent) {
	char[] chars = new char[indent * _INDENTSIZE];
	for (int i = 0; i < chars.length; i++) {
	    chars[i] = ' ';
	}
	return new String(chars);
    }

    public static void output(String name, Object o) {
	System.out.printf("%s: %s\n", name, toBaseName(o));
    }

    public static String toBaseName(Object o) {
	if (o == null)
	    return null;

	Class clazz = o.getClass();
	String name = TextUtil.getBaseName(clazz);
	if (name.matches(".*\\$\\d+$")) {
	    clazz = clazz.getSuperclass();
	    name += " (a " + TextUtil.getBaseName(clazz) + ")";
	}

	return name;
    }

    public static void trackComponentFocus() {
	KeyboardFocusManager.getCurrentKeyboardFocusManager().
	    addPropertyChangeListener("focusOwner",
	    new PropertyChangeListener() {
		@Override
		public void propertyChange(PropertyChangeEvent e) {
		    dump(e.getNewValue());
		}
	    });
    }

    public static void trackComponentHierarchy(Component comp) {
	addComponentHandler(comp,
	    new ComponentHandler() {
		@Override
		public void handle(Component comp) {
		    print(comp);
		}

		private String print(Component comp) {
		    Container parent = comp.getParent();
		    String indent = parent == null ? "" : print(parent);
		    dump(indent, comp);
		    return indent + "  ";
		}
	    });
    }
}
