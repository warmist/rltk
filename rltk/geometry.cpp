#include "geometry.hpp"
#include <cstdlib>
#include <cmath>

namespace rltk {

/*
 * From a given point x/y, project forward radius units (generally tiles) at an angle of degrees_radians degrees
 * (in radians).
 */
std::pair<int, int> project_angle(const int &x, const int &y, const double &radius, const double &degrees_radians) noexcept
{
	return std::make_pair(static_cast<int>(x + radius * std::cos(degrees_radians)), static_cast<int>(y + radius * std::sin(degrees_radians)));
}

/*
 * Perform a function for each line element between x1/y1/z1 and x2/y2/z2. Uses a 3D
 * implementation of Bresenham's line algorithm.
 * https://gist.github.com/yamamushi/5823518
 */
void line_func_3d(const int &x1, const int &y1, const int &z1, const int &x2, const int &y2, const int &z2, std::function<void(int, int, int)> &&func) noexcept
{
	float x = static_cast<float>(x1)+0.5F;
	float y = static_cast<float>(y1)+0.5F;
	float z = static_cast<float>(z1)+0.5F;

	float length = distance3d(x1, y1, z1, x2, y2, z2);
	int steps = static_cast<int>(std::floor(length));
	float x_step = (x - x2) / length;
	float y_step = (y - y2) / length;
	float z_step = (z - z2) / length;

	for (int i=0; i<steps; ++i) {
		x += x_step;
		y += y_step;
		z += z_step;
		func(static_cast<int>(std::floor(x)), static_cast<int>(std::floor(y)), static_cast<int>(std::floor(z)));
	}
}

/*
 * Perform a function for each line element between x1/y1/z1 and x2/y2/z2. Uses a 3D
 * implementation of Bresenham's line algorithm.
 * https://gist.github.com/yamamushi/5823518
 */
void line_func_3d_cancellable(const int &x1, const int &y1, const int &z1, const int &x2, const int &y2, const int &z2, std::function<bool(int, int, int)> &&func) noexcept
{
	float x = static_cast<float>(x1)+0.5F;
	float y = static_cast<float>(y1)+0.5F;
	float z = static_cast<float>(z1)+0.5F;

	float length = distance3d(x1, y1, z1, x2, y2, z2);
	int steps = static_cast<int>(std::floor(length));
	float x_step = (x - x2) / length;
	float y_step = (y - y2) / length;
	float z_step = (z - z2) / length;

	for (int i=0; i<steps; ++i) {
		x += x_step;
		y += y_step;
		z += z_step;
		const bool keep_going = func(static_cast<int>(std::floor(x)), static_cast<int>(std::floor(y)), static_cast<int>(std::floor(z)));
		if (!keep_going) return;
	}
}

}