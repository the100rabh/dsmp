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
#include <iostream>
#include <fstream>


//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
#include "Images/Self_SMPDlg_XPM.xpm"
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

#include "Images/Pause_Click.xpm"
#include "Images/Pause_Hover.xpm"
#include "Images/Pause_Normal.xpm"


//----------------------------------------------------------------------------
// SMPDlg
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(SMPDlg,wxDialog)
	////Manual Code Start
	EVT_HOTKEY(ID_HOT_NEXT, SMPDlg::HotKeyNext)
	EVT_HOTKEY(ID_HOT_STOP, SMPDlg::HotKeyStop)
	EVT_HOTKEY(ID_HOT_PLAY, SMPDlg::HotKeyPlay)
	EVT_HOTKEY(ID_HOT_PREV, SMPDlg::HotKeyPrev)
	////Manual Code End
	
	EVT_CLOSE(SMPDlg::OnClose)
	EVT_DROP_FILES(SMPDlg::SMPDlgDropFiles)
	EVT_TIMER(ID_WXTIMER1,SMPDlg::WxTimer1Timer)
	EVT_MENU(ID_MNU_ADDFILES_1026 , SMPDlg::WxButton2Click)
	EVT_MENU(ID_MNU_ADDFOLDER_1027 , SMPDlg::WxButton1Click)
	EVT_MENU(ID_MNU_LOADPLAYLIST_1028 , SMPDlg::LoadPlaylistClick)
	EVT_MENU(ID_MNU_SAVEPLAYLIST_1029 , SMPDlg::SavePlaylistClick)
	EVT_MENU(ID_MNU_PLAY_PAUSE_1019 , SMPDlg::PlayButtonClick)
	EVT_MENU(ID_MNU_STOP_1020 , SMPDlg::StopButtonClick)
	EVT_MENU(ID_MNU_NEXT_1021 , SMPDlg::NextButtonClick)
	EVT_MENU(ID_MNU_PREVIOUS_1022 , SMPDlg::PreviousButtonClick)
	EVT_MENU(ID_MNU_ADDFOLDER_1023 , SMPDlg::WxButton1Click)
	EVT_MENU(ID_MNU_SAVEPLAYLIST_1024 , SMPDlg::SavePlaylistClick)
	EVT_UPDATE_UI(ID_MNU_SAVEPLAYLIST_1024 , SMPDlg::SavePlaylistUpdateUI0)
	EVT_MENU(ID_MNU_LOADPLAYLIST_1025 , SMPDlg::LoadPlaylistClick)
	
	EVT_LIST_ITEM_ACTIVATED(ID_WXLISTCTRL1,SMPDlg::WxListCtrl1ItemActivated)
	EVT_LIST_KEY_DOWN(ID_WXLISTCTRL1,SMPDlg::WxListCtrl1KeyDown)
	
	EVT_MEDIA_STOP(ID_WXMEDIACTRL1,SMPDlg::WxMediaCtrl1MediaStop)
	EVT_MEDIA_LOADED(ID_WXMEDIACTRL1,SMPDlg::WxMediaCtrl1MediaLoaded)
	EVT_MEDIA_PLAY(ID_WXMEDIACTRL1,SMPDlg::WxMediaCtrl1MediaPlay)
	EVT_MEDIA_PAUSE(ID_WXMEDIACTRL1,SMPDlg::WxMediaCtrl1MediaPause)
	EVT_MEDIA_FINISHED(ID_WXMEDIACTRL1,SMPDlg::WxMediaCtrl1MediaFinished)
	
	EVT_COMMAND_SCROLL(ID_WXSLIDER2,SMPDlg::WxSlider2Scroll)
	
	EVT_COMMAND_SCROLL(ID_WXSLIDER1,SMPDlg::WxSlider1Scroll)
	EVT_BUTTON(ID_ADDBUTTON,SMPDlg::AddButtonClick)
	EVT_BUTTON(ID_PLAYLISTS,SMPDlg::PlaylistsButtonClick)
	EVT_BUTTON(ID_NEXTBUTTON,SMPDlg::NextButtonClick)
	EVT_BUTTON(ID_STOPBUTTON,SMPDlg::StopButtonClick)
	EVT_BUTTON(ID_PLAYBUTTON,SMPDlg::PlayButtonClick)
	EVT_BUTTON(ID_PREVIOUSBUTTON,SMPDlg::PreviousButtonClick)
END_EVENT_TABLE()
////Event Table End
void SMPError(wxString errorString)
{
//    wxMessageDialog ErrorDlg(NULL,errorString);
//    ErrorDlg.ShowModal();
}

