#include "main.h"
#include <numbers>
#include "rc.h"



COLORREF col(HWND par, COLORREF c) {
	COLORREF custCols[16] = { 0 };
	CHOOSECOLOR cc;
	ZeroMemory(&cc, sizeof cc);
	cc.lStructSize = sizeof cc;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	cc.lpCustColors = custCols;
	cc.rgbResult = c;
	if (ChooseColor(&cc))
		return cc.rgbResult;
	return c;
}

int number_dialog::idd() const {
	return IDD_NUMBER;
}
bool number_dialog::on_init_dialog() {
	set_int(IDC_EDIT1, number);
	return true;
}
bool number_dialog::on_ok() {
	try {
		number = get_int(IDC_EDIT1);
	}
	catch (std::exception) {
		return false;
	}
	return true;
}

void main_window::on_paint(HDC hdc) {
	RECT clientRect;
	GetClientRect(*this, &clientRect);
	int centerX = clientRect.right / 2;
	int centerY = clientRect.bottom / 2;
	int circleRadius = clientRect.bottom / 4;
	brush b(color);
	obj sb(hdc, b);
	SetROP2(hdc, R2_NOTXORPEN);
	
	double angleIncrement = 2 * std::numbers::pi / n;
	
	for (int i = 0; i < n; ++i) {
		
		int smallCircleCenterX = centerX + (clientRect.bottom / 4) * cos(i * angleIncrement);
		int smallCircleCenterY = (clientRect.bottom/2) - (clientRect.bottom / 4) * sin(i * angleIncrement);
		

		Ellipse(hdc, smallCircleCenterX - circleRadius, smallCircleCenterY - circleRadius,
			smallCircleCenterX + circleRadius, smallCircleCenterY + circleRadius);
	}
	
}

void main_window::on_command(int id){
	switch(id){
		case ID_COLOR: 
		{
			color = col(*this, color);
			InvalidateRect(*this, NULL, TRUE);
			break;
		}
		case ID_NUMBER: 
		{
			number_dialog d;
			d.number = n;
			if (d.do_modal(::GetModuleHandle(NULL), *this) == IDOK) {
				n = d.number;
			}
			InvalidateRect(*this, NULL, TRUE);
			break;	
		}
		case ID_EXIT: 
			DestroyWindow(*this); 
			break;
	}
}

void main_window::on_destroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	vsite::nwp::application app;
	main_window wnd;
	wnd.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP"), (int)LoadMenu(instance, MAKEINTRESOURCE(IDM_MAIN)));
	return app.run();
}
