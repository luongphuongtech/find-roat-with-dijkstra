#include "Street.cpp"
#include "Function.cpp"
using namespace std;
 
int main()
{
    vector<Street> v;
    pair<char, pair<char, double>> streetName = make_pair('A', make_pair('B', 1));
    Street st1(streetName, 60, 4);
    v.push_back(st1);
    streetName = make_pair('A', make_pair('E', 3));
   Street st2(streetName, 30, 2);
   v.push_back(st2);
   streetName = make_pair('A', make_pair('D', 1));
   Street st3(streetName, 90, 2);
   v.push_back(st3);
   streetName = make_pair('A', make_pair('J', 7));
   Street st4(streetName, 110, 8);
   v.push_back(st4);
   streetName = make_pair('B', make_pair('C', 3));
   Street st5(streetName, 35, 2);
   v.push_back(st5);
   streetName = make_pair('B', make_pair('H', 8));
   Street st6(streetName, 100, 8);
   v.push_back(st6);
   streetName = make_pair('C', make_pair('E', 1)); 
   Street st7(streetName, 30, 2);
   v.push_back(st7);
   streetName = make_pair('C', make_pair('G', 2));
   Street st8(streetName, 30, 2);
   v.push_back(st8);
   streetName = make_pair('D', make_pair('F', 2));
   Street st9(streetName, 30, 2);
   v.push_back(st9);
   streetName = make_pair('E', make_pair('F', 1));
   Street st10(streetName, 40, 2);
   v.push_back(st10);
   streetName = make_pair('F', make_pair('G', 5));
   Street st11(streetName, 90, 6);
   v.push_back(st11);
   streetName = make_pair('F', make_pair('J', 3));
   Street st12(streetName, 70, 3);
   v.push_back(st12);
   streetName = make_pair('G', make_pair('I', 1));
   Street st13(streetName, 60, 3);
   v.push_back(st13);
   streetName = make_pair('I', make_pair('H', 1));
   Street st14(streetName, 60, 3);
   v.push_back(st14);
   streetName = make_pair('I', make_pair('K', 1));
   Street st15(streetName, 60, 3);
   v.push_back(st15);
   streetName = make_pair('H', make_pair('K', 1));
   Street st16(streetName, 40, 2);
   v.push_back(st16);
   streetName = make_pair('K', make_pair('L', 2));
   Street st17(streetName, 60, 3);
   v.push_back(st17);
    cout << endl;
        cout << "      ***********************************************" << endl;
        cout << "                *          SMART MAP           *" << endl;
        cout << "      ***********************************************" << endl
             << endl;
        cout << "                    Welcome to the smart map!" << endl;
    int choice = 0;
    while (choice != 4)
    {
        cout << endl;
        cout << "What would you like to do?" << endl;
        cout << "   1. View streets information" << endl;
        cout << "   2. Find the way" << endl;
        cout << "   3. Add your location" << endl;
        cout << "   4. Exit." << endl;
        cout << "Enter your choice: ";
        string s;
        cin >> s;
        if (!CheckInput(s, 4))
            cout << "Invalid choice. Please try again." << endl;
        else
            choice = s[0] - ('1' - 1);
        switch (choice)
        {
        case 1:
        {
            Edit();
            cout << "  Which street information would you like to receive?" << endl;
            for (int i = 0; i < 17; i++)
            {
                if(i<9) cout << "     " << i + 1 << "." << v[i].name.first << v[i].name.second.first  << "     ";
                else cout << "     " << i + 1 << "." << v[i].name.first  << v[i].name.second.first  << "    ";
                if ((i + 1) % 4 == 0)
                    cout << endl;
            }
            cout << endl;
            cout << "  Enter here: ";
            string Checking = "" ;
            cin >> Checking;
            if(!CheckInput(Checking,17))
            { 
                do{
                cout << "  Your selection does not match, please re-enter. " <<endl;
                cout << "    Enter here: ";
                cin >> Checking;
                } while(!CheckInput(Checking,17));
            }
            int Choice1 = 0, c = 1 ;
            for(int i=Checking.size()-1; i >= 0; i--)
            {
                Choice1= Choice1+(Checking[i]-('1'-1))*c;
                c=c*10;
            }
            v[Choice1 - 1].Print();
            Edit();
            break;
        }
        case 2:
        {
            Edit();
            cout << "   Enter starting point" << endl;
            cout << "     Enter here: ";
            string Start;
            cin >> Start;
            if (!CheckPoint(Start, v))
            {
                do
                {
                    cout << "  Location does not exist on the map. Please re-enter." << endl;
                    cout << "    Enter again here: ";
                    cin >> Start;
                } while (!CheckPoint(Start, v));
            }
            char a= Start[0];
            cout << "   Enter the end point" << endl;
            cout << "     Enter here: ";
            string End;
            cin >> End;
            if (!CheckPoint(End, v))
            {
                do
                {
                    cout << "  Location does not exist on the map. Please re-enter." << endl;
                    cout << "  Enter again here: ";
                    cin >> End;
                } while (!CheckPoint(End, v));
            }
            char b=End[0];
            cout << "   Minimum distance traveled from " << Start << " to " << End << endl;
            cout << "             " ;
            Dijkstra(a - 64, b - 64, v);
            cout << "(KM):Total path length" << endl;
            cout << "   The route with the shortest travel time" << endl;
            cout << "             " ;
            Dijkstra(a - 64, b - 64, ResetLeght(v));
            cout << "(h):Total estimated time" <<endl;
            Edit();
            break;
        }
        case 3:
        {
            Edit();
            AddPoint(v);
            Edit();
            break;
        }
        default:
            break;
        }
        if (choice != 4)
        { 
            string s="";
            if( !CheckInput(s,2) )
            { 
                do {
                    cout << "Do you want continue" << endl;
                    cout<< " 1.YES" <<endl;
                    cout<< " 2.NO"  <<endl;
                    cout<< "Enter here: ";
                    cin >> s;
                    } while ( !CheckInput(s,2) );
                if( s[0] == '2' ) choice = 4;
            }  
        }
        if(choice == 4) cout << endl << "           Good Bye! ";
    }
}