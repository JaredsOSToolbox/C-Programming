#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

void file_size(const char* path){
  struct stat stbuf;
  if(stat(path, &stbuf) == -1){
    fprintf(stderr, "cannot access %s, cowardly refusing!\n", path);
    return;
  }
  /*if((stbuf.st_mode & S_IFMT) == S_IFDIR){*/
    /*dirwalk(path, file_size);*/
  /*}*/
  printf("%ld %s \n", stbuf.st_size, path);
}
int main(){
  file_size("fsize.c");
  return 0;
}
