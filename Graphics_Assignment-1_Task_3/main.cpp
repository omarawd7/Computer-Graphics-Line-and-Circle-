#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
#include <tchar.h>
#include <windows.h>
#include<math.h>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

void swap(int& x1, int& y1, int& x2, int& y2)
{
	int tmp = x1;
	x1 = x2;
	x2 = tmp;
	tmp = y1;
	y1 = y2;
	y2 = tmp;
}
int Round(double x)
{
	return (int)(x + 0.5);
}
void DrawLine1(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)//Simple Digital Different Analyzer DDA   to Draw a line
{
	int dx = x2 - x1; // Different of x
	int dy = y2 - y1;// Different of y
	if (abs(dy) <= abs(dx))// if the M<1
	{
		if (x1 > x2)swap(x1, y1, x2, y2);
		SetPixel(hdc, x1, y1, c);//the center
		int x = x1;
		while (x < x2)
		{
			x++;
			double y = y1 + (double)(x - x1)*dy / dx; //y=y+m
			SetPixel(hdc, x, Round(y), c);
		}
	}
	else {
		if (y1 > y2)swap(x1, y1, x2, y2);
		SetPixel(hdc, x1, y1, c);
		int y = y1;
		while (y < y2)
		{
			y++;
			double x = x1 + (double)(y - y1)*dx / dy;//x+=1/m
			SetPixel(hdc, Round(x), y, c);
		}
	}

}


void draweight(HDC hdc,int x,int y,int xc,int yc){//every two octals will have same color
SetPixel(hdc,xc+x,yc+y,RGB(100,0,0));
SetPixel(hdc,xc-x,yc-y,RGB(100,0,0));
DrawLine1(hdc,xc+x,yc+y,xc-x,yc-y,RGB(128,0,128));

SetPixel(hdc,xc+x,yc-y,RGB(100,0,0));
SetPixel(hdc,xc-x,yc+y,RGB(100,0,0));
DrawLine1(hdc,xc+x,yc-y,xc-x,yc+y,RGB(65,105,225));

SetPixel(hdc,xc+y,yc+x,RGB(100,0,0));
SetPixel(hdc,xc-y,yc-x,RGB(100,0,0));
DrawLine1(hdc,xc+y,yc+x,xc-y,yc-x,RGB(255,0,0));

SetPixel(hdc,xc+y,yc-x,RGB(100,0,0));
SetPixel(hdc,xc-y,yc+x,RGB(100,0,0));
DrawLine1(hdc,xc+y,yc-x,xc-y,yc+x,RGB(255,255,0));

}

void DrawCircleMidpoint(HDC hdc,int xc,int yc,int r){//Bresenham's Circle Algorithm //if d <0  d+=2x+3 else d+=2(x-y)+5
int x=0;
int y=r;
double d=1-r;
draweight(hdc,x,y,xc,yc);
while(x<y){
    if(d<=0){
        d=d+2*x+3;
    }
    else{
        d=d+2*(x-y)+5;
        y--;
    }
    x++;
    draweight(hdc,x,y,xc,yc);
}
}
int x1,x2,y2;
int rr,x_c,y_c,x_2,y_2;

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        case WM_LBUTTONDBLCLK:
            x_c=LOWORD(lParam);
            y_c=HIWORD(lParam);
            break;
        case WM_RBUTTONDBLCLK:
            x_2=LOWORD(lParam);
            y_2=HIWORD(lParam);
            rr=sqrt(pow((x_2-x_c),2)+pow((y_2-y_c),2));
            DrawCircleMidpoint(hdc,x_c,y_c,rr);
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
