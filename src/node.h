/*классы Node, EmptyNode, DateComparisonNode, EventComparisonNode и LogicalOperationNode — сформировать их иерархию и публичный интерфейс вам поможет анализ функций main и ParseCondition;*/
/*node.h/cpp — эти файлы должны содержать объявления и определения класса Node, а также всех его потомков (см. выше), которые представляют собой узлы абстрактного синтаксического дерева, формируемого функцией ParseCondition;*/

#pragma once

#include "date.h"

class Node {
public:
	virtual ~Node ();
  virtual int Evaluate(const Date& date, const string& string)/* const = 0*/;

};
