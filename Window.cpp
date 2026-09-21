/*Yes, I know this code sucks..... (but I'm working on it - Seigers ;-) ).
 *Only started with Hello World this morning! <- No really... he told me the rest of the driver was written by small monkey slaves he captured whilst out in Milton Keynes!
 
 Initial code:
 Mark Watson: 20/6/00																																																												And those Monkeys! ;-)
 
 Bug fixes/Change log:-
 
 Seigers: Sat Jul  8 01:57:22 GMT 2000 
 -- Changed the radio buttons somewhat so easier expansion is possible.
 -- Fixed a minor problem with the initial settings not always being correct (was possible to turn on dual head 
 mode in modes that didn't work with it - also now only acts as a mode changer for other cards (I think - does for
 me).
 -- Added a 'firstRun' variable, used for initial setting up of things that don't need to be re-initialised after
 every change - notably the radio buttons! Version 0.0.1b should also sort out the popup menus
 
 Seigers: Sun Jul  9 20:25:53 GMT 2000
 -- Broke the CreateMenus function to create seperation between GUI and functionality.
 -- Changed the Popup menus to more system compliant versions.
 -- Put the popup's into menu fields and added labels to each.
 -- Added the 'GRAY' constant... for setting the background of the MenuFields.
 -- Added a 'VERSION' identifier for keeping track of changes (a and b releases and such). The is printed to a console when started from one.
 -- Used the SetDivider function for working out the label and popup positions in the MenuField (lined up the popups nicely!)
 --->> Generally got angry at the lack of a well thought out ComboBox facility in the InterfaceKit (ARE YOU LISTENING Be ENGINEERS!!)
 
 Seigers: Mon Jul 10 00:46:48 GMT 2000
 -- Added a BMenuBar (in it's proper use Mark!), mainly so I could get some credit and have an 'AboutBox'
 -- Note some BRects have changed to accomodate the BMenuBar's new imposition...
 -- I also note that some of the BRects were not at the edges of the window... not sure if this was deliberate or not... changed them to something I like anyhow.
 -- Just realised... version b will never see the light of day now (forgot to mail it to Mark)... ah well.... on with the improvements!!!!
 -- GRRRRRRRRRRRRR!!!! I want a G400 so I can see if this is working or not! Pah! Hummm.... now what to add/re-write??
 -- Added a cancel option to the 'test' feature, always useful, don't say I never think of the clumsy prats out there... ;-)
 
 Seigers: Mon Jul 10 17:03:25 GMT 2000
 -- Sorted Marks virtual screen problem, changing res now doesn't mean that the BeMenu goes all over the place.
 -- Got a list of bugs/features from Mark... two of them are now done (one of them was in release 'b'!)
 --  Others are now nolonger applicable because of changes already made (WOO!)
 Seigers: Mon Jul 10 22:55:45 GMT 2000
 -- Ok, only just got any of these versions tested on a G400, so some bugs have reared their ugly head. Seems as if the radioButton re-write broke their usefulness
 -- Fixed broken radioButtons (I hope). Would Mark take a look at lines marked in the constructor to tell me why he did that please...
 -- Added contact info to the about box and removed the version printing facility for commandline use - it's in the about box if needed!

 Wato: Tues Jul 11 20:00 GMT 2000
 -- Removed firstRun variable (all firstrun should be done in the constructor)
 -- Removed all currentMode references (other than in constructor and setting modes)
 
 Seigers: Wed Jul 12 13:16:27 BST 2000
 -- Added one line of comment and then cried about my own stupidity at times... PAH!
 -- Then smiled after realising that this is now a release version!! Woo!!!!!!!!
 -- Oh and Mark I just realised... you re-badged your code in the RC2 directory but left the VERSION string as RC1!!! I'm nit picking because my code was crap and didn't do what it was supposed to.
 
 Seigers: Thu Jul 13 00:42:40 BST 2000
 -- Will upload the 0.02a Release today having finished the docs.
 -- Started work on 0.03a, the new features here are minimal - GUI enhancements, mainly me playing around learning the various API's. No harm in icing a cake though.
 -- First attempt at this gave an exe size of over 200K!!! Using more brain power I have cut it to 79K
 
 Seigers: Thu Jul 13 17:37:46 BST 2000
 -- Just graduated today!!! I now have a shiny certificate that says I can put BEng HONS after my name... I'm impressed if your not.
 -- Cut the compiled EXE file size again... now 63K Better than 200K!
 -- I now need a way to re-size the frame on the fly... humm... I could kludge it with a 'for' loop for now... let's try it as a proof of concept.
 -- Am now somewhat inebriated, the rest of today's code will probably be removed tomorrow.... ah well t'was a fun night (11:17)

 Seigers: Fri Jul 14 21:49:30 BST 2000
 -- Further to lastnights rather drunken exploits I managed to write one line and that comment before collapsing into bed... (don't try this at home kiddies! ;-) ).
 -- On with the real work!!!!!!
 Fri Jul 14 23:19:17 BST 2000 -- Later that day...
 -- IT WORKS!!!! I have now got the helper views into the program such that if you can't follow the Docs on what each radiobutton means the views should be self explanitory.
 -- There has been talk of moving this over to a new codebase at some stage to get around some problems and try and cut file sizes etc... this will not be happening soon.
 -- The reason is that I have been given a new mandate... create a replacement for ScreenPrefs for dualhead G400 cards (by Wato). Therefor I have a whole bunch of features to add!
 -- Final testing of this will be done tonight and a release should be due sometime on Saturday. 
 
 Seigers: Sat Jul 15 00:23:30 BST 2000
 -- Ok!! It's tested, picked up one bug, and squashed it under my all powerful heal!!
 -- Updating documents now... done!
 -- Expect 0.03 sometime later today (after I sleep etc...)
 -- Got horribly confused by the version numbering system... from now on:
 	-- Internal versions go up by letters.
 	-- Potential release version get RC status (Internal swapping between myself and Wato).
 	-- Release versions lose both the internal letters and RC number.
 -- Should stop a few future headaches.
 
 Rudolf Cornelissen: Thu Nov 10 2005
 -- Added Video TVout modes support,
 -- Added primary/secondary TVout switch option support,
 -- Numerous bugfixes (added asking driver for confirmation/denial of support for some options in some places),
 -- Fixed 'hanging occuring sometimes' problem (don't delete menu's as they might be in the process of being drawn),
 -- Probably added some bugs of my own as well ;-)
 */

