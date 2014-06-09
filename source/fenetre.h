#ifndef FENETRE_H
#define FENETRE_H

#include <Window.h> //BWindow 
#include <MenuItem.h>
#include <Menu.h>
#include <MenuBar.h>
#include "mainview.h"
#include "enum.h"

class MainWindow : public BWindow 
{
 private :
	BMenuBar* Menu;
	BMenu* SubMenu;
	BMenu* SubMenu2;
	BMenu* SubMenu3;

 public:
	MainView* Main;

	MainWindow(); //constructeur
	virtual	bool QuitRequested(); //pour quitter
	virtual void MessageReceived(BMessage* message);
};

#endif
