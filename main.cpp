#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
//sizeof instead of rand with certain index

//TODO CHANGE TO COPY

using namespace std;

const string names[]={"Chandler", "Joey", "Rachel", "Phoebe", "Monika", "Ross", "Jannice", "Julie"};

const string postArchive[]={"Hello", "Bye-Bye" ,"LoL", "How you doin'?", "Chick and Duck", "Du be da be da"};

const string titles[]={"Introduction", "Finale", "Summary"};

const string subjects[]={"Sports", "Science", "Cooking", "Hobbies"};

const string forumTitle[]={"Programming","Movies","Gaming"};

int id=0; //for incrementing post_number

//time for current date
time_t now = time(0);
tm* ltm = localtime(&now);







class post{

private:
    int Post_number;
    string title;
    string creator;
    tm creationDate;
    string text;
public:
    //post constructor
    post(){

        Post_number=id++;
        int index = rand() % 6;
        creator=names[index];
        index = rand() % 6;
        text=postArchive[index];
        index= rand() %3;
        title=titles[index];

        creationDate.tm_mday=ltm->tm_mday;
        creationDate.tm_mon=1+ltm->tm_mon;
        creationDate.tm_year=1900+ltm->tm_year;

        cout<< "Post with number: " << Post_number << " title: " << title << " creator: " <<creator;
        cout<< " date: " << creationDate.tm_mday << "/"<<creationDate.tm_mon<<"/"<<creationDate.tm_year <<" and text: " << text << " has been created" <<endl;
    }

    int getId(){
        return Post_number;
    }

    string getCreator(){
        return creator;
    }

    string getText(){
        return text;
    }

    void printPost(){
        cout<< "Post : " << Post_number << " title: " << title << " creator: " <<creator;
        cout<< " date: " << creationDate.tm_mday << "/"<<creationDate.tm_mon<<"/"<<creationDate.tm_year <<" and text: " << text <<endl;
    }


    ~post(){
        cout<<"Post number:"<<Post_number<<" is about to be destroyed"<<endl;
    }

};


class thread{

private:
    string subject;
    string creator;
    tm creationDate;
    post** posts;
    int n=rand() % 10 +2;

public:

    //default constructor
    thread(){
        int index= rand() % 4;
        subject=subjects[index];
        index= rand() % 6;
        creator= names[index];

        creationDate.tm_mday=ltm->tm_mday;
        creationDate.tm_mon=1+ltm->tm_mon;
        creationDate.tm_year=1900+ltm->tm_year;

        posts= new post*[n];

        for (int i = 0; i < n; i++) {

            posts[i]=new post();
        }
        cout<<"Thread with subject: " <<subject<< " has just been created!" <<endl;
    }

    //constructor with certain subject as input
    thread(string subjectIn){

        subject=subjectIn;
        int index= rand() % 6;
        creator= names[index];

        creationDate.tm_mday=ltm->tm_mday;
        creationDate.tm_mon=1+ltm->tm_mon;
        creationDate.tm_year=1900+ltm->tm_year;

        posts= new post*[n];

        for (int i = 0; i < n; i++) {

            posts[i]=new post();
        }
        cout<<"Thread with subject: " <<subject<< " has just been created!" <<endl;
    }

    string getSubject(){
        return subject;
    }

    int getN(){
        return n;
    }

    void printThread(){
        cout<<"Thread subject is "<<subject<<" creator is "<<creator;
        cout<< " creation date: " << creationDate.tm_mday << "/"<<creationDate.tm_mon<<"/"<<creationDate.tm_year<<endl;
        cout<<" and posts:"<<endl;
        for ( int i = 0; i < n; i++)
           posts[i]->printPost();
    }

    void printRandomPosts(){
        for (int i = 0; i < rand () %n; i++) {
            posts[i]->printPost();
        }
    }

    int findPostById(int id){
        for (int i = 0; i < n; i++) {
            if (id==posts[i]->getId()){
                posts[i]->printPost();
                return 1;
            }
        }
        return 0;
    }

	string getPostCreator(int i){
		return posts[i]->getCreator();
	}

    post* getPost(int i){
        return posts[i];
    }


