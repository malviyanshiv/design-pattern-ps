/*
* Liskov Substitution Principle
* Let Φ(x) be a property provable about objects x of type T.
* Then Φ(y) should be true for objects y of type S where S is a subtype of T.
* 
* The object of superclass should be replacable with objects of its subclass
* without breaking the application.
*/

#include <iostream>

class Rectangle {
protected:
	int height;
	int width;

public:
	Rectangle(int width, int height) : width{ width }, height{ height } {}

	virtual int getHeight() const {
		return height;
	}

	virtual void setHeight(const int height) {
		this->height = height;
	}

	virtual int getWidth() const {
		return width;
	}

	virtual void setWidth(const int width) {
		this->width = width;
	}

	int area() {
		return this->height * this->width;
	}
};

/*
=== A bugy code example ===
*/
class Square : public Rectangle {
public:
	Square(int size) : Rectangle(size, size) {}

	void setHeight(const int height) {
		this->height = width = height;
	}

	void setWidth(const int width) {
		this->width = height = width;
	}
};

void process(Rectangle& rectangle) {
	int w = rectangle.getWidth();
	rectangle.setHeight(10);
	std::cout << "Expected area: " << 10 * w
		<< ", actual height: " << rectangle.area() << std::endl;
}

int main() {

	Rectangle rectangle(5, 10);
	Square square(5);
	process(rectangle);
	process(square);

	return 0;
}