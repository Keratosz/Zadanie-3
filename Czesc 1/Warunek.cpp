#include <iostream>
#include<string>
#include<cstdlib>

using namespace std;

int main(int argc, char *argv[]) {
	if( argc > 6 ){
		int Tab[argc-1];
		for(int i=0; i<argc-1; i++) Tab[i]=atoi(argv[i+1]);
		if( Tab[0] > 0 && ( Tab[0] > Tab[1] || Tab[2] < Tab[3] ) && Tab[argc-2] < Tab[argc-3] && Tab[argc-4] % 2 == 1 && Tab[argc-5] > 0 && Tab[argc-6] % 3 == 0) {
			 cout<<"1"<<endl;
			 return 1;
		}
		else {
			cout<<"0"<<endl; 
			return 0;
		}
			 
	}
	else
	cout<<"Podano bledna liczbe argumentow!"<<endl;	

}
