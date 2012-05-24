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

package com.oracle.solaris.vp.panel.swing.timezone;

import java.awt.*;
import java.awt.event.*;
import java.awt.geom.Point2D;
import java.util.*;
import javax.swing.*;
import com.oracle.solaris.vp.util.swing.ScaledIcon;

public class LocationPicker<T> extends JLabel
    implements MouseListener, MouseMotionListener
{
    static final int LOC_OFFSET = 2;
    static final int LOC_SIZE = LOC_OFFSET * 2 + 1;

    /**
     * Maps a normalized 2D location (0..1, 0..1) to a pixel location
     * using the provided image dimensions.
     *
     * @param dim the dimension of the image to map into
     * @param point the normalized 2D location
     * @return the discrete pixel location within the image
     */
    private static Point normToPixel(Dimension dim, Point2D point)
    {
	double width = dim.getWidth();
	double height = dim.getHeight();
	return new Point((int)(width * point.getX()),
	    (int)(height * point.getY()));
    }

    private class LocationLabel extends JLabel
    {
	private final T object_;
	private final String label_;
	private final Point2D center_;
	private Point pixelCenter_;
	private boolean highlit_;
	private boolean selected_;

	LocationLabel(T object)
	{
	    object_ = object;
	    label_ = mapper_.getLabel(object);
	    center_ = mapper_.map(object);

	    setSize(LOC_SIZE, LOC_SIZE);
	}

	@Override
	public void paint(Graphics g)
	{
	    Graphics2D g2 = (Graphics2D)g;
	    g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
		RenderingHints.VALUE_ANTIALIAS_ON);

	    g.setColor(Color.black);
	    g.fillRect(1, 1, LOC_SIZE - 2, LOC_SIZE - 2);
	    g.setColor(selected_ ?
		Color.yellow : highlit_ ? Color.cyan : Color.red.darker());
	    g.fillRect(0, 0, LOC_SIZE - 2, LOC_SIZE - 2);
	}

	Point2D getCenter()
	{
	    return (center_);
	}

	Point getPixelCenter()
	{
	    return (pixelCenter_);
	}

	void setPixelCenter(Point pixelCenter)
	{
	    pixelCenter_ = pixelCenter;
	    setLocation(pixelCenter.x - LOC_OFFSET, pixelCenter.y - LOC_OFFSET);
	}

	T getObject()
	{
	    return (object_);
	}

	String getToolTip()
	{
	    return (label_);
	}

	void setHighlit(boolean highlit)
	{
	    highlit_ = highlit;
	    repaint(getVisibleRect());
	}

	void setSelected(boolean selected)
	{
	    selected_ = selected;
	    repaint(getVisibleRect());
	}
    }

    private class LocationLayout implements LayoutManager
    {
	public void addLayoutComponent(String name, Component comp)
	{
	}

	public void removeLayoutComponent(Component comp)
	{
	}

	public Dimension preferredLayoutSize(Container parent)
	{
	    return (new Dimension(0, 0));
	}

	public Dimension minimumLayoutSize(Container parent)
	{
	    return (new Dimension(0, 0));
	}

	public void layoutContainer(Container parent)
	{
	    int nComps = parent.getComponentCount();

	    Dimension size = parent.getSize();
	    for (int i = 0; i < nComps; i++) {
		Component c = parent.getComponent(i);
		if (!c.isVisible())
		    continue;
		LocationLabel label = (LocationLabel)c;
		label.setPixelCenter(normToPixel(size, label.getCenter()));
	    }
	}
    }

    private LocationMapper<T> mapper_;
    private Map<T, LocationLabel> objects_ = new HashMap<T, LocationLabel>();
    private LocationLabel current_;
    private LocationLabel selection_;

    private LocationSelectionListeners<T> selectionListeners_ =
	new LocationSelectionListeners<T>();

    private LocationSelectionListeners<T> highlightListeners_ =
	new LocationSelectionListeners<T>();

    private ScaledIcon icon_;

    //
    // Constructors
    //

    public LocationPicker(Icon background, LocationMapper<T> mapper) {

	icon_ = new ScaledIcon(background);
	setIcon(icon_);
	mapper_ = mapper;
	current_ = null;

	setLayout(new LocationLayout());

	addMouseMotionListener(this);
	addMouseListener(this);
    }

    @Override
    public Dimension getPreferredSize() {
	if (isPreferredSizeSet()) {
	    return super.getPreferredSize();
	}

	Insets insets = getInsets();
	Icon icon = icon_.getIcon();
	int width = icon.getIconWidth() + insets.left + insets.right;
	int height = icon.getIconHeight() + insets.top + insets.bottom;

	return new Dimension(width, height);
    }

    @Override
    public void setBounds(int x, int y, int width, int height)
    {
	super.setBounds(x, y, width, height);
	icon_.setIconWidth(width);
	icon_.setIconHeight(height);
    }

    /*
     * MouseListener methods
     */

    public void mouseClicked(MouseEvent e)
    {
	/* Theoretically, motion could be lost or not occur. */
	mouseMoved(e);
	setSelection(current_);
    }

    public void mousePressed(MouseEvent e)
    {
	return;
    }

    public void mouseReleased(MouseEvent e)
    {
	return;
    }

    public void mouseEntered(MouseEvent e)
    {
	return;
    }

    public void mouseExited(MouseEvent e)
    {
	return;
    }

    /*
     * MouseMotionListener methods
     */

    public void mouseDragged(MouseEvent e)
    {
	return;
    }

    public void mouseMoved(MouseEvent e)
    {
	double mindist = Double.MAX_VALUE;
	LocationLabel closest = null;

	/*
	 * Simple but sufficient.
	 */
	Point target = e.getPoint();
	for (LocationLabel ll : objects_.values()) {
	    double dist = target.distanceSq(ll.getPixelCenter());
	    if (dist < mindist) {
		mindist = dist;
		closest = ll;
	    }
	}
	setCurrent(closest);
    }

    /*
     * LocationPicker methods
     */

    private void sendEvent(LocationSelectionListeners<T> listeners,
	LocationSelectionEvent.Type type, LocationLabel location)
    {
	LocationSelectionEvent<T> event =
	    new LocationSelectionEvent<T>(this, type,
	    location == null ? null : location.getObject());

	listeners.locationChanged(event);
    }

    private void setCurrent(LocationLabel newloc)
    {
	if (newloc != current_) {
	    if (current_ != null)
		current_.setHighlit(false);
	    if (newloc != null) {
		newloc.setHighlit(true);
		setToolTipText(newloc.getToolTip());
	    } else {
		setToolTipText(null);
	    }

	    current_ = newloc;

	    sendEvent(highlightListeners_,
		LocationSelectionEvent.Type.HIGHLIGHT, selection_);
	}
    }

    private void setSelection(LocationLabel newloc)
    {
	if (newloc != selection_) {
	    if (selection_ != null)
		selection_.setSelected(false);
	    if (newloc != null)
		newloc.setSelected(true);

	    selection_ = newloc;

	    sendEvent(selectionListeners_,
		LocationSelectionEvent.Type.SELECTION, selection_);
	}
    }

    public void setSelection(T object)
    {
	LocationLabel ll = objects_.get(object);
	if (ll == null && object != null)
	    throw (new IllegalArgumentException("Object not in display"));
	setSelection(ll);
    }

    public T getSelection()
    {
	return ((selection_ == null) ? null : selection_.getObject());
    }

    public void addSelectionListener(LocationSelectionListener<T> listener)
    {
	selectionListeners_.add(listener);
    }

    public boolean removeSelectionListener(
	LocationSelectionListener<T> listener)
    {
	return selectionListeners_.remove(listener);
    }

    public void addHighlightListener(LocationSelectionListener<T> listener)
    {
	highlightListeners_.add(listener);
    }

    public boolean removeHighlightListener(
	LocationSelectionListener<T> listener)
    {
	return highlightListeners_.remove(listener);
    }

    public void setObjects(Set<T> objects) {
	if (!objects_.isEmpty()) {
	    for (LocationLabel label : objects_.values())
		remove(label);
	    objects_.clear();
	}

	for (T o : objects) {
	    LocationLabel l = new LocationLabel(o);
	    add(l);
	    objects_.put(o, l);
	}
    }
}
