#include <bits/stdc++.h>
using namespace std;

bool isCapital(string str){
    char stmp = str[0];
    if(isupper(stmp))
        return true;
    return false;
}

unordered_map <char,vector <char>> umpfirst;
void findfirst(vector <string> production){ 
    for(int i=0;i<production.size();i++){
        string s = production[i],mn="",tmp="";
        vector <char> crtmp;
        for(int j = 0;j < s.size();j++){
            if(s[j] == '|'){
                umpfirst[mn[0]].push_back(s[j+1]);
            }
            else if(s[j] == '-' && s[j+1] == '>'){
                mn = tmp;
                tmp = "";
                umpfirst[mn[0]].push_back(s[j+2]);
                j++;
            }
            else{
                tmp += s[j];
            }
        }
    }
    cout << "First: " << endl;
    for(auto &it:umpfirst){
        cout << it.first << " ";
        for(auto &jt:it.second){
            if(isupper(jt)){
                for(auto &bt:umpfirst[jt]){
                    cout << bt << " ";
                } 
            }
            else{
                cout << jt << " ";
            }
        }
        cout << endl;
    }
    return;
}

void findfollow(vector <string> production){
    unordered_map <char,vector <char>> ump;
    vector <string> temp;
    ump['S'].push_back('$');
    for(int i=0;i<production.size();i++){
        string st = production[i],mn="",tmp="";
        for(int j=0;j<st.size();j++){
            if(st[j]=='|'){
                if(isupper(tmp[tmp.size()-1])){
                    tmp += mn;
                }
                temp.push_back(tmp);
                tmp = "";
            }
            else if(st[j] == '-' && st[j+1] == '>'){
                mn = tmp;
                tmp = "";
                j++;
            }
            else{
                tmp+=st[j];
            }
        }
        if(isupper(tmp[tmp.size()-1])){
            tmp += mn;
        }
        temp.push_back(tmp);
    }
    for(auto &it: temp){
        string s = it;
        for(int i=0;i<s.size();i++){
            if(isupper(s[i])){
                if(i+1 < s.size()){
                    ump[s[i]].push_back(s[i+1]);
                }
            }
        }
    }
    cout << "Follow: " << endl;
    for(auto &it:ump){
         cout << it.first << " ";
        for(auto &jt:it.second){
            if(jt == it.first){
                for(auto &bt:umpfirst[jt]){
                    if(!isupper(bt)){
                        cout << bt << " ";
                    }
                }
            }
            else if(isupper(jt)){
                for(auto &bt:ump[jt]){
                    cout << bt << " ";
                }
            }
            else{
                cout << jt << " ";
            }
        }
        cout << endl;
    }
    return;
}

void parsing_table(vector <string> production){
    set <char> up,lw;
    unordered_map <char,vector <string>> umpmax;
    for(int i=0;i<production.size();i++){
        string st = production[i],tmp="",mn="";
        for(int j=0;j<st.size();j++){
            if(isupper(st[j])){
                up.insert(st[j]);
            }
            if(islower(st[j])){
                lw.insert(st[j]);
            }
            if(st[j]=='|'){
                umpmax[mn[0]].push_back(tmp);
                tmp = "";
                tmp += mn;
                tmp += "->";
            }
            else if(st[j] == '-' && st[j+1] == '>'){
                mn = tmp;
                tmp = "";
                tmp += mn;
                tmp += "->";
                j++;
            }
            else{
                tmp+=st[j];
            }
        }
        umpmax[mn[0]].push_back(tmp);
    }
    
    for(auto &it:up){
        for(auto &bt:lw){
            cout << it << "-" << bt << " -> ";
            bool tu = false;
            for(auto jt:umpmax[it]){
                if(jt[3] == bt){
                    cout << jt << endl;
                    tu = true;
                    break;
                }
            }
            if(!tu){
                cout << umpmax[it][0] << endl;
            }
        }
    }
}

int main(){
    int n;
    cin >> n;
    vector <string> production;
    string input;
    for(int i=0;i<n;i++){
        cin >> input;
        production.push_back(input);
    }
    cout << endl;
    findfirst(production);
    cout << endl;
    findfollow(production);
    cout << endl;
    parsing_table(production);
    return 0;
}