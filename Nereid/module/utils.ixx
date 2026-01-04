export module utils;
import <vector>;
export namespace utils {
	template<typename T>
	auto swap(T& a, T& b) -> void {
		auto temp{ a };
		a = b;
		b = temp;
	}
}
export namespace utils {
	auto add(int a, int b) -> int;
	// n阶方阵顺时针选择90°,参数必须是方阵，没有做任何错误处理。
	auto formation_rotate90(std::vector<std::vector<int>>& f) -> void;
}