#include "printer.h"

//enum Kind { Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };

void Printer::resetCellDetails() {
    for (unsigned int i = 0; i < numTotalCells; i++) {
        cells[i].set = false;
    }
}

void Printer::printParent() {
	cout << cells[Parent].state;
	if (cells[Parent].state == 'D') {
		cout << " " << value1 << "," << value2;
	}
	cout << "\t";
}

void Printer::printGroupoff() {
	cout << cells[Groupoff].state;
	if (cells[Groupoff].state == 'D') {
		cout << " " << value1;
	}
	cout << "\t";
}

void Printer::printWATOff() {
	cout << cells[WATCardOffice].state;
	if (cells[WATCardOffice].state == 'C' || cells[WATCardOffice].state == 'T') {
		cout << " " << value1 << "," << value2;
	}
	cout << "\t";
}

void Printer::printNameServer() {
	cout << cells[NameServer].state;
	if (cells[NameServer].state == 'R') {
		cout << " " << value1;
	} else if (cells[NameServer].state == 'N') {
		cout << " " << value1 << "," << value2;
	}
	cout << "\t";
}

void Printer::printTruck() {
	cout << cells[Truck].state;
	if (cells[Truck].state == 'P') {
		cout << " " << value1;
	} else if (cells[Truck].state == 'd' || 
				cells[Truck].state == 'U'  || 
				cells[Truck].state == 'D' ) {
		cout << " " << value1 << "," << value2;
	}
	cout << "\t";
}

void Printer::printBottlingPlant() {
	cout << cells[BottlingPlant].state;
	if (cells[BottlingPlant].state == 'G') {
		cout << " " << value1;
	}
	cout << "\t";
}

void Printer::printStudent(unsigned int id) {
	cout << cells[id].state;
	if (cells[id].state == 'V' || cells[id].state == 'G' || cells[id].state == 'B') {
		cout << " " << value1;
	} else if (cells[id].state == 'S') {
		cout << " " << value1 << "," << value2;
	}
	cout << "\t";
}

void Printer::printVending(unsigned int id) {
	cout << cells[id].state;
	if (cells[id].state == 'S') {
		cout << " " << value1;
	} else if (cells[id].state == 'B') {
		cout << " " << value1 << "," << value2;
	}
	cout << "\t";
}

void Printer::printCourier(unsigned int id) {
	cout << cells[id].state;
	if (cells[id].state == 't' || cells[id].state == 'T') {
		cout << " " << value1 << "," << value2;
	}
	cout << "\t";
}

void Printer::printCell(unsigned int id) {
    if (id <= BottlingPlant) {
    	switch (id) {
    		case Parent:
    			printParent();
    			break;
    		case Groupoff:
    			printGroupoff();
    			break;
    		case WATCardOffice:
    			printWATOff();
    			break;
    		case NameServer:
    			printNameServer();
    			break;
    		case Truck:
    			printTruck();
    			break;
    		case BottlingPlant:
    			printBottlingPlant();
    			break;
    		default:
    			break;
    	}
    } else if (id <= BottlingPlant + numStudents) {
    	printStudent(id);
    } else if (id <= BottlingPlant + numStudents + numVendingMachines) {
    	printVending(id);
    } else {
    	printCourier(id);
    }
}

void Printer::flushLine(bool finished) {
    for (unsigned int i = 0; i < numTotalCells; i++) {
        if (cells[i].set || (finished && cells[i].state == 'F')) { 
            printCell(i);
        } else if (finished) {
            cout << "...\t";
        }
    }
    cout << endl;
    resetCellDetails();
}

Printer::Printer(unsigned int numStudents, unsigned int numVendingMachines,
				unsigned int numCouriers) :
				numStudents(numStudents),
				numVendingMachines(numVendingMachines),
				numCouriers(numCouriers) {
	numTotalCells = Student + numStudents + numCouriers + numVendingMachines;
    cout << "Parent\tGroupoff\tWATOff\tNames\tTruck\tPlant\t";
    
    cells.push_back(Cell(Parent));
    cells.push_back(Cell(Groupoff));
    cells.push_back(Cell(WATOff));
    cells.push_back(Cell(Names));
    cells.push_back(Cell(Truck));
    cells.push_back(Cell(Plant));

    for (unsigned int i = 0; i < numStudents; i++){
        cout << "Stud" << i << "\t";
        cells.push_back(Cell(Student));
    }

    for (unsigned int i = 0; i < numVendingMachines; i++){
        cout << "Mach" << i << "\t";
        cells.push_back(Cell(Vending));
    }

    for (unsigned int i = 0; i < numCouriers; i++){
        cout << "Cour" << i << "\t";
        cells.push_back(Cell(Courier));
    }
	cout << endl;
    
    for (unsigned int i = 0; i < numTotalCells; i++) {
        cout << "*******\t";
    }
    cout << endl;
}

void Printer::print(Kind kind, char state) {
	if (state == 'F') flushLine(false);
	cells[kind].set = true;
	cells[kind].state = state;
	if (state == 'F') flushLine(true);
}

void Printer::print(Kind kind, char state, int value1) {
	print(kind, state);
	cells[kind].value1 = value1;
}

void Printer::print(Kind kind, char state, int value1, int value2) {
	print(kind, state, value1);
	cells[kind].value2 = value2;	
}

unsigned int Printer::getIdx(Kind kind, unsigned int lid) {
	if (kind == Student) {
		return Student + lid;
	} else if (kind == Vending) {
		return Student + numStudents + lid;
	} else {
		return Student + numStudents + numVendingMachines + lid;
	}
}

// Students, Vending Machines, and Couriers
void Printer::print(Kind kind, unsigned int lid, char state) {
	unsigned int idx = getIdx(kind, lid);
	if (state == 'F') flushLine(false);
	cells[idx].set = true;
	cells[idx].state = state;
	if (state == 'F') flushLine(true);
}

void Printer::print(Kind kind, unsigned int lid, char state, int value1) {
	print(kind, lid, state);
	cells[getIdx(kind, lid)].value1 = value1;
}

void Printer::print(Kind kind, unsigned int lid, char state, int value1, int value2) {
	print(kind, lid, state, value1);
	cells[getIdx(kind, lid)].value2 = value2;
}
