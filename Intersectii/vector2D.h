#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "point2D.h"

class Vector2D {
public:
	float XVect, YVect;
	Vector2D(const float & xVect , const float & yVect) : XVect(xVect) , YVect(yVect) {};
	Vector2D(const Point2D & point) : Vector2D(point.X , point.Y) {};
	Vector2D(const Point2D & point1 , const Point2D & point2) : XVect(point2.X - point1.X) , YVect(point2.Y - point1.Y) {};
	bool IsLeftTurn(const Vector2D & other) const;
};

#endif /* VECTOR2D_H */
