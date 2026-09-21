/*Yes, I know this code sucks.....
 *Only started with Hello World this morning!
 *
 *Mark Watson 20/6/00
 */

#include "Window.h"
#include "main.h"

int main(int, char**)
{	
	DualHeadApplication	App;
	App.Run();

	return(0);
}

DualHeadApplication::DualHeadApplication()
		  		  : BApplication("application/x-vnd.Be-DualHeadSetup")
{
	DualHeadWindow		*configWindow;
	BRect			configRect;
	// create a window for the config stuff
	configRect.Set(200, 200, (440+(139)), 340);
	configWindow = new DualHeadWindow(configRect);
	configWindow->Show();
}
