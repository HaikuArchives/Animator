#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <TranslationUtils.h>
#include <Bitmap.h>
#include <String.h>
#include "enum.h"
#include "View.h"
#include <list>
#include <OS.h>

typedef list<BBitmap*>::iterator ITER;

class MainView : public BView
{
	BBitmap* CurrentBitmap; //bitmap courrant
	BView* offscreenView; //view pour dessiner offscreen
	list<BBitmap*> file; //tous les bitmaps
	ITER runner;
	int Speed;
	int Loop;
	
 public:
	translator_id* all_translators;
	int CurrentTranslator;
	
	MainView();
	~MainView();
	bool GetImage(const char* path);
	virtual void Draw(BRect);
	virtual void MessageReceived(BMessage *message);
	void AddBitmap(BBitmap* B); //add a bitmap to the deque
	void Flush(); //Flush all image in the deque
	void Animate();
};

#endif