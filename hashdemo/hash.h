#ifndef HASH_H
#define HASH_H
#include <stdlib.h>

class Hash{
public:
  Hash(const char *);
  int hash() const;  //return the hash value
private:
  int key;  
};
#endif
