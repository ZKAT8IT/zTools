#include "main.h"
#include "TPConnection.h"

using namespace std;

wxIMPLEMENT_APP_CONSOLE(zToolsApp);

wxBEGIN_EVENT_TABLE(zToolsApp, wxAppConsole)
    EVT_TIMER(TIMER_ID, zToolsApp::OnTimer)
    EVT_TIMER(MAINTIMER_ID, zToolsApp::OnMainTimer)
wxEND_EVENT_TABLE()

bool zToolsApp::OnInit()
{
    wxImage::AddHandler( new wxPNGHandler );

    for(int i = 0; i < 12; i++)
        tLoopCount[i] = 0;


    return true;
}

int zToolsApp::OnRun()
{
    MyTimer = new wxTimer(this, TIMER_ID);
    MainTimer = new wxTimer(this, MAINTIMER_ID);
    MyTPSocket = new TPConnection(wxT("zk_tools"));
    //GetApplicationInfo();

    CaptureSetup = false;


    ClearIcon = new wxImage(128,128);
    if(!ClearIcon->HasAlpha())
        ClearIcon->InitAlpha();

    for(int py=0; py < 128; py++)
        for(int px=0; px < 128; px++)
            ClearIcon->SetAlpha(px,py,0);

    exeAry.Add(wxT("Screen Capture"));
    EnumWindows(zToolsApp::enumWindowCallback, reinterpret_cast<LPARAM>(&exeAry));
    MyTPSocket->UpdateList(wxT("zt_window_01"),exeAry);
    MyTPSocket->UpdateState(wxT("ClearIcon"),ClearIcon);

    //cout << " here 2 " << endl;
    //cout << ":size: " << exeAry[5] << endl;

    MainTimer->Start(1);
    MyTimer->Start(25);
    //MyTimer->Start(1);
    //ProcessTPEvents();




	return wxAppConsole::OnRun();
}

