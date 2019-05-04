/*
  ==============================================================================

    sspCommandIDs.h
    Created: 21 Apr 2019 8:43:40pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

namespace sspCommandIDs
{
	enum
	{
		DocNew = 0x300000,
		DocOpen = 0x300001,
		DocSave = 0x300002, 
		DocSaveAs = 0x300003,

		RunVerify = 0x300010, 
		RunInit = 0x300011, 
		RunStart = 0x300012, 
		RunStop = 0x300013,

		EditSettings = 0x300020,

		lastCommandIDEntry
	};
}
