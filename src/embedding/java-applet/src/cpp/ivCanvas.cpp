#include <windows.h>
#include <assert.h>
#include <gl/gl.h>
#include <stdio.h>
#include "jawt_md.h"
#include "JAWT_Info.h"
#include "ivCanvas.h"

#include <iostream>
#include <fstream>

#include <string>
#include <iostream>
#include <Inventor/SoSceneManager.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/events/SoKeyboardEvent.h>
#include <Inventor/events/SoButtonEvent.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoSelection.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoScale.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/SoInteraction.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/draggers/SoTranslate1Dragger.h>
#include <Inventor/engines/SoCompose.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoCube.h>

//event IDs declarations
#define M_BACKSPACE     10001
#define M_DELETE        10002      
#define M_HOME          10003
#define M_END           10004
#define M_PAGE_UP       10005
#define M_PAGE_DOWN     10006
#define M_LEFT_ARROW    10007
#define M_RIGHT_ARROW   10008
#define M_UP_ARROW      10009
#define M_DOWN_ARROW    10010

#define BUTTON_PRESS 501
#define BUTTON_RELEASE 502
#define MOUSE_MOVE 503
#define MOUSE_DRAGGED 506

#define LEFT_BUTTON 1
#define MIDDLE_BUTTON 2
#define RIGHT_BUTTON 3
#define BUTTON_4 4
#define BUTTON_5 5



// Static variables for the OpenGL calls.
static HGLRC    hRC = NULL;
static HDC        hDC = NULL;

//global declarations
SoSceneManager *mSceneManager;
SoTranslation *myTranslation;

SoKeyboardEvent::Key translateKey(int charCode);

//This function splits a nodeName.fieldname string into nodename 
//and fieldname subparts
void splitName(std::string& name, std::string &node, std::string &field)
{
	char *tmp = 0;

	node.erase();
	field.erase();

	// find delimiter dot that separates field from node
	char *delim = (char*)strchr(name.c_str(), '.');
	if (!delim)
	{
		node = std::string(name.c_str());
	}
	else
	{
		*delim = 0;
		field = std::string(delim + 1);
		node = std::string(name.c_str());
	}
}


//this Keyboard event callback function is used in the "test" network 
//to show the keyboard event handling for right and left arrow keys
void myKeyPressCB(void *userData, SoEventCallback *eventCB)
{
	SoSelection *selection = (SoSelection *) userData;
	const SoEvent *event = eventCB->getEvent();

	if(!myTranslation)
		return;

	// Check for the right and left arrow keys being pressed.
	if (SO_KEY_PRESS_EVENT(event, RIGHT_ARROW)) 
	{
		SbVec3f myTest= myTranslation->translation.getValue();
		float val = myTest[0];
		if(val < 0.8 )
		{
			myTranslation->translation.setValue(val+0.2,0.0,0.0);
			mSceneManager->scheduleRedraw();
		}
		eventCB->setHandled();
	} 
	else if (SO_KEY_PRESS_EVENT(event, LEFT_ARROW)) 
	{
		SbVec3f myTest= myTranslation->translation.getValue();
		float val = myTest[0];
		if(val > -0.8 )
		{
			myTranslation->translation.setValue(val-0.2,0.0,0.0);
			mSceneManager->scheduleRedraw();
		}
		eventCB->setHandled();
	}
}







//This callback function is used as the renderScene callback in Inventor
void RenderScene(void *,SoSceneManager *mySceneMag)
{
	
	mSceneManager->render();
	mSceneManager->scheduleRedraw();
    ::glPopMatrix();
    ::SwapBuffers( hDC );
	
}

/*
 * Class:     ivCanvas
 * Method:    initialSetup
 * Signature: ()V
 */

//Initial setup for inventor and scenemanager initialization
JNIEXPORT void JNICALL Java_ivCanvas_initialSetup
  (JNIEnv *env, jobject panel)
{

	{
			SoInteraction::init();
			SoDB::init();
			mSceneManager = new SoSceneManager();
	}
}

/*
 * Class:     ivCanvas
 * Method:    loadGraphOpenGL
 * Signature: ()V
 */

