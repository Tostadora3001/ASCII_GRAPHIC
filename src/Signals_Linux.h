//THis self-made library provides the necesary code in order to handle correctly the Linux Signals

#ifndef SIGNALS_LINUX_H
#define SIGNALS_LINUX_H

//Handlers
//-------------------------------------------------------------------------------------------------------------------------//

//PRE  : Must be configurated by resize_signal_configuration() and a resize signal must arrive
//POST :
void handle_resize(int sig);

//PRE  : Must be configurated by CrtlC_signal_configuration() and a Crtl-C signal must arrive
//POST
void handle_CrtlC(int sig);

//Signals configurators 
//-------------------------------------------------------------------------------------------------------------------------//

//PRE  : -
//POST : All the configuration functions are called, configurating all relevant signals
void Configure_all_signals();

//PRE  : -
//POST : The resize signal is configurated
void resize_signal_configuration();

//PRE  : -
//POST : The Crtl-C signal is configureted in order to avoid problems from unexpected terminations
void CrtlC_signal_configuration();

#endif