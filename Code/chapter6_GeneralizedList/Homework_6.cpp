#include <string>
#include "./GList.h"

using namespace std;

class Homework_6 {
public:
    // T6.2 compare two glist
    void testCompare(
            const string& s1 = "(a, (b, c), d)",
            const string& s2 = "(a, (b, c), d, e)") {
        GList<char> gl1(s1);
        GList<char> gl2(s2);
        cout << gl1.same(gl2) << "\n";
    }
    
    // T6.3 delete atoms of x
    void testDelete(
            const string s = "((a, b), g, a, f)",
            char x = 'a') {
        GList<char> gl(s);
        gl.print();
        gl.deleteAtom(x);
        gl.print();
    }
};