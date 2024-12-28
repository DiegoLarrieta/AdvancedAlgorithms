#include <iostream>

using namespace std;
typedef unsigned char uchar;


uchar add(uchar mask, int pos){
	return (mask | (1 << pos));
}

uchar remove(uchar mask, int pos){
	return (mask & ~(1 << pos));
}

bool test(uchar mask, int pos){
	return ((mask & (1 << pos)) != 0);
}

void print (uchar mask){
	for (int i=7; i>=0; i--){
		cout << ((test(mask,i)) ? "1" : "0");
	}
	cout << endl;
}


int main(){
/*	long dato;
	cin >> dato;
	dato = (dato << 2);
	cout << dato << endl;
	*/
	int pos;
	uchar b = 11;
	print(b);
	cout << "Cuál bit prendo? ";
	cin >> pos;
	b = add(b, pos);
	print(b);
	cout << "Cuál bit apago?  ";
	cin >> pos;
	b = remove(b, pos);
	print(b);
	uchar b2 = 27;
	print(b2);
	b2 = (b2 << 4);
	print(b2);
	b2 = (b2 >> 5);
	print(b2);
	int val;
	cin >> val;
	cout << (val << 2) << endl;
	return 0;
}