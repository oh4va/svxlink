/**
@file	 ModuleMMI.cpp
@brief   Multi-Mode Interface
@author  Veijo Arponen / OH4VA
@date	 2020-07-26

\verbatim
A module (plugin) for the multi purpose tranciever frontend system.
Copyright (C) 2004  Tobias Blomberg

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



/****************************************************************************
 *
 * System Includes
 *
 ****************************************************************************/

#include <stdio.h>

#include <iostream>
#include <sstream>
#include <chrono>

#include <AsyncCppApplication.h>
#include <AsyncTimer.h>

using namespace std;
using namespace Async;

/****************************************************************************
 *
 * Project Includes
 *
 ****************************************************************************/

//#include <version/MODULE_MMI.h>



/****************************************************************************
 *
 * Local Includes
 *
 ****************************************************************************/

#include "ModuleMMI.h"
#include "MmiTx.h"



/****************************************************************************
 *
 * Namespaces to use
 *
 ****************************************************************************/

using namespace std;



/****************************************************************************
 *
 * Defines & typedefs
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Local class definitions
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Prototypes
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Exported Global Variables
 *
 ****************************************************************************/




/****************************************************************************
 *
 * Local Global Variables
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Pure C-functions
 *
 ****************************************************************************/


extern "C" {
  Module *module_init(void *dl_handle, Logic *logic, const char *cfg_name)
  {
    return new ModuleMMI(dl_handle, logic, cfg_name);
  }
} /* extern "C" */



/****************************************************************************
 *
 * Public member functions
 *
 ****************************************************************************/


ModuleMMI::ModuleMMI(void *dl_handle, Logic *logic, const string& cfg_name)
  : Module(dl_handle, logic, cfg_name)
{
  //cout << "\tModule MMI v" MODULE_TXMMI_VERSION " starting...\n";
  cout << "\tModule MMI starting...\n";

} /* ModuleMMI */


ModuleMMI::~ModuleMMI(void)
{
    delete timer;


} /* ~ModuleMMI */





/****************************************************************************
 *
 * Protected member functions
 *
 ****************************************************************************/


/*
 *------------------------------------------------------------------------
 * Method:    
 * Purpose:   
 * Input:     
 * Output:    
 * Author:    
 * Created:   
 * Remarks:   
 * Bugs:      
 *------------------------------------------------------------------------
 */






/****************************************************************************
 *
 * Private member functions
 *
 ****************************************************************************/


/*
 *----------------------------------------------------------------------------
 * Method:    initialize
 * Purpose:   Called by the core system right after the object has been
 *    	      constructed. As little of the initialization should be done in
 *    	      the constructor. It's easier to handle errors here.
 * Input:     None
 * Output:    Return \em true on success or else \em false should be returned
 * Author:    Tobias Blomberg / SM0SVX
 * Created:   2005-08-28
 * Remarks:   The base class initialize method must be called from here.
 * Bugs:      
 *----------------------------------------------------------------------------
 */
bool ModuleMMI::initialize(void)
{
  if (!Module::initialize())
  {
    return false;
  }


  timer = new Timer(100, Timer::TYPE_PERIODIC);
  timer->expired.connect(mem_fun(*this, &ModuleMMI::onTimerExpired));
  
  return true;
  
} /* initialize */


/*
 *----------------------------------------------------------------------------
 * Method:    activateInit
 * Purpose:   Called by the core system when this module is activated.
 * Input:     None
 * Output:    None
 * Author:    Tobias Blomberg / SM0SVX
 * Created:   2004-03-07
 * Remarks:   
 * Bugs:      
 *----------------------------------------------------------------------------
 */
void ModuleMMI::activateInit(void)
{

} /* activateInit */


/*
 *----------------------------------------------------------------------------
 * Method:    deactivateCleanup
 * Purpose:   Called by the core system when this module is deactivated.
 * Input:     None
 * Output:    None
 * Author:    Tobias Blomberg / SM0SVX
 * Created:   2004-03-07
 * Remarks:   Do NOT call this function directly unless you really know what
 *    	      you are doing. Use Module::deactivate() instead.
 * Bugs:      
 *----------------------------------------------------------------------------
 */
void ModuleMMI::deactivateCleanup(void)
{
  
} /* deactivateCleanup */


/*
 *----------------------------------------------------------------------------
 * Method:    dtmfDigitReceived
 * Purpose:   Called by the core system when a DTMF digit has been
 *    	      received. This function will only be called if the module
 *    	      is active.
 * Input:     digit   	- The DTMF digit received (0-9, A-D, *, #)
 *            duration	- The length in milliseconds of the received digit
 * Output:    Return true if the digit is handled or false if not
 * Author:    Tobias Blomberg / SM0SVX
 * Created:   2004-03-07
 * Remarks:   
 * Bugs:      
 *----------------------------------------------------------------------------
 */
bool ModuleMMI::dtmfDigitReceived(char digit, int duration)
{
  cout << "DTMF digit received in module " << name() << ": " << digit << endl;
  
  return false;
  
} /* dtmfDigitReceived */


/*
 *----------------------------------------------------------------------------
 * Method:    dtmfCmdReceived
 * Purpose:   Called by the core system when a DTMF command has been
 *    	      received. A DTMF command consists of a string of digits ended
 *    	      with a number sign (#). The number sign is not included in the
 *    	      command string. This function will only be called if the module
 *    	      is active.
 * Input:     cmd - The received command.
 * Output:    None
 * Author:    Tobias Blomberg / SM0SVX
 * Created:   2004-03-07
 * Remarks:   
 * Bugs:      
 *----------------------------------------------------------------------------
 */
void ModuleMMI::dtmfCmdReceived(const string& cmd)
{
  cout << "DTMF command received in module " << name() << ": " << cmd << endl;
  
  if (cmd == "")
  {
    deactivateMe();
  }
  else
  {

  }
} /* dtmfCmdReceived */


#if 0
void ModuleMMI::dtmfCmdReceivedWhenIdle(const std::string &cmd)
{

} /* dtmfCmdReceivedWhenIdle */
#endif


/*
 *----------------------------------------------------------------------------
 * Method:    squelchOpen
 * Purpose:   Called by the core system when the squelch open or close.
 * Input:     is_open - Set to \em true if the squelch is open or \em false
 *    	      	      	if it's not.
 * Output:    None
 * Author:    Tobias Blomberg / SM0SVX
 * Created:   2005-08-28
 * Remarks:   
 * Bugs:      
 *----------------------------------------------------------------------------
 */
void ModuleMMI::squelchOpen(bool is_open)
{
  
} /* squelchOpen */


/*
 *----------------------------------------------------------------------------
 * Method:    allMsgsWritten
 * Purpose:   Called by the core system when all announcement messages has
 *    	      been played. Note that this function also may be called even
 *    	      if it wasn't this module that initiated the message playing.
 * Input:     None
 * Output:    None
 * Author:    Tobias Blomberg / SM0SVX
 * Created:   2005-08-28
 * Remarks:   
 * Bugs:      
 *----------------------------------------------------------------------------
 */
void ModuleMMI::allMsgsWritten(void)
{

} /* allMsgsWritten */


void ModuleMMI::onTimerExpired(Timer *t)
{
    static int count = 0;

    //cout << "Timer expired " << getCurrentTimestamp() << " ...\n";
    cout << "Timer expired " << ++count << " ...\n";
}

/*
 * This file has not been truncated
 */
