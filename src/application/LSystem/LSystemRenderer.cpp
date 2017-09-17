#include "LSystemRenderer.h"
#include "LSystem.h"

#include <osg/Node>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>
#include <osg/Geode>

#include <iostream>

LSystemRenderer::LSystemRenderer(LSystem const &lSys, osg::ref_ptr<osg::Group> rootNode) : m_lSystem(&lSys), m_rootNode(rootNode), m_originScale(1.0f)
{
	
	createOriginGeometry();
}


LSystemRenderer::~LSystemRenderer(void){
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