//This function loads an iv graph whose path is specified as the string arguement
JNIEXPORT void JNICALL Java_ivCanvas_loadGraphOpenGL
  (JNIEnv *env, jobject panel, jstring filePath)
{
	
	const char *path  = env->GetStringUTFChars(filePath, 0);
	SoInput in;

	if(strcmp(path,"Test")==0)
	{
			SoSeparator *myGroup = new SoSeparator();
			myGroup->ref();
			SoOrthographicCamera *myCamera = new SoOrthographicCamera();
			SoScale *myScale = new SoScale();
			myScale->scaleFactor.setValue(0.3,0.3,0.3);
			SoDirectionalLight *myLight = new SoDirectionalLight(); 
			myLight->setName("DirLight");
			myLight->direction.setValue(SbVec3f(0.0,0.0,1.0));
			SoTranslate1Dragger  *myDragger = new SoTranslate1Dragger();
			myDragger->translation.setValue(SbVec3f(1.28031,0,0));
			SoCone *myCone=NULL;
			myCone = new SoCone();
			myTranslation = new SoTranslation();			
			SoDecomposeVec3f *myDec = new SoDecomposeVec3f();
			myDec->vector.connectFrom(&(myDragger->translation));
			myCone->bottomRadius.connectFrom(&(myDec->x));

			// An event callback node so we can receive key press events
			SoEventCallback *myEventCB = new SoEventCallback;
			myEventCB->addEventCallback(SoKeyboardEvent::getClassTypeId(),myKeyPressCB, myGroup);
			myGroup->addChild(myEventCB);
			myGroup->addChild(myCamera);
			myGroup->addChild(myScale);
			myGroup->addChild(myDragger);
			myGroup->addChild(myLight);
			myGroup->addChild(myTranslation);
			myGroup->addChild(myCone);
			
			mSceneManager->setSceneGraph(myGroup);

	}
	else
	{
		SoSeparator *rootNode = (SoSeparator*) mSceneManager->getSceneGraph();
		if(rootNode)
		{
			rootNode->removeAllChildren();
			rootNode->unref();
		}
		if (strncmp(path, "#Inventor V2.1", 14) == 0)
		{
			in.setBuffer((void*)path, strlen(path)); // string
		}
		else
		{
			in.openFile(path); // file
		}
		SoSeparator *topNode = SoDB::readAll(&in);
		topNode->ref();
		if(topNode)
			mSceneManager->setSceneGraph(topNode);
		
	}

}

/*
 * Class:     ivCanvas
 * Method:    initializeOpenGL
 * Signature: ()V
 */

//This function is responsible for initializing OpenGL
//and creating the context necessary for rendering
JNIEXPORT void JNICALL Java_ivCanvas_initializeOpenGL
  (JNIEnv *env, jobject panel)
{
	// get the window handle
    JAWT_Info info(env, panel);
    HWND hWnd = (HWND)info.getHWND();
    if(hWnd == NULL)
	{
		return;
	}
    PIXELFORMATDESCRIPTOR pfd;

    // get the device context (DC)
    HWND hwnd = info.getHWND();
    hDC = ::GetDC(hwnd);

    // set the pixel format for the DC
    ::ZeroMemory( &pfd, sizeof( pfd ) );
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cStencilBits = 8;
	pfd.cColorBits = 32;

	int pf = ChoosePixelFormat(hDC, &pfd);
	if (pf == 0) 
	{
		// ChoosePixelFormat() failed.
		return ;
	} 

	if (!SetPixelFormat(hDC, pf, &pfd)) 
	{
		// SetPixelFormat() failed.
		return;
	} 

	DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	if ((pfd.cStencilBits == 0) || (pfd.cColorBits < 24))
	{
		ReleaseDC(hWnd, hDC);
		// Pixel format unsupported.
		return ;
	}
    hRC = ::wglCreateContext( hDC );
    ::wglMakeCurrent( hDC, hRC );

	RECT rect;
	::GetClientRect(hWnd, &rect);
	int mWidth = rect.right - rect.left  ;
	int mHeight = rect.bottom - rect.top ;

	mSceneManager->setWindowSize(SbVec2s(mWidth, mHeight));
	mSceneManager->setSize(SbVec2s(mWidth, mHeight));
	mSceneManager->setViewportRegion(SbViewportRegion(mWidth, mHeight));
	mSceneManager->getGLRenderAction()->setTransparencyType(SoGLRenderAction::BLEND);
	mSceneManager->setBackgroundColor(SbColor(0.0, 0.0, 0.0));
	mSceneManager->setRenderCallback(RenderScene);
	mSceneManager->activate();
}



