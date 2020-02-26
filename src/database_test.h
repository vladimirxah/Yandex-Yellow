/*
 * database_test.h
 *
 *  Created on: 18 февр. 2020 г.
 *      Author: gonchrov
 */

#pragma once

#include "database.h"
#include "vector"
#include "string"
#include "test_runner.h"
#include "condition_parser.h"

void TestDatabase();

void TestCommandLast();

string ParseEvent(istream& is);
