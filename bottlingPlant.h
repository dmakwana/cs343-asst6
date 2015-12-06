#pragma once

#include "vendingMachine.h"
#include "printer.h"
#include "nameServer.h"
#include "config.h"

_Task BottlingPlant {
	Printer &prt;
	NameServer &nameServer;
	unsigned int numVendingMachines;
	unsigned int maxShippedPerFlavour;
	unsigned int maxStockPerFlavour;
	unsigned int timeBetweenShipments;
	unsigned int productionRun[VendingMachine::NUM_FLAVOURS];
	bool plantShuttingDown;
    void main();
  public:
    _Event Shutdown {};                    // shutdown plant
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    void getShipment(unsigned int cargo[]);
};
