#ifndef __GUICONTROL_H__
#define __GUICONTROL_H__

#include "Input.h"
#include "Render.h"
#include "Module.h"

#include "Point.h"
#include "SString.h"

#include "SDL/include/SDL.h"

enum class GuiControlType
{
    BUTTON,
    TOGGLE,
    CHECKBOX,
    SLIDER,
    SLIDERBAR,
    COMBOBOX,
    DROPDOWNBOX,
    INPUTBOX,
    VALUEBOX,
    SPINNER
};

enum class GuiControlState
{
    DISABLED,
    NORMAL,
    FOCUSED,
    PRESSED,
    SELECTED
};

class GuiControl
{
public:

    GuiControl(GuiControlType type, uint32 id) : type(type), id(id), state(GuiControlState::NORMAL) {}

    GuiControl(GuiControlType type, SDL_Rect bounds, const char* text) :
        type(type),
        state(GuiControlState::NORMAL),
        bounds(bounds),
        text(text) 
    {
        color.r = 255; color.g = 255; color.b = 255;
        textureIdle = NULL;
        textureFocused = NULL;
        texturePressed = NULL;
    }

    virtual bool Update(Input* input, float dt)
    {
        return true;
    }

    virtual bool Draw(Render* render) const
    {
        return true;
    }

    void SetTexture(SDL_Texture* texIdle, SDL_Texture* texFocused, SDL_Texture* texPressed)
    {
        textureIdle = texIdle;
        textureFocused = texFocused;
        texturePressed = texPressed;
        section = { 0, 0, 0, 0 };
    }

    void SetDisableTexture(SDL_Texture* textDisable)
    {
        textureDisable = textDisable;
    }

    void SetObserver(Module* module)
    {
        observer = module;
    }

    void NotifyObserver()
    {
        observer->OnGuiMouseClickEvent(this);
    }

public:

    uint32 id;
    GuiControlType type;
    GuiControlState state;

    SString text;           // Control text (if required)
    SDL_Rect bounds;        // Position and size
    SDL_Color color;        // Tint color

    SDL_Texture* textureIdle;
    SDL_Texture* textureFocused;   // Texture atlas reference
    SDL_Texture* texturePressed;
    SDL_Texture* textureDisable;
    SDL_Rect section;       // Texture atlas base section

    //Font font;              // Text font

    Module* observer;        // Observer module (it should probably be an array/list)

    //Audio

    uint selectFx = 0;
    uint selectedFx = 0;
    uint releaseFx = 0;
    uint pencilFx = 0;
    bool audio;
    bool audioB;
    bool audioR;

};

#endif // __GUICONTROL_H__