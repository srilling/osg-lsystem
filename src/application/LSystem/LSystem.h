#ifndef LSYSTEM_H
#define LSYSTEM_H

#include <string>
#include <vector>
#include <map>

#include "../JsonCpp/json/json.h"

class LSystem{

	//------------CONSTRUCTORS & DESTRUCTOR-----------------
	public:
		LSystem(std::string const &filename);
		~LSystem(void);

	//------------MEMBER VARIABLES--------------------------
	private:
		Json::Value m_jsonDocumentRoot;

		std::string m_name;
		std::vector<std::string> m_variables;
		std::vector<std::string> m_constants;
		std::string m_axiom;
		std::map<std::string, std::string> m_rules;

	//------------MEMBER FUNCTIONS--------------------------
	private:
		void loadLSystemFromJsonFile(std::string const &filename);

		void parseName(void);
		void parseVariables(void);
		void parseConstants(void);
		void parseAxiom(void);
		void parseRules(void);


		void init(void);

	public:
		std::string const & getName(void) const const {return m_name;}
		std::vector<std::string> const &getVariables(void) const{return m_variables;}
		std::vector<std::string> const &getConstants(void) const{return m_constants;}
		std::string const & getAxiom(void) const {return m_axiom;}
		std::map<std::string, std::string> const & getRules(void) const { return m_rules;}
};


inline std::ostream &operator<<(std::ostream &os, LSystem const &lSys) { 
    os << "L-System: " + lSys.getName()<<std::endl;
	
	os << "variables: "<<std::endl;
	for(int i=0; i<lSys.getVariables().size(); i++){
		os<<"\t"<<lSys.getVariables()[i]<<std::endl;
	}

	os << "constants: "<<std::endl;
	for(int i=0; i<lSys.getVariables().size(); i++){
		os<<"\t"<<lSys.getConstants()[i]<<std::endl;
	}

	os << "axiom: " + lSys.getAxiom()<<std::endl;
	os << "rules: "<<std::endl;
	for(auto rIt = lSys.getRules().cbegin(); rIt != lSys.getRules().cend(); rIt++){
		os<<"\t"<<rIt->first<<" -> "<<rIt->second<<std::endl;
	}


	return os;
}

#endif //LSYSTEM_H
