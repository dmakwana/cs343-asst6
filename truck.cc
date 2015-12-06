#include "truck.h"
#include "MPRNG.h"

extern MPRNG mprng;

bool Truck::truckEmpty() {
	for (int i = 0; i < VendingMachine::NUM_FLAVOURS; i++) {
		if(cargo[i]) {
			return false;
		}
	}
	return true;
}

void Truck::main() {
	while(true) {
		yield(mprng(1,10));
		try {
			_Enable {
				plant.getShipment(cargo);
			}
		} catch (BottlingPlant::Shutdown s) {
			break;
		}

		for (unsigned int i = 0; i < numVendingMachines; i++) {
			VendingMachine* vm = machineList[stocking];
			unsigned int *stock = vm->inventory();
			for (int j = 0; j < VendingMachine::NUM_FLAVOURS; j++) {
				unsigned int openSpace = maxStockPerFlavour - stock[j];
				unsigned int restock = cargo[j] > openSpace ? openSpace : cargo[j];
				cargo[j] -= restock;
				stock[j] += restock;
			}
			stocking = (stocking + 1) % numVendingMachines;
			if (truckEmpty()) {
				break;
			}
		}
	}
}

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour ): prt(prt), nameServer(nameServer), plant(plant),
																			   numVendingMachines(numVendingMachines),
																			   maxStockPerFlavour(maxStockPerFlavour) {
	machineList = nameServer.getMachineList();
}
