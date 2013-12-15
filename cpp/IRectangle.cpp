#include <iostream>
#include <stdlib.h>

using namespace std;

typedef unsigned long RGB;

class Shape {
public:
	virtual void Draw(void) = 0;
};

void Draw(Shape *pShape)
{
	pShape->Draw();
	//(*pShape).Draw();
}

class Rectangle: public Shape {
public:
	virtual void Draw() { cout << "Rectangle::Draw()" << endl; }
};
class Circle: public Shape {
public:
	virtual void Draw() { cout << "Circle::Draw()" << endl; }
};
class Ellipse: public Shape {
public:
	virtual void Draw() { cout << "Ellipse::Draw()" << endl; }
};
class Cube: public Shape {
public:
	virtual void Draw() { cout << "Cube::Draw()" << endl; }
};
class Sphere: public Shape {
public:
	virtual void Draw() { cout << "Sphere::Draw()" << endl; }
};

class IRectangle{
public:
	virtual ~IRectangle(){}

	virtual float GetLength() const = 0;
	virtual void SetLength(float newLength) = 0;

	virtual float GetWidth() const = 0;
	virtual void SetWidth(float newWidth) = 0;

	virtual RGB GetColor() const = 0;
	virtual void SetColor(RGB newColor) = 0;

	virtual float CalculateArea() const = 0;

	virtual void Draw() = 0;

	static IRectangle *CreatRectangle();
	void Destroy(){ delete this; }
};

class RectangleImpl : public IRectangle{
public:
	RectangleImpl(): m_length(1), m_width(1), m_color(0x00FFEC4D){}
	virtual ~RectangleImpl(){}

	virtual float GetLength() const { return m_length; }
	virtual void  SetLength(float newLength) { m_length = newLength; }

	virtual float GetWidth() const { return m_width; }
	virtual void  SetWidth(float newWidth) { m_width = newWidth; }

	virtual RGB  GetColor() const { return m_color; }
	virtual void SetColor(RGB newColor) { m_color = newColor; }

	virtual float CalculateArea() const { return m_length * m_width; };

	virtual void Draw() { cout << "RectangleImpl::Draw()" << endl; }
	virtual void Draw(int scale) { cout << "RectangleImpl::Draw(int)" << endl; }

private:
	float m_length;
	float m_width;
	RGB   m_color;
};

IRectangle *IRectangle::CreatRectangle()
{
	return new(nothrow) RectangleImpl;
}

int main()
{
	IRectangle *pRect = IRectangle::CreatRectangle();

	if (pRect == NULL) exit(-1);

	pRect->SetLength(100.5);
	pRect->SetWidth(35);
	pRect->SetColor(0x00FFFFFF);

	cout <<"Length: " <<pRect->GetLength() <<endl;
	cout <<"Width:  " <<pRect->GetWidth() <<endl;
	cout <<"Area:   " <<pRect->CalculateArea() <<endl;
	cout <<"Color:  " <<pRect->GetColor() <<endl;
	pRect->Draw();

//	RectangleImpl *pImpl = (RectangleImpl *)pRect; 
	RectangleImpl *pImpl = new RectangleImpl; 
	pImpl->Draw();
	pImpl->Draw(200);

	pRect->Destroy();
	pRect = NULL;

	Shape *pShape = NULL;
	Circle aCircle;
	Cube aCube;
	Sphere aSphere;

	::Draw(&aCircle);
	::Draw(&aCube);
	::Draw(&aSphere);

	pShape = &aCircle;
	pShape->Draw();
	(*pShape).Draw();

	pShape = &aCube;
	pShape->Draw();
	(*pShape).Draw();

	pShape = &aSphere;
	pShape->Draw();
	(*pShape).Draw();
}
