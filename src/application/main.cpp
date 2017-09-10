#include <iostream>
#include <string>
#include <fstream>
#include "JsonCpp/json/json.h"


Json::Value loadLSystemFromJsonFile(std::string const &filename){
	Json::Reader reader;
	std::ifstream jsonConfigFileStr(filename, std::ios::in);
	
	std::cout<<"opening l-system config file "<<filename<<"..."<<std::endl;

	if(!jsonConfigFileStr.is_open()){
		std::string err = "loadLSystemFromJsonFile: opening render config file failed\n";
		throw err;
	}
	else{
		std::cerr<<"done."<<std::endl;
	}

	Json::Value jsonDocumentRoot;

	if(reader.parse(jsonConfigFileStr, jsonDocumentRoot)){
		std::cerr<<"config file parsing successful."<<std::endl;
	}
	else{
		//std::string err = "ERROR RenderParameterManager::loadConfigFile: EPIC FAIL parsing config file! \n" + reader.getFormattedErrorMessages();
		std::string err = "loadLSystemFromJsonFile: EPIC FAIL parsing config file! \n" + reader.getFormattedErrorMessages();
		throw err;
	}


	return jsonDocumentRoot;

}


int main(int argc, char **argv){
	std::cout<<"* * * l-system test program mk 0.0 * * * "<<std::endl;

	Json::Value documentRoot = loadLSystemFromJsonFile("./test.json");

	//std::cout<<documentRoot;

	
	Json::Value variables = documentRoot["variables"];
	for(int i=0; i<variables.size(); i++){
		std::cout<<"SIE FAUCHT "<<variables[i].asString()<<std::endl;
	}

	

	return 0;

}