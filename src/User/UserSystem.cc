#include "UserSystem.h"

namespace bookstore {

namespace user {

UserSystem::UserSystem() : uid_table("data/user/uid_table.dat") {
    // TODO
}
UserSystem::~UserSystem() {
    // TODO
}

int UserSystem::QueryUnum(const std::string &user_id) {
    // std::vector<int> ret = uid_table.find(String(user_id));
}

} // namespace user
} // namespace bookstore