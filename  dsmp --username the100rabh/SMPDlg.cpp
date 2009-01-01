//---------------------------------------------------------------------------
//
// Name:        SMPDlg.cpp
// Author:      100rabh
// Created:     29-Dec-08 3:40:27 PM
// Description: SMPDlg class implementation
//
//---------------------------------------------------------------------------

#include "SMPDlg.h"
#include "wx/dir.h"
#include "wx/filename.h"
#include <wx/file.h>
//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
#include "Images/SMPDlg_NextButton_XPM.xpm"
#include "Images/SMPDlg_StopButton_XPM.xpm"
#include "Images/SMPDlg_PlayButton_XPM.xpm"
#include "Images/SMPDlg_PreviousButton_XPM.xpm"
////Header Include End

#include "Images/Previous_Hoverl.xpm"
#include "Images/Previous_click.xpm"

#include "Images/Play_Clickl.xpm"
#include "Images/Play_Hover.xpm"

#include "Images/Stop_Click.xpm"
#include "Images/Stop_Hover.xpm"
#include "Images/Next_Click.xpm"
#include "Images/Next_Hover.xpm"

//----------------------------------------------------------------------------
// SMPDlg
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(SMPDlg,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(SMPDlg::OnClose)
	EVT_TIMER(ID_WXTIMER1,SMPDlg::WxTimer1Timer)
	
	EVT_LIST_ITEM_ACTIVATED(ID_WXLISTCTRL1,SMPDlg::WxListCtrl1ItemActivated)
	EVT_LIST_KEY_DOWN(ID_WXLISTCTRL1,SMPDlg::WxListCtrl1KeyDown)
	
	EVT_MEDIA_STOP(ID_WXMEDIACTRL1,SMPDlg::WxMediaCtrl1MediaStop)
	EVT_MEDIA_LOADED(ID_WXMEDIACTRL1,SMPDlg::WxMediaCtrl1MediaLoaded)
	EVT_MEDIA_PLAY(ID_WXMEDIACTRL1,SMPDlg::WxMediaCtrl1MediaPlay)
	EVT_MEDIA_PAUSE(ID_WXMEDIACTRL1,SMPDlg::WxMediaCtrl1MediaPause)
	EVT_MEDIA_FINISHED(ID_WXMEDIACTRL1,SMPDlg::WxMediaCtrl1MediaFinished)
	
	EVT_COMMAND_SCROLL(ID_WXSLIDER2,SMPDlg::WxSlider2Scroll)
	
	EVT_COMMAND_SCROLL(ID_WXSLIDER1,SMPDlg::WxSlider1Scroll)
	EVT_BUTTON(ID_WXBUTTON2,SMPDlg::WxButton1Click)
	EVT_BUTTON(ID_WXBUTTON1,SMPDlg::WxButton1Click)
	EVT_BUTTON(ID_NEXTBUTTON,SMPDlg::NextButtonClick)
	EVT_BUTTON(ID_PLAYBUTTON,SMPDlg::PlayButtonClick)
END_EVENT_TABLE()
////Event Table End
void SMPError(wxString errorString)
{
    wxMessageDialog ErrorDlg(NULL,errorString);
    ErrorDlg.ShowModal();
}

SMPDlg::SMPDlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
	selItem = -1;
}

SMPDlg::~SMPDlg()
{
} 

