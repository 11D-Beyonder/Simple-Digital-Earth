// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// DigitalEarthView.cpp: CDigitalEarthView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DigitalEarth.h"
#endif

#include "DigitalEarthDoc.h"
#include "DigitalEarthView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDigitalEarthView

IMPLEMENT_DYNCREATE(CDigitalEarthView, CView)

BEGIN_MESSAGE_MAP(CDigitalEarthView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_EDIT_PROVINCE_OPT, &CDigitalEarthView::OnEditProvinceOpt)
	ON_COMMAND(ID_BUTTON_OPT_OK, &CDigitalEarthView::OnButtonOptOk)
	ON_COMMAND(ID_EDIT_COUNTRY_OPT, &CDigitalEarthView::OnEditCountryOpt)
	ON_COMMAND(ID_EDIT_LONGITUDE, &CDigitalEarthView::OnEditLongitude)
	ON_COMMAND(ID_EDIT_LATITUDE, &CDigitalEarthView::OnEditLatitude)
	ON_COMMAND(ID_EDIT_ALTITUDE, &CDigitalEarthView::OnEditAltitude)
	ON_COMMAND(ID_CHECK_NATION_FLAG, &CDigitalEarthView::OnCheckNationFlag)
	ON_UPDATE_COMMAND_UI(ID_CHECK_NATION_FLAG, &CDigitalEarthView::OnUpdateCheckNationFlag)
	ON_COMMAND(ID_CHECK_PROVINCE_BOUNDARY, &CDigitalEarthView::OnCheckProvinceBoundary)
	ON_UPDATE_COMMAND_UI(ID_CHECK_PROVINCE_BOUNDARY, &CDigitalEarthView::OnUpdateCheckProvinceBoundary)
	ON_COMMAND(ID_CHECK_COUNTRY_BOUNDARY, &CDigitalEarthView::OnCheckCountryBoundary)
	ON_UPDATE_COMMAND_UI(ID_CHECK_COUNTRY_BOUNDARY, &CDigitalEarthView::OnUpdateCheckCountryBoundary)
	ON_COMMAND(ID_CHECK_CONTOUR, &CDigitalEarthView::OnCheckContour)
	ON_UPDATE_COMMAND_UI(ID_CHECK_CONTOUR, &CDigitalEarthView::OnUpdateCheckContour)
	ON_COMMAND(ID_CHECK_DETAIL, &CDigitalEarthView::OnCheckDetail)
	ON_UPDATE_COMMAND_UI(ID_CHECK_DETAIL, &CDigitalEarthView::OnUpdateCheckDetail)
	ON_UPDATE_COMMAND_UI(ID_CHECK_GLOBE, &CDigitalEarthView::OnUpdateCheckGlobe)
	ON_COMMAND(ID_CHECK_GLOBE, &CDigitalEarthView::OnCheckGlobe)
	ON_COMMAND(ID_EDIT_FLY_HEIGHT, &CDigitalEarthView::OnEditFlyHeight)
	ON_COMMAND(ID_EDIT_FLY_LATITUDE, &CDigitalEarthView::OnEditFlyLatitude)
	ON_COMMAND(ID_EDIT_FLY_LONGITUDE, &CDigitalEarthView::OnEditFlyLongitude)
	ON_COMMAND(ID_BUTTON_FLY, &CDigitalEarthView::OnButtonFly)
	ON_COMMAND(ID_EDIT_VIEW_LONGITUDE, &CDigitalEarthView::OnEditViewLongitude)
	ON_COMMAND(ID_EDIT_VIEW_LATITUDE, &CDigitalEarthView::OnEditViewLatitude)
	ON_COMMAND(ID_EDIT_VIEW_HEIGHT, &CDigitalEarthView::OnEditViewHeight)
	ON_COMMAND(ID_EDIT_VIEW_Z, &CDigitalEarthView::OnEditViewZ)
	ON_COMMAND(ID_EDIT_VIEW_HEADING, &CDigitalEarthView::OnEditViewHeading)
	ON_COMMAND(ID_EDIT_VIEW_PITCH, &CDigitalEarthView::OnEditViewPitch)
	ON_COMMAND(ID_CHECK_ANIMAL, &CDigitalEarthView::OnCheckAnimal)
	ON_UPDATE_COMMAND_UI(ID_CHECK_ANIMAL, &CDigitalEarthView::OnUpdateCheckAnimal)
	ON_COMMAND(ID_BUTTON_SEE_ANIMAL, &CDigitalEarthView::OnButtonSeeAnimal)
