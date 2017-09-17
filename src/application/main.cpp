#include <iostream>
#include <string>
#include <fstream>
#include "JsonCpp/json/json.h"
#include "LSystem/LSystem.h"




int main(int argc, char **argv){
	std::cout<<"* * * l-system test program mk 0.0 * * * "<<std::endl;


	LSystem lSystem("./test.json");

	std::cout<<lSystem<<std::endl;
	
	return 0;

}