#include "LSystemRenderer.h"
#include "LSystem.h"

#include <osg/Node>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/LineWidth>
#include <osg/Material>

#include <iostream>

LSystemRenderer::LSystemRenderer(LSystem const &lSys, osg::ref_ptr<osg::Group> rootNode) : 
	m_lSystem(&lSys), 
	m_rootNode(rootNode), 
	m_originScale(0.666f)
{
	
	createOriginGeometry();
	createGroundPlane();
}


LSystemRenderer::~LSystemRenderer(void){
}


void LSystemRenderer::createPlantModel(void){
	osg::ref_ptr<osg::Geode> trunk = createTrunkGeometry();

	m_rootNode->addChild(trunk);
}


osg::ref_ptr<osg::Geode> LSystemRenderer::createTrunkGeometry(void){
	
	float height = 10.0;
	float rad = 0.05 * height;

	osg::Cylinder *cylinderZ = new osg::Cylinder(osg::Vec3(0.0, 0.0, 0.5 * height), rad, height); 
	osg::ShapeDrawable *cylinderZDrawable = new osg::ShapeDrawable(cylinderZ);

	osg::Geode* trunkGeode = new osg::Geode;
	trunkGeode ->addDrawable(cylinderZDrawable);
	
	osg::ref_ptr<osg::Material> material = new osg::Material();
	material->setDiffuse(osg::Material::FRONT,  osg::Vec4(0.6, 0.4, 0.0, 1.0));
	material->setAmbient(osg::Material::FRONT,  osg::Vec4(0.2, 0.15, 0.0, 1.0));
	
	trunkGeode ->getOrCreateStateSet()->setAttribute(material);


	return trunkGeode;
}


osg::ref_ptr<osg::Geode> LSystemRenderer::createLeafGeometry(void){
	osg::Geode* leafGeode = new osg::Geode;


	return leafGeode;
}


void LSystemRenderer::createOriginGeometry(void){

	m_originVisTransform = new osg::PositionAttitudeTransform();
	
	//double s = 0.05;
	
	m_originVisTransform->setScale(osg::Vec3d(m_originScale, m_originScale, m_originScale));
	       
	float height = 1.0f;
	float rad = 0.1f;
	       
	//- - - x-Axis - - -
	osg::Cylinder *cylinderX = new osg::Cylinder(osg::Vec3(0.5 * height, 0.0, 0.0), rad, height); 
	cylinderX->setRotation(osg::Quat(osg::PI_2, osg::Vec3(0.0, 1.0, 0.0)));
	osg::ShapeDrawable *cylinderXDrawable = new osg::ShapeDrawable(cylinderX);
	cylinderXDrawable->setColor(osg::Vec4(1.0, 0.0, 0.0, 1.0));
	
	osg::Geode* cylXGeode = new osg::Geode;
	cylXGeode->addDrawable(cylinderXDrawable);
	
	cylXGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	m_originVisTransform->addChild(cylXGeode);
	
	
	//- - - y-Axis - - -
	osg::Cylinder *cylinderY = new osg::Cylinder(osg::Vec3(0.0, 0.5 * height, 0.0), rad, height); 
	cylinderY->setRotation(osg::Quat(osg::PI_2, osg::Vec3(1.0, 0.0, 0.0)));
	osg::ShapeDrawable *cylinderYDrawable = new osg::ShapeDrawable(cylinderY);
	cylinderYDrawable->setColor(osg::Vec4(0.0, 1.0, 0.0, 1.0));
	
	osg::Geode* cylYGeode = new osg::Geode;
	cylYGeode->addDrawable(cylinderYDrawable);
	
	cylYGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	
	m_originVisTransform->addChild(cylYGeode);
	
	
	//- - - z-Axis - - -
	osg::Cylinder *cylinderZ = new osg::Cylinder(osg::Vec3(0.0, 0.0, 0.5 * height), rad, height); 
	//cylinderZ->setRotation(osg::Quat(osg::PI_2, osg::Vec3(1.0, 0.0, 0.0)));
	osg::ShapeDrawable *cylinderZDrawable = new osg::ShapeDrawable(cylinderZ);
	cylinderZDrawable->setColor(osg::Vec4(0.0, 0.0, 1.0, 1.0));
	
	osg::Geode* cylZGeode = new osg::Geode;
	cylZGeode->addDrawable(cylinderZDrawable);
	
	cylZGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	       
	m_originVisTransform->addChild(cylZGeode);
	
	m_rootNode->addChild(m_originVisTransform);

	

}