SMPDlg::SMPDlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
    WxMediaCtrl1 = NULL;
	CreateGUIControls();
	selItem = -1;
    lastPlayed.clear();
    nextPlay.clear();
    wxAcceleratorEntry entries[4];
    entries[0].Set(wxACCEL_NORMAL,  (int) 'Z',     ID_PREVIOUSBUTTON);
    entries[1].Set(wxACCEL_NORMAL,  (int) 'X',     ID_PLAYBUTTON);
    entries[2].Set(wxACCEL_NORMAL, (int) 'C',     ID_STOPBUTTON);
    entries[3].Set(wxACCEL_NORMAL,  (int) 'V',   ID_NEXTBUTTON );
    wxAcceleratorTable accel(4, entries);
    if(accel.IsOk())
    {
        this->SetAcceleratorTable(accel);
    }
    this->Connect(wxID_ANY,wxEVT_RIGHT_UP,wxMouseEventHandler(SMPDlg::SMPDlgRightUP));
    
    wxString path, filePath;
    if(wxGetEnv("APPDATA", &path))
    {
        path.append("\\DSMP");
        wxFileName dir;
        SMPError(path);
        filePath = path;
        filePath.append("\\settings.dsmp");
        dir.Assign(filePath);
        if(dir.FileExists() == true)
        {
            std::ifstream file;
            file.open(filePath.c_str(), std::ifstream::in);
            char name[5000];
            file.get(name,5000,'\n');
            file.seekg(1, std::ios::cur);
            int val; 
            sscanf(name,"%d",&val);
            RandomCheckbox->SetValue(val);
            file.get(name,5000,'\n');
            file.seekg(1, std::ios::cur);
            
            while(!file.eof())
            {
                wxString test = name;
                long loc = WxListCtrl1->InsertItem(WxListCtrl1->GetItemCount() + 1, test.BeforeLast(wxFileName::GetPathSeparator()).AfterLast(wxFileName::GetPathSeparator()));
                WxListCtrl1->SetItem(loc, 1, test.AfterLast(wxFileName::GetPathSeparator()).BeforeLast('.'));
                WxListCtrl1->SetItem(loc, 2, test);                
                file.get(name,5000,'\n');
                file.seekg(1, std::ios::cur);
            }
        }
    }
    
    //register hot keys
    RegisterHotKey(ID_HOT_PLAY, wxMOD_CONTROL | wxMOD_ALT, 88);
    RegisterHotKey(ID_HOT_STOP, wxMOD_CONTROL | wxMOD_ALT, 67);
    RegisterHotKey(ID_HOT_NEXT, wxMOD_CONTROL | wxMOD_ALT, 86);
    RegisterHotKey(ID_HOT_PREV, wxMOD_CONTROL | wxMOD_ALT, 90);
    WxSlider2->SetValue(long(WxMediaCtrl1->GetVolume() * 100));
     
        
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

	WxPanel1 = new wxPanel(this, ID_WXPANEL1, wxPoint(0, 0), wxSize(758, 272), wxWANTS_CHARS);
	WxBoxSizer1->Add(WxPanel1,1,wxALIGN_CENTER | wxEXPAND | wxALL,0);

	WxFlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	WxPanel1->SetSizer(WxFlexGridSizer1);
	WxPanel1->SetAutoLayout(true);

	WxPanel = new wxPanel(WxPanel1, ID_WXPANEL2, wxPoint(0, 0), wxSize(749, 42), wxWANTS_CHARS);
	WxFlexGridSizer1->Add(WxPanel,0,wxALIGN_LEFT | wxALL,0);

	wxBitmap PreviousButton_BITMAP (SMPDlg_PreviousButton_XPM);
	PreviousButton = new wxBitmapButton(WxPanel, ID_PREVIOUSBUTTON, PreviousButton_BITMAP, wxPoint(9, 3), wxSize(32, 32), wxNO_BORDER, wxDefaultValidator, wxT("PreviousButton"));

	wxBitmap PlayButton_BITMAP (SMPDlg_PlayButton_XPM);
	PlayButton = new wxBitmapButton(WxPanel, ID_PLAYBUTTON, PlayButton_BITMAP, wxPoint(48, 3), wxSize(32, 32), wxNO_BORDER, wxDefaultValidator, wxT("PlayButton"));

	wxBitmap StopButton_BITMAP (SMPDlg_StopButton_XPM);
	StopButton = new wxBitmapButton(WxPanel, ID_STOPBUTTON, StopButton_BITMAP, wxPoint(90, 3), wxSize(32, 32), wxNO_BORDER, wxDefaultValidator, wxT("StopButton"));

	wxBitmap NextButton_BITMAP (SMPDlg_NextButton_XPM);
	NextButton = new wxBitmapButton(WxPanel, ID_NEXTBUTTON, NextButton_BITMAP, wxPoint(131, 3), wxSize(32, 32), wxNO_BORDER, wxDefaultValidator, wxT("NextButton"));

	PlaylistsButton = new wxButton(WxPanel, ID_PLAYLISTS, wxT("Playlist..."), wxPoint(629, 6), wxSize(67, 27), 0, wxDefaultValidator, wxT("PlaylistsButton"));

	AddButton = new wxButton(WxPanel, ID_ADDBUTTON, wxT("Add..."), wxPoint(564, 6), wxSize(60, 27), 0, wxDefaultValidator, wxT("AddButton"));

	WxSlider1 = new wxSlider(WxPanel, ID_WXSLIDER1, 0, 0, 10, wxPoint(185, 7), wxSize(197, 24), wxSL_HORIZONTAL | wxSL_SELRANGE , wxDefaultValidator, wxT("WxSlider1"));
	WxSlider1->SetRange(0,10);
	WxSlider1->SetValue(0);

	WxSlider2 = new wxSlider(WxPanel, ID_WXSLIDER2, 0, 0, 100, wxPoint(708, 1), wxSize(18, 40), wxSL_VERTICAL | wxSL_INVERSE , wxDefaultValidator, wxT("WxSlider2"));
	WxSlider2->SetRange(0,100);
	WxSlider2->SetValue(0);

	WxMediaCtrl1 = new wxMediaCtrl(WxPanel, ID_WXMEDIACTRL1,wxT(""), wxPoint(412, 10), wxSize(0, 0) );
	WxMediaCtrl1->Show(false);
	WxMediaCtrl1->Enable(false);
	WxMediaCtrl1->ShowPlayerControls(wxMEDIACTRLPLAYERCONTROLS_NONE);

	RandomCheckbox = new wxCheckBox(WxPanel, ID_RANDOMCHECKBOX, wxT("Random"), wxPoint(498, 11), wxSize(61, 16), 0, wxDefaultValidator, wxT("RandomCheckbox"));

	WxListCtrl1 = new wxListCtrl(WxPanel1, ID_WXLISTCTRL1, wxPoint(61, 47), wxSize(627, 165), wxLC_REPORT | wxLC_AUTOARRANGE | wxLC_EDIT_LABELS, wxDefaultValidator, wxT("WxListCtrl1"));
	WxListCtrl1->InsertColumn(0,wxT("Queue"),wxLIST_FORMAT_LEFT,47 );
	WxListCtrl1->InsertColumn(0,wxT("Path"),wxLIST_FORMAT_LEFT,100 );
	WxListCtrl1->InsertColumn(0,wxT("Name"),wxLIST_FORMAT_LEFT,100 );
	WxListCtrl1->InsertColumn(0,wxT("Directory"),wxLIST_FORMAT_LEFT,100 );
	WxFlexGridSizer1->Add(WxListCtrl1,1,wxALIGN_LEFT | wxEXPAND | wxALL,5);

	WxPopupMenu1 = new wxMenu(wxT(""));WxPopupMenu1->Append(ID_MNU_PLAY_PAUSE_1019, wxT("Play/Pause"), wxT(""), wxITEM_NORMAL);
	WxPopupMenu1->Append(ID_MNU_STOP_1020, wxT("Stop"), wxT(""), wxITEM_NORMAL);
	WxPopupMenu1->Append(ID_MNU_NEXT_1021, wxT("Next"), wxT(""), wxITEM_NORMAL);
	WxPopupMenu1->Append(ID_MNU_PREVIOUS_1022, wxT("Previous"), wxT(""), wxITEM_NORMAL);
	WxPopupMenu1->Append(ID_MNU_ADDFOLDER_1023, wxT("Add Folder"), wxT(""), wxITEM_NORMAL);
	WxPopupMenu1->Append(ID_MNU_SAVEPLAYLIST_1024, wxT("Save Playlist"), wxT(""), wxITEM_NORMAL);
	WxPopupMenu1->Append(ID_MNU_LOADPLAYLIST_1025, wxT("Load Playlist"), wxT(""), wxITEM_NORMAL);

	PlaylistMenu = new wxMenu(wxT(""));PlaylistMenu->Append(ID_MNU_LOADPLAYLIST_1028, wxT("Load Playlist"), wxT(""), wxITEM_NORMAL);
	PlaylistMenu->Append(ID_MNU_SAVEPLAYLIST_1029, wxT("Save Playlist"), wxT(""), wxITEM_NORMAL);

	AddMenu = new wxMenu(wxT(""));AddMenu->Append(ID_MNU_ADDFILES_1026, wxT("Add Files"), wxT(""), wxITEM_NORMAL);
	AddMenu->Append(ID_MNU_ADDFOLDER_1027, wxT("Add Folder"), wxT(""), wxITEM_NORMAL);

	WxTimer1 = new wxTimer();
	WxTimer1->SetOwner(this, ID_WXTIMER1);

	SetTitle(wxT("DSMP"));
	SetIcon(Self_SMPDlg_XPM);
	
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
    wxString path, filePath;
    if(wxGetEnv("APPDATA", &path))
    {
        path.append("\\DSMP");
        wxFileName dir;
        SMPError(path);
        filePath = path;
        filePath.append("\\settings.dsmp");
        dir.Assign(filePath);
        if(dir.DirExists() != true)
        {
            SMPError(filePath);
            if(dir.Mkdir())
            {
                SMPError("Dir Created");
            }
            else
            {
                SMPError("Dir Created Failed");
            }
        }
        else
        {
            SMPError("Dir Found");

        }
        path.append("\\settings.dsmp");
        SMPError(path);
        wxFile file;
        file.Create(path, true);
        file.Write(wxString::Format("%d\n",RandomCheckbox->IsChecked()));
        for(int iCount = 0; iCount < WxListCtrl1->GetItemCount(); iCount++)
        {
            wxListItem item;
            item.SetId(iCount);
            item.SetMask(wxLIST_MASK_TEXT);
            /*WxListCtrl1->GetItem(item);
            file.Write(item.GetText() + "|");
            item.SetColumn(1);
            WxListCtrl1->GetItem(item);
            file.Write(item.GetText() + "|");*/
            item.SetColumn(2);
            WxListCtrl1->GetItem(item);
            file.Write(item.GetText() + "\n");
            item.Clear();            
        }
        file.Close();
    }
    
    
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
	if(isPlaying)
	{
        //Pause now 
        WxMediaCtrl1->Pause();
        //SMPError("CalledPause");
        isPlaying = false;
    	wxBitmap PlayButton_normal_BITMAP (SMPDlg_PlayButton_XPM);
    	PlayButton->SetBitmapLabel(PlayButton_normal_BITMAP);


    	wxBitmap PlayButton_hover_BITMAP (Play_Hover_xpm);
    	PlayButton->SetBitmapHover(PlayButton_hover_BITMAP);

    	wxBitmap PlayButton_click_BITMAP (Play_Clickl_xpm);
    	PlayButton->SetBitmapSelected(PlayButton_click_BITMAP);
    }
    else
    {
        //Play now
        if(WxMediaCtrl1->GetState() == wxMEDIASTATE_PAUSED)
        {
            if(WxMediaCtrl1->Play());
            //SMPError("Now Playing");
        }
        else
        {
            PlayNextFile();
            //SMPError("Now Playing Next File");
        }
        isPlaying = true;

        wxBitmap PauseButton_normal_BITMAP (Pause_Normal_xpm);
        PlayButton->SetBitmapLabel(PauseButton_normal_BITMAP);
        
        
        wxBitmap PauseButton_hover_BITMAP (Pause_Hover_xpm);
        PlayButton->SetBitmapHover(PauseButton_hover_BITMAP);
        
        wxBitmap PauseButton_click_BITMAP (Pause_Click_xpm);
        PlayButton->SetBitmapSelected(PauseButton_click_BITMAP);       
    }
	
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
	wxListItem temp;
	temp.Clear();
	temp.SetId(selItem);
	temp.SetMask(wxLIST_MASK_STATE);
	temp.SetState(~wxLIST_STATE_SELECTED);
	WxListCtrl1->SetItemState(selItem,~wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED);	
    PlayNextFile();
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
    isPlaying = true;
}

