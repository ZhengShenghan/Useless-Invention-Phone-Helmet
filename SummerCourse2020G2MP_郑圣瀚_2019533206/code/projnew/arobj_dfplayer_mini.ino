//
// arobj_dfplayer_mini.cpp
//
// generated by the Ardestan programming language : Tue Dec 03 17:55:19 CST 2019
//

#include <stdio.h>
#include <stdint.h>
#include "ArdestanIDs.h"
#include "Ardestan.h"


#include "arobj_dfplayer_mini.hpp"

//----------------------------------------------------------------------------
// implementation
//----------------------------------------------------------------------------

void init_func_dfplayer_mini(
    ARObject*        self      ,
    void*            __fields__,
    uint_fast8_t     argc      ,
    ARMessageType*   argt      ,
    ARValue*         argv
)
{
    ARObjDfplayerMini* fields = (ARObjDfplayerMini*)__fields__;

	fields->serial = NULL;
	fields->player = NULL;

    if (argt[0] != ARMessageType::INT || argt[1] != ARMessageType::INT){
    	return;
    }

	fields->serial = new SoftwareSerial(argv[0].i, argv[1].i);
	fields->player = new DFRobotDFPlayerMini();

	fields->serial->begin(DFPLAYER_MINI_SERIAL_BAUD_RATE);

	bool ret = fields->player->begin(*(fields->serial));
	if (ret == false){
		delete fields->serial;
		delete fields->player;
		fields->serial = NULL;
		fields->player = NULL;
		return;
	}

	fields->player->setTimeOut(DFPLAYER_MINI_TIMEOUT);
	fields->player->volume(DFPLAYER_MINI_DEFAULT_VOLUME);

	return;
}

void trigger_func_dfplayer_mini(
    ARObject*        self      ,
    int32_t          inlet_no  ,
    void*            __fields__
)
{
    ARObjDfplayerMini* fields = (ARObjDfplayerMini*)__fields__;

	//if the volume is changed.
	if (inlet_no == 1){
		if (self->getInputType(1) == ARMessageType::INT){
			int32_t vol = self->getInputInt(1);
			if (0 <= vol && vol <= 30){
				fields->player->volume(vol);
			}
		}
		return;
	}

	//if it is a play request.
	ARMessageType t = self->getInputType(0);
	if (t == ARMessageType::INT){
		int32_t no = self->getInputInt(0);
		fields->player->play(no);
		return;
	}

	if (t != ARMessageType::SYM_ID){
		return;
	}


	switch(self->getInputSymbol(0)){
	case ID_VOLUME_UP:
		fields->player->volumeUp();
		break;	

	case ID_VOLUME_DOWN:
		fields->player->volumeDown();
		break;	

	case ID_NEXT:
		fields->player->next();
		break;

	case ID_PREVIOUS:
		fields->player->previous();
		break;	

	case ID_PAUSE:
		fields->player->pause();
		break;

	case ID_START:
		fields->player->start();
		break;

	case ID_ENABLE_LOOP:
		fields->player->enableLoop();
		break;

	case ID_DISABLE_LOOP:
		fields->player->disableLoop();
		break;

	default:
		break;
	}
	
	return;
}

