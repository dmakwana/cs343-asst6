#include "bottlingPlant.h"
#include "printer.h"
#include "nameServer.h"
#include "MPRNG.h"
#include "truck.h"

extern MPRNG mprng;

void BottlingPlant::main() {
	// Begin by creating truck
	prt.print(Printer::BottlingPlant, 'S');
	Truck truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour);
	for (;;) {
		// Perform the production run
		unsigned int totalSodas = 0;
		for (unsigned int i = 0; i < VendingMachine::NUM_FLAVOURS; i++) {
			productionRun[i] = mprng(maxShippedPerFlavour);
			totalSodas += productionRun[i];
		}
		// prt.print(Printer::BottlingPlant, 'G', totalSodas);

		yield(timeBetweenShipments);
		// Wait for truck to pick up the production run before starting new one
		_Accept(~BottlingPlant) {
			plantShuttingDown = true;
			_Accept(getShipment) {}
			break;
		} or _Accept(getShipment) {
			// prt.print(Printer::BottlingPlant, 'P');
		}
	}
	prt.print(Printer::BottlingPlant, 'F');
}

BottlingPlant::BottlingPlant(Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
            				unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
            				unsigned int timeBetweenShipments ) :
							prt(prt), nameServer(nameServer), 
							numVendingMachines(numVendingMachines),
							maxShippedPerFlavour(maxShippedPerFlavour),
							maxStockPerFlavour(maxStockPerFlavour),
							timeBetweenShipments(timeBetweenShipments),
							plantShuttingDown(false) {}

void BottlingPlant::getShipment(unsigned int cargo[]) {
	if (plantShuttingDown) {
		_Resume Shutdown() _At uThisTask();
	} else {
		for (unsigned int j = 0; j < VendingMachine::NUM_FLAVOURS; j++) {
			cargo[j] = productionRun[j];
		}
	}
}
