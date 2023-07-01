#include "Street.cpp"
using namespace std;

vector<Street> ResetLeght(vector<Street> v); // Hàm quy doi quang duong sang thoi gian

void Input(vector<Street> st,vector<vector<pair<int, double>>>& adj); // Hàm tạo đồ thị.

void Dijkstra(int Start, int End,vector<Street> st); // Thuật toán Dijkstra.

bool CheckPoint(string s, vector<Street> v); // kiểm tra xem một địa điểm có tồn tại trên bản đồ hay không.

bool CheckInput(string s, int n); // Kiểm tra xem đầu vào của người dùng có hợp lệ hay không

const int maxn = 10001;
int NumPlaces = 12 ;// Số điểm trên bản đồ 
int NumStreet = 17;// Số đường đi được khởi tạo.
const double INF = 1e9; // tạo ra số thực vô cùng lớn

vector<Street> ResetLeght(vector<Street> v) // Hàm quy doi quang duong sang thoi gian
{
    vector<Street> vt;
    for (int j = 0; j < v.size(); j++)
    {
        double NewLength = ((v[j].name.second.second) / (v[j].maxspeed)); //v[j].name.second.second= độ dài quãng đường
        v[j].name.second.second = NewLength;
        vt.push_back(v[j]);
    }
    return vt;
}
  
void Input(vector<Street> st,vector<vector<pair<int, double>>>& adj) // Nhập thông tin vào vector các vector 
{         
    for (int i = 0; i < NumStreet; i++)
    {
        adj[st[i].name.first-64].push_back({st[i].name.second.first-64, st[i].name.second.second});//
        adj[st[i].name.second.first-64].push_back({st[i].name.first-64, st[i].name.second.second}); // Tạo đồ thi vô hướng
    }
}

void Dijkstra(int Start, int End,vector<Street> st) // Thuật toán Dijkstra
{
    vector<vector<pair<int, double>>> adj(NumPlaces+1); // khởi tạo vector các vector với số phần tử xin cấp phát là NumPlaces+1
    Input(st, adj); // thực hiện nhập vào adj tạo đồ thị.
    int pre[maxn];  // tạo mảng pre[] có tác dụng in ra đường đi ngắn nhất.
    vector<double> Distance(NumPlaces + 1, INF); // tạo vector số thực để khởi tạo khoảng cách đến mọi điểm, ban đầu khởi tạo khoảng cách là vô cùng.
    Distance[Start] = 0; // Cho khoảng cách đến điểm bắt đầu bằng 0.
    pre[Start] = Start; // cho pre[Start]=Start tức đường đi đến điểm khởi đầu là chính nó.
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> Q; // Khởi tạo hàng đợi ưu tiên theo thứ tự bé đến lớn
    Q.push({0, Start}); // push điểm đầu với chiều dài là 0.
    while (!Q.empty()) 
    {
        pair<double, int> top = Q.top();
        Q.pop();
        int u = top.second; 
        double Dis = top.first;
        if (Dis > Distance[u]) // kiểm tra xem điểm này đã được thăm trước đó chưa.
            continue;
        for (auto it : adj[u]) // it là pair gồm điểm lân cận và khoảng cách từ điểm lân cận đến điểm đang xét.
        {
            int v = it.first;  //  v là điểm lân cận
            double w = it.second; // w là khoảng cách từ điểm lân cận đến điểm đang xét.
            if (Distance[v] > Distance[u] + w) // Nếu khoảng cách từ Start đến v lớn hơn tổng khoách cách từ Start đến u kết hợp với w.
            {
                Distance[v] = Distance[u] + w; // Tiến hành cài đặt lại k/c rừ Start đến v;
                Q.push({Distance[v], v}); // push điểm v và k/c của v vào Q.
                pre[v] = u; // đặt điểm trước v là u
            }
        }
    }
    vector<int> path; // tạo vector path để in thứ tự các điểm trên đường đi từ Start đến End  
    int p=End; // Tạo p bằng End để in ra chiều dài tử start đến End thông qua 
    while (1)
    {
        path.push_back(End); // đưa vị trị End vào vector path.
        if (End == Start) 
            break;
        End = pre[End]; // thay End bằng điểm trước End để có thể đi từ Start đến End. 
    }
    reverse(begin(path), end(path)); // Đảo thứ tự vector path.
    for (int i = 0; i < path.size(); i++) // thực hiện vòng for để in đường đi
    {
        if (i == path.size() - 1)
            cout << char(path[i] + 64) << endl;
        else
            cout << char(path[i] + 64) << " -> ";
    }
    cout << "        " << Distance[p]; // in khoảng cách ngắn nhất từ Start đến End thông qua p.
}

bool CheckPoint(string s, vector<Street> v) // kiểm tra xem một địa điểm có tồn tại trên bản đồ hay không.
{
    if (s.length() != 1)
        return false;
    for (int i=0;i<v.size();i++)
    {
        if (v[i].name.first == s[0] || v[i].name.second.first == s[0])   
            return true;
    }
    return false;
}
 
 bool CheckInput(string s, int n) // Kiểm tra xem đầu vào của người dùng có hợp lệ hay không. chua dung
{
    if (s.size() > (n / 10) + 1)
        return false;
    int c=1,Count=0;
    for(int i=s.size()-1; i >= 0; i--)
    {
            if(s[i] > '9' || s[i] < '0' ) return false;
            Count= Count+(s[i]-('1'-1))*c;
            c=c*10;
    }
    for (int i = 1; i <= n; i++)
    {
        if (i==Count)
            return true;
    }
    return false;
}

void AddPoint(vector<Street> &v) // Cho phép người dùng thêm một địa điểm mới vào bản đồ và cập nhật đồ thị tương ứng.
{ 
      cout << "  Which Street are you on on the map? " << endl;
      for (int i = 0; i < v.size(); i++)
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
        int choice1 = 0, c = 1 ;
        for(int i=Checking.size()-1; i >= 0; i--)
        {
            choice1= choice1+(Checking[i]-('1'-1))*c;
            c=c*10;
        }
    double l;
    cout << "   The distance from your location to location " << v[choice1-1].name.first <<" (km)" << endl;
    cout << "     Enter here: ";
    cin >> l;
    if(l < 0 || l > v[choice1-1].name.second.second)
    {
        do
        {
            cout << "   The distance you selected is not valid, please choose again " << endl;
            cout << "     Enter here: ";
            cin >> l;
        } while (l < 0 || l > v[choice1-1].name.second.second);
    }
    NumPlaces++; 
    NumStreet=NumStreet+2;
    pair<char, pair<char, double>> streetName = make_pair(char(NumPlaces+64), make_pair(v[choice1-1].name.first, l));
    Street st1(streetName, v[choice1-1].maxspeed , v[choice1-1].numLanes);
    streetName = make_pair(char(NumPlaces+64), make_pair(v[choice1-1].name.second.first, v[choice1-1].name.second.second - l));
    Street st2(streetName, v[choice1-1].maxspeed , v[choice1-1].numLanes);
    v.push_back(st2);
    v.push_back(st1);
    cout << "   You have successfully added the location." << endl;
    cout << "   Your position is called " << char(NumPlaces + 64) << endl;
}

void Edit()
{
    for(int i = 0; i < 30; i++)
    {
        cout <<"*"<<"-";
    }
    cout << endl;
}