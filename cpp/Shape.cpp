#include <iostream>
#include <stdlib.h>
#include <typeinfo>

using namespace std;

struct Point {
	Point(int x, int y): m_x(x), m_y(y) {}
	int m_x;
	int m_y;
};

ostream& operator<<(ostream& os, const Point& p)
{
	cerr << "\n{\n    HorizontalOrdinate = " << p.m_x\
		 << "\n    VerticalOrdinate   = " << p.m_y <<"\n}\n";
	return os;
}

class Shape {
	Point m_origin;
public:
	Shape(): m_origin(0,0) {}
	explicit Shape(const Point& origin): m_origin(origin) {}
	virtual ~Shape() {cerr << "Shape::~Shape()" << endl;}

	Point GetOrigin() const { return m_origin; }
	virtual void Draw() const {
		cerr << "Shape::Draw()" << endl;
		cerr << "Origin Point:" << m_origin << endl;
	}
};

class Rectangle: public Shape {
	Point m_rightBottom;
public:
	Rectangle(): m_rightBottom(1, 1) {}
	Rectangle(const Point& leftTop, const Point& rightBottom) 
		: Shape(leftTop), m_rightBottom(rightBottom) {}
	virtual ~Rectangle() { cerr << "Rectangle::~Rectangle()" << endl; }

	Point GetLeftTop() const { return GetOrigin(); }
	Point GetRightBottom() const { return m_rightBottom; }
	virtual void Draw() const {
		cerr << "Rectangle::Draw()" << endl;
		cerr << "Left-top Point:     " << GetLeftTop()\
		     << "Right-bottom Point: " << m_rightBottom << endl << endl;
	}

};

class Circle: public Shape {
	int m_radius;
public:
	Circle(): m_radius(1) {}
	Circle(const Point& origin, int radius)
		: Shape(origin), m_radius(radius) {}
	virtual ~Circle() { cerr << "Circle::~Circle()" << endl; }

	int GetRadius() const { return m_radius;}
	virtual void Draw() const {
		cerr << "Circle::Draw()" << endl;
		cerr << "Origin Point:" << GetOrigin()\
		     << "Radius = " << m_radius << endl << endl;
	}
};

void DrawShapes(const Shape shapes[], int numOfShapes)
{
	Shape *p = (Shape *)shapes;
	for (int i=0; i<numOfShapes; ++i)
	{
		if (typeid(*p) == typeid(Shape))
		{
			p->Draw();
			p++;
		}
		else if (typeid(*p) == typeid(Circle))
		{
			Circle *q = (Circle *)p;
			q->Draw();
			p = ++q;
		}
		else if (typeid(*p) == typeid(Rectangle))
		{
			Rectangle *r = (Rectangle *)p;
			r->Draw();
			p = ++r;
		}
		else
		{
		}
	}
}



int main()
{
//	Shape  a(Point(1,1));
//	Circle b(Point(2,2), 5);
//	Rectangle c(Point(3,3), Point(4,4));
//	Shape myShapes[3];
//
//	myShapes[0] = a;
//	myShapes[1] = b;
//	myShapes[2] = c;
//
//	for (int i=0; i<3; ++i)
//		myShapes[i].Draw();

//	DrawShapes(myShapes, 3);
//
//	Rectangle d(Point(3,3), Point(4,4));
//	Rectangle e(Point(5,5), Point(6,6));
//	Rectangle f(Point(7,7), Point(8,8));
//	Rectangle myRects[3];
//
//	myRects[0] = d;
//	myRects[1] = e;
//	myRects[2] = f;
//	DrawShapes(myRects, 3);
//
//	Shape *p = new Shape(Point(1,1));
//	Shape *q = new Circle(Point(2,2), 5);
//	Shape *r = new Rectangle(Point(3,3), Point(4,4));
//	Shape *shapes[3];
//
//	shapes[0] = p;
//	shapes[1] = q;
//	shapes[2] = r;
//
//	for (int i=0; i<3; ++i)
//		shapes[i]->Draw();
//	for (int j=0; j<3; ++j)
//		delete shapes[j];
//
	typedef SmartPtr<Shape> ShapeSmartPtr;//why compile wrong?
	ShapeSmartPtr shapes[3];
	ShapeSmartPtr p(new Shape(Point(1,1)));
	ShapeSmartPtr q(new Circle(Point(2,2), 5));
	ShapeSmartPtr r(new Rectangle(Point(3,3), Point(4,4)));

	shapes[0] = p;
	shapes[1] = q;
	shapes[2] = r;

	for (int i=0; i<3; ++i)
		shapes[i]->Draw();
	for (int j=0; j<3; ++j)
		delete shapes[j];
}
