#include <bits/stdc++.h>
#include <fstream>
#include <ctime>

#define pb push_back
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define cy cout << "YES" << endl
#define cn cout << "NO" << endl
using namespace std;

map<string,string> contact_info;

class SMS
{
public:
    string sender;
    string receiver;
    string message;
    string date;
    string contactNumber;
    SMS *next;

    SMS(string s, string r, string m, string date)
    {
        this->sender = s;
        this->receiver = r;
        this->message = m;
        this->date = date;
        next = NULL;
    }
};

class Linkedlist
{
public:
    SMS *head;
    Linkedlist()
    {
        head = NULL;
    }
    void addSMS(string s, string r, string m, string date)
    {
        SMS *newNode = new SMS(s, r, m, date);
        if (head == NULL)
        {
            head = newNode;
        }
        else
        {
            SMS *curr = head;
            while (curr->next)
            {
                curr = curr->next;
            }
            curr->next = newNode;
        }
    }

    void display(SMS *curr,int c){
        cout << endl;
        cout << "Message number :" << c << endl;
        cout << "From :" << curr->sender << ' ';
        cout << contact_info[curr->sender] << endl;
        cout << "To :" << curr->receiver << ' ';
        cout << contact_info[curr->receiver] << endl;
        cout << "Message :" << curr->message << endl;
        cout << "Date:" << curr->date << endl;
    }

    void displayall(){
        cout << "INBOX" << endl;
        SMS *curr = head;
        int c = 1;
        while (curr)
        {
            display(curr,c);
            curr = curr->next;
            c += 1;
        }
    }

    void displayUserMessage(string user)
    {
        SMS *curr = head;
        int c = 1;
        while (curr)
        {
            if (curr->sender == user || curr->receiver == user)
            {
                display(curr,c);
            }
            curr = curr->next;
            c += 1;
        }
    }
    void displayDateMessage(string d)
    {
        SMS *curr = head;
        int c = 1;
        while (curr)
        {
            if (curr->date == d)
            {
                display(curr,c);
            }
            curr = curr->next;
            c += 1;
        }
    }
    void SearchMessage(string k)
    {
        SMS *curr = head;
        int c = 1;
        while (curr)
        {
            if (curr->message.find(k) != string ::npos)
            {
                display(curr,c);
            }
            curr = curr->next;
            c += 1;
        }
    }
    void deleteMessage(int de)
    {
        SMS *curr = head;
        SMS *prev = NULL;
        ofstream outFile("deleted_sms.txt", ios::app);
        int cnt=1;
        while (curr)
        {
            if (cnt==de)
            {
                if (prev)
                {
                    prev->next = curr->next;
                }
                else
                {
                    head = curr->next;
                }
                cout << "Your Message has been deleted and transfer into txt file." << endl;
                outFile << "From :" << curr->sender << ' '
                        << contact_info[curr->sender] << endl
                        << "To :" << curr->receiver << ' '
                        << contact_info[curr->receiver] << endl
                        << "Message :" << curr->message << endl
                        << "Date:" << curr->date << endl;
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
            cnt++;
        }
        outFile.close();
    }
};
int main()
{
    Linkedlist list;
    while (true)
    {
        list.displayall();
        cout << endl;
        cout << "SMS Portal Menu:" << endl;
        cout << "1. Add SMS" << endl;
        cout << "2. Display Messages by User" << endl;
        cout << "3. Display Messages by Date" << endl;
        cout << "4. Search Messages" << endl;
        cout << "5. Delete SMS" << endl;
        cout << "6. Exit" << endl<<endl;
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            string s, r, m, d, num, n1, n2;
            cout << endl;
            while (1){
                cout << "From (number):";
                cin >> s;
                if (s.size() == 10 && regex_match(s, regex("[0-9]+"))){ break;}
                else{ cout << "Error Try Again. " << endl; }
            }
            if (contact_info.count(s) > 0){
                cout << "Name : " << contact_info[s] << endl;
            } else{
                cout << "Enter (name): ";
                cin >> n1; 
                contact_info[s] = n1;
            }

            while (1){
                cout << "To (number):";
                cin >> r;
                if (r.size() == 10 && regex_match(r, regex("[0-9]+"))){ break;}
                else{ cout << "Error Try Again. " << endl; }
            }
            if (contact_info.count(r) > 0){
                cout << "Name : " << contact_info[r] << endl;
            } else{
                cout << "Enter (name): ";
                cin >> n2;
                contact_info[r] = n2;
            }

            cout << "Message :";
            cin.ignore();
            getline(cin, m);

            time_t now = time(0);
            tm *ltm = localtime(&now);
            d = to_string(ltm->tm_mday) + '-' + to_string(1+ltm->tm_mon) + '-' + to_string(1900+ltm->tm_year);

            list.addSMS(s, r, m, d);
            cout <<endl<< "SMS is added successfully." << endl;
        }
        if (choice == 2)
        {
            string k;
            cout << "Enter User Number :";
            cin >> k;
            list.displayUserMessage(k);
        }
        if (choice == 3)
        {
            string k2;
            cout << "Enter Date :";
            cin >> k2;
            list.displayDateMessage(k2);
        }
        if (choice == 4)
        {
            string s;
            cout << "Enter search keyword : ";
            
            cin >> s;
            list.SearchMessage(s);
        }
        if (choice == 5)
        {
            int de;
            cout << "Enter the message number: ";
            cin >> de;
            list.deleteMessage(de);
        }
        if (choice == 6)
        {
            break;
        }
        string trash;
        cout <<endl<< "Enter somthing to continue." << endl;
        cin >> trash;
        system("cls");
    }
    return 0;
}
