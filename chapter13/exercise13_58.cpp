// Write a class <Foo> to force assignment to a LVALUE ONLY on the left side
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// NOTE: 
// - & means this function must be called on <lvalue> object i.e. object must be permanent
// - && means this function must be called on <rvalue> i.e. object can be temporary
class Foo {
public:
	Foo() = default;
	Foo(initializer_list<int> il): data(il) {}

	Foo& operator=(const Foo&) &;

	Foo sorted() &&;
	Foo sorted() const &;

	void print(const string& name) const {
		for (auto i: data)
			cout << i << " ";
		cout << endl;
	}

private:
	vector<int> data;
};

Foo& Foo::operator=(const Foo& rhs) & {
	cout << "Lvalue assignment operator called\n";
	data = rhs.data;
	return *this;
}

// can be called on <rvalue> (temporary variable)
Foo Foo::sorted() && {
	cout << "sorted() called on rvalue\n";
	sort(data.begin(), data.end());
	return *this;
}

// must be called on <lvalue> (permanent variable)
Foo Foo::sorted() const & {
	cout << "sorted() called on lvalue\n";
	Foo ret(*this);
	sort(ret.data.begin(), ret.data.end());
	return ret;
}

int main() {
	cout << "=== LVALUE ASSIGNMENT ===\n";
	Foo a{5, 3, 1};
	Foo b{9, 7, 8};
	a = b; // should be OK
	// Foo{} = a; // should NOT be OK
  
	cout << "\n=== SORT ON LVALUE ===\n";
	Foo c{4,2,6};
	Foo sortedC = c.sorted(); // call const & version
	c.print("c (original)");
	sortedC.print("sortedC");

	cout << "\n=== SORT ON RVALUE ===\n";
	Foo sortedTemp = Foo{10,3,7}.sorted(); // call && version
	sortedTemp.print("sortedTemp");

	cout << "\n=== CHAINING ===\n";
	Foo chained = Foo{8,4,2}.sorted().sorted();
	chained.print("chained");
	
	return 0;
}