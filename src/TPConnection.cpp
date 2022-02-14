#include "TPConnection.h"


TPConnection::TPConnection(wxString id)
{
    pID = id;

    //address to connect
    TPAddr.LocalHost();

    //TP plugin port = 12136;
    TPAddr.Service(12136);

    //Connect To Touch Portal
    this->wxSocketClient::Connect(TPAddr);
    if (this->wxSocketClient::IsConnected())
        cout << (wxT("Connected to ") + TPAddr.IPAddress()) << endl;
    else
        cout << (wxT("Can not connect to ") + TPAddr.IPAddress()) << endl;

    //Create Pairing JSON Request
    wxString request = wxT("{ \"type\":\"pair\", \"id\":\"") + pID + wxT("\" }\n");

    //Send the request to Touch Portal
    this->wxSocketClient::Write(request.mb_str(), request.Length());
    cout << "Request sent" << endl;

    //memOutputStream = new wxMemoryOutputStream();
    //memBuffer = new wxMemoryBuffer();
}

bool TPConnection::IsData()
{
    if(this->wxSocketClient::IsData())
    {
        if(MyJSONValues.size() > 0)
            MyJSONValues.clear();

        char c = 0x00;

        wxJSONReader* MyReader = new wxJSONReader();

        while( this->wxSocketClient::IsConnected() && !this->wxSocketClient::Error() && this->wxSocketClient::IsData())
        {
            this->wxSocketClient::Read(&c, 1);

            switch(c)
            {
                case '\n':
                    cout << "Data - " << rData.mb_str() << endl;
                    if(MyReader->Parse( rData, &MyJSONVal ) == 0)
                    {
                        if(MyJSONVal["type"].IsSameAs(wxT("info")))
                        {
                            TPInfo.type = MyJSONVal["type"].AsString();
                            TPInfo.tpVersionString = MyJSONVal["tpVersionString"].AsString();
                            TPInfo.pluginVersion = MyJSONVal["pluginVersion"].AsString();
                            TPInfo.tpVersionCode = MyJSONVal["tpVersionCode"].AsString();
                            TPInfo.sdkVersion = MyJSONVal["sdkVersion"].AsString();
                            TPInfo.status = MyJSONVal["status"].AsString();
                            cout << "Info Found" << endl;
                        }
                        else
                        {
                            MyJSONValues.push_back(MyJSONVal);
                            //MyJSONVal.Clear();
                        }
                    }
                    else
                    {
                        cout << "Error Parsing JSON Data" << endl;
                    }
                    rData.Clear();
                    break;
                default:
                    rData.Append((wxChar)c, 1);
                    break;
            }
        }
        //cout << "Data - " << rData.mb_str() << endl;

        delete(MyReader);
        return true;
    }
    //cout << "No Data" << endl;
    return false;
}

void TPConnection::UpdateState(wxString id, wxString value)
{
    wxString request = wxT("{\"type\":\"stateUpdate\",\"id\":\"") + id + wxT("\",\"value\":\"") + value + wxT("\"}\n");
    if(this->wxSocketClient::IsConnected())
        this->wxSocketClient::Write(request.mb_str(), request.Length());
}

void TPConnection::UpdateState(wxString id, wxImage* value)
{
    wxMemoryOutputStream* memOutputStream = new wxMemoryOutputStream();
    value->SaveFile(*memOutputStream,wxBITMAP_TYPE_PNG);

    wxMemoryBuffer* memBuffer = new wxMemoryBuffer();
    memBuffer->SetBufSize(memOutputStream->GetSize());
    memBuffer->SetDataLen(memOutputStream->GetSize());
    memOutputStream->CopyTo(memBuffer->GetData(), memBuffer->GetDataLen());

    wxString value2 = wxBase64Encode(*memBuffer);
    wxString request = wxT("{\"type\":\"stateUpdate\",\"id\":\"") + id + wxT("\",\"value\":\"") + value2 + wxT("\"}\n");
    if(this->wxSocketClient::IsConnected())
        this->wxSocketClient::Write(request.mb_str(), request.Length());

    delete(memOutputStream);
    delete(memBuffer);
}