#include "Window.h"
#include <TranslationUtils.h>



const rgb_color Gray = { 216, 216, 216, 255};
const char *VERSION = "0.04";
const char *RDATE = "11 Oct 2005";

DualHeadWindow::~DualHeadWindow()
{
	/*delete screenModes list*/
	if (screenModes)
		free(screenModes);
	if (screenModesList)
		free(screenModesList);
}

DualHeadWindow::DualHeadWindow(BRect frame)
				: BWindow(frame, "Dualhead Setup", B_TITLED_WINDOW,B_NOT_RESIZABLE )
{
	screenModes=NULL;
	frameState = false;
	//Get information on supported screenmodes
	screenInfo = new BScreen(this);
	if (!screenInfo->IsValid())
	{
		BAlert *invalidScreen;
		invalidScreen = new BAlert
		(
			"Invalid Screen", 
			"Failed to get screen information", 
			"Quit", 
			0,
			0,
			B_WIDTH_AS_USUAL, B_OFFSET_SPACING, B_WARNING_ALERT
		);
		invalidScreen->Go();
		be_app->PostMessage(B_QUIT_REQUESTED);
		return;
	}

	//Make copy of modes and free, because it is not mine to keep (Crashes if switch mode)
	display_mode * tempModeList;
	screenInfo->GetModeList(&tempModeList,&screenModeListCount);
	/* if the driver exports less modes than this app has internally, we need to allocate extra space.. */
	if (screenModeListCount < (DT_MODE_COUNT * 4))
	{
		screenModes=(display_mode *)malloc((DT_MODE_COUNT * 4)*sizeof(display_mode));
		screenModesList=(display_mode *)malloc((DT_MODE_COUNT * 4)*sizeof(display_mode));
	}
	else
	{
		screenModes=(display_mode *)malloc(screenModeListCount*sizeof(display_mode));
		screenModesList=(display_mode *)malloc(screenModeListCount*sizeof(display_mode));
	}
	for (unsigned int i=0;i<screenModeListCount;i++)
	{
		screenModes[i]=screenModesList[i]=tempModeList[i];
	}
	free(tempModeList);
	screenModeCount = screenModeListCount;

	//find what screenmode I am in
	/* the driver will have set/cleared the DUALHEAD_CAPABLE, TV_CAPABLE, TV_BITS and DUALHEAD_BITS
	 * bits before so we can just check for them */
	screenInfo->GetMode(&currentMode);
	/* select the modelist according to current set mode */
	switch (currentMode.flags & TVM_BITS)
	{
	case TVM_PAL:
		if (currentMode.flags & TV_VIDEO)
			tvMode = VID_TV_PAL;
		else
			tvMode = DESK_TV_PAL;
		break;
	case TVM_NTSC:
		if (currentMode.flags & TV_VIDEO)
			tvMode = VID_TV_NTSC;
		else
			tvMode = DESK_TV_NTSC;
		break;
	default:
		tvMode = TV_MONITOR;
		break;
	}
	if (currentMode.flags & TV_PRIMARY)
		tvHead = TV_PRIM;
	else
		tvHead = TV_SEC;

	//select the current mode (seems a good place to start!)
	//after this, current mode is only touched when one is set...
	selectedMode=currentMode;

	mainBar = new BMenuBar(BRect(0,0,0,0),"Main MenuBar");
	BMenu *fileMenu = BuildFileMenu();
	mainBar->AddItem(fileMenu);
	tvMenu = BuildTVMenu();
	mainBar->AddItem(tvMenu);
	tvheadMenu = BuildTVheadMenu();
	mainBar->AddItem(tvheadMenu);
	AddChild(mainBar);
	UpdateTVMenu();
	UpdateTVheadMenu();

	//create the config view
	configView = new BBox
	(
		*(new BRect((-1+139),20,(241+139),100)), 
		"config view", 
		B_FOLLOW_LEFT|B_FOLLOW_TOP,
		B_WILL_DRAW|B_NAVIGABLE,
		B_FANCY_BORDER
	);
	AddChild(configView);
	
	//Create the helper views... this is the cool bit!!
	rightView = new BBox
	(
		*(new BRect(0,20,139,145)),
		"rightView",
		B_FOLLOW_LEFT|B_FOLLOW_TOP,
		B_WILL_DRAW|B_NAVIGABLE,
		B_FANCY_BORDER
	);
	AddChild(rightView);
	leftView = new BBox
	(
		*(new BRect(380,20,519,145)),
		"leftView",
		B_FOLLOW_LEFT|B_FOLLOW_TOP,
		B_WILL_DRAW|B_NAVIGABLE,
		B_FANCY_BORDER
	);
	//Load the bitmaps for display in helper views...
	empire = GetBitmap("empire6.jpg");
	rebel = GetBitmap("rebel6.jpg");
	combined = GetBitmap("combined6.jpg");
	//Display the righthand one... this one never goes away... the left one though.... ;-)
	rightView->SetViewBitmap(combined);

	//create the activate button view
	BBox * activateView = new BBox
	(
		*(new BRect((0+139),100,(242+139),145)), 
		"activate view", 
		B_FOLLOW_LEFT|B_FOLLOW_TOP,
		B_WILL_DRAW|B_NAVIGABLE,
		B_FANCY_BORDER
	);
	AddChild(activateView);
	
	//create the activate buttons
	BButton * testButton = new BButton
	(
		*(new BRect(25,10,75,30)),
		"test button",
		"test",
		new BMessage('TEST')	
	);
	BButton * useButton = new BButton
	(
		*(new BRect(95,10,145,30)),
		"use button",
		"use",
		new BMessage('USE')
	);
	BButton * saveButton = new BButton
	(
		*(new BRect(165,10,215,30)),
		"save button",
		"save",
		new BMessage('SAVE')
	);	
	activateView->AddChild(testButton);
	activateView->AddChild(useButton);
	activateView->AddChild(saveButton);
		
	//create a few radio buttons for dualhead
	multiHeadButton[0] = new BRadioButton
	(
		*(new BRect(150,3,230,8)),
		"Single Head", 
		"Single Head",
		new BMessage('SING'),
		B_FOLLOW_LEFT | B_FOLLOW_TOP,
		B_WILL_DRAW | B_NAVIGABLE
	);
	multiHeadButton[1] = new BRadioButton
	(
		*(new BRect(150,21,230,26)),
		"Clone Head", 
		"Clone Head",
		new BMessage('CLON'),
		B_FOLLOW_LEFT | B_FOLLOW_TOP,
		B_WILL_DRAW | B_NAVIGABLE
	);
	multiHeadButton[2] = new BRadioButton
	(
		*(new BRect(150,39,230,44)),
		"Dual Head", 
		"Dual Head",
		new BMessage('DUAL'),
		B_FOLLOW_LEFT | B_FOLLOW_TOP,
		B_WILL_DRAW | B_NAVIGABLE
	);
	multiHeadButton[3] = new BRadioButton
	(
		*(new BRect(150,57,230,62)),
		"Switch Head", 
		"Switch Head",
		new BMessage('SWIT'),
		B_FOLLOW_LEFT | B_FOLLOW_TOP,
		B_WILL_DRAW | B_NAVIGABLE
	);

	//Add the radio buttons on the first run, no need to repeat everytime
	configView->AddChild(multiHeadButton[0]);
	configView->AddChild(multiHeadButton[1]);
	configView->AddChild(multiHeadButton[2]);
	configView->AddChild(multiHeadButton[3]);

	/* create new modelist for selected output device, and select mode from new list */
	setModeList();
	//create a few menu items
	CreateMenus();
	CreateRadio();
}

