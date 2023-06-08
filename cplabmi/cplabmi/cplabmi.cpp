#include <iostream>

using namespace std;

class Area
{
public:
	int areav = 0;
	int myArea(int len, int wid)
	{
		areav = 2 * (len + wid);
		return areav;
	}
	~Area()
	{
		cout << "Area has been destroyed." << endl;
	}
};

class Perimeter
{
public:
	int perimv = 0;
	int myPerimeter(int len, int wid)
	{
		perimv = 2 * (len + wid);
		return perimv;
	}
	~Perimeter()
	{
		cout << "Rectangle has been destroyed." << endl;
	}

};

class Rectangle : public Area, public Perimeter
{
	int reclen;
	int recwid;
public:
	Rectangle()
	{
		reclen = 2;
		recwid = 3;
	}
	int area()
	{
		return myArea(reclen, recwid);
	}
	int perimeter()
	{
		return myPerimeter(reclen, recwid);
	}
	~Rectangle()
	{
		cout << "Rectangle has been destroyed." << endl;
	}
};
