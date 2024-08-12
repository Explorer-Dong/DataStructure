//
// Created by Wenjie Dong on 2023-10-10.
//

#include <iostream>
#include <fstream>
#include "./SeqList.h"
#include "./LinkList.h"

using namespace std;

struct item {
    string id, name;
    int price, cnt;
    bool operator< (const item& t) const {
        return this->id < t.id;
    }
    bool operator> (const item& t) const {
        return this->id > t.id;
    }
    bool operator== (const item& t) const {
        return this->id == t.id;
    }
    friend ostream& operator<< (ostream& os, const item& t) {
        os << t.id << " " << t.name << " " << t.price << " " << t.cnt;
        return os;
    }
};

struct stu {
    string id, name, gender, major, birth;
    bool operator== (const stu& t) const {
        return this->id == t.id;
    }
    friend ostream& operator<< (ostream& os, const stu& t) {
        os << t.id << " " << t.name << " " << t.gender << " " << t.major << " " << t.birth << endl;
        return os;
    }
};

#ifndef Experiment_2_H
#define Experiment_2_H

class Experiment_2 {
private:
    void displaySeqMenu() {
        cout << endl;
        cout << "====================" << endl;
        cout << "1. print" << endl;
        cout << "2. del min element" << endl;
        cout << "3. del all x" << endl;
        cout << "4. del one x" << endl;
        cout << "5. del all element range from l to r" << endl;
        cout << "6. unique" << endl;
        cout << "7. insert" << endl;
        cout << "8. insert to increase seq" << endl;
        cout << "9. sort once" << endl;
        cout << "0. exit" << endl;
        cout << "please input your choice:";
    }
    
    void displayItemMenu() {
        cout << endl;
        cout << "====================" << endl;
        cout << "1. print" << endl;
        cout << "2. modify or add info" << endl;
        cout << "3. del item with id" << endl;
        cout << "4. sort in id" << endl;
        cout << "0. save and exit" << endl;
        cout << "please input your choice:";
    }
    
    void displayLinkMenu() {
        cout << endl;
        cout << "====================" << endl;
        cout << "1. print" << endl;
        cout << "2. insert to head" << endl;
        cout << "3. sort and print" << endl;
        cout << "0. exit" << endl;
        cout << "please input your choice:";
    }
    
    void displayStuMenu() {
        cout << endl;
        cout << "====================" << endl;
        cout << "1. print" << endl;
        cout << "2. add one info" << endl;
        cout << "3. del one info" << endl;
        cout << "4. modify one info" << endl;
        cout << "0. save and exit" << endl;
        cout << "please input your choice:";
    }

public:
    // Exp1.1 test Seqlist all functions
    void testSeqList() {
        int arr[] = {4, 2, 1, 3, 8, 0, 123}, n = 7;
        SeqList<int> seqList(arr, n);
        
        int choice;
        while (true) {
            displaySeqMenu();
            cin >> choice;
            cout << endl;
            
            switch (choice) {
                case 1: {
                    cout << "print" << endl;
                    seqList.Output();
                    break;
                }
                case 2: {
                    int minVal = seqList.DeleteMin();
                    break;
                }
                case 3: {
                    cout << "del all x";
                    int deleteX;
                    cin >> deleteX;
                    seqList.DeleteAllX(deleteX);
                    break;
                }
                case 4: {
                    int deleteValue;
                    cout << "del one x";
                    cin >> deleteValue;
                    seqList.DeleteAllX(deleteValue);
                    break;
                }
                case 5: {
                    int left, right;
                    cout << "input l:" << endl;
                    cin >> left;
                    cout << "input r:" << endl;
                    cin >> right;
                    seqList.DeleteRange(left, right);
                    break;
                }
                case 6: {
                    seqList.Unique();
                    break;
                }
                case 7: {
                    cout << "insert position:";
                    int insertPos, insertValue;
                    cin >> insertPos;
                    cout << "insert value:";
                    cin >> insertValue;
                    seqList.Insert(insertPos, insertValue);
                    break;
                }
                case 8: {
                    cout << "insert value:";
                    int insertIncreasing;
                    cin >> insertIncreasing;
                    seqList.IncreaseInsert(insertIncreasing);
                    break;
                }
                case 9: {
                    seqList.SortOnce();
                    break;
                }
                case 0: {
                    break;
                }
                default: {
                    cout << "invalid input!" << endl;
                }
            }
        }
    }
    
    
    // Exp1.2 sort
    void testSort() {
        int arr[] = {4, 2, 1, 3}, n = 4;
        SeqList<int> a(arr, n);
        a.Output();
        a.Sort();
        a.Output();
    }
    
    
    // Exp 1.2 merge two ordered list
    void testMergeOrderedSeqList() {
        int arr1[] = {1, 2, 3, 4}, n1 = 4;
        int arr2[] = {0, 7, 10}, n2 = 3;
        SeqList<int> a(arr1, n1), b(arr2, n2);
        a.Output(), b.Output();
        a.Merge(b);
        a.Output();
    }
    
    
    // Exp2 item manage system with seqlist
    void testItemManageSystem() {
        // read data from txt file
        ifstream fin("HomeWork\\Exp2_T2.txt");
        if (!fin) {
            cout << "unsuccessful open file" << endl;
            exit(1);
        } else {
            cout << "successful open file" << endl;
        }
        
        // store data in cpu
        int n;
        fin >> n;
        SeqList<item> a(n);
        for (int i = 0; i < n; i++) {
            fin >> a[i].id >> a[i].name >> a[i].price >> a[i].cnt;
        }
        
        int choice;
        while (true) {
            displayItemMenu();
            cin >> choice;
            switch (choice) {
                case 1: {
                    a.Output();
                    break;
                }
                case 2: {
                    cout << "input item id:";
                    string nowid;
                    cin >> nowid;
                    if (!a.find({nowid, "", 0, 0})) {
                        // new item info
                        item now;
                        now.id = nowid;
                        cout << "input item name:";
                        cin >> now.name;
                        cout << "input item price:";
                        cin >> now.price;
                        cout << "input item count:";
                        cin >> now.cnt;
                        a.Insert(n++, now);
                    } else {
                        // modify cnt
                        int cnt;
                        cout << "input item count:";
                        cin >> cnt;
                        for (int i = 0; i < n; i++) {
                            if (a[i].id == nowid) {
                                a[i].cnt += cnt;
                                break;
                            }
                        }
                    }
                    break;
                }
                case 3: {
                    cout << "input item id:";
                    string nowid;
                    cin >> nowid;
                    for (int i = 0; i < n; i++) {
                        if (a[i].id == nowid) {
                            a.DeleteAllX({nowid, "", 0, 0});
                            n--;
                            break;
                        }
                    }
                    break;
                }
                case 4: {
                    a.Sort();
                    break;
                }
                case 0: {
                    ofstream fout("HomeWork\\Exp2_T2.txt");
                    fout << n << endl;
                    for (int i = 0; i < n; i++) {
                        fout << a[i].id << " " << a[i].name << " " << a[i].price << " " << a[i].cnt << endl;
                    }
                    fout.close();
                    return;
                }
            }
        }
    }


