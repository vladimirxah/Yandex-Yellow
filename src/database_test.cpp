#include "database_test.h"

string ParseEvent(istream& is) {
	while (is.peek() == ' ') { // skip spaces
		is.get();
	}
	string str;
	getline(is, str);
	return str;
}

void TestDatabase() {
  istringstream empty_is("");
  auto empty_condition = ParseCondition(empty_is);
  auto empty_predicate = [empty_condition](const Date& date, const string& event) {
    return empty_condition->Evaluate(date, event);
  };

  // Add 2 - Del 1 - Add deleted again
//  cout << "Add 2 - Del 1 - Add deleted again" << endl;

  try {
		Database db;
		Date d(2019, 1, 1);
		db.Add(d, "e1");
		db.Add(d, "e2");
//		cout << "Debug print start DB\n";
//    db.Print(cout);
		istringstream is(R"(event == "e1")");
		auto condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const string& event) {
			return condition->Evaluate(date, event);
		};
		AssertEqual(db.RemoveIf(predicate), 1, "Db Add2-Del-Add 1");
//		cout << "Debug print DB sfter deletion of e1\n";
//		db.Print(cout);
		AssertEqual(db.Size(), 1u, "Size of Db must be 1 after 1e deleted from it");
		db.Add(d, "e1");
		AssertEqual(db.FindIf(empty_predicate).size(), 2u, "Db Add2-Del-Add 2");
//		cerr << "Add 2 - Del 1 - Add deleted again" << " OK" << endl;
	} catch (runtime_error& e) {
//		cerr << "Add 2 - Del 1 - Add deleted again" << " fail: " << e.what() << endl;
		throw runtime_error("Add 2 - Del 1 - Add deleted again fail.");
	}

  // Last
  {
    Database db;
    Date d(2019, 1, 1);
    Date d1(2019, 1, 2);
    Date d2(2018, 12, 22);
    db.Add(d1, "e1");
    db.Add(d2, "e2");
    db.Add(d2, "e2");
    AssertEqual(db.Last(d), "2018-12-22 e2", "Db Last 1");
//    cerr << "Db Last 1 OK" << endl;
    Date d3(2018, 12, 24);
    db.Add(d3, "e3");
    AssertEqual(db.Last(d), "2018-12-24 e3", "Db Last 2");
//    cerr << "Db Last 2 OK" << endl;

    // Get last event for date before first event 
    try {
      Date d4(2017, 2, 2);
      db.Last(d4);
      Assert(true, "Db Last 3");
    } catch (invalid_argument &e) {
//    	cerr << e.what() << endl;
    	// Pass
    }

    // Delete event and get last
//    cerr << "Test Delete event and get last" << endl;
    istringstream is("date == 2018-12-24");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };    
    db.RemoveIf(predicate);
//    db.Print(cout);
    AssertEqual(db.Last(d), "2018-12-22 e2", "Db Last 4");
//    AssertEqual(db.Last(d), make_pair<Date,string>({2018,12,22}, "e2"), "Db Last 4");

    AssertEqual(db.Last(d1), "2019-01-02 e1", "Db Last 5");
//    AssertEqual(db.Last(d1), make_pair<Date,string>({2019,01,02}, "e1"), "Db Last 5");
    db.Add(d2, "e4");
    AssertEqual(db.Last(d2), "2018-12-22 e4", "Db Last 6");
