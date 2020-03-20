#include <OpsCore.h>
#include "InputHandler.h"
 

Command* InputHandler::HandleInput() {

    //OC_CLIENT_INFO("Inputhandler HandleInput");
    if (oc::Input::IsKeyPressed(OC_KEY_SPACE)) return shootButton;
    if (oc::Input::IsKeyPressed(OC_KEY_LEFT_CONTROL)) return sheatheButton;
    if (oc::Input::IsKeyPressed(OC_KEY_D)) return moveRightButton;
    if (oc::Input::IsKeyPressed(OC_KEY_A)) return moveLeftButton;

    // No button pressed 
    return noButton;

}

