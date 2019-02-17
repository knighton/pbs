#include <cassert>

#include "pbs/pbs.h"
#include "person.pb.h"

void MakeData(vector<Person>* people) {
    Person p;

    p.set_name("ABC");
    p.set_phone("15551234567");
    people->emplace_back(p);

    p.Clear();
    p.set_name("DEF");
    p.set_phone("15551012345");
    auto bd = p.mutable_birthday();
    bd->set_year(1933);
    bd->set_month(2);
    bd->set_day(7);
    people->emplace_back(p);

    p.Clear();
    p.set_name("GHI");
    bd = p.mutable_birthday();
    bd->set_year(1958);
    bd->set_month(4);
    bd->set_day(15);
    people->emplace_back(p);

    p.Clear();
    p.set_name("Davy Jones");
    people->emplace_back(p);
}

void TestBasic() {
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

void TestOne(const vector<Person>& people) {
    for (auto& p : people) {
        string s;
        assert(pbs::WriteOneToString(p, &s));

        size_t index = 0;
        Person p2;
        assert(pbs::ReadOneFromString(s, &index, &p2) == pbs::ReadResult::OK);

        string ps;
        p.SerializeToString(&ps);

        string p2s;
        p2.SerializeToString(&p2s);

        assert(ps == p2s);
    }
}

void TestMany(const vector<Person>& people) {
    string s;
    assert(pbs::WriteToString(people, &s));

    size_t index = 0;
    vector<Person> people2;
    pbs::SequenceReadResult result;
    assert(pbs::ReadFromString(s, &index, &people2, &result));
    assert(people2.size() == people.size());
    for (size_t i = 0; i < people2.size(); ++i) {
        string ps;
        people[i].SerializeToString(&ps);

        string p2s;
        people2[i].SerializeToString(&p2s);

        assert(ps == p2s);
    }
    assert(result.num_ok == 4);
    assert(!result.num_bad_checksum);
    assert(!result.num_bad_proto);
}

int main() {
    vector<Person> people;
    MakeData(&people);
    TestOne(people);
    TestMany(people);
}
