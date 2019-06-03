#ifndef CRITICAL_H
#define CRITICAL_H

extern volatile int bInISR;

#ifdef __cplusplus
extern "C" void ARMEnableInt();
extern "C" void ARMDisableInt();
#endif // __cplusplus


int inISR();
void enterCritical();
void exitCritical();


#endif /* CRITICAL_H */
