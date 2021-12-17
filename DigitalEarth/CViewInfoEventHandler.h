#pragma once
#include <osgGA/GUIEventHandler>
#include <osgEarth/MapNode>
#include <osg/CoordinateSystemNode>
#include <osgEarth/TerrainEngineNode>
#include <osgViewer/Viewer>

class CViewInfoEventHandler :
	public osgGA::GUIEventHandler
{
public:
	CViewInfoEventHandler
	(
		CMFCRibbonEdit* _longitudeEdit, 
		CMFCRibbonEdit* _latitudeEdit,
		CMFCRibbonEdit* _altitudeEdit,
		CMFCRibbonEdit* _viewLongitudeEdit,
		CMFCRibbonEdit* _viewLatitudeEdit,
		CMFCRibbonEdit* _viewZEdit,
		CMFCRibbonEdit* _viewHeadingEdit,
		CMFCRibbonEdit* viewPitchEdit,
		CMFCRibbonEdit* _viewRangeEdit
	);
	~CViewInfoEventHandler();
	bool handle(const osgGA::GUIEventAdapter& eventAdapter, osgGA::GUIActionAdapter& actionAdapter);
private:
	CMFCRibbonEdit* longitudeEdit;
	CMFCRibbonEdit* latitudeEdit;
	CMFCRibbonEdit* altitudeEdit;
	CMFCRibbonEdit* viewLongitudeEdit;
	CMFCRibbonEdit* viewLatitudeEdit;
	CMFCRibbonEdit* viewZEdit;
	CMFCRibbonEdit* viewHeadingEdit;
	CMFCRibbonEdit* viewPitchEdit;
	CMFCRibbonEdit* viewRangeEdit;
};