//Lets have some fame and fortune eh... time for an about box!
BMenu* DualHeadWindow::BuildFileMenu(void) const
{
	BMenu *fileMenu = new BMenu("File");
	
	BMenuItem* AboutItem = new BMenuItem("About", new BMessage('ABUT'));
	fileMenu->AddItem(AboutItem);

	//Go on then... lets 'ave a close item too... 
	fileMenu->AddSeparatorItem();
	fileMenu->AddItem(new BMenuItem("Close", new BMessage(B_QUIT_REQUESTED)));

	return fileMenu;
}

BMenu* DualHeadWindow::BuildTVMenu(void) const
{
	//Temporary TVout solution
	BMenu * tmpMenu = new BMenu("Output");
	tmpMenu->SetRadioMode(true);
	BMenuItem * tempItem1 = new BMenuItem("Monitor", new BMessage('MONI'));
	BMenuItem * tempItem2 = new BMenuItem("Desktop TV (PAL)", new BMessage('DPAL'));
	BMenuItem * tempItem3 = new BMenuItem("Desktop TV (NTSC)", new BMessage('DNTC'));
	BMenuItem * tempItem4 = new BMenuItem("Video TV (PAL)", new BMessage('VPAL'));
	BMenuItem * tempItem5 = new BMenuItem("Video TV (NTSC)", new BMessage('VNTC'));
	tmpMenu->AddItem(tempItem1);
	tmpMenu->AddItem(tempItem2);
	tmpMenu->AddItem(tempItem3);
	tmpMenu->AddItem(tempItem4);
	tmpMenu->AddItem(tempItem5);

	/* select mode */
	switch (tvMode)
	{
	case DESK_TV_PAL:
		tempItem2->SetMarked(true);
		break;
	case DESK_TV_NTSC:
		tempItem3->SetMarked(true);
		break;
	case VID_TV_PAL:
		tempItem4->SetMarked(true);
		break;
	case VID_TV_NTSC:
		tempItem5->SetMarked(true);
		break;
	default:
		tempItem1->SetMarked(true);
		break;
	}

	return tmpMenu;
}

void DualHeadWindow::UpdateTVMenu()
{
	bool prim_vid_cap = false;
	bool sec_vid_cap = false;

	/* ask the driver for Desktop TVout capability (Matrox G450 and G550 can't do that) */
	display_mode tmp = dt_mode_list[0]; /* 640x480 is supported by all VGA screens outthere.. (otherwise could miss from list!) */
	/* poke space supported on all cards (Matrox!) */
	tmp.space = B_RGB32_LITTLE;
	/* ask explicitly for a TVout mode in Desktop mode on the secondary head in a dualhead mode */
	/* (select dualhead clone mode, in NTSC TVout mode) */
	tmp.flags &= ~(DUALHEAD_BITS | TVM_BITS);
	tmp.flags |= (DUALHEAD_CLONE | TVM_NTSC); /* PAL 640x480 could be done without flickerfilter though, hence NTSC here! */
	/* (secondary head, desktop mode) */
	tmp.flags &= ~(TV_PRIMARY | TV_VIDEO);
	screenInfo->ProposeMode(&tmp,&tmp,&tmp);
	if (!(tmp.flags & TV_CAPABLE))
	{
		/* can't do Desktop TVout: so block these menu items */
		if ((tvMode == DESK_TV_PAL) || (tvMode == DESK_TV_NTSC))
		{
			/* we were in an 'illegal mode', so switch to always-valid monitor-only mode */
			tvMode = TV_MONITOR;
			tvMenu->ItemAt(0)->SetMarked(true);
			/* preselect the upper mode (640x480x32x60Hz) from the monitor-only list */
			selectedMode=screenModesList[0];

		}
		tvMenu->ItemAt(1)->SetEnabled(false);
		tvMenu->ItemAt(2)->SetEnabled(false);
	}


	/* ask the driver for 4:3 aspect Video TVout capability: if this can't be done
	 * the card cant' do TVout at all */

	/* SECONDARY HEAD */
	tmp = vtn_mode_list[0]; /* 640x480 is supported by all VGA screens outthere.. (otherwise could miss from list!) */
	/* poke space supported on all cards (Matrox!) */
	tmp.space = B_RGB32_LITTLE;
	/* ask explicitly for a TVout mode in Video mode on the secondary head in a dualhead mode */
	/* (select dualhead clone mode, in NTSC TVout mode) */
	tmp.flags &= ~(DUALHEAD_BITS | TVM_BITS);
	tmp.flags |= (DUALHEAD_CLONE | TVM_NTSC);
	/* (secondary head, video mode) */
	tmp.flags &= ~TV_PRIMARY;
	tmp.flags |= TV_VIDEO;
	screenInfo->ProposeMode(&tmp,&tmp,&tmp);
	if (tmp.flags & TV_CAPABLE)
		sec_vid_cap = true;

	/* PRIMARY HEAD */
	tmp = vtn_mode_list[0]; /* 640x480 is supported by all VGA screens outthere.. (otherwise could miss from list!) */
	/* poke space supported on all cards (Matrox!) */
	tmp.space = B_RGB32_LITTLE;
	/* ask explicitly for a TVout mode in Video mode on the primary head in a singlehead mode */
	/* (select singlehead mode, in NTSC TVout mode) */
	tmp.flags &= ~(DUALHEAD_BITS | TVM_BITS);
	tmp.flags |= (DUALHEAD_OFF | TVM_NTSC);
	/* (primary head, video mode) */
	tmp.flags |= (TV_PRIMARY | TV_VIDEO);
	screenInfo->ProposeMode(&tmp,&tmp,&tmp);
	if (tmp.flags & TV_CAPABLE)
		prim_vid_cap = true;

	if (!prim_vid_cap && !sec_vid_cap)
	{
		/* can't do TVout: so remove menu alltogether */
		if (tvMode != TV_MONITOR)
		{
			/* we were in an 'illegal mode', so switch to always-valid monitor-only mode */
			tvMode = TV_MONITOR;
			tvMenu->ItemAt(0)->SetMarked(true);
			/* preselect the upper mode (640x480x32x60Hz) from the monitor-only list */
			selectedMode=screenModesList[0];

		}
		tvMenu->ItemAt(1)->SetEnabled(false);
		tvMenu->ItemAt(2)->SetEnabled(false);
		tvMenu->ItemAt(3)->SetEnabled(false);
		tvMenu->ItemAt(4)->SetEnabled(false);
	}
}

