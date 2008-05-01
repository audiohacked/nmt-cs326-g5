#include "AppMain.h"

#include "enum.h" // needed for the MENU_Quit and etc.

/* we have here is the event table used for event handling
	I still have no idea how this works
	*/
	
// Event Table for frame - used for menu
BEGIN_EVENT_TABLE( DDPSFrame, wxFrame )
	EVT_MENU(MENU_Quit, DDPSFrame::OnExit) /* when we click Quit in the menu system this event closes	the window and cleans up */
	EVT_MENU(MENU_About, DDPSFrame::AboutBox) /* when we click Help->About_This_App this event opens the about box */
	EVT_MENU(MENU_Support, DDPSFrame::GoToSupportPanel)
	EVT_MENU(MENU_Settings, DDPSFrame::SettingsDialog) // open the settings dialog when file->settings is clicked
	EVT_MENU(MENU_Home, DDPSFrame::GotoHomepage)
	EVT_MENU(MENU_Community, DDPSFrame::GotoCommunity)
	EVT_MENU(MENU_Downloads, DDPSFrame::GotoDownloads)

END_EVENT_TABLE()

BEGIN_EVENT_TABLE( DDPSTabbed, wxNotebook )
	//EVT_NOTEBOOK_PAGE_CHANGED(wxID_ANY, DDPSTabbed::OnNotebook)
	//EVT_NOTEBOOK_PAGE_CHANGING(wxID_ANY, DDPSTabbed::OnNotebook)
END_EVENT_TABLE()

// Event table for DDPSPanel buttons at the bottom of the program
BEGIN_EVENT_TABLE( DDPSPanel, wxPanel )
	EVT_BUTTON(TABB_News, DDPSPanel::GotoNewsTab)
	EVT_BUTTON(TABB_Support, DDPSPanel::GotoSupport)
	EVT_BUTTON(TABB_Settings, DDPSFrame::SettingsDialog)
END_EVENT_TABLE()

IMPLEMENT_APP(DDPS)

bool DDPS::OnInit()
{
	#ifdef __DDPS_PROTOCOL_H
		wxFileSystem::AddHandler(new wxInternetFSHandler());
		wxFileSystem::AddHandler(new wxZipFSHandler());
		wxFileSystem::AddHandler(new wxMemoryFSHandler());
	#endif
	
	#ifdef __DDPS_PROTOCOL_H
		const wxUId id = {(wxUint32)0x8a2bcf71,(wxUint16)0x3f5b,(wxUint16)0x4559,
			{(wxUint8)0x89, (wxUint8)0x0f,(wxUint8)0xf3,(wxUint8)0xc2,(wxUint8)0xe9,(wxUint8)0x8e,
			(wxUint8)0xa7,(wxUint8)0x01}};
		wxRegisterProtocolHandler(wxT("The DDPS protocol handler"), wxT("ddps"), id, &(ddpsProtocolHandler::Create));
	#endif
	
	DDPSFrame *frame = new DDPSFrame(_T("DDPSFrame"), wxPoint(50, 50), wxSize(800,600));

	frame->Show(TRUE);

	SetTopWindow(frame);
	return TRUE;
}

DDPSFrame::DDPSFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
: wxFrame((wxFrame*) NULL, -1, title, pos, size)
{
	CreateStatusBar(2);
	SetStatusText(wxT("Ready!"), 0);
	DDPSMenu *menu = new DDPSMenu();
	SetMenuBar(menu);
	panel = new DDPSPanel(this, -1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL|wxNO_BORDER);
	
	AppLoginDialog loginDlg(this, -1, wxT("User Login"), wxDefaultPosition, wxDefaultSize);
	if(loginDlg.ShowModal() == wxID_OK)
	{
		panel->SetFocus();
	} else {
		Close(TRUE);
	}
}

void DDPSFrame::OnExit(wxCommandEvent& WXUNUSED(event))
{
	Close(TRUE);
}

void DDPSFrame::AboutBox(wxCommandEvent& WXUNUSED(event))
{
	//#ifdef __WXMAC__
		wxAboutDialogInfo info;
		info.SetName(wxT("DDPS"));
		info.SetVersion(wxT("1.0 Beta"));
		info.SetDescription(wxT("This Program is a Digital Content Distribution and Publishing System."));
		info.SetCopyright(wxT("(C) 2008 Sean Nelson <snelson@nmt.edu>"));
		wxAboutBox(info);
	//#endif
}

void DDPSFrame::GoToSupportPanel(wxCommandEvent& event)
{
	panel->GotoSupport(event);
}

void DDPSFrame::GotoHomepage(wxCommandEvent& event)
{
	panel->GotoHomepage(event);
}

void DDPSFrame::GotoCommunity(wxCommandEvent& event)
{
	panel->GotoCommunity(event);
}