void zToolsApp::ProcessTPEvents()
{
    if(MyTPSocket->IsConnected())
    {
        if(MyTPSocket->IsData())
        {
//cout << "here 1" << endl;
                TPData = MyTPSocket->GetJSONData();
//cout << "here 2" << endl;
                //if(TPData.size() > 0)
                //{
                    //for(wxVector<wxJSONValue>::size_type i = 0; i < TPData.size(); i++)
                    //for(wxVector<wxJSONValue>::iterator it = TPData.begin(); it != TPData.end(); ++it)
                    wxVector<wxJSONValue>::iterator it = TPData.begin();
                    while(it != TPData.end())
                    {
                        //cout << "Size - " << TPData.size() << endl;
                        wxJSONValue TempVal = TPData.front();
                        //cout << "TPDataType - " << TempVal["type"].AsString().mb_str() << endl;
                        cout << "Data - " << TempVal.AsString().mb_str() << endl;
                        if(TempVal["type"].IsSameAs(wxT("action")))
                        {
                            cout << "here 4" << endl;
                            //wxArrayString aValues;
                            //if(MyTPSocket->GetTPeDataCount(i) > 0)
                            //{
                            //    for(int c = 0; c < MyTPSocket->GetTPeDataCount(i); c++)
                            //    {
                            //        aValues.Add(MyTPSocket->GetTPeDataValue(i,c));
                                    //cout << "Value " << c << " - " << MyTPSocket->GetTPeDataValue(i,c).mb_str() << endl;
                            //    }
                            //}
                            cout << "TPData - " << TempVal["data"][0]["value"].AsString().mb_str() << endl;
                            if(TempVal["actionId"].IsSameAs(wxT("ztools_operator")))
                                DoComparison(TempVal["data"][0]["value"].AsString(),TempVal["data"][1]["value"].AsString(),TempVal["data"][2]["value"].AsString(),TempVal["data"][3]["value"].AsString());

                            if(TempVal["actionId"].IsSameAs(wxT("ztools_if")))
                                DoIfComparison(TempVal["data"][0]["value"].AsString(),TempVal["data"][1]["value"].AsString(),TempVal["data"][2]["value"].AsString(),TempVal["data"][3]["value"].AsString(),TempVal["data"][4]["value"].AsString());

                            if(TempVal["actionId"].IsSameAs(wxT("ztools_ifelse")))
                                DoIfElseComparison(TempVal["data"][0]["value"].AsString(),TempVal["data"][1]["value"].AsString(),TempVal["data"][2]["value"].AsString(),TempVal["data"][3]["value"].AsString(),TempVal["data"][4]["value"].AsString(),TempVal["data"][5]["value"].AsString(),TempVal["data"][6].AsString());

                            if(TempVal["actionId"].IsSameAs(wxT("ztools_ifandor")))
                                DoIfAndOrComparison(TempVal["data"][0]["value"].AsString(),TempVal["data"][1]["value"].AsString(),TempVal["data"][2]["value"].AsString(),TempVal["data"][3]["value"].AsString(),TempVal["data"][4]["value"].AsString(),TempVal["data"][5]["value"].AsString(),TempVal["data"][6]["value"].AsString(),TempVal["data"][7]["value"].AsString(),TempVal["data"][8]["value"].AsString());

                            if(TempVal["actionId"].IsSameAs(wxT("ztools_ifandorelse")))
                                DoIfAndOrElseComparison(TempVal["data"][0]["value"].AsString(),TempVal["data"][1]["value"].AsString(),TempVal["data"][2]["value"].AsString(),TempVal["data"][3]["value"].AsString(),TempVal["data"][4]["value"].AsString(),TempVal["data"][5]["value"].AsString(),TempVal["data"][6]["value"].AsString(),TempVal["data"][7]["value"].AsString(),TempVal["data"][8]["value"].AsString(),TempVal["data"][9]["value"].AsString(),TempVal["data"][10]["value"].AsString());

                            if(TempVal["actionId"].IsSameAs(wxT("ztools_substring")))
                                SubString(TempVal["data"][0]["value"].AsString(),TempVal["data"][1]["value"].AsString(),TempVal["data"][2]["value"].AsString(),TempVal["data"][3]["value"].AsString());

                            if(TempVal["actionId"].IsSameAs(wxT("ztools_mid")))
                                Mid(TempVal["data"][0]["value"].AsString(),TempVal["data"][1]["value"].AsString(),TempVal["data"][2]["value"].AsString(),TempVal["data"][3]["value"].AsString());

                            if(TempVal["actionId"].IsSameAs(wxT("ztools_left")))
                                Left(TempVal["data"][0]["value"].AsString(),TempVal["data"][1]["value"].AsString(),TempVal["data"][2]["value"].AsString());

                            if(TempVal["actionId"].IsSameAs(wxT("ztools_right")))
                                Right(TempVal["data"][0]["value"].AsString(),TempVal["data"][1]["value"].AsString(),TempVal["data"][2]["value"].AsString());

                            if(TempVal["actionId"].IsSameAs(wxT("ztools_startswith")))
                                StartsWith(TempVal["data"][0]["value"].AsString(),TempVal["data"][1]["value"].AsString(),TempVal["data"][2]["value"].AsString());

                            if(TempVal["actionId"].IsSameAs(wxT("ztools_endswith")))
                                EndsWith(TempVal["data"][0]["value"].AsString(),TempVal["data"][1]["value"].AsString(),TempVal["data"][2]["value"].AsString());

                            if(TempVal["actionId"].IsSameAs(wxT("ztools_length")))
                                Length(TempVal["data"][0]["value"].AsString(),TempVal["data"][1]["value"].AsString());

                            if(TempVal["actionId"].IsSameAs(wxT("ztools_timer"))) { }

                            if(TempVal["actionId"].IsSameAs(wxT("ztools_smarquee")))
                                ScrollingMarquee(TempVal["data"][0]["value"].AsString(),TempVal["data"][1]["value"].AsString(),TempVal["data"][2]["value"].AsString());

                            //if(TempVal["actionId"].IsSameAs(wxT("ztools_screencapture")))
                            //    ScreenCapture(TempVal["data"][0]["value"].AsString(),TempVal["data"][1]["value"].AsString(),TempVal["data"][2]["value"].AsString(),TempVal["data"][3]["value"].AsString(),TempVal["data"][4]["value"].AsString());
                            //if(TempVal["actionId"].IsSameAs(wxT("ztools_windowcapture")))
                            //    WindowCapture(TempVal["data"][0]["value"].AsString(),TempVal["data"][1]["value"].AsString(),TempVal["data"][2]["value"].AsString(),TempVal["data"][3]["value"].AsString(),TempVal["data"][4]["value"].AsString(),TempVal["data"][5]["value"].AsString());
                            if(TempVal["actionId"].IsSameAs(wxT("ztools_screenwindowcapture")))
                                ScreenWindowCapture(TempVal["data"][0]["value"].AsString(),TempVal["data"][1]["value"].AsString(),TempVal["data"][2]["value"].AsString(),TempVal["data"][3]["value"].AsString(),TempVal["data"][4]["value"].AsString(),TempVal["data"][5]["value"].AsString());



                            //if(TempVal["connectorId"].IsSameAs(wxT("ztools_advancedslider")))
                            //    cout << TempVal["data"][0]["value"].AsString().mb_str() << endl;
                                //GetSliderValue(TempVal["data"][0]["value"].AsString(),TempVal["data"][1]["value"].AsString());

                                //AdvancedSlider();


                            //aValues.Clear();
                        }
                        if(TempVal["type"].IsSameAs(wxT("shortConnectorIdNotification")))
                        {
                            cout << "Short ID Generated" << endl;
                            ShortID = TempVal["shortID"].AsString();
                        }
                        if(TempVal["type"].IsSameAs(wxT("connectorChange")))
                        {
                            if(TempVal["connectorId"].IsSameAs(wxT("ztools_getslidervalue")))
                            {
                                //cout << "SValue 1 - " << TempVal["data"][0]["value"].AsString().mb_str() << endl;
                                GetSliderValue(TempVal["data"][0]["value"].AsString(),TempVal["value"].AsString());
                            }
                            if(TempVal["connectorId"].IsSameAs(wxT("ztools_linksliders")))
                            {
                                cout << "SValue 1 - " << TempVal["data"][0]["value"].AsString().mb_str() << endl;
                                LinkSliders(TempVal["data"][0]["value"].AsString(),TempVal["data"][1]["value"].AsString(),TempVal["value"].AsString());
                            }
                        }
                        if(TempVal["type"].IsSameAs(wxT("down")))
                        {
                        }
                        if(TempVal["type"].IsSameAs(wxT("up")))
                        {
                        }
                        it = TPData.erase(it);
                        //TPData.pop_back();
                        //if(MyTPSocket->GetTPeType(i).IsSameAs(wxT("listChange")))
                        //{
                        //    cout << "listChange" << endl;
                        //}
                        //if(MyTPSocket->GetTPeType(i).IsSameAs(wxT("broadcast")))
                        //{
                        //    cout << "broadcast" << endl;
                        //}
                    }
                    cout << "Ended Loop" << endl;
                //}
            //TPData.clear();

        }
    }
    else
    {
        delete(MyTPSocket);
        this->wxAppConsole::OnExit();
    }
    //MyTPSocket->UpdateState(wxT("zk_fruit"),wxT("Pears"));
    //Timer();
}