BMenu* DualHeadWindow::BuildTVheadMenu(void) const
{
	//Temporary TVout solution
	BMenu * tmpMenu = new BMenu("TV head");
	tmpMenu->SetRadioMode(true);
	BMenuItem * tempItem1 = new BMenuItem("Primary", new BMessage('PRIM'));
	BMenuItem * tempItem2 = new BMenuItem("Secondary", new BMessage('SEC'));
	tmpMenu->AddItem(tempItem1);
	tmpMenu->AddItem(tempItem2);

	/* select mode */
	if (tvHead == TV_PRIM)
		tempItem1->SetMarked(true);
	else
		tempItem2->SetMarked(true);
	
	return tmpMenu;
}

void DualHeadWindow::UpdateTVheadMenu()
{
	if (tvMode == TV_MONITOR)
	{
		if (mainBar->FindItem("TV head"))
			mainBar->RemoveItem(tvheadMenu);
		/* reset this mode.flag for max non-custom drivers compatibility */
		tvHead = TV_SEC;
	}
	else
	{
		if (!mainBar->FindItem("TV head"))
			mainBar->AddItem(tvheadMenu);	
		if (!(selectedMode.flags & DUALHEAD_BITS))
		{
			/* ask the driver for singlehead TVout capability (Matrox G450 and G550 can't do that) */
			display_mode tmp = selectedMode;
			/* ask explicitly for a TVout mode... */
			CheckMode(&tmp);
			/* ... on the secondary head (in a singlehead mode) */
			tmp.flags &= ~TV_PRIMARY;
			screenInfo->ProposeMode(&tmp,&tmp,&tmp);
			if (tmp.flags & TV_PRIMARY)
			{
				/* can do singlehead TVout: so set the only valid choice */
				tvHead = TV_PRIM;
				tvheadMenu->ItemAt(0)->SetMarked(true);
				tvheadMenu->SetEnabled(false);
			}
			else
			{
				/* can't do singlehead TVout: grey out menu and indicate secondary TVout */
				tvHead = TV_SEC;
				tvheadMenu->ItemAt(1)->SetMarked(true);
				tvheadMenu->SetEnabled(false);
			}
		}
		else
		{
			/* (ask the driver for 4:3 aspect Video TVout capability: if this can't be done
			 * the card can't do TVout at all) */
			display_mode tmp = vtn_mode_list[0]; /* 640x480 is supported by all VGA screens outthere.. (otherwise could miss from list!) */
			/* poke space supported on all cards (Matrox!) */
			tmp.space = B_RGB32_LITTLE;
			/* ask explicitly for a TVout mode in Video mode on the primary head in a dualhead mode */
			/* (select dualhead mode, in NTSC TVout mode) */
			tmp.flags &= ~(DUALHEAD_BITS | TVM_BITS);
			tmp.flags |= (DUALHEAD_CLONE | TVM_NTSC);
			/* (primary head, video mode) */
			tmp.flags |= (TV_PRIMARY | TV_VIDEO);
			screenInfo->ProposeMode(&tmp,&tmp,&tmp);
			if (tmp.flags & TV_PRIMARY)
			{
				tvheadMenu->SetEnabled(true);
			}
			else
			{
				/* Matrox G450/G550 cannot do dualhead modes with primary TVout:
				 * grey out menu and indicate secondary TVout */
				tvHead = TV_SEC;
				tvheadMenu->ItemAt(1)->SetMarked(true);
				tvheadMenu->SetEnabled(false);
			}
		}
	}
}

//Bit nicer on the HCI front... also allows easy expansion for cards that allow
//some but not all of the possible modes (not sure if needed but there anyway).
void DualHeadWindow::CreateRadio()
{
	static bool first_run = true;

	if (selectedMode.flags & DUALHEAD_CAPABLE)
	{
		multiHeadButton[1]->SetEnabled(true);
		multiHeadButton[2]->SetEnabled(true);
		multiHeadButton[3]->SetEnabled(true);
		/* select dualhead mode */
		multiHeadButton[(selectedMode.flags&DUALHEAD_BITS)>>6]->SetValue(1);
		if (first_run)
		{
			//GAAA!!! I hate this way of doing it... I'll change this later... assuming there is a better way.
			switch (selectedMode.flags & DUALHEAD_BITS)
			{
			case DUALHEAD_OFF:
				BLooper::PostMessage(new BMessage('SING'));
				break;
			case DUALHEAD_CLONE:
				BLooper::PostMessage(new BMessage('CLON'));
				break;
			case DUALHEAD_ON:
				BLooper::PostMessage(new BMessage('DUAL'));
				break;
			case DUALHEAD_SWITCH:
				BLooper::PostMessage(new BMessage('SWIT'));
				break;
			}
		}
	}
	else
	{
		multiHeadButton[0]->SetValue(1); 
		multiHeadButton[1]->SetEnabled(false);
		multiHeadButton[2]->SetEnabled(false);
		multiHeadButton[3]->SetEnabled(false);
		//GAAA!!! I hate this way of doing it... I'll change this later... assuming there is a better way.
		BLooper::PostMessage(new BMessage('SING'));
	}

	first_run = false;
}

