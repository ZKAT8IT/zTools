#ifndef _MAIN_H_
#define _MAIN_H_

#include <wx/wxprec.h>

#include "TPConnection.h"
#include "JSON/jsonval.h"
#include <wx/clipbrd.h>
#include <windows.h>
#include <psapi.h>
#include <wx/msw/dib.h>
#include <wx/webview.h>
#include <audiopolicy.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <wx/dcclient.h>
//#include <wx/msw/dc.h>
#include <wx/webview.h>
//#include <string.h>
//#include <locale.h>

#define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = 0; } }

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


class zToolsApp: public wxAppConsole
{
    public:
        virtual bool OnInit();
        virtual int OnRun();

        static BOOL enumWindowCallback(HWND, LPARAM);

    private:
        wxDECLARE_EVENT_TABLE();

        enum Ids
        {
            TIMER_ID = 10000,
            MAINTIMER_ID = 10001
        };
        struct MarqueeSt
        {
            wxString Message;
            long DisplayLength;
        };
        struct Apps
        {
            wxString TitleName;
            wxString ExePath;
            wxString ExeName;
            HWND WindowHandle;
            HINSTANCE hInstance;
            DWORD ProcessID;
            HANDLE ProcessHandle;
            DWORD ThreadID;
            bool Updated;
        };

        Apps MyApps[1000];

        struct MixerAppSt
        {
            DWORD procID;
            string szProcessName;
        };

        MixerAppSt MixerApps[20];
        int MixerAppCount;
        IMMDeviceCollection *pCollection = NULL;

        TPConnection* MyTPSocket;
        wxTimer* MyTimer;
        wxTimer* MainTimer;
        wxArrayString exeAry;
        wxVector<wxJSONValue> TPData;

        wxImage* ClearIcon;

        wxString ShortID;

        int tLoopCount[12];
        int tMilliseconds;
        MarqueeSt sMarquee[10];

        wxBitmap* screenshot;
        wxImage* buttonImage;
        wxScreenDC* myScreenDC;
        wxClientDC* myWindowDC;
        wxMemoryDC* memScreenDC;
        wxMemoryDC* memWindowDC;
        wxWindow* parentWindow;
        wxString oldTitle;
        HWND oldHWND;
        RECT rc;
        long lx,ly, lbp;
        bool CaptureSetup;

        void OnTimer(wxTimerEvent& event);
        void OnMainTimer(wxTimerEvent& event);

        void ProcessTPEvents();

        void DoComparison(wxString,wxString,wxString,wxString);
        void DoIfComparison(wxString,wxString,wxString,wxString,wxString);
        void DoIfElseComparison(wxString,wxString,wxString,wxString,wxString,wxString,wxString);
        void DoIfAndOrComparison(wxString,wxString,wxString,wxString,wxString,wxString,wxString,wxString,wxString);
        void DoIfAndOrElseComparison(wxString,wxString,wxString,wxString,wxString,wxString,wxString,wxString,wxString,wxString,wxString);
        void SubString(wxString,wxString,wxString,wxString);
        void Mid(wxString,wxString,wxString,wxString);
        void Left(wxString,wxString,wxString);
        void Right(wxString,wxString,wxString);
        void StartsWith(wxString,wxString,wxString);
        void EndsWith(wxString,wxString,wxString);
        void Length(wxString,wxString);
        void ScrollingMarquee(wxString,wxString,wxString);
        //void ScreenCapture(wxString,wxString,wxString,wxString,wxString);
        //void WindowCapture(wxString,wxString,wxString,wxString,wxString,wxString);
        void ScreenWindowCapture(wxString,wxString,wxString,wxString,wxString,wxString);
        void SetupCapture();

        void GetApplicationInfo();

        void ChangeAppVolume(wxString, float);
        void ChangeMainVolume(float);

        void GetSliderValue(wxString,wxString);
        void LinkSliders(wxString,wxString,wxString);
};

#endif