/*
 * Class:     ivCanvas
 * Method:    paintOpenGL
 * Signature: (Ljava/awt/Graphics;)V
 */

//This methid paints the canvas, which is the current opengl context,
//using opengl calls
JNIEXPORT void JNICALL Java_ivCanvas_paintOpenGL
  (JNIEnv *env, jobject panel)
{
	
	static float theta = 0.0f;
    // get the window handle
    JAWT_Info info(env, panel);
    HWND hWnd = (HWND)info.getHWND();
	

    if(hWnd == NULL)
        return;
	hDC = ::GetDC(hWnd);
	RECT rect;
	::GetClientRect(hWnd, &rect);
	int mWidth = rect.right - rect.left  ;
	int mHeight = rect.bottom - rect.top ;
	mSceneManager->setWindowSize(SbVec2s(mWidth, mHeight));
	mSceneManager->setSize(SbVec2s(mWidth, mHeight));
	mSceneManager->setViewportRegion(SbViewportRegion(mWidth, mHeight));
	mSceneManager->reinitialize();
    ::glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    ::glClear( GL_COLOR_BUFFER_BIT );
    ::glPushMatrix();
	::glEnable(GL_DEPTH_TEST);
	mSceneManager->render(true,true);
    ::glPopMatrix();
	::SwapBuffers( hDC );
}

/*
 * Class:     ivCanvas
 * Method:    cleanupOpenGL
 * Signature: ()V
 */

//This function cleans up the OpenGL context and releases resources
JNIEXPORT void JNICALL Java_ivCanvas_cleanupOpenGL
(JNIEnv *env, jobject panel)
{
	// get the window handle
    JAWT_Info info(env, panel);
    HWND hWnd = (HWND)info.getHWND();
    if(hWnd == NULL)
        return;

    ::wglMakeCurrent( NULL, NULL );
    ::wglDeleteContext( hRC );
    ::ReleaseDC( hWnd, hDC );
	delete mSceneManager;
}

/*
 * Class:     ivCanvas
 * Method:    setBackgroundColor
 * Signature: ()V
 */

//
JNIEXPORT void JNICALL Java_ivCanvas_setBackgroundColor
  (JNIEnv *env, jobject panel, jint red, jint green, jint blue)
{
	mSceneManager->setBackgroundColor(SbColor(red, green, blue));
	mSceneManager->activate();
}

/*
 * Class:     ivCanvas
 * Method:    setViewportRegion
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ivCanvas_setViewportRegion
  (JNIEnv *env, jobject panel,  jint width, jint height)
{
	mSceneManager->setViewportRegion(SbViewportRegion(width, height));
	mSceneManager->activate();
}

/*
 * Class:     ivCanvas
 * Method:    keyPressedEvent
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ivCanvas_keyPressedEvent
  (JNIEnv *env, jobject canvas, jstring eventdescription)
{
	/*global_env = env;*/

	
	const char *eventDesc = env->GetStringUTFChars(eventdescription, 0);
	
	std::string eventDes = std::string(eventDesc);
	//handle the case where key pressed is pipe, as pipe is also used as delimiter


	int fpos = (int)eventDes.find_first_of('|');
	int epos = (int)eventDes.find_last_of('|');
	if(fpos == 0)
		return;
	
	std::string keyCode = eventDes.substr(0,fpos);
	std::string time = eventDes.substr(fpos+1,epos);
	std::string modifiers = eventDes.substr(epos+1,eventDes.length());

	
	
	//if the keycode is only one character, it must be a letter
	//else if it is a special key like HOME, it will be more than one character.

	int key;
	if(keyCode.length() == 1)
		key = *(keyCode.c_str());
	else
		key = atoi(keyCode.c_str());

	long timeValue = atol(time.c_str());

	int mod = atoi(modifiers.c_str());
	
	bool shift_down = false;
	bool ctrl_down = false;
	bool alt_down = false;
	int temp =0;
	if(mod != 0)
	{
		temp = mod % 10;
		if(temp == 1)
			shift_down = true;
		mod = mod/10;
		temp = mod % 10;
		if(temp == 1)
			ctrl_down = true;
		mod = mod/10;
		temp = mod % 10;
		if(temp == 1)
			alt_down = true;
	}
	SoKeyboardEvent::Key sokey = translateKey(key);

	SbTime eventTime((double)timeValue);

	SoKeyboardEvent userEvent;
	userEvent.setKey(sokey);
	userEvent.setTime(eventTime);
	userEvent.setShiftDown(shift_down);
	userEvent.setCtrlDown(ctrl_down);
	userEvent.setAltDown(alt_down);
	userEvent.setState(SoButtonEvent::DOWN);
	
	if (mSceneManager->processEvent(&userEvent))
	{
		
        SoDB::getSensorManager()->processDelayQueue(FALSE);
	}
}

