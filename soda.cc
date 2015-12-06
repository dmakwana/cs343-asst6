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

using std::cerr;
using std::endl;
using std::stringstream;
using std::dec;
using std::string;
using std::vector;

MPRNG mprng;

// Display correct usage and terminate program
void usage(char *argv[]) {
    cerr << "Usage: " << argv[0] << " [ config-file [ random-seed (> 0) ] ]" << endl;
    exit(EXIT_FAILURE); // TERMINATE
}

bool convert(int &val, char *buffer) {              // convert C string to integer
    stringstream ss(buffer);                        // connect stream and buffer
    ss >> dec >> val;                               // convert integer from buffer
    return ! ss.fail() &&                           // conversion successful ?
    // characters after conversion all blank ?
    string(buffer).find_first_not_of(" ", ss.tellg()) == string::npos;
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

    Printer prt(cparms.numStudents, cparms.numVendingMachines, cparms.numCouriers);
    Bank bank(cparms.numStudents);
    Parent parent(prt, bank, cparms.numStudents, cparms.parentalDelay);
    WATCardOffice cardOffice(prt, bank, cparms.numCouriers);
    Groupoff groupoff(prt, cparms.numStudents, cparms.sodaCost, cparms.groupoffDelay);
    NameServer nameServer(prt, cparms.numVendingMachines, cparms.numStudents);

    vector<VendingMachine*> vendingMachines;
    for (unsigned int i = 0; i < cparms.numVendingMachines; i++) {
    	vendingMachines.push_back(new VendingMachine(prt, nameServer, i, cparms.sodaCost,
                    								 cparms.maxStockPerFlavour));
    }

    BottlingPlant *bottlingPlant = new BottlingPlant(prt, nameServer, cparms.numVendingMachines,
                 									 cparms.maxShippedPerFlavour, 
                 									 cparms.maxStockPerFlavour, 
                 									 cparms.timeBetweenShipments);

    vector<Student*> students;
    for (unsigned int i = 0; i < cparms.numStudents; i++) {
    	students.push_back(new Student(prt, nameServer, cardOffice, groupoff, i, 
    								   cparms.maxPurchases));
    }
		
	for (unsigned int i = 0; i < cparms.numStudents; i++) {
    	delete students[i];
    }

    delete bottlingPlant;

    std::cout << "***********************" << std::endl;
    return;
}