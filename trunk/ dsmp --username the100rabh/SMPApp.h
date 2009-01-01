//---------------------------------------------------------------------------
//
// Name:        SMPApp.h
// Author:      100rabh
// Created:     29-Dec-08 3:40:26 PM
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __SMPDLGApp_h__
#define __SMPDLGApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class SMPDlgApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