	// Exp3 test LinkList all functions
	void testLinkList() {
		int arr[] = {4, 2, 1, 3, 8, 0, 123}, n = 7;
		LinkList<int> linkList(arr, n);
  
		int choice;
        while (true) {
            displayLinkMenu();
            cin >> choice;
            cout << "\n";
            
            switch (choice) {
                case 1: {
                    cout << "print" << endl;
                    linkList.Output();
                    break;
                }
                case 2: {
                    cout << "insert value:" << endl;
                    int insertValue;
                    cin >> insertValue;
                    linkList.PushFront(insertValue);
                    break;
                }
                case 3: {
                    linkList.PrintInOrder();
                    break;
                }
                case 0:
                    cout << "exit" << endl;
                    return;
                default:
                    cout << "invalid input!" << endl;
            }
        }
	}


	// Exp3.1 reverse list
	void testReverseLinkList() {
		int arr[] = {4, 2, 1, 3, 8, 0, 123}, n = 7;
		LinkList<int> ls(arr, n);
  
		cout << "original:";
		ls.Output();
        ls.Reverse();
		cout << "reversed:";
		ls.Output();
	}


	// Exp3.2 merge two ordered linklist
	void testMergeLinkList() {
		int arr1[] = {1, 2, 3, 4}, n1 = 4;
		int arr2[] = {0, 7, 10}, n2 = 3;
		LinkList<int> a(arr1, n1), b(arr2, n2);
		cout << "original:\n";
		a.Output(), b.Output();
		a.Merge(b);
		cout << "merged:";
		a.Output();
	}


	// Exp4 student manage system with linklist
	void testStudentManageSystem() {
		// read data from txt file
		ifstream fin("Exp2_T4.txt");
		if (!fin) {
			cout << "unsuccessful open file" << endl;
			exit(1);
		} else {
			cout << "successful open file" << endl;
		}

		// store data in cpu
		int n;
		fin >> n;
		stu arr[n];
		for (int i = 0; i < n; i++) {
			fin >> arr[i].id >> arr[i].name >> arr[i].gender >> arr[i].major >> arr[i].birth;
		}
		LinkList<stu> ls(arr, n);

		int choice;
		while (true) {
            displayStuMenu();
			cin >> choice;
			switch (choice) {
				case 1: {
                    ls.Output();
					break;
				}
				case 2: {
					cout << "input student info:";
					stu now;
					cout << "id:";
					cin >> now.id;
					cout << "name:";
					cin >> now.name;
					cout << "gender:";
					cin >> now.gender;
					cout << "major:";
					cin >> now.major;
					cout << "birth:";
					cin >> now.birth;
                    ls.PushFront(now);
					cout << "over" << endl;
					break;
				}
				case 3: {
                    cout << "input student id:";
                    string nowid;
					cin >> nowid;
                    ls.Delete({nowid, "", "", "", ""});
					break;
				}
				case 4: {
                    cout << "input student id:";
                    string nowid;
                    cin >> nowid;
                    if (ls.Find({nowid, "", "", "", ""})) {
                        ls.Delete({nowid, "", "", "", ""});
                        cout << "input new info:";
                        stu now;
                        now.id = nowid;
                        cout << "name:";
                        cin >> now.name;
                        cout << "gender:";
                        cin >> now.gender;
                        cout << "major:";
                        cin >> now.major;
                        cout << "birth:";
                        cin >> now.birth;
                        ls.PushFront(now);
                    }
					break;
				}
				case 0: {
					ls.OutputToFile("Exp2_T4.txt");
					return;
				}
			}
		}
	}
};

#endif //Experiment_2_H