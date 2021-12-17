#include "pch.h"
#include "COSGObject.h"

COSGObject::COSGObject
(
	HWND _hWnd, 
	CMFCRibbonEdit* _longitudeEdit, 
	CMFCRibbonEdit* _latitudeEdit, 
	CMFCRibbonEdit* _altitudeEdit,
	CMFCRibbonEdit* _viewLongitudeEdit,
	CMFCRibbonEdit* _viewLatitudeEdit,
	CMFCRibbonEdit* _viewZEdit,
	CMFCRibbonEdit* _viewHeadingEdit,
	CMFCRibbonEdit* _viewPitchEdit,
	CMFCRibbonEdit* _viewRangeEdit
)
{
	hWnd = _hWnd;
	infoEvent = nullptr;
	longitudeEdit = _longitudeEdit;
	latitudeEdit = _latitudeEdit;
	altitudeEdit = _altitudeEdit;
	viewLongitudeEdit = _viewLongitudeEdit;
	viewLatitudeEdit = _viewLatitudeEdit;
	viewZEdit = _viewZEdit;
	viewHeadingEdit = _viewHeadingEdit;
	viewPitchEdit = _viewPitchEdit;
	viewRangetEdit = _viewRangeEdit;
}


COSGObject::~COSGObject(void)
{
}

void COSGObject::InitOSG()
{
	initSceneGraph();
	initCameraConfig();
	initOsgEarth();
}

void COSGObject::initSceneGraph()
{
	// �������ڵ����
	sceneRoot = new osg::Group;
	// ��ȡӰ��
	osg::ref_ptr<osg::Node> mp = osgDB::readNodeFile("./earthfile/DigitalMap.earth");
	// ����ӽڵ�
	sceneRoot->addChild(mp);
	// ����������ת��
	mapNode = dynamic_cast<osgEarth::MapNode*>(mp.get());
}

void COSGObject::initCameraConfig()
{
	RECT rect;
	// �����鿴��
	viewer = new osgViewer::Viewer;
	// ��ȡ���ڵľ�������
	::GetWindowRect(hWnd, &rect);
	// ��������������
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	// ��ȡwindata
	osg::ref_ptr<osg::Referenced> windata = new osgViewer::GraphicsWindowWin32::WindowData(hWnd);
	// ������ʾ�ĸ�������
	traits->x = 0;
	traits->y = 0;
	traits->width = rect.right - rect.left;
	traits->height = rect.bottom - rect.top;
	traits->windowDecoration = false;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;
	traits->setInheritedWindowPixelFormat = true;
	traits->inheritedWindowData = windata;
	
	// ����������
	osg::GraphicsContext* gc = osg::GraphicsContext::createGraphicsContext(traits);
	// ��������ͷ
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setGraphicsContext(gc);
	// �����ӿ�
	camera->setViewport(new osg::Viewport(traits->x, traits->y, traits->width, traits->height));
	// �����ӽ�
	camera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(traits->width) / static_cast<double>(traits->height), 1.0, 1000.0);
	// ��������ͷ
	viewer->setCamera(camera);
	//viewer->setCameraManipulator(new osgGA::TrackballManipulator);
	// ���ó���
	viewer->setSceneData(sceneRoot);
	// ����ڲ������߳�
	viewer->realize();
}

void COSGObject::Render(void* ptr)
{
	COSGObject* osg = (COSGObject*)ptr;
	osgViewer::Viewer* viewer = osg->getViewer();
	while (!viewer->done())
	{
		viewer->frame();
	}
	_endthread();
}

osgViewer::Viewer* COSGObject::getViewer()
{
	return viewer;
}

void COSGObject::initOsgEarth()
{
	
	initManipulator();
	initSky();
	initLayer();
	initNationFlag();
	initSpaceship();

	if (nullptr == infoEvent)
	{
		infoEvent = new CViewInfoEventHandler(
			longitudeEdit, latitudeEdit, altitudeEdit,
			viewLongitudeEdit, viewLatitudeEdit, viewZEdit,
			viewHeadingEdit, viewPitchEdit, viewRangetEdit);
	}
	viewer->addEventHandler(infoEvent);
}

void COSGObject::setProvinceBoundaryOpacity(float opacity)
{
	if (provinceBoundaryLayer.valid())
	{
		provinceBoundaryLayer->setOpacity(opacity);
	}
}
float COSGObject::getProvinceBoundaryOpacity()
{
	if (provinceBoundaryLayer.valid())
	{
		return provinceBoundaryLayer->getOpacity();
	}
	else
	{
		return -1.0;
	}
}
void COSGObject::setCountryBoundaryOpacity(float opacity)
{
	if (countryBoundaryLayer.valid())
	{
		countryBoundaryLayer->setOpacity(opacity);
	}
}
float COSGObject::getCountryBoundaryOpacity() 
{
	if (countryBoundaryLayer.valid())
	{
		return countryBoundaryLayer->getOpacity();
	}
	else
	{
		return -1.0;
	}
}

