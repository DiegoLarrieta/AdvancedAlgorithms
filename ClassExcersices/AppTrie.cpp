#include<iostream>

using namespace std;
#include "trie.h"


int main(){
  int n , q;
  string s;
  trie *miTrie;
  cin>>n;
  for(int i =0;i<n;i++){
    cin>>s;
    miTrie.insert(s);

  }
  cout<<"==================";
  cin>>q;
  for(int i=0;i<q;i++){
    if(miTrie->search(s)){
      cout<<"Si esta la palabra en el trie"<<endl;
    }
    else{
      cout<<"No esta la palabra en el tire"<<endl;
    }
  }
  return 0;
}