#include "config.h"
#include "MPRNG.h"
#include "printer.h"
#include "bank.h"
#include "parent.h"
#include "watcardOffice.h"
#include "groupOff.h"
#include "nameServer.h"
#include "student.h"
#include "bottlingPlant.h"
#include "vendingMachine.h"

#include <sstream>
#include <iostream>
#include <string>
#include <vector>

MPRNG mprng;

// Display correct usage and terminate program
void usage(char *argv[]) {
    std::cerr << "Usage: " << argv[0] << " [ config-file [ random-seed (> 0) ] ]" << std::endl;
    exit(EXIT_FAILURE); // TERMINATE
}

bool convert(int &val, char *buffer) {              // convert C string to integer
    std::stringstream ss(buffer);                        // connect stream and buffer
    ss >> std::dec >> val;                               // convert integer from buffer
    return ! ss.fail() &&                           // conversion successful ?
    // characters after conversion all blank ?
    std::string(buffer).find_first_not_of(" ", ss.tellg()) == std::string::npos;
}

void uMain::main() {
	int seed = getpid();
	char fileName[100] = "soda.config";
    switch(argc){
	    case 3:
	        if (!convert(seed, argv[2]) || seed <= 0) {               // invalid integer ?
	            usage(argv);
	        }
	    case 2:
	    	strcpy(fileName,argv[1]);
		case 1:
			break;
	    default:
	        usage(argv);
    }
	ConfigParms cparms;
    processConfigFile(fileName, cparms);
    {
        Printer prt(cparms.numStudents, cparms.numVendingMachines, cparms.numCouriers);
        Bank bank(cparms.numStudents);
        Parent parent(prt, bank, cparms.numStudents, cparms.parentalDelay);
        WATCardOffice* cardOffice = new WATCardOffice(prt, bank, cparms.numCouriers);
        Groupoff groupoff(prt, cparms.numStudents, cparms.sodaCost, cparms.groupoffDelay);
        NameServer nameServer(prt, cparms.numVendingMachines, cparms.numStudents);
        std::vector<VendingMachine*> vendingMachines;
        for (unsigned int i = 0; i < cparms.numVendingMachines; i++) {
        	vendingMachines.push_back(new VendingMachine(prt, nameServer, i, cparms.sodaCost,
                        								 cparms.maxStockPerFlavour));
        }

        BottlingPlant *bottlingPlant = new BottlingPlant(prt, nameServer, cparms.numVendingMachines,
                     									 cparms.maxShippedPerFlavour, 
                     									 cparms.maxStockPerFlavour, 
                     									 cparms.timeBetweenShipments);

        std::vector<Student*> students;
        for (unsigned int i = 0; i < cparms.numStudents; i++) {
        	students.push_back(new Student(prt, nameServer, *cardOffice, groupoff, i, 
        								   cparms.maxPurchases));
        }
    		
    	for (unsigned int i = 0; i < cparms.numStudents; i++) {
        	delete students[i];
        }

        delete bottlingPlant;

        for (unsigned int i = 0; i < cparms.numVendingMachines; i++) {
            delete vendingMachines[i];
        }
        
        delete cardOffice;
    }
    std::cout << "***********************" << std::endl;
    return;
}