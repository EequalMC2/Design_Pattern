#include <boost/lexical_cast.hpp>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace boost;

/////////INFO
////Signle Responsibility Principle basically states is that a class should have a one responsibility
////It should not take on other responsibilities.

///////////////// Before Signle Responsibility
// struct Journal {
//     string title;
//     vector<string> entries;
//     Journal(const string& title)
//         : title(title)
//     {
//     }
//     void add_entry(const string& entry)
//     {
//         static int counter = 1;
//         entries.push_back(lexical_cast<string>(counter++) + " : " + entry);
//     }

//     void save(const string& filename)
//     {
//         ofstream ofs(filename);
//         ofs << title << ":" << "\n";
//         for (auto& i : entries)
//             ofs << i << endl;
//     }
// };

// int main()
// {
//     Journal journal("romanlar");
//     journal.add_entry("Fareler ve İnsanlar");
//     journal.add_entry("Oblamov");
//     journal.add_entry("Simyacı");
//     journal.save("./saved");
// }


//////////////// After Signle Responsibility
struct Journal {
    string title;
    vector<string> entries;
    Journal(const string& title)
        : title(title)
    {
    }
    void add_entry(const string& entry)
    {
        static int counter = 1;
        entries.push_back(lexical_cast<string>(counter++) + " : " + entry);
    }

};
struct PersistenceManager {
    static void save(const Journal& j, const string& filename)
    {
        ofstream ofs(filename);
        ofs << j.title << ":" << "\n";
        for (const auto& i : j.entries)
            ofs << i << endl;
    }

    //can be save fonction overloading 
};

int main()
{
    Journal journal("romanlar");
    journal.add_entry("Fareler ve İnsanlar");
    journal.add_entry("Oblamov");
    journal.add_entry("Simyacı");

    PersistenceManager::save(journal, "./save");

}
