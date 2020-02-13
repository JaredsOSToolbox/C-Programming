#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

enum SEVERITY{none, low, moderate, high};

struct message{
  struct tm* time_;
  enum SEVERITY severity_;
  const char* content;
  const char* function_message;
  size_t line_number;
};

struct message* new_message(){
  struct message *m = (struct message*)malloc(sizeof(struct message));
  struct tm* time_info;
  time_t rt;
  time(&rt);
  time_info = localtime(&rt);
  m->time_ = time_info;
  return m;
}

void set_message(struct message* packet, const char* m){
  packet->content = m;
}

void set_severity(struct message* packet, enum SEVERITY s){
  packet->severity_ = s;
}

void set_line_number(struct message* packet, size_t ln){
  packet->line_number = ln;
}

void print_time(FILE* out, struct message* m){
  fprintf(out, "Current local time is: %s\n", asctime(m->time_));
  fprintf(out, "Current local hour is: %d\n", m->time_->tm_hour);
}

void print_log(FILE* out, struct message* m, char s){
 // out <- file to print to
 // m <- message packet
 // s <- separator for time format
 fprintf(out, "[%d%c%d%c%d]\n", 
          m->time_->tm_mon, s, m->time_->tm_mday, s, 1900+m->time_->tm_year);
 fprintf(out, "[LN: %zu]\n", m->line_number);
 fprintf(out, "[FN: %s]\n", m->function_message);
 fprintf(out, "[Severity: %d]\n", m->severity_);
 fprintf(out, "%s\n", m->content);
}

/*END HELPER FUNCTIONS*/

bool open_file(FILE* input){ return (input != NULL); }

bool close_file(FILE* file_to_close){
  if(file_to_close != NULL){ 
    fclose(file_to_close); 
    return true;
  }
  return false;
}

void read_log(FILE* output){
  /*fprintf(output, "")*/
}
int main(int argc, const char* argv[]){
  struct message* n = new_message();
  /*print_time(stdout, n);*/
  print_log(stdout, n, '|');
  free(n);
  return 0;
}