END_MESSAGE_MAP()

// CDigitalEarthView 构造/析构

CDigitalEarthView::CDigitalEarthView() noexcept
{
	// TODO: 在此处添加构造代码
	earth = nullptr;
	mThreadHandle = nullptr;
	longitudeEdit = nullptr;
	latitudeEdit = nullptr;
	provinceBoundaryEdit = nullptr;
	countryBoundaryEdit = nullptr;
	flyLatitudeEdit = nullptr;
	flyLongitudeEdit = nullptr;
	flyHeightEdit = nullptr;

	isShowNationFlag = TRUE;
	isShowProvinceBoundary = true;
	isShowCountryBoundary = true;
	isShowContour = true;
	isShowDetail = true;
	isShowGlobe = true;
	isShowAnimal = TRUE;
}

CDigitalEarthView::~CDigitalEarthView()
{
}

BOOL CDigitalEarthView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDigitalEarthView 绘图

void CDigitalEarthView::OnDraw(CDC* /*pDC*/)
{
	CDigitalEarthDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CDigitalEarthView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDigitalEarthView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDigitalEarthView 诊断

#ifdef _DEBUG
void CDigitalEarthView::AssertValid() const
{
	CView::AssertValid();
}

void CDigitalEarthView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDigitalEarthDoc* CDigitalEarthView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDigitalEarthDoc)));
	return (CDigitalEarthDoc*)m_pDocument;
}
#endif //_DEBUG


// CDigitalEarthView 消息处理程序


int CDigitalEarthView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	

	return 0;
}


void CDigitalEarthView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码

	if (nullptr != earth)
	{
		delete earth;
	}
	WaitForSingleObject(mThreadHandle, 1000);
}


BOOL CDigitalEarthView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (nullptr == earth)
	{
		return CView::OnEraseBkgnd(pDC);
	}
	else
	{
		return FALSE;
	}
}