//    AssertEqual(db.Last(d2), make_pair<Date,string>({2018,12,22}, "e4"), "Db Last 6");
  }

  // Del
  {
//  	cerr << "Test db Del" << endl;
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is("date == 2018-01-07");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };    
    AssertEqual(db.RemoveIf(predicate), 2, "Db Del 1");
  }
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is("date >= 2018-01-07 AND date <= 2020-01-01");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };    
    AssertEqual(db.RemoveIf(predicate), 4, "Db Del 2");
  }
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    AssertEqual(db.RemoveIf(empty_predicate), 4, "Db Del 3");
  }
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is(R"(event == "e1")");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };    
    AssertEqual(db.RemoveIf(predicate), 1, "Db Del 4");
  }

  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is(R"(event == "e1" OR date == 2019-01-01)");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };    
    AssertEqual(db.RemoveIf(predicate), 2, "Db Del 5");
  }

  // Find
  {
//  	cerr << "Test db Find" << endl;
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is("date == 2018-01-07");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };    
    AssertEqual(db.FindIf(predicate).size(), 2u, "Db Find 1");
  }
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is("date >= 2018-01-07 AND date <= 2020-01-01");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };    
    AssertEqual(db.FindIf(predicate).size(), 4u, "Db Find 2");
  }
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    AssertEqual(db.FindIf(empty_predicate).size(), 4u, "Db Find 3");
  }
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is(R"(event == "e1")");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };    
    AssertEqual(db.FindIf(predicate).size(), 1u, "Db Find 4");
  }

  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is(R"(event == "e1" OR date == 2019-01-01)");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };    
    AssertEqual(db.FindIf(predicate).size(), 2u, "Db Find 5");
  }

  // Add - Del - Add - Del
  {
//  	cerr << "Add - Del - Add - Del" << endl;
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    AssertEqual(db.RemoveIf(empty_predicate), 2, "Db Add-Del-Add-Del 1");

    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    AssertEqual(db.RemoveIf(empty_predicate), 2, "Db Add-Del-Add-Del 1");
  }

  {                                       // всего понемногу
          Database db;
          istringstream is, iss, is5;

          //------------------------------------------------------
          //                     Add
          //------------------------------------------------------
//          cerr << "Test db Add 2" << endl;
          is.str("\
  Add 2017-11-21 Tuesday\n\
  Add 2017-11-20 Monday\n\
  Add 2017-11-21 Weekly meeting\n");

          for(int i = 0; i < 3; i++)
          {
              string command;
              is >> command;

              const auto date = ParseDate(is);
              const auto event = ParseEvent(is);
              db.Add(date, event);
          }

         //------------------------------------------------------
         //                     find
         //------------------------------------------------------
//          cerr << "Test db Find 2" << endl;
         is.str("Find event != \"Weekly meeting\"\n");
          string command;
          is >> command;

         auto condition = ParseCondition(is);
         auto predicate = [condition](const Date& date, const string& event){
             return condition->Evaluate(date, event);
         };

         auto entries3 = db.FindIf(predicate);
         string end_ = "Found 2 entries";
         entries3.push_back(end_);
         vector<string> b = {"2017-11-20 Monday", "2017-11-21 Tuesday", "Found 2 entries"};
         AssertEqual(entries3, b, "Parse find 05");

         //------------------------------------------------------
                   //                        Last
                   //------------------------------------------------------
                   is5.str("Last 2017-11-20\n");
                   string command3;
                   is5 >> command3;
         //          string d_date = ParseDate(is5).Str();
         //          cout << is5.str();
//                   db.Print(cout);
                   auto tmp4 = db.Last(ParseDate(is5));
                   AssertEqual(tmp4, "2017-11-20 Monday", "Parse Last 07");
//                   cerr << "Last 2 Ok" << endl;

         //------------------------------------------------------
         //                        Del
         //------------------------------------------------------
//         cerr << "Test db Del 2" << endl;
         is.str("Del date > 2017-11-20\n");
         string command2;
         is >> command2;

         auto condition2 = ParseCondition(is);
         auto predicate3 = [condition2](const Date& date, const string& event){
             return condition2->Evaluate(date, event);
         };

          int count = db.RemoveIf(predicate3);
          string tmp3 = "Removed " + to_string(count) + " entries";

          AssertEqual(tmp3, "Removed 3 entries", "Parse Del 06");


      }

  // test for 14/19
	{
//		cerr << "Start new test for 14-19 case ";
		Database db;
		istringstream is, iss, is5;
		is.str("\
			Add 1-1-1 aa\n\
			Add 1-1-1 a\n\
			Add 1-1-1 aaa\n\
			Add 1-1-1 aaaa\n");

		for(int i = 0; i < 4; i++)
		{
			string command;
			is >> command;

			const auto date = ParseDate(is);
			const auto event = ParseEvent(is);
			db.Add(date, event);
		}

		is.str("Del event >= \"aaa\"");
		string command2;
		is >> command2;

		auto condition2 = ParseCondition(is);
		auto predicate3 = [condition2](const Date& date, const string& event){
			 return condition2->Evaluate(date, event);
		};

		int count = db.RemoveIf(predicate3);
		string tmp3 = "Removed " + to_string(count) + " entries";
		AssertEqual(tmp3, "Removed 2 entries", "Parse 14-19 test");

		ostringstream os1;
		db.Print(os1);
		auto strtmp = os1.str();
		AssertEqual(strtmp, "0001-01-01 aa\n\
0001-01-01 a\n", "Print aa-a-aaa-aaaa after Del");
//		cerr << "OK" << endl;

  }

}