void zToolsApp::GetSliderValue(wxString id, wxString val)
{
    MyTPSocket->UpdateState(id,val);
}

void zToolsApp::LinkSliders(wxString sub, wxString t, wxString val)
{
    if(t.IsSameAs(wxT("MainOverride")))
    {
        cout << "Connect Override - " << ShortID.mb_str() << endl;
        //MyTPSocket->UpdateConnector(sub,val);
        MyTPSocket->UpdateConnector(wxT("pc_zk_tools_ztools_linksliders|sliderid=") + sub + wxT("|sliderlinktype=") + t,val);
    }
}

void zToolsApp::OnMainTimer(wxTimerEvent& event)
{
    ProcessTPEvents();
}

void zToolsApp::OnTimer(wxTimerEvent& event)
{
    //ProcessTPEvents();


    for(int i = 0; i < 12; i++)
        tLoopCount[i]++;

    if(tLoopCount[2] == 4)
    //if(tLoopCount[2] == 100)
    {
        for(int i2 = 0; i2 < 10; i2++)
        {
            if(!sMarquee[i2].Message.IsEmpty())
            {
                if(sMarquee[i2].Message.Length() >= 3)
                {
                    //Get First Character
                    wxString f = sMarquee[i2].Message.Left(1);
                    //Get Rest Of String
                    wxString rest = sMarquee[i2].Message.Right(sMarquee[i2].Message.Length()-1);
                    //Update Marquee
                    sMarquee[i2].Message.Empty();
                    sMarquee[i2].Message = rest + f;
                    MyTPSocket->UpdateStateArray(wxT("sMarquee")+wxString::Format(wxT("%i"),i2),sMarquee[i2].Message.Left(sMarquee[i2].DisplayLength));
                    f.Clear();
                    rest.Clear();
                }
            }
        }
    }


    if(tLoopCount[0] == 1)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("25")); tLoopCount[0] = 0; }
    if(tLoopCount[1] == 2)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("50")); tLoopCount[1] = 0; }
    if(tLoopCount[2] == 4)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("100")); tLoopCount[2] = 0; }
    if(tLoopCount[3] == 8)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("200")); tLoopCount[3] = 0; }
    if(tLoopCount[4] == 12)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("300")); tLoopCount[4] = 0; }
    if(tLoopCount[5] == 16)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("400")); tLoopCount[5] = 0; }
    if(tLoopCount[6] == 20)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("500")); tLoopCount[6] = 0; }
    if(tLoopCount[7] == 24)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("600")); tLoopCount[7] = 0; }
    if(tLoopCount[8] == 28)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("700")); tLoopCount[8] = 0; }
    if(tLoopCount[9] == 32)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("800")); tLoopCount[9] = 0; }
    if(tLoopCount[10] == 36)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("900")); tLoopCount[10] = 0; }
    if(tLoopCount[11] == 40)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("1000")); tLoopCount[11] = 0; }


    /*
    bool SendArray = false;

    if(tLoopCount[0] == 25)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("25")); tLoopCount[0] = 0; SendArray = true; }
    if(tLoopCount[1] == 50)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("50")); tLoopCount[1] = 0; SendArray = true; }
    if(tLoopCount[2] == 100)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("100")); tLoopCount[2] = 0; SendArray = true; }
    if(tLoopCount[3] == 200)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("200")); tLoopCount[3] = 0; SendArray = true; }
    if(tLoopCount[4] == 300)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("300")); tLoopCount[4] = 0; SendArray = true; }
    if(tLoopCount[5] == 400)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("400")); tLoopCount[5] = 0; SendArray = true; }
    if(tLoopCount[6] == 500)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("500")); tLoopCount[6] = 0; SendArray = true; }
    if(tLoopCount[7] == 600)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("600")); tLoopCount[7] = 0; SendArray = true; }
    if(tLoopCount[8] == 700)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("700")); tLoopCount[8] = 0; SendArray = true; }
    if(tLoopCount[9] == 800)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("800")); tLoopCount[9] = 0; SendArray = true; }
    if(tLoopCount[10] == 900)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("900")); tLoopCount[10] = 0; SendArray = true; }
    if(tLoopCount[11] == 1000)
        { MyTPSocket->UpdateStateArray(wxT("tTimer0"),wxT("1000")); tLoopCount[11] = 0; SendArray = true; }

    // do whatever you want to do every second here
    if(SendArray)
        MyTPSocket->SendStateArray();
    */
    MyTPSocket->SendStateArray();
}

