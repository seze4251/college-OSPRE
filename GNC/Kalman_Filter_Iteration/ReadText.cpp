#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main(){
    using namespace std;

    vector<double> time;
    vector<double> X;
    vector<double> Y;
    vector<double> Z;
    vector<double> VX;
    vector<double> VY;
    vector<double> VZ;

    double number;
    int column = 1;

    ifstream file("Skyfire_J2000_7_ECI_Epsecs_Short.txt");
    if(file.is_open()){
        while(file >> number){
	    if(column == 1){
	        time.push_back(number);
		++column;
	    }
	    else if(column == 2){
		X.push_back(number);
		++column;
	    }
	    else if(column == 3){
		Y.push_back(number);
		++column;
	    }
	    else if(column == 4){
		Z.push_back(number);
		++column;
	    }
	    else if(column == 5){
		VX.push_back(number);
		++column;
	    }
	    else if(column == 6){
		VY.push_back(number);
		++column;
	    }
	    else{
		VZ.push_back(number);
		column = 1;
	    }
	}
    }

    for(int i = 0; i < X.size(); ++i){
	cout << time[i] << '\n';
    }

}