void TestDateParse()
{
	Database db;
	istringstream is;
	is.str("\
		Add 1-1-1 a\n\
		Add 1-1-2 aa\n\
		Add 1-1-3 aaa\n\
		Add 1-1-4 aaaa\n");

	for(int i = 0; i < 4; i++)
	{
		string command;
		is >> command;

		const auto date = ParseDate(is);
		const auto event = ParseEvent(is);
		db.Add(date, event);
	}
//		Find date
	{
		is.clear();
		is.str("date < 1-1-2");
		auto condition = ParseCondition(is);
		auto predicate0 = [condition](const Date& date, const string& event){
			 return condition->Evaluate(date, event);
		};
		AssertEqual(db.FindIf(predicate0), vector<string> {"0001-01-01 a"}, "Parse date < 1-1-2");

		is.clear();
		is.str("date == 1-1-2");
		condition = ParseCondition(is);
		auto predicate1 = [condition](const Date& date, const string& event){
			 return condition->Evaluate(date, event);
		};
		AssertEqual(db.FindIf(predicate1), vector<string> {"0001-01-02 aa"}, "Parse date == 1-1-2");

		is.clear();
		is.str("date > 1-1-2");
		condition = ParseCondition(is);
		auto predicate2 = [condition](const Date& date, const string& event){
			 return condition->Evaluate(date, event);
		};
		AssertEqual(db.FindIf(predicate2), vector<string> {"0001-01-03 aaa", "0001-01-04 aaaa"}, "Parse date > 1-1-2");
	}
//		RemoveIf date
	{
		Database db1;
		db1 = db;
		is.clear();
		is.str("date < 1-1-2");
		auto condition = ParseCondition(is);
		auto predicate0 = [condition](const Date& date, const string& event){
			 return condition->Evaluate(date, event);
		};
		db1.RemoveIf(predicate0);
		ostringstream os1;
		db1.Print(os1);
		auto strtmp = os1.str();
		AssertEqual(strtmp, "0001-01-02 aa\n\
0001-01-03 aaa\n\
0001-01-04 aaaa\n", "RemoveIf date < 1-1-2");
	}
	{
		Database db1;
		db1 = db;
		is.clear();
		is.str("date < 1-1-2 OR date > 1-1-3");
		auto condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const string& event){
			 return condition->Evaluate(date, event);
		};
		db1.RemoveIf(predicate);
		ostringstream os2;
		db1.Print(os2);
		auto strtmp = os2.str();
		AssertEqual(strtmp, "0001-01-02 aa\n\
0001-01-03 aaa\n", "RemoveIf date < 1-1-2 OR date > 1-1-3");
	}
	{
		Database db1;
		db1 = db;
		is.clear();
		is.str("date > 1-1-1 AND date < 1-1-4");
		auto condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const string& event){
			 return condition->Evaluate(date, event);
		};
		db1.RemoveIf(predicate);
		ostringstream os2;
		db1.Print(os2);
		auto strtmp = os2.str();
		AssertEqual(strtmp, "0001-01-01 a\n\
0001-01-04 aaaa\n", "date > 1-1-1 AND date < 1-1-4");
	}
	//		Find date and event
		{
			is.clear();
			is.str("date < 1-1-4 AND event == \"a\"");
			auto condition = ParseCondition(is);
			auto predicate0 = [condition](const Date& date, const string& event){
				 return condition->Evaluate(date, event);
			};
			AssertEqual(db.FindIf(predicate0), vector<string> {"0001-01-01 a"}, "date < 1-1-4 AND event == \"a\"");
		}
		is.clear();
		is.str("\
			Add 1-1-1 aa1\n\
			Add 1-1-1 a2\n\
			Add 1-1-1 aaa3\n\
			Add 1-1-1 aaaa4\n\
			Add 1-1-2 aaa1\n");

		for(int i = 0; i < 4; i++)
		{
			string command;
			is >> command;

			const auto date = ParseDate(is);
			const auto event = ParseEvent(is);
			db.Add(date, event);
		}

		{
			is.clear();
			is.str("date < 1-1-2");
			auto condition = ParseCondition(is);
			auto predicate0 = [condition](const Date& date, const string& event){
				 return condition->Evaluate(date, event);
			};
			AssertEqual(db.FindIf(predicate0),
									vector<string> {"0001-01-01 a", "0001-01-01 aa1", "0001-01-01 a2", "0001-01-01 aaa3", "0001-01-01 aaaa4"},
									"Parse date < 1-1-2 after added events");
		}
		{
				Database db1;
				db1 = db;
				is.clear();
				is.str("event == \"aa1\" OR event == \"aa\"");
				auto condition = ParseCondition(is);
				auto predicate = [condition](const Date& date, const string& event){
					 return condition->Evaluate(date, event);
				};
				db1.RemoveIf(predicate);
				is.clear();
				is.str("date < 1-1-2");
				auto condition0 = ParseCondition(is);
				auto predicate0 = [condition0](const Date& date, const string& event){
					 return condition0->Evaluate(date, event);
				};
				AssertEqual(db1.FindIf(predicate0),
										vector<string> {"0001-01-01 a", "0001-01-01 a2", "0001-01-01 aaa3", "0001-01-01 aaaa4"},
										"Parse date < 1-1-2 after added and removed events");

				ostringstream os2;
				db1.Print(os2);
				auto strtmp = os2.str();
				AssertEqual(strtmp, "0001-01-01 a\n\
0001-01-01 a2\n\
0001-01-01 aaa3\n\
0001-01-01 aaaa4\n\
0001-01-03 aaa\n\
0001-01-04 aaaa\n", "Print after RemoveIf date < 1-1-2 OR date > 1-1-3");
			}
			{
				Database db;
				db.Add({2017, 1, 1}, "first");
				db.Add({2017, 1, 1}, "second");
				db.Add({2017, 1, 1}, "third");
				db.Add({2017, 1, 1}, "fourth");
				db.Add({2017, 1, 1}, "five");

				is.clear();
				is.str(R"(event == "second" OR event == "fourth")");
				auto condition = ParseCondition(is);
				auto predicate = [condition](const Date& date, const string& event){
					 return condition->Evaluate(date, event);
				};
				AssertEqual(2, db.RemoveIf(predicate), "Remove several");

				ostringstream os2;
				db.Print(os2);
				auto strtmp = os2.str();
				AssertEqual(strtmp, "2017-01-01 first\n\
2017-01-01 third\n\
2017-01-01 five\n", "Check print after remove several-1");

				db.Add({2017, 1, 1}, "second");
				db.Add({2017, 1, 1}, "second");
				db.Add({2017, 1, 1}, "New Year");
				os2.str("");
				os2.clear();
				db.Print(os2);
				strtmp = os2.str();
				AssertEqual(strtmp, "2017-01-01 first\n\
2017-01-01 third\n\
2017-01-01 five\n\
2017-01-01 second\n\
2017-01-01 New Year\n", "Check print after remove several-2");
//				AssertEqual(2, DoRemove(db, R"(event == "second" OR event == "fourth")"), "Remove several");
//				AssertEqual("2017-01-01 first\n2017-01-01 third\n2017-01-01 five\n", DoPrint(db), "Check print after remove several- 3");

			}
}

