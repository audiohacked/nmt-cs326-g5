/*
 * wxWindows Mozilla Browser Component
 * 
 * Developers:
 *  Jeremiah Cornelius McCarthy <jeremiah@whoop-ass.ca>
 *  Kevin Ollivier <kevino@tulane.edu>
 *  Dave Fancella <david.fancella@attbi.com>
 */

#include "wx/wxprec.h"
#include "helpers.h"

#include "nsIComponentManager.h"
#include "nsIComponentRegistrar.h"
#include "nsIInputStream.h"
#include "nsIAtom.h"
#include "nsIPref.h"
#include "nsISupports.h"
#include "nsIBaseWindow.h"
#include "nsIWebBrowser.h"
#include "nsIWebBrowserPersist.h"
#include "nsIWebBrowserChrome.h"
#include "nsIEmbeddingSiteWindow.h"
#include "nsEmbedAPI.h"
#include "nsIWindowCreator.h"
#include "nsIWindowWatcher.h"
#include "nsCWebBrowser.h"
#include "nsIWebProgressListener.h"
#include "nsIContextMenuListener2.h"
#include "nsIInterfaceRequestor.h"
#include "nsIWebBrowserSetup.h"
#include "nsIDocShellTreeItem.h"
#include "nsIWebBrowserChromeFocus.h"
#include "nsIInterfaceRequestor.h"
#include "nsIInterfaceRequestorUtils.h"
#include "nsStringAPI.h"
#include "nsIWeakReference.h"
#include "nsIWeakReferenceUtils.h"
#include "nsWeakReference.h"
#include "wx/event.h"
#include "nsISelection.h"
#include "nsIURI.h"
#include "nsIClipboardCommands.h"
#include "nsIWebBrowserFind.h"
#include "nsIDOMWindow.h"

#include "nsIDOMEventListener.h"
#include "nsPIDOMWindow.h"
#include "nsIChromeEventHandler.h"
#include "nsIDOMWindowInternal.h"
#include "nsIDocShell.h"
#include "nsIDocument.h"
#include "nsIDOMDocument.h"
#include "nsIDocumentEncoder.h"
#include "nsIStringStream.h"
#include "nsIAppShell.h"
#include "nsIEditorSpellCheck.h"
#include "nsIURIContentListener.h"

#include "nsICookieManager.h"
#include "nsICookieService.h"
#include "nsNetUtil.h"


#include "nsNetCID.h"
// ----------------------------------------------------------------------
// String conversion
// ----------------------------------------------------------------------

#if wxUSE_WCHAR_T

// converts string data between buffers of different char sizes:
template<typename S, typename D> class ConvertCharBuffer
{
public:
    ConvertCharBuffer(const S *src)
    {
        if (sizeof(S) != sizeof(D))
        {
            D *pt;
            const S *ps;
            size_t len = 0;
            for (ps = src; *ps; ps++) len++;        
            m_buffer = new D[len+1];
            for (pt = m_buffer, ps = src; *ps;) *(pt++) = *(ps++);
            *pt = 0;
        }
        else
        {
            m_buffer = (D*)src;
        }
    }

    operator D*() { return m_buffer; }
    operator const D*() const { return m_buffer; }
    
    ~ConvertCharBuffer()
    {
        if (sizeof(S) != sizeof(D))
        {
            delete[] m_buffer;
        }
    }
private:
    D *m_buffer;
};

#endif


nsString wxString_to_nsString(const wxString& s, wxMBConv& conv)
{
#if wxUSE_WCHAR_T
    const wxWX2WCbuf buf = s.wc_str(conv);
    if ((const wchar_t*)buf != NULL)
    {
        return nsString(ConvertCharBuffer<wchar_t,PRUnichar>(buf));
    }
    else
#endif
    {
#if wxUSE_UNICODE
        wxFAIL_MSG(wxT("this can never happen"));
#else
        // Fallback to Mozilla's (bad) conversion routine:
        nsString ns;
        ns.AssignWithConversion(s.c_str());
        return ns;
#endif
    }
}

wxString nsString_to_wxString(const nsString& s, wxMBConv& conv)
{
#if wxUSE_WCHAR_T
    wxWCharBuffer buf(ConvertCharBuffer<PRUnichar,wchar_t>(s.get()));
    const wxWC2WXbuf buf2 = conv.cWC2WX(buf);
    if ((const wxChar*)buf2 != NULL)
    {
        return wxString(buf2);
    }
    else
#endif
    {
#if wxUSE_UNICODE
        wxFAIL_MSG(wxT("this can never happen"));
#else
        // Fallback to Mozilla's (bad) conversion routine:
        nsCString cstring;
        cstring.AssignWithConversion(s.get());
        return wxString(cstring.get());
#endif
    }
}

wxString nsURI_to_wxString(nsIURI* from)
{
  if(from==nsnull)
    return wxString();  
  nsCAutoString converter;
  nsresult rv = from->GetSpec(converter);  
  wxASSERT_MSG(NS_SUCCEEDED(rv), wxT("Could not get string specification for uri"));
  return nsString_to_wxString(NS_ConvertUTF8toUCS2(converter), wxConvLocal);//@todo YORIC : is this the right converter ?
}

nsIURI* wxString_to_nsURI(const wxString from)
{
  nsCString utf8_buffer = NS_ConvertUCS2toUTF8(wxString_to_nsString(from, wxConvLocal));//@todo YORIC : is this the right converter ?
  
	nsresult rv;
	nsCOMPtr<nsIURI> url = do_CreateInstance( NS_SIMPLEURI_CONTRACTID, &rv );
  wxASSERT_MSG(NS_SUCCEEDED(rv), wxT("Could not create an instance of the url"));
  rv = url->SetSpec(nsCAutoString(utf8_buffer));
  wxASSERT_MSG(NS_SUCCEEDED(rv), wxT("Could not create set specs for the url"));
  return url;
}


nsID wxUId_to_nsID(const wxUId& aID)
{
	const nsID result = {aID.m0, aID.m1, aID.m2, {aID.m3[0], aID.m3[1], aID.m3[2], aID.m3[3], aID.m3[4], aID.m3[5], aID.m3[6], aID.m3[7]}};
	return result;
}
