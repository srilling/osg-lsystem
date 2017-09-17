#include <iostream>
#include <string>
#include <fstream>

#include "JsonCpp/json/json.h"

#include "LSystem/LSystem.h"
#include "LSystem/LSystemRenderer.h"

#include <osgViewer/Viewer>


int main(int argc, char **argv){
	std::cout<<"* * * l-system test program mk 0.0 * * * "<<std::endl;

	osgViewer::Viewer viewer;
	viewer.setUpViewInWindow(100, 100, 800, 600);
	viewer.getCamera()->setClearColor(osg::Vec4(0.8, 1.0, 1.0, 1.0));
	viewer.realize(); 

	LSystem lSystem("./test.json");

	//DEBUG
	std::cout<<lSystem<<std::endl;

	lSystem.generate(10);

	osg::ref_ptr<osg::Group> rootNode = new osg::Group();
	viewer.setSceneData(rootNode);


	LSystemRenderer lSystemRenderer(lSystem, rootNode);

	
	
	
	return viewer.run();

	

}