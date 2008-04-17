#ifndef __BROWSER_EMBED_H
#define __BROWSER_EMBED_H
	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif
	
	
	#include <wxmozilla/wxMozilla.h>
/*
	#include <wx/filesys.h>
	#include <wx/fs_inet.h>
	#include <wx/fs_zip.h>
	#include <wx/fs_mem.h>
	#include <wxmozilla/wxMozillaProtocolHandler.h>
*/	
	class sAppBrowser : public wxPanel
	{
		public:
			sAppBrowser(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size);
			wxMozillaBrowser *browser;
	};

	/*
	class ddpsProtocolHandler : public wxProtocolHandler
	{
		public:
			ddpsProtocolHandler(const wxString scheme) : wxProtocolHandler(scheme){}
			~ddpsProtocolHandler(){}
			const wxString NewURI(const wxString spec, const wxString base);
			wxProtocolChannel* OpenChannel(const wxString uri);
			static wxProtocolHandler* Create(const wxString scheme){return new ddpsProtocolHandler(scheme);}

		
		protected:
			wxFileSystem mFileSystem;

	};
	*/
#endif
