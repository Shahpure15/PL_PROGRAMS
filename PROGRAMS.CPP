// Program: Left and right rotation of an array by k positions

#include <iostream>
using namespace std;

void rotateLeft(int arr[], int n, int k){
    k %= n;
    while(k--){
        int temp = arr[0];
        for(int i = 0; i < n - 1; i++)
            arr[i] = arr[i+1];
        arr[n-1] = temp;
    }
}

void rotateRight(int arr[], int n, int k){
    k %= n;
    while(k--){
        int temp = arr[n-1];
        for(int i = n-1; i > 0; i--)
            arr[i] = arr[i-1];
        arr[0] = temp;
    }
}

int main(){
    int a[] = {3,6,9,12,15};
    int n = 5;
    int k = 2;

    cout << "Original array: ";
    for(int x : a) cout << x << " ";

    rotateLeft(a,n,k);
    cout << "\nLeft rotated: ";
    for(int x : a) cout << x << " ";

    rotateRight(a,n,k);
    cout << "\nRight rotated (should restore original): ";
    for(int x : a) cout << x << " ";

    return 0;
}

// Matrix addition and multiplication using 2D array logic

#include <iostream>
using namespace std;

int main(){
    int A[2][2] = {{1,2},{3,4}};
    int B[2][2] = {{5,6},{7,8}};
    int C[2][2];

    // Addition
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            C[i][j] = A[i][j] + B[i][j];

    cout << "Addition Result:\n";
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++) cout << C[i][j] << " ";
        cout << endl;
    }

    // Multiplication
    int M[2][2];
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            M[i][j] = 0;
            for(int k=0;k<2;k++)
                M[i][j] += A[i][k] * B[k][j];
        }
    }

    cout << "\nMultiplication Result:\n";
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++) cout << M[i][j] << " ";
        cout << endl;
    }
    return 0;
}

// Addition of two polynomials using linked list

#include <iostream>
using namespace std;

struct Node{
    int coef, pow;
    Node* next;
};

Node* insert(Node* head, int c, int p){
    Node* temp = new Node{c, p, head};
    return temp;
}

Node* add(Node* x, Node* y){
    Node* res = nullptr;
    while(x && y){
        if(x->pow > y->pow){
            res = insert(res, x->coef, x->pow);
            x = x->next;
        }
        else if(x->pow < y->pow){
            res = insert(res, y->coef, y->pow);
            y = y->next;
        }
        else{
            res = insert(res, x->coef + y->coef, x->pow);
            x = x->next; y = y->next;
        }
    }
    while(x){ res = insert(res, x->coef, x->pow); x = x->next; }
    while(y){ res = insert(res, y->coef, y->pow); y = y->next; }

    return res;
}

void print(Node* t){
    while(t){
        cout << t->coef << "x^" << t->pow;
        if(t->next) cout << " + ";
        t = t->next;
    }
    cout << endl;
}

int main(){
    Node *P=nullptr, *Q=nullptr;
    P = insert(P,3,2); P = insert(P,4,1); P = insert(P,5,0);
    Q = insert(Q,2,2); Q = insert(Q,1,1); Q = insert(Q,3,0);

    Node* R = add(P,Q);
    print(R);
    return 0;
}

// Merge one doubly linked list into another (alternate nodes) and sort

#include <iostream>
using namespace std;

struct DNode{
    int data;
    DNode *prev, *next;
};

void addNode(DNode*& head,int x){
    DNode* t = new DNode{x,nullptr,nullptr};
    if(!head){ head=t; return; }
    DNode* c=head;
    while(c->next) c=c->next;
    c->next=t;
    t->prev=c;
}

void mergeAlternate(DNode*& A, DNode*& B){
    DNode *t1=A,*t2=B;
    while(t1 && t2){
        DNode* bn = t2->next;
        t2->next = t1->next;
        if(t1->next) t1->next->prev = t2;
        t1->next = t2;
        t2->prev = t1;
        t1 = t2->next;
        t2 = bn;
    }
    B = nullptr;
}

void sortList(DNode*& h){
    for(DNode* i=h;i;i=i->next)
        for(DNode* j=i->next;j;j=j->next)
            if(i->data > j->data)
                swap(i->data,j->data);
}

void show(DNode* h){
    while(h){ cout<<h->data<<" "; h=h->next; }
    cout<<endl;
}

int main(){
    DNode *A=nullptr,*B=nullptr;
    addNode(A,50);addNode(A,10);addNode(A,40);
    addNode(B,20);addNode(B,30);

    mergeAlternate(A,B);
    sortList(A);
    show(A);
}

// Circular linked list railway reservation demo

#include <iostream>
using namespace std;

struct Seat{
    int id;
    string passenger;
    bool free;
    Seat* link;
};

Seat* generate(int n){
    Seat *head=nullptr,*prev=nullptr;
    for(int i=1;i<=n;i++){
        Seat* t = new Seat{i,"",true,nullptr};
        if(!head) head=t;
        else prev->link = t;
        prev = t;
    }
    prev->link = head;
    return head;
}

int main(){
    Seat* head = generate(4);
    Seat* t=head;
    t->free=false; t->passenger="Zaki"; t=t->link;

    cout << "Seat status:\n";
    for(int i=0;i<4;i++){
        cout << "Seat " << t->id << ": " << (t->free?"Free":"Booked") << endl;
        t=t->link;
    }
}

// 8 Queens using stack-based backtracking

#include <iostream>
#include <vector>
using namespace std;

