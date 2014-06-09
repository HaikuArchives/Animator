#ifndef MAIN_H
#define MAIN_H

#include <Application.h> //BApplication
#include <Entry.h>
#include "fenetre.h" //la fenetre de l'application
#include "about.h"

class Animator : public BApplication
{
 public:
 	MainWindow* Fenetre;
	AboutBox* About;
	Animator(); //constructeur de l'application
	virtual void RefsReceived( BMessage *message );
};

#endif