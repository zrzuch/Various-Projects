#ifndef MOUSEBUFFER_H
#define MOUSEBUFFER_H

#include <GLFW/glfw3.h>

class MouseBuffer
{
public:

	MouseBuffer ();

	void
	setClick(GLFWwindow* window, bool isLeft = true);

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

	static constexpr float MOUSE_SENSITIVITY = 1.1;

	enum class MouseButton
	{
		NEITHER,
		LEFT_CLICK,
		RIGHT_CLICK
	};

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