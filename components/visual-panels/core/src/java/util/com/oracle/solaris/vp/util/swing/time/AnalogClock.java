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

package com.oracle.solaris.vp.util.swing.time;

import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import java.awt.image.BufferedImage;
import java.beans.*;
import java.util.Calendar;
import javax.swing.*;
import org.jdesktop.animation.timing.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;

@SuppressWarnings({"serial"})
public class AnalogClock extends JPanel implements MouseListener,
    MouseMotionListener, TimingTarget {

    //
    // Static data
    //

    private static final int _DIAMETER = 150;

    //
    // Instance data
    //

    private TimeModel model;
    private TimeSelectionModel selModel;

    private PropertyChangeListener timeListener =
	new PropertyChangeListener() {
	    @Override
	    public void propertyChange(PropertyChangeEvent event) {
		timeChanged();
	    }
	};

    // Cached images to speed up repaints
    private BufferedImage baseImage;
    private BufferedImage timeImage;
    private BufferedImage centerImage;

    private int frameWidth;
    private Point centerPoint;
    private Point mousePoint;
    private boolean interactive;
    private boolean useToolTips;
    private SunIcon sunIcon = new SunIcon();
    private MoonIcon moonIcon = new MoonIcon();
    private StarIcon starIcon = new StarIcon();
    private Shape amPm;
    private Point hourPoint;
    private Point minPoint;
    private Point secPoint;

    private Animator amPmAnimator = new Animator(300, this);
    private float amPmAnimOffset;
    private int amPmAnimFactor;

    // UI prefs
    private Color centerColor = Color.black;
    private Color frameColor = ColorUtil.darker(
	UIManager.getColor("Panel.background"), .2f);
    private Color faceColor = Color.white;
    private Color hourHandColor = Color.black;
    private Color hourMarkColor = Color.black;
    private float lightAngle = (float)Math.toRadians(122);
    private Color minuteHandColor = Color.black;
    private Color minuteMarkColor = Color.gray;
    private Color secondHandColor = Color.red.darker();
    private Color highlightColor = new Color(0, 0, 204);
    private Color amColor = new Color(148, 188, 246);
    private Color pmColor = new Color(0, 0, 78);

    //
    // Constructors
    //

    /**
     * Constructs an {@code AnalogClock} for the given model.
     */
    public AnalogClock(TimeModel model) {
	setTimeModel(model);
	setTimeSelectionModel(new SimpleTimeSelectionModel());
	setOpaque(false);
	setPreferredDiameter(_DIAMETER);
    }

    /**
     * Constructs an {@code AnalogClock} with a zero {@link
     * TimeModel#getTimeOffset offset} from the system clock.
     */
    public AnalogClock() {
	this(new SimpleTimeModel());
    }

    //
    // MouseListener methods
    //

    @Override
    public void mouseClicked(MouseEvent e) {
	int selectedField = selModel.getSelectedField();
	if (selectedField == Calendar.AM_PM && GUIUtil.isUnmodifiedClick(e, 1))
	{
	    amPmAnimOffset = (float)Math.PI;

	    amPmAnimFactor = model.getCalendar().get(
		selectedField) == Calendar.AM ? 1 : -1;

	    // 43200000 = 1000 * 60 * 60 * 12 = milliseconds in 12-hour change
	    long delta = amPmAnimFactor * 43200000;
	    model.setTimeOffset(model.getTimeOffset() + delta);

	    amPmAnimator.start();
	}
    }

    @Override
    public void mouseEntered(MouseEvent e) {
    }

    @Override
    public void mouseExited(MouseEvent e) {
	mousePoint = null;
	repaint();
    }

    @Override
    public void mousePressed(MouseEvent e) {
	mousePoint = null;
	repaint();
    }

    @Override
    public void mouseReleased(MouseEvent e) {
	mouseMoved(e);
    }

    //
    // MouseMotionListener methods
    //

    @Override
    public void mouseDragged(MouseEvent e) {
	int selectedField = selModel.getSelectedField();
	if (selectedField != Calendar.HOUR &&
	    selectedField != Calendar.MINUTE &&
	    selectedField != Calendar.SECOND) {
	    return;
	}

	Point centerPoint = this.centerPoint;
	Point dragPoint = e.getPoint();
	int dY = centerPoint.y - dragPoint.y;
	int dX = dragPoint.x - centerPoint.x;
	float angle = (float)Math.atan2(dY, dX);

	int newVal;
	int period;

	if (selectedField == Calendar.HOUR) {
	    newVal = (int)radiansToHour(angle);
	    period = 12;
	} else {
	    newVal = (int)radiansToMin(angle);
	    period = 60;
	}

	Calendar cal = model.getCalendar();
	int curVal = cal.get(selectedField);
	int factor = (newVal - curVal + period) % period;
	if (factor >= period / 2) {
	    factor -= period;
	}

        long timeOffset = model.getTimeOffset() + factor *
	    timeFieldToMillis(selectedField);
	model.setTimeOffset(timeOffset);
    }

    @Override
    public void mouseMoved(MouseEvent e) {
	mousePoint = e.getPoint();
	repaint();
    }

    //
    // TimingTarget methods
    //

    @Override
    public void begin() {
    }

    @Override
    public void end() {
    }

    @Override
    public void repeat() {
    }

    @Override
    public void timingEvent(float fraction) {
	amPmAnimOffset = amPmAnimFactor * (float)Math.PI * (1 - fraction);
	timeImage = null;
	repaint();
    }

    //
    // JComponent methods
    //

    @Override
    protected void paintComponent(Graphics g1) {
	super.paintComponent(g1);

	Graphics2D g = (Graphics2D)g1;
	g.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
	    RenderingHints.VALUE_ANTIALIAS_ON);

	Insets insets = getInsets();
	int width = getWidth() - insets.left - insets.right;
	int height = getHeight() - insets.top - insets.bottom;

	if (width <= 0 || height <= 0) {
	    return;
	}

	// TimeModel is square
	int diameter = Math.min(width, height);

	int diff = height - width;
	int hDiff = diff / 2;
	if (diff > 0) {
	    diameter = width;
	    insets.top += hDiff;
	    insets.bottom += diff - hDiff;
	} else if (diff < 0) {
	    diameter = height;
	    insets.left -= hDiff;
	    insets.right -= diff - hDiff;
	}

	g.translate(insets.left, insets.top);

	createBaseImage(diameter);
	g.drawImage(baseImage, 0, 0, null);

	g.translate(frameWidth, frameWidth);

	diameter -= 2 * frameWidth;
	int radius = Math.round(diameter/ 2f);

	createTimeImage(diameter);
	g.drawImage(timeImage, 0, 0, null);

	Point centerPoint = new Point(radius, radius);
	Point mousePoint = this.mousePoint;

	if (mousePoint != null) {
	    int selectedField = -1;
	    mousePoint = (Point)mousePoint.clone();
	    mousePoint.translate(-frameWidth - insets.left,
		-frameWidth - insets.top);

	    Line2D line = new Line2D.Float();

	    line.setLine(centerPoint, hourPoint);
	    double hourDist = line.ptSegDist(mousePoint);

	    line.setLine(centerPoint, minPoint);
	    double minDist = line.ptSegDist(mousePoint);

	    line.setLine(centerPoint, secPoint);
	    double secDist = line.ptSegDist(mousePoint);

	    // Is the mouse close enough to a hand to call it selected?
	    double closest = Math.min(hourDist, Math.min(minDist, secDist));
	    if (closest / diameter <= .02f) {
		if (hourDist == closest) {
		    selectedField = Calendar.HOUR;
		    drawHourHand(g, diameter, centerPoint, hourPoint);
		} else if (minDist == closest) {
		    selectedField = Calendar.MINUTE;
		    drawMinuteHand(g, diameter, centerPoint, minPoint);
		} else {
		    selectedField = Calendar.SECOND;
		    drawSecondHand(g, diameter, centerPoint, secPoint);
		}
	    } else if (amPm.contains(mousePoint)) {
		selectedField = Calendar.AM_PM;
	    }

	    setSelectedField(selectedField);
	}

	createCenterImage(diameter);
	g.drawImage(centerImage, 0, 0, null);

	centerPoint.translate(frameWidth + insets.left,
	    frameWidth + insets.top);

	this.centerPoint = centerPoint;

	g.translate(-frameWidth - insets.left, -frameWidth - insets.top);
    }

    //
    // AnalogClock methods
    //

    protected float amPmToRadians() {
	Calendar cal = model.getCalendar();
	int hour = cal.get(Calendar.HOUR);
	int minute = cal.get(Calendar.MINUTE);
	int second = cal.get(Calendar.SECOND);
	int amPm = cal.get(Calendar.AM_PM);
	return amPmToRadians(amPm, hour, minute, second);
    }

    protected Shape drawAmPm(Graphics2D g, int diameter) {
	// Create shapes

	float outerMargin = diameter * .17f;
	float innerMargin = diameter * .105f;

	diameter -= Math.round(2 * outerMargin);
	float radius = diameter / 2f;

	int offset = Math.round(outerMargin);
	g.translate(offset, offset);

	Arc2D.Float outer = new Arc2D.Float(0, 0,
	    diameter, diameter, 0, 180, Arc2D.OPEN);

	int innerDiam = Math.round(2 * innerMargin);
	Arc2D.Float inner = new Arc2D.Float(radius - innerMargin,
	    radius - innerMargin, innerDiam, innerDiam, 180, -180, Arc2D.OPEN);

	Line2D.Float[] lines = {
	    new Line2D.Float(outer.getEndPoint(), inner.getStartPoint()),
	    new Line2D.Float(inner.getEndPoint(), outer.getStartPoint()),
	};

	GeneralPath window = new GeneralPath(outer);
	window.append(lines[0], true);
	window.append(inner, true);
	window.append(lines[1], true);
	window.closePath();

	// Fill background

	float angle = (float)Math.PI - amPmToRadians() - amPmAnimOffset;
	float cos = (float)Math.cos(angle);
	float sin = (float)Math.sin(angle);
	float xDelta = radius * cos;
	float yDelta = radius * sin;

	g.setPaint(new GradientPaint(
	    Math.round(radius + xDelta), Math.round(radius + yDelta), amColor,
	    Math.round(radius - xDelta), Math.round(radius - yDelta), pmColor));
	g.fill(window);

	// Paint icons

	Shape clip = g.getClip();
	g.setClip(window);

	float arcWidth = radius - innerMargin;
	float midPointToCtr = innerMargin + arcWidth * .5f;
	int sunIconDiam = (int)(arcWidth * .7f);
	float sunIconRad = sunIconDiam / 2f;
	xDelta = midPointToCtr * cos;
	yDelta = midPointToCtr * sin;

	sunIcon.setDiameter(sunIconDiam);
	sunIcon.paintIcon(this, g, Math.round(radius + xDelta - sunIconRad),
	    Math.round(radius + yDelta - sunIconRad));

	int moonIconDiam = (int)(sunIconDiam * sunIcon.getOrbSizePercentage());
	float moonIconRad = moonIconDiam / 2f;

	moonIcon.setDiameter(moonIconDiam);
	moonIcon.paintIcon(this, g, Math.round(radius - xDelta - moonIconRad),
	    Math.round(radius - yDelta - moonIconRad));

	int starIconDiam = (int)(moonIconDiam * .4f);
	float starIconRad = starIconDiam / 2f;

	starIcon.setDiameter(starIconDiam);

	// Angle (degree) offset from moon, percent distance between arcs
	float[] starData = {
	    -48f, .55f,
	    -30f, .22f,
	    -25f, .7f,
	    5f, .85f,
	    20f, .25f,
	    25f, .65f,
	    45f, .35f,
	};

	for (int i = 0; i < starData.length; i += 2) {
	    float starAngle = (float)Math.toRadians(starData[i]);
	    float starDist = innerMargin + arcWidth * starData[i + 1];

	    int x = Math.round(radius - starDist *
		(float)Math.cos(angle + starAngle) - starIconRad);

	    int y = Math.round(radius - starDist *
		(float)Math.sin(angle + starAngle) - starIconRad);

	    starIcon.paintIcon(this, g, x, y);
	}

	g.setClip(clip);

	// Paint inset border

	Stroke stroke = g.getStroke();
	g.setStroke(new BasicStroke(diameter / 80));

	cos = (float)Math.cos(lightAngle);
	sin = (float)Math.sin(lightAngle);
	xDelta = radius * cos;
	yDelta = radius * sin;

	Color color = Color.gray;
	Color shadow = ColorUtil.darker(color, .25f);
	Color light = ColorUtil.darker(Color.white, .25f);

	g.setPaint(new GradientPaint(radius + xDelta, radius - yDelta, shadow,
	    radius - xDelta, radius + yDelta, light, false));
	g.draw(outer);

	xDelta = innerMargin * cos;
	yDelta = innerMargin * sin;

	g.setPaint(new GradientPaint(radius + xDelta, radius - yDelta, light,
	    radius - xDelta, radius + yDelta, shadow, false));
	g.draw(inner);

	float theta = lightAngle - (float)Math.PI / 2f;
	float pct = (1 - (float)Math.cos(theta)) / 2f;

	g.setColor(ColorUtil.blend(light, shadow, pct));
	g.draw(lines[0]);
	g.draw(lines[1]);

	g.setStroke(stroke);
	g.translate(-offset, -offset);

	Shape shape = AffineTransform.getTranslateInstance(offset, offset).
	    createTransformedShape(window);

	return shape;
    }

    protected void drawCenterDot(Graphics2D g, int diameter) {
	float radius = diameter / 2f;
	int dotDiam = Math.round(diameter * .06f);
	float dotRadius = dotDiam / 2f;
	float pctFromCtr = .75f;
	float distFromCtr = dotRadius * pctFromCtr;
	float xCenter = radius + distFromCtr * (float)Math.cos(lightAngle);
	float yCenter = radius - distFromCtr * (float)Math.sin(lightAngle);

	Color focusColor = ColorUtil.lighter(centerColor, .65f);
	float[] fractions = {0.0f, 1.0f};
	Color[] colors = {focusColor, centerColor};
	RadialGradientPaint paint = new RadialGradientPaint(
	    xCenter, yCenter, dotRadius, fractions, colors,
	    MultipleGradientPaint.CycleMethod.NO_CYCLE);
	g.setPaint(paint);
	int coord = Math.round(radius - dotRadius);
	g.fillOval(coord, coord, dotDiam, dotDiam);
    }

    protected void drawFace(Graphics2D g, int diameter) {
	g.setColor(faceColor);
	g.fillOval(0, 0, diameter, diameter);
    }

    protected int drawFrame(Graphics2D g, int diameter) {
	// Draw outline
	int frameWidth = 0;
	float radius = diameter / 2f;

	float cos = (float)Math.cos(lightAngle);
	float sin = (float)Math.sin(lightAngle);
	float pctFromEdge = .67f;
	float xStart = radius * (1 + cos);
	float yStart = radius * (1 - sin);
	float xEnd = radius * (1 + pctFromEdge * cos);
	float yEnd = radius * (1 - pctFromEdge * sin);

	g.setPaint(new GradientPaint(xStart, yStart,
	    ColorUtil.darker(Color.white, .25f), xEnd, yEnd,
	    ColorUtil.darker(frameColor, .25f), false));
	g.fillOval(frameWidth, frameWidth, diameter, diameter);

	// Draw outer edge
	int gap = Math.round(diameter * .006f);
	frameWidth += gap;
	diameter -= 2 * gap;
	radius = diameter / 2f;

	xStart = radius * (1 + cos);
	yStart = radius * (1 - sin);
	xEnd = radius * (1 + pctFromEdge * cos);
	yEnd = radius * (1 - pctFromEdge * sin);

	g.setPaint(new GradientPaint(xStart, yStart, Color.white, xEnd, yEnd,
	    frameColor, false));
	g.fillOval(frameWidth, frameWidth, diameter, diameter);

	// Draw inner edge
	gap = Math.round(diameter * .025f);
	frameWidth += gap;
	diameter -= 2 * gap;
	radius = diameter / 2f;

	cos = (float)Math.cos(lightAngle + Math.PI);
	sin = (float)Math.sin(lightAngle + Math.PI);
	pctFromEdge = .5f;
	xStart = radius * (1 + cos);
	yStart = radius * (1 - sin);
	xEnd = radius * (1 + pctFromEdge * cos);
	yEnd = radius * (1 - pctFromEdge * sin);

	g.setPaint(new GradientPaint(xStart, yStart,
	    ColorUtil.lighter(frameColor, .55f), xEnd, yEnd, frameColor,
	    false));
	g.fillOval(frameWidth, frameWidth, diameter, diameter);

	gap = Math.round(diameter * .011f);
	frameWidth += gap;

	return frameWidth;
    }

    protected void drawHand(Graphics2D g, Color color, float handWidth,
	Point p1, Point p2) {

	Stroke stroke = g.getStroke();
	g.setStroke(new BasicStroke(handWidth, BasicStroke.CAP_ROUND,
	    BasicStroke.JOIN_MITER));

	g.setColor(color);
	g.drawLine(p1.x, p1.y, p2.x, p2.y);

	g.setStroke(stroke);
    }

    protected Point drawHand(Graphics2D g, Color color, float handWidth,
	float handLength, float angle, int diameter) {

	float radius = diameter / 2f;
	float cos = (float)Math.cos(angle);
	float sin = (float)Math.sin(angle);
	int x = Math.round(radius + handLength * cos);
	int y = Math.round(radius - handLength * sin);

	// Shadow
	float offset = diameter * .02f;
	cos = (float)Math.cos(lightAngle + Math.PI);
	sin = (float)Math.sin(lightAngle + Math.PI);
	int xOffset = Math.round(offset * cos);
	int yOffset = -Math.round(offset * sin);

	drawHand(g, ColorUtil.alpha(Color.black, .2f), handWidth,
	    new Point((int)radius + xOffset, (int)radius + yOffset),
	    new Point(x + xOffset, y + yOffset));

	// Hand
	Point p = new Point(x, y);
	drawHand(g, color, handWidth, new Point((int)radius, (int)radius), p);

	return p;
    }

    protected void drawHourHand(Graphics2D g, int diameter, Point p1,
	Point p2) {
	drawHand(g, highlightColor, diameter * .02f, p1, p2);
    }

    protected Point drawHourHand(Graphics2D g, int diameter) {
	return drawHand(g, hourHandColor, diameter * .02f, diameter * .275f,
	    hourToRadians(), diameter);
    }

    protected void drawHourMarks(Graphics2D g, int diameter) {
	float markWidth = diameter * .015f;
	float markLength = diameter * .04f;
	float pctFromCtr = .9f;
	float radius = diameter / 2f;

	Stroke stroke = g.getStroke();
	g.setStroke(new BasicStroke(markWidth, BasicStroke.CAP_ROUND,
	    BasicStroke.JOIN_MITER));
	g.setColor(hourMarkColor);

	float angleConst = (float)Math.PI / 6f;
	float distFromCtrStart = radius * pctFromCtr;
	float distFromCtrEnd = distFromCtrStart - markLength;

	for (int i = 0; i < 12; i++) {
	    float angle = i * angleConst;
	    float cos = (float)Math.cos(angle);
	    float sin = (float)Math.sin(angle);

	    int xStart = Math.round(radius + distFromCtrStart * cos);
	    int yStart = Math.round(radius - distFromCtrStart * sin);

	    int xEnd = Math.round(radius + distFromCtrEnd * cos);
	    int yEnd = Math.round(radius - distFromCtrEnd * sin);

	    g.drawLine(xStart, yStart, xEnd, yEnd);
	}

	g.setStroke(stroke);
    }

    protected void drawMinuteHand(Graphics2D g, int diameter, Point p1,
	Point p2) {
	drawHand(g, highlightColor, diameter * .02f, p1, p2);
    }

    protected Point drawMinuteHand(Graphics2D g, int diameter) {
	return drawHand(g, minuteHandColor, diameter * .02f, diameter * .405f,
	    minToRadians(), diameter);
    }

    protected void drawMinuteMarks(Graphics2D g, int diameter) {
	float markWidth = diameter * .009f;
	float markLength = diameter * .015f;
	float pctFromCtr = .9f;
	float radius = diameter / 2f;

	Stroke stroke = g.getStroke();
	g.setStroke(new BasicStroke(markWidth, BasicStroke.CAP_ROUND,
	    BasicStroke.JOIN_MITER));
	g.setColor(minuteMarkColor);

	float angleConst = (float)Math.PI / 30f;
	float distFromCtrStart = radius * pctFromCtr;
	float distFromCtrEnd = distFromCtrStart - markLength;

	for (int i = 0; i < 60; i++) {
	    if (i % 5 != 0) {
		float angle = i * angleConst;
		float cos = (float)Math.cos(angle);
		float sin = (float)Math.sin(angle);

		int xStart = Math.round(radius + distFromCtrStart * cos);
		int yStart = Math.round(radius - distFromCtrStart * sin);

		int xEnd = Math.round(radius + distFromCtrEnd * cos);
		int yEnd = Math.round(radius - distFromCtrEnd * sin);

		g.drawLine(xStart, yStart, xEnd, yEnd);
	    }
	}

	g.setStroke(stroke);
    }

    protected void drawSecondHand(Graphics2D g, int diameter, Point p1,
	Point p2) {
	drawHand(g, highlightColor, diameter * .011f, p1, p2);
    }

    protected Point drawSecondHand(Graphics2D g, int diameter) {
	return drawHand(g, secondHandColor, diameter * .011f,
	    diameter * .405f, secToRadians(), diameter);
    }

    protected void drawShadow(Graphics2D g, int diameter) {
	// This puts the shadow around the entire face, which also looks nice
	// float offset = 0f;
	// float[] fractions = {0f, .95f, 1f};

	float radius = diameter / 2f;
	Color shadow = Color.black;
	Color focus = ColorUtil.alpha(Color.black, 0f);
	float[] fractions = {0f, .94f, 1f};
	Color[] colors = {focus, focus, shadow};

	float cos = (float)Math.cos(lightAngle + Math.PI);
	float sin = (float)Math.sin(lightAngle + Math.PI);
	float offset = radius * .02f;
	float xOffset = offset * cos;
	float yOffset = -offset * sin;
	RadialGradientPaint paint = new RadialGradientPaint(radius + xOffset,
	    radius + yOffset, radius + offset, fractions, colors,
	    MultipleGradientPaint.CycleMethod.NO_CYCLE);

	g.setPaint(paint);
	g.fillOval(0, 0, diameter, diameter);
    }

    /**
     * Gets the color at the AM end of the AM-PM gradient.
     */
    public Color getAmColor() {
	return amColor;
    }

    /**
     * Gets the {@code Animator} the controls the animation of the interactive
     * change from AM to PM and back.
     */
    public Animator getAmPmAnimator() {
	return amPmAnimator;
    }

    /**
     * Gets the color of the center dial of the clock.
     */
    public Color getCenterColor() {
	return centerColor;
    }

    /**
     * Gets the color of the face of the clock.
     */
    public Color getFaceColor() {
	return faceColor;
    }

    /**
     * Gets the color of the outer frame of the clock.
     */
    public Color getFrameColor() {
	return frameColor;
    }

    /**
     * Gets the color to use when highlighting a hand.
     */
    public Color getHighlightColor() {
	return highlightColor;
    }

    public Color getHourHandColor() {
	return hourHandColor;
    }

    /**
     * Gets the color of the hour mark on the clock face.
     */
    public Color getHourMarkColor() {
	return hourMarkColor;
    }

    /**
     * Gets the angle of the light, in radians, with 0 at three o'clock, shining
     * onto the clock.
     */
    public float getLightAngle() {
	return lightAngle;
    }

    public Color getMinuteHandColor() {
	return minuteHandColor;
    }

    /**
     * Gets the color of the minute mark on the clock face.
     */
    public Color getMinuteMarkColor() {
	return minuteMarkColor;
    }

    /**
     * Gets the color at the PM end of the AM-PM gradient.
     */
    public Color getPmColor() {
	return pmColor;
    }

    public Color getSecondHandColor() {
	return secondHandColor;
    }

    public TimeModel getTimeModel() {
	return model;
    }

    public TimeSelectionModel getTimeSelectionModel() {
	return selModel;
    }

    /**
     * Gets whether to use instructional tooltips over the interactive portions
     * of the clock.
     */
    public boolean getUseToolTips() {
	return useToolTips;
    }

    protected float hourToRadians() {
	Calendar cal = model.getCalendar();
	int hour = cal.get(Calendar.HOUR);
	int minute = cal.get(Calendar.MINUTE);
	int second = cal.get(Calendar.SECOND);
	return hourToRadians(hour, minute, second);
    }

    /**
     * Gets whether this {@code AnalogClock}'s time can be set by dragging the
     * hands.
     */
    public boolean isInteractive() {
	return interactive;
    }

    protected float minToRadians() {
	Calendar cal = model.getCalendar();
	int minute = cal.get(Calendar.MINUTE);
	int second = cal.get(Calendar.SECOND);
	return minToRadians(minute, second);
    }

    protected float secToRadians() {
	Calendar cal = model.getCalendar();
	int second = cal.get(Calendar.SECOND);
	return secToRadians(second);
    }

    /**
     * Sets the color at the AM end of the AM-PM gradient.
     */
    public void setAmColor(Color amColor) {
	this.amColor = amColor;
	repaint();
    }

    /**
     * Sets the color of the center dial of the clock.
     */
    public void setCenterColor(Color centerColor) {
	this.centerColor = centerColor;
	repaint();
    }

    /**
     * Sets the preferred widht and height of this {@code AnalogClock} to {@code
     * diameter}.
     */
    public void setPreferredDiameter(int diameter) {
	setPreferredSize(new Dimension(diameter, diameter));
    }

    /**
     * Sets the color of the face of the clock.
     */
    public void setFaceColor(Color faceColor) {
	this.faceColor = faceColor;
	baseImage = null;
	repaint();
    }

    /**
     * Sets the color of the outer frame of the clock.
     */
    public void setFrameColor(Color frameColor) {
	this.frameColor = frameColor;
	baseImage = null;
	repaint();
    }

    /**
     * Sets the color to use when highlighting a hand.
     */
    public void setHighlightColor(Color highlightColor) {
	this.highlightColor = highlightColor;
    }

    public void setHourHandColor(Color hourHandColor) {
	this.hourHandColor = hourHandColor;
	repaint();
    }

    /**
     * Sets the color of the hour mark on the clock face.
     */
    public void setHourMarkColor(Color hourMarkColor) {
	this.hourMarkColor = hourMarkColor;
	baseImage = null;
	repaint();
    }

    /**
     * Sets whether this {@code AnalogClock}'s time can be set by dragging the
     * hands.
     */
    public void setInteractive(boolean interactive) {
	if (this.interactive != interactive) {
	    this.interactive = interactive;
	    if (interactive) {
		addMouseListener(this);
		addMouseMotionListener(this);
	    } else {
		removeMouseListener(this);
		removeMouseMotionListener(this);
		mousePoint = null;
	    }
	}
    }

    /**
     * Sets the angle of the light, in radians, with 0 at three o'clock, shining
     * onto the clock.
     */
    public void setLightAngle(float lightAngle) {
	this.lightAngle = lightAngle;
	baseImage = null;
	timeImage = null;
	centerImage = null;
	repaint();
    }

    public void setMinuteHandColor(Color minuteHandColor) {
	this.minuteHandColor = minuteHandColor;
	repaint();
    }

    /**
     * Sets the color of the minute mark on the clock face.
     */
    public void setMinuteMarkColor(Color minuteMarkColor) {
	this.minuteMarkColor = minuteMarkColor;
	baseImage = null;
	repaint();
    }

    /**
     * Sets the color at the PM end of the AM-PM gradient.
     */
    public void setPmColor(Color pmColor) {
	this.pmColor = pmColor;
	repaint();
    }

    public void setSecondHandColor(Color secondHandColor) {
	this.secondHandColor = secondHandColor;
	repaint();
    }

    public void setTimeModel(TimeModel model) {
	if (this.model != model) {
	    if (this.model != null) {
		this.model.removePropertyChangeListener(timeListener);
	    }

	    model.addPropertyChangeListener(TimeModel.PROPERTY_TIME,
		timeListener);

	    this.model = model;
	    timeChanged();
	}
    }

    public void setTimeSelectionModel(TimeSelectionModel selModel) {
	this.selModel = selModel;
    }

    /**
     * Sets whether to use instructional tooltips over the interactive portions
     * of the clock.
     */
    public void setUseToolTips(boolean useToolTips) {
	if (this.useToolTips != useToolTips) {
	    this.useToolTips = useToolTips;
	    setToolTipText();
	}
    }

    //
    // Private methods
    //

    private void createBaseImage(int diameter) {
	if (baseImage == null || baseImage.getWidth() != diameter) {
	    baseImage = new BufferedImage(diameter, diameter,
		BufferedImage.TYPE_INT_ARGB);

	    Graphics2D g = baseImage.createGraphics();
	    g.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
		RenderingHints.VALUE_ANTIALIAS_ON);

	    frameWidth = drawFrame(g, diameter);
	    diameter -= 2 * frameWidth;

	    g.translate(frameWidth, frameWidth);

	    drawFace(g, diameter);
	    drawHourMarks(g, diameter);
	    drawMinuteMarks(g, diameter);
	    drawShadow(g, diameter);

	    g.translate(-frameWidth, -frameWidth);
	}
    }

    private void createCenterImage(int diameter) {
	if (centerImage == null || centerImage.getWidth() != diameter) {
	    centerImage = new BufferedImage(diameter, diameter,
		BufferedImage.TYPE_INT_ARGB);

	    Graphics2D g = centerImage.createGraphics();
	    g.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
		RenderingHints.VALUE_ANTIALIAS_ON);

	    drawCenterDot(g, diameter);
	}
    }

    private void createTimeImage(int diameter) {
	if (timeImage == null || timeImage.getWidth() != diameter) {
	    timeImage = new BufferedImage(diameter, diameter,
		BufferedImage.TYPE_INT_ARGB);

	    Graphics2D g = timeImage.createGraphics();
	    g.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
		RenderingHints.VALUE_ANTIALIAS_ON);

	    amPm = drawAmPm(g, diameter);
	    hourPoint = drawHourHand(g, diameter);
	    minPoint = drawMinuteHand(g, diameter);
	    secPoint = drawSecondHand(g, diameter);
	}
    }

    private void setSelectedField(int selectedField) {
	setCursor(selectedField == -1 ? null :
	    Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
	selModel.setSelectedField(selectedField);

	setToolTipText();
    }

    private void setToolTipText() {
	String resource = null;

	if (useToolTips) {
	    switch (selModel.getSelectedField()) {
		case Calendar.AM_PM:
		    resource = "time.tooltip.ampm";
		    break;

		case Calendar.HOUR:
		    resource = "time.tooltip.hour";
		    break;

		case Calendar.MINUTE:
		    resource = "time.tooltip.minute";
		    break;

		case Calendar.SECOND:
		    resource = "time.tooltip.second";
		    break;
	    }
	}

	setToolTipText(resource == null ? null : Finder.getString(resource));
    }

    private void timeChanged() {
	timeImage = null;
	repaint();
    }

    //
    // Static methods
    //

    public static float amPmToRadians(int amPm, int hour, int minute,
	int second) {

	hour = (hour % 12) + (amPm == Calendar.PM ? 12 : 0);
	return (6 - (hour + minute / 60f + second / 3600f)) * (float)Math.PI /
	    12f;
    }

    public static float hourToRadians(int hour, int minute, int second) {
	return (15 - (hour + minute / 60f + second / 3600f)) * (float)Math.PI /
	    6f;
    }

    public static float minToRadians(int minute, int second) {
	return (75 - (minute + second / 60f)) * (float)Math.PI / 30f;
    }

    public static float radiansToHour(float radians) {
	float value = (-6 * radians / (float)Math.PI) + 3;
	if (value < 1) {
	    value += 12;
	}
	return value;
    }

    public static float radiansToMin(float radians) {
	float value = (-30 * radians / (float)Math.PI) + 15;
	if (value < 0) {
	    value += 60;
	}
	return value;
    }

    public static float secToRadians(int second) {
	return (75 - second) * (float)Math.PI / 30f;
    }

    /**
     * Converts {@code Calendar} time fields to milliseconds.
     *
     * @param	    calendarField
     *		    {@code Calendar.MILLISECOND},
     *		    {@code Calendar.SECOND},
     *		    {@code Calendar.MINUTE},
     *		    {@code Calendar.HOUR},
     *		    {@code Calendar.HOUR_OF_DAY}, or
     *		    {@code Calendar.AM_PM},
     *
     * @return	    the number of milliseconds in a unit of the given field, or
     *		    zero if {@code calendarField} is not any of the allowed
     *		    fields
     */
    public static long timeFieldToMillis(int calendarField) {
	long millis = 0;
	switch (calendarField) {
	    case Calendar.MILLISECOND:
		millis = 1;
		break;

	    case Calendar.SECOND:
		millis = 1000;
		break;

	    case Calendar.MINUTE:
		millis = 60000;
		break;

	    case Calendar.HOUR:
	    case Calendar.HOUR_OF_DAY:
		millis = 3600000;
		break;

	    case Calendar.AM_PM:
		millis = 43200000;
		break;
	}

	return millis;
    }

    public static void main(String args[]) {
	AnalogClock clock = new AnalogClock();
	clock.setInteractive(true);
	clock.setPreferredDiameter(300);

	TimeModelUpdater updater = new TimeModelUpdater(clock.getTimeModel());
	updater.start();

	JFrame frame = new JFrame();
	Container c = frame.getContentPane();
	c.setLayout(new BorderLayout());
	c.add(clock, BorderLayout.CENTER);
	frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	frame.pack();
	frame.setVisible(true);
    }
}
