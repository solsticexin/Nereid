module utils;
namespace utils {
	auto add(int a, int b) -> int {
		return a + b;
	}
	auto formation_rotate90(std::vector<std::vector<int>>& f) -> void {
		auto n = f.size();
		//第一个for ：原地转换为转置矩阵
		for (size_t i{ 0 }; i < n; i++)
			for (size_t j{ i }; j < n; j++)
				swap(f[i][j], f[j][i]);

		//将转置后的矩阵水平逆序排序，即每行元素逆序排序。
		for (size_t i{ 0 }; i < n; i++) {
			auto temp{ n - 1 };
			for (size_t j{ 0 }; j < n / 2; j++)
				swap(f[i][j], f[i][temp--]);
		}
	}
}