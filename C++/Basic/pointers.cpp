#include <iostream>
 
using namespace std;
 
int main()
{ 
  int x;            // A normal integer
  int *p = new int;           // A pointer to an integer
  int *y = new int;
 
  p = &x;           // Read it, "assign the address of x to p"
  cin>> x;          // Put a value in x, we could also use *p here
  cin.ignore();
  y = p;
  cout<< *p <<"\n" << *y << "\n"; // Note the use of the * to get the value
  cout<< p <<"\n" << y << "\n";
  cin.get();
}