void SMPDlg::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxBoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizer(WxBoxSizer1);
	this->SetAutoLayout(true);

	WxPanel1 = new wxPanel(this, ID_WXPANEL1, wxPoint(5, 5), wxSize(758, 272));
	WxBoxSizer1->Add(WxPanel1,1,wxALIGN_CENTER | wxEXPAND | wxALL,5);

	WxFlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	WxPanel1->SetSizer(WxFlexGridSizer1);
	WxPanel1->SetAutoLayout(true);

	WxPanel = new wxPanel(WxPanel1, ID_WXPANEL2, wxPoint(5, 5), wxSize(749, 42));
	WxFlexGridSizer1->Add(WxPanel,0,wxALIGN_LEFT | wxALL,5);

	wxBitmap PreviousButton_BITMAP (SMPDlg_PreviousButton_XPM);
	PreviousButton = new wxBitmapButton(WxPanel, ID_PREVIOUSBUTTON, PreviousButton_BITMAP, wxPoint(9, 4), wxSize(32, 32), wxNO_BORDER, wxDefaultValidator, wxT("PreviousButton"));

	wxBitmap PlayButton_BITMAP (SMPDlg_PlayButton_XPM);
	PlayButton = new wxBitmapButton(WxPanel, ID_PLAYBUTTON, PlayButton_BITMAP, wxPoint(48, 4), wxSize(32, 32), wxNO_BORDER, wxDefaultValidator, wxT("PlayButton"));

	wxBitmap StopButton_BITMAP (SMPDlg_StopButton_XPM);
	StopButton = new wxBitmapButton(WxPanel, ID_STOPBUTTON, StopButton_BITMAP, wxPoint(90, 4), wxSize(32, 32), wxNO_BORDER, wxDefaultValidator, wxT("StopButton"));

	wxBitmap NextButton_BITMAP (SMPDlg_NextButton_XPM);
	NextButton = new wxBitmapButton(WxPanel, ID_NEXTBUTTON, NextButton_BITMAP, wxPoint(131, 4), wxSize(32, 32), wxNO_BORDER, wxDefaultValidator, wxT("NextButton"));

	WxButton1 = new wxButton(WxPanel, ID_WXBUTTON1, wxT("Add Folder"), wxPoint(629, 7), wxSize(67, 27), 0, wxDefaultValidator, wxT("WxButton1"));

	WxButton2 = new wxButton(WxPanel, ID_WXBUTTON2, wxT("Add File"), wxPoint(564, 7), wxSize(60, 27), 0, wxDefaultValidator, wxT("WxButton2"));

	WxSlider1 = new wxSlider(WxPanel, ID_WXSLIDER1, 0, 0, 10, wxPoint(184, 12), wxSize(198, 24), wxSL_HORIZONTAL | wxSL_SELRANGE , wxDefaultValidator, wxT("WxSlider1"));
	WxSlider1->SetRange(0,10);
	WxSlider1->SetValue(0);

	WxSlider2 = new wxSlider(WxPanel, ID_WXSLIDER2, 0, 0, 100, wxPoint(708, 1), wxSize(18, 40), wxSL_VERTICAL | wxSL_INVERSE , wxDefaultValidator, wxT("WxSlider2"));
	WxSlider2->SetRange(0,100);
	WxSlider2->SetValue(0);

	WxMediaCtrl1 = new wxMediaCtrl(WxPanel, ID_WXMEDIACTRL1,wxT(""), wxPoint(412, 10), wxSize(0, 0) );
	WxMediaCtrl1->Show(false);
	WxMediaCtrl1->Enable(false);
	WxMediaCtrl1->ShowPlayerControls(wxMEDIACTRLPLAYERCONTROLS_NONE);

	WxListCtrl1 = new wxListCtrl(WxPanel1, ID_WXLISTCTRL1, wxPoint(66, 57), wxSize(627, 165), wxLC_REPORT | wxLC_AUTOARRANGE | wxLC_EDIT_LABELS, wxDefaultValidator, wxT("WxListCtrl1"));
	WxListCtrl1->InsertColumn(0,wxT("Path"),wxLIST_FORMAT_LEFT,100 );
	WxListCtrl1->InsertColumn(0,wxT("Name"),wxLIST_FORMAT_LEFT,100 );
	WxListCtrl1->InsertColumn(0,wxT("Directory"),wxLIST_FORMAT_LEFT,100 );
	WxFlexGridSizer1->Add(WxListCtrl1,1,wxALIGN_LEFT | wxEXPAND | wxALL,5);

	WxTimer1 = new wxTimer();
	WxTimer1->SetOwner(this, ID_WXTIMER1);

	RandomCheckbox = new wxCheckBox(WxPanel, ID_RANDOMCHECKBOX, wxT("Random"), wxPoint(498, 14), wxSize(61, 16), 0, wxDefaultValidator, wxT("RandomCheckbox"));

	SetTitle(wxT("SMP"));
	SetIcon(wxNullIcon);
	
	GetSizer()->Layout();
	GetSizer()->Fit(this);
	GetSizer()->SetSizeHints(this);
	Center();
	
	////GUI Items Creation End
	WxFlexGridSizer1->AddGrowableRow(1,1);
	WxFlexGridSizer1->AddGrowableCol(0,1);

	wxBitmap PreviousButton_hover_BITMAP (Previous_Hoverl_xpm);
	PreviousButton->SetBitmapHover(PreviousButton_hover_BITMAP);

	wxBitmap PreviousButton_click_BITMAP (Previous_click_xpm);
	PreviousButton->SetBitmapSelected(PreviousButton_click_BITMAP);

	wxBitmap PlayButton_hover_BITMAP (Play_Hover_xpm);
	PlayButton->SetBitmapHover(PlayButton_hover_BITMAP);

	wxBitmap PlayButton_click_BITMAP (Play_Clickl_xpm);
	PlayButton->SetBitmapSelected(PlayButton_click_BITMAP);

	wxBitmap StopButton_click_BITMAP (Stop_Click_xpm);
	StopButton->SetBitmapSelected(StopButton_click_BITMAP);

	wxBitmap StopButton_hover_BITMAP (Stop_Hover_xpm);
	StopButton->SetBitmapHover(StopButton_hover_BITMAP);


	wxBitmap NextButton_hover_BITMAP (Next_Hover_xpm);
	NextButton->SetBitmapHover(NextButton_hover_BITMAP);

	wxBitmap NextButton_click_BITMAP (Next_Click_xpm);
	NextButton->SetBitmapSelected(NextButton_click_BITMAP);
	
}

