#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  // Реализуйте эту функцию
		string type;
		is >> type;
		map< string, QueryType> enumResolver = {{"NEW_BUS", QueryType::NewBus}, {"BUSES_FOR_STOP", QueryType::BusesForStop}, {"STOPS_FOR_BUS", QueryType::StopsForBus}, {"ALL_BUSES", QueryType::AllBuses}};
		q.type = enumResolver[type];
		string bus, stop;
		vector<string> stops;
		switch (q.type) {
			case QueryType::NewBus:
				is >> bus >> stop;
				for (auto i = 0; i < stoi(stop); ++i)
				{
					string newstop = "";
					is >> newstop;
					stops.push_back(newstop);
				}
				q = {enumResolver[type], bus, stop, stops};
				break;
			case QueryType::BusesForStop:
				{
					string searchstop;
					is >> searchstop;
					q.stop = searchstop;
				}
				break;
			case QueryType::StopsForBus:
				is >> bus;
				q.bus = bus;
				break;
			case QueryType::AllBuses:
				break;
		}
	return is;
}

struct BusesForStopResponse {
  // Наполните полями эту структуру
	vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  // Реализуйте эту функцию
	if (r.buses.empty()) {
		os << "No stop";
	} else {
		for (const string& bus : r.buses) {
			os << bus << " ";
		}
//		os << endl;
	}
  return os;
}

struct StopsForBusResponse {
  // Наполните полями эту структуру
	vector<string> vec;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  // Реализуйте эту функцию
	if (r.vec.empty()) {
		os << "No bus";
	} else {
		for (const string& bus_item : r.vec) {
			os << bus_item << endl;
		}
	}
	return os;
}

struct AllBusesResponse {
  // Наполните полями эту структуру
	vector<string> buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  // Реализуйте эту функцию
	if (r.buses.empty()) {
		os << "No buses";
	} else {
		for (const string& bus_item : r.buses) {
			os << bus_item;
		}
	}
	return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    // Реализуйте этот метод
  	buses_to_stops[bus] = stops;
		vector<string>& stops2 = buses_to_stops[bus];
		for (string& stop : stops2) {
			stops_to_buses[stop].push_back(bus);
//			контрольный вывод
/*			cout << "Add " << bus << " for stop " << stop << endl;*/
		}
//		контрольный вывод
/*		cout << "Added buses for stops:" << endl;
		for (const auto& st : stops_to_buses) {
			cout << st.first << ": ";
			for (const auto& bs : st.second) {
				cout << bs << " ";
			}
			cout << "\n";
		}*/
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    // Реализуйте этот метод
  	BusesForStopResponse stopbuses;
/*  	for (const auto& item : stops_to_buses) {
  		cout << item.first << ": ";
  		for (const auto& bus : item.second) {
  			cout << bus << " ";
  		}
  		cout << endl;
  	}
  	cout << "Size of stops_to_buses is " << stops_to_buses.size() << endl;
  	if (stops_to_buses.count(stop) > 0) {
  		auto s = stops_to_buses.at(stop).size();
  		cout << "Size is " << s << endl;
  	} else {
  		cout << "Count for " << stop << " is 0." << endl;
  		return stopbuses;
  	}*/
  	if (stops_to_buses.count(stop) == 0) return stopbuses;
  	const vector<string>& stbuses = stops_to_buses.at(stop);
//  	cout << stbuses.size() << endl;
		for (const auto& bus : stbuses) {
			stopbuses.buses.push_back(bus);
		}
		return stopbuses;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    // Реализуйте этот метод
  	StopsForBusResponse r;
  	if (buses_to_stops.count(bus) == 0) return r;
		for (const string& stop : buses_to_stops.at(bus)) {
			string line = "";
			line = "Stop " + stop + ": ";
			if (stops_to_buses.at(stop).size() == 1) {
				line.append("no interchange");
			} else {
				for (const string& other_bus : stops_to_buses.at(stop)) {
					if (bus != other_bus) {
						line.append(other_bus + " ");
					}
				}
			}
			r.vec.push_back(line);
		}
		return r;
  }

  AllBusesResponse GetAllBuses() const {
    // Реализуйте этот метод
  	AllBusesResponse allbuses;
  	for (const auto& bus_item : buses_to_stops) {
			string line;
			line = line + "Bus " + bus_item.first + ": ";
			for (const string& stop : bus_item.second) {
//				cout << "next stop is " << stop << " ";
				line = line + stop + " ";
			}
			line.push_back('\n');
//			cout << line << " new line" << endl;
			allbuses.buses.push_back(line);
		}
  	return allbuses;
  }
private:
  map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

/*NEW_BUS bus stop_count stop1 stop2 ... — добавить маршрут автобуса с названием bus и stop_count остановками с названиями stop1, stop2, ...
BUSES_FOR_STOP stop — вывести названия всех маршрутов автобуса, проходящих через остановку stop.
STOPS_FOR_BUS bus — вывести названия всех остановок маршрута bus со списком автобусов, на которые можно пересесть на каждой из остановок.
ALL_BUSES*/

/*
10
ALL_BUSES
BUSES_FOR_STOP Marushkino
STOPS_FOR_BUS 32K
NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo
NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo
BUSES_FOR_STOP Vnukovo
NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo
NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo
STOPS_FOR_BUS 272
ALL_BUSES
*/

/*
4
NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo
NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo
BUSES_FOR_STOP Vnukovo
ALL_BUSES
*/

void TestInOperator () {
	Query q;
	istringstream is1("NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo");
	is1 >> q;
	if (q.type == QueryType::NewBus) {
		cout << "Type pass. ";
	} else {
		cout << "Type fail. ";
	}
	if (q.bus == "32") {
		cout << "Bus pass. ";
	} else {
		cout << "Bus fail. ";
	}
	if (q.stop == "3") {
		cout << "Num stop pass. ";
	} else {
		cout << "Num stop fail. ";
	}
	vector<string> vec = {"Tolstopaltsevo", "Marushkino", "Vnukovo"};
	if (q.stops == vec) {
		cout << "Vec stops pass. " << endl;
	} else {
		cout << "Vec stops fail. " << endl;
	}

	Query q2;
	istringstream is2("BUSES_FOR_STOP Vnukovo");
	is2 >> q2;
	if (q2.type == QueryType::BusesForStop) {
		cout << "Type pass. ";
	} else {
		cout << "Type fail. ";
	}
	if (q2.bus.empty()) {
		cout << "Bus pass. ";
	} else {
		cout << "Bus fail. ";
	}
	if (q2.stop.empty()) {
		cout << "Num stop pass. ";
	} else {
		cout << "Num stop fail. ";
	}
	vector<string> vec2 = {"Vnukovo"};
	if (q2.stops == vec2) {
		cout << "Vec stops pass. " << endl;
	} else {
		cout << "Vec stops fail. " << endl;
	}

/*	istringstream is3("STOPS_FOR_BUS 32K");
	is3 >> q;

	istringstream is4("ALL_BUSES");
	is4 >> q;*/
}


int main() {


  int query_count;
  Query q;

  cin >> query_count;

//  	query_count = 3;
  BusManager bm;
//  stringstream stre("NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo/n NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo/n ALL_BUSES");
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
//  	stre >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