/*
 * Class:     ivCanvas
 * Method:    keyReleasedEvent
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ivCanvas_keyReleasedEvent
  (JNIEnv *env, jobject canvas, jstring eventdescription)
{
	/*global_env = env;*/
	const char *eventDesc = env->GetStringUTFChars(eventdescription, 0);
	
	std::string eventDes = std::string(eventDesc);
	//handle the case where key pressed is pipe, as pipe is also used as delimiter

	
	int fpos = (int)eventDes.find_first_of('|');
	int epos = (int)eventDes.find_last_of('|');
	if(fpos == 0)
		return;
	
	std::string keyCode = eventDes.substr(0,fpos);
	std::string time = eventDes.substr(fpos+1,epos);
	std::string modifiers = eventDes.substr(epos+1,eventDes.length());

	
	
	//if the keycode is only one character, it must be a letter
	//else if it is a special key like HOME, it will be more than one character.

	int key;
	if(keyCode.length() == 1)
		key = *(keyCode.c_str());
	else
		key = atoi(keyCode.c_str());

	long timeValue = atol(time.c_str());

	int mod = atoi(modifiers.c_str());
	
	bool shift_down = false;
	bool ctrl_down = false;
	bool alt_down = false;

	int temp =0;
	if(mod != 0)
	{
		temp = mod % 10;
		if(temp == 1)
			shift_down = true;
		mod = mod/10;
		temp = mod % 10;
		if(temp == 1)
			ctrl_down = true;
		mod = mod/10;
		temp = mod % 10;
		if(temp == 1)
			alt_down = true;
	}

	SoKeyboardEvent::Key sokey = translateKey(key);

	SbTime eventTime((double)timeValue);

	SoKeyboardEvent userEvent;
	userEvent.setKey(sokey);
	userEvent.setTime(eventTime);
	userEvent.setShiftDown(shift_down);
	userEvent.setCtrlDown(ctrl_down);
	userEvent.setAltDown(alt_down);
	userEvent.setState(SoButtonEvent::UP);

	if (mSceneManager->processEvent(&userEvent))
        SoDB::getSensorManager()->processDelayQueue(FALSE);
}