void SMPDlg::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

/*
 * WxButton1Click
 */
void SMPDlg::WxButton1Click(wxCommandEvent& event)
{
	// insert your code here
	wxFileName base;
	base.AssignHomeDir();
	//SMPError(base.GetFullPath());
	base.AppendDir("My Documents");
    base.AppendDir("My Music");
	//SMPError(base.GetHomeDir());
	//SMPError(base.GetFullPath());	
	wxDirDialog DirDlg(this,"Select Directory",base.GetFullPath(),wxDD_DIR_MUST_EXIST);
	if(DirDlg.ShowModal() == wxID_OK)
	{
        wxString AddPath = DirDlg.GetPath();
        AddFilesFromFolder(AddPath);
    }
}

wxString getDirNameFromString(wxString name)
{
    wxString dirName;
    //dirName = name.BeforeLast('/');
    dirName = name.AfterLast('\\');
    //SMPError(dirName);
    return dirName;
}

// No description
void SMPDlg::AddFilesFromFolder(wxString FileName)
{
	/* TODO (#1#): Implement SMPDlg::AddFilesFromFolder() */
    wxDir AddDir(FileName);
	if(wxDir::Exists(FileName))
	{
        wxArrayString files;
        files.Clear();
        //SMPError(FileName);
        //AddDir.SetPath("C:\\My Documents\\My Music");
        wxDir::GetAllFiles(FileName,&files,wxT("*.mp3"));
        wxString temp;
        temp.Printf(wxT("%d"),files.GetCount());
        //SMPError(temp);
        
      
        for(unsigned int iCount = 0; iCount < files.GetCount(); iCount++)
        {
            temp.Printf(files[iCount]);
            //SMPError(temp);
            
            wxFileName curFile(files[iCount]), tempFilename;
            FileList::iterator DirNode, FileNode;
            temp.Printf(curFile.GetPath());
//            SMPError(temp);

            if((DirNode = Dirs.find(curFile.GetFullPath())) == Dirs.end())
            {

                temp = curFile.GetPath();
                //SMPError(temp);
                temp = getDirNameFromString(temp);
                int start = -1;
                int found = 0;
                while((start = WxListCtrl1->FindItem(start,curFile.GetPath().AfterLast(curFile.GetPathSeparator()))) != -1)
                {
                	wxListItem itemp;
                	itemp.SetId(start);
                	itemp.SetColumn(2);
                	itemp.SetMask(wxLIST_MASK_TEXT);
                	WxListCtrl1->GetItem(itemp);
                	//SMPError(itemp.GetText());
                	if( itemp.GetText() == curFile.GetFullPath())
                	{
                        found = 1;
                    	//SMPError(curFile.GetFullPath());
                        
                        break;
                    }
                    start = start + 1;
                    if(start > WxListCtrl1->GetItemCount())
                        break;
                }
                if(found == 1) 
                    continue;
                long loc = WxListCtrl1->InsertItem(WxListCtrl1->GetItemCount() + 1, curFile.GetPath().AfterLast(curFile.GetPathSeparator()));
                WxListCtrl1->SetItem(loc, 1, curFile.GetName());
                WxListCtrl1->SetItem(loc, 2, curFile.GetFullPath());
                
                
                //SMPError(temp);
                
                //WxTreeListCtrl1->AddRoot(curFile.)
                //WxTreeListCtrl1->InsertItem()
                //long loc = WxListCtrl1->InsertItem(WxListCtrl1->GetItemCount() + 1, curFile.GetPath().AfterLast(curFile.GetPathSeparator()));
                //WxListCtrl1->SetItem(loc, 1, curFile.GetName());
                /*element = new FileListElement;
                element->FullPath = curFile.GetPath();
                element->item = WxTreeListCtrl1->AppendItem (root , curFile.GetPath());
                //Dirs.Append(curFile.GetPath(), element);
                Dirs[curFile.GetPath()] = element;*/

            }
            else
            {
                temp.Printf(wxT("%d"),__LINE__);
//                SMPError(temp);
            }
      }
    }
    WxListCtrl1->Refresh();    
}