void LSystemRenderer::createGroundPlane(void){
	m_groundPlaneTransform = new osg::PositionAttitudeTransform();
	//m_groundPlaneTransform->setPosition(osg::Vec3(0.0, 0.0, m_boundingBoxMinExt.z() + m_modelTransform->getPosition().z()));

	//m_groundPlaneTransform->setPosition(osg::Vec3(0.0, 0.0, m_modelTransform->getPosition().z() * -2.0));
	

	m_groundPlaneGeode = new osg::Geode();
	m_groundPlaneTransform->addChild(m_groundPlaneGeode);
	m_rootNode->addChild(m_groundPlaneTransform);

	/*float xDim = fabs(m_boundingBoxMaxExt.x() - m_boundingBoxMinExt.x());
	float yDim = fabs(m_boundingBoxMaxExt.y() - m_boundingBoxMinExt.y());*/

	float xDim = 10.0f;
	float yDim = 10.0f;

	float maxDim = std::max<float>(xDim, yDim);
	float step = 0.25f * maxDim;
	/*float xStep = 0.1f * xDim;
	float yStep = 0.1f * yDim;*/

	/*float xExtHalf = 7.0f * xDim;
	float yExtHalf = 7.0f * yDim;*/

	float extHalf = 7.0 * maxDim;

	/*int numLinesX = (2 * xExtHalf) / step;
	int numLinesY = (2 * yExtHalf) / step;*/

	int numLinesX = (2 * extHalf) / step;
	int numLinesY = (2 * extHalf) / step;

	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array();
	osg::ref_ptr<osg::DrawElementsUShort> indices = new osg::DrawElementsUShort(osg::PrimitiveSet::LINES);

	unsigned short index = 0;

	//float xPos = -xExtHalf;
	float xPos = -extHalf;
	for(int i=0; i<numLinesX; i++){
		/*vertices->push_back(osg::Vec3(xPos, -yExtHalf, 0.0));
		vertices->push_back(osg::Vec3(xPos,  yExtHalf, 0.0));*/

		vertices->push_back(osg::Vec3(xPos, -extHalf, 0.0));
		vertices->push_back(osg::Vec3(xPos,  extHalf, 0.0));
		
		indices->push_back(index++);
		indices->push_back(index++);

		xPos += step;
	}

	//float yPos = -yExtHalf;
	float yPos = -extHalf;
	for(int i=0; i<numLinesY; i++){
		/*vertices->push_back(osg::Vec3(-xExtHalf, yPos, 0.0));
		vertices->push_back(osg::Vec3( xExtHalf, yPos, 0.0));*/

		vertices->push_back(osg::Vec3(-extHalf, yPos, 0.0));
		vertices->push_back(osg::Vec3( extHalf, yPos, 0.0));
		
		indices->push_back(index++);
		indices->push_back(index++);

		yPos += step;
	}

	colors->push_back(osg::Vec4(1.0, 1.0, 1.0, 1.0));
	//colors->push_back(osg::Vec4(0.0, 0.0, 0.0, 1.0));

	osg::ref_ptr<osg::Geometry> gridGeom = new osg::Geometry();
	gridGeom->setVertexArray(vertices);
	gridGeom->setColorArray(colors);
	gridGeom->setColorBinding(osg::Geometry::BIND_OVERALL);
	gridGeom->addPrimitiveSet(indices);

	m_groundPlaneGeode->addDrawable(gridGeom);
	m_groundPlaneGeode->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF);

	osg::ref_ptr<osg::LineWidth> lineWidth = new osg::LineWidth();
	lineWidth->setWidth(2.3f);
	m_groundPlaneGeode->getOrCreateStateSet()->setAttribute(lineWidth, osg::StateAttribute::ON);

	/*osg::ref_ptr<osg::Fog> fog = new osg::Fog();
	fog->setMode(osg::Fog::LINEAR);
	fog->setColor(STLProcessing::fabbOneGrey);
	
	try{
		m_fogDensity = RenderParameterManager::instance().getFogParameter("fog_density").at(0);
		m_fogStartMultiplier = RenderParameterManager::instance().getFogParameter("fog_start_multiplier").at(0);
		m_fogEndMultiplier = RenderParameterManager::instance().getFogParameter("fog_end_multiplier").at(0);
	}
	catch(std::string err){
		std::cout<<err<<std::endl;
	}

	fog->setDensity(m_fogDensity);
	fog->setStart(m_fogStartMultiplier * std::max<float>(xDim, yDim));
	fog->setEnd(m_fogEndMultiplier * std::max<float>(xDim, yDim));

	fog->setUseRadialFog(true);

	fog->setFogCoordinateSource(osg::Fog::FRAGMENT_DEPTH);
	m_groundPlaneGeode->getOrCreateStateSet()->setAttribute( fog, osg::StateAttribute::ON ); 
	m_groundPlaneGeode->getOrCreateStateSet()->setMode( GL_FOG, osg::StateAttribute::ON );*/

	/*m_sceneRoot->getOrCreateStateSet()->setAttribute( fog, osg::StateAttribute::ON ); 
	m_sceneRoot->getOrCreateStateSet()->setMode( GL_FOG, osg::StateAttribute::ON );*/

	
}