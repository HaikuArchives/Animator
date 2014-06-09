#include "mainview.h"
#include <Path.h>
#include <TranslationUtils.h>
#include <TranslatorRoster.h>
#include <Directory.h>
#include <File.h>
#include <BitmapStream.h>
#include <string.h>
#include <NodeInfo.h>
#include <Screen.h>
#include <Application.h>
#include "main.h"
#include <stdlib.h>
//--------------------------------------------------------------------
#define min(a,b) ((a)>(b)?(b):(a))
#define max(a,b) ((a)>(b)?(a):(b))
//--------------------------------------------------------------------
MainView::MainView() 
	: BView(BRect(0, 20, 200, 100), "Image", B_FOLLOW_NONE, B_WILL_DRAW)
{
	SetViewColor(128, 128, 128);
	SetViewColor(B_TRANSPARENT_32_BIT);
	CurrentBitmap = NULL;
	all_translators = NULL;
	CurrentTranslator = -1;
	Speed = 100000;
	Loop = 1;
}
//----------------------------------------------------------------------
MainView::~MainView()
{
	Flush();
}
//----------------------------------------------------------------------
bool MainView::GetImage(const char* path)
{
	CurrentBitmap = BTranslationUtils::GetBitmap(path);
	if(CurrentBitmap == NULL) return false;

	rgb_color c;
	int height, width;
	width = (int)CurrentBitmap->Bounds().right+1;
	height = (int)CurrentBitmap->Bounds().bottom+1;

	for(int row = 0; row < height; row++)
		for(int col = 0; col < width; col++)
		{
			c = ((rgb_color *)CurrentBitmap->Bits())[(row*width + col)];
			if(c.red == 255 && c.green == 0 && c.blue == 255)
			{
				((rgb_color *)CurrentBitmap->Bits())[(row*width + col)].red = 0;
				((rgb_color *)CurrentBitmap->Bits())[(row*width + col)].green = 0;
				((rgb_color *)CurrentBitmap->Bits())[(row*width + col)].blue = 0;
			}
		}

	//on ajoute le bitmap dans la queue
	AddBitmap(CurrentBitmap);

	//on resize la fenetre et la view a la taille de la derniere image
	ResizeTo(CurrentBitmap->Bounds().right, CurrentBitmap->Bounds().bottom+20); //grosseur originale
	Window()->ResizeTo(CurrentBitmap->Bounds().right, CurrentBitmap->Bounds().bottom+20);
	Invalidate();
	return true;
}
//----------------------------------------------------------------------
void MainView::Draw(BRect R)
{
	BRect B = Bounds();
	if(file.empty())
	{//on fait un petit fill bon chic bon genre
		 FillRect(B);
		 return;
	}

	DrawBitmap(CurrentBitmap); //Copie le bitmap a l'ecran
}
//----------------------------------------------------------------------
void MainView::MessageReceived(BMessage *message)
{
   	entry_ref ref;
	BPath path;
		
 	switch (message->what)
 	{
   		case B_SIMPLE_DATA:
   		{// Look for a ref in the message
   			if(message->FindRef("refs", &ref) == B_OK)
   			{
				BEntry Entry(&ref);
				Entry.GetPath(&path);
				GetImage(path.Path());
			}
		}
		
		case ABOUT:
			((Animator*)be_app)->About->MessageReceived(message);
		break;
		
		case ANIMATE: Animate();break;
		case SPEED1: Speed = 100000;break;
		case SPEED2: Speed = 200000;break;
		case SPEED3: Speed = 300000;break;
		case SPEED4: Speed = 400000;break;
		case SPEED5: Speed = 500000;break;

		case LOOP1: Loop = 1;break;
		case LOOP2: Loop = 2;break;
		case LOOP3: Loop = 3;break;
		case LOOP4: Loop = 5;break;
		case LOOP5: Loop = 10;break;

		case CLEAR: Flush();break;			
	  	default:BView::MessageReceived(message);break;
	}
}
//----------------------------------------------------------------------
void MainView::AddBitmap(BBitmap* B)
{
	file.push_back(B);
}
//-------------------------------------------------------------------
void MainView::Flush()
{
	while(!file.empty())
	{
		delete file.back();
		file.pop_back();
	}
}
//-------------------------------------------------------------------
void MainView::Animate()
{
	for(int i=0; i<Loop; i++)
	{
   		for(runner = file.begin(); runner != file.end(); runner++)
   		{
   			CurrentBitmap = (*runner);
			Invalidate();
			Window()->UpdateIfNeeded();
			snooze(Speed);
		}
	}
}
//-------------------------------------------------------------------