//Ok... made these popup selectors a LOT better! Also added info on what they were for (for idiots).
//Also note I broke this function up a bit to understand each part better.
//Though it was my intention to do away with having to remove and repaint each popup component I have found that
//due to a deficiency in the API there is no easy way to 'SetSelectedItem', so I have had to stick with the old method.
void DualHeadWindow::CreateMenus()
{
	/* fill strings resolution, refresh and depth according to selected mode */
	CalcModeInfo(&selectedMode);
	
	//Create the Popup menus with these strings and add them to a MenuField for labelling.
	//Then add the MenuField to the configView to get it displayed.
	resolutionPopup = new BPopUpMenu(resolution, true, true, B_ITEMS_IN_COLUMN);
	resSelector = new BMenuField(*(new BRect(10,5,150,5)), "Resolution", "Resolution:", resolutionPopup, B_FOLLOW_LEFT|B_FOLLOW_TOP, B_WILL_DRAW);
	//Split the BRect unequally in order to give the labels more/less room... useful!
	resSelector->SetDivider(resSelector->Divider() - 15);
	resSelector->SetViewColor(Gray);
	configView->AddChild(resSelector);
	
	refreshPopup = new BPopUpMenu(refresh, true, true, B_ITEMS_IN_COLUMN);
	refSelector = new BMenuField(*(new BRect(10,30,150,30)), "Refresh", "Refresh:", refreshPopup, B_FOLLOW_LEFT|B_FOLLOW_TOP, B_WILL_DRAW);
	refSelector->SetDivider(refSelector->Divider() - 15);
	refSelector->SetViewColor(Gray);
	configView->AddChild(refSelector);
	
	depthPopup = new BPopUpMenu(depth, true, true, B_ITEMS_IN_COLUMN);
	depSelector = new BMenuField(*(new BRect(10,55,150,55)), "Depth", "Depth:", depthPopup, B_FOLLOW_LEFT, B_WILL_DRAW);
	depSelector->SetDivider(depSelector->Divider() - 15);
	depSelector->SetViewColor(Gray);
	configView->AddChild(depSelector);

	/* if the active mode is unknown to us, come up with a mode that we know! (preventing trouble...) */
	findFallback();

	//Fill each of these Popup menus with the resolution data for the user to choose from...
	fillMenus();

	/* 'check' current active mode in list */
	CalcModeInfo(&selectedMode);
	resolutionPopup->FindItem(resolution)->SetMarked(true);
	refreshPopup->FindItem(refresh)->SetMarked(true);
	depthPopup->FindItem(depth)->SetMarked(true);

	return;
}

void DualHeadWindow::findFallback()
{
	bool resFound = false, refFound = false, depthFound = false;
	bool resIndexFound = false, refIndexFound = false;
	uint16 resIndex = 0, refIndex = 0;

	/* scan our 'known' modelist for mode */
	for (uint16 i = 0; i < screenModeCount; i++)
	{
		if
		(
			(selectedMode.timing.h_display == screenModes[i].timing.h_display) &&
			(selectedMode.timing.v_display == screenModes[i].timing.v_display)
		)
		{
			resFound = true;
			if (!resIndexFound)
			{
				resIndex = i;
				resIndexFound = true;
			}
		}

		if
		(
			(selectedMode.timing.h_display == screenModes[i].timing.h_display) &&
			(selectedMode.timing.v_display == screenModes[i].timing.v_display) &&
			(selectedMode.timing.pixel_clock == screenModes[i].timing.pixel_clock) &&
			(selectedMode.timing.h_total == screenModes[i].timing.h_total) &&
			(selectedMode.timing.v_total == screenModes[i].timing.v_total)
		)
		{
			refFound = true;
			if (!refIndexFound)
			{
				refIndex = i;
				refIndexFound = true;
			}
		}

		if
		(
			(selectedMode.timing.h_display == screenModes[i].timing.h_display) &&
			(selectedMode.timing.v_display == screenModes[i].timing.v_display) &&
			(selectedMode.timing.pixel_clock == screenModes[i].timing.pixel_clock) &&
			(selectedMode.timing.h_total == screenModes[i].timing.h_total) &&
			(selectedMode.timing.v_total == screenModes[i].timing.v_total) &&
			(selectedMode.space == screenModes[i].space)
		)
		{
			depthFound = true;
		}
	}

	/* if resolution not known, fallback to first mode in our list.
	 * (has lowest 'known' resolution) */
	if (!resFound)
	{
		selectedMode = screenModes[0];
		return;
	}

	/* if refresh for mode with known res not known, fallback to first same res mode in our list.
	 * (has lowest 'known' refresh) */
	if (!refFound)
	{
		selectedMode = screenModes[resIndex];
		return;
	}

	/* if depth for known mode not known, fallback to same res and refresh mode in our list.
	 * (has highest 'known' depth for that mode) */
	if (!depthFound)
	{
		selectedMode = screenModes[refIndex];
		return;
	}
}

