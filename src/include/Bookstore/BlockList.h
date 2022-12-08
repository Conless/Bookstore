#include <list>
#include <vector>

#include "Bookstore/Exception.h"

namespace bookstore {

namespace list {

template <class ListType, class DataType> void InsertList(std::list<ListType> &ls, const DataType &ins_data) {
    for (auto ls_iter = ls.begin(); ls_iter != ls.end(); ls_iter++) {
        auto nex_iter = ls_iter;
        nex_iter++;
        if (*ls_iter <= ins_data && (nex_iter == ls.end() || *nex_iter >= ins_data)) {
            ls.insert(ls_iter, ins_data);
            return;
        }
    }
    throw Exception(UNKNOWN, "InsertList fails with unknown error.");
}

template <class KeyType, class DataType> class BlockList {
  private:
    const int max_list_size = 10;
    typedef std::pair<KeyType, DataType> pr;
    std::list<std::list<pr>> data_list;

  public:
    void insert(KeyType key, DataType value) {
        pr ins_data = std::make_pair(key, value);
        if (data_list.empty()) {
            std::list<pr> fir_list;
            fir_list.push_back(ins_data);
            data_list.push_back(fir_list);
        } else {
            for (auto now_list_iter = data_list.begin(); now_list_iter != data_list.end(); now_list_iter++) {
                auto now_list = *now_list_iter;
                if ((now_list.front() <= ins_data && now_list.back() >= ins_data) || (now_list.size() < max_list_size)) {
                    InsertList(now_list, ins_data);
                    if (now_list.size() >= 2 * max_list_size) {
                        std::list<pr> nex_list;
                        while (now_list.size() > max_list_size) {
                            nex_list.push_front(now_list.back());
                            now_list.pop_back();
                        }
                        data_list.insert(now_list_iter, nex_list);
                    }
                }
            }
            std::list<pr> las_list;
            las_list.push_back(ins_data);
            data_list.push_back(las_list);
        }
        return;
    }
    void remove(KeyType key, DataType value) {
        pr del_data = std::make_pair(key, value);
        for (auto now_list_iter = data_list.begin(); now_list_iter != data_list.end(); now_list_iter++) {
            auto now_list = *now_list_iter;
            if (now_list.front() <= del_data && now_list.back() >= del_data) {
                for (auto now_data_iter = now_list.begin(); now_data_iter != now_list.end(); now_data_iter++) {
                    auto now_data = *now_data_iter;
                    if (now_data == del_data)
                        now_list.erase(now_data_iter);
                }
                auto nex_list_iter = now_list_iter;
                nex_list_iter++;
                auto nex_list = *nex_list_iter;
                if (now_list.size() + nex_list.size() <= max_list_size) {
                    while (!nex_list.empty()) {
                        now_list.push_back(nex_list.front());
                        nex_list.pop_front();
                    }
                    data_list.erase(nex_list_iter);
                }
            } else if (now_list.front() > del_data)
                break;
        }
        return;
    }
    std::vector<DataType> find(KeyType key) {
        std::vector<DataType> ret_list;
        for (auto now_list_iter = data_list.begin(); now_list_iter != data_list.end(); now_list_iter++) {
            auto now_list = *now_list_iter;
            if (now_list.front().first <= key && now_list.back().first >= key) {
                for (auto now_data_iter = now_list.begin(); now_data_iter != now_list.end(); now_data_iter++) {
                    auto now_data = *now_data_iter;
                    if (now_data.first == key)
                        ret_list.push_back(now_data.second);
                }
            } else if (now_list.front().first > key)
                break;
        }
        return ret_list;
    }
};

} // namespace list
} // namespace bookstore