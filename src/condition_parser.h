#pragma once

#include "node.h"

#include <memory>
#include <map>
#include <iostream>

using namespace std;

shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();

Date ParseDate(istream& is);
