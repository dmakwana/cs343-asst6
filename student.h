#pragma once
#include "printer.h"
#include "nameServer.h"
#include "watcardOffice.h"
#include "groupOff.h"

_Task Student {
	Printer &prt;
	NameServer &nameServer;
	WATCardOffice &cardOffice;
	Groupoff &groupoff;
    unsigned int id;
    unsigned int maxPurchases;
    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
             unsigned int id, unsigned int maxPurchases );
};
