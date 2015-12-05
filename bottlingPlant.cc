#include "printer.h"
#include "nameServer.h"
#include "mprng.h"

void BottlingPlant::main() {
	
}

_Event BottlingPlant::Shutdown {};                    // shutdown plant

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
             unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
             unsigned int timeBetweenShipments ) :
	prt(prt), nameServer(nameServer), numVendingMachines(numVendingMachines),
	maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour),
	timeBetweenShipments(timeBetweenShipments) {}

void BottlingPlant::getShipment(unsigned int cargo[]) {

}