void CDigitalEarthView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CDigitalEarthApp* pApp = (CDigitalEarthApp*)AfxGetApp();
	CMainFrame* pWnd = (CMainFrame*)pApp->GetMainWnd();
	latitudeEdit = dynamic_cast<CMFCRibbonEdit*>(pWnd->m_wndRibbonBar.FindByID(ID_EDIT_LATITUDE));
	longitudeEdit = dynamic_cast<CMFCRibbonEdit*>(pWnd->m_wndRibbonBar.FindByID(ID_EDIT_LONGITUDE));
	altitudeEdit = dynamic_cast<CMFCRibbonEdit*>(pWnd->m_wndRibbonBar.FindByID(ID_EDIT_ALTITUDE));
	countryBoundaryEdit = dynamic_cast<CMFCRibbonEdit*>(pWnd->m_wndRibbonBar.FindByID(ID_EDIT_COUNTRY_OPT));
	provinceBoundaryEdit = dynamic_cast<CMFCRibbonEdit*>(pWnd->m_wndRibbonBar.FindByID(ID_EDIT_PROVINCE_OPT));
	flyLongitudeEdit = dynamic_cast<CMFCRibbonEdit*>(pWnd->m_wndRibbonBar.FindByID(ID_EDIT_FLY_LONGITUDE));
	flyLatitudeEdit = dynamic_cast<CMFCRibbonEdit*>(pWnd->m_wndRibbonBar.FindByID(ID_EDIT_FLY_LATITUDE));
	flyHeightEdit = dynamic_cast<CMFCRibbonEdit*>(pWnd->m_wndRibbonBar.FindByID(ID_EDIT_FLY_HEIGHT));
	viewLongitudeEdit = dynamic_cast<CMFCRibbonEdit*>(pWnd->m_wndRibbonBar.FindByID(ID_EDIT_VIEW_LONGITUDE));
	viewLatitudeEdit = dynamic_cast<CMFCRibbonEdit*>(pWnd->m_wndRibbonBar.FindByID(ID_EDIT_VIEW_LATITUDE));
	viewZEdit = dynamic_cast<CMFCRibbonEdit*>(pWnd->m_wndRibbonBar.FindByID(ID_EDIT_VIEW_Z));
	viewHeadingEdit = dynamic_cast<CMFCRibbonEdit*>(pWnd->m_wndRibbonBar.FindByID(ID_EDIT_VIEW_HEADING));
	viewPitchEdit = dynamic_cast<CMFCRibbonEdit*>(pWnd->m_wndRibbonBar.FindByID(ID_EDIT_VIEW_PITCH));
	viewRangeEdit = dynamic_cast<CMFCRibbonEdit*>(pWnd->m_wndRibbonBar.FindByID(ID_EDIT_VIEW_HEIGHT));

	
	altitudeEdit->OnEnable(FALSE);
	latitudeEdit->OnEnable(FALSE);
	longitudeEdit->OnEnable(FALSE);
	viewLongitudeEdit->OnEnable(FALSE);
	viewLatitudeEdit->OnEnable(FALSE);
	viewZEdit->OnEnable(FALSE);
	viewHeadingEdit->OnEnable(FALSE);
	viewPitchEdit->OnEnable(FALSE);
	viewRangeEdit->OnEnable(FALSE);

	earth = new COSGObject(m_hWnd,
		longitudeEdit, latitudeEdit, altitudeEdit,
		viewLongitudeEdit, viewLatitudeEdit, viewZEdit,
		viewHeadingEdit, viewPitchEdit, viewRangeEdit);
	earth->InitOSG();
	mThreadHandle = (HANDLE)_beginthread(&COSGObject::Render, 0u, earth);
	
}


void CDigitalEarthView::OnEditProvinceOpt()
{
	// TODO: 在此添加命令处理程序代码
}


void CDigitalEarthView::OnButtonOptOk()
{
	// TODO: 在此添加命令处理程序代码
	std::string str;
	// 用正则匹配小数
	std::regex r("^(-?\\d+)(\\.\\d+)?");
	float opt = 0;
	str = CT2A(provinceBoundaryEdit->GetEditText().GetBuffer());
	opt = std::atof(str.c_str());
	if (!std::regex_match(str, r))
	{
		MessageBox(_T("透明度必须为 0~1 小数"), _T("错误"), MB_OK | MB_ICONERROR);
	}
	else if (opt < 0 || opt > 1)
	{
		MessageBox(_T("透明度必须为 0~1 小数"), _T("错误"), MB_OK | MB_ICONERROR);
	}
	else
	{
		earth->setProvinceBoundaryOpacity(opt);
	}

	str = CT2A(countryBoundaryEdit ->GetEditText().GetBuffer());
	opt = std::atof(str.c_str());
	if (!std::regex_match(str, r))
	{
		MessageBox(_T("透明度必须为 0~1 小数"), _T("错误"), MB_OK | MB_ICONERROR);
	}
	else if (opt < 0 || opt > 1)
	{
		MessageBox(_T("透明度必须为 0~1 小数"), _T("错误"), MB_OK | MB_ICONERROR);
	}
	else
	{
		earth->setCountryBoundaryOpacity(opt);
	}
}


void CDigitalEarthView::OnEditCountryOpt()
{
	// TODO: 在此添加命令处理程序代码
}


void CDigitalEarthView::OnEditLongitude()
{
	// TODO: 在此添加命令处理程序代码
}


void CDigitalEarthView::OnEditLatitude()
{
	// TODO: 在此添加命令处理程序代码
}


void CDigitalEarthView::OnEditAltitude()
{
	// TODO: 在此添加命令处理程序代码
}


