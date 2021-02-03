#pragma once
#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#define PRINT(x) std::cout << x << std::endl

/*
	 1 -> represent the wall
	 0 -> represent there is no obstacle
	 2 -> represent the exit
*/

class Map {
private:
	std::vector<int> _map;
	std::vector<int> _traps;
	int _column, _line, _exit, _start, _numberTraps, _numberWalls;

public:
	Map() : _column(0), _line(0), _start(0), _exit(0), _numberTraps(0), _numberWalls(0) {};

	Map(const Map& m) :_numberWalls(m._numberWalls), _column(m._column), _line(m._line), _exit(m._exit), _start(m._start), _numberTraps(m._numberTraps){
		this->_map = m._map;
		this->_traps = m._traps;
	};

	Map(int column, int line, int start, int exit, int numberTraps, int numberWalls) : _column(column), _line(line), _start(start), _exit(exit), _numberTraps(numberTraps), _numberWalls(numberWalls){};

	void setColumn(int column) {
		this->_column = column;
	}

	void setLine(int line) {
		this->_line = line;
	}

	void setNumberTraps(int numberTraps) {
		this->_numberTraps = numberTraps;
	}

	void setStart(int start) {
		this->_start = start;
	}

	void setNumberWalls(int numberWalls) {
		this->_numberWalls = numberWalls;
	}

	void setTraps(const std::vector<int> traps) {
		this->_traps = traps;
	}

	void setMap(const std::vector<int> map) {
		this->_map = map;
	}

	void setExit(int exit) {
		_exit = exit;
	}

	int getExit() const {
	return this->_exit;
	}

	int getStart() const {
		return this->_start;
	}

	int getLine() const {
		return this->_line;
	}

	int getColumn() const {
		return this->_column;
	}

	int getStart() {
		return this->_start;
	}

	int getExit() {
		return this->_exit;
	}

	int getLine() {
		return this->_line;
	};

	int getColumn() {
		return this->_column;
	}

	std::vector<int> getMap() const {
		return this->_map;
	}

	std::vector<int> getTraps() const {
		return this->_traps;
	}

	void createWalls();

	void createMap();

	void createTraps();

	bool mapHasAnExit();

	void cls();
};
