/**
 * Created By: Anonymous Noman
 * Created On: 12/9/2019 2:10:04 AM
 */

#include <windows.h>

/* NOTE: 
 * The reason why we needed to define a window callback is because
 * Windows will actually use this callback function to dispatch all its necessary hidden messages immediately.
 * And that's the reason we don't actually get the direct control we handle messages ourselves
 */
LRESULT CALLBACK
MainWindowCallback(
	HWND windowHandle,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
) {
	LRESULT result = 0;
	switch(message) {

		// NOTE: The system sends this message to a window procedure when changes to the window have altered the content of the client area.	
		// !!! NOTE: The system sends the message only if there are no other messages in the application message queue.
		// !!! NOTE: WM_PAINT has lower priority than WM_SIZE except for Update and Redraw functions
		// NOTE: On resizing WM_SIZE is dispatched first
		// TODO (Dec 09, 2019): Handle WM_SIZE and WM_PAINT separately when needed 
		case WM_PAINT:
			OutputDebugStringA("WM_PAINT\n");
		case WM_SIZE:
	 		if(message == WM_SIZE) OutputDebugStringA("WM_SIZE\n");
		{
			PAINTSTRUCT paint;
			HDC deviceContext = BeginPaint(windowHandle, &paint);
			// NOTE: PatBlt is a drawing api fro gdi32.lib
			// And we are going to paint in the area provided by our device context in paint
			int x = paint.rcPaint.left;
			int y = paint.rcPaint.top;
			int width = paint.rcPaint.right - paint.rcPaint.left;
			int height = paint.rcPaint.bottom - paint.rcPaint.top;
			static DWORD color = WHITENESS;
			PatBlt(deviceContext, x, y, width, height, color);
			// Get Ready for Party Night
			if (color == WHITENESS) {
				color = BLACKNESS;
			} else {
				color = WHITENESS;
			}
			EndPaint(windowHandle, &paint);
		} break;

		case WM_DESTROY:
		{
			OutputDebugStringA("WM_DESTROY\n");
			
		} break;

		case WM_CLOSE:
		{
			OutputDebugStringA("WM_CLOSE\n");
			
		} break;

		case WM_ACTIVATEAPP:
		{
			OutputDebugStringA("WM_ACTIVATEAPP\n");
			
		} break;

		default:
		{	
			result = DefWindowProcA(windowHandle, message, wParam, lParam);
			// OutputDebugStringA("DEFAULT\n");
		} break;
	}

	return result;
}

int CALLBACK
WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd

) {
	WNDCLASSA windowClass = {0};
	// TODO (Dec 09, 2019): Check whether the following legacy flags are still needed or not
	windowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
  	windowClass.lpfnWndProc = &MainWindowCallback;
  	windowClass.hInstance = hInstance;
  	// windowClass.hIcon;
  	windowClass.lpszClassName = "HandmadeHeroWindowClass";
		
	if(RegisterClassA(&windowClass)){
		HWND windowHandle = CreateWindowExA(
								0,
								windowClass.lpszClassName,
								"Handmade Hero",
								// MAYBE: We are using overlapped window to avoid extra overhead.
								WS_OVERLAPPEDWINDOW|WS_VISIBLE,
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								NULL,
								NULL,
								hInstance,
								// NOTE: Any param that is passed here will be passed to Callback Function with WM_CREATE flag 
								NULL
							);
		if (windowHandle) {
			// NOTE: Windows doesn't automatically dispatch messages, it just adds the messages to it's queue
			// For more check the message loop
			MSG msg;
			for (; ; ) {
				// First we are going to get the message
				// !!! NOTE: GetMessage actually stall the program untill there is message to handle
				// which are we not going to use, we will use PeekMessage to just peek at the queue 
				// and handle available messages, if there is no message we will continue to other stuff
				// which is not possible through GetMessage function
				BOOL messageResult = GetMessage(&msg, NULL, 0, 0);
				if (messageResult > 0) {
					// Then we will do some processing
					TranslateMessage(&msg);
					// Finally we will dispatch the message
					DispatchMessageA(&msg);
				} else {
					// if anything goes wrong we will just break out of loop
					break;
				}
			}
			// TODO (Dec 09, 2019): Process WM_QUIT and negative message Result 
			
		} else {
			// TODO (Dec 09, 2019): Logging --> Handle the Exception
		}
	
	} else {
		// TODO (Dec 09, 2019): Logging --> Handle the Exception
	}

	return 0;
}
