#ifndef SCREEN1_VIEW_HPP
#define SCREEN1_VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <array>
#include "config.h"

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    std::array<bool, NBR_OF_BUTTONS> getButtonsState();
    void setBallNbr(int nbr);
    void btnMinusPressed();
    void btnPlusPressed();
    void setPower(int power);

protected:
};

#endif // SCREEN1_VIEW_HPP