void COSGObject::initSky()
{
	// ��ʼ�����
	osg::ref_ptr<osgEarth::Util::SkyNode> skyNode = osgEarth::Util::SkyNode::create(mapNode);
	skyNode->setDateTime(osgEarth::DateTime(2021, 12, 11, 15));
	skyNode->attach(viewer, 1);
	skyNode->setStarsVisible(true);
	skyNode->setSunVisible(true);
	sceneRoot->addChild(skyNode);
}
void COSGObject::initLayer()
{
	// ��earth�ļ��и���name���ͼ��
	globeLayer = mapNode->getMap()->getLayerByName<osgEarth::ImageLayer>("globeImage");
	provinceBoundaryLayer = mapNode->getMap()->getLayerByName<osgEarth::ImageLayer>("provinceBoundary");
	countryBoundaryLayer = mapNode->getMap()->getLayerByName<osgEarth::ImageLayer>("countryBoundary");
	contourLayer = mapNode->getMap()->getLayerByName<osgEarth::ImageLayer>("contour");
	detailLayer = mapNode->getMap()->getLayerByName<osgEarth::ImageLayer>("detail");
}
void COSGObject::initNationFlag()
{
	// ��ʼ���ص��ʶ
	nationFlag = new osg::Group;
	sceneRoot->addChild(nationFlag);
	osg::Image* chinaIcon = osgDB::readImageFile("data/label/chinaYES.png");
	osg::ref_ptr<osgEarth::Annotation::PlaceNode> placeNode = new osgEarth::Annotation::PlaceNode;
	placeNode->setIconImage(chinaIcon);
	placeNode->setPosition(osgEarth::GeoPoint(mapNode->getMapSRS()->getGeographicSRS(), 110, 34));
	nationFlag->addChild(placeNode.get());
}
void COSGObject::initManipulator()
{
	// ��ʼ��������
	earthManipulator = new osgEarth::Util::EarthManipulator;
	if (mapNode.valid())
	{
		earthManipulator->setNode(mapNode);
	}
	earthManipulator->getSettings()->setArcViewpointTransitions(true);
	viewer->setCameraManipulator(earthManipulator);
	earthManipulator->setViewpoint(osgEarth::Viewpoint(nullptr, 112.44, 33.75, 404.06, -3.55, -84.59, 22935594.99), 5);
}
void COSGObject::initSpaceship()
{

	osg::Matrixd matrix;
	mapNode->getMapSRS()->getGeocentricSRS()->getEllipsoid()->computeLocalToWorldTransformFromLatLongHeight(osg::DegreesToRadians(30.58), osg::DegreesToRadians(119.99), 10, matrix);
	matrix.preMult(osg::Matrixd::scale(osg::Vec3d(29, 25, 25)));
	scenicSpot = new osg::MatrixTransform;
	scenicSpot->setMatrix(matrix);
	osg::ref_ptr<osg::StateSet> state = scenicSpot->getOrCreateStateSet();
	state->setMode(GL_LIGHTING, osg::StateAttribute::ON);
	state->setMode(GL_LIGHT0, osg::StateAttribute::ON);
	state->setMode(GL_LIGHT1, osg::StateAttribute::ON);
	osg::ref_ptr<osg::LightSource> lightSource0 = new osg::LightSource;
	osg::ref_ptr<osg::Light>light0 = new osg::Light;
	light0->setLightNum(0);
	light0->setDirection(osg::Vec3(0, -1, 0));
	light0->setPosition(osg::Vec4(-4817129, -5391926, -141700, 0));
	light0->setDiffuse(osg::Vec4(1.0, 1.0, 0.8, 1));
	lightSource0->setLight(light0);
	osg::ref_ptr<osg::LightSource> lightSource1 = new osg::LightSource;
	osg::ref_ptr<osg::Light>light1 = new osg::Light;
	light1->setLightNum(0);
	light1->setDirection(osg::Vec3(0, 1, 0));
	light1->setPosition(osg::Vec4(-4817129, 5391926, -141700, 0));
	light1->setDiffuse(osg::Vec4(1.0, 1.0, 0.9, 1));
	lightSource1->setLight(light1);

	osg::ref_ptr<osg::Node>cow = osgDB::readNodeFile("./data/model/cow.osg");
	cow->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
	scenicSpot->addChild(cow);
	scenicSpot->addChild(lightSource0);
	scenicSpot->addChild(lightSource1);
	sceneRoot->addChild(scenicSpot);
}

void COSGObject::enableNationFlag(BOOL flag)
{

	nationFlag->getChild(0)->setNodeMask(flag);
}
void COSGObject::enableProvinceBoundary(bool flag)
{
	provinceBoundaryLayer->setVisible(flag);
}
void COSGObject::enableCountryBoundary(bool flag)
{
	countryBoundaryLayer->setVisible(flag);
}
void COSGObject::enableContour(bool flag)
{
	contourLayer->setVisible(flag);
}
void COSGObject::enableDetail(bool flag)
{
	detailLayer->setVisible(flag);
}
void COSGObject::enableGlobe(bool flag)
{
	globeLayer->setVisible(flag);
}
void COSGObject::enableAnimal(BOOL flag)
{
	scenicSpot->setNodeMask(flag);
}

void COSGObject::flyTo(double longitude, double latitude, double height, double z, double heading, double pitch)
{
	earthManipulator->setViewpoint(osgEarth::Viewpoint(nullptr, longitude, latitude, z, heading, pitch, height), 3.1415926535);
}