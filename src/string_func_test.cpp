#include <cassert>

#include "pbs/pbs.h"
#include "person.pb.h"

int main() {
    Person p;
    p.set_name("ABC");
    p.set_phone("15551234567");
    string s;
    assert(pbs::WriteOneToString(p, &s));
    size_t index = 0;
    Person p2;
    assert(pbs::ReadOneFromString(s, &index, &p2) == pbs::ReadResult::OK);
    assert(p.name() == p2.name());
    assert(p2.has_phone());
    assert(p.phone() == p2.phone());
    assert(!p2.has_birthday());
    assert(index == s.size());
    assert(pbs::ReadOneFromString(s, &index, &p2) == pbs::ReadResult::END);
    assert(pbs::ReadOneFromString(s, &index, &p2) == pbs::ReadResult::END);
}
