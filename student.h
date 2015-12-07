#pragma once

#include "printer.h"
#include "nameServer.h"
#include "watcardOffice.h"
#include "groupOff.h"
#include "watcard.h"
#include "vendingMachine.h"

_Task Student {
	Printer &prt;
	NameServer &nameServer;
	WATCardOffice &cardOffice;
	Groupoff &groupoff;
  unsigned int id;
  unsigned int maxPurchases;
  void main();
  unsigned int num_sodas;
  VendingMachine::Flavours favorite;
  VendingMachine *vm;
  WATCard::FWATCard fcard, giftCard;
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
             unsigned int id, unsigned int maxPurchases );
};