    ~thread(){
        for(int i =0 ; i< n ; i++){
            delete  posts[i];
        }
        delete[]  posts;
        cout<<"Thread with subject: " <<subject<< " is about to be destroyed" <<endl;

    }

};

struct listNode
  {
    post* data = NULL;
    listNode *next = NULL;

    ~listNode(){
        delete data;
        }
  };

class list
  {
  private:
    listNode *head, *tail;
  public:
    list()
    {
      head=NULL;
      tail=NULL;
    }

    void createnode(post* value)
    	listNode *temp=new listNode;
        {
        post* temp_post=new post(*value);
    	temp->data=temp_post;
    	temp->next=NULL;
    	if(head==NULL)
    	{
          head=temp;
          tail=temp;
    	}
    	else
    	{
          tail->next=temp;
          tail=temp;

    	}
	}

    void display()
    {
        listNode *temp=head;
        while(temp!=NULL)
        {
           temp->data->printPost();
    	   temp=temp->next;
        }
    }

   listNode* getHead(){
       return head;
   }

   listNode* getTail(){
       return tail;
   }


   void copyLists(listNode* headIn){
       while (headIn!=NULL){
           post* temp_post=new post(*headIn->data);
           temp_post->printPost();
           listNode* temp =new listNode;
           temp->data=temp_post;
           temp->next=NULL;
           tail->next=temp;
           tail=temp;
           headIn=headIn->next;
       }

   }


    ~list(){
        listNode* temp=head;
        while (temp!=NULL){
            head=temp->next;
            delete temp;
            temp=head;
        }
    }
  };

struct treeNode{
	string creator;
	list myList;
	treeNode *left = NULL;;
	treeNode *right = NULL;
};

class btree
    {
    private:
        treeNode* root=NULL;
    public:

        btree(){}
        btree(thread* threadIn){
        root=new treeNode;
        treeNode* temp= new treeNode;
        root->creator=threadIn->getPostCreator(0);
        root->myList.createnode(threadIn->getPost(0));
        int n=threadIn->getN();
		treeNode* tempRoot=root;
        for (int i=1; i<n ; i++){
			temp->creator=threadIn->getPostCreator(i);
            root=tempRoot;

            while (root!=NULL){
                if (temp->creator > root->creator){
                    if (root->right==NULL){
                        root->right= new treeNode;
                        root->right->creator=threadIn->getPostCreator(i);
                        root->right->myList.createnode(threadIn->getPost(i));
                        break;
                    }
                    else{
                        root=root->right;}
                }
                else if (temp->creator < root->creator){
                    if (root->left==NULL){
                        root->left= new treeNode;
                        root->left->creator=threadIn->getPostCreator(i);
                        root->left->myList.createnode(threadIn->getPost(i));
                        break;
                    }
                    else{
                        root=root->left;
                    }
                }
                else if (temp->creator == root->creator){
                        root->myList.createnode(threadIn->getPost(i));
                        break;
                }
            }
		}
        root=tempRoot;
        delete temp;
        }
        treeNode* getRoot(){
        return root;
        }

        void addPost(post* Post){
            treeNode* temp=root;
            while (temp!=NULL){
                if (Post->getCreator() > temp->creator){
                    if (temp->right==NULL){
                        temp->right= new treeNode;
                        temp->right->creator=Post->getCreator();
                        temp->right->myList.createnode(Post);
                        break;
                    }
                    else{
                        temp=temp->right;}
                }
                else if (Post->getCreator() < temp->creator){
                    if (temp->left==NULL){
                        temp->left= new treeNode;
                        temp->left->creator=Post->getCreator();
                        temp->left->myList.createnode(Post);
                        break;
                    }
                    else{
                        temp=temp->left;
                    }
                }
                else if (Post->getCreator() == temp->creator){
                        temp->myList.createnode(Post);
                        break;
                }
            }
        }

        //adding a tree to another tree
        void enhanceTree(treeNode* treeIn){
            if (treeIn == NULL){

                return;}

            /* first recur on left child */
            enhanceTree(treeIn->left);

            treeNode* temp=root;
            /* add node to the tree */
            while (temp!=NULL){
                if (treeIn->creator > temp->creator){
                    if (temp->right==NULL){
                        temp->right= new treeNode;
                        temp->right->creator=treeIn->creator;
                        temp->right->myList.createnode((treeIn->myList.getHead())->data);
                        if (treeIn->myList.getHead()->next !=NULL){
                        temp->right->myList.copyLists(treeIn->myList.getHead()->next);
                        }
                        break;

                    }
                    else{
                        temp=temp->right;
                    }
                }
                else if (treeIn->creator < temp->creator){
                    if (temp->left==NULL){
                        temp->left= new treeNode;
                        temp->left->creator=treeIn->creator;
                        temp->left->myList.createnode((treeIn->myList.getHead())->data);
                        if (treeIn->myList.getHead()->next !=NULL){
                        temp->left->myList.copyLists(treeIn->myList.getHead()->next);
                        }
                        break;

                    }
                    else{
                        temp=temp->left;
                    }
                }
                else if (treeIn->creator == temp->creator){
                        temp->myList.copyLists(treeIn->myList.getHead());
                        break;
                }
            }

            /* now recur on right child */
            enhanceTree(treeIn->right);

        }

        void printBTree(){
            printInOrder(root);
            }

        //printing current tree
        void printInOrder(treeNode* node){

            if (node == NULL){
                return;}

            /* first recur on left child */
            printInOrder(node->left);

            /* then print the data of node */
            cout<<node->creator << " ";
            node->myList.display();

            /* now recur on right child */
            printInOrder(node->right);
        }

        void destroyRecursive(treeNode* node)
        {
            if (node == NULL){
                return;}

                destroyRecursive(node->left);
                destroyRecursive(node->right);
                delete node;
        }

    ~btree(){
        destroyRecursive(root);
    }
};



