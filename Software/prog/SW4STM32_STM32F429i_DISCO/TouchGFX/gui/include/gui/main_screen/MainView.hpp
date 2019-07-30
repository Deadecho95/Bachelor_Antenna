#ifndef MAIN_VIEW_HPP
#define MAIN_VIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <array>
class MainView : public MainViewBase
{
public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    std::array<bool, NBR_OF_BUTTONS> getButtonsState();
    void setBallNbr(uint16_t nbr);
    void btnMinusPressed();
    void btnPlusPressed();
    void setPower(int16_t power);
    void setPosition(int16_t position);
    void setPowerBar(uint16_t value);
protected:
};

#endif // MAIN_VIEW_HPP
