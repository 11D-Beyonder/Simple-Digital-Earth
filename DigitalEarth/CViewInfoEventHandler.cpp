#include "pch.h"
#include "COSGObject.h"

CViewInfoEventHandler::CViewInfoEventHandler
(
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
	longitudeEdit = _longitudeEdit;
	latitudeEdit = _latitudeEdit;
	altitudeEdit = _altitudeEdit;

	viewLongitudeEdit = _viewLongitudeEdit;
	viewLatitudeEdit = _viewLatitudeEdit;
	viewZEdit = _viewZEdit;
	viewHeadingEdit = _viewHeadingEdit;
	viewPitchEdit = _viewPitchEdit;
	viewRangeEdit = _viewRangeEdit;
}
CViewInfoEventHandler::~CViewInfoEventHandler()
{
}

bool CViewInfoEventHandler::handle
(
	const osgGA::GUIEventAdapter& eventAdapter, 
	osgGA::GUIActionAdapter& actionAdapter
)
{
	osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&actionAdapter);
	if (nullptr != viewer)
	{
		if (eventAdapter.getEventType() & osgGA::GUIEventAdapter::FRAME)
		{
			osgUtil::LineSegmentIntersector::Intersections res;
			// 求交点
			if (viewer->computeIntersections(eventAdapter, res))
			{
				osgUtil::LineSegmentIntersector::Intersection first = *res.begin();
				// 取出交点坐标
				osg::Vec3d point = first.getWorldIntersectPoint();
				double latitude, longitude, altitude;
				// 转经纬度
				osg::ref_ptr<osg::EllipsoidModel> ellipsoidModel = new osg::EllipsoidModel;
				ellipsoidModel->convertXYZToLatLongHeight(point.x(), point.y(), point.z(), latitude, longitude, altitude);
				latitude = osg::RadiansToDegrees(latitude);
				longitude= osg::RadiansToDegrees(longitude);
				CString str;
				str.Format(_T("%.2lf"), longitude);
				latitudeEdit->SetEditText(str);
				str.Format(_T("%.2lf"), latitude);
				longitudeEdit->SetEditText(str);
				str.Format(_T("%.2lfm"), altitude);
				altitudeEdit->SetEditText(str);
			}
			// 获取视点
			osgEarth::Viewpoint viewpoint = dynamic_cast<osgEarth::Util::EarthManipulator*>(viewer->getCameraManipulator())->getViewpoint();
			CString str;
			osgEarth::GeoPoint pos = viewpoint.focalPoint().value();
			
			str.Format(_T("%.2lf"), pos.x());
			viewLongitudeEdit->SetEditText(str);
			str.Format(_T("%.2lf"), pos.y());
			viewLatitudeEdit->SetEditText(str);
			str.Format(_T("%.2lf"), pos.z());
			viewZEdit->SetEditText(str);
			str.Format(_T("%.2lf"), viewpoint.getHeading());
			viewHeadingEdit->SetEditText(str);
			str.Format(_T("%.2lf"), viewpoint.getPitch());
			viewPitchEdit->SetEditText(str);
			str.Format(_T("%.2lf"), viewpoint.getRange());
			viewRangeEdit->SetEditText(str);
			return true;
		}
	}
	return false;
}