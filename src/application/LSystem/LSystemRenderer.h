#ifndef LSYSTEMRENDERER_H
#define LSYSTEMRENDERER_H

#include <osg/ref_ptr>

class LSystem;

namespace osg{
	class Node;
	class Group;
	class PositionAttitudeTransform;
}

class LSystemRenderer{

	//------------CONSTRUCTORS & DESTRUCTOR-----------------
	public:
		LSystemRenderer(LSystem const &lSys, osg::ref_ptr<osg::Group> rootNode);
		~LSystemRenderer(void);

	//------------MEMBER VARIABLES--------------------------
	private:
		LSystem const *m_lSystem;

		osg::ref_ptr<osg::Group> m_rootNode;

		osg::ref_ptr<osg::PositionAttitudeTransform> m_originVisTransform;
		float m_originScale;
	//------------MEMBER FUNCTIONS--------------------------
	private:
		void createOriginGeometry(void);

	public:
};

#endif //LSYSTEMRENDERER_H
