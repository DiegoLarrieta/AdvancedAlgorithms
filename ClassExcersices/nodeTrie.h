#include <iostream>

using namespace std;

class nodeTrie{
  public:
  nodeTrie(char c, nodeTrie *p);
  nodeTrie* getChild(char c);
  nodeTrie* addChild(nodeTrie *n);
  void setEnd(bool e);
  bool getEnd();

  private:
  char letter;
  bool end;
  nodeTrie *parent;
  nodeTrie* child[26];
}

nodeTrie::nodeTrie(char c, nodeTrie *p){
  letter = c;
  end = false;
  parent = p;
  for(int i = 0; i<26; i++){
    child[i] = nullptr;
  }
}

nodeTrie* nodeTrie::getChild(char c){
  return child[c-'a'];
}

nodeTrie* nodeTrie::addChild(nodeTrie *n){
  child[n->letter-'a'] = n;
  return child[n->letter-'a'];
}

void nodeTrie::setEnd(bool e){
  end = e;
}

bool nodeTrie::getEnd(){
  return end;
}