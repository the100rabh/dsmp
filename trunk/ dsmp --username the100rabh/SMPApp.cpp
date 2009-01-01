//---------------------------------------------------------------------------
//
// Name:        SMPApp.cpp
// Author:      100rabh
// Created:     29-Dec-08 3:40:26 PM
// Description: 
//
//---------------------------------------------------------------------------

#include "SMPApp.h"
#include "SMPDlg.h"

IMPLEMENT_APP(SMPDlgApp)

bool SMPDlgApp::OnInit()
{
	SMPDlg* dialog = new SMPDlg(NULL);
	SetTopWindow(dialog);
	dialog->Show(true);		
	return true;
}
 
int SMPDlgApp::OnExit()
{
	return 0;
}
