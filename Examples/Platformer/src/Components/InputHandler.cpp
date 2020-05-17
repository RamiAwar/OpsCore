#include <PumpkinBox.h>
#include "InputHandler.h"
 

Command* InputHandler::HandleInput() {

    //PB_CLIENT_INFO("Inputhandler HandleInput");
    if (oc::Input::IsKeyPressed(PB_KEY_SPACE)) return shootButton;
    if (oc::Input::IsKeyPressed(PB_KEY_LEFT_CONTROL)) return sheatheButton;
    if (oc::Input::IsKeyPressed(PB_KEY_D)) return moveRightButton;
    if (oc::Input::IsKeyPressed(PB_KEY_A)) return moveLeftButton;

    // No button pressed 
    return noButton;

}

