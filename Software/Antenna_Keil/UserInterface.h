#ifndef GUI_H
#define GUI_H

#ifdef __cplusplus

class UserInterface
{
	UserInterface();
	static void init();
	static void refresh();
};

#endif //cplusplus

#ifdef __cplusplus
	extern "C" {
#endif
		
void userInterface_init();
void userInterface_refresh();
		
#ifdef __cplusplus
	}
#endif //cplusplus
#endif //factory_H