void zToolsApp::DoComparison(wxString result, wxString value1, wxString oper, wxString value2)
{
    long num1, num2;
    bool Is1String = false;
    bool Is2String = false;
    //If Value 1 Is Number Only
    if(value1.IsNumber())
    {
        value1.ToLong(&num1);
    }
    else
    {
        Is1String = true;
        num1 = value1.Length();
    }

    //If Value 2 Is Number Only
    if(value2.IsNumber())
    {
        value2.ToLong(&num2);
    }
    else
    {
        Is2String = true;
        num2 = value2.Length();
    }


    wxString strResult;
    if(oper.IsSameAs(wxT("==")))
    {
        if(Is1String == true && Is2String == true)
            strResult = wxString::Format(wxT("%i"),value1.IsSameAs(value2));
        else
            strResult = wxString::Format(wxT("%i"),(num1 == num2));
    }
    if(oper.IsSameAs(wxT("!=")))
    {
        if(Is1String == true && Is2String == true)
            strResult = wxString::Format(wxT("%i"),!value1.IsSameAs(value2));
        else
            strResult = wxString::Format(wxT("%i"),(num1 != num2));
    }
    //if(oper.IsSameAs(wxT("!=")))
    //    strResult = wxString::Format(wxT("%i"),(num1 != num2));
    if(oper.IsSameAs(wxT(">=")))
        strResult = wxString::Format(wxT("%i"),(num1 >= num2));
    if(oper.IsSameAs(wxT("<=")))
        strResult = wxString::Format(wxT("%i"),(num1 <= num2));
    if(oper.IsSameAs(wxT(">")))
        strResult = wxString::Format(wxT("%i"),(num1 > num2));
    if(oper.IsSameAs(wxT("<")))
        strResult = wxString::Format(wxT("%i"),(num1 < num2));
    if(oper.IsSameAs(wxT("*")))
        strResult = wxString::Format(wxT("%i"),(num1 * num2));
    if(oper.IsSameAs(wxT("/")))
        strResult = wxString::Format(wxT("%i"),(num1 / num2));
    if(oper.IsSameAs(wxT("+")))
        strResult = wxString::Format(wxT("%i"),(num1 + num2));
    if(oper.IsSameAs(wxT("-")))
        strResult = wxString::Format(wxT("%i"),(num1 - num2));

    MyTPSocket->UpdateState(result,strResult);

}
void zToolsApp::DoIfComparison(wxString value1, wxString oper, wxString value2, wxString result, wxString store)
{
    long num1, num2;
    bool Is1String = false;
    bool Is2String = false;
    //If Value 1 Is Number Only
    if(value1.IsNumber())
    {
        value1.ToLong(&num1);
    }
    else
    {
        Is1String = true;
        num1 = value1.Length();
    }

    //If Value 2 Is Number Only
    if(value2.IsNumber())
    {
        value2.ToLong(&num2);
    }
    else
    {
        Is2String = true;
        num2 = value2.Length();
    }

    //wxString strResult;
    if(oper.IsSameAs(wxT("==")))
    {
        if(Is1String == true && Is2String == true)
        {
            if(value1.IsSameAs(value2))
                MyTPSocket->UpdateState(result,store);
        }
        else
        {
            if(num1 == num2)
                MyTPSocket->UpdateState(result,store);
        }
    }
    if(oper.IsSameAs(wxT("!=")))
    {
        if(Is1String == true && Is2String == true)
        {
            if(!value1.IsSameAs(value2))
                MyTPSocket->UpdateState(result,store);
        }
        else
        {
            if(num1 != num2)
                MyTPSocket->UpdateState(result,store);
        }
    }
    if(oper.IsSameAs(wxT(">=")))
        if(num1 >= num2)
            MyTPSocket->UpdateState(result,store);
    if(oper.IsSameAs(wxT("<=")))
        if(num1 <= num2)
            MyTPSocket->UpdateState(result,store);
    if(oper.IsSameAs(wxT(">")))
        if(num1 > num2)
            MyTPSocket->UpdateState(result,store);
    if(oper.IsSameAs(wxT("<")))
        if(num1 < num2)
            MyTPSocket->UpdateState(result,store);

}
void zToolsApp::DoIfElseComparison(wxString value1, wxString oper, wxString value2, wxString result1, wxString store1, wxString result2, wxString store2)
{
    long num1, num2;
    bool Is1String = false;
    bool Is2String = false;
    //If Value 1 Is Number Only
    if(value1.IsNumber())
    {
        value1.ToLong(&num1);
    }
    else
    {
        Is1String = true;
        num1 = value1.Length();
    }

    //If Value 2 Is Number Only
    if(value2.IsNumber())
    {
        value2.ToLong(&num2);
    }
    else
    {
        Is2String = true;
        num2 = value2.Length();
    }

    //wxString strResult;
    if(oper.IsSameAs(wxT("==")))
    {
        if(Is1String == true && Is2String == true)
        {
            if(value1.IsSameAs(value2))
                MyTPSocket->UpdateState(result1,store1);
            else
                MyTPSocket->UpdateState(result2,store2);
        }
        else
        {
            if(num1 == num2)
                MyTPSocket->UpdateState(result1,store1);
            else
                MyTPSocket->UpdateState(result2,store2);
        }
    }
    if(oper.IsSameAs(wxT("!=")))
    {
        if(Is1String == true && Is2String == true)
        {
            if(!value1.IsSameAs(value2))
                MyTPSocket->UpdateState(result1,store1);
            else
                MyTPSocket->UpdateState(result2,store2);
        }
        else
        {
            if(num1 != num2)
                MyTPSocket->UpdateState(result1,store1);
            else
                MyTPSocket->UpdateState(result2,store2);
        }
    }
    if(oper.IsSameAs(wxT(">=")))
    {
        if(num1 >= num2)
            MyTPSocket->UpdateState(result1,store1);
        else
            MyTPSocket->UpdateState(result2,store2);
    }
    if(oper.IsSameAs(wxT("<=")))
    {
        if(num1 <= num2)
            MyTPSocket->UpdateState(result1,store1);
        else
            MyTPSocket->UpdateState(result2,store2);
    }
    if(oper.IsSameAs(wxT(">")))
    {
        if(num1 > num2)
            MyTPSocket->UpdateState(result1,store1);
        else
            MyTPSocket->UpdateState(result2,store2);
    }
    if(oper.IsSameAs(wxT("<")))
    {
        if(num1 < num2)
            MyTPSocket->UpdateState(result1,store1);
        else
            MyTPSocket->UpdateState(result2,store2);
    }
}