/*
 * WxMediaCtrl1MediaStop
 */
void SMPDlg::WxMediaCtrl1MediaStop(wxMediaEvent& event)
{
	// insert your code here
    isPlaying = false;

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
    PlayNextFile();
	
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
    	if( WxMediaCtrl1->Load(path) == false)
    	{
            PlayNextFile();
            return;
        }
    	lastPlayed.push_front(path);
    	temp.SetColumn(1);
    	temp.SetMask(wxLIST_MASK_TEXT);
    	if( WxListCtrl1->GetItem( temp))
    	{
            this->SetTitle(wxString::Format("DSMP - %s - %s",name.c_str(), temp.GetText().c_str()));
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
	wxBitmap PauseButton_normal_BITMAP (Pause_Normal_xpm);
	PlayButton->SetBitmapLabel(PauseButton_normal_BITMAP);


	wxBitmap PauseButton_hover_BITMAP (Pause_Hover_xpm);
	PlayButton->SetBitmapHover(PauseButton_hover_BITMAP);

	wxBitmap PauseButton_click_BITMAP (Pause_Click_xpm);
	PlayButton->SetBitmapSelected(PauseButton_click_BITMAP);    	
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
        //add current one to queue
        case WXK_INSERT:
            item = WxListCtrl1->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
            if(item != -1) 
            {
                wxListItem tempItem;
                tempItem.SetId(item);
                tempItem.SetColumn(2);
                tempItem.SetMask(wxLIST_MASK_TEXT);
                WxListCtrl1->GetItem(tempItem);
                SMPError(tempItem.GetText());
                nextPlay.push_back(tempItem.GetText());
                WxListCtrl1->SetItem(item,3,wxString::Format("%d",nextPlay.size()));
            }
            break;
            
        case 'A':
            
                if(wxGetKeyState(WXK_CONTROL))
                {
                    item = -1;
                    while( (item = WxListCtrl1->GetNextItem(item)) != -1)
                    {
                        WxListCtrl1->SetItemState(item, wxLIST_STATE_SELECTED , wxLIST_STATE_SELECTED);                        
                    }
                }
                    
            
            break;

    }
}

