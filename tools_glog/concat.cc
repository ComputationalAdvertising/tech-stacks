#include <string.h>
#include <stdio.h>
#include <string>

int main(int argc, char** argv) {
  char* dir = "/opt/home";
  char* name = "exec";
  size_t size = strlen(dir) + strlen(name) + 1 + 1;
  char* tmp = new char[size];
  tmp[size-1] = '\0';
  snprintf(tmp, size, "%s/%s", dir, name);
  printf("dir:%s, name:%s, new_name:%s\n", dir, name, tmp);
}
