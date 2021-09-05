#include <stdio.h>

/*
* packed means it will use the smallest possible space for struct- i.e. it will cram fields together without padding
* aligned means each struct will begin on a 4 byte boundary - i.e. for any struct, its address can be divided by 4
*/
#define STRUCTSIZE(str) printf("%s:%d\n", #str, sizeof(str))
#define STRUCTMAP(str) {\
  str s;\
  s.pf();\
}

struct S1 {
  char ch1;
  int val;
  char ch2;
  void pf() {
    long add1 = long(&ch1);
    long add2 = long(&val);
    long add3 = long(&ch2);
    printf("%ld, %ld, %ld\n", 0, add2 - add1, add3 - add2);
  }
};

struct S2 {
  char ch1;
  int val;
  char ch2;
  void pf() {
    long add1 = long(&ch1);
    long add2 = long(&val);
    long add3 = long(&ch2);
    printf("%ld, %ld, %ld\n", 0, add2 - add1, add3 - add2);
  }
} __attribute__((packed));

struct S3 {
  char ch1;
  int val;
  char ch2;
  void pf() {
    long add1 = long(&ch1);
    long add2 = long(&val);
    long add3 = long(&ch2);
    printf("%ld, %ld, %ld\n", 0, add2 - add1, add3 - add2);
  }
} __attribute__((aligned(4)));

struct S4 {
  char ch1;
  int val;
  char ch2;
  void pf() {
    long add1 = long(&ch1);
    long add2 = long(&val);
    long add3 = long(&ch2);
    printf("%ld, %ld, %ld\n", 0, add2 - add1, add3 - add2);
  }
} __attribute__((packed, aligned(4)));

int main() {
  STRUCTSIZE(S1);
  STRUCTMAP(S1);
  STRUCTSIZE(S2);
  STRUCTMAP(S2);
  STRUCTSIZE(S3);
  STRUCTMAP(S3);
  STRUCTSIZE(S4);
  STRUCTMAP(S4);
  
  return 0;
}