void DualHeadWindow::setModeList()
{
	status_t result = B_OK;
	color_space spaces[4] = {B_RGB32_LITTLE,B_RGB16_LITTLE,B_RGB15_LITTLE,B_CMAP8};

	switch (tvMode)
	{
	case DESK_TV_PAL:
		{
			uint16 z = 0;
			screenModeCount = DT_MODE_COUNT;
			for (unsigned int i=0;i<screenModeCount;i++)
			{
				/* do it once for each depth we want to support */
				for (uint8 j = 0; j < (sizeof(spaces) / sizeof(color_space)); j++) 
				{
					screenModes[z]=dt_mode_list[i];
					screenModes[z].flags &= ~TVM_BITS;
					screenModes[z].flags |= TVM_PAL;
					screenModes[z].flags &= ~TV_VIDEO;
					/* poke the specific space */
					screenModes[z].space = spaces[j];
					result = screenInfo->ProposeMode(&(screenModes[z]),&(screenModes[z]),&(screenModes[z]));
					if ((result != B_ERROR) && (screenModes[z].flags & TV_CAPABLE)) z++;
				}
			}
			screenModeCount = z;
		}
		break;
	case DESK_TV_NTSC:
		{
			uint16 z = 0;
			screenModeCount = DT_MODE_COUNT;
			for (unsigned int i=0;i<screenModeCount;i++)
			{
				/* do it once for each depth we want to support */
				for (uint8 j = 0; j < (sizeof(spaces) / sizeof(color_space)); j++) 
				{
					screenModes[z]=dt_mode_list[i];
					screenModes[z].flags &= ~TVM_BITS;
					screenModes[z].flags |= TVM_NTSC;
					screenModes[z].flags &= ~TV_VIDEO;
					/* poke the specific space */
					screenModes[z].space = spaces[j];
					result = screenInfo->ProposeMode(&(screenModes[z]),&(screenModes[z]),&(screenModes[z]));
					if ((result != B_ERROR) && (screenModes[z].flags & TV_CAPABLE)) z++;
				}
			}
			screenModeCount = z;
		}
		break;
	case VID_TV_PAL:
		{
			uint16 z = 0;
			screenModeCount = VTP_MODE_COUNT;
			for (unsigned int i=0;i<screenModeCount;i++)
			{
				/* do it once for each depth we want to support */
				for (uint8 j = 0; j < (sizeof(spaces) / sizeof(color_space)); j++) 
				{
					screenModes[z]=vtp_mode_list[i];
					screenModes[z].flags &= ~TVM_BITS;
					screenModes[z].flags |= TVM_PAL;
					screenModes[z].flags |= TV_VIDEO;
					/* poke the specific space */
					screenModes[z].space = spaces[j];
					result = screenInfo->ProposeMode(&(screenModes[z]),&(screenModes[z]),&(screenModes[z]));
					if ((result != B_ERROR) && (screenModes[z].flags & TV_CAPABLE)) z++;
				}
			}
			screenModeCount = z;
		}
		break;
	case VID_TV_NTSC:
		{
			uint16 z = 0;
			screenModeCount = VTN_MODE_COUNT;
			for (unsigned int i=0;i<screenModeCount;i++)
			{
				/* do it once for each depth we want to support */
				for (uint8 j = 0; j < (sizeof(spaces) / sizeof(color_space)); j++) 
				{
					screenModes[z]=vtn_mode_list[i];
					screenModes[z].flags &= ~TVM_BITS;
					screenModes[z].flags |= TVM_NTSC;
					screenModes[z].flags |= TV_VIDEO;
					/* poke the specific space */
					screenModes[z].space = spaces[j];
					result = screenInfo->ProposeMode(&(screenModes[z]),&(screenModes[z]),&(screenModes[z]));
					if ((result != B_ERROR) && (screenModes[z].flags & TV_CAPABLE)) z++;
				}
			}
			screenModeCount = z;
		}
		break;
	default:
		screenModeCount = screenModeListCount;
		for (unsigned int i=0;i<screenModeCount;i++)
		{
			screenModes[i]=screenModesList[i];
		}
		break;
	}

	/* on startup keep the already preselected current mode */
	static bool startup = true;
	if (startup)
	{
		startup = false;
	}
	else
	{
		selectedMode=screenModes[0];
	}
}

//Broken off from the above function for seperation of the GUI code from functionality code.
void DualHeadWindow::fillMenus()
{
	/* used for tracking items in the lists for the purpose of 'checking' them in msg-rx'd */
	uint8 resItemNr = 0, refItemNr = 0, depthItemNr = 0;

	/* make sure lists are empty */
	resolutionPopup->RemoveItems(0, resolutionPopup->CountItems(), true);
	refreshPopup->RemoveItems(0, refreshPopup->CountItems(), true);
	depthPopup->RemoveItems(0, depthPopup->CountItems(), true);

	//Create all menu items
	for (uint32 i=0;i<screenModeCount;i++)
	{
		/* first fill strings resolution, refresh and depth according to mode being processed */
		CalcModeInfo(&screenModes[i]);

		//Add resolution if it does not already exist
		if (resolutionPopup->FindItem(resolution)==NULL)
		{
			BMenuItem * resolutionItem = new BMenuItem
			(
				resolution,
				new BMessage((resItemNr++ << 24) | (RS << 16) | i),
				0,
				0
			);
			resolutionPopup->AddItem(resolutionItem);
		}
	
		//Add menu item if (valid for resolution and does not already exist) 
		if 
		(
			(selectedMode.timing.h_display==screenModes[i].timing.h_display) &&
			(selectedMode.timing.v_display==screenModes[i].timing.v_display) && 
			(refreshPopup->FindItem(refresh)==NULL)
		)
		{
			BMenuItem * refreshItem = new BMenuItem
			(
				refresh,
				new BMessage((refItemNr++ << 24) | (RF << 16) | i),
				0,
				0
			);
			refreshPopup->AddItem(refreshItem);
		}

		//Add menu item if (valid for resolution and refresh and does not already exist) 
		if 
		(
			(selectedMode.timing.h_display==screenModes[i].timing.h_display) &&
			(selectedMode.timing.v_display==screenModes[i].timing.v_display) && 
			(selectedMode.timing.pixel_clock==screenModes[i].timing.pixel_clock) &&
			(selectedMode.timing.h_total==screenModes[i].timing.h_total) &&
			(selectedMode.timing.v_total==screenModes[i].timing.v_total) && 
			(depthPopup->FindItem(depth)==NULL)
		)
		{
			BMenuItem * depthItem = new BMenuItem
			(
				depth,
				new BMessage((depthItemNr++ << 24) | (DE << 16) | i),
				0,
				0
			);
			depthPopup->AddItem(depthItem);
		}
	}

	return;
}

