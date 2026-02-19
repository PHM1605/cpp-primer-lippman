// Add a rvalue reference version of push_back() in <StrBlob>
#include <iostream>

using namespace std;

class StrBlob {
public:
	StrBlob();
	StrBlob(initializer_list<string>);

	size_t size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back();
	void pop_back();
private:
	shared_ptr<vector<string>> data;
};

int main() {
  return 0;
}