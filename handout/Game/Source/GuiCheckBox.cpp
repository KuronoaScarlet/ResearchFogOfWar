#include "GuiCheckBox.h"
#include "Options.h"

GuiCheckBox::GuiCheckBox(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::CHECKBOX, id)
{
    this->bounds = bounds;
    this->text = text;
}

GuiCheckBox::~GuiCheckBox()
{
}

bool GuiCheckBox::Update(Input* input, float dt)
{
    if (state != GuiControlState::DISABLED)
    {
        int mouseX, mouseY;
        input->GetMousePosition(mouseX, mouseY);
        mouseX -= app->render->camera.x;
        mouseY -= app->render->camera.y;
        // Check collision between mouse and button bounds
        if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) && 
            (mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
        {
            state = GuiControlState::FOCUSED;

            if (input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
            {
                state = GuiControlState::PRESSED;
            }

            // If mouse button pressed -> Generate event!
            if (input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
            {
                NotifyObserver();
                checked = !checked;
                
            }
        }
        else state = GuiControlState::NORMAL;
    }

    return false;
}

bool GuiCheckBox::Draw(Render* render)
{
    // Draw the right button depending on state
    if(!app->debugButton)
        {
        switch (state)
        {
            case GuiControlState::DISABLED:
            {
                if (checked) render->DrawRectangle(bounds, 100, 100, 100, 255);
                else render->DrawRectangle(bounds, 100, 100, 100, 255);
            } break;
            case GuiControlState::NORMAL:
            {
                if (checked) render->DrawTexture(texturePressed, bounds.x, bounds.y, NULL);
                else render->DrawTexture(textureIdle, bounds.x, bounds.y, NULL);
            } break;
            case GuiControlState::FOCUSED:
                render->DrawTexture(textureFocused, bounds.x, bounds.y, NULL);
               // render->DrawRectangle(bounds, 100, 25, 70, 255);
                if (audio == false)
                {
                    audio = true;
                    app->audio->PlayFx(selectedFx);
                }
                break;
            case GuiControlState::PRESSED:
                render->DrawTexture(texturePressed, bounds.x, bounds.y, NULL);
             //   render->DrawRectangle(bounds, 100, 25, 70, 255);
                if (audio == false)
                {
                    audio = true;
                    app->audio->PlayFx(selectedFx);
                }
                break;
            case GuiControlState::SELECTED:
              //  render->DrawRectangle(bounds, 0, 255, 0, 255);
                render->DrawTexture(texturePressed, bounds.x, bounds.y, NULL);
                if (audio == false)
                {
                    audio = true;
                    app->audio->PlayFx(selectedFx);
                }
                break;
            default:
                break;
            }
        }
    else
    {
        switch (state)
        {
        case GuiControlState::DISABLED:
        {
            if (checked) render->DrawRectangle(bounds, 100, 100, 100, 255);
            else render->DrawRectangle(bounds, 100, 100, 100, 255);
        } break;
        case GuiControlState::NORMAL:
        {
            if (checked) render->DrawRectangle(bounds, 0, 255, 0, 255);
            else render->DrawRectangle(bounds, 100, 100, 100, 255);
        } break;
        case GuiControlState::FOCUSED: render->DrawRectangle(bounds, 100, 0, 100, 255);
            break;
        case GuiControlState::PRESSED:  render->DrawRectangle(bounds, 100, 100, 0, 255);
            break;
        case GuiControlState::SELECTED: render->DrawRectangle(bounds, 0, 255, 0, 255);
            break;
        default:
            break;
        }
    
    }

    return false;
}