/* resolution, refresh and depth are strings which are set according to display_mode relayed here */
void DualHeadWindow::CalcModeInfo(display_mode * dm)
{
	sprintf(resolution,"%dx%d",dm->timing.h_display,dm->timing.v_display); 
	sprintf(refresh,"%.1f Hz",(dm->timing.pixel_clock*1000)/(float)(dm->timing.v_total*dm->timing.h_total));
	switch(dm->space)
	{
		case B_CMAP8:
			sprintf(depth,"8  Bits/Pixel");
			break;
		case B_RGB15_LITTLE:
			sprintf(depth,"15 Bits/Pixel");
			break;
		case B_RGB16_LITTLE:
			sprintf(depth,"16 Bits/Pixel");
			break;
		case B_RGB32_LITTLE:
			sprintf(depth,"32 Bits/Pixel");
			break;	
		default:
			sprintf(depth,"????");
			break;
	}
}

bool DualHeadWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return(true);
}

void DualHeadWindow::MessageReceived(BMessage* message)
{	
	//check if it is a listbox update code
	uint16 matching_mode = (message->what) & 0x0000ffff;
	uint8 item_list_nr = (message->what) >> 24;
	switch(((message->what) >> 16) & 0x00ff)
	{
		case RS: /*resolution*/
			selectedMode.timing=screenModes[matching_mode].timing;
			//Make sure we get a correct virtual screen... don't want the mouse going off the bottom of the screen.
			selectedMode.virtual_width=screenModes[matching_mode].virtual_width;
			selectedMode.virtual_height=screenModes[matching_mode].virtual_height;
			selectedMode.h_display_start=screenModes[matching_mode].h_display_start;
			selectedMode.v_display_start=screenModes[matching_mode].v_display_start;
			selectedMode.flags&=~DUALHEAD_CAPABLE;
			selectedMode.flags|=screenModes[matching_mode].flags&DUALHEAD_CAPABLE;
			/* update refresh and depth menu plus reset their selectors */
			fillMenus();
			resolutionPopup->ItemAt(item_list_nr)->SetMarked(true);
			refreshPopup->ItemAt(0)->SetMarked(true);
			depthPopup->ItemAt(0)->SetMarked(true);
			/* update dualhead selection buttons */
			CreateRadio();
			break;
		case RF: /*refresh*/
			selectedMode.timing=screenModes[matching_mode].timing;
			selectedMode.flags&=~DUALHEAD_CAPABLE;
			selectedMode.flags|=screenModes[matching_mode].flags&DUALHEAD_CAPABLE;
			/* update depth menu plus reset it's selector */
			fillMenus();
			refreshPopup->ItemAt(item_list_nr)->SetMarked(true);
			depthPopup->ItemAt(0)->SetMarked(true);
			/* update dualhead selection buttons */
			CreateRadio();
			break;
		case DE: /*depth*/
			selectedMode.space=screenModes[matching_mode].space;
			/* ask the driver for dualhead capability of this mode: this can't be done via the menu's depth items! */
			display_mode tmp = selectedMode;
			CheckMode(&tmp);
			screenInfo->ProposeMode(&tmp,&tmp,&tmp);
			selectedMode.flags&=~DUALHEAD_CAPABLE;
			selectedMode.flags|= ((tmp.flags) & DUALHEAD_CAPABLE);
			depthPopup->ItemAt(item_list_nr)->SetMarked(true);
			/* update dualhead selection buttons */
			CreateRadio();
			break;
		default:   /*if not, use standard switch*/
			switch(message->what)
			{
				case 'SING':
					selectedMode.flags&=~DUALHEAD_BITS;
					selectedMode.flags|=DUALHEAD_OFF;
					if(frameState)
					{
						//Shouldn't need to delete it, as it's not going anywhere!
						rightView->RemoveSelf();
						AddChild(rightView);
						rightView->SetViewBitmap(combined);

						snooze(1000);
						for(int i=0;i<138;i++)
						{
							ResizeBy(-1,0);
							snooze(1000);
						}
						leftView->RemoveSelf();
						frameState=false;
					}						
					UpdateTVheadMenu();
					break;
				case 'CLON':					
					selectedMode.flags&=~DUALHEAD_BITS;
					selectedMode.flags|=DUALHEAD_CLONE;
					if(!frameState)
					{
						//Shouldn't need to delete it, as it's not going anywhere!
						rightView->RemoveSelf();
						AddChild(rightView);
						AddChild(leftView);
						rightView->SetViewBitmap(rebel);
						leftView->SetViewBitmap(rebel);

						snooze(1000);
						for(int i=0;i<138;i++)
						{
							ResizeBy(1,0);
							snooze(1000);
						}
						frameState=true;
					}else{
						leftView->RemoveSelf();
						AddChild(leftView);
						leftView->SetViewBitmap(rebel);
						rightView->RemoveSelf();
						AddChild(rightView);
						rightView->SetViewBitmap(rebel);
						//snooze(10);
					}
					UpdateTVheadMenu();
					break;
				case 'DUAL':
					selectedMode.flags&=~DUALHEAD_BITS;
					selectedMode.flags|=DUALHEAD_ON;
					if(!frameState)
					{
						//Shouldn't need to delete it, as it's not going anywhere!
						rightView->RemoveSelf();
						AddChild(rightView);
						AddChild(leftView);
						rightView->SetViewBitmap(rebel);
						leftView->SetViewBitmap(empire);
						
						snooze(1000);
						for(int i=0;i<138;i++)
						{
							ResizeBy(1,0);
							snooze(1000);
						}
						frameState=true;
					}else{
						leftView->RemoveSelf();
						AddChild(leftView);
						leftView->SetViewBitmap(empire);
						rightView->RemoveSelf();
						AddChild(rightView);
						rightView->SetViewBitmap(rebel);
						//snooze(10);
					}
					UpdateTVheadMenu();
					break;
				case 'SWIT':
					selectedMode.flags&=~DUALHEAD_BITS;
					selectedMode.flags|=DUALHEAD_SWITCH;
					if(!frameState)
					{
						//Shouldn't need to delete it, as it's not going anywhere!
						rightView->RemoveSelf();
						AddChild(rightView);
						AddChild(leftView);
						rightView->SetViewBitmap(empire);
						leftView->SetViewBitmap(rebel);
						
						snooze(1000);
						for(int i=0;i<138;i++)
						{
							ResizeBy(1,0);
							snooze(1000);
						}
						frameState=true;
					}else{
						leftView->RemoveSelf();
						AddChild(leftView);
						leftView->SetViewBitmap(rebel);
						rightView->RemoveSelf();
						AddChild(rightView);
						rightView->SetViewBitmap(empire);
						//snooze(10);
					}
					UpdateTVheadMenu();
					break;
				case 'TEST':
					BAlert *testScreen;
					testScreen = new BAlert
					(
						"Test Screen", 
						"Current settings will be restored in 5 seconds", 
						"OOPS", 
						"OK",
						0,
						B_WIDTH_AS_USUAL, B_OFFSET_SPACING, B_WARNING_ALERT
					);
					
					CheckMode(&selectedMode);
					
					if (1==testScreen->Go())
					{
						screenInfo->SetMode(&selectedMode,false);
						snooze(5000000);			
						screenInfo->SetMode(&currentMode,false);
					};
					break;
				case 'USE':
					BAlert *useScreen;
					useScreen = new BAlert
					(
						"Use Screen", 
						"Use screen temporarily?", 
						"Yes", 
						"No",
						0,
						B_WIDTH_AS_USUAL, B_OFFSET_SPACING, B_WARNING_ALERT
					);
					
					CheckMode(&selectedMode);

					if (0==useScreen->Go())
					{
						screenInfo->SetMode(&selectedMode,false);
						currentMode=selectedMode;
					}
					break;
				case 'SAVE':
					BAlert *saveScreen;
					saveScreen = new BAlert
					(
						"Save Screen", 
						"Use screen permanently?", 
						"Yes", 
						"No",
						0,
						B_WIDTH_AS_USUAL, B_OFFSET_SPACING, B_WARNING_ALERT
					);
					
					CheckMode(&selectedMode);
					
					if (0==saveScreen->Go())
					{
						screenInfo->SetMode(&selectedMode,true);
						currentMode=selectedMode;
					}	
					break;
				case 'ABUT':
					AboutRequested();
					break;
				case 'MONI':
					tvMode = TV_MONITOR;
					/* create new modelist for selected output device, and select mode from new list */
					setModeList();
					UpdateTVheadMenu();
					fillMenus();
					resolutionPopup->ItemAt(0)->SetMarked(true);
					refreshPopup->ItemAt(0)->SetMarked(true);
					depthPopup->ItemAt(0)->SetMarked(true);
					CreateRadio();
					break;
				case 'DPAL':
					tvMode = DESK_TV_PAL;
					/* create new modelist for selected output device, and select mode from new list */
					setModeList();
					UpdateTVheadMenu();
					fillMenus();
					resolutionPopup->ItemAt(0)->SetMarked(true);
					refreshPopup->ItemAt(0)->SetMarked(true);
					depthPopup->ItemAt(0)->SetMarked(true);
					CreateRadio();
					break;
				case 'DNTC':
					tvMode = DESK_TV_NTSC;
					/* create new modelist for selected output device, and select mode from new list */
					setModeList();
					UpdateTVheadMenu();
					fillMenus();
					resolutionPopup->ItemAt(0)->SetMarked(true);
					refreshPopup->ItemAt(0)->SetMarked(true);
					depthPopup->ItemAt(0)->SetMarked(true);
					CreateRadio();
					break;
				case 'VPAL':
					tvMode = VID_TV_PAL;
					/* create new modelist for selected output device, and select mode from new list */
					setModeList();
					UpdateTVheadMenu();
					fillMenus();
					resolutionPopup->ItemAt(0)->SetMarked(true);
					refreshPopup->ItemAt(0)->SetMarked(true);
					depthPopup->ItemAt(0)->SetMarked(true);
					CreateRadio();
					break;
				case 'VNTC':
					tvMode = VID_TV_NTSC;
					/* create new modelist for selected output device, and select mode from new list */
					setModeList();
					UpdateTVheadMenu();
					fillMenus();
					resolutionPopup->ItemAt(0)->SetMarked(true);
					refreshPopup->ItemAt(0)->SetMarked(true);
					depthPopup->ItemAt(0)->SetMarked(true);
					CreateRadio();
					break;
				case 'PRIM':
					tvHead = TV_PRIM;
					break;
				case 'SEC':
					tvHead = TV_SEC;
					break;
				default:
					BWindow::MessageReceived(message);
			}
	}
}

