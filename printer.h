#pragma once

_Monitor Printer {
	struct Cell {
		Cell(Kind kind) : 
			set(false), kind(kind), state('x'), value1(value1), value2(value2) {}
		bool set;
		Kind kind;
		char state;
		unsigned int id;
		int value;
		int value2;
	};
	vector<Cell> cells;
	unsigned int numStudents;
	unsigned int numVendingMachines;
	unsigned int numCouriers;
	unsigned int numTotalCells;
	void resertCellDetails();
	void printCell();
	void flushLine();
	unsigned int getIdx();
  public:
    enum Kind { Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers);
    void print(Kind kind, char state);
    void print(Kind kind, char state, int value1);
    void print(Kind kind, char state, int value1, int value2);
    void print(Kind kind, unsigned int lid, char state);
    void print(Kind kind, unsigned int lid, char state, int value1);
    void print(Kind kind, unsigned int lid, char state, int value1, int value2);
};
