/*
If we want to develop some filters function for Product based on their color and size
*/

#include <iostream>
#include <string>
#include <vector>

enum class Color { Red, Green, Blue };
enum class Size { Small, Medium, Large };

struct Product {
	std::string name;
	Color color;
	Size size;

	Product(std::string name, Color color, Size size) : name{ name }, color{ color }, size{ size } {}
};

/*
=== the poor way ===
*/
struct ProductFilter {
	/*
	different filters
	*/
	std::vector<Product*> by_color(const std::vector<Product*>& products, Color color) {
		std::vector<Product*> result;
		for (auto& product : products) {
			if (product->color == color)
				result.push_back(product);
		}

		return result;
	}

	std::vector<Product*> by_size(const std::vector<Product*> products, Size size) {
		std::vector<Product*> result;
		for (auto& product : products) {
			if (product->size == size)
				result.push_back(product);
		}

		return result;
	}

	// for each new type of filter we need to change the ProductFilter and re-test all the prev filters,
	// hence close for extension and open for modification
};

/*
=== better way ===
*/
template <typename T>
struct ISpecification {
	virtual bool is_satisfied(T* p) const = 0;
};

template<typename T>
struct IFilter {
	virtual std::vector<T*> filter(std::vector<T*>&, ISpecification<T> &) = 0;
};

struct ColorSpecification : ISpecification<Product> {
	Color color;
	
	explicit ColorSpecification(const Color color) : color{ color } {};

	bool is_satisfied(Product* p) const override{
		return p->color == color;
	}
};

struct SizeSpecification : ISpecification<Product> {
	Size size;

	explicit SizeSpecification(const Size size) : size{ size } {};

	bool is_satisfied(Product* p) const override{
		return p->size == size;
	}
};

template<typename T>
struct AndSpecification : ISpecification<T> {
	ISpecification<T> &first;
	ISpecification<T> &second;

	AndSpecification(ISpecification<T> &first, ISpecification<T> &second) : first{ first }, second{ second } {}

	bool is_satisfied(Product* p) const override {
		return first.is_satisfied(p) && second.is_satisfied(p);
	}
};

struct BetterFilter : IFilter<Product> {

	std::vector<Product*> filter(std::vector<Product*> &products, ISpecification<Product> &spec) override{
		std::vector<Product*> result;
		for (Product * product : products) {
			if (spec.is_satisfied(product))
				result.push_back(product);
		}

		return result;
	}
};

int main() {

	Product apple{ "Apple", Color::Green, Size::Small };
	Product tree{ "Tree", Color::Green, Size::Large };
	Product house{ "House", Color::Blue, Size::Large };

	std::vector<Product*> products{ &apple, &tree, &house };

	BetterFilter betterFilter;
	ColorSpecification greenSpec{ Color::Green };
	SizeSpecification largeSpec{ Size::Large };
	AndSpecification<Product> andSpec{ greenSpec, largeSpec };
	
	std::vector<Product*> greenProducts = betterFilter.filter(products, greenSpec);
	std::vector<Product*> greenAndLargeProducts = betterFilter.filter(products, andSpec);
	
	for (auto& product : greenProducts) {
		std::cout << product->name << " is green" << std::endl;
	}

	for (auto& product : greenAndLargeProducts) {
		std::cout << product->name << " is green and large" << std::endl;
	}

	return 0;
}