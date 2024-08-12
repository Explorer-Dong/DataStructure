#include <string>
#include "./GList.h"

using namespace std;

class Experiment_6 {
private:
    void displayGListMenu() {
        cout << endl;
        cout << "====================" << endl;
        cout << "1. print all" << endl;
        cout << "2. print length" << endl;
        cout << "3. print depth" << endl;
        cout << "0. exit" << endl;
        cout << "please input: ";
    }

public:
    // test glist: print all, lenth, depth
    void testGList(const string& s = "((a, (), b), g, a, f)") {
        GList<char> g(s);
        int choice;
        while (true) {
            displayGListMenu();
            cin >> choice;
            switch (choice) {
                case 1:
                    g.print();
                    break;
                case 2:
                    cout << g.length() << "\n";
                    break;
                case 3:
                    cout << g.depth() << "\n";
                    break;
                case 0:
                    return;
                default:
                    cout << "invalid input!\n";
            }
        }
    }
    
    // test replace atom from origin to target
    void testReplaceAtom(
            const string& s = "((a, (), b), g, a, f)",
            char origin = 'a', char target = 'h') {
        GList<char> g(s);
        g.print();
        g.replaceAtom(origin, target);
        g.print();
    }
};