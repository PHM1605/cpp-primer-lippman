// Extend <ConstStrBlobStr> class to have "Member-access operators"
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class StrBlob {
private:
  shared_ptr<vector<string>> data;
};

int main() {
  return 0;
}