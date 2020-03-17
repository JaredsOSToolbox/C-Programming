#include <assert.h>
#include <stdio.h>

size_t strlen_(char* string){
  size_t size_;
  for(size_ = 0; string[size_] != '\0'; ++size_) {}
  return size_;
}

void test_strlen_(char* str, size_t size_){
  assert(strlen_(str) == size_);
}

void test_all_strlen_(){
  test_strlen_("string", 6);
  test_strlen_("Hello", 5);
  printf("All strlen_ assertions passed!\n");
}

int main(int argc, const char* argv[]){
  test_all_strlen_();
  return 0;
}