void zToolsApp::DoIfAndOrComparison(wxString value1, wxString oper, wxString value2, wxString ao, wxString value3, wxString oper2, wxString value4, wxString result1, wxString store1)
{
    long num1, num2, num3, num4;
    bool Is1String, Is2String, Is3String, Is4String;
    Is1String = false; Is2String = false; Is3String = false; Is4String = false;

    //Convert Strings To Numbers
    if(value1.IsNumber()) {
        value1.ToLong(&num1); }
    else {
        Is1String = true; value1.Length(); }
    if(value2.IsNumber()) {
        value2.ToLong(&num2); }
    else {
        Is2String = true; value2.Length(); }
    if(value3.IsNumber()) {
        value3.ToLong(&num3); }
    else {
        Is3String = true; value3.Length(); }
    if(value4.IsNumber()) {
        value4.ToLong(&num4); }
    else {
        Is4String = true; value4.Length(); }

    bool Operation1 = false;
    bool Operation2 = false;

    if(oper.IsSameAs(wxT("==")))
    {
        if(Is1String == true && Is2String == true)
        {
            if(value1.IsSameAs(value2))
                Operation1 = true;
        }
        else
        {
            if(num1 == num2)
                Operation1 = true;
        }
    }
    if(oper.IsSameAs(wxT("!=")))
    {
        if(Is1String == true && Is2String == true)
        {
            if(!value1.IsSameAs(value2))
                Operation1 = true;
        }
        else
        {
            if(num1 != num2)
                Operation1 = true;
        }
    }
    if(oper.IsSameAs(wxT(">=")))
    {
        if(num1 >= num2)
            Operation1 = true;
    }
    if(oper.IsSameAs(wxT("<=")))
    {
        if(num1 <= num2)
            Operation1 = true;
    }
    if(oper.IsSameAs(wxT(">")))
    {
        if(num1 > num2)
            Operation1 = true;
    }
    if(oper.IsSameAs(wxT("<")))
    {
        if(num1 < num2)
            Operation1 = true;
    }

    if(oper2.IsSameAs(wxT("==")))
    {
        if(Is3String == true && Is4String == true)
        {
            if(value3.IsSameAs(value4))
                Operation2 = true;
        }
        else
        {
            if(num3 == num4)
                Operation2 = true;
        }
    }
    if(oper2.IsSameAs(wxT("!=")))
    {
        if(Is3String == true && Is4String == true)
        {
            if(!value3.IsSameAs(value4))
                Operation2 = true;
        }
        else
        {
            if(num3 != num4)
                Operation2 = true;
        }
    }
    if(oper2.IsSameAs(wxT(">=")))
    {
        if(num3 >= num4)
            Operation2 = true;
    }
    if(oper2.IsSameAs(wxT("<=")))
    {
        if(num3 <= num4)
            Operation2 = true;
    }
    if(oper2.IsSameAs(wxT(">")))
    {
        if(num3 > num4)
            Operation2 = true;
    }
    if(oper2.IsSameAs(wxT("<")))
    {
        if(num3 < num4)
            Operation2 = true;
    }

    if(ao.IsSameAs(wxT("And")))
    {
        if(Operation1 == true && Operation2 == true)
        {
            MyTPSocket->UpdateState(result1,store1);
        }
    }
    if(ao.IsSameAs(wxT("Or")))
    {
        if(Operation1 == true || Operation2 == true)
        {
            MyTPSocket->UpdateState(result1,store1);
        }
    }
}

void zToolsApp::DoIfAndOrElseComparison(wxString value1, wxString oper, wxString value2, wxString ao, wxString value3, wxString oper2, wxString value4, wxString result1, wxString store1, wxString result2, wxString store2)
{
    long num1, num2, num3, num4;
    bool Is1String, Is2String, Is3String, Is4String;
    Is1String = false; Is2String = false; Is3String = false; Is4String = false;

    //Convert Strings To Numbers
    if(value1.IsNumber()) {
        value1.ToLong(&num1); }
    else {
        Is1String = true; value1.Length(); }
    if(value2.IsNumber()) {
        value2.ToLong(&num2); }
    else {
        Is2String = true; value2.Length(); }
    if(value3.IsNumber()) {
        value3.ToLong(&num3); }
    else {
        Is3String = true; value3.Length(); }
    if(value4.IsNumber()) {
        value4.ToLong(&num4); }
    else {
        Is4String = true; value4.Length(); }

    bool Operation1 = false;
    bool Operation2 = false;

    if(oper.IsSameAs(wxT("==")))
    {
        if(Is1String == true && Is2String == true)
        {
            if(value1.IsSameAs(value2))
                Operation1 = true;
        }
        else
        {
            if(num1 == num2)
                Operation1 = true;
        }
    }
    if(oper.IsSameAs(wxT("!=")))
    {
        if(Is1String == true && Is2String == true)
        {
            if(!value1.IsSameAs(value2))
                Operation1 = true;
        }
        else
        {
            if(num1 != num2)
                Operation1 = true;
        }
    }
    if(oper.IsSameAs(wxT(">=")))
    {
        if(num1 >= num2)
            Operation1 = true;
    }
    if(oper.IsSameAs(wxT("<=")))
    {
        if(num1 <= num2)
            Operation1 = true;
    }
    if(oper.IsSameAs(wxT(">")))
    {
        if(num1 > num2)
            Operation1 = true;
    }
    if(oper.IsSameAs(wxT("<")))
    {
        if(num1 < num2)
            Operation1 = true;
    }

    if(oper2.IsSameAs(wxT("==")))
    {
        if(Is3String == true && Is4String == true)
        {
            if(value3.IsSameAs(value4))
                Operation2 = true;
        }
        else
        {
            if(num3 == num4)
                Operation2 = true;
        }
    }
    if(oper2.IsSameAs(wxT("!=")))
    {
        if(Is3String == true && Is4String == true)
        {
            if(!value3.IsSameAs(value4))
                Operation2 = true;
        }
        else
        {
            if(num3 != num4)
                Operation2 = true;
        }
    }
    if(oper2.IsSameAs(wxT(">=")))
    {
        if(num3 >= num4)
            Operation2 = true;
    }
    if(oper2.IsSameAs(wxT("<=")))
    {
        if(num3 <= num4)
            Operation2 = true;
    }
    if(oper2.IsSameAs(wxT(">")))
    {
        if(num3 > num4)
            Operation2 = true;
    }
    if(oper2.IsSameAs(wxT("<")))
    {
        if(num3 < num4)
            Operation2 = true;
    }

    if(ao.IsSameAs(wxT("And")))
    {
        if(Operation1 == true && Operation2 == true)
        {
            MyTPSocket->UpdateState(result1,store1);
        }
        else
        {
            MyTPSocket->UpdateState(result2,store2);
        }
    }
    if(ao.IsSameAs(wxT("Or")))
    {
        if(Operation1 == true || Operation2 == true)
        {
            MyTPSocket->UpdateState(result1,store1);
        }
        else
        {
            MyTPSocket->UpdateState(result2,store2);
        }
    }
}

