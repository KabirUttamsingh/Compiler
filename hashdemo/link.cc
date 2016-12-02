#include "link.h"

Link::Link(const char *k, double d, Link* nx):key(k),data(d),next(nx){}

Link::Link(const Link& t):key(t.key),data(t.data),next(t.next){}

ostream & operator<<(ostream& out,const Link& x){
  out << "("<< x.key << ", " << x.data << ")";
  return out;
}

/*  Some simple tests of the class Link */
void show(Link *t){
  while(t != NULL){
    cout << "-->" << *t;
    t = t->next;
  }
  cout<<endl;
}

