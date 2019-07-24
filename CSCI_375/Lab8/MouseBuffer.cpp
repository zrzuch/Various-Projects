#include "MouseBuffer.h"

MouseBuffer::MouseBuffer ()
: m_currentMouseButton	(MouseButton::NEITHER)
, m_x 					(0)
, m_y 					(0)
, m_newX				(0)
, m_newY				(0)
, m_width  				(0)
, m_height				(0)
{ }

void
MouseBuffer::setLeftClick(double x, double y)
{
	m_currentMouseButton = MouseButton::LEFT_CLICK;
	m_x 		= x;
	m_y 		= y;
	m_newX		= x;
	m_newY 		= y;
}

void
MouseBuffer::setRightClick(double x, double y)
{
	m_currentMouseButton = MouseButton::RIGHT_CLICK;
	m_x 		= x;
	m_y 		= y;
	m_newX		= x;
	m_newY 		= y;
}

void
MouseBuffer::setReleased ()
{
	m_currentMouseButton = MouseButton::NEITHER;
}

bool
MouseBuffer::isLeftClicked()
{
	return m_currentMouseButton == MouseButton::LEFT_CLICK;
}

bool
MouseBuffer::isRightClicked()
{
	return m_currentMouseButton == MouseButton::RIGHT_CLICK;
}

void
MouseBuffer::translate (double x, double y)
{
	m_x 		= m_newX;
	m_y 		= m_newY;
	m_newX		= x;
	m_newY 		= y;
}

void
MouseBuffer::setWidth(double width)
{
	m_width = width;
}

void
MouseBuffer::setHeight(double height)
{
	m_height = height;
}

void
MouseBuffer::setXFOV(double xFOV)
{
	m_xFOV = xFOV;
}

void
MouseBuffer::setYFOV(double yFOV)
{
	m_yFOV = yFOV;
}

double
MouseBuffer::getXDegrees() const
{
	return MOUSE_SENSITIVITY * -m_xFOV * getTranslateX() / m_width;
}

double
MouseBuffer::getYDegrees() const
{
	return MOUSE_SENSITIVITY * -m_yFOV * getTranslateY() / m_height;
}

double
MouseBuffer::getTranslateX() const
{
	return m_newX - m_x;
}

double
MouseBuffer::getTranslateY() const
{
	return m_newY - m_y;
}