/*
 * Class:     ivCanvas
 * Method:    mouseEventHandler
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ivCanvas_mouseEventHandler
  (JNIEnv *env, jobject canvas , jstring eventdescription)
{

	
	const char *eventDesc = env->GetStringUTFChars(eventdescription, 0);

	std::string eventDes = std::string(eventDesc);
	unsigned int fpos = (int)eventDes.find_first_of('|');
	unsigned int pos1 = eventDes.find('|',fpos+1);
	unsigned int pos2 = eventDes.find('|',pos1+1);
	unsigned int pos3 = eventDes.find('|',pos2+1);
	unsigned int pos4 = eventDes.find('|',pos3+1);

	if(fpos == 0)
		return;
	
	std::string eventCodeStr = eventDes.substr(0,fpos);
	std::string buttonIDStr = eventDes.substr(fpos+1,pos1-fpos-1);
	std::string xcordStr = eventDes.substr(pos1+1,pos2-pos1-1);
	std::string ycordStr = eventDes.substr(pos2+1,pos3-pos2-1);
	std::string timeStr  = eventDes.substr(pos3+1,pos4-pos3-1);
	std::string modifiersStr = eventDes.substr(pos4+1,eventDes.length()-pos4-1);

	int eventCode = atoi(eventCodeStr.c_str());
	int buttonID = atoi(buttonIDStr.c_str());
	int xcord = atoi(xcordStr.c_str());
	int ycord = atoi(ycordStr.c_str());
	long time = atoi(timeStr.c_str());
	int modifiers = atoi(modifiersStr.c_str());

	bool shift_down = false;
	bool ctrl_down = false;
	bool alt_down = false;

	int temp =0;
	if(modifiers != 0)
	{
		temp = modifiers % 10;
		if(temp == 1)
			shift_down = true;
		modifiers = modifiers/10;
		temp = modifiers % 10;
		if(temp == 1)
			ctrl_down = true;
		modifiers = modifiers/10;
		temp = modifiers % 10;
		if(temp == 1)
			alt_down = true;
	}
	if(eventCode == BUTTON_PRESS || eventCode == BUTTON_RELEASE)
	{
	SoMouseButtonEvent myEvent;

	switch(eventCode)
	{
	case BUTTON_PRESS:
		myEvent.setState(SoButtonEvent::DOWN);
		break;
	case BUTTON_RELEASE:
		myEvent.setState(SoButtonEvent::UP);
	}

	switch(buttonID)
	{
	case LEFT_BUTTON:
		myEvent.setButton(SoMouseButtonEvent::BUTTON1);
		break;
	case MIDDLE_BUTTON:
		myEvent.setButton(SoMouseButtonEvent::BUTTON2);
		break;
	case RIGHT_BUTTON:
		myEvent.setButton(SoMouseButtonEvent::BUTTON3);
		break;
	/*case BUTTON_4:
		myEvent.setButton(SoMouseButtonEvent::BUTTON4);
		break;
	case BUTTON_5:
		myEvent.setButton(SoMouseButtonEvent::BUTTON5);
		break;*/
	}
	myEvent.setPosition(SbVec2s(xcord,ycord));
	SbTime eventTime((double)time);
	myEvent.setTime(eventTime);
	myEvent.setShiftDown(shift_down);
	myEvent.setCtrlDown(ctrl_down);
	myEvent.setAltDown(alt_down);

	if (mSceneManager->processEvent(&myEvent))
        SoDB::getSensorManager()->processDelayQueue(FALSE);
	}
	else
	{
		SoLocation2Event myEvent;
		myEvent.setPosition(SbVec2s(xcord,ycord));
		SbTime eventTime((double)time);
		myEvent.setTime(eventTime);
		myEvent.setShiftDown(shift_down);
		myEvent.setCtrlDown(ctrl_down);
		myEvent.setAltDown(alt_down);
		
		if (mSceneManager->processEvent(&myEvent))

			SoDB::getSensorManager()->processDelayQueue(FALSE);
		}
}