void zToolsApp::SubString(wxString r, wxString str, wxString s, wxString c)
{
    if(c.IsNumber() && s.IsNumber())
    {
        long num, num2;
        s.ToLong(&num);
        c.ToLong(&num2);
        MyTPSocket->UpdateState(r,str.SubString(num,num2));
    }
}

void zToolsApp::Mid(wxString r, wxString str, wxString s, wxString c)
{
    if(c.IsNumber() && s.IsNumber())
    {
        long num, num2;
        s.ToLong(&num);
        c.ToLong(&num2);
        MyTPSocket->UpdateState(r,str.Mid(num,num2));
    }

}

void zToolsApp::Left(wxString r, wxString str, wxString c)
{
    if(c.IsNumber())
    {
        long num;
        c.ToLong(&num);
        MyTPSocket->UpdateState(r,str.Left(num));
    }

}

void zToolsApp::Right(wxString r, wxString str, wxString c)
{
    if(c.IsNumber())
    {
        long num;
        c.ToLong(&num);
        MyTPSocket->UpdateState(r,str.Right(num));
    }

}

void zToolsApp::StartsWith(wxString r, wxString str, wxString s)
{
    MyTPSocket->UpdateState(r,wxString::Format(wxT("%i"),str.StartsWith(s)));
}

void zToolsApp::EndsWith(wxString r, wxString str, wxString s)
{
    MyTPSocket->UpdateState(r,wxString::Format(wxT("%i"),str.EndsWith(s)));
}

void zToolsApp::Length(wxString r, wxString str)
{
    MyTPSocket->UpdateState(r,wxString::Format(wxT("%i"),str.Length()));
}

void zToolsApp::ScrollingMarquee(wxString r, wxString str, wxString ln)
{
    long tempLn = 0;
    if(ln.IsNumber())
        ln.ToLong(&tempLn);

    if(tempLn <= 0 || tempLn > (int)str.Length())
        tempLn = str.Length();



    if(r.IsSameAs(wxT("sMarquee0")))
    {
        sMarquee[0].Message = str + wxT(" - ");
        if(ln.IsNumber())
            ln.ToLong(&sMarquee[0].DisplayLength);
    }
    if(r.IsSameAs(wxT("sMarquee1")))
    {
        sMarquee[1].Message = str + wxT(" - ");
        if(ln.IsNumber())
            ln.ToLong(&sMarquee[1].DisplayLength);
    }
    if(r.IsSameAs(wxT("sMarquee2")))
    {
        sMarquee[2].Message = str + wxT(" - ");
        if(ln.IsNumber())
            ln.ToLong(&sMarquee[2].DisplayLength);
    }
    if(r.IsSameAs(wxT("sMarquee3")))
    {
        sMarquee[3].Message = str + wxT(" - ");
        if(ln.IsNumber())
            ln.ToLong(&sMarquee[3].DisplayLength);
    }
    if(r.IsSameAs(wxT("sMarquee4")))
    {
        sMarquee[4].Message = str + wxT(" - ");
        if(ln.IsNumber())
            ln.ToLong(&sMarquee[4].DisplayLength);
    }
    if(r.IsSameAs(wxT("sMarquee5")))
    {
        sMarquee[5].Message = str + wxT(" - ");
        if(ln.IsNumber())
            ln.ToLong(&sMarquee[5].DisplayLength);
    }
    if(r.IsSameAs(wxT("sMarquee6")))
    {
        sMarquee[6].Message = str + wxT(" - ");
        if(ln.IsNumber())
            ln.ToLong(&sMarquee[6].DisplayLength);
    }
    if(r.IsSameAs(wxT("sMarquee7")))
    {
        sMarquee[7].Message = str + wxT(" - ");
        if(ln.IsNumber())
            ln.ToLong(&sMarquee[7].DisplayLength);
    }
    if(r.IsSameAs(wxT("sMarquee8")))
    {
        sMarquee[8].Message = str + wxT(" - ");
        if(ln.IsNumber())
            ln.ToLong(&sMarquee[8].DisplayLength);
    }
    if(r.IsSameAs(wxT("sMarquee9")))
    {
        sMarquee[9].Message = str + wxT(" - ");
        if(ln.IsNumber())
            ln.ToLong(&sMarquee[9].DisplayLength);
    }

    MyTPSocket->UpdateState(r,str.Left(tempLn));
}

