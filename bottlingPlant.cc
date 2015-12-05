#include "printer.h"
#include "nameServer.h"
#include "mprng.h"
#include "truck.h"

void BottlingPlant::main() {
	// Begin by creating truck
	Truck truck = Truck(prt, nameServer, self, numVendingMachines, maxStockPerFlavour);
	for (;;) {
		// Perform the production run
		for (unsigned int i = 0; i < NUM_FLAVOURS; i++) {
			productionRun[i] = mprng(MaxShippedPerFlavour);
		}
		yield(TimeBetweenShipments);
		// Wait for truck to pick up the production run before starting new one
		_Accept(~BottlingPlant) {
			plantShuttingDown = true;
			_Accept(getShipment) {}
			break;
		} or _Accept(getShipment) {}
	}
}

BottlingPlant::BottlingPlant(Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
            				unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
            				unsigned int timeBetweenShipments ) :
							prt(prt), nameServer(nameServer), 
							numVendingMachines(numVendingMachines),
							maxShippedPerFlavour(maxShippedPerFlavour),
							maxStockPerFlavour(maxStockPerFlavour)
							timeBetweenShipments(timeBetweenShipments),
							plantShuttingDown(false) {}

void BottlingPlant::getShipment(unsigned int cargo[]) {
	if (plantShuttingDown) {
		_Throw Shutdown;
	} else {
		unsigned int i = 0;
		for (unsigned int j = 0; j < NUM_FLAVOURS; j++) {
			for (unsigned int k = 0; k < productionRun[j]; k++, i++){
				cargo[i] = j;
			}
		}
	}
}
