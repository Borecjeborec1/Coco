#include <windows.h>
#include <atlbase.h>
#include <atlwin.h>
#include <exdisp.h>
#include <mshtml.h>
#include <string>

class MyWindow : public CWindow
{
public:
    BEGIN_MSG_MAP(MyWindow)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_SIZE, OnSize)
    COMMAND_ID_HANDLER(ID_FILE_EXIT, OnFileExit)
    END_MSG_MAP()

    MyWindow() : webBrowser(nullptr) {}

private:
    CComPtr<IWebBrowser2> webBrowser;

    LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL & /*bHandled*/)
    {
        RECT rcClient;
        GetClientRect(&rcClient);

        // Create the WebBrowser control
        CComPtr<IWebBrowser2> pBrowser;
        HRESULT hr = CoCreateInstance(CLSID_WebBrowser, NULL, CLSCTX_INPROC_SERVER, IID_IWebBrowser2, (void **)&pBrowser);
        if (SUCCEEDED(hr))
        {
            webBrowser = pBrowser;

            // Navigate to the specified HTML content
            std::wstring htmlContent = L"<html><body><h1>Hello, World!</h1></body></html>";
            webBrowser->put_RegisterAsDropTarget(VARIANT_FALSE);
            webBrowser->put_Offline(VARIANT_FALSE);
            webBrowser->put_Silent(VARIANT_TRUE);
            webBrowser->put_Visible(VARIANT_TRUE);

            CComVariant varUrl(htmlContent.c_str());
            CComVariant varFlags(navNoHistory);
            CComVariant varTargetFrameName(L"_self");
            CComVariant varPostData;
            CComVariant varHeaders;
            webBrowser->Navigate2(&varUrl, &varFlags, &varTargetFrameName, &varPostData, &varHeaders);

            // Embed the WebBrowser control into the window
            CComPtr<IOleObject> pOleObject;
            hr = webBrowser->QueryInterface(IID_IOleObject, (void **)&pOleObject);
            if (SUCCEEDED(hr))
            {
                pOleObject->SetClientSite(this);
                pOleObject->DoVerb(OLEIVERB_INPLACEACTIVATE, NULL, this, 0, m_hWnd, &rcClient);
            }
        }

        return 0;
    }

    LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL & /*bHandled*/)
    {
        if (webBrowser)
        {
            RECT rcClient;
            GetClientRect(&rcClient);
            webBrowser->put_Width(rcClient.right - rcClient.left);
            webBrowser->put_Height(rcClient.bottom - rcClient.top);
        }

        return 0;
    }

    LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL & /*bHandled*/)
    {
        PostMessage(WM_CLOSE);
        return 0;
    }
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
    CComModule module;
    module.Init(NULL, hInstance);

    MyWindow mainWindow;
    if (mainWindow.Create(NULL, CRect(0, 0, 800, 600), _T("HTML Viewer"), WS_OVERLAPPEDWINDOW | WS_VISIBLE) == NULL)
    {
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    module.Term();
    return 0;
}
