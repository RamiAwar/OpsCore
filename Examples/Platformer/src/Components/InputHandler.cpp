#include <OpsCore.h>
#include "InputHandler.h"
 

Command* InputHandler::HandleInput() {

    if (oc::Input::IsKeyPressed(OC_KEY_SPACE)) return shootButton;
    if (oc::Input::IsKeyPressed(OC_KEY_W)) return sheatheButton;
    if (oc::Input::IsKeyPressed(OC_KEY_D)) return moveRightButton;
    if (oc::Input::IsKeyPressed(OC_KEY_A)) return moveLeftButton;

    // No button pressed 
    return NULL;

}