void DualHeadWindow::AboutRequested()
{
    sprintf(info, 
    	"Matrox/nVidia Dualhead Setup program.\n\n"
    	"Created By FoFTDesign\n\n"
    	"Primary Code: Mark 'Wato' Watson\n"
    	"Re-write\\bug fixes: Chris 'Seigers' Haggan\n"
    	"Extensions\\bug fixes: Rudolf Cornelissen\n\n"
    	"Current version: %s - %s\n\n"
    	"For comments\\bug reports please E-Mail Rudolf:\n"
    	"info.be-hold@inter.nl.net", VERSION, RDATE);
	BAlert* aboutBox = new BAlert("DualHead Setup Program", info, "Cool!");
	aboutBox->Go(); 
}

void DualHeadWindow::CheckMode(display_mode * Mode)
{
	if (!(Mode->flags&DUALHEAD_CAPABLE))
	{
		Mode->flags&=~DUALHEAD_BITS;
	}	
	switch(Mode->flags&DUALHEAD_BITS)
	{
		case DUALHEAD_OFF:
			Mode->virtual_width = Mode->timing.h_display;
			break;
		case DUALHEAD_CLONE:
			Mode->virtual_width = Mode->timing.h_display;
			break;
		case DUALHEAD_ON:
			Mode->virtual_width = Mode->timing.h_display * 2;
			break;
		case DUALHEAD_SWITCH:
			Mode->virtual_width = Mode->timing.h_display * 2;
			break;
	}

	Mode->flags&=~(TVM_BITS | TV_VIDEO);
	switch(tvMode)
	{
	case VID_TV_PAL:
		Mode->flags|=TV_VIDEO;
	case DESK_TV_PAL:
		Mode->flags|=TVM_PAL;
		break;
	case VID_TV_NTSC:
		Mode->flags|=TV_VIDEO;
	case DESK_TV_NTSC:
		Mode->flags|=TVM_NTSC;
		break;
	}

	switch(tvHead)
	{
	case TV_PRIM:
		Mode->flags|=TV_PRIMARY;
		break;
	case TV_SEC:
		Mode->flags&=~TV_PRIMARY;
		break;
	}
}

BBitmap* DualHeadWindow::GetBitmap(char *name)
{
	return BTranslationUtils::GetBitmap(name);
}