/*
 * PlayButtonClick
 */
void SMPDlg::PlayButtonClick(wxCommandEvent& event)
{
	// insert your code here
	int itemCount = WxListCtrl1->GetItemCount();
	if(itemCount < 1) 
	   return;
	//SMPError(wxString::Format("%d",itemCount));
	if(RandomCheckbox->IsChecked())
	   selItem = (itemCount - long(floor(rand() * 10000000))%itemCount) % itemCount  ;
	else
	{
        selItem = (selItem + 1) % itemCount;
    }
	//SMPError(wxString::Format("%d",selItem));
	PlayThisFile(selItem);
	
//	WxMediaCtrl1->Load()
	
}

/*
 * WxMediaCtrl1MediaLoaded
 */
void SMPDlg::WxMediaCtrl1MediaLoaded(wxMediaEvent& event)
{
	// insert your code here
	WxMediaCtrl1->Play();
	WxSlider1->SetMin(0);
	WxSlider1->SetMax(WxMediaCtrl1->Length() / 1000);
	WxSlider1->SetValue(0);
	WxTimer1->Start(1000,false);
	
}

/*
 * WxMediaCtrl1MediaFinished
 */
void SMPDlg::WxMediaCtrl1MediaFinished(wxMediaEvent& event)
{
	// insert your code here
	wxCommandEvent  a;
	PlayButtonClick(a);
}

/*
 * WxMediaCtrl1MediaPause
 */
void SMPDlg::WxMediaCtrl1MediaPause(wxMediaEvent& event)
{
	// insert your code here
}

/*
 * WxMediaCtrl1MediaPlay
 */
void SMPDlg::WxMediaCtrl1MediaPlay(wxMediaEvent& event)
{
	// insert your code here
}

