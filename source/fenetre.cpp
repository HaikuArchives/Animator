#include "fenetre.h"
#include <Application.h>
//-------------------------------------------------------------------
MainWindow::MainWindow()
	: BWindow(BRect(140, 30, 340, 130), "Animator v1.0", 
	B_TITLED_WINDOW, B_NOT_ZOOMABLE | B_WILL_ACCEPT_FIRST_CLICK | B_NOT_RESIZABLE)
{
	//Load the drop-down list
	Menu = new BMenuBar(BRect(0, 0, 100, 10), "MainMenu");
	SubMenu = new BMenu("Menu");
	SubMenu2 = new BMenu("Delay");
	SubMenu3 = new BMenu("Loop");

	SubMenu->AddItem(new BMenuItem("Animate", new BMessage(ANIMATE)));
	SubMenu->AddItem(new BMenuItem("Clear", new BMessage(CLEAR)));
	SubMenu->AddItem(new BMenuItem("About", new BMessage(ABOUT)));

	SubMenu2->AddItem(new BMenuItem("0.1 sec", new BMessage(SPEED1)));
	SubMenu2->AddItem(new BMenuItem("0.2 sec", new BMessage(SPEED2)));
	SubMenu2->AddItem(new BMenuItem("0.3 sec", new BMessage(SPEED3)));
	SubMenu2->AddItem(new BMenuItem("0.4 sec", new BMessage(SPEED4)));
	SubMenu2->AddItem(new BMenuItem("0.5 sec", new BMessage(SPEED5)));
	SubMenu2->SetRadioMode(true);

	SubMenu3->AddItem(new BMenuItem("1 time", new BMessage(LOOP1)));
	SubMenu3->AddItem(new BMenuItem("2 times", new BMessage(LOOP2)));
	SubMenu3->AddItem(new BMenuItem("3 times", new BMessage(LOOP3)));
	SubMenu3->AddItem(new BMenuItem("5 times", new BMessage(LOOP4)));
	SubMenu3->AddItem(new BMenuItem("10 times", new BMessage(LOOP5)));
	SubMenu3->SetRadioMode(true);

	SubMenu->AddItem(SubMenu2);
	SubMenu->AddItem(SubMenu3);
	Menu->AddItem(SubMenu);
	AddChild(Menu);
	Main = new MainView();
	AddChild(Main);
}
//-------------------------------------------------------------------
bool MainWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true; //on permet de quitter
}
//-------------------------------------------------------------------
void MainWindow::MessageReceived(BMessage * message)
{
	switch(message->what) 
	{
		case ABOUT: case CLEAR:
		case SPEED1: case SPEED2: case SPEED3: case SPEED4: case SPEED5:
		case LOOP1: case LOOP2: case LOOP3: case LOOP4: case LOOP5:
		case ANIMATE: Main->MessageReceived(message);break;
		
		default:BWindow::MessageReceived(message);break;
	}
	UpdateIfNeeded();
}
//-------------------------------------------------------------------