void TPConnection::UpdateState(wxString id, wxMemoryBuffer* value)
{
    wxString value2 = wxBase64Encode(*value);
    wxString request = wxT("{\"type\":\"stateUpdate\",\"id\":\"") + id + wxT("\",\"value\":\"") + value2 + wxT("\"}\n");
    if(this->wxSocketClient::IsConnected())
        this->wxSocketClient::Write(request.mb_str(), request.Length());
}

void TPConnection::UpdateStateArray(wxString id, wxString value)
{
    stateArray.Add(wxT("{\"type\":\"stateUpdate\",\"id\":\"") + id + wxT("\",\"value\":\"") + value + wxT("\"}\n"));
}

void TPConnection::SendStateArray()
{
    if((int)stateArray.Count() > 0)
        for(int i = 0; i < (int)stateArray.Count(); i++)
            if(this->wxSocketClient::IsConnected())
                this->wxSocketClient::Write(stateArray[i].mb_str(), stateArray[i].Length());

    stateArray.Clear();
}

void TPConnection::UpdateList(wxString id, wxArrayString valueList)
{
    wxString request = wxT("{\"type\":\"choiceUpdate\",\"id\":\"") + id + wxT("\",\"value\":[");
    for(int i = 0; i < (int)valueList.GetCount(); i++)
    {
        if(i == ((int)valueList.GetCount() - 1))
            request.Append(wxT("\"") + valueList[i] + wxT("\""));
        else
            request.Append(wxT("\"") + valueList[i] + wxT("\","));
    }
    request.Append(wxT("]}\n"));
    //cout << "List 2 = " << request.mb_str() << endl;
    if(this->wxSocketClient::IsConnected())
        this->wxSocketClient::Write(request.mb_str(), request.Length());
}

void TPConnection::UpdateList(wxString id, wxString instanceId, wxArrayString valueList)
{
    wxString request = wxT("{\"type\":\"choiceUpdate\",\"id\":\"") + id + wxT("\",\"instanceId\":\"") + instanceId + wxT("\",\"value\":[");
    for(int i = 0; i < (int)valueList.GetCount(); i++)
    {
        if(i == ((int)valueList.GetCount() - 1))
            request.Append(wxT("\"") + valueList[i] + wxT("\""));
        else
            request.Append(wxT("\"") + valueList[i] + wxT("\","));
    }
    request.Append(wxT("]}\n"));
    if(this->wxSocketClient::IsConnected())
        this->wxSocketClient::Write(request.mb_str(), request.Length());
}

void TPConnection::UpdateConnector(wxString id, wxString value)
{
    wxString request = wxT("{\"type\":\"connectorUpdate\",\"connectorId\":\"") + id + wxT("\",\"value\":") + value + wxT("}\n");
    cout << "Update Request " << request.mb_str() << endl;
    if(this->wxSocketClient::IsConnected())
        this->wxSocketClient::Write(request.mb_str(), request.Length());
}

void TPConnection::AddState(wxString id, wxString desc, wxString dValue)
{
    wxString request = wxT("{\"type\":\"createState\",\"id\":\"") + id + wxT("\",\"desc\":\"") + desc + wxT("\",\"defaultValue\":\"") + dValue + wxT("\"}");
    if(this->wxSocketClient::IsConnected())
        this->wxSocketClient::Write(request.mb_str(), request.Length());
}

void TPConnection::RemoveState(wxString id)
{
    wxString request = wxT("{\"type\":\"removeState\",\"id\":\"") + id + wxT("\"}");
    if(this->wxSocketClient::IsConnected())
        this->wxSocketClient::Write(request.mb_str(), request.Length());
}
