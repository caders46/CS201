#include <iostream>
using namespace std;
#include "CircularDynamicArray.cpp"








//THIS IS NOT THE MAIN PHASE1MAIN















int main() {
	CircularDynamicArray<char> C(10);
	C[0] = 'i';
	C[1] = 'a';
	C[2] = 'm';
	C[3] = 'i';
	C[4] = 'n';
	C[5] = 'p';
	C[6] = 'a';
	C[7] = 'i';
	C[8] = 'n';
	C[9] = '!';
	for (int i = 0; i < C.length(); i++) cout << C[i] << " ";  cout << endl;
	// C => "0 1 2 3 4 5 6 7 8 9"
	C.delFront();
	for (int i = 0; i < C.length(); i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8 9"
	C.delEnd();
	for (int i = 0; i < C.length(); i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8"
	C.addEnd('r');
	for (int i = 0; i < C.length(); i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8 100"
	C.delFront();
	C.addEnd('f');
	// C => "2 3 4 5 6 7 8 100 200"	

	C.addEnd('g');
	C.addEnd('h');
	// C => "2 3 4 5 6 7 8 100 200 300 400"	

	C.reverse();
	for (int i = 0; i < C.length(); i++) cout << C[i] << " ";  cout << endl;
	// C => "400 300 200 100 8 7 6 5 4 3 2"	

	C.delFront(); C.delFront(); C.delEnd();
	for (int i = 0; i < C.length(); i++) cout << C[i] << " ";  cout << endl;
	// C => "200 100 8 7 6 5 4 3"	

	C.reverse();
	for (int i = 0; i < C.length(); i++) cout << C[i] << " ";  cout << endl;
	// C => "3 4 5 6 7 8 100 200"		
	cout << "Size is " << C.length() << endl << "Capacity is " << C.capacity() << endl;

	cout << "Search is " << C.QuickSelect(3) << endl; 

	C.stableSort();

	cout << "Search is " << C.binSearch('a')	<< endl;
	cout << "Search is " << C.binSearch('z') << endl;
	cout << "Search is " << C.linearSearch('f') << endl;

	
	
	for (int i = 0; i < C.length(); i++) cout << C[i] << " ";  cout << endl;

}