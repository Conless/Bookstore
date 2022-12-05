#include "Bookstore.h"

#include "Bookstore/Exception.h"

namespace bookstore {

void CheckAuthority(Identity vis, std::string opt) {
    // TODO        
    switch (vis) {
    case Manager:
        break;
    case Staff:
        break;
    case Customer:
        break;
    case Visitor:
        break;
    default:
        break;
    }
    return;
}

Bookstore::Bookstore() {
    // TODO
}
Bookstore::~Bookstore() {
    // TODO
}

void Bookstore::AcceptMsg(input::InputMsg msg) { throw Exception(UNIMPLEMENTED, "Bookstore doesn't support this operation."); }
}