#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool compare(const char* X, const char* Y){
  while(*X && *Y){
    if(*X != *Y){ return false; }
    X++;
    Y++;
    }
  return (*Y == '\0');
}

const char *strstr_(const char *heap_, const char *pattern_){
  while(*heap_ != '\0'){
    if((*heap_ == *pattern_) && compare(heap_, pattern_)){
      return heap_;
    }
    heap_++;
  }
  return NULL;
}

void test_strtr_(const char *input, const char *after, const char *compared){
  assert(strcmp(strstr_(input, after), compared) == 0);
}

void all_test_strstr_(){
  test_strtr_("---Hello---", "Hello", strstr("---Hello---", "Hello"));
  test_strtr_("Jared,.Dyreson", ",.", strstr("Jared,.Dyreson", ",."));
  test_strtr_("Jared|Dyreson", "|", strstr("Jared|Dyreson", "|"));
}

int main(int argc, const char* argv[]){
  all_test_strstr_();
  printf("All assertions passed!\n");
  return 0;
}
