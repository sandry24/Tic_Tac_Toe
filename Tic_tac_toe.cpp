#include <bits/stdc++.h>
 
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;
#define pb push_back
#define mp make_pair
#define f first
#define s second

std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
std::uniform_int_distribution<> die{1, 9};
int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int dy[8] = {0, -1, -1, -1, 0, 1, 1, 1};

bool valid(pi pos){
    return ((pos.f >= 0) && (pos.f < 3) && (pos.s >= 0) && (pos.s < 3));
}

int next_Move(vector<char> a){
    int defend_move = -1, end_move = -1;
    for(int i = 0; i < 9; i++){
        int row = i / 3, col = i % 3;
        for(int j = 0; j < 8; j++){
            map<char, int> m;
            bool flag = 1;
            int space;
            for(int k = 0; k < 3; k++){
                int row1 = row + k * dx[j], col1 = col + k * dy[j];
                if(!valid({row1, col1})){
                    flag = 0;
                    break;
                }
                m[a[row1*3+col1]]++;
                if(a[row1*3+col1] == ' ')
                    space = row1*3+col1;
            }
            if(!flag)
                continue;
            if(m[' '] == 1 && m['O'] == 2)
                end_move = space;
            if(m[' '] == 1 && m['X'] == 2)
                defend_move = space;
        }
    }
    if(end_move != -1)
        return end_move+1;
    else if(defend_move != -1)
        return defend_move+1;
    return 0;
}

bool check(vector<char> a){
    for(int i = 0; i < 9; i++){
        int row = i / 3, col = i % 3;
        for(int j = 0; j < 8; j++){
            map<char, int> m;
            bool flag = 1;
            for(int k = 0; k < 3; k++){
                int row1 = row + k * dx[j], col1 = col + k * dy[j];
                if(!valid({row1, col1})){
                    flag = 0;
                    break;
                }
                m[a[row1*3+col1]]++;
            }
            if(!flag)
                continue;
            if(m['X'] == 3 || m['O'] == 3)
                return true;
        }
    }
    return false;
}

void output_Table(vector<char> a){
    cout << a[0] << " | " << a[1] << " | " << a[2] << '\n';
    cout << "--|---|--\n";
    cout << a[3] << " | " << a[4] << " | " << a[5] << '\n';
    cout << "--|---|--\n";
    cout << a[6] << " | " << a[7] << " | " << a[8] << '\n';
}

void solve(){
    cout << "Press 'Y' to play, 'N' to return\n";
    char ans; cin >> ans;
    while(ans == 'Y'){
        vi occupied(9); vector<char> elements(9); int i;
        for(int i = 0; i < 9; i++)
            elements[i] = ' ';
        output_Table(elements);
        int move;
        for(i = 0; i < 9; i++){
            if(i % 2 == 0){
                cout << "Please select a free cell(1-9): ";
                cin >> move;
                cout << '\n';
                while(occupied[move-1] == 1 || move > 9 || move < 1){
                    cout << "Please select a free cell(1-9): "; 
                    cin >> move;
                }
                occupied[move-1] = 1;
                elements[move-1] = 'X';
            } else {
                cout << "Generating a move: ";
                move = next_Move(elements);
                if(move != 0){
                    cout << move << '\n';
                    occupied[move-1] = 1;
                    elements[move-1] = 'O';
                } else {
                    move = die(mersenne);
                    while(occupied[move-1] == 1)
                        move = die(mersenne);
                    cout << move << '\n';
                    occupied[move-1] = 1;
                    elements[move-1] = 'O';
                }
            }
            cout << '\n';
            output_Table(elements);
            if(check(elements)){
                break;
            }
        }
        cout << '\n' << "GAME OVER\n";
        cout << '\n' << "Continue? Y/N\n";
        cin >> ans;
    }
    if(ans == 'N')
        cout << "Goodbye.\n";
}

int main()
{   
    //ios::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
}