BOOL zToolsApp::enumWindowCallback(HWND hWnd, LPARAM lparam) {
    wxArrayString& tempAry = *reinterpret_cast<wxArrayString*>(lparam);

    int length = GetWindowTextLength(hWnd);
    char* buffer = new char[length + 1];
    GetWindowTextA(hWnd, buffer, length + 1);
    wxString windowTitle = wxString::FromUTF8(buffer);
    delete(buffer);

    //Get Exe Name
    TCHAR buffer2[MAX_PATH] = {0};
    DWORD dwProcId = 0;

    GetWindowThreadProcessId(hWnd, &dwProcId);

    HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ , FALSE, dwProcId);
    //GetModuleFileName((HMODULE)hProc, buffer2, MAX_PATH);
    GetModuleFileNameEx(hProc, NULL, buffer2, MAX_PATH);
    CloseHandle(hProc);
    wxString exeTitle(buffer2);
    // List visible windows with a non-empty title
    if (IsWindowVisible(hWnd) && length != 0) {
        if(windowTitle.Find('\\') > 0)
            windowTitle.Replace(wxT("\\"),wxT("\\\\"),true);
        //wxString h = wxString::Format(wxT("%p"),hWnd);
        tempAry.Add(wxT("[") + exeTitle.AfterLast(wxT('\\')) + wxT("] ") + windowTitle);
        //tempAry.Add(wxT("[") + exeTitle.AfterLast(wxT('\\')) + wxT("] ") + windowTitle + wxT(" [") + h + wxT("]"));
    }
    return TRUE;
}

void zToolsApp::GetApplicationInfo()
{
    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
    wxArrayString myAry;

    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
        return;

    cProcesses = cbNeeded / sizeof(DWORD);

    for ( i = 0; i < cProcesses; i++ )
    {
        if( aProcesses[i] != 0 )
        {
            //PrintProcessNameAndID( aProcesses[i] );
            HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i] );
            if (NULL != hProcess )
            {
                HMODULE hMod;
                DWORD cbNeeded;

                if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), &cbNeeded) )
                {
                    GetModuleBaseName( hProcess, hMod, szProcessName, sizeof(szProcessName)/sizeof(TCHAR) );
                    wxString exeName(szProcessName);
                    myAry.Add(exeName);
                    //wxString handleName
                }
            }
            CloseHandle( hProcess );
        }
    }
    MyTPSocket->UpdateList(wxT("zt_window_01"),myAry);
}
void zToolsApp::SetupCapture()
{
    CaptureSetup = true;
    screenshot = new wxBitmap(128,128);
    buttonImage = new wxImage(128,128);
    parentWindow = new wxWindow();
    myScreenDC = new wxScreenDC();
    memScreenDC = new wxMemoryDC();
    memWindowDC = new wxMemoryDC();
}

void zToolsApp::ScreenWindowCapture(wxString r, wxString app, wxString x, wxString y, wxString b, wxString bp)
{
    if(!CaptureSetup)
        SetupCapture();

    cout << "Made It Past Setup" << endl;

    if(!app.IsEmpty())
    {
        if(x.IsNumber() && y.IsNumber())
        {
            x.ToLong(&lx);
            y.ToLong(&ly);
            bp.ToLong(&lbp);

            if(app.IsSameAs(wxT("Screen Capture")))
            {
                cout << "Desktop Found" << endl;
                memScreenDC->SelectObject(*screenshot);
                memScreenDC->Blit(0, 0, 128, 128, myScreenDC, lx, ly);
                memScreenDC->SelectObject(wxNullBitmap);
            }
            else
            {
                wxString windowTitle = app.AfterFirst(']');
                windowTitle.Trim(true); windowTitle.Trim(false);

                //RECT rc;

                HWND appHWND = FindWindow(NULL,windowTitle);

                if (appHWND == NULL)
                {
                    cout << "it can't find any 'note' window" << endl;
                    return;
                }
                GetClientRect(appHWND, &rc);

                if((lx+128) > (rc.right - rc.left) || (ly+128) > rc.bottom - rc.top)
                    return;

                memWindowDC->SelectObject(*screenshot);
                if(!oldTitle.IsSameAs(windowTitle))
                {
                    if(parentWindow)
                        delete(parentWindow);
                    parentWindow = new wxWindow();
                    parentWindow->SetHWND(appHWND);
                    myWindowDC = new wxClientDC(parentWindow);
                }

                PrintWindow(appHWND, myWindowDC->GetHDC(), 3);
                memWindowDC->Blit( 0, 0, 128, 128, myWindowDC, lx, ly);
                memWindowDC->SelectObject(wxNullBitmap);

                oldTitle = windowTitle;
                oldHWND = appHWND;
            }


            *buttonImage = screenshot->ConvertToImage();

            if(buttonImage->IsOk())
            {
                if(!buttonImage->HasAlpha())
                    buttonImage->InitAlpha();

                if(b.Find(wxT("Top")) > -1 || b.IsSameAs(wxT("All")))
                {
                    for(int py=0; py < lbp; py++)
                        for(int px=0; px < 128; px++)
                            buttonImage->SetAlpha(px,py,0);
                }
                if(b.Find(wxT("Bottom")) > -1 || b.IsSameAs(wxT("All")))
                {
                    for(int py=(128-lbp); py < 128; py++)
                        for(int px=0; px < 128; px++)
                            buttonImage->SetAlpha(px,py,0);
                }
                if(b.Find(wxT("Left")) > -1 || b.IsSameAs(wxT("All")))
                {
                    for(int px=0; px < lbp; px++)
                        for(int py=0; py < 128; py++)
                            buttonImage->SetAlpha(px,py,0);
                }
                if(b.Find(wxT("Right")) > -1 || b.IsSameAs(wxT("All")))
                {
                    for(int px=(128-lbp); px < 128; px++)
                        for(int py=0; py < 128; py++)
                            buttonImage->SetAlpha(px,py,0);
                }

                MyTPSocket->UpdateState(r,buttonImage);

                //buttonImage->Destroy();
            }
        }
    }
}