void TestVGBase()
{
	{
					Database db;
					istringstream is;
					is.str("\
	Add 0001-01-21 monday\n\
	Add 0001-01-01 Start of time\n\
	Add 0001-01-01 Creation of sun\n\
	Add 0001-01-01 other 8 planets\n\
	Add 0001-01-02 Earth\n\
	Add 0001-01-02 our Moon\n\
	Add 0001-01-21 tuesday\n\
	Add 0001-01-02 pangeya\n\
	Add 0001-01-02 sea\n\
	Add 9999-12-31 fixing seeing\n\
	Add 9999-12-31 try to cath a star\n\
	Add 9999-12-31 burn it\n\
	Add 9999-12-31 trashtodel\n\
	Add 0001-01-21 wendsday\n\
	Add 9999-12-31 cant burn it :(\n\
	Add 0001-11-01 aabbcc\n\
	Add 0001-11-01 bbccdd\n\
	Add 0001-11-01 aaaacc\n\
	Add 9999-12-31 end of Time\n\
	Add 9999-12-31 event-to-del\n\
	Add 0001-01-21 thursday\n\
	Add 1986-03-20 March of eighty six\n\
	Add 1986-03-31 last day of march\n\
	Add 1986-03-31 some new event\n\
	Add 0001-01-21 friday\n\
	Add 1986-03-31 and2\n\
	Add 1986-03-31 some7\n\
	Add 1986-03-31 kind of\n\
	Add 1986-03-31 end of thirty one\n\
	Add 1986-03-31 trashtodel\n");

					for(int i = 0; i < 30; i++)
					{
						string command;
						is >> command;

						const auto date = ParseDate(is);
						const auto event = ParseEvent(is);
						db.Add(date, event);
					}

					ostringstream os;
					db.Print(os);
					auto strprnt = os.str();
					AssertEqual(strprnt, "0001-01-01 Start of time\n\
0001-01-01 Creation of sun\n\
0001-01-01 other 8 planets\n\
0001-01-02 Earth\n\
0001-01-02 our Moon\n\
0001-01-02 pangeya\n\
0001-01-02 sea\n\
0001-01-21 monday\n\
0001-01-21 tuesday\n\
0001-01-21 wendsday\n\
0001-01-21 thursday\n\
0001-01-21 friday\n\
0001-11-01 aabbcc\n\
0001-11-01 bbccdd\n\
0001-11-01 aaaacc\n\
1986-03-20 March of eighty six\n\
1986-03-31 last day of march\n\
1986-03-31 some new event\n\
1986-03-31 and2\n\
1986-03-31 some7\n\
1986-03-31 kind of\n\
1986-03-31 end of thirty one\n\
1986-03-31 trashtodel\n\
9999-12-31 fixing seeing\n\
9999-12-31 try to cath a star\n\
9999-12-31 burn it\n\
9999-12-31 trashtodel\n\
9999-12-31 cant burn it :(\n\
9999-12-31 end of Time\n\
9999-12-31 event-to-del\n", "Check print after full fill of my database");

					Database dbc;
					dbc = db;
					is.clear();
					is.str("date == 1-1-21 OR date >= 1986-03-31");
					auto condition = ParseCondition(is);
					auto predicate = [condition](const Date& date, const string& event){
						 return condition->Evaluate(date, event);
					};
					AssertEqual(dbc.RemoveIf(predicate), 19, "Del cond 001");
					os.str("");
					os.clear();
					dbc.Print(os);
					strprnt = os.str();
					AssertEqual(strprnt, "0001-01-01 Start of time\n\
0001-01-01 Creation of sun\n\
0001-01-01 other 8 planets\n\
0001-01-02 Earth\n\
0001-01-02 our Moon\n\
0001-01-02 pangeya\n\
0001-01-02 sea\n\
0001-11-01 aabbcc\n\
0001-11-01 bbccdd\n\
0001-11-01 aaaacc\n\
1986-03-20 March of eighty six\n", "Check print after Del cond 001");
	}
}

