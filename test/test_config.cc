#include "../config.h"

#include <iostream>

void uMain::main() {
	ConfigParms parms;
	processConfigFile("../soda.config", parms);
	std::cout << parms.sodaCost << std::endl;
	std::cout << parms.numStudents << std::endl;
	std::cout << parms.maxPurchases << std::endl;
	std::cout << parms.numVendingMachines << std::endl;
	std::cout << parms.maxStockPerFlavour << std::endl;
	std::cout << parms.maxShippedPerFlavour << std::endl;
	std::cout << parms.timeBetweenShipments << std::endl;
	std::cout << parms.groupoffDelay << std::endl;
	std::cout << parms.parentalDelay << std::endl;
	std::cout << parms.numCouriers << std::endl;
	return;
}

// u++ -o test_config.out test_config.cc ../config.o
