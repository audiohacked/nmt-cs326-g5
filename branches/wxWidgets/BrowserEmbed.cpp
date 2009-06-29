#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/filesys.h>
#include <wx/fs_inet.h>
#include <wx/fs_zip.h>
#include <wx/fs_mem.h>
#include <wx/url.h>

#include "AppEnum.h"
#include "AppMain.h"
#include "BrowserEmbed.h"

BEGIN_EVENT_TABLE( DDPSBrowser, wxPanel )
	EVT_BUTTON(BROWSER_Next, DDPSBrowser::OnNext)
	EVT_BUTTON(BROWSER_Prev, DDPSBrowser::OnPrev)
	EVT_BUTTON(BROWSER_Stop, DDPSBrowser::OnStop)
	EVT_BUTTON(BROWSER_Refresh, DDPSBrowser::OnRefresh)
	EVT_BUTTON(BROWSER_Home, DDPSBrowser::OnHome)
	
	EVT_COMMAND(wxID_ANY, wxEVT_MOZVIEW_TITLE_CHANGED, MyFrame::TitleChanged)
	EVT_COMMAND(wxID_ANY, wxEVT_MOZVIEW_LOCATION_CHANGED, MyFrame::LocationChanged)
	EVT_COMMAND(wxID_ANY, wxEVT_MOZVIEW_STATUS_CHANGED, MyFrame::StatusChanged)
END_EVENT_TABLE()

DDPSBrowser::DDPSBrowser(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size) 
: wxPanel(parent, id, pos, size)
{
	wParent = parent;
	browser = new wxMozView(this, -1, wxDefaultPosition, wxDefaultSize, wxBORDER);
	
	wxButton *back, *forward, *refresh, *stop, *home;
	
	back 	= new wxButton(this, BROWSER_Prev, 		wxT("Back"));
	forward = new wxButton(this, BROWSER_Next, 		wxT("Forward"));
	refresh = new wxButton(this, BROWSER_Refresh, 	wxT("Refresh"));
	stop 	= new wxButton(this, BROWSER_Stop, 		wxT("Stop"));
	home 	= new wxButton(this, BROWSER_Home, 		wxT("Home"));
	
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *browser_buttons_sizer = new wxBoxSizer(wxHORIZONTAL);

	browser_buttons_sizer->Add(back, 0, wxALL, 10);
	browser_buttons_sizer->Add(forward, 0, wxALL, 10);
	browser_buttons_sizer->Add(refresh, 0, wxALL, 10);
	browser_buttons_sizer->Add(stop, 0, wxALL, 10);
	browser_buttons_sizer->Add(home, 0, wxALL, 10);

	sizer->Add(browser_buttons_sizer, 0,  wxALIGN_TOP, 5);
	sizer->Add(browser, 1, wxEXPAND|wxALL, 5);
	SetSizer(sizer);
}

DDPSBrowser::~DDPSBrowser()
{
	delete browser;
}


void DDPSBrowser::LoadURI(wxString& uri)
{
    browser->LoadURI(uri);
}

void DDPSBrowser::TitleChanged(wxCommandEvent& event)
{
    this->SetTitle(event.GetString());
}

void DDPSBrowser::StatusChanged(wxCommandEvent& event)
{
    this->SetStatusText(event.GetString());
}

void DDPSBrowser::LocationChanged(wxCommandEvent& event)
{
    this->txtLocation_->SetValue(event.GetString());
}

void DDPSBrowser::BeforeLoad(wxCommandEvent &event)
{
	wxURL url(event.GetURL());
	if (url.GetScheme() == wxString("ddps", wxConvUTF8))
	{
		event.Cancel();
		wxLogDebug(wxString("DDPS Protocol Intercepted -- ", wxConvUTF8) + event.GetURL());
		if (url.GetServer() == wxString("browser", wxConvUTF8))
		{
			//wxLogDebug(wxT("http:/")+url.GetPath());
			browser->LoadURL( wxT("http:/")+url.GetPath() );
		} 
		else if (url.GetServer() == wxString("torrentDownload", wxConvUTF8))
		{
			wxString hash = url.GetPath().AfterFirst(wxChar('/')).BeforeFirst(wxChar('@'));
			wxString tracker = url.GetPath().AfterFirst(wxChar('@'));
			//wxLogDebug(wxT("DDPS Protocol Torrent Hash -- ") + hash);
			//wxLogDebug(wxT("DDPS Protocol Torrent Tracker -- ") + tracker);
			wxGetApp().frame->panel->tabs->Downloads->listDownloads->AddTorrentDownload( hash.mb_str(), tracker.mb_str(), hash.mb_str() );
			//wxGetApp().frame->panel->tabs->Downloads->listDownloads->AddTorrentFileDownload("original.torrent");
		}
		else if (url.GetServer() == wxString("httpDownload", wxConvUTF8))
		{
			wxString addr = wxString("http:/", wxConvUTF8)+url.GetPath();
			//wxGetApp().frame->panel->tabs->Downloads->listDownloads->httpDownloads->AddDownload( addr );
		}
	}
}

void DDPSBrowser::OnPrev(wxCommandEvent& event)
{
	wxLogDebug(wxT("OnPrev.."));
	if (browser->CanGoBack())
	{
		browser->GoBack();		
	}
}
void DDPSBrowser::OnNext(wxCommandEvent& event)
{
	wxLogDebug(wxT("OnNext.."));
	if ( browser->CanGoForward() )
	{
		browser->GoForward();
	}
}
void DDPSBrowser::OnStop(wxCommandEvent& event)
{
	wxLogDebug(wxT("OnStop.."));
#ifndef __WXMAC__
	if ( browser->IsBusy() )
	{
		browser->Stop();
	}
#else
	browser->Stop();
#endif
}
void DDPSBrowser::OnRefresh(wxCommandEvent& event)
{
	wxLogDebug(wxT("OnRefresh.."));
#ifndef __WXMAC__
	if ( !browser->IsBusy() )
	{
		browser->Reload();
	}
#else
	browser->Reload();
#endif
}

void DDPSBrowser::OnHome(wxCommandEvent& event)
{
	wxLogDebug(wxT("OnHome.."));
	browser->LoadURL(home);
}

void DDPSBrowser::GotoHomepage(void)
{
	wxLogDebug(wxT("GotoHomepage.."));
	browser->LoadURL(home);	
}