bool safe(const vector<int>& pos,int r,int c){
    for(int i=0;i<r;i++)
        if(pos[i]==c || abs(pos[i]-c)==abs(i-r))
            return false;
    return true;
}

int main(){
    vector<int> pos(8,-1);
    int r=0,c=0;
    while(r<8){
        while(c<8 && !safe(pos,r,c)) c++;
        if(c<8){
            pos[r]=c;
            r++; c=0;
        }
        else{
            r--;
            if(r<0) break;
            c=pos[r]+1;
        }
    }

    cout << "Solution:\n";
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++)
            cout << (pos[i]==j?"Q ":"- ");
        cout << endl;
    }
}

// Recursive Tower of Hanoi program

#include <iostream>
using namespace std;

void hanoi(int n,char A,char B,char C){
    if(n==0) return;
    hanoi(n-1,A,C,B);
    cout << "Move disk " << n << " from " << A << " to " << C << endl;
    hanoi(n-1,B,A,C);
}

int main(){
    hanoi(3,'A','B','C');
}

// Simple priority queue simulation for patients

#include <iostream>
#include <vector>
using namespace std;

struct Patient{ string name; int pr; };

int main(){
    vector<Patient> pq = { {"Sam",3},{"Ali",1},{"John",2} };

    while(!pq.empty()){
        int best=0;
        for(int i=1;i<pq.size();i++)
            if(pq[i].pr < pq[best].pr)
                best = i;

        cout<<"Serving: "<<pq[best].name<<endl;
        pq.erase(pq.begin()+best);
    }
}

// FCFS and SJF scheduling (non-preemptive)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct P{ int pid, at, bt; };

int main(){
    vector<P> job = {{1,0,5},{2,2,3},{3,4,1}};
    
    cout<<"\nFCFS:\n";
    sort(job.begin(),job.end(),[](P a,P b){ return a.at<b.at; });
    int t=0;
    for(auto &p:job){
        if(t<p.at) t=p.at;
        cout<<"P"<<p.pid<<" starts at "<<t<<endl;
        t+=p.bt;
    }

    cout<<"\nSJF:\n";
    vector<bool> done(job.size(),false);
    t=0; int finished=0;
    while(finished < job.size()){
        int idx=-1;
        for(int i=0;i<job.size();i++)
            if(!done[i] && job[i].at<=t && (idx==-1 || job[i].bt < job[idx].bt))
                idx=i;

        if(idx==-1){ t++; continue; }

        cout<<"P"<<job[idx].pid<<" starts at "<<t<<endl;
        t+=job[idx].bt;
        done[idx]=1;
        finished++;
    }
}

// Palindrome check using deque

#include <iostream>
#include <deque>
using namespace std;

int main(){
    string s = "Racecar";
    deque<char> dq;

    for(char ch:s) dq.push_back(tolower(ch));

    while(dq.size()>1 && dq.front()==dq.back()){
        dq.pop_front();
        dq.pop_back();
    }

    cout << (dq.size()<=1 ? "Palindrome" : "Not Palindrome");
}

// Phonebook stored in sorted order, sentinel search used

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Rec{ string n,p; };

int main(){
    vector<Rec> pb = {{"Zara","123"},{"Aman","456"},{"John","789"}};
    sort(pb.begin(),pb.end(),[](Rec a,Rec b){ return a.n<b.n; });

    string key; cout<<"Search name: "; cin>>key;

    pb.push_back({key,""});
    int i=0;
    while(pb[i].n != key) i++;

    if(i < pb.size()-1)
        cout<<"Found: "<<pb[i].n<<" -> "<<pb[i].p;
    else{
        cout<<"Not found. Enter phone: ";
        cin >> pb[i].p;
        sort(pb.begin(),pb.end(),[](Rec a,Rec b){ return a.n<b.n; });
    }
}

// Merge sort on array of floating numbers

#include <iostream>
using namespace std;

void merge(float a[],int l,int m,int r){
    int i=l,j=m+1,k=0;
    float tmp[50];

    while(i<=m && j<=r)
        tmp[k++] = (a[i] < a[j]) ? a[i++] : a[j++];

    while(i<=m) tmp[k++] = a[i++];
    while(j<=r) tmp[k++] = a[j++];

    for(int x=0;x<k;x++) a[l+x] = tmp[x];
}

void mergesort(float a[],int l,int r){
    if(l<r){
        int m=(l+r)/2;
        mergesort(a,l,m);
        mergesort(a,m+1,r);
        merge(a,l,m,r);
    }
}

int main(){
    float per[] = {65.4,91.2,72.6,58.1};
    mergesort(per,0,3);

    for(float x: per) cout << x << " ";
}

// Hash table (separate chaining) for scores per over

#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> data = {10,5,4,14,15,20,1,11,6,16,36,28};
    vector<vector<int>> table(12);

    for(int x:data)
        table[x % 12].push_back(x);

    for(int i=0;i<12;i++){
        cout << i << ": ";
        for(int v:table[i]) cout<<v<<" -> ";
        cout<<"NULL\n";
    }
}

// Hash table for medical shop stock using modulo hashing

#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> keys = {101,67,89,23,54};
    vector<vector<int>> H(9);

    for(int k:keys)
        H[k % 9].push_back(k);

    for(int i=0;i<9;i++){
        cout<<i<<" : ";
        for(int x:H[i]) cout<<x<<" -> ";
        cout<<"NULL\n";
    }
}
