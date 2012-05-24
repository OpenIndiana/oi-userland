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

package com.oracle.solaris.vp.util.swing;

import java.awt.*;
import java.util.NoSuchElementException;
import javax.swing.*;
import javax.swing.event.*;
import com.oracle.solaris.vp.util.misc.Stackable;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public class BreadCrumbs<T> extends JPanel implements ListDataListener,
    Stackable<T> {

    //
    // Instance data
    //

    private DefaultListModel model;
    private Component indicator;
    private int firstVisibleIndex;

    //
    // Constructors
    //

    public BreadCrumbs(int gap) {
	indicator = createHiddenBreadCrumbIndicator();
	setOpaque(false);

	setModel(new DefaultListModel());

	ConstrainedLayout<RowLayoutConstraint> layout =
	    new RowLayout(HorizontalAnchor.LEFT);

	layout.setDefaultConstraint(
	    new RowLayoutConstraint(VerticalAnchor.FILL, gap));

	setLayout(layout);

	addAll();
    }

    public BreadCrumbs() {
	this(0);
    }

    //
    // ListDataListener methods
    //

    @Override
    public void contentsChanged(ListDataEvent e) {
	addAll();
    }

    @Override
    public void intervalAdded(ListDataEvent e) {
	contentsChanged(e);
    }

    @Override
    public void intervalRemoved(ListDataEvent e) {
	contentsChanged(e);
    }

    //
    // Stackable methods
    //

    /**
     * Clears the model.
     */
    @Override
    public void clear() {
	getModel().clear();
    }

    @Override
    public int getCount() {
	return getModel().getSize();
    }

    /**
     * Gets the last element of the model.
     *
     * @return	    the last element, or {@code null} if the model contains no
     *		    elements
     */
    @Override
    public T peek() {
	try {
	    return peekOrErr();
	} catch (NoSuchElementException e) {
	    return null;
	}
    }

    /**
     * Gets the last element of the model.
     *
     * @return	    the last element
     *
     * @exception   NoSuchElementException
     *		    if the model contains no elements
     */
    @Override
    public T peekOrErr() {
	return peekOrErr(0);
    }

    @Override
    public T peekOrErr(int n) {
	DefaultListModel model = getModel();
	int size = model.getSize();

	@SuppressWarnings({"unchecked"})
	T element = (T)model.get(size - 1 - n);

	return element;
    }

    /**
     * Removes the last element of the model.
     *
     * @return	    the removed element
     *
     * @exception   NoSuchElementException
     *		    if the model contains no elements
     */
    @Override
    public T pop() {
	int size = getModel().getSize();
	if (size == 0) {
	    throw new NoSuchElementException();
	}

	DefaultListModel model = getModel();

	@SuppressWarnings({"unchecked"})
	T element = (T)model.remove(size - 1);

	return element;
    }

    /**
     * Adds the given element to the model as the last element.
     */
    @Override
    public void push(T element) {
	getModel().addElement(element);
    }

    //
    // Component methods
    //

    @Override
    public synchronized Dimension getPreferredSize() {
	int width = 0;
	int height = 0;

	// Preferred width is the sum of the preferred widths of each
	// breadcrumb separator
	for (Component c : getComponents()) {
	    if (c != indicator) {
		Dimension d = c.getPreferredSize();
		width += d.width;
		height = d.height > height ? d.height : height;
	    }
	}

	return new Dimension(width, height);
    }

    @Override
    public synchronized void setBounds(int x, int y, int width, int height) {
	super.setBounds(x, y, width, height);

	int pWidth = getPreferredSize().width;

	// Whether to show hidden breadcrumb indicator
	boolean visible = pWidth > width;
	indicator.setVisible(visible);

	if (visible) {
	    pWidth += indicator.getPreferredSize().width;
	}

	// Components have the following order:
	// 0: Hidden breadcrumb indicator
	// 1: 1st breadcrumb
	// 2: separator
	// 3: 2nd breadcrumb
	// 4: separator
	// ...
	// 2n - 1: nth breadcrumb
	Component[] components = getComponents();

	int firstVisibleIndex = -1;

	for (int i = 0, n = model.getSize(); i < n; i++) {

	    // Whether to show this breadcrumb and following separator
	    // (always show the last breadcrumb)
	    visible = pWidth <= width || i == n - 1;

	    if (visible && firstVisibleIndex == -1) {
		firstVisibleIndex = i;
	    }

	    Component breadCrumb = components[1 + 2 * i];
	    breadCrumb.setVisible(visible);
	    if (!visible) {
		pWidth -= breadCrumb.getPreferredSize().width;
	    }

	    if (i != n - 1) {
		Component separator = components[2 + 2 * i];
		separator.setVisible(visible);
		if (!visible) {
		    pWidth -= separator.getPreferredSize().width;
		}
	    }
	}

	setFirstVisibleIndex(firstVisibleIndex);

	super.setBounds(x, y, width, height);
    }

    //
    // BreadCrumbs methods
    //

    protected Component createBreadCrumb(int index) {
	T element = getElementAt(index);
	return new JLabel(toString(element));
    }

    protected Component createHiddenBreadCrumbIndicator() {
	JLabel indicator = new JLabel(
	    Finder.getString("breadcrumb.hidden.text"));

	indicator.setIcon(ArrowIcon.LEFT);
	indicator.setHorizontalTextPosition(SwingConstants.LEFT);
	return indicator;
    }

    protected Component createSeparator(int index) {
	return new JLabel(ArrowIcon.RIGHT);
    }

    public T getElementAt(int index) {
	@SuppressWarnings({"unchecked"})
	T element = (T)model.getElementAt(index);

	return element;
    }

    protected synchronized int getFirstVisibleIndex() {
	return firstVisibleIndex;
    }

    protected void setFirstVisibleIndex(int firstVisibleIndex) {
	this.firstVisibleIndex = firstVisibleIndex;
    }

    /**
     * Returns the underlying model.
     */
    public DefaultListModel getModel() {
	return model;
    }

    public void setModel(DefaultListModel model) {
	if (this.model != model) {
	    if (this.model != null) {
		ListDataEvent removeEvent = new ListDataEvent(
		    this.model, ListDataEvent.INTERVAL_REMOVED, 0,
		    this.model.getSize() - 1);
		intervalRemoved(removeEvent);

		this.model.removeListDataListener(this);
	    }

	    this.model = model;

	    ListDataEvent addEvent = new ListDataEvent(
		model, ListDataEvent.INTERVAL_ADDED, 0, model.getSize() - 1);
	    intervalAdded(addEvent);

	    model.removeListDataListener(this);
	    model.addListDataListener(this);
	}
    }

    /**
     * Converts the given element to a {@code String} to be displayed as a label
     * This default implementation calls {@code element.toString()}.
     */
    public String toString(T element) {
	return element.toString();
    }

    //
    // Private methods
    //

    private synchronized void addAll() {
	removeAll();
	add(indicator);
	indicator.setVisible(false);

	for (int i = 0, n = model.getSize(); i < n; i++) {
	    if (i != 0) {
		Component separator = createSeparator(i);
		add(separator);
	    }

	    Component breadCrumb = createBreadCrumb(i);
	    add(breadCrumb);
	}

	revalidate();
	repaint();
    }
}
