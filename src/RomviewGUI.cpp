#include "RomviewGUI.h"
#include "ColorDef.h"
#include "Util.h"
#include "Debug.h"

using namespace agbplay;
using namespace std;

/*
 * public
 */

RomviewGUI::RomviewGUI(uint32_t height, uint32_t width, uint32_t yPos, uint32_t xPos, Rom& rrom, SoundData& rsdata) 
    : CursesWin(height, width, yPos, xPos) 
{
    rrom.Seek(0xA0); // seek to game title;
    gameName = rrom.ReadString(12);
    gameCode = rrom.ReadString(4);
    songTable = rsdata.sTable->GetSongTablePos();
    numSongs = rsdata.sTable->GetNumSongs();
    update();
}

RomviewGUI::~RomviewGUI() 
{
}

void RomviewGUI::Resize(uint32_t height, uint32_t width, uint32_t yPos, uint32_t xPos) 
{
    CursesWin::Resize(height, width, yPos, xPos);
    update();
}

/*
 * private
 */

void RomviewGUI::update() 
{
    // clear
    wattrset(winPtr, A_NORMAL);
    wclear(winPtr);

    // draw borders
    wattrset(winPtr, COLOR_PAIR(Color::WINDOW_FRAME) | A_REVERSE);
    mvwvline(winPtr, 1, 0, ' ', height-1);
    mvwprintw(winPtr, 0, 0, "%*s", width, " ROM Information");

    // print information
    wattrset(winPtr, A_UNDERLINE | COLOR_PAIR(Color::DEF_DEF));
    mvwprintw(winPtr, 2, 2, "ROM Name:");
    wattrset(winPtr, A_BOLD | COLOR_PAIR(Color::DEF_DEF));
    mvwprintw(winPtr, 3, 2, "%s", gameName.c_str());
    wattrset(winPtr, A_UNDERLINE | COLOR_PAIR(Color::DEF_DEF));
    mvwprintw(winPtr, 5, 2, "ROM Code:");
    wattrset(winPtr, A_BOLD | COLOR_PAIR(Color::DEF_DEF));
    mvwprintw(winPtr, 6, 2, "%s", gameCode.c_str());
    wattrset(winPtr, A_UNDERLINE | COLOR_PAIR(Color::DEF_DEF));
    mvwprintw(winPtr, 8, 2, "Songtable Offset:");
    wattrset(winPtr, A_BOLD | COLOR_PAIR(Color::DEF_DEF));
    mvwprintw(winPtr, 9, 2, "0x%lX", songTable);
    wattrset(winPtr, A_UNDERLINE | COLOR_PAIR(Color::DEF_DEF));
    mvwprintw(winPtr, 11, 2, "Song Amount:");
    wattrset(winPtr, A_BOLD | COLOR_PAIR(Color::DEF_DEF));
    mvwprintw(winPtr, 12, 2, "%d", numSongs);
    wrefresh(winPtr);
}
