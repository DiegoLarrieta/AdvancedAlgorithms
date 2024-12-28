#include "nodeTrie.h"


class trie{
  public:
    trie();
    void insert(string word);
    bool search(string word);
  private:
    nodeTrie *root;

};

trie::trie(){
  root = new nodeTrie('\0', nullptr);
}

void trie::insert(string word){
  nodeTrie *current = root;
  for(int i=0 ; i<word.size(); i++){
    char c = word[i];
    nodeTrie *sub = current -> getChild(c);
    if(sub != nullptr){
      current = sub;
    }
    else{
      current -> addChild(new nodeTrie(c, current));
      current = current -> getChild(c);
    }
  }
  current ->setEnd(true);
}

bool trie::search(string word){
  nodeTrie *current = root;
  for(int i=0;i<word.size(); i++){
    char c = word[i];
    nodeTrie *sub = current -> getChild(c);
    if(sub == nullptr){
      return false;
    }
    current = sub;
  }
  return current ->getEnd();
}