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

    /**
      * @brief get the state of the Buttons
      * @param None
      * @retval array of button state
      */
    std::array<bool, NBR_OF_BUTTONS> getButtonsState();

    /**
      * @brief set the ball nbr
      * @param nbr : the number of the chosen ball
      * @retval None
      */
    void setBallNbr(uint16_t nbr);

    /**
      * @brief Minus button pressed
      * @param None
      * @retval None
      */
    void btnMinusPressed();

    /**
      * @brief plus button pressed
      * @param None
      * @retval None
      */
    void btnPlusPressed();

    /**
      * @brief set the LPDA power
      * @param power : the power of the antenna
      * @retval None
      */
    void setPower(int16_t power);

    /**
      * @brief set the LOOP power
      * @param power : the power of the antenna
      * @retval None
      */
    void setPosition(int16_t position);

    /**
      * @brief set the LPDA power into a progress bar
      * @param power : the power of the antenna in %
      * @retval None
      */
    void setPowerBar(uint16_t value);

protected:
};

#endif // MAIN_VIEW_HPP
