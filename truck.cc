#include "truck.h"
#include "MPRNG.h"

extern MPRNG mprng;

void Truck::main() {
	while(true) {
		plant.getShipment(cargo);
	}
}

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour ): prt(prt), nameServer(nameServer), plant(plant),
																			   numVendingMachines(numVendingMachines),
																			   maxStockPerFlavour(maxStockPerFlavour) {
	machineList = nameServer.getMachineList();
}
