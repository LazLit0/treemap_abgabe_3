// Testtreiber für Aufgabe treemap von Hartmut Schirmacher, Berliner Hochschule für Technik (BHT)

#include <iostream>
#include <string>

#include "assert.h"

#include "treemap.h"
#include "payload.h"

using namespace std;
using my::treemap;

// helper function for human readable output
ostream& operator<<(ostream& os, Payload p)
{
    return os << "(" << p.x << "," << p.y << "," << p.z << ") ";
}

int main()
{

     {
        cout << "1. treemap basics..." << endl;

        treemap<string, Payload> m;
 
        // initially the map must be empty
        assert(m.size() == 0); 
        // no Payload objects created
        assert(Payload::count() == 0);

        cout << "done..." << endl;
    }
    assert(Payload::count() == 0);
    cout << endl;

    {
        cout << "2. insert, find, count, size, clear ..." << endl;

        // implement insert() first!
        treemap<string, Payload> m;

        // inserting (key,value) pairs
        cout << "insert Three, " << Payload(3,3,3) << endl;
        auto [iter3,flag3] = m.insert("Three", Payload(3,3,3));
        assert(flag3 == true);
        assert(m.size() == 1);

        cout << "insert Seven, " << Payload(7,7,7) << endl;
        auto [iter7,flag7] = m.insert("Seven", Payload(7,7,7));
        assert(flag7 == true);
        assert(m.size() == 2);
        {
            // insert a third element
            // insert() returns a pair of an iterator an a bool
            cout << "insert Eleven" << endl;
            auto [iter11, was_inserted11] = m.insert("Eleven", Payload(11,11,11));

            // the bool should be true if the alement was newly inserted (key has not been in the map befoee)
            assert(was_inserted11 == true);

            // returned iterator should point to the inserted key and value
            assert(iter11->first == "Eleven");
            assert(iter11->second == Payload(11,11,11));

            assert(m.size() == 3);
        }
        {
            // try to overwrite the value for the existing key "Three"
            cout << "do not overwrite Three" << endl;
            auto [iter_three, was_inserted] = m.insert("Three", Payload(3,4,5));
            assert(was_inserted == false);
            assert(iter_three->second == Payload(3,3,3));
        }
        {
            // now implement insert_or_assign; refactor so you do not duplicate too much code of insert() 
            cout << "overwrite Three" << endl;
            auto [iter_three, was_inserted] = m.insert_or_assign("Three", Payload(3,4,5));
            assert(was_inserted == false);
            assert(iter_three->second == Payload(3,4,5));
        }

        // now implement find() and count() 
        cout << "count and find... " << endl;

        // key "Three" should be found exactly once
        assert(m.count("Three") == 1);

        // key "Four" should not be found
        assert(m.count("Four") == 0);

        // there have been three Payloads inserted, not less, not more
        assert(Payload::count() == 3);

        {

            // find() finds the key in the map and returns an iterator. Should not change count.
            auto eleven = m.find("Eleven");
            assert(Payload::count() == 3);

            // output key and value to console
            auto key = eleven->first;
            auto value = eleven->second;
            cout << "found payload Eleven: [ " << key << "," << value << " ]" << endl;

            // clear()
            cout << "clear!" << endl;
            m.clear();
            assert(m.size() == 0);

            // "value" still holds a shared_ptr to one Payload obj, so the Payload has not been destroyed
            assert(Payload::count() == 1); 
        }
        assert(Payload::count() == 0);

        cout << "done." << endl;
    }
    // }


    assert(Payload::count() == 0);
    cout << endl;

    {
        cout << "3. operator [] read/write..." << endl;

        treemap<string, Payload> m;

        // [] write operation
        m["B=1"] = Payload(1,1,1);
        m["A=2"] = Payload(2,2,2);
        m["C=3"] = Payload(3,4,5);
        assert(m["C=3"] == Payload(3,4,5));

        // overwriting an existing value
        m["C=3"] = Payload(3,3,3);
        assert(m["C=3"] == Payload(3,3,3));

        // count()
        assert(m.count("A=2") == 1);
        assert(m.count("B=1") == 1);
        assert(m.count("C=3") == 1);
        assert(m.size() == 3);

        // const version of operator[]
        auto const& const_m = m;
        cout << "A: " << const_m["A=2"] << endl;
        assert(const_m["A=2"] == Payload(2,2,2));
        cout << "B: " << const_m["B=1"] << endl;
        assert(const_m["B=1"] == Payload(1,1,1));
        cout << "C: " << const_m["C=3"] << endl;
        assert(const_m["C=3"] == Payload(3,3,3));

        cout << "done." << endl;

    }

    assert(Payload::count() == 0);
    cout << endl;

    {
        cout << "4. begin(), end(), ++ ..." << endl;

        treemap<string, int> m;

        m["Hartmut"] = 1;
        m["Helmut"] = 2;
        m["Zebra"] = 3;
        m["Anna"] = 4;
        m["Klaus"] = 5;
        assert(m.size() == 5);

        // iterator++, iterator operator->
        cout << "iterating through list in normal order:" << endl;
        for(auto i=m.begin(); i!=m.end(); ++i)
            cout << "  " << i->first << ": " << i->second << endl;

        assert(m.begin()->first == "Anna");
        assert((++m.begin())->first == "Hartmut");
        assert((++++m.begin())->first == "Helmut");
        assert((++++++m.begin())->first == "Klaus");
        assert((++++++++m.begin())->first == "Zebra");

        // iterator++, iterator operator*
        cout << "iterating through list using range-based for loop:" << endl;
        for(auto x : m)
            cout << "  " << x.first << ": " << x.second << endl;

        cout << "done." << endl;

    }

    assert(Payload::count() == 0);
    cout << endl;

    {
        cout << "5. iterator, -- ..." << endl;

        treemap<string, int> m;
        m["Hartmut"] = 1;
        m["Helmut"] = 2;
        m["Zebra"] = 3;
        m["Anna"] = 4;
        m["Klaus"] = 5;
        assert(m.size() == 5);

        // iterator--
        cout << "iterating through list in reverse order:" << endl;
        /* todo */
        // while(...) {
        //        cout << "  " << i->first << ": " << i->second << endl;
        // }
            // }

            for(auto i=m.end(); i!=--m.begin(); --i)
            cout << "  " << i->first << ": " << i->second << endl;
         
        // some bit of automatic testing in addition
        assert((--m.end())->first == "Zebra");
        assert((----m.end())->first == "Klaus");

        cout << "done." << endl;

    }

    assert(Payload::count() == 0);
    cout << endl;

    {
        cout << "6. move ..." << endl;
        assert(Payload::count() == 0); // just for sanity's sake

        treemap<string, Payload> m;
        m["Hartmut"] = Payload(1,1,1);
        m["Helmut"]  = Payload(1,2,1);
        m["Zebra"]   = Payload(1,3,1);
        m["Anna"]    = Payload(1,4,1);
        m["Klaus"]   = Payload(1,5,1);
        assert(m.size() == 5);
        assert(Payload::count() == 5);

        // move it
        auto m2 = std::move(m);

        // no duplicates?
        assert(Payload::count() == 5);

        // keys and values still intact?
        assert(m2["Anna"] == Payload(1,4,1));
        assert(m2["Klaus"] == Payload(1,5,1));

        cout << "done." << endl;
    }        
    assert(Payload::count() == 0);
    cout << endl;

    {
        cout << "7. deep copy ..." << endl;

        assert(Payload::count() == 0); // just for sanity's sake

        treemap<string, Payload> m;
        m["Hartmut"] = Payload(1,1,1);
        m["Helmut"]  = Payload(1,2,1);
        m["Zebra"]   = Payload(1,3,1);
        m["Anna"]    = Payload(1,4,1);
        m["Klaus"]   = Payload(1,5,1);
        assert(m.size() == 5);
        assert(Payload::count() == 5);

        // copy it
        auto m2 = m;

        // exactly twice as many objects now?
        assert(Payload::count() == 10);

        // keys and values still intact?
        assert(m2["Anna"] == m["Anna"]);
        assert(m2["Klaus"] == m["Klaus"]);

        // two independent copies?
        auto old_anna = m["Anna"];
        m["Anna"] = Payload(99,100,101);
        assert(m2["Anna"] == old_anna);

        cout << "done." << endl;
    }

    assert(Payload::count() == 0);
    cout << endl;


    return 0;
#if 0
#endif
}
