#include "BlockList.h"

#include "Bookstore/Exception.h"

namespace bookstore {

namespace list {

template <class ListType, class DataType>
void InsertList(std::list<ListType> &ls, const DataType &ins_data) {
    for (auto ls_iter = ls.begin(); ls != ls.end(); ls++) {
        auto ls_data = *ls_iter;
        if (ls_data <= ins_data && (ls_iter.next() == ls_data.end() || ls_data.next() >= ins_data)) {
            ls.insert(ls_iter, ins_data);
            return;
        }
    }
    throw Exception(UNKNOWN, "InsertList fails with unknown error.");
}

template <class KeyType, class DataType>
void BlockList<KeyType, DataType>::insert(const KeyType &key, const DataType &value) {
    pr ins_data = std::make_pair(key, value);
    if (data_list.empty()) {
        std::list<pr> fir_list;
        fir_list.push_back(ins_data);
    } else {
        for (auto now_list_iter = data_list.begin(); now_list_iter != data_list.end(); now_list_iter++) {
            auto now_list = *now_list_iter;
            if (now_list.front() <= ins_data && now_list.back() >= ins_data) {
                InsertList(now_list, ins_data);
                if (now_list.size() > max_list_size) {
                    
                }
            }
        }
    }
}

}
}