/*
 * PreviousButtonClick
 */
void SMPDlg::PreviousButtonClick(wxCommandEvent& event)
{
	// insert your code here
    //SMPError("0");
	if(lastPlayed.size() >= 1)
	{
        //SMPError("1");
        if(isPlaying)
            lastPlayed.pop_front();
    	if(lastPlayed.size() >= 1)
    	{
            //SMPError("1");
            wxString path = lastPlayed.front();
            lastPlayed.pop_front();
            long item = WxListCtrl1->GetNextItem(-1, wxLIST_NEXT_ALL);
            while ( item != -1 )
            {
                //SMPError("2");
                wxListItem temp;
                temp.SetId(item);
            	temp.SetColumn(2);
            	temp.SetMask(wxLIST_MASK_TEXT);
            	WxListCtrl1->GetItem( temp);
            	if( temp.GetText() == path)
            	{
                	WxMediaCtrl1->Stop();
                	wxListItem temp;
                	temp.Clear();
                	temp.SetId(selItem);
                	temp.SetMask(wxLIST_MASK_STATE);
                	temp.SetState(~wxLIST_STATE_SELECTED);
                	WxListCtrl1->SetItemState(selItem,~wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED);
                    
                    PlayThisFile(item);
                    //SMPError("4");
                    return;
                }
                        
    
                //wxLogMessage(_T("Item %ld deleted"), item);
    
              
                item = WxListCtrl1->GetNextItem(item, wxLIST_NEXT_ALL);
            }
            
        }
    }
    lastPlayed.clear();
    long item = WxListCtrl1->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    while ( item != -1 )
    {
       	WxListCtrl1->SetItemState(item,~wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED);
        
        //wxLogMessage(_T("Item %ld deleted"), item);
        //SMPError(wxString::Format("Unselected item ID %d",item));

        item = WxListCtrl1->GetNextItem(item,
                           wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    }
    PlayFileNow();

}

/*
 * StopButtonClick
 */
void SMPDlg::StopButtonClick(wxCommandEvent& event)
{
	// insert your code here
	WxMediaCtrl1->Stop();
	wxListItem temp;
	temp.Clear();
	temp.SetId(selItem);
	temp.SetMask(wxLIST_MASK_STATE);
	temp.SetState(~wxLIST_STATE_SELECTED);
	WxListCtrl1->SetItemState(selItem,~wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED);	
	wxBitmap PlayButton_normal_BITMAP (SMPDlg_PlayButton_XPM);
	PlayButton->SetBitmapLabel(PlayButton_normal_BITMAP);


	wxBitmap PlayButton_hover_BITMAP (Play_Hover_xpm);
	PlayButton->SetBitmapHover(PlayButton_hover_BITMAP);

	wxBitmap PlayButton_click_BITMAP (Play_Clickl_xpm);
	PlayButton->SetBitmapSelected(PlayButton_click_BITMAP);	
	
}

// No description
void SMPDlg::PlayNextFile()
{
	/* TODO (#1#): Implement SMPDlg::PlayNextFile() */
   	int itemCount = WxListCtrl1->GetItemCount();
	if(itemCount < 1)
	   return;
	//SMPError(wxString::Format("%d",itemCount));
	
	
	if(nextPlay.size() > 0)
    {
        PlayFromQueue();
    }
    else 
    {
       if(RandomCheckbox->IsChecked())
    	   selItem = (itemCount - long(floor(rand() * 10000000))%itemCount) % itemCount  ;
    	else
    	{
            selItem = (selItem + 1) % itemCount;
        }
    	//SMPError(wxString::Format("%d",selItem));
    	PlayThisFile(selItem);
    }
}

/*
 * RandomCheckboxClick
 */
void SMPDlg::RandomCheckboxClick(wxCommandEvent& event)
{
	// insert your code here
	SMPError(wxString::Format("Random %d",RandomCheckbox->IsChecked()));
	//RandomCheckbox->SetValue(1 - RandomCheckbox->IsChecked());
	//SMPError(wxString::Format("Random %d",RandomCheckbox->IsChecked()));
	
}

// No description
void SMPDlg::AddToQueue(wxCommandEvent &event)
{
	/* TODO (#1#): Implement SMPDlg::AddToQueue() */
}

// No description
void SMPDlg::PlayFromQueue()
{
	/* TODO (#1#): Implement SMPDlg::PlayFromQueue() */
	if(nextPlay.size() > 0) 
	{
        wxString path = nextPlay.front();
        nextPlay.pop_front();
        wxListItem item;
        long iCount;
        for(iCount = 0; iCount < WxListCtrl1->GetItemCount(); iCount++)
        {
            item.SetId(iCount);
            item.SetColumn(2);
            item.SetMask(wxLIST_MASK_TEXT);
            WxListCtrl1->GetItem(item);
            if(item.GetText() == path)
            {
                break;
            }
        }
        selItem = iCount;
        for(iCount = 0; iCount < WxListCtrl1->GetItemCount(); iCount++)
        {
            item.SetId(iCount);
            item.SetColumn(3);
            item.SetMask(wxLIST_MASK_TEXT);
            WxListCtrl1->GetItem(item);
            if(item.GetText() != wxString(""))
            {
                wxString ChangeString = item.GetText();
                long value;
                ChangeString.ToLong(&value, 10);
                if(value == 1)
                {
                    item.SetText("");
                }
                else
                {
                    item.SetText(wxString::Format("%d",(value - 1)));
                }
                WxListCtrl1->SetItem(item);            
            }
        }
        PlayThisFile(selItem);
    }
}

/*
 * WxButton2Click
 */
void SMPDlg::WxButton2Click(wxCommandEvent& event)
{
	// insert your code here
	wxFileDialog dlg(this, "Select the mp3 files to add to library","","","mp3 files(*mp3)|*.mp3",
                      wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_MULTIPLE  );
	if( dlg.ShowModal() == wxID_OK)
	{
        SMPError("Get Files list");
        wxArrayString files;
        dlg.GetPaths(files);
        for(int iCount = 0; iCount < files.Count(); iCount++)
        {
            SMPError(files[iCount]);
            wxString temp = files[iCount];
            //SMPError(temp);
            temp = getDirNameFromString(temp);
            int start = -1;
            int found = 0;
            while((start = WxListCtrl1->FindItem(start,files[iCount].BeforeLast(wxFileName::GetPathSeparator()).AfterLast(wxFileName::GetPathSeparator()))) != -1)
            {
            	wxListItem itemp;
            	itemp.SetId(start);
            	itemp.SetColumn(2);
            	itemp.SetMask(wxLIST_MASK_TEXT);
            	WxListCtrl1->GetItem(itemp);
            	//SMPError(itemp.GetText());
            	if( itemp.GetText() == files[iCount])
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
            long loc = WxListCtrl1->InsertItem(WxListCtrl1->GetItemCount() + 1, files[iCount].BeforeLast(wxFileName::GetPathSeparator()).AfterLast(wxFileName::GetPathSeparator()));
            WxListCtrl1->SetItem(loc, 1, files[iCount].AfterLast(wxFileName::GetPathSeparator()).BeforeLast('.'));
            WxListCtrl1->SetItem(loc, 2, files[iCount]);
            
        }
    }
}

/*
 * SavePlaylistClick
 */
void SMPDlg::SavePlaylistClick(wxCommandEvent& event)
{
	// insert your code here
	wxFileDialog dlg(this, "Save Playlist as ...", "", "", "DSMP Playlist(*.dspp)|*.dspp", 
                    wxFD_SAVE|wxFD_OVERWRITE_PROMPT|wxFD_CHANGE_DIR);
    if(dlg.ShowModal() == wxID_OK)
    {
        wxString path = dlg.GetPath();
        wxFile file;
        file.Create(path, true);
        file.Write("DSMP Playlist\n");
        for(int iCount = 0; iCount < WxListCtrl1->GetItemCount(); iCount++)
        {
            wxListItem item;
            item.SetId(iCount);
            item.SetMask(wxLIST_MASK_TEXT);
            /*WxListCtrl1->GetItem(item);
            file.Write(item.GetText() + "|");
            item.SetColumn(1);
            WxListCtrl1->GetItem(item);
            file.Write(item.GetText() + "|");*/
            item.SetColumn(2);
            WxListCtrl1->GetItem(item);
            file.Write(item.GetText() + "\n");
            item.Clear();            
            
        }
        file.Close();
    }
}

/*
 * SavePlaylistUpdateUI0
 */
void SMPDlg::SavePlaylistUpdateUI0(wxUpdateUIEvent& event)
{
	// insert your code here
}

/*
 * WxListCtrl1RightClick
 */
void SMPDlg::WxListCtrl1RightClick(wxListEvent& event)
{
	// insert your code here
	SMPError("right click");
	PopupMenu(WxPopupMenu1,0,0);
}

/*
 * SMPDlgRightUP
 */
void SMPDlg::SMPDlgRightUP(wxMouseEvent& event)
{
	// insert your code here
	SMPError("right click2");
	PopupMenu(WxPopupMenu1,event.GetX(),event.GetY());
}

/*
 * LoadPlaylistClick
 */
void SMPDlg::LoadPlaylistClick(wxCommandEvent& event)
{
	// insert your code here
	wxFileDialog dlg(this, "Select the Playlist to load","","","DSMP Playlist(*.dspp)|*.dspp",
                    wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if(dlg.ShowModal())
    {
        wxString path = dlg.GetPath();
        std::ifstream file;
        SMPError(path);
        file.open(path.c_str(),std::ifstream::in);
        char teststr[5000];
        if(!file.eof())
        {
            file.get(teststr,5000,'\n');
            SMPError(teststr);
            if(strcmp(teststr,"DSMP Playlist") == 0)
            {
                file.seekg(1, std::ios::cur);
                file.get(teststr,5000,'\n');                
                while(!file.eof())
                {
                    wxString test(teststr, strlen(teststr));
                    wxString temp = test;
                    SMPError(teststr);
                    temp = getDirNameFromString(temp);
                    int start = -1;
                    int found = 0;
                    while((start = WxListCtrl1->FindItem(start,test.BeforeLast(wxFileName::GetPathSeparator()).AfterLast(wxFileName::GetPathSeparator()))) != -1)
                    {
                        if(WxListCtrl1->GetItemCount() < 1)
                            break;
                    	wxListItem itemp;
                    	itemp.SetId(start);
                    	itemp.SetColumn(2);
                    	itemp.SetMask(wxLIST_MASK_TEXT);
                    	WxListCtrl1->GetItem(itemp);
                    	//SMPError(itemp.GetText());
                    	if( itemp.GetText() == test)
                    	{
                            found = 1;
                        	//SMPError(test);
        
                            break;
                        }
                        start = start + 1;
                        if(start > WxListCtrl1->GetItemCount())
                            break;
                    }
                    if(found != 1)
                    {
                        long loc = WxListCtrl1->InsertItem(WxListCtrl1->GetItemCount() + 1, test.BeforeLast(wxFileName::GetPathSeparator()).AfterLast(wxFileName::GetPathSeparator()));
                        WxListCtrl1->SetItem(loc, 1, test.AfterLast(wxFileName::GetPathSeparator()).BeforeLast('.'));
                        WxListCtrl1->SetItem(loc, 2, test);
                    }
                    file.seekg(1, std::ios::cur);
                    file.get(teststr,5000,'\n'); 
                    
                }
                file.close();
            }
        }

    }
}

/*
 * SMPDlgDropFiles
 */
void SMPDlg::SMPDlgDropFiles(wxDropFilesEvent& event)
{
	// insert your code here
	SMPError(event.GetFiles()[0]);
}

/*
 * WxListCtrl1ColRightClick
 */
void SMPDlg::WxListCtrl1ColRightClick(wxListEvent& event)
{
	// insert your code here
		SMPError("right click9");
	PopupMenu(WxPopupMenu1,0,0);
}

/*
 * AddButtonClick
 */
void SMPDlg::AddButtonClick(wxCommandEvent& event)
{
	// insert your code here
	int x, y, height, width;
	AddButton->GetPosition(&x,&y);
	AddButton->GetSize(&width, &height);
	PopupMenu(AddMenu,x , y + height - 1);
}

/*
 * PlaylistsButtonClick
 */
void SMPDlg::PlaylistsButtonClick(wxCommandEvent& event)
{
	// insert your code here
	int x, y, height, width;
	PlaylistsButton->GetPosition(&x,&y);
	PlaylistsButton->GetSize(&width, &height);
	PopupMenu(PlaylistMenu,x, y + height - 1);

}

// No description
void SMPDlg::HotKeyPlay(wxKeyEvent &event)
{
	// insert your code here
	if(isPlaying)
	{
        //Pause now 
        WxMediaCtrl1->Pause();
        //SMPError("CalledPause");
        isPlaying = false;
    	wxBitmap PlayButton_normal_BITMAP (SMPDlg_PlayButton_XPM);
    	PlayButton->SetBitmapLabel(PlayButton_normal_BITMAP);


    	wxBitmap PlayButton_hover_BITMAP (Play_Hover_xpm);
    	PlayButton->SetBitmapHover(PlayButton_hover_BITMAP);

    	wxBitmap PlayButton_click_BITMAP (Play_Clickl_xpm);
    	PlayButton->SetBitmapSelected(PlayButton_click_BITMAP);
    }
    else
    {
        //Play now
        if(WxMediaCtrl1->GetState() == wxMEDIASTATE_PAUSED)
        {
            WxMediaCtrl1->Play();
            //SMPError("Now Playing");
        }
        else
        {
            PlayNextFile();
            //SMPError("Now Playing Next File");
        }
        isPlaying = true;

        wxBitmap PauseButton_normal_BITMAP (Pause_Normal_xpm);
        PlayButton->SetBitmapLabel(PauseButton_normal_BITMAP);
        
        
        wxBitmap PauseButton_hover_BITMAP (Pause_Hover_xpm);
        PlayButton->SetBitmapHover(PauseButton_hover_BITMAP);
        
        wxBitmap PauseButton_click_BITMAP (Pause_Click_xpm);
        PlayButton->SetBitmapSelected(PauseButton_click_BITMAP);       
    }
}
/*
 * HotNextButton
 */
void SMPDlg::HotKeyNext(wxKeyEvent& event)
{
	// insert your code here
	WxMediaCtrl1->Stop();
	wxListItem temp;
	temp.Clear();
	temp.SetId(selItem);
	temp.SetMask(wxLIST_MASK_STATE);
	temp.SetState(~wxLIST_STATE_SELECTED);
	WxListCtrl1->SetItemState(selItem,~wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED);
    PlayNextFile();
	
}

/*
 * HotKeyStop
 */
void SMPDlg::HotKeyStop(wxKeyEvent& event)
{
	// insert your code here
	WxMediaCtrl1->Stop();
	wxListItem temp;
	temp.Clear();
	temp.SetId(selItem);
	temp.SetMask(wxLIST_MASK_STATE);
	temp.SetState(~wxLIST_STATE_SELECTED);
	WxListCtrl1->SetItemState(selItem,~wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED);	
	wxBitmap PlayButton_normal_BITMAP (SMPDlg_PlayButton_XPM);
	PlayButton->SetBitmapLabel(PlayButton_normal_BITMAP);


	wxBitmap PlayButton_hover_BITMAP (Play_Hover_xpm);
	PlayButton->SetBitmapHover(PlayButton_hover_BITMAP);

	wxBitmap PlayButton_click_BITMAP (Play_Clickl_xpm);
	PlayButton->SetBitmapSelected(PlayButton_click_BITMAP);	
	
}

/*
 * HotKeyPrev
 */
void SMPDlg::HotKeyPrev(wxKeyEvent& event)
{
	// insert your code here
    //SMPError("0");
	if(lastPlayed.size() >= 1)
	{
        //SMPError("1");
        if(isPlaying)
            lastPlayed.pop_front();
    	if(lastPlayed.size() >= 1)
    	{
            //SMPError("1");
            wxString path = lastPlayed.front();
            lastPlayed.pop_front();
            long item = WxListCtrl1->GetNextItem(-1, wxLIST_NEXT_ALL);
            while ( item != -1 )
            {
                //SMPError("2");
                wxListItem temp;
                temp.SetId(item);
            	temp.SetColumn(2);
            	temp.SetMask(wxLIST_MASK_TEXT);
            	WxListCtrl1->GetItem( temp);
            	if( temp.GetText() == path)
            	{
                	WxMediaCtrl1->Stop();
                	wxListItem temp;
                	temp.Clear();
                	temp.SetId(selItem);
                	temp.SetMask(wxLIST_MASK_STATE);
                	temp.SetState(~wxLIST_STATE_SELECTED);
                	WxListCtrl1->SetItemState(selItem,~wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED);
                    
                    PlayThisFile(item);
                    //SMPError("4");
                    return;
                }
                        
    
                //wxLogMessage(_T("Item %ld deleted"), item);
    
              
                item = WxListCtrl1->GetNextItem(item, wxLIST_NEXT_ALL);
            }
            
        }
    }
    lastPlayed.clear();
    long item = WxListCtrl1->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    while ( item != -1 )
    {
       	WxListCtrl1->SetItemState(item,~wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED);
        
        //wxLogMessage(_T("Item %ld deleted"), item);
        //SMPError(wxString::Format("Unselected item ID %d",item));

        item = WxListCtrl1->GetNextItem(item,
                           wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    }
    if(nextPlay.size() > 0)
    {
        PlayFromQueue();
    }
    else if(RandomCheckbox->IsChecked()) 
        PlayNextFile();
    else
    {
        int itemCount = WxListCtrl1->GetItemCount();
        if(itemCount < 1)
           return;
        //SMPError(wxString::Format("%d",itemCount));
            if(selItem <=0)
                selItem = itemCount - 1;
            else
                selItem = ( selItem - 1) % itemCount;
        PlayThisFile(selItem);        
    }

}

// No description
void SMPDlg::PlayFileNow()
{
    if(nextPlay.size() > 0)
    {
        PlayFromQueue();
    }
    else if(RandomCheckbox->IsChecked()) 
        PlayNextFile();
    else
    {
        int itemCount = WxListCtrl1->GetItemCount();
        if(itemCount < 1)
           return;
        //SMPError(wxString::Format("%d",itemCount));
            if(selItem <=0)
                selItem = itemCount - 1;
            else
                selItem = ( selItem - 1) % itemCount;
        PlayThisFile(selItem);        
    }
	
}
