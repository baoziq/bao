#include<iostream>
using namespace std;
struct Node {
	int a;
	int no;
	Node* next;
};
void show(Node* head){
	Node* p=head;
	while(p){
		cout << p->a << ' ' ;
		p=p->next;
	}
	cout << endl;
}
void cer(Node* head) {
	Node* p=head;
	int count=1;
	while(p) {
		p->no=count;
		count++;
		p=p->next;
	}
}
void insert(Node* &head,int n) {
	Node* p=head;
	Node* node=new Node;
	node->a=0;
	node->next=NULL;
	while(p) {
		if(p->no==n) {
			node->next=p->next;
			p->next=node;
		}
		p=p->next;
	}
}
void zen(Node* &head,int n){
	Node* p=head;
	while(p){
		if(p->no==n) p->a=p->a+1;
		p=p->next;
	}
	
}
void del(Node* & head,int key) {
	Node* p;
	if(head->no==key) {
		p=head;
		head=head->next;
		delete p;
		return;
	}
	for(Node* pg=head; pg->next; pg=pg->next) {
		if(pg->next->no==key) {
			p=pg->next;
			pg->next=p->next;
			delete p;
			p=NULL;
			return;
		}
	}
}
int main() {
	Node* node1=new Node;
	node1->a=3;
	Node* head=node1;
	Node* node2=new Node;
	node2->a=7;
	node1->next=node2;
	Node* node3=new Node;
	node3->a=1;
	node2->next=node3;
	node3->next=NULL;
	Node* p=head;
	cer(head);
	show(head);
	int a;
	while(cin >>a && a!=0){
		if(a==1){
			int b;
			cin >> b;
			insert(head,b);
			cer(head);
			show(head);
		}
		if(a==2){
			int b;
			cin >> b;
			zen(head,b);
			cer(head);
			show(head);
		}
		if(a==3){
			int b;
			cin >> b;
			del(head,b);
			cer(head);
			show(head);
		}
	} 
	
}
