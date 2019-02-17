#include <cassert>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unistd.h>

#include "pbs/pbs.h"
#include "person.pb.h"

using namespace pbs;
using std::string;

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

string GetTempFilename() {
    uint32_t number = static_cast<uint32_t>(rand());
    char filename[16];
    snprintf(filename, 16, "test_%x.pbs", number);
    return string(filename, strlen(filename));
}

bool FileToString(const string& filename, string* data) {
    FILE* file = fopen(filename.c_str(), "r");
    if (!file) {
        return false;
    }
    fseek(file, 0, SEEK_END);
    size_t size = static_cast<size_t>(ftell(file));
    fseek(file, 0, SEEK_SET);
    data->resize(size);
    fread(&(*data)[0], sizeof(char), size, file);
    fclose(file);
    return true;
}

int Unlink(const string& filename) {
    return unlink(filename.c_str());
}

struct SerializationResults {
    string buffer_func_one;
    string buffer_func_many;
    string buffer_writer_one;
    string buffer_writer_many;

    string file_func_one;
    string file_func_many;
    string file_writer_one;
    string file_writer_many;

    string string_func_one;
    string string_func_many;
    string string_writer_one;
    string string_writer_many;
};

void SerializeToBuffers(const vector<Person>& people,
                        SerializationResults* ways) {
    size_t data_max_size = 1024;

    {
        char* data = new char[data_max_size];
        const char* data_begin = data;
        const char* data_end = &data[data_max_size];
        for (auto& person : people) {
            assert(WriteOneToBuffer(person, &data, data_end));
        }
        size_t data_size = static_cast<size_t>(data - data_begin);
        ways->buffer_func_one = string(data_begin, data_size);
        delete [] data_begin;
    }

    {
        char* data = new char[data_max_size];
        const char* data_begin = data;
        const char* data_end = &data[data_max_size];
        assert(WriteToBuffer(people, &data, data_end) == people.size());
        size_t data_size = static_cast<size_t>(data - data_begin);
        ways->buffer_func_many = string(data_begin, data_size);
        delete [] data_begin;
    }

    {
        char* data = new char[data_max_size];
        const char* data_begin = data;
        const char* data_end = &data[data_max_size];
        BufferWriter<Person> writer(&data, data_end);
        for (auto& person : people) {
            assert(writer.WriteOne(person));
        }
        size_t data_size = static_cast<size_t>(data - data_begin);
        ways->buffer_writer_one = string(data_begin, data_size);
        delete [] data_begin;
    }

    {
        char* data = new char[data_max_size];
        const char* data_begin = data;
        const char* data_end = &data[data_max_size];
        BufferWriter<Person> writer(&data, data_end);
        assert(writer.Write(people) == people.size());
        size_t data_size = static_cast<size_t>(data - data_begin);
        ways->buffer_writer_many = string(data_begin, data_size);
        delete [] data_begin;
    }
}

void SerializeToFiles(const vector<Person>& people,
                      SerializationResults* ways) {
    {
        string filename = GetTempFilename();
        FILE* file = fopen(filename.c_str(), "w");
        for (auto& person : people) {
            assert(WriteOneToFile(person, file));
        }
        fclose(file);
        assert(FileToString(filename, &ways->file_func_one));
        assert(!Unlink(filename));
    }

    {
        string filename = GetTempFilename();
        FILE* file = fopen(filename.c_str(), "w");
        assert(WriteToFile(people, file) == people.size());
        fclose(file);
        assert(FileToString(filename, &ways->file_func_many));
        assert(!Unlink(filename));
    }

    {
        string filename = GetTempFilename();
        FILE* file = fopen(filename.c_str(), "w");
        FileWriter<Person> writer(file);
        for (auto& person : people) {
            assert(writer.WriteOne(person));
        }
        fclose(file);
        assert(FileToString(filename, &ways->file_writer_one));
        assert(!Unlink(filename));
    }
    {
        string filename = GetTempFilename();
        FILE* file = fopen(filename.c_str(), "w");
        FileWriter<Person> writer(file);
        assert(writer.Write(people) == people.size());
        fclose(file);
        assert(FileToString(filename, &ways->file_writer_many));
        assert(!Unlink(filename));
    }
}

void SerializeToStrings(const vector<Person>& people,
                        SerializationResults* ways) {
    for (auto& person : people) {
        assert(WriteOneToString(person, &ways->string_func_one));
    }

    assert(WriteToString(people, &ways->string_func_many) == people.size());

    {
        StringWriter<Person> writer(&ways->string_writer_one);
        for (auto& person : people) {
            assert(writer.WriteOne(person));
        }
    }

    {
        StringWriter<Person> writer(&ways->string_writer_many);
        assert(writer.Write(people) == people.size());
    }
}

void CheckAllSame(const SerializationResults& ways) {
    string s = ways.buffer_func_one;
    assert(ways.buffer_func_one == s);
    assert(ways.buffer_func_many == s);
    assert(ways.buffer_writer_one == s);
    assert(ways.buffer_writer_many == s);
    assert(ways.file_func_one == s);
    assert(ways.file_func_many == s);
    assert(ways.file_writer_one == s);
    assert(ways.file_writer_many == s);
    assert(ways.string_func_one == s);
    assert(ways.string_func_many == s);
    assert(ways.string_writer_one == s);
    assert(ways.string_writer_many == s);
}

int main() {
    vector<Person> people;
    MakeData(&people);
    SerializationResults ways;
    SerializeToBuffers(people, &ways);
    SerializeToFiles(people, &ways);
    SerializeToStrings(people, &ways);
    CheckAllSame(ways);
}