void TestCommandLast()
{
	{                                        // Add
			Database db;
			istringstream is, iss;
			is.str("Add 2017-01-01 New Year");

			string command;
			is >> command;

			const auto date = ParseDate(is);
			const auto event = ParseEvent(is);
			db.Add(date, event);

			ostringstream os;
			db.Print(os);

			vector<string> events;
			events.push_back(os.str());
			AssertEqual(events, vector<string>{"2017-01-01 New Year\n"}, "Parse Add 01");
	}

	{                                       // Add
		Database db;
		istringstream is, iss;
		is.str("\
	Add 2017-01-01 Holiday\n\
	Add 2017-03-08 Holiday\n\
	Add 2017-1-1 New Year\n\
	Add 2017-1-1 New Year\n");

		for(int i = 0; i < 4; i++)
		{
			string command;
			is >> command;

			const auto date = ParseDate(is);
			const auto event = ParseEvent(is);
			db.Add(date, event);
		}

		ostringstream os;
		db.Print(os);

		vector<string> events;
		events.push_back(os.str());
		AssertEqual(events, vector<string>{"\
2017-01-01 Holiday\n\
2017-01-01 New Year\n\
2017-03-08 Holiday\n"}, "Parse multi-Add 02");
	}

	{                                       // Last
		Database db;
		istringstream is, iss;
		is.str("\
Add 2017-01-01 New Year\n\
Add 2017-03-08 Holiday\n\
Last 2016-12-31\n\
Last 2017-01-01\n\
Last 2017-03-08\n");

	for(int i = 0; i < 2; i++)
	{
		string command;
		is >> command;

		const auto date = ParseDate(is);
		const auto event = ParseEvent(is);
		db.Add(date, event);
	}

	ostringstream os;
	for(int i = 0; i < 3; i++)
	{
		string command;
		is >> command;

		const auto date = ParseDate(is);
		os << db.Last(date) << endl;
	}

	vector<string> events;
	events.push_back(os.str());
//	cout << events;
	AssertEqual(events, vector<string>{"\
No entries\n\
2017-01-01 New Year\n\
2017-03-08 Holiday\n"}, "Parse Last 03");
	}

	{
	Database db;
	istringstream is, iss, is5;

  //------------------------------------------------------
  //                     Add
  //------------------------------------------------------
  is.str("\
Add 2017-11-21 Tuesday\n\
Add 2017-11-20 Monday\n\
Add 2017-11-21 Weekly meeting\n");

  for(int i = 0; i < 3; i++)
  {
      string command;
      is >> command;

      const auto date = ParseDate(is);
      const auto event = ParseEvent(is);
      db.Add(date, event);
  }

 //------------------------------------------------------
 //                     find
 //------------------------------------------------------

 is.str("Find event != \"Weekly meeting\"\n");
  string command;
  is >> command;

  auto condition = ParseCondition(is);
  auto predicate = [condition](const Date& date, const string& event){
     return condition->Evaluate(date, event);
  };

  auto entries3 = db.FindIf(predicate);
  string end_ = "Found 2 entries";
  entries3.push_back(end_);
  AssertEqual(entries3, vector<string>{"2017-11-20 Monday", "2017-11-21 Tuesday", "Found 2 entries"}, "Parse find 05");

  //------------------------------------------------------
  //                        Del
  //------------------------------------------------------
  is.str("Del date > 2017-11-20\n");
  string command2;
  is >> command2;

  auto condition2 = ParseCondition(is);
  auto predicate3 = [condition2](const Date& date, const string& event){
      return condition2->Evaluate(date, event);
  };

   int count = db.RemoveIf(predicate3);
   string tmp3 = "Removed " + to_string(count) + " entries";

   AssertEqual(tmp3, "Removed 3 entries", "Parse Del 06");

		//---------------------------------------------------------------------------------------------------------
		{                                       // всего понемногу
		Database db;
		istringstream is, iss, is5;

		//------------------------------------------------------
		//                        Last
		//------------------------------------------------------
		is5.str("Last 2017-11-30\n");
		string command3;
		is5 >> command3;

		auto d_date = ParseDate(is5);
		auto tmp4 = db.Last(d_date);

		AssertEqual(tmp4, "No entries", "Parse Last 07");
		}
	}

    //---------------------------------------------------------------------------------------------------------
    {
		// Add 2018-03-08 preved
		// Add 2018-03-08 medved
		// Del event !="medved"
		// Add 2018-03-08 krasavcheg
		// Last 2018-03-08
		// Add 2018-03-08 medved
		// Last 2018-03-08


        Database db;
        istringstream is, iss, is5, is6, is7, is8;

        //------------------------------------------------------
        //                     Add
        //------------------------------------------------------
        is.str("\
Add 2018-03-08 preved\n\
Add 2018-03-08 medved\n");

        for(int i = 0; i < 2; i++)
        {
            string command;
            is >> command;

            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        }

       //------------------------------------------------------
       //                        Del
       //------------------------------------------------------
       is.str("Del event !=\"medved\"\n");
       string command2;
       is >> command2;

       auto condition2 = ParseCondition(is);
       auto predicate3 = [condition2](const Date& date, const string& event){
           return condition2->Evaluate(date, event);
       };

        int count = db.RemoveIf(predicate3);
        string tmp3 = "Removed " + to_string(count) + " entries";

        AssertEqual(tmp3, "Removed 1 entries", "Parse Del 063");
        ostringstream os;
				db.Print(os);
				auto strprnt = os.str();
				AssertEqual(strprnt, "2018-03-08 medved\n", "Parse Print after Del 063");
        //------------------------------------------------------
        //                     Add
        //------------------------------------------------------
        is7.str("Add 2018-03-08 krasavcheg\n");

        for(int i = 0; i < 1; i++)
        {
            string command;
            is7 >> command;

            const auto date = ParseDate(is7);
            const auto event = ParseEvent(is7);
            db.Add(date, event);
        }

				os.str("");
				os.clear();
				db.Print(os);
				strprnt = os.str();
				AssertEqual(strprnt, "2018-03-08 medved\n\
2018-03-08 krasavcheg\n", "Parse Print after Del 063");

        //------------------------------------------------------
        //                        Last
        //------------------------------------------------------
        is5.str("Last 2018-03-08\n");
        string command3;
        is5 >> command3;

        auto d_date = ParseDate(is5);
        auto tmp4 = db.Last(d_date);
        AssertEqual(tmp4, "2018-03-08 krasavcheg", "Parse Last 071");
        //------------------------------------------------------
        //                     Add
        //------------------------------------------------------
        is8.str("Add 2018-03-08 medved\n");

        for(int i = 0; i < 1; i++)
        {
            string command;
            is8 >> command;

            const auto date = ParseDate(is8);
            const auto event = ParseEvent(is8);
            db.Add(date, event);
        }


				os.str("");
				os.clear();
				db.Print(os);
				strprnt = os.str();
				AssertEqual(strprnt, "2018-03-08 medved\n\
2018-03-08 krasavcheg\n", "Parse Print after Add 917");
        //------------------------------------------------------
        //                        Last
        //------------------------------------------------------
        is6.str("Last 2018-03-08\n");
        string command4;
        is6 >> command4;

        auto d_date2 = ParseDate(is6);
        auto tmp5 = db.Last(d_date2);

        AssertEqual(tmp5, "2018-03-08 krasavcheg", "Parse Last 939");
    }
}

/*void TestCommandLast()
{
    {
        Database db;
        db.Add((Date){2017, 1, 1}, "first");
        db.Add((Date){2017, 1, 1}, "second");
        db.Add((Date){2017, 1, 1}, "third");
        db.Add((Date){2017, 1, 1}, "fourth");
        db.Add((Date){2017, 1, 1}, "five");
        AssertEqual(2, DoRemove(db, R"(event == "second" OR event == "fourth")"), "Remove several");
        //AssertEqual("2017-01-01 first\n2017-01-01 third\n2017-01-01 five\n", DoPrint(db), "Check print after remove several- 3");

    }



}*/
