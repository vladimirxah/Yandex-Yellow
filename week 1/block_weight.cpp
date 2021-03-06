#include <iostream>
#include <vector>
#include <iterator>
#include <string>

using namespace std;

/*
 * Вычислите суммарную массу имеющих форму прямоугольного параллелепипеда бетонных блоков одинаковой плотности, но разного размера.

	Указание
	Считайте, что размеры блоков измеряются в сантиметрах, плотность — в граммах на кубический сантиметр, а итоговая масса — в граммах. Таким образом, массу блока можно вычислять как простое произведение плотности на объём.

	Формат ввода
	В первой строке вводятся два целых положительных числа: количество блоков N и плотность каждого блока R. Каждая из следующих N строк содержит три целых положительных числа W, H, D — размеры очередного блока.

	Гарантируется, что:

	количество блоков N не превосходит 10^5;
	плотность блоков R не превосходит 100;
	размеры блоков W, H, D не превосходят 10^4.
 *
 * Варианты ввода для отладки
 *
 *
2 14
1 2 3
30 40 50
 *
 *
840084
 */

int main() {
	uint_fast32_t n;
	uint_fast32_t dens;
	cin >> n >> dens;
	uint_least64_t sum = 0;
	while (n > 0) {
		uint_fast32_t W, H, D;
		cin >> W >> H >> D;
		sum += W * H * D * dens;
		--n;
	}
	cout << sum;

	return 0;
}



/*
 * Главное, на что нужно было обратить внимание при решении задачи — корректный выбор целочисленных типов. Как следует из условия, максимально возможное значение массы равно 10^4 * 10^4 * 10^4 * 10^5 * 100 = 10^19, что умещается лишь в тип uint64_t.



Пример:
#include <cstdint>
#include <iostream>

using namespace std;

int main() {
  int N, R;
  cin >> N >> R;
  uint64_t answer = 0;
  for (int i = 0; i < N; ++i) {
    int W, H, D;
    cin >> W >> H >> D;
    // Если не привести W к типу uint64_t перед умножением,
    // произведение будет иметь тип int и случится переполнение.
    // Альтернативное решение — хранить сами W, H, D в uint64_t
    answer += static_cast<uint64_t>(W) * H * D;
  }
  answer *= R;
  cout << answer << endl;
  return 0;
}

}*/
