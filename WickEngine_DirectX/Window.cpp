// ------------------------------------------------------------------------------------------------
// File:			Window.cpp
//-------------------------------------------------------------------------------------------------

#include "Window.h"
namespace wick
{
	// Constructor.
	Window::Window(string title, int width, int height)
	{
		title_ = title;
		if(height <= 0 || width <= 0)
		{
			wickThrowError("Invalid Window dimensions.");
		}
		width_ = width;
		height_ = height;
		fps_ = 60;
		frames_ = 0;
		initialized_ = false;
		graphics_ = new Graphics();
		graphics_->states_.push_back(new DefaultState());
		graphics_->currentState_ = graphics_->states_[0];
		initializeWick();
		wickPrint("WickEngine_DirectX " + wickVersion_);
	}

	// Starts and runs the window.
	int Window::start()
	{
		ApplicationHandle = this;
		hInstance_ = GetModuleHandle(NULL);

		WNDCLASSEX wc;
		ZeroMemory(&wc, sizeof(WNDCLASSEX));

		wc.lpfnWndProc = WndProc;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.hInstance = hInstance_;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.lpszClassName = "wickapp";

		RegisterClassEx(&wc);

		hWnd_ = CreateWindow("wickapp", title_.c_str(), WS_OVERLAPPED | WS_CAPTION |
							   WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, 0, 0,  width_ + 7,
							   height_ + 32, NULL, NULL, hInstance_, NULL);

		ShowWindow(hWnd_, SW_SHOW);

		initializeD3D(hWnd_);

		const int UPDATE_TIMER_ID = 0;
		SetTimer(hWnd_, UPDATE_TIMER_ID , 15, NULL);
		const int SECOND_TIMER_ID = 1;
		SetTimer(hWnd_, SECOND_TIMER_ID, 1000, NULL);

		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));

		while(GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return msg.wParam;
		wickPrint("Window " + title_ + " created.");
		wickPrintSeparator();
	}

	// Adds state to the window.
	void Window::addState(State* state, int id)
	{
		graphics_->addState(state, id);
	}

	// Message handler.
	LRESULT Window::MessageHandler(HWND hWnd, UINT message, WPARAM wParam,
								   LPARAM lParam)
	{
		char temp;
		string key;
		switch(message)
		{
		case WM_DESTROY:
			releaseD3D();
			releaseWick();
			PostQuitMessage(0);
			wickPrintSeparator();
			wickPrint("Window terminated (0).");
			wickPrint("Press return to continue...");
			std::cin.get();
			return(0);
		case WM_TIMER:
			if(wParam == 0)
			{
				if(!initialized_)
				{
					graphics_->device_ = device_;
					for(unsigned int i = 0; i<graphics_->states_.size(); i++)
					{
						graphics_->states_[i]->initialize(graphics_);
					}
					initialized_ = true;
				}
				else
				{
					graphics_->currentState_->update(input_, fps_, graphics_);

					if(graphics_->stateReleased_)
					{
						unsigned int size = graphics_->releasedStates_.size();
						for(unsigned int i = 0; i<size; i++)
						{
							graphics_->releasedStates_[i]->release();
						}
						graphics_->releasedStates_.clear();
						graphics_->stateReleased_ = false;
					}

					if(graphics_->stateInitialized_)
					{
						unsigned int size = graphics_->initializedStates_.size();
						for(unsigned int i = 0; i<size; i++)
						{
							graphics_->initializedStates_[i]->initialize(graphics_);
						}
						graphics_->initializedStates_.clear();
						graphics_->stateInitialized_ = false;
					}

					if(graphics_->stateRemoved_)
					{
						unsigned int size = graphics_->removedStates_.size();
						for(unsigned int a = 0; a<size; a++)
						{
							int id = graphics_->removedStates_[a];
							for(unsigned int b = 0; b<graphics_->stateIds_.size(); b++)
							{
								if(graphics_->stateIds_[b] == id)
								{
									graphics_->states_.erase(graphics_->states_.begin()+b);
									graphics_->stateIds_.erase(graphics_->stateIds_.begin()+b);
								}
							}
							graphics_->removedStates_.clear();
							graphics_->stateRemoved_ = false;
						}
					}

					frames_++;
					renderFrame();
					input_->reset();
				}
			}
			else
			{
				fps_ = frames_;
				frames_ = 0;
			}
			return(0);

		case WM_SETFOCUS:
			input_->activate();
			return(0);

		case WM_KILLFOCUS:
			input_->deactivate();
			return(0);

		case WM_MOUSEMOVE:
			POINT point;
			GetCursorPos(&point);
			if (ScreenToClient(hWnd, &point))
			input_->setMouseLocation(Pair(point.x,point.y));
			return(0);

		case WM_KEYDOWN:
			key = vkToName(wParam);
			if(key != "")
			{
				input_->keyDown(key);
				input_->keyPressed(key);
			}
			return(0);
		case WM_CHAR:
			temp = wParam;
			if(temp == 8)
			{
				return(0);
			}
			key = temp;
			input_->keyDown(key);
			input_->keyPressed(key);
			return(0);
		case WM_KEYUP:
			key = vkToName(wParam);
			if(key == "")
			{
				BYTE state[256];
				GetKeyboardState(state);
				wchar_t temp2[2];
				int result = ToUnicode(wParam,(lParam >> 16) & 0xFF,state,temp2,2,1);
				if(result>0)
				{
					std::wstring wstr = (std::wstring) temp2;
					string strTo(1,0);
					WideCharToMultiByte (CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], 1, NULL, NULL);
					key = strTo;
				}
			}
			input_->keyUp(key);
			return(0);
		case WM_LBUTTONDOWN:
			key = "LMB";
			input_->keyDown(key);
			input_->keyPressed(key);
			return(0);
		case WM_LBUTTONUP:
			key = "LMB";
			input_->keyUp(key);
			return(0);
		case WM_RBUTTONDOWN:
			key = "RMB";
			input_->keyDown(key);
			input_->keyPressed(key);
			return(0);
		case WM_RBUTTONUP:
			key = "RMB";
			input_->keyUp(key);
			return(0);
		case WM_MOUSEWHEEL:
			if((short) HIWORD(wParam)>0)
			{
				key = "MWF";
			}
			else
			{
				key = "MWB";
			}
			input_->keyPressed(key);
			return(0);
		default:
			key = "";
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

	// Window procedure called by Windows.
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
							 LPARAM lParam)
	{
		return(ApplicationHandle->MessageHandler(hWnd, message, wParam,
												 lParam));
	}

	// Initilizes Direct3D.
	void Window::initializeD3D(HWND hWnd)
	{
		d3d_ = Direct3DCreate9(D3D_SDK_VERSION);

		D3DPRESENT_PARAMETERS d3dpp;

		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.BackBufferCount = 1;
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;
		d3dpp.hDeviceWindow = hWnd;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

		d3d_->CreateDevice(D3DADAPTER_DEFAULT,
						  D3DDEVTYPE_HAL,
						  hWnd,
						  D3DCREATE_SOFTWARE_VERTEXPROCESSING,
						  &d3dpp,
						  &device_);
		D3DXCreateSprite(device_, &imageSprite_);
		D3DXCreateSprite(device_, &textSprite_);
	}

	// Initilizes Wick Engine.
	void Window::initializeWick()
	{
		input_ = new Input();
	}

	// Draws a single frame to the screen.
	void Window::renderFrame()
	{
		graphics_->currentState_->paint(graphics_);

		device_->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0),
					   1.0f, 0);
		device_->BeginScene();

		vector<int> ids = graphics_->ids_;
		int id;
		unsigned int idIndex = 0;

		vector<Image*> images = graphics_->images_;
		Image* image;
		int imageIndex = 0;

		vector<Text*> texts = graphics_->texts_;
		Text* text;
		int textIndex = 0;

		for(idIndex; idIndex < ids.size(); idIndex++)
		{
			id = ids[idIndex];
			switch(id)
			{
			case Image::ID:
				image = images[imageIndex];
				imageSprite_->SetTransform(image->getMatrix());
				imageSprite_->Begin(D3DXSPRITE_ALPHABLEND);
				imageSprite_->Draw(image->getTexture()->getData(),image->getDirectXBounds(), NULL,
						           image->getDirectXLocation(), 0xFFFFFFFF);


				imageSprite_->End();
				imageIndex++;
				break;
			case Text::ID:
				text = texts[textIndex];
				textSprite_->SetTransform(text->getMatrix());
				text->getFont()->getData()->DrawText(textSprite_, text->getMessage().c_str(), -1,
													 text->getDirectXLocation(), DT_NOCLIP,
													 text->getColor().getData());
				textIndex++;
				break;
			}
		}

		device_->EndScene();
		device_->Present(NULL, NULL, NULL, NULL);

		graphics_->clear();
	}

	// Converts special virtual key codes to their Wick names.
	string Window::vkToName(int code)
	{
		switch(code)
		{
		case VK_BACK:
			return("BACK");
		case VK_TAB:
			return("TAB");
		case VK_CLEAR:
			return("CLEAR");
		case VK_RETURN:
			return("ENTER");
		case VK_SHIFT:
			return("SHIFT");
		case VK_CONTROL:
			return("CTRL");
		case VK_MENU:
			return("ALT");
		case VK_CAPITAL:
			return("CAPS");
		case VK_ESCAPE:
			return("ESC");
		case VK_PRIOR:
			return("PGUP");
		case VK_NEXT:
			return("PGDOWN");
		case VK_END:
			return("END");
		case VK_HOME:
			return("HOME");
		case VK_LEFT:
			return("LEFT");
		case VK_UP:
 			return("UP");
		case VK_RIGHT:
			return("RIGHT");
		case VK_DOWN:
			return("DOWN");
		case VK_SNAPSHOT:
			return("PRTSCREEN");
		case VK_INSERT:
			return("INS");
		case VK_DELETE:
			return("DEL");
		case VK_LWIN:
			return("LWIN");
		case VK_RWIN:
			return("RWIN");
		case VK_NUMLOCK:
			return("NUM");
		case VK_SCROLL:
			return("SCROLL");
		case VK_F1:
			return("F1");
		case VK_F2:
			return("F2");
		case VK_F3:
			return("F3");
		case VK_F4:
			return("F4");
		case VK_F5:
			return("F5");
		case VK_F6:
			return("F6");
		case VK_F7:
			return("F7");
		case VK_F8:
			return("F8");
		case VK_F9:
			return("F9");
		case VK_F10:
			return("F10");
		case VK_F11:
			return("F11");
		case VK_F12:
			return("F12");
		default:
			return("");
		}
	}

	// Deallocates Wick Engine resources.
	void Window::releaseWick()
	{
		// Releases all states.
		for(int unsigned i = 0; i<graphics_->states_.size(); i++)
		{
			graphics_->states_[i]->release();
		}
		delete(graphics_);
		delete(input_);
		// Removes all fonts.
		vector<string> installedFonts = Font::installedFonts;
		for(int unsigned i = 0; i<installedFonts.size(); i++)
		{
			RemoveFontResource(installedFonts[i].c_str());
		}
	}

	// Deallocates Direct3D resources.
	void Window::releaseD3D()
	{
		imageSprite_->Release();
		textSprite_->Release();
		device_->Release();
		d3d_->Release();
	}
}
