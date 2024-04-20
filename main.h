#include "nwpwin.h"
#include "nwpdlg.h"

class number_dialog : public vsite::nwp::dialog {
protected:
	int idd() const override;
	bool on_init_dialog() override;
	bool on_ok() override;
public:
	int number;
};

class main_window : public vsite::nwp::window {
protected:
	void on_paint(HDC hdc) override;
	void on_command(int id) override;
	void on_destroy() override;
public:
	COLORREF color{ RGB(0,0,0) };
	int n{ 10 };
};

class brush {
	HBRUSH h;
public:
	brush(COLORREF color, int hatch = -1) :
		h(hatch >= 0 ? CreateHatchBrush(hatch, color) : ::CreateSolidBrush(color)) {}
	~brush() { ::DeleteObject(h); }
	operator HBRUSH() { return h; }
};
class obj {
	HDC hdc;
	HGDIOBJ hOld;
public:
	obj(HDC hdc, HGDIOBJ hObj) :
		hdc(hdc), hOld(::SelectObject(hdc, hObj)) { }
	~obj() { ::SelectObject(hdc, hOld); }
};