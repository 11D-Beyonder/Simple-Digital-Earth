#pragma once

#include <osgDB/ReadFile>
#include <osgViewer/api/win32/GraphicsWindowWin32>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/Sky>
#include <osgEarthAnnotation/PlaceNode>
#include <osgEarth/ImageLayer>
#include <osgEarthSymbology/Style>
#include <osgEarthUtil/Controls>
#include "CViewInfoEventHandler.h"


class COSGObject
{
public:
	COSGObject(HWND _hWnd, 
		CMFCRibbonEdit* _longitudeEdit, 
		CMFCRibbonEdit* _latitudeEdit, 
		CMFCRibbonEdit* _altitudeEdit,
		CMFCRibbonEdit* _viewLongitudeEdit,
		CMFCRibbonEdit* _viewLatitudeEdit,
		CMFCRibbonEdit* _viewZEdit,
		CMFCRibbonEdit* _viewHeadingEdit,
		CMFCRibbonEdit* _viewPitchEdit,
		CMFCRibbonEdit* _viewRangeEdit);
	~COSGObject();
	void InitOSG();
	static void Render(void* ptr);
	osgViewer::Viewer* getViewer();
	void setProvinceBoundaryOpacity(float opacity);
	float getProvinceBoundaryOpacity();
	void setCountryBoundaryOpacity(float opacity);
	float getCountryBoundaryOpacity();

	void enableNationFlag(BOOL flag);
	void enableProvinceBoundary(bool flag);
	void enableCountryBoundary(bool flag);
	void enableContour(bool flag);
	void enableDetail(bool flag);
	void enableGlobe(bool flag);
	void enableAnimal(BOOL flag);

	void flyTo(double longitude, double latitude, double height, double z = 0.0, double heading = 0.0, double pitch = -90.0);
private:
	/// <summary>
	/// 显示窗口的句柄
	/// </summary>
	HWND hWnd;
	/// <summary>
	/// 查看器
	/// </summary>
	osgViewer::Viewer* viewer;
	/// <summary>
	/// 场景根节点
	/// </summary>
	osg::ref_ptr<osg::Group> sceneRoot;
	/// <summary>
	/// 地图节点
	/// </summary>
	osg::ref_ptr<osgEarth::MapNode> mapNode;
	/// <summary>
	/// osgEarth控制器
	/// </summary>
	osg::ref_ptr<osgEarth::Util::EarthManipulator> earthManipulator;
	/// <summary>
	/// 省界线的图层
	/// </summary>
	osg::ref_ptr<osgEarth::ImageLayer> provinceBoundaryLayer;
	/// <summary>
	/// 国界线的图层
	/// </summary>
	osg::ref_ptr<osgEarth::ImageLayer> countryBoundaryLayer;
	/// <summary>
	/// 等高线图层
	/// </summary>
	osg::ref_ptr<osgEarth::ImageLayer> contourLayer;
	/// <summary>
	/// 局部高清纹理
	/// </summary>
	osg::ref_ptr<osgEarth::ImageLayer> detailLayer;
	/// <summary>
	/// 全局纹理
	/// </summary>
	osg::ref_ptr<osgEarth::ImageLayer> globeLayer;
	/// <summary>
	/// 国旗图标节点
	/// </summary>
	osg::ref_ptr<osg::Group> nationFlag;
	/// <summary>
	/// 初始化天空
	/// </summary>
	void initSky();
	void initLayer();
	void initNationFlag();
	void initManipulator();
	void initSceneGraph();
	void initCameraConfig();
	void initOsgEarth();
	void initSpaceship();

	CViewInfoEventHandler* infoEvent;
	CMFCRibbonEdit* longitudeEdit;
	CMFCRibbonEdit* latitudeEdit;
	CMFCRibbonEdit* altitudeEdit;
	CMFCRibbonEdit* viewLongitudeEdit;
	CMFCRibbonEdit* viewLatitudeEdit;
	CMFCRibbonEdit* viewZEdit;
	CMFCRibbonEdit* viewHeadingEdit;
	CMFCRibbonEdit* viewPitchEdit;
	CMFCRibbonEdit* viewRangetEdit;

	osg::ref_ptr<osg::MatrixTransform>scenicSpot;
};