SoKeyboardEvent::Key translateKey(int charCode)
{
      SoKeyboardEvent::Key sokey;

	

      switch (charCode)
      {
            case '0':  sokey = SoKeyboardEvent::NUMBER_0; break;
            case '1':  sokey = SoKeyboardEvent::NUMBER_1; break;
            case '2':  sokey = SoKeyboardEvent::NUMBER_2; break;
            case '3':  sokey = SoKeyboardEvent::NUMBER_3; break;
            case '4':  sokey = SoKeyboardEvent::NUMBER_4; break;
            case '5':  sokey = SoKeyboardEvent::NUMBER_5; break;
            case '6':  sokey = SoKeyboardEvent::NUMBER_6; break;
            case '7':  sokey = SoKeyboardEvent::NUMBER_7; break;
            case '8':  sokey = SoKeyboardEvent::NUMBER_8; break;
            case '9':  sokey = SoKeyboardEvent::NUMBER_9; break;
            case 'a':  case 'A': sokey = SoKeyboardEvent::A; break;
            case 'b':  case 'B': sokey = SoKeyboardEvent::B; break;
            case 'c':  case 'C': sokey = SoKeyboardEvent::C; break;
            case 'd':  case 'D': sokey = SoKeyboardEvent::D; break;
            case 'e':  case 'E': sokey = SoKeyboardEvent::E; break;
            case 'f':  case 'F': sokey = SoKeyboardEvent::F; break;
            case 'g':  case 'G': sokey = SoKeyboardEvent::G; break;
            case 'h':  case 'H': sokey = SoKeyboardEvent::H; break;
            case 'i':  case 'I': sokey = SoKeyboardEvent::I; break;
            case 'j':  case 'J': sokey = SoKeyboardEvent::J; break;
            case 'k':  case 'K': sokey = SoKeyboardEvent::K; break;
            case 'l':  case 'L': sokey = SoKeyboardEvent::L; break;
            case 'm':  case 'M': sokey = SoKeyboardEvent::M; break;
            case 'n':  case 'N': sokey = SoKeyboardEvent::N; break;
            case 'o':  case 'O': sokey = SoKeyboardEvent::O; break;
            case 'p':  case 'P': sokey = SoKeyboardEvent::P; break;
            case 'q':  case 'Q': sokey = SoKeyboardEvent::Q; break;
            case 'r':  case 'R': sokey = SoKeyboardEvent::R; break;
            case 's':  case 'S': sokey = SoKeyboardEvent::S; break;
            case 't':  case 'T': sokey = SoKeyboardEvent::T; break;
            case 'u':  case 'U': sokey = SoKeyboardEvent::U; break;
            case 'v':  case 'V': sokey = SoKeyboardEvent::V; break;
            case 'w':  case 'W': sokey = SoKeyboardEvent::W; break;
            case 'x':  case 'X': sokey = SoKeyboardEvent::X; break;
            case 'y':  case 'Y': sokey = SoKeyboardEvent::Y; break;
            case 'z':  case 'Z': sokey = SoKeyboardEvent::Z; break;
            case ' ':  sokey = SoKeyboardEvent::SPACE;  break;
            case '\n': sokey = SoKeyboardEvent::RETURN; break;
            case '(':  sokey = SoKeyboardEvent::BRACKETLEFT;  break;
            case '\\': sokey = SoKeyboardEvent::BACKSLASH;    break;
            case ')':  sokey = SoKeyboardEvent::BRACKETRIGHT; break;
            case ',':  sokey = SoKeyboardEvent::COMMA;  break;
            case '-':  sokey = SoKeyboardEvent::MINUS;  break;
            case '/':  sokey = SoKeyboardEvent::SLASH;  break;
            case ';':  sokey = SoKeyboardEvent::SEMICOLON;  break;
            case '=':  sokey = SoKeyboardEvent::EQUAL;  break;
            case M_BACKSPACE : sokey = SoKeyboardEvent::BACKSPACE; break;
            case M_DELETE: sokey = SoKeyboardEvent::KEY_DELETE; break;
            case M_HOME:     sokey = SoKeyboardEvent::HOME; break;
            case M_END: sokey = SoKeyboardEvent::END; break;
            case M_PAGE_UP: sokey = SoKeyboardEvent::PAGE_UP; break;
            case M_PAGE_DOWN: sokey = SoKeyboardEvent::PAGE_DOWN; break;
            case M_LEFT_ARROW: sokey = SoKeyboardEvent::LEFT_ARROW; break;
            case M_RIGHT_ARROW: sokey = SoKeyboardEvent::RIGHT_ARROW; break;
            case M_UP_ARROW: sokey = SoKeyboardEvent::UP_ARROW; break;
            case M_DOWN_ARROW: sokey = SoKeyboardEvent::DOWN_ARROW; break;
            default:
                  sokey = SoKeyboardEvent::ANY;

      }
	  return sokey;
}




JNIEXPORT jboolean JNICALL Java_ivCanvas_loadLibraries
  (JNIEnv *env, jobject canvas, jstring library)
{
	const char *buf = env->GetStringUTFChars(library, 0);
	std::string libs = buf;
	// pre-load all libraries given in the arguments (separated by comma)
	bool loaded = true;
	//pin_ptr<const wchar_t> wch = PtrToStringChars(libs);
	std::string libraries(libs);

	while (libraries.length() > 0)
	{
		int pos = libraries.find(',');
		std::string tmp = libraries.substr(0, pos > 0 ? pos : libraries.length());
		libraries.erase(0, pos > 0 ? pos + 1 : libraries.length());

		HMODULE hm = ::LoadLibraryA(tmp.c_str());
		if (!hm)
		{
			loaded = false;
			char errMsg[2 * MAX_PATH];
			DWORD err = ::GetLastError();
			printf("\nLoading %s failed: %d ",tmp.c_str(),err);
			
			LPSTR s = 0;
			if (FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
					err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR) &s, 0, NULL) == 0)
			{ 
				// failed
				_snprintf_s(errMsg, 2 * MAX_PATH, "radAppletInventor: Failed to load library '%S' - %d\n", tmp.c_str(), err, err);
				::OutputDebugStringA(errMsg);
			}
			else
			{ 
				// succeeded
				_snprintf_s(errMsg, 2 * MAX_PATH, "radAppletInventor: Failed to load library '%S' - %d / %s", tmp.c_str(), err, s);
				::OutputDebugStringA(errMsg);
				::LocalFree(s);
			}
		}
	}

	return loaded;
}