void CDigitalEarthView::OnCheckNationFlag()
{
	// TODO: 在此添加命令处理程序代码
	isShowNationFlag = !isShowNationFlag;
	earth->enableNationFlag(isShowNationFlag);
}


void CDigitalEarthView::OnUpdateCheckNationFlag(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(isShowNationFlag);

}


void CDigitalEarthView::OnCheckProvinceBoundary()
{
	// TODO: 在此添加命令处理程序代码
	isShowProvinceBoundary = !isShowProvinceBoundary;
	earth->enableProvinceBoundary(isShowProvinceBoundary);
}


void CDigitalEarthView::OnUpdateCheckProvinceBoundary(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(isShowProvinceBoundary);
}


void CDigitalEarthView::OnCheckCountryBoundary()
{
	// TODO: 在此添加命令处理程序代码
	isShowCountryBoundary = !isShowCountryBoundary;
	earth->enableCountryBoundary(isShowCountryBoundary);
}


void CDigitalEarthView::OnUpdateCheckCountryBoundary(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(isShowCountryBoundary);
}


void CDigitalEarthView::OnCheckContour()
{
	// TODO: 在此添加命令处理程序代码
	isShowContour = !isShowContour;
	earth->enableContour(isShowContour);
}


void CDigitalEarthView::OnUpdateCheckContour(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(isShowContour);
}


void CDigitalEarthView::OnCheckDetail()
{
	// TODO: 在此添加命令处理程序代码
	isShowDetail = !isShowDetail;
	earth->enableDetail(isShowDetail);
}


void CDigitalEarthView::OnUpdateCheckDetail(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(isShowDetail);
}


void CDigitalEarthView::OnUpdateCheckGlobe(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(isShowGlobe);
}


void CDigitalEarthView::OnCheckGlobe()
{
	// TODO: 在此添加命令处理程序代码
	isShowGlobe = !isShowGlobe;
	earth->enableGlobe(isShowGlobe);
}


void CDigitalEarthView::OnEditFlyHeight()
{
	// TODO: 在此添加命令处理程序代码
}


void CDigitalEarthView::OnEditFlyLatitude()
{
	// TODO: 在此添加命令处理程序代码
}


void CDigitalEarthView::OnEditFlyLongitude()
{
	// TODO: 在此添加命令处理程序代码
}


void CDigitalEarthView::OnButtonFly()
{
	// TODO: 在此添加命令处理程序代码
	std::string str;
	str = CT2A(flyLongitudeEdit->GetEditText().GetBuffer());
	double longitude = std::atof(str.c_str());
	str = CT2A(flyLatitudeEdit->GetEditText().GetBuffer());
	double latitude = std::atof(str.c_str());
	str = CT2A(flyHeightEdit->GetEditText().GetBuffer());
	double height = std::atof(str.c_str());
	earth->flyTo(longitude, latitude, height);
}

void CDigitalEarthView::OnEditViewLongitude()
{
	// TODO: 在此添加命令处理程序代码
}


void CDigitalEarthView::OnEditViewLatitude()
{
	// TODO: 在此添加命令处理程序代码
}


void CDigitalEarthView::OnEditViewHeight()
{
	// TODO: 在此添加命令处理程序代码
}


void CDigitalEarthView::OnEditViewZ()
{
	// TODO: 在此添加命令处理程序代码
}


void CDigitalEarthView::OnEditViewHeading()
{
	// TODO: 在此添加命令处理程序代码
}


void CDigitalEarthView::OnEditViewPitch()
{
	// TODO: 在此添加命令处理程序代码
}

void CDigitalEarthView::OnCheckAnimal()
{
	// TODO: 在此添加命令处理程序代码
	isShowAnimal = !isShowAnimal;
	earth->enableAnimal(isShowAnimal);
}


void CDigitalEarthView::OnUpdateCheckAnimal(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(isShowAnimal);
}


void CDigitalEarthView::OnButtonSeeAnimal()
{
	// TODO: 在此添加命令处理程序代码
	earth->flyTo(120.00, 30.58, 1571.65, 38.94, -152.59, -17.09);
}