class forum{

private:
    string title;
    thread** threads;
    int n=rand() %10 +2; //creating at least 2 threads to avoid errors
public:
    //default constructor
    forum(){
        threads=new thread*[n];
        for (int i = 0; i < n; i++) {
            threads[i] = new thread;
        }
        cout<<"Forum with title: "<<title<<" has just been created!"<<endl;
    }

    //constructor with specific title
    forum(string titleIn){
        title=titleIn;
        threads=new thread*[n];
        int i=0;
        //using Rules and useful info as first thread when input is OOP
        if (titleIn=="OOP" && n>=1) {
            threads[0]=new thread("Rules and useful info");
            i=1;
        }
        for ( ; i < n; i++) {
            threads[i] = new thread;
        }
        cout<<"Forum with title: "<<title<<" has just been created!"<<endl;
    }

	thread* getThread(int i){
		return threads[i];
	}

    void printForum(){
        cout<<"Forum with title: "<<title<< " has threads with titles: "<<endl;
        for ( int i = 0; i < n; i++)
           cout<<threads[i]->getSubject()<<" ";
        cout<<endl;
    }

    //finding and printing certain Thread
    int printThread(string threadIn){

        for (int i = 0; i < n; i++) {
            if (threadIn==threads[i]->getSubject()){
                threads[i]->printThread();
                return 1;
            }
        }
        return 0;
    }

    void printRandomPosts(){
        cout<<"Printing random posts: "<<endl;
        for (int i = 0; i < rand() % n ; i++) {
            threads[i]->printRandomPosts();
        }
        cout<<endl;
    }

    int findPostById(int id){
        for (int i = 0; i < n; i++) {
            if (threads[i]->findPostById(id)){
                cout<<"Post found and it's above^ "<<endl;
                return 1;
            }
        }
        cout<<"Post not found."<<endl;
        return 0;
    }

	void print_sorted(){

        btree** trees;
        trees= new btree*[n];

        for (int i = 0; i < n; i++) {
            trees[i]=new btree(threads[i]);
        }
        for (int i = 1; i < n; i++) {
            trees[0]->enhanceTree(trees[i]->getRoot());

        }
        trees[0]->printBTree();
        cout<<endl;

        for(int i =0 ; i< n ; i++){
            delete  trees[i];
        }
        delete[]  trees;
	}

    ~forum(){
            for(int i =0 ; i< n ; i++){
                delete  threads[i];
            }
            delete[]  threads;
            cout<<"Forum with title "<<title<<" is about to be destroyed"<<endl;
    }
};


int main(){

    srand (time(0));
    forum forum1("OOP");
    forum1.print_sorted();
    return 0;
}
