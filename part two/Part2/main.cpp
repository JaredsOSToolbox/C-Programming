#include <iostream>

class A{
  public:
    int v = 0;
  private:
    int va = 100;

};

int main(){
  A a;
  std::cout << a.v << std::endl;
  std::cout << a.va << std::endl;
  return 0;
}
