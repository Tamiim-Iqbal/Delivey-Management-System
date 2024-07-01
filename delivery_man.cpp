#include<bits/stdc++.h>
using namespace std;
const int N = 100;
int dis[N];
vector<pair<int,int>>v[N];
class cmp
{
    public:
        bool operator()(pair<int,int> a, pair<int,int> b)
        {
            return a.second > b.second;
        }
};
void dijkstra(int src)
{
    priority_queue<pair<int,int>,vector<pair<int,int>>,cmp> pq;
    pq.push({src,0});
    dis[src]=0;
    while(!pq.empty())
    {
        pair<int,int> par = pq.top();
        pq.pop();
        int node = par.first;
        int cost = par.second;
        for(pair<int,int> c: v[node])
        {
            int childNode = c.first;
            int childCost = c.second;
            if(cost+childCost < dis[childNode])
            {
                //path relax
                dis[childNode] = cost+childCost;
                pq.push({childNode,dis[childNode]});
            }
        }
    }
}
struct DeliveryBoy
{
    string name;
    string contact;
    int task = 0;
    int salary = 0;
    vector<pair<int, int>> result;
};
map<int, DeliveryBoy> deliveryBoy;

// option 1
void add_a_delivery_boy()
{
    int id;
    string name, contact;

    cout<<"Enter Id: ";
    cin>>id;
    cin.ignore();

    cout<<"Enter Name: ";
    getline(cin, name);

    cout<<"Enter Contact: ";
    getline(cin, contact);

    DeliveryBoy  newDeliveryBoy;
    newDeliveryBoy.name = name;
    newDeliveryBoy.contact = contact;

    deliveryBoy[id] = newDeliveryBoy;
    cout<<endl<<"Delivery Boy Inserted Successfully"<<endl<<endl;

}
//option 2
void remove_a_delivery_boy()
{
    int id;
    cout<<"Enter Id of the delivery boy to unregester: ";
    cin>>id;

    if(deliveryBoy.find(id) != deliveryBoy.end())
    {
        deliveryBoy.erase(id);
        cout<<endl<<"Successfully unregester delivery boy "<<id<<endl<<endl;
    }
    else
    {
        cout<<endl<<"Delivery boy with id "<<id<<" does not exist"<<endl<<endl;
    }
}
//option 3
void display_all_delivery_boy()
{
    cout<<endl<<"Delivery boys: "<<endl;
    cout<<"ID "<<" Name  "<<"  Contact"<<endl;
    for(auto pair : deliveryBoy)
    {
        cout<<pair.first<<"   "<<pair.second.name<<"   "<<pair.second.contact<<" "<<endl;
    }
    cout<<endl;
}
//option 4
void delivery()
{
    int id, newTask;
    cout << "Enter delivery boy Id: ";
    cin >> id;

    auto it = deliveryBoy.find(id);
    if(it != deliveryBoy.end())
    {
        cout << "Enter new task number: ";
        cin >> newTask;
        //it->second.task = newTask;
        deliveryBoy[id].task = newTask;
        cout <<endl<< "Task updated successfully for delivery boy " << id << endl;
    }
    else
    {
        cout <<endl<< "Delivery boy with ID " << id << " does not exist" << endl<<endl;;
        return;
    }
    cout<<"Enter total places & number of road (node & edges): ";
    int n,e;
    cin>>n>>e;
    cout<<"Enter source, destination, cost "<<e <<" times: "<<endl;
    while (e--)
    {
        int a,b,c;
        cin>>a>>b>>c;
        v[a].push_back({b,c});
        v[b].push_back({a,c});
    }
    vector<pair<int, int>> &result = deliveryBoy[id].result;
    //result.clear();
    deliveryBoy[id].result.clear();
    for(int i=0; i<n; i++)
    {
        dis[i]=INT_MAX;
    }
    dijkstra(0);
    for(int i=0; i<n; i++)
    {
        //cout<<i<<"->"<<dis[i]<<endl;
        result.push_back({i,dis[i]});
    }
    cout<<"Successfully placed order"<<endl<<endl;
}
//option 5
void assignted_task()
{
    cout<<endl<<"Delivery boys: "<<endl;
    cout<<"ID "<<" Name  "<<"  Contact  "<<"Task Number "<<endl;
    for(auto pair : deliveryBoy)
    {
        cout<<pair.first<<"   "<<pair.second.name<<"   "<<pair.second.contact<<"    "<<pair.second.task<<endl;
    }
    cout<<endl;
}
//option 6
void display_path()
{
    int id;
    cout<<"Enter id to view output: ";
    cin>>id;
    auto it = deliveryBoy.find(id);
    if(it != deliveryBoy.end())
    {
        //vector<pair<int, int>> result = it->second.result;
        //result.clear();
        if(deliveryBoy[id].task==0)
        {
            cout <<endl<< "No order placed for delivery boy " << id << endl<<endl;
            return;
        }
        cout<<endl<<"Delivery boy id: "<<id<<" Task Number: "<<deliveryBoy[id].task<<endl;
        cout<<"Source : 0"<<endl;
        cout<<"Distance"<<" "<<"Cost"<<endl;
        for (size_t i = 0; i < it->second.result.size(); i++)
        {
            cout<<deliveryBoy[id].result[i].first<<"   ->   "<<deliveryBoy[id].result[i].second<<endl;
        }
        cout<<endl;
    } 
    else
    {
        cout <<endl<< "Delivery boy with ID " << id << " does not exist" << endl<<endl;
    }
}
//option 7
void cancel_delivery()
{
    int id;
    cout<<"Enter id to cancel delivery: ";
    cin>>id;
    auto it = deliveryBoy.find(id);
    if(it != deliveryBoy.end())
    {
        deliveryBoy[id].result.clear();
        it->second.task = 0;
        cout <<endl<< "Delivery canceled successfully for delivery boy " << id << endl<<endl;
    }
    else
    {
        cout <<endl<< "Delivery boy with ID " << id << " does not exist" << endl<<endl;
    }
}
//option 8
void salary()
{
    for(auto &pair : deliveryBoy)
    {
        int salary = 0;
        for(auto result : pair.second.result)
        {
            salary += result.second; 
        }
        salary = salary*10;
        pair.second.salary = salary;
    }
    cout<<endl<<"ID "<<" Name  "<<" Contact"<<"  Salary"<<endl;
    for(auto pair : deliveryBoy)
    {
        cout<<pair.first<<"   "<<pair.second.name<<"  "<<pair.second.contact<<"  1  "<<pair.second.salary<<endl;
    }
    cout<<endl; 
}
//option 9
void display_invoice()
{
    int task;
    cout<<"Enter task number to view statement: ";
    cin>>task;
    
    bool found = false;
    for(auto &pair : deliveryBoy)
    {
        if(pair.second.task == task)
        {
            found = true;
            cout <<endl<< "***** Invoice for task: " << task << "*****" << endl;
            cout<<"Order \tBils"<<endl;
            for(const auto &result : pair.second.result)
            {
                if(result.first == 0) continue; 
                int bill = result.second * 10; 
                
                cout << result.first << "\t" << bill << "$"<<endl;
            }
            cout << endl;
        }
    }
    if(!found)
    {
        cout <<endl<< "No delivery found with task number: " << task<<endl<<endl;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int option;
    while(true)
    {
        cout<<"Choose option: "<<endl;
        cout<<"1. Register Delivery Boy"<<endl;
        cout<<"2. Unregister Delivery Boy"<<endl;
        cout<<"3. List of Delivery Boy"<<endl;
        cout<<"4. Place Delivery"<<endl;
        cout<<"5. Assignted Tasks"<<endl;
        cout<<"6. View Delivery Boy Task"<<endl;
        cout<<"7. Cancel Delivery"<<endl;
        cout<<"8. Salary Summary"<<endl;
        cout<<"9. Display Invoice"<<endl;
        cout<<"10. Exit"<<endl;
        cout<<endl;
        cout<<"Enter option: ";
        cin>>option;

        switch(option)
        {
            case 1: 
                add_a_delivery_boy();
                break;
            case 2:
                remove_a_delivery_boy();
                break;
            case 3:
                display_all_delivery_boy();
                break;
            case 4:
                delivery();
                break;
            case 5:
                assignted_task();
                break;
            case 6:
                display_path();
                break;
            case 7:
                cancel_delivery();
                break;
            case 8:
                salary();
                break;
            case 9:
                display_invoice();
                break;
            case 10:
                cout<<"Existing program..."<<endl;
                cout<<"Program returned successfully"<<endl<<endl;
                return 0;
            default:
                cout<<"Invalid choice. Please enter a valid option"<<endl<<endl;
        }
    }
    return 0;
}

/*
Sample Graph:
4 5
0 1 5
0 2 2
1 2 1
1 3 7
2 3 2


5 6
0 1 3
0 2 4
0 3 6
1 4 1
1 3 9
2 5 5
*/