JNIEXPORT jstring JNICALL Java_ivCanvas_get
  (JNIEnv *env, jobject canvas, jstring param)
{
	const char *nodeNameChar = env->GetStringUTFChars(param,0);
	std::string fullparam = nodeNameChar;
	std::string nodeName, fieldName;
	
	splitName(fullparam, nodeName, fieldName);

	SoFieldContainer *node = SoNode::getByName(nodeName.c_str());
	if (!node)
	{
		// maybe an engine?
		node = SoEngine::getByName(nodeName.c_str());
	}

	if (node)
	{
		if (fieldName.length() == 0)
		{
			// no field specified, return pointer to class
			char address[20];
			_snprintf_s(address, 20, "0x%p", node);

			return env->NewStringUTF(address);;
		}
		else
		{
			SoField *field = node->getField(fieldName.c_str());
			if (field)
			{
				SbString str;
				field->get(str);
				const char *currentValue = str.getString();
				std::string temp = currentValue;
				return env->NewStringUTF(currentValue);
			}
			else
				return env->NewStringUTF("");
		}
	}
	else
		return env->NewStringUTF("");
}









JNIEXPORT jboolean JNICALL Java_ivCanvas_set
  (JNIEnv *env, jobject canvas, jstring param, jstring valueString)
{
	const char *nodeNameChar = env->GetStringUTFChars(param, 0);	
	const char *inputValue = env->GetStringUTFChars(valueString,0);

	//myfile << __LINE__ << " nodeNameChar: " << (nodeNameChar ? nodeNameChar : "NULL") << std::endl;
	//myfile << __LINE__ << " inputValue: " << (inputValue ? inputValue : "NULL") << std::endl;

	std::string fullparam = nodeNameChar;
	std::string value = inputValue;
	// set generic OIV parameter
	bool isValueSet = false;
	std::string nodeName, fieldName;
	splitName(fullparam, nodeName, fieldName);

	//myfile << __LINE__ << " nodeName: " << nodeName.c_str() << std::endl;
	
	//{
	//SoFieldContainer *node = SoNode::getByName("VRTViewportBorder");
	//SoField *field = node->getField("viewAll");
	//field->set("trigger");
	//}

	SoFieldContainer *node = SoNode::getByName(nodeName.c_str());
	if (!node)
	{
		//myfile << __LINE__ << " maybe an engine?" << std::endl;
		// maybe an engine?
		node = SoEngine::getByName(nodeName.c_str());
	}

	//if (!node)
	//{
	//	myfile << __LINE__ << " !node " << std::endl;
	//}

	if (node)
	{
		//myfile << __LINE__ << " node ok" << std::endl;
		//std::auto_ptr<char> str(convertToMbs(value));

		if(value.empty())
		{
			//myfile << __LINE__ << " value is empty" << std::endl;
			SoField *field = node->getField(fieldName.c_str());
			if (field)
			{
				field->touch();
				isValueSet = true;
			}
		}

		if (!value.empty())
		{
			//myfile << __LINE__ << " value not empty" << std::endl;
			SoField *field = node->getField(fieldName.c_str());
			
			//myfile << __LINE__ << " fieldname " << fieldName.c_str() << std::endl;
			if (field)
			{
				if (value.length() > 0)
				{
					SbString valueString;
					field->get(valueString);

					//myfile << __LINE__ << " valueString " << valueString.getString() << std::endl;
					//myfile << __LINE__ << " value.c_str() " << value.c_str() << std::endl;

					if (valueString != SbString(value.c_str()))
					{
						if (field->set(value.c_str()))
							isValueSet = true;
					}
				}
				else
				{
					field->touch();
					isValueSet = false;
				}
			}
			else
			{
				if (node->set(value.c_str()))
					isValueSet = false;
			}
		}
	}

	return isValueSet;
}