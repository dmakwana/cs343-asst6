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
	prt.print(Printer::Truck, 'S');
	while(true) {
		yield(mprng(1,10));
		unsigned int totalSodas = 0;
		try {
			_Enable {
				plant.getShipment(cargo);
				for (unsigned int i = 0; i < VendingMachine::NUM_FLAVOURS; i++) {
					totalSodas += cargo[i];
				}
				prt.print(Printer::Truck, 'P', totalSodas);
			}
		} catch (BottlingPlant::Shutdown s) {
			break;
		}

		for (unsigned int i = 0; i < numVendingMachines; i++) {
			unsigned int notReplenished = 0;
			prt.print(Printer::Truck, 'd', i, totalSodas);
			VendingMachine* vm = machineList[stocking];
			unsigned int *stock = vm->inventory();
			for (int j = 0; j < VendingMachine::NUM_FLAVOURS; j++) {
				unsigned int openSpace = maxStockPerFlavour - stock[j];
				unsigned int restock = cargo[j] > openSpace ? openSpace : cargo[j];
				if (restock != openSpace) {
					notReplenished += openSpace - restock;
				}
				cargo[j] -= restock;
				totalSodas -= restock;
				stock[j] += restock;
			}
			if (notReplenished) {
				prt.print(Printer::Truck, 'U', i, notReplenished);
			}
			prt.print(Printer::Truck, 'D', i, totalSodas);
			stocking = (stocking + 1) % numVendingMachines;
			if (truckEmpty()) {
				break;
			}
		}
	}
	prt.print(Printer::Truck, 'F');
}

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour ): prt(prt), nameServer(nameServer), plant(plant),
																			   numVendingMachines(numVendingMachines),
																			   maxStockPerFlavour(maxStockPerFlavour) {
	machineList = nameServer.getMachineList();
}
