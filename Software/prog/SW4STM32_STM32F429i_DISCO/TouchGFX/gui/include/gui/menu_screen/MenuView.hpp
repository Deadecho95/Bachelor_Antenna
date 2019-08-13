#ifndef MENU_VIEW_HPP
#define MENU_VIEW_HPP

#include <gui_generated/menu_screen/MenuViewBase.hpp>
#include <gui/menu_screen/MenuPresenter.hpp>

class MenuView : public MenuViewBase
{
public:
    MenuView();
    virtual ~MenuView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    /**
      * @brief calibrate button is pressed
      * @param None
      * @retval None
      */
    void CalibrateButtonPressed();
protected:
};

#endif // MENU_VIEW_HPP
