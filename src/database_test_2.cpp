#include "database_test_2.h"

void TestDbAddPrint() {
  // Add
  {
    Database db;
    Date d(2019, 1, 1);
    db.Add(d, "e1");
    AssertEqual(db.Size(), 1u, "Db Add 1 event");
    ostringstream os, os_db;
    os.str("2019-01-01 e1\n");
    db.Print(os_db);
    AssertEqual(os_db.str(), os.str(), "Db Print 1 event");
  }
  {
    Database db;
    Date d(1, 1, 1);
    db.Add(d, "e1");
    AssertEqual(db.Size(), 1u, "Db Add 0001.01.01 event");
    ostringstream os, os_db;
		os.str("0001-01-01 e1\n");
		db.Print(os_db);
		AssertEqual(os_db.str(), os.str(), "Db Print 0001.01.01 event");
  }
  {
    Database db;
    Date d(0, 1, 1);
    db.Add(d, "e1");
    AssertEqual(db.Size(), 1u, "Db Add 0000.01.01 event");
    ostringstream os, os_db;
		os.str("0000-01-01 e1\n");
		db.Print(os_db);
		AssertEqual(os_db.str(), os.str(), "Db Print 0001.01.01 event");
  }
  {
    Database db;
    Date d(9999, 12, 31);
    db.Add(d, "e1");
    AssertEqual(db.Size(), 1u, "Db Add 9999.12.31 event");
    ostringstream os, os_db;
		os.str("9999-12-31 e1\n");
		db.Print(os_db);
		AssertEqual(os_db.str(), os.str(), "Db Print 9999.12.31 event");
  }
  {
    Database db;
    Date d1(2019, 1, 1);
    Date d2(2019, 1, 2);
    Date d3(2019, 1, 3);
    Date d4(2019, 1, 4);
    Date d5(2019, 1, 5);
    db.Add(d1, "e1");
    db.Add(d2, "e2");
    db.Add(d3, "e3");
    db.Add(d4, "e4");
    db.Add(d5, "e5");
    AssertEqual(db.Size(), 5u, "Db Add 5 event");
    ostringstream os, os_db;
		os.str("\
2019-01-01 e1\n\
2019-01-02 e2\n\
2019-01-03 e3\n\
2019-01-04 e4\n\
2019-01-05 e5\n");
		db.Print(os_db);
		AssertEqual(os_db.str(), os.str(), "Db Print 5 events");
  }
  {
  	srand (time(NULL));
    Database db;
    for (auto i = 0; i < 1000; ++i) {
    	Date di (i, rand()%11+1, rand()%30+1);
    	db.Add(di, "event " + to_string(i));
    }
    AssertEqual(db.Size(), 1000u, "Db Add 1000 random event");
  }
}

void TestDbDublicates() {
	{
	    Database db;
	    Date d(2019, 1, 1);
	    db.Add(d, "e1");
	    db.Add(d, "e1");
	    istringstream is("date == 2019-01-01");
	    auto condition = ParseCondition(is);
	    auto predicate = [condition](const Date& date, const string& event) {
	      return condition->Evaluate(date, event);
	    };
	    AssertEqual(db.FindIf(predicate).size(), 1u, "Db Add Duplicates 1");
	  }
}

void TestAnotherOne () {
	{
		istringstream is("date != 2017-11-18");
		shared_ptr<Node> root = ParseCondition(is);
		Assert(root->Evaluate({2017, 1, 1}, ""), "Parse condition 1");
		Assert(!root->Evaluate({2017, 11, 18}, ""), "Parse condition 2");
	}
}
