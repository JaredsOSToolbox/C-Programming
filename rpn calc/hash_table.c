#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
  char* key_ = "Jared";
  double value_ = 21.0;
  struct hash_table* map = new_hash_table();
  insert(map, key_, value_);
  fprintf(stdout, "inserted value of: %g!\n", value_);
  double key_value_ = get_key(map, key_);
  fprintf(stdout, "got value of: %g from table!\n", key_value_);
  destructor_(map);
  return 0;
}
