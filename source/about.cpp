#include "about.h"
#include <Roster.h>
#include "enum.h"
//-------------------------------------------------------------------
AboutBox::AboutBox()
	: BWindow(BRect(140, 40, 350, 175), "About Animator...", B_TITLED_WINDOW_LOOK,
	B_MODAL_APP_WINDOW_FEEL, B_NOT_ZOOMABLE | B_NOT_CLOSABLE |
	B_NOT_RESIZABLE | B_NOT_MINIMIZABLE)
{
	Info1 = new BStringView(BRect(10,10,340,20), "", "Animator v1.0 for R5");
	AddChild(Info1);
	Info2 = new BStringView(BRect(10,25,340,35), "", "Copyright ©2000");
	AddChild(Info2);
	Info3 = new BStringView(BRect(10,40,340,50), "", "Freeware");
	AddChild(Info3);
	Info4 = new BStringView(BRect(10,55,340,65), "", "by Jonathan Villemure");
	AddChild(Info4);
	Info5 = new BStringView(BRect(10,70,340,80), "", "Check readme.txt for more information");
	AddChild(Info5);
	Web = new BButton(BRect(10, 80, 200, 80), "", "Animator Web Page", new BMessage(WEB));
	AddChild(Web);
	Bouton = new BButton(BRect(10, 105, 200, 105), "", "OK", new BMessage(HIDEABOUT));
	AddChild(Bouton);
}
//--------------------------------------------------------------------------------
void AboutBox::MessageReceived(BMessage* message)
{
	switch(message->what)
	{
		case ABOUT: Show();break;
		case HIDEABOUT: Hide();break;

		case WEB :
		{
			char* ad = "http://www.bigfoot.com/~jvillemure";
			be_roster->Launch("application/x-vnd.Be-NPOS", 1, &ad);					
		}break;

		default: BWindow::MessageReceived(message);
	}
}
