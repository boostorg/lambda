#include "boost/lambda/lambda.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

#include <functional>

void begin_section(std::string name) {
  std::cout << "-------------------------------------------------------\n";
  std::cout << name << '\n';
  std::cout << "-------------------------------------------------------\n";
  return;
};

void end_section() {
  std::cout << "-------------------------------------------------------\n";
  return;
};

template<class Test>
void call_test(Test t, std::string name)
{
  begin_section(name);
  t();
  end_section();
};

void introduction() {

  using boost::lambda::_1;

  std::cout << "Output should be: 1 2\n";
  std::vector<int> a; a.push_back(1); a.push_back(2);
  for_each(a.begin(), a.end(), std::cout << _1 << ' ');
  std::cout << '\n';
  return; 
}

void motivation() {

  using std::vector;
  using std::ostream_iterator;
  using std::cout;
  using std::bind1st;
  using std::plus;

  using std::transform;
  using std::for_each;

  vector<int> a; a.push_back(1); a.push_back(2);

  std::cout << "Output should be: 23 = 23 = 23\n";
  transform(a.begin(), a.end(), ostream_iterator<int>(cout),
          bind1st(plus<int>(), 1));
  
  using boost::lambda::_1;

  cout << " = "; 

  transform(a.begin(), a.end(), ostream_iterator<int>(cout), 1 + _1);
  
  cout << " = "; 

  for_each(a.begin(), a.end(), cout << (_1 + 1));

  std::cout << '\n';
  return; 
}

int main() {

  using std::cout;

  call_test(introduction, "introduction");  cout << '\n';

  call_test(motivation, "Motivation");  cout << '\n';

  return 0;
}
