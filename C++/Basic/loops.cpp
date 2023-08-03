#include <iostream>
 
using namespace std; // So the program can see cout and endl
 
int main()
{
    for ( int x = 0; x < 5; x++ ) {   
        cout<< x <<"-";
    }
    cout<<"\n\n";

    int x = 0;
    while ( x < 5 ) {
        cout<< x <<"-";
        x++;             
    }
    cout<<"\n\n";

    do {
        // "Hello, world!" is printed at least one time
        //  even though the condition is false
        cout<<"Hello, world!\n";
    } while ( x != 5 );

    cin.get();
}