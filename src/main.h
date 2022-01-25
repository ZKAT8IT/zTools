#ifndef _MAIN_H_
#define _MAIN_H_

#include <wx/wxprec.h>

#include "TPConnection.h"
#include "JSON/jsonval.h"

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


class zToolsApp: public wxAppConsole
{
    public:
        virtual bool OnInit();
        virtual int OnRun();

    private:
        wxDECLARE_EVENT_TABLE();

        enum Ids
        {
            TIMER_ID = 10000
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

        TPConnection* MyTPSocket;
        wxTimer* MyTimer;

        wxVector<wxJSONValue> TPData;

        int tLoopCount[12];
        int tMilliseconds;
        MarqueeSt sMarquee[10];

        void OnTimer(wxTimerEvent& event);

        void ProcessTPEvents();

        void DoComparison(wxString,wxString,wxString,wxString);
        void DoIfComparison(wxString,wxString,wxString,wxString,wxString);
        void DoIfElseComparison(wxString,wxString,wxString,wxString,wxString,wxString,wxString);
        void SubString(wxString,wxString,wxString,wxString);
        void Mid(wxString,wxString,wxString,wxString);
        void Left(wxString,wxString,wxString);
        void Right(wxString,wxString,wxString);
        void StartsWith(wxString,wxString,wxString);
        void EndsWith(wxString,wxString,wxString);
        void Length(wxString,wxString);
        void ScrollingMarquee(wxString,wxString,wxString);
        void ScreenCapture(wxString,wxString,wxString,wxString,wxString);

        void AdvancedSlider(wxString,wxString,wxString);
        void GetSliderValue(wxString,wxString);
};

#endif
