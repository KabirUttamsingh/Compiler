#include "hashTable.h"

HashTable::HashTable(int n):size(n){
  check(n > 2 && prime(n),
	"(HashTable()) Need positive prime number for table size");
  table = new Link*[n];
  check(table != NULL,"(HashTable(int)) Heap overflow");
  for(int j = 0; j < size; j++)
    table[j] = NULL;
}

HashTable::HashTable(const HashTable& t):size(t.size){
  table = new Link*[size];
  check(table != NULL, "(HashTable(HashTable)) Heap overflow");
  for(int j = 0; j < size; j++)
    table[j] = t.table[j];
}

HashTable::~HashTable(){
  /*  for(int j = 0; j < size; j++)
    if(table[j] != NULL)
      delete table[j];
      delete [] table;*/
}

HashTable& HashTable::add(string str, string d){
  int h;
  check(!inTable(str),"(add()) Duplicate key");
  h = Hash(str).hash() % size;
  table[h] = new Link(str, d, table[h]);
  check(table[h] != NULL, "(add()) Heap overflow");
  return *this;
}

bool HashTable::inTable(string k) const{
  int h;
  Link *temp;
  h = Hash(k).hash() % size;
  temp = table[h];
  while(temp != NULL && temp->key!=k)
    temp = temp->next;
  return temp != NULL;
}

string HashTable::get(string k) const
{
  int h;
  Link *temp;
    h = Hash(k).hash() % size;
    temp = table[h];
    while(temp!=NULL && temp->key!=k)
      {
	temp = temp->next;
      }
  if(temp!=NULL)
    {
  return temp->key;
    }
  else
    {
      return "error";
    }
}
string& HashTable::operator [](string str){
  int h;
  Link *temp;
  if(!inTable(str)) // t["Lehigh"] = 5;
    *this += str;
  h = Hash(str).hash() % size;
  temp = table[h];
  while(temp != NULL && temp->key != str) 
    temp = temp->next;
  return temp->data;
}

const string HashTable::operator [](string str) const{
  int h;
  Link *temp;  // double x = t["Lehigh"];
  check(inTable(str),"([]const) Missing key");
  h = Hash(str).hash() % size;
  temp = table[h];
  while(temp != NULL && temp->key!=str)
    temp = temp->next;
  return temp->data;
}

HashTable& HashTable::operator +=(string k){
  return add(k, "");
}

void HashTable::remove(string str){
  int h;
  Link *tempa, *tempb;
  check(inTable(str),"(remove()) Missing key");
  h = Hash(str).hash() % size;
  if(table[h]->key==str){
    tempa = table[h];
    table[h] = table[h]->next;
  }
  else{
    tempb = table[h];
    while(tempb->next->key!= str)
      tempb = tempb->next;
    tempa = tempb->next;
    tempb->next = tempb->next->next;
  }
  delete tempa;
}

ostream& operator <<(ostream& out, const HashTable& h){
  Link *temp;
  for(int j = 0; j < h.size; j++){
    temp = h.table[j];
    if(temp != NULL)
      out << "-----------[ " << j << "]------\n";
    while(temp != NULL){
      out << *temp << endl;
      temp = temp->next;
    }
  }
  return out;
}

bool HashTable::prime(int k){
  int divisor;
  if(k < 0)
    k = -k;
  divisor = 2;
  while(divisor * divisor <= k && k % divisor != 0)
    divisor++;
  return k % divisor != 0;
}
  
void HashTable::check(bool b, string mess){
  if(!b){
    cerr << "ERROR[HashTable]: " << mess << endl;
    exit(1);
  }
}