//void ChangeAppVolume(int ArgCount, char* AppList)
void zToolsApp::ChangeAppVolume(wxString AppName, float incVol)
{
    HRESULT hr=NULL;
    int nSessionCount;
    DWORD procID;

    CoInitialize(NULL);
    IMMDeviceEnumerator *deviceEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
    IMMDevice *defaultDevice = NULL;

    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);

    deviceEnumerator->Release();
    deviceEnumerator = NULL;

    IAudioSessionManager2* pAudioSessionManager2;
    hr = defaultDevice->Activate(__uuidof(IAudioSessionManager2), CLSCTX_ALL, NULL, (VOID**) &pAudioSessionManager2);
    IAudioSessionEnumerator* pAudioSessionEnumerator;
    hr = pAudioSessionManager2->GetSessionEnumerator(&pAudioSessionEnumerator);
    pAudioSessionEnumerator->GetCount(&MixerAppCount);


    cout << MixerAppCount << endl;

    IAudioSessionControl* pSessionControl = NULL;
    IAudioSessionControl2* pSessionControl2 = NULL;
    LPWSTR pswSession = NULL;

    for (int index = 0 ; index < MixerAppCount ; index++)
    {
        CoTaskMemFree(pswSession);
        SAFE_RELEASE(pSessionControl);

        hr = pAudioSessionEnumerator->GetSession(index, &pSessionControl);

        hr = pSessionControl->QueryInterface(__uuidof(IAudioSessionControl2), (void**) &pSessionControl2);
        hr = pSessionControl2->GetDisplayName(&pswSession);
        wcout << "Process Name Identifier: " << pswSession << endl;
        //printf(("Session Index , \"%s\"\n"), pswSession);

        if(pswSession[0] == '@')
        {
            cout << "Notifications Found!" << endl;
            MixerApps[index].szProcessName = "Windows Notifications";
            cout << MixerApps[index].szProcessName << endl;
            MixerApps[index].procID = 0;
        }


        hr = pSessionControl2->GetProcessId(&procID);
        TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

        if (NULL != procID ) {
            HMODULE hMod;
            DWORD cbNeeded;
            HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, procID);
            if(GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName)/sizeof(*szProcessName)) == 0 ) {
                //if(pSessionControl2->IsSystemSoundsSession())
                //    cout << "System Sound" << endl;
                cout << "Process Name: Error" << endl;
            } else {
                MixerApps[index].procID = procID;
                //string tmp = szProcessName;
                wxString tmp(szProcessName);
                MixerApps[index].szProcessName = tmp;
                cout << "Process ID Name: " << MixerApps[index].szProcessName << endl;
                cout << "Process ID: " << MixerApps[index].procID << endl;

                wxString tempName(MixerApps[index].szProcessName);
                cout << "TempName - " << tempName << endl;
                if(tempName.Lower().IsSameAs(AppName.Lower()))
                {
                    //Hope It Works
                    ISimpleAudioVolume *pSimpleAudioVolume = NULL;
                    hr = pSessionControl2->QueryInterface(__uuidof(ISimpleAudioVolume), (void**) &pSimpleAudioVolume);
                    //hr = pSimpleAudioVolume->SetMute(false,NULL);
                    //hr = pSimpleAudioVolume->SetMasterVolume(1.0f,NULL);
                    cout << "Changed Volume" << endl;
                    float curVol;
                    pSimpleAudioVolume->GetMasterVolume(&curVol);
                    hr = pSimpleAudioVolume->SetMasterVolume(curVol+(incVol/100.0f),NULL);
                    cout << "CurVol = " << curVol << endl;
                    //hr = pSimpleAudioVolume->SetMasterVolume(0.5f,NULL);
                }
            }
        }
    }

    CoTaskMemFree(pswSession);

    CoUninitialize();
}

void zToolsApp::ChangeMainVolume(float nVolume)
{
    CoInitialize(NULL);
    HRESULT hr=NULL;


    IMMDeviceEnumerator *deviceEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
    IMMDevice *defaultDevice = NULL;
    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);

    IAudioEndpointVolume *endpointVolume = NULL;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
    defaultDevice->Release();
    defaultDevice = NULL;


    float currentVolume = 0;
    hr = endpointVolume->GetMasterVolumeLevel(&currentVolume);

    hr = endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);

    //if (bScalar==false)
    //{
        hr = endpointVolume->SetMasterVolumeLevel(nVolume, NULL);
    //}
    //else if (bScalar==true)
    //{
        hr = endpointVolume->SetMasterVolumeLevelScalar(nVolume, NULL);
    //}

    endpointVolume->Release();

    CoUninitialize();


    //return FALSE;
}
