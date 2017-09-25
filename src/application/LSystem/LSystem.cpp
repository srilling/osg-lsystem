#include "LSystem.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>

LSystem::LSystem(std::string const &filename, unsigned int numIterations) : m_numIterations(numIterations)
{
	try{
		loadLSystemFromJsonFile(filename);
	}
	catch (std::string err){
		std::cerr<<err;
		exit(666);
	}


	init();
}


LSystem::~LSystem(void){
}


void LSystem::init(void){
	parseName();
	parseVariables();
	parseConstants();
	parseAxiom();
	parseRules();

}


void LSystem::generate(unsigned int numIterations){
	m_numIterations = numIterations;

	generate();

}


void LSystem::generate(void){
	m_lSysWord = m_axiom;

	for(unsigned int i=0; i<m_numIterations; i++){
		std::string res = "";

		std::istringstream iss(m_lSysWord);
		std::vector<std::string> tokens;
		
		std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(tokens));

		
		for(auto tIt = tokens.begin(); tIt != tokens.end(); tIt++){
			if(isVariable(*tIt)){
				if(m_rules.find(*tIt) != m_rules.end()){
					res.append(m_rules[*tIt]);
				}
			}
			else{
				res.append(*tIt + " ");
			}
		}



		m_lSysWord = res;
	}

	createTokensFromLSysWord();
}


void LSystem::createTokensFromLSysWord(void){
	m_lSysWordTokens.clear();

	std::vector<std::string> tokens;
	std::istringstream iss(m_lSysWord);
	std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(tokens));

	for(auto tIt = tokens.begin(); tIt != tokens.end(); tIt++){
		std::string tt = (*tIt).substr(0, 1);
		if(isConstant(tt)){
			

			size_t paraStart = tIt->find('(');
			size_t paraEnd = tIt->find(')');

			std::string params = tIt->substr(paraStart + 1, paraEnd - 2);
			std::replace(params.begin(), params.end(), ',', ' ');
			
			//DEBUG
			std::cout<<"SIE FAUCHT "<<*tIt<<"\t"<<params<<std::endl;

			std::vector<std::string> paramTokens;
			std::istringstream iss(params);
			std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(paramTokens));

			LSystemToken tok;
			tok.tokenType = tt;

			m_lSysWordTokens.push_back(tok);
		}
	}
	
}


bool LSystem::isVariable(std::string const &token){
	for(auto varIt = m_variables.begin(); varIt != m_variables.end(); varIt++){
		if(token == *varIt){
			return true;
		}
	}

	return false;
}
		

bool LSystem::isConstant(std::string const &token){
	for(auto conIt = m_constants.begin(); conIt != m_constants.end(); conIt++){
		if(token == *conIt){
			return true;
		}
	}

	return false;
}


void LSystem::parseName(void){
	m_name = m_jsonDocumentRoot["name"].asString();
}


void LSystem::parseVariables(void){
	Json::Value variables = m_jsonDocumentRoot["variables"];
	for(int i=0; i<variables.size(); i++){
		m_variables.push_back(variables[i].asString());
	}
}


void LSystem::parseConstants(void){
	Json::Value constants = m_jsonDocumentRoot["constants"];
	for(int i=0; i<constants.size(); i++){
		m_constants.push_back(constants[i].asString());
	}
}


void LSystem::parseAxiom(void){
	m_axiom = m_jsonDocumentRoot["axiom"].asString();
}


void LSystem::parseRules(void){
	Json::Value rules = m_jsonDocumentRoot["rules"];
	for(int i=0; i<rules.size(); i++){
		std::string ruleStr = rules[i].asString();
		
		//ruleStr.erase(std::remove_if(ruleStr.begin(), ruleStr.end(), [](const char& c){return c == ' ';}), ruleStr.end()); //remove all blanks
		
		size_t delimPos = ruleStr.find('=');
		std::string ruleVar = ruleStr.substr(0, delimPos - 1);
		std::string ruleProd = ruleStr.substr(delimPos + 2, ruleStr.length());

		m_rules[ruleVar] = ruleProd;

	}
}



void LSystem::loadLSystemFromJsonFile(std::string const &filename){
	Json::Reader reader;
	std::ifstream jsonConfigFileStr(filename, std::ios::in);
	
	std::cout<<"opening l-system config file "<<filename<<"..."<<std::endl;

	if(!jsonConfigFileStr.is_open()){
		std::string err = "loadLSystemFromJsonFile: opening l-system config file failed\n";
		throw err;
	}
	else{
		std::cerr<<"done."<<std::endl;
	}

	if(reader.parse(jsonConfigFileStr, m_jsonDocumentRoot)){
		std::cerr<<"config file parsing successful."<<std::endl;
	}
	else{
		//std::string err = "ERROR RenderParameterManager::loadConfigFile: EPIC FAIL parsing config file! \n" + reader.getFormattedErrorMessages();
		std::string err = "loadLSystemFromJsonFile: EPIC FAIL parsing config file! \n" + reader.getFormattedErrorMessages();
		throw err;
	}
}

