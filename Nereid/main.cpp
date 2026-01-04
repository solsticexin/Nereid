import utils;
import list;

import <iostream>;
import <print>;
import <vector>;
int main() {
    std::cout << "Testing SimpleList with int locate_elem return...\n";

    // 创建一个 SimpleList 实例
    list::SimpleList<int> my_list;

    // 插入一些元素
    my_list.insert(0, 10);
    my_list.insert(1, 20);
    my_list.insert(2, 30);

    std::cout << "List: ";
    my_list.print(); // [ 10, 20, 30 ]

    // 测试按值查找
    int index = my_list.locate_elem(20);
    if (index >= 0) { // 检查返回值是否非负
        std::cout << "Found 20 at index: " << index << std::endl; // Found 20 at index: 1
    }
    else {
        std::cout << "Element 20 not found." << std::endl;
    }

    index = my_list.locate_elem(99);
    if (index >= 0) {
        std::cout << "Found 99 at index: " << index << std::endl;
    }
    else {
        std::cout << "Element 99 not found." << std::endl; // This will print
    }

    // 测试其他功能
    std::cout << "Length: " << my_list.length() << std::endl; // 3
    std::cout << "Is empty: " << (my_list.is_empty() ? "yes" : "no") << std::endl; // no

    auto get_result = my_list.get_elem(1);
    if (get_result.has_value()) {
        std::cout << "Element at index 1: " << get_result.value() << std::endl; // Element at index 1: 20
    }
    else {
        std::cout << "Get failed: " << get_result.error().message << std::endl;
    }

    auto drop_result = my_list.drop(1); // 删除索引 1 的元素 (20)
    if (drop_result.has_value()) {
        std::cout << "Dropped element: " << drop_result.value() << std::endl; // Dropped element: 20
    }
    else {
        std::cout << "Drop failed: " << drop_result.error().message << std::endl;
    }

    std::cout << "After dropping index 1: ";
    my_list.print(); // [ 10, 30 ]
}