/*
 * WxMediaCtrl1MediaStop
 */
void SMPDlg::WxMediaCtrl1MediaStop(wxMediaEvent& event)
{
	// insert your code here
}

/*
 * WxTimer1Timer
 */
void SMPDlg::WxTimer1Timer(wxTimerEvent& event)
{
	// insert your code here
	if(isPlaying)
	{
        int state = WxMediaCtrl1->GetState();
        switch (state)
        {
            case wxMEDIASTATE_STOPPED:
                WxSlider1->SetValue(0);
                //SMPError("its not on yet");
                break; 
            
            default:
                wxFileOffset time = WxMediaCtrl1->Tell();
                WxSlider1->SetValue(long(time)/1000);
                WxSlider2->SetValue(long(WxMediaCtrl1->GetVolume() * 100));                
        }
    }
}

/*
 * WxSlider2Scroll
 */
void SMPDlg::WxSlider2Scroll(wxScrollEvent& event)
{
	// insert your code here
	WxMediaCtrl1->SetVolume(double(WxSlider2->GetValue())/100);
}

/*
 * WxSlider1Scroll
 */
void SMPDlg::WxSlider1Scroll(wxScrollEvent& event)
{
	// insert your code here
	WxMediaCtrl1->Seek(WxSlider1->GetValue()*1000,wxFromStart);
}

/*
 * NextButtonClick
 */
void SMPDlg::NextButtonClick(wxCommandEvent& event)
{
	// insert your code here
	WxMediaCtrl1->Stop();
	wxListItem temp;
	temp.Clear();
	temp.SetId(selItem);
	temp.SetMask(wxLIST_MASK_STATE);
	temp.SetState(~wxLIST_STATE_SELECTED);
	WxListCtrl1->SetItemState(selItem,~wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED);
	wxCommandEvent  a;
	PlayButtonClick(a);	
	
}

/*
 * WxListCtrl1ItemActivated
 */
void SMPDlg::WxListCtrl1ItemActivated(wxListEvent& event)
{
	// insert your code here
	PlayThisFile(event.GetIndex());
}

// No description
void SMPDlg::PlayThisFile(long id)
{
	/* TODO (#1#): Implement SMPDlg::PlayThisFile() */
	selItem = id;
	wxString name = WxListCtrl1->GetItemText(selItem);
	//SMPError(name);
	wxListItem temp;
	temp.SetId(selItem);
	temp.SetColumn(2);
	temp.SetMask(wxLIST_MASK_TEXT);
	if( WxListCtrl1->GetItem( temp))
	{
    	wxString path = temp.GetText();
    	//SMPError(path);
    	WxMediaCtrl1->Load(path);
    	temp.SetColumn(1);
    	temp.SetMask(wxLIST_MASK_TEXT);
    	if( WxListCtrl1->GetItem( temp))
    	{
            this->SetTitle(wxString::Format("SMP - %s - %s",name.c_str(), temp.GetText().c_str()));
        }
        temp.Clear();
    	temp.SetId(selItem);
    	temp.SetState(wxLIST_STATE_SELECTED);
    	WxListCtrl1->EnsureVisible(selItem);
        WxListCtrl1->SetItemState(selItem, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
    }
    else
    {
        SMPError("Cannot get item");
    }
    isPlaying = true;
	
}

/*
 * WxListCtrl1KeyDown
 */
void SMPDlg::WxListCtrl1KeyDown(wxListEvent& event)
{
	// insert your code here
    switch ( event.GetKeyCode() )
    {
        case WXK_DELETE:
            long item = WxListCtrl1->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
            while ( item != -1 )
            {
                WxListCtrl1->DeleteItem(item);

                //wxLogMessage(_T("Item %ld deleted"), item);

                // -1 because the indices were shifted by DeleteItem()
                item = WxListCtrl1->GetNextItem(item - 1,
                                   wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
            }
            break;
            
    }
}
