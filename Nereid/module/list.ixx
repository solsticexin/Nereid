export module list;
import <expected>;
import <string>;
import <string>;  // 导入 std::string
import <stdexcept>; // 导入标准异常
import <iostream>;
import <vector>;
export namespace list {
	// --- 定义错误类型 ---
	struct GetElemError {
		std::string message;
		size_t index_requested; // 记录请求的索引 (可选)
		// 可以根据需要添加更多错误信息字段
	};

	struct InsertError {
		std::string message;
		size_t index_requested; // 记录请求的索引 (可选)
		// 可以根据需要添加更多错误信息字段
	};

	struct DropError {
		std::string message;
		size_t index_requested; // 记录请求的索引 (可选)
		// 可以根据需要添加更多错误信息字段
	};

    // --- 修改后的基类 ---
    template<typename T>
    class Boperation {
    public:
        Boperation() = default;
        virtual ~Boperation() = default;

        // 长度
        virtual auto length()const -> size_t = 0;

        // 按值查找 (返回索引，如果找不到可能需要返回特殊值或 expected，这里保持原样，但可以改进)
        // 例如，可以返回 std::optional<size_t> 或 std::expected<size_t, LocateError>
        virtual auto locate_elem(const T& elem)const -> int = 0;

        // 按位置查找 (修改: 返回 std::expected)
        virtual auto get_elem(size_t i)const -> std::expected<T, GetElemError> = 0;

        // 插入操作 (修改: 移除 const, 返回 std::expected)
        virtual auto insert(size_t i, T e) -> std::expected<void, InsertError> = 0;

        // 删除单个元素操作 (修改: 移除 const, 返回 std::expected)
        virtual auto drop(size_t i) -> std::expected<T, DropError> = 0;

        // 输出操作
        virtual auto print()const -> void = 0;

        // 判断为空
        virtual auto is_empty()const -> bool = 0;
    };
}

export namespace list {
    template<typename T>
    class SimpleList : public Boperation<T> {
    private:
        std::vector<T> data;

    public:
        // 构造函数
        SimpleList() = default;
        explicit SimpleList(const std::vector<T>& initial_data) : data(initial_data) {}

        // 实现基类的纯虚函数

        auto length() const -> size_t override {
            return data.size();
        }

        // locate_elem: 返回第一个匹配元素的索引，如果找不到返回 -1
        auto locate_elem(const T& elem) const -> int override {
            for (size_t i = 0; i < data.size(); ++i) {
                if (data[i] == elem) {
                    // 将 size_t 转换为 int
                    // 注意：如果 size_t 的值大于 int 的最大值，这里可能会溢出
                    // 在大多数实际场景下，线性表的大小不会达到 int 的最大值
                    return static_cast<int>(i);
                }
            }
            return -1; // 表示未找到
        }

        auto get_elem(size_t i) const -> std::expected<T, GetElemError> override {
            if (i >= data.size()) {
                return std::unexpected(GetElemError{
                    "Index out of bounds in get_elem",
                    i
                    });
            }
            return data[i];
        }

        auto insert(size_t i, T e) -> std::expected<void, InsertError> override {
            if (i > data.size()) { // 允许在末尾插入 (i == size())
                return std::unexpected(InsertError{
                    "Index out of bounds in insert",
                    i
                    });
            }
            data.insert(data.begin() + static_cast<std::vector<T>::difference_type>(i), e);
            return {}; // 返回一个空的 expected<void> 表示成功
        }

        auto drop(size_t i) -> std::expected<T, DropError> override {
            if (i >= data.size()) {
                return std::unexpected(DropError{
                    "Index out of bounds in drop",
                    i
                    });
            }
            T removed_element = data[i];
            data.erase(data.begin() + static_cast<std::vector<T>::difference_type>(i));
            return removed_element;
        }

        auto print() const -> void override {
            std::cout << "[ ";
            for (size_t j = 0; j < data.size(); ++j) {
                std::cout << data[j];
                if (j < data.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << " ]" << std::endl;
        }

        auto is_empty() const -> bool override {
            return data.empty();
        }
    };


}