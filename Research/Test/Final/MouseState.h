#ifndef MOUSESTATE_H
#define MOUSESTATE_H

class MouseState
{
public:

	MouseState ();

	void
	setLeftClick(double x, double y);

	void
	setRightClick(double x, double y);

	void
	setReleased ();

	bool
	isLeftClicked();

	bool
	isRightClicked();

	void
	translate (double x, double y);

	void
	setWidth(double width);

	void
	setHeight(double height);

	void
	setXFOV(double xFOV);

	void
	setYFOV(double yFOV);

	double
	getXDegrees() const;

	double
	getYDegrees() const;

	double
	getTranslateX() const;

	double
	getTranslateY() const;

private:

	enum class MouseButton
	{
		NEITHER,
		LEFT_CLICK,
		RIGHT_CLICK
	};

	bool m_isPressed;
	MouseButton m_currentMouseButton;

	double m_x;
	double m_y;

	double m_newX;
	double m_newY;

	double m_width;
	double m_height;

	double m_xFOV;
	double m_yFOV;
};

#endif