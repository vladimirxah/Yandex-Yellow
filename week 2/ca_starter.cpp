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
	string iquery;
	is >> iquery;
	if (iquery.empty()) {
		return is;
	}
	stringstream ss(iquery);
	string type;
	string bus, stop;
	vector<string> stops;
	ss >> type >> bus >> stop;
	while ( !(ss.eof()) )
		{
		string newstop = "";
		ss >> newstop;
		stops.push_back(newstop);
		}
	map< string, QueryType> enumResolver = {{"NewBus", QueryType::NewBus}, {"BusesForStop", QueryType::BusesForStop}, {"StopsForBus", QueryType::StopsForBus}, {"AllBuses", QueryType::AllBuses}};
	q = {enumResolver[type], bus, stop, stops};
	cout << bus << " " << stop << endl;
  return is;
}
//Проверить, павильно ли я написал

struct BusesForStopResponse {
  // Наполните полями эту структуру
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  // Реализуйте эту функцию
  return os;
}

struct StopsForBusResponse {
  // Наполните полями эту структуру
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  // Реализуйте эту функцию
  return os;
}

struct AllBusesResponse {
  // Наполните полями эту структуру
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  // Реализуйте эту функцию
  return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    // Реализуйте этот метод
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    // Реализуйте этот метод
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    // Реализуйте этот метод
  }

  AllBusesResponse GetAllBuses() const {
    // Реализуйте этот метод
  }
};

// Не меняя тела функции main, реализуйте функции и классы выше

/*NEW_BUS bus stop_count stop1 stop2 ... — добавить маршрут автобуса с названием bus и stop_count остановками с названиями stop1, stop2, ...
BUSES_FOR_STOP stop — вывести названия всех маршрутов автобуса, проходящих через остановку stop.
STOPS_FOR_BUS bus — вывести названия всех остановок маршрута bus со списком автобусов, на которые можно пересесть на каждой из остановок.
ALL_BUSES*/
/*ALL_BUSES
BUSES_FOR_STOP Marushkino
STOPS_FOR_BUS 32K
NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo
NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo
BUSES_FOR_STOP Vnukovo
NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo
NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo
STOPS_FOR_BUS 272*/

void TestInOperator (Query& q) {
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
		cout << "Vec stops pass. ";
	} else {
		cout << "Vec stops fail. ";
	}

	/*istringstream is2("BUSES_FOR_STOP Vnukovo");
	is2 >> q;

	istringstream is3("STOPS_FOR_BUS 32K");
	is3 >> q;

	istringstream is4("ALL_BUSES");
	is4 >> q;*/
}


int main() {

	{
		Query qq;
		TestInOperator(qq);
		return 0;
	}

  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
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
