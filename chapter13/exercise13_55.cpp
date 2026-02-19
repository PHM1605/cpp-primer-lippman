// Add a rvalue reference version of push_back() in <StrBlob>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class StrBlob {
public:
	StrBlob();
	StrBlob(initializer_list<string>);

	size_t size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	StrBlob push_back(const string&) &&; // <rvalue> version
	void pop_back();

	void print() {
		for (auto& s: *data) {
			cout << s << " ";
		} 
		cout << endl;
	}

private:
	shared_ptr<vector<string>> data;
};

StrBlob::StrBlob():
	data(make_shared<vector<string>>()) {}

StrBlob::StrBlob(initializer_list<string> il):
	data(make_shared<vector<string>>(il)) {}

// <rvalue> version
StrBlob StrBlob::push_back(const string& t) && {
	data->push_back(t);
	return *this;
}

void StrBlob::pop_back() {
	data->pop_back();
}

int main() {
	// Prove <rvalue>: can be called in a chain
	cout << "\n=== Test: Chaining on temporary ===" << endl;
	auto my_strblob = StrBlob({"X", "Y"}).push_back("Z").push_back("T");
	my_strblob.print();
	
  return 0;
}