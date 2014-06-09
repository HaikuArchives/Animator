#include "main.h"
//--------------------------------------------------------------
int main()
{
	Animator* programme; 
	programme = new Animator;
	programme->Run();  
	delete programme;
	return 0;
}
//--------------------------------------------------------------
Animator::Animator() : BApplication("application/x-vnd.Animator")
{
	Fenetre = new MainWindow(); //fenetre sont les images
	About = new AboutBox(); //fenetre about
	Fenetre->Show();
	About->Run();
}
//--------------------------------------------------------------
void Animator::RefsReceived(BMessage *message) 
{ 
    entry_ref ref;
    
	// get the ref from the message
    if(message->FindRef("refs", &ref) == B_OK)
    {
        BMessage aMessage(B_SIMPLE_DATA); // Make a new message
        aMessage.AddRef( "refs", &ref ); // Copy the ref into it
       	Fenetre->PostMessage(&aMessage, Fenetre->Main); // Post the message via the window
    }
}
//--------------------------------------------------------------