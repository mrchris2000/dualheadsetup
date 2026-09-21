#include <Application.h>
#include <InterfaceKit.h>
#include <stdio.h>
#include <stdlib.h>
//#include <TranslationUtils.h>

/*dualhead extensions to flags*/
#define DUALHEAD_OFF (0<<6)
#define DUALHEAD_CLONE (1<<6)
#define DUALHEAD_ON (2<<6)
#define DUALHEAD_SWITCH (3<<6)
#define DUALHEAD_BITS (3<<6)
#define DUALHEAD_CAPABLE (1<<8)
#define TVM_BITS (3<<9)
#define TVM_MON (0<<9
#define TVM_PAL (1<<9)
#define TVM_NTSC (2<<9)
#define TV_CAPABLE (1<<11)
#define TV_VIDEO (1<<12)
#define TV_PRIMARY (1<<13)

#define	T_POSITIVE_SYNC	(B_POSITIVE_HSYNC | B_POSITIVE_VSYNC)
/* mode flags will be setup as status info by PROPOSEMODE! */
#define MODE_FLAGS 0
#define DT_MODE_COUNT (sizeof (dt_mode_list) / sizeof (display_mode))
#define VTP_MODE_COUNT (sizeof (vtp_mode_list) / sizeof (display_mode))
#define VTN_MODE_COUNT (sizeof (vtn_mode_list) / sizeof (display_mode))

static const display_mode dt_mode_list[] = {
{ { 25175, 640, 656, 752, 800, 480, 490, 492, 525, 0}, B_CMAP8, 640, 480, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@60Hz_(640X480X8.Z1) */
{ { 27500, 640, 672, 768, 864, 480, 488, 494, 530, 0}, B_CMAP8, 640, 480, 0, 0, MODE_FLAGS}, /* 640X480X60Hz */
{ { 30500, 640, 672, 768, 864, 480, 517, 523, 588, 0}, B_CMAP8, 640, 480, 0, 0, MODE_FLAGS}, /* SVGA_640X480X60HzNI */
{ { 31500, 640, 664, 704, 832, 480, 489, 492, 520, 0}, B_CMAP8, 640, 480, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@70-72Hz_(640X480X8.Z1) */
{ { 31500, 640, 656, 720, 840, 480, 481, 484, 500, 0}, B_CMAP8, 640, 480, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@75Hz_(640X480X8.Z1) */
{ { 36000, 640, 696, 752, 832, 480, 481, 484, 509, 0}, B_CMAP8, 640, 480, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@85Hz_(640X480X8.Z1) */
/* 4:3 modes; 480k pixels */
{ { 36000, 800, 824, 896, 1024, 600, 601, 603, 625, 0}, B_CMAP8, 800, 600, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@56Hz_(800X600) from Be, Inc. driver + XFree86 */
{ { 38100, 800, 832, 960, 1088, 600, 602, 606, 620, 0}, B_CMAP8, 800, 600, 0, 0, MODE_FLAGS}, /* SVGA_800X600X56HzNI */
{ { 40000, 800, 840, 968, 1056, 600, 601, 605, 628, T_POSITIVE_SYNC}, B_CMAP8, 800, 600, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@60Hz_(800X600X8.Z1) + XFree86 */
{ { 49500, 800, 816, 896, 1056, 600, 601, 604, 625, T_POSITIVE_SYNC}, B_CMAP8, 800, 600, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@75Hz_(800X600X8.Z1) + XFree86 */
{ { 50000, 800, 856, 976, 1040, 600, 637, 643, 666, T_POSITIVE_SYNC}, B_CMAP8, 800, 600, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@70-72Hz_(800X600X8.Z1) + XFree86 */
{ { 56250, 800, 832, 896, 1048, 600, 601, 604, 631, T_POSITIVE_SYNC}, B_CMAP8, 800, 600, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@85Hz_(800X600X8.Z1) + XFree86 */
/* 4:3 modes; 786.432k pixels */
{ { 65000, 1024, 1048, 1184, 1344, 768, 771, 777, 806, 0}, B_CMAP8, 1024, 768, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@60Hz_(1024X768X8.Z1) + XFree86 */
{ { 75000, 1024, 1048, 1184, 1328, 768, 771, 777, 806, 0}, B_CMAP8, 1024, 768, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@70-72Hz_(1024X768X8.Z1) + XFree86 */
{ { 78750, 1024, 1040, 1136, 1312, 768, 769, 772, 800, T_POSITIVE_SYNC}, B_CMAP8, 1024, 768, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@75Hz_(1024X768X8.Z1) + XFree86 */
{ { 94500, 1024, 1072, 1168, 1376, 768, 769, 772, 808, T_POSITIVE_SYNC}, B_CMAP8, 1024, 768, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@85Hz_(1024X768X8.Z1) + XFree86 */
};
static const display_mode vtp_mode_list[] = {
{ { 33300, 720, 736, 848, 888, 576, 579, 621, 625, T_POSITIVE_SYNC}, B_CMAP8, 720, 576, 0, 0, MODE_FLAGS}, /* PAL DVD mode, moni @ 60Hz */
{ { 38850, 720, 736, 848, 888, 576, 579, 621, 625, T_POSITIVE_SYNC}, B_CMAP8, 720, 576, 0, 0, MODE_FLAGS}, /* PAL DVD mode, moni @ 70Hz */
{ { 35400, 768, 848, 872, 944, 576, 579, 621, 625, T_POSITIVE_SYNC}, B_CMAP8, 768, 576, 0, 0, MODE_FLAGS}, /* PAL VCD mode, moni @ 60Hz */
{ { 41300, 768, 848, 872, 944, 576, 579, 621, 625, T_POSITIVE_SYNC}, B_CMAP8, 768, 576, 0, 0, MODE_FLAGS}, /* PAL VCD mode, moni @ 70Hz */
};
static const display_mode vtn_mode_list[] = {
{ { 24696, 640, 728, 752, 784, 480, 490, 515, 525, 0}, B_CMAP8, 640, 480, 0, 0, MODE_FLAGS}, /* NTSC VCD mode, moni @ 60Hz */
{ { 28812, 640, 728, 752, 784, 480, 490, 515, 525, 0}, B_CMAP8, 640, 480, 0, 0, MODE_FLAGS}, /* NTSC VCD mode, moni @ 70Hz */
{ { 27972, 720, 736, 848, 888, 480, 490, 510, 525, T_POSITIVE_SYNC}, B_CMAP8, 720, 480, 0, 0, MODE_FLAGS}, /* NTSC DVD mode, moni @ 60Hz */
{ { 32634, 720, 736, 848, 888, 480, 490, 510, 525, T_POSITIVE_SYNC}, B_CMAP8, 720, 480, 0, 0, MODE_FLAGS}, /* NTSC DVD mode, moni @ 70Hz */
};

class DualHeadWindow : public BWindow 
{
public:
				DualHeadWindow(BRect frame); 
				~DualHeadWindow();
virtual	bool	QuitRequested();

void			MessageReceived(BMessage* message);

private:

BScreen *		screenInfo;
display_mode 	currentMode;
display_mode	selectedMode;
display_mode * 	screenModesList;
display_mode * 	screenModes;
uint32 			screenModeCount;
uint32 			screenModeListCount;

int      		tvMode;
int				tvHead;
enum {TV_MONITOR, DESK_TV_PAL, DESK_TV_NTSC, VID_TV_PAL, VID_TV_NTSC};
enum {TV_PRIM, TV_SEC};
enum {RS, RF, DE};

BRadioButton *	multiHeadButton[4];
BBox *			configView;
BBox *			rightView;
BBox *			leftView;

void 			CreateMenus();
void			findFallback();
void			CreateRadio();
void 			setModeList();

void			CalcModeInfo(display_mode *);
char 			resolution[64];
char 			refresh[64];
char 			depth[64];
char			info[512];

void			CheckMode(display_mode * Mode);
void			fillMenus();

bool			firstRun;
BPopUpMenu *	resolutionPopup;
BPopUpMenu * 	refreshPopup;
BPopUpMenu *	depthPopup;

BMenuField *	resSelector;
BMenuField *	refSelector;
BMenuField *	depSelector;

BMenuBar *		mainBar;
BMenu	 *		tvMenu;
BMenu	 *		tvheadMenu;
BMenu	 *		BuildFileMenu(void) const;	
BMenu    *		BuildTVMenu(void) const;
void			UpdateTVMenu();
BMenu	 * 		BuildTVheadMenu(void) const;
void			UpdateTVheadMenu();

BBitmap	 * 		GetBitmap(char*);
void			AboutRequested();

BBitmap	*		empire;
BBitmap	*		rebel;
BBitmap	*		combined;
bool 			frameState;
};

