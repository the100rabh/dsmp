//---------------------------------------------------------------------------
//
// Name:        SMPDlg.h
// Author:      100rabh
// Created:     29-Dec-08 3:40:27 PM
// Description: SMPDlg class declaration
//
//---------------------------------------------------------------------------

#ifndef __SMPDLG_h__
#define __SMPDLG_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif

#include "filelist.h"
#include <list>


//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/menu.h>
#include <wx/timer.h>
#include <wx/listctrl.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/mediactrl.h>
#include <wx/slider.h>
#include <wx/button.h>
#include <wx/bmpbuttn.h>
#include <wx/panel.h>
#include <wx/sizer.h>
////Header Include End

////Dialog Style Start
#undef SMPDlg_STYLE
#define SMPDlg_STYLE wxWANTS_CHARS | wxALWAYS_SHOW_SB | wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxTHICK_FRAME | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class SMPDlg : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		SMPDlg(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("SMP"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = SMPDlg_STYLE);
	public:
		// No description
		void AddToQueue(wxCommandEvent &event);
		virtual ~SMPDlg();
		void WxButton1Click(wxCommandEvent& event);
		void WxMediaCtrl1MediaLoaded(wxMediaEvent& event);
		void PlayButtonClick(wxCommandEvent& event);
		void WxMediaCtrl1MediaFinished(wxMediaEvent& event);
		void WxMediaCtrl1MediaPause(wxMediaEvent& event);
		void WxMediaCtrl1MediaPlay(wxMediaEvent& event);
		void WxMediaCtrl1MediaStop(wxMediaEvent& event);
		void WxTimer1Timer(wxTimerEvent& event);
		void WxSlider2Scroll(wxScrollEvent& event);
		void WxSlider1Scroll(wxScrollEvent& event);
		void NextButtonClick(wxCommandEvent& event);
		void WxListCtrl1ItemActivated(wxListEvent& event);
		void WxListCtrl1KeyDown(wxListEvent& event);
		void PreviousButtonClick(wxCommandEvent& event);
	public:
		// No description
		void PlayFileNow();
		void StopButtonClick(wxCommandEvent& event);
		void RandomCheckboxClick(wxCommandEvent& event);
		void WxButton2Click(wxCommandEvent& event);
		void SavePlaylistClick(wxCommandEvent& event);
		void WxListCtrl1RightClick(wxListEvent& event);
		void SavePlaylistUpdateUI0(wxUpdateUIEvent& event);
		void SMPDlgRightUP(wxMouseEvent& event);
		void LoadPlaylistClick(wxCommandEvent& event);
		void SMPDlgDropFiles(wxDropFilesEvent& event);
		void WxListCtrl1ColRightClick(wxListEvent& event);
		void AddButtonClick(wxCommandEvent& event);
		void PlaylistsButtonClick(wxCommandEvent& event);
		// No description
		void HotKeyNext(wxKeyEvent &event);
		void HotKeyStop(wxKeyEvent &event);
		void HotKeyPlay(wxKeyEvent &event);
		void HotKeyPrev(wxKeyEvent &event);
		void WxListCtrl1ColLeftClick(wxListEvent& event);
		void FindButtonClick(wxCommandEvent& event);		
		void FindTextEditEnter(wxCommandEvent& event);
		void FindNextButtonClick(wxCommandEvent& event);
		void FindPrevButtonClick(wxCommandEvent& event);
	
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxMenu *PlaylistMenu;
		wxMenu *WxPopupMenu1;
		wxMenu *AddMenu;
		wxTimer *WxTimer1;
		wxListCtrl *WxListCtrl1;
		wxButton *FindPrevButton;
		wxButton *FindNextButton;
		wxTextCtrl *FindTextEdit;
		wxStaticText *WxStaticText1;
		wxPanel *SearchPanel;
		wxButton *FindButton;
		wxCheckBox *RandomCheckbox;
		wxMediaCtrl *WxMediaCtrl1;
		wxSlider *WxSlider2;
		wxSlider *WxSlider1;
		wxButton *AddButton;
		wxButton *PlaylistsButton;
		wxBitmapButton *NextButton;
		wxBitmapButton *StopButton;
		wxBitmapButton *PlayButton;
		wxBitmapButton *PreviousButton;
		wxPanel *WxPanel;
		wxFlexGridSizer *WxFlexGridSizer1;
		wxPanel *WxPanel1;
		wxBoxSizer *WxBoxSizer1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_MNU_LOADPLAYLIST_1028 = 1028,
			ID_MNU_SAVEPLAYLIST_1029 = 1029,
			
			ID_MNU_PLAY_PAUSE_1019 = 1019,
			ID_MNU_STOP_1020 = 1020,
			ID_MNU_NEXT_1021 = 1021,
			ID_MNU_PREVIOUS_1022 = 1022,
			ID_MNU_ADDFOLDER_1023 = 1023,
			ID_MNU_SAVEPLAYLIST_1024 = 1024,
			ID_MNU_LOADPLAYLIST_1025 = 1025,
			
			ID_MNU_ADDFILES_1026 = 1026,
			ID_MNU_ADDFOLDER_1027 = 1027,
			
			ID_WXTIMER1 = 1017,
			ID_WXLISTCTRL1 = 1015,
			ID_FINDPREVBUTTON = 1034,
			ID_FINDNEXTBUTTON = 1033,
			ID_FINDEDITTXT = 1044,
			ID_WXSTATICTEXT1 = 1032,
			ID_SEARCHPANEL = 1031,
			ID_FINDBUTTON = 1030,
			ID_RANDOMCHECKBOX = 1018,
			ID_WXMEDIACTRL1 = 1016,
			ID_WXSLIDER2 = 1014,
			ID_WXSLIDER1 = 1013,
			ID_ADDBUTTON = 1008,
			ID_PLAYLISTS = 1007,
			ID_NEXTBUTTON = 1006,
			ID_STOPBUTTON = 1005,
			ID_PLAYBUTTON = 1004,
			ID_PREVIOUSBUTTON = 1003,
			ID_WXPANEL2 = 1002,
			ID_WXPANEL1 = 1011,
			////GUI Enum Control ID End
			ID_HOT_PLAY,
			ID_HOT_STOP,
			ID_HOT_NEXT,
			ID_HOT_PREV,
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
	protected:
		// No description
		void AddFilesFromFolder(wxString FileName);
		FileList Dirs, Files;
		wxTreeItemId root;	
        bool isPlaying;	
        long selItem;
		// No description
		void PlayThisFile(long id);
		// No description
		void PlayFromQueue();
		std::list<wxString> lastPlayed, nextPlay;
		// No description
		void PlayNextFile();
		void DeselectAllFiles();
		
};

#endif