void DDPSFrame::GotoDownloads(wxCommandEvent& event)
{
	panel->GotoDownloads(event);
}

//open the settings dialog
void DDPSFrame::SettingsDialog(wxCommandEvent& WXUNUSED(event))
{
	SettingsFrame *settingsFrame = new SettingsFrame(_T("Settings"), wxPoint(50, 50), wxSize(400,300));
	settingsFrame->Show(TRUE);
}

DDPSPanel::DDPSPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos,
	const wxSize &size, long style) : wxPanel(parent, id, pos, size, style)
{
	tabs = new DDPSTabbed(this, -1, wxDefaultPosition, wxDefaultSize, wxNB_FIXEDWIDTH);
	
	wxButton *News = new wxButton(this, TABB_News, wxT("News"));
	wxButton *Settings = new wxButton(this, TABB_Settings, wxT("Settings"));
	wxButton *Support = new wxButton(this, TABB_Support, wxT("Support"));
	//wxButton *InstaMessenger = new wxButton(this, -1, wxT("InstaMessenger"));

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *button_sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(tabs, 1, wxEXPAND|wxALL, 5);
	sizer->Add(button_sizer, 0, wxALIGN_BOTTOM, 5);
	button_sizer->Add(News, 0, wxALL, 10);
	button_sizer->Add(Settings, 0, wxALL, 10);
	button_sizer->Add(Support, 0, wxALL, 10);
	//button_sizer->Add(InstaMessenger, 0, wxALL, 10);
	SetSizer(sizer);
	sizer->SetSizeHints(this);
}

void DDPSPanel::GotoNewsTab(wxCommandEvent& WXUNUSED(event))
{
	#ifdef BUILTIN_BROWSER
		if ( tabs )
		{
			if (tabs->Home->browser)
			{
				#ifdef NEWSPAGE
				tabs->Home->browser->LoadURL(wxT(NEWSPAGE));
				#else
				tabs->Home->browser->LoadURL(wxT("coreyb.homelinux.org/contentmanager/news"));
				#endif
			}
			tabs->ChangeSelection(0);
		}
	#endif
}

void DDPSPanel::GotoSupport(wxCommandEvent& WXUNUSED(event))
{
	#ifdef BUILTIN_BROWSER
		if ( tabs )
		{
			if (tabs->Home->browser)
			{
				#ifdef SUPPORTPAGE
				tabs->Home->browser->LoadURL(wxT(SUPPORTPAGE));
				#else
				tabs->Home->browser->LoadURL(wxT("coreyb.homelinux.org/contentmanager/support"));
				#endif
			}
			tabs->ChangeSelection(0);
		}
	#else
	
	#endif
	
}

void DDPSPanel::GotoHomepage(wxCommandEvent& event)
{
	#ifdef BUILTIN_BROWSER
		tabs->ChangeSelection(0);
	#endif
}

void DDPSPanel::GotoCommunity(wxCommandEvent& event)
{
	#ifdef BUILTIN_BROWSER
		tabs->ChangeSelection(1);
	#elif COMMUNITY_PORTAL
		tabs->ChangeSelection(0);
	#endif
}

void DDPSPanel::GotoDownloads(wxCommandEvent& event)
{
	#ifdef BUILTIN_BROWSER
		tabs->ChangeSelection(2);
	#elif COMMUNITY_PORTAL
		tabs->ChangeSelection(1);
	#else
		tabs->ChangeSelection(0);
	#endif
}

DDPSTabbed::DDPSTabbed(wxWindow *parent, wxWindowID id, const wxPoint &pos,
	 const wxSize &size, long style) : wxNotebook(parent, id, pos, size, style)
{
	#ifdef BUILTIN_BROWSER
		Home = new DDPSBrowser(this, TABPAGE_Browser, 
			wxDefaultPosition, wxDefaultSize);
		#ifdef HOMEPAGE
		Home->home = wxT(HOMEPAGE);
		#else
		Home->home = wxT("coreyb.homelinux.org/contentmanager");
		#endif
		Home->GotoHomepage();
		AddPage(Home, _T("Browser"));
	#endif
	
	#ifdef COMMUNITY_PORTAL
		Community = new DDPSBrowser(this, TABPAGE_Community, 
			wxDefaultPosition, wxDefaultSize);
		#ifdef COMMUNITYPAGE
		Community->home = wxT(COMMUNITYPAGE);
		#else
		Community->home = wxT("coreyb.homelinux.org/contentmanager/community");
		#endif
		Community->GotoHomepage();
		AddPage(Community, _T("Community"));
	#endif

	#ifdef __TRANSFER_MANAGER_H
		wxPanel *Downloads = new TransferManager(this, -1, wxDefaultPosition, 
			wxDefaultSize, wxTAB_TRAVERSAL|wxCLIP_CHILDREN|wxNO_BORDER);
		AddPage(Downloads, _T("Downloads"));
	#endif
}