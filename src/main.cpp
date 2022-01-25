#include "main.h"
#include "TPConnection.h"

using namespace std;

wxIMPLEMENT_APP_CONSOLE(zToolsApp);

wxBEGIN_EVENT_TABLE(zToolsApp, wxAppConsole)
    EVT_TIMER(TIMER_ID, zToolsApp::OnTimer)
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
    MyTPSocket = new TPConnection(wxT("zk_tools"));


    MyTimer->Start(25);
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
                        cout << "Size - " << TPData.size() << endl;
                        wxJSONValue TempVal = TPData.front();
                        cout << "TPDataType - " << TempVal["type"].AsString().mb_str() << endl;
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

                            if(TempVal["actionId"].IsSameAs(wxT("ztools_screencapture")))
                                ScreenCapture(TempVal["data"][0]["value"].AsString(),TempVal["data"][1]["value"].AsString(),TempVal["data"][2]["value"].AsString(),TempVal["data"][3]["value"].AsString(),TempVal["data"][4]["value"].AsString());

                            //if(TempVal["connectorId"].IsSameAs(wxT("ztools_advancedslider")))
                            //    cout << TempVal["data"][0]["value"].AsString().mb_str() << endl;
                                //GetSliderValue(TempVal["data"][0]["value"].AsString(),TempVal["data"][1]["value"].AsString());

                                //AdvancedSlider();


                            //aValues.Clear();
                        }
                        if(TempVal["type"].IsSameAs(wxT("connectorChange")))
                        {
                            if(TempVal["connectorId"].IsSameAs(wxT("ztools_getslidervalue")))
                            {
                                cout << "SValue 1 - " << TempVal["data"][0]["value"].AsString().mb_str() << endl;
                                GetSliderValue(TempVal["data"][0]["value"].AsString(),TempVal["value"].AsString());
                            }

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

void zToolsApp::AdvancedSlider(wxString val1, wxString val2, wxString val3)
{

}

void zToolsApp::OnTimer(wxTimerEvent& event)
{
    ProcessTPEvents();

    for(int i = 0; i < 12; i++)
        tLoopCount[i]++;

    if(tLoopCount[2] == 4)
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

    // do whatever you want to do every second here
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

void zToolsApp::ScreenCapture(wxString r, wxString x, wxString y, wxString b, wxString bp)
{
    if(x.IsNumber() && y.IsNumber())
    {
        wxScreenDC* MyScreen = new wxScreenDC();

        long lx,ly, lbp;
        x.ToLong(&lx);
        y.ToLong(&ly);
        bp.ToLong(&lbp);

        //Create a Bitmap that will later on hold the screenshot image
        //Note that the Bitmap must have a size big enough to hold the screenshot
        //-1 means using the current default colour depth
        //wxBitmap screenshot(screenWidth, screenHeight,-1);
        wxBitmap* screenshot = new wxBitmap(128, 128);

        //Create a memory DC that will be used for actually taking the screenshot
        wxMemoryDC* memDC = new wxMemoryDC();
        //Tell the memory DC to use our Bitmap
        //all drawing action on the memory DC will go to the Bitmap now
        memDC->SelectObject(*screenshot);
        //Blit (in this case copy) the actual screen on the memory DC
        //and thus the Bitmap
        memDC->Blit( 0, //Copy to this X coordinate
                    0, //Copy to this Y coordinate
                    128, //Copy this width
                    128, //Copy this height
                    MyScreen, //From where do we copy?
                    lx, //What's the X offset in the original DC?
                    ly  //What's the Y offset in the original DC?
                );
        //Select the Bitmap out of the memory DC by selecting a new
        //uninitialized Bitmap
        memDC->SelectObject(wxNullBitmap);

        //Convert To wxImage
        //wxImage buttonImage = screenshot.ConvertToImage();
        //buttonImage.InitAlpha();

        if(screenshot->IsOk())
        {
            wxImage buttonImage = screenshot->ConvertToImage();

            if(!buttonImage.HasAlpha())
                buttonImage.InitAlpha();

            //if(b.IsSameAs(wxT("Top")))
            if(b.Find(wxT("Top")) > -1 || b.IsSameAs(wxT("All")))
            {
                for(int py=0; py < lbp; py++)
                    for(int px=0; px < 128; px++)
                        buttonImage.SetAlpha(px,py,0);
            }
            if(b.Find(wxT("Bottom")) > -1 || b.IsSameAs(wxT("All")))
            {
                for(int py=(128-lbp); py < 128; py++)
                    for(int px=0; px < 128; px++)
                        buttonImage.SetAlpha(px,py,0);
            }
            if(b.Find(wxT("Left")) > -1 || b.IsSameAs(wxT("All")))
            {
                for(int px=0; px < lbp; px++)
                    for(int py=0; py < 128; py++)
                        buttonImage.SetAlpha(px,py,0);
            }
            if(b.Find(wxT("Right")) > -1 || b.IsSameAs(wxT("All")))
            {
                for(int px=(128-lbp); px < 128; px++)
                    for(int py=0; py < 128; py++)
                        buttonImage.SetAlpha(px,py,0);
            }

            //wxMemoryOutputStream* memOutputStream = new wxMemoryOutputStream();
            //buttonImage.SaveFile(*memOutputStream,wxBITMAP_TYPE_PNG);

            //wxMemoryBuffer* memBuffer = new wxMemoryBuffer();
            //memBuffer->SetBufSize(memOutputStream->GetSize());
            //memBuffer->SetDataLen(memOutputStream->GetSize());
            //memOutputStream->CopyTo(memBuffer->GetData(), memBuffer->GetDataLen());

            //MyTPSocket->UpdateState(r,memBuffer);

            MyTPSocket->UpdateState(r,&buttonImage);

            buttonImage.Destroy();
            //delete(memOutputStream);
            //delete(memBuffer);
        }
        delete(MyScreen);
        delete(screenshot);
        delete(memDC);
    }
}
