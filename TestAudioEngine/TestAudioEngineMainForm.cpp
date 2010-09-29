// Application main form file.
 
// Original file name: TestAudioEngineMainForm.cpp
// Generated by TOPS Builder:Project wizard,Date:2010-9-29
 

 
#include  "TestAudioEngineMainForm.h"
#include  "testaudioengine_res_def.h"
#include  "TestAudioEngineUnicodeScript_str.h"
#include  "SimpleAudioEngine/SimpleAudioEngine.h"
#include  <cassert>

const static char s_BackgroundFile[] = "/NEWPLUS/TDA_DATA/UserData/background.mp3";
const static char s_Effect1File[]    = "/NEWPLUS/TDA_DATA/UserData/Effect1.mp3";
const static char s_Effect2File[]    = "/NEWPLUS/TDA_DATA/UserData/Effect2.mp3";

TMainForm::TMainForm(TApplication * pApp):TWindow(pApp)
, m_nEffect1ID(0)
, m_nEffect2ID(0)
{
	Create(TESTAU_ID_Form1002);
}

TMainForm::~TMainForm()
{

}

Boolean TMainForm::EventHandler(TApplication * pApp, EventType * pEvent)
{
	Boolean bHandled = FALSE;

	switch(pEvent->eType)
	{
	case EVENT_WinInit:
		{
			bHandled = TRUE;
		}
		break;
	case EVENT_WinPaint:
		{
			DrawWindow();
			bHandled = TRUE;
		}
		break;
	case EVENT_CtrlSelect:
		{
			//switch(pEvent->sParam1)
			//{
			//case RES_SYSTEM_WINDOW_TITLE_BUTTON_ID:
			//	bHandled = TRUE;
			//	break;			
			//}
            bHandled = CtrlSelected(pApp, pEvent);
		}
		break;
	case EVENT_WinClose:
		{
			// Stop the application since the main form has been closed
			pApp->SendStopEvent();
		}
		break;
	}
	
	if (FALSE == bHandled)
	{
		return TWindow::EventHandler(pApp,pEvent);
	}
	return bHandled;
}

Boolean TMainForm::CtrlSelected(TApplication * pApp, EventType * pEvent)
{
    Boolean bHandled = FALSE;
    SimpleAudioEngine* pAudioEngine = SimpleAudioEngine::getSharedSimpleAudioEngine();

    switch (pEvent->sParam1)
    {
    case TESTAU_ID_Form1002_PlayBack:
        // play background music
        pAudioEngine->playBackgroundMusic(s_BackgroundFile, true);
        pAudioEngine->SetBackgroundMusicVolume(30);
        bHandled = TRUE;
        break;

    case TESTAU_ID_Form1002_StopBack:
        // stop background music
        pAudioEngine->stopBackgroundMusic();
        bHandled = TRUE;
        break;

    case TESTAU_ID_Form1002_LoadEffect:
        // load effect1
        m_nEffect1ID = pAudioEngine->preloadEffect(/*s_Effect1File*/s_BackgroundFile);
        assert(m_nEffect1ID > 0);
        bHandled = TRUE;
        break;

    case TESTAU_ID_Form1002_UnLoadBtn:
        // unload effect1
        pAudioEngine->unloadEffect(m_nEffect1ID);
        m_nEffect1ID = 0;
        bHandled = TRUE;
        break;

    case TESTAU_ID_Form1002_PlayLoaded:
        // play loaded effect1
        if (m_nEffect1ID == 0)
        {
            pApp->MessageBox(UnloadedTip, FailedTitle, WMB_OKCANCEL);
        }
        else
        {
            pAudioEngine->playPreloadedEffect(m_nEffect1ID);
            pAudioEngine->SetEffectsVolume(30);
        }
        bHandled = TRUE;
        break;
    case TESTAU_ID_Form1002_PlayEffect:
        // play effect2
        m_nEffect2ID = pAudioEngine->playEffect(s_Effect2File);
        assert(m_nEffect2ID > 0);

        pAudioEngine->SetEffectsVolume(30);
        bHandled = TRUE;
        break;
    default:
        break;
    }

    return bHandled;
}
