/**
@file	 ModuleMMI.h
@brief   Multi-Mode Interface
@author  Veijo Arponen / OH4VA
@date	 2020-07-26

\verbatim
A module (plugin) for the svxlink server, a multi purpose tranciever
frontend system.
Copyright (C) 2004-2005  Tobias Blomberg / SM0SVX

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
\endverbatim
*/


#ifndef MODULE_MMI_INCLUDED
#define MODULE_MMI_INCLUDED


/****************************************************************************
 *
 * System Includes
 *
 ****************************************************************************/

#include <string>



/****************************************************************************
 *
 * Project Includes
 *
 ****************************************************************************/

#include <Module.h>
#include <version/SVXLINK.h>
#include <AsyncTimer.h>



/****************************************************************************
 *
 * Local Includes
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Forward declarations
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Namespace
 *
 ****************************************************************************/

//namespace TxMMI
//{


/****************************************************************************
 *
 * Forward declarations of classes inside of the declared namespace
 *
 ****************************************************************************/

  

/****************************************************************************
 *
 * Defines & typedefs
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Exported Global Variables
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Class definitions
 *
 ****************************************************************************/

/**
@brief	A_brief_description_of_this_class
@author Tobias Blomberg
@date   2005-08-28
*/
class ModuleMMI : public Module
{
  public:
    ModuleMMI(void *dl_handle, Logic *logic, const std::string& cfg_name);
    ~ModuleMMI(void);
    const char *compiledForVersion(void) const { return SVXLINK_VERSION; }

  private:
    bool initialize(void);
    void activateInit(void);
    void deactivateCleanup(void);
    bool dtmfDigitReceived(char digit, int duration);
    void dtmfCmdReceived(const std::string& cmd);
    //void dtmfCmdReceivedWhenIdle(const std::string &cmd);
    void squelchOpen(bool is_open);
    void allMsgsWritten(void);
    void onTimerExpired(Timer *t);

    Timer * timer;


};  /* class ModuleMMI */


//} /* namespace */

#endif /* MODULE_MMI_INCLUDED */



/*
 * This file has not been truncated
 */
