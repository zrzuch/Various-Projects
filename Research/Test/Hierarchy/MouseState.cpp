#include "MouseState.h"

MouseState::MouseState ()
: m_isPressed			(false)
, m_currentMouseButton	(MouseButton::NEITHER)
, m_x 					(0)
, m_y 					(0)
, m_newX				(0)
, m_newY				(0)
, m_width  				(0)
, m_height				(0)
{ }

void
MouseState::setLeftClick(double x, double y)
{
	m_currentMouseButton = MouseButton::LEFT_CLICK;
	m_isPressed	= true;
	m_x 		= x;
	m_y 		= y;
	m_newX		= x;
	m_newY 		= y;
}

void
MouseState::setRightClick(double x, double y)
{
	m_currentMouseButton = MouseButton::RIGHT_CLICK;
	m_isPressed	= true;
	m_x 		= x;
	m_y 		= y;
	m_newX		= x;
	m_newY 		= y;
}

void
MouseState::setReleased ()
{
	m_currentMouseButton = MouseButton::NEITHER;
}

bool
MouseState::isLeftClicked()
{
	return m_currentMouseButton == MouseButton::LEFT_CLICK;
}

bool
MouseState::isRightClicked()
{
	return m_currentMouseButton == MouseButton::RIGHT_CLICK;
}

void
MouseState::translate (double x, double y)
{
	m_x 		= m_newX;
	m_y 		= m_newY;
	m_newX		= x;
	m_newY 		= y;
}

void
MouseState::setWidth(double width)
{
	m_width = width;
}

void
MouseState::setHeight(double height)
{
	m_height = height;
}

void
MouseState::setXFOV(double xFOV)
{
	m_xFOV = xFOV;
}

void
MouseState::setYFOV(double yFOV)
{
	m_yFOV = yFOV;
}

double
MouseState::getXDegrees() const
{
	return -m_xFOV * getTranslateX() / m_width;
}

double
MouseState::getYDegrees() const
{
	return -m_yFOV * getTranslateY() / m_height;
}

double
MouseState::getTranslateX() const
{
	return m_newX - m_x;
}

double
MouseState::getTranslateY() const
{
	return m_newY - m_y;
}