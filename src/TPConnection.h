#ifndef _TPCONNECTION_H_
#define _TPCONNECTION_H_

#include <wx/wxprec.h>
#include <wx/app.h>
#include <wx/socket.h>
#include <wx/base64.h>
#include <wx/mstream.h>
//#include <wx/arrstr.h>
#include <wx/vector.h>
#include "JSON/jsonreader.h"
#include "JSON/jsonval.h"

#include <iostream>

using namespace std;


#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class TPConnection : public wxSocketClient
{
    private:
        struct TPInfoSt
        {
            wxString type;
            wxString sdkVersion;
            wxString tpVersionString;
            wxString tpVersionCode;
            wxString pluginVersion;
            wxString status;
        };
        TPInfoSt TPInfo;
        wxIPV4address TPAddr;
        wxString pID;
        wxString rData;
        wxArrayString stateArray;
        wxVector<wxJSONValue> MyJSONValues;
        wxJSONValue MyJSONVal;

        //wxMemoryOutputStream* memOutputStream;
        //wxMemoryBuffer* memBuffer;

    public:
        TPConnection() {};
        TPConnection(wxString);
        ~TPConnection() {};
        bool IsConnected() { return this->wxSocketClient::IsConnected(); };
        bool Error() { return this->wxSocketClient::Error(); };
        bool IsData();

        wxString ReadData() { return rData; };
        wxVector<wxJSONValue> GetJSONData() { return MyJSONValues; };

        void UpdateState(wxString, wxString);
        void UpdateState(wxString, wxImage*);
        void UpdateState(wxString, wxMemoryBuffer*);
        void UpdateStateArray(wxString, wxString);
        void SendStateArray();
        void UpdateList(wxString, wxArrayString);
        void UpdateList(wxString, wxString, wxArrayString);

        void AddState(wxString, wxString, wxString);
        void RemoveState(wxString);

        void UpdateConnector(wxString, wxString);

        wxString GetSDKVersion() { return TPInfo.sdkVersion; }
        wxString GetTPVersionString() { return TPInfo.tpVersionString; }
        long GetTPVersionCode() { long n; TPInfo.tpVersionCode.ToLong(&n); return n; }
        double GetTPPluginVersion() { double n; TPInfo.pluginVersion.ToDouble(&n); return n; }
        wxString GetTPPluginStatus() { return TPInfo.status; }

};

#endif
