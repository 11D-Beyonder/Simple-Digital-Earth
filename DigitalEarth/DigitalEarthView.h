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

// DigitalEarthView.h: CDigitalEarthView 类的接口
//

#pragma once

#include "COSGObject.h"
#include "DigitalEarthDoc.h"
#include "MainFrm.h"
#include <regex>
class CDigitalEarthView : public CView
{
protected: // 仅从序列化创建
	CDigitalEarthView() noexcept;
	DECLARE_DYNCREATE(CDigitalEarthView)

// 特性
public:
	CDigitalEarthDoc* GetDocument() const;

// 操作
public:
// 自定义变量
private:
	COSGObject* earth;
	HANDLE mThreadHandle;

	CMFCRibbonEdit* longitudeEdit;
	CMFCRibbonEdit* latitudeEdit;
	CMFCRibbonEdit* altitudeEdit;
	CMFCRibbonEdit* provinceBoundaryEdit;
	CMFCRibbonEdit* countryBoundaryEdit;
	CMFCRibbonEdit* flyLongitudeEdit;
	CMFCRibbonEdit* flyLatitudeEdit;
	CMFCRibbonEdit* flyHeightEdit;
	CMFCRibbonEdit* viewLongitudeEdit;
	CMFCRibbonEdit* viewLatitudeEdit;
	CMFCRibbonEdit* viewZEdit;
	CMFCRibbonEdit* viewHeadingEdit;
	CMFCRibbonEdit* viewPitchEdit;
	CMFCRibbonEdit* viewRangeEdit;

	BOOL isShowNationFlag;
	bool isShowProvinceBoundary;
	bool isShowCountryBoundary;
	bool isShowContour;
	bool isShowDetail;
	bool isShowGlobe;
	BOOL isShowAnimal;
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CDigitalEarthView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnInitialUpdate();
	afx_msg void OnEditProvinceOpt();
	afx_msg void OnButtonOptOk();
	afx_msg void OnEditCountryOpt();
	afx_msg void OnEditLongitude();
	afx_msg void OnEditLatitude();
	afx_msg void OnEditAltitude();
	afx_msg void OnCheckNationFlag();
	afx_msg void OnUpdateCheckNationFlag(CCmdUI* pCmdUI);
	afx_msg void OnCheckProvinceBoundary();
	afx_msg void OnUpdateCheckProvinceBoundary(CCmdUI* pCmdUI);
	afx_msg void OnCheckCountryBoundary();
	afx_msg void OnUpdateCheckCountryBoundary(CCmdUI* pCmdUI);
	afx_msg void OnCheckContour();
	afx_msg void OnUpdateCheckContour(CCmdUI* pCmdUI);
	afx_msg void OnCheckDetail();
	afx_msg void OnUpdateCheckDetail(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCheckGlobe(CCmdUI* pCmdUI);
	afx_msg void OnCheckGlobe();
	afx_msg void OnEditFlyHeight();
	afx_msg void OnEditFlyLatitude();
	afx_msg void OnEditFlyLongitude();
	afx_msg void OnButtonFly();
	afx_msg void OnEditViewLongitude();
	afx_msg void OnEditViewLatitude();
	afx_msg void OnEditViewHeight();
	afx_msg void OnEditViewZ();
	afx_msg void OnEditViewHeading();
	afx_msg void OnEditViewPitch();
	afx_msg void OnCheckAnimal();
	afx_msg void OnUpdateCheckAnimal(CCmdUI* pCmdUI);
	afx_msg void OnButtonSeeAnimal();
};

#ifndef _DEBUG  // DigitalEarthView.cpp 中的调试版本
inline CDigitalEarthDoc* CDigitalEarthView::GetDocument() const
   { return reinterpret_cast<CDigitalEarthDoc*>(m_pDocument); }
#endif