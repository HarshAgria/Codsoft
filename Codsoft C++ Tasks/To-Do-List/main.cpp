# include<iostream>
# include<vector>
# include<string>

using namespace std;

class Task{
    public:
    string description;
    bool isCompleted;

    Task(string desc): description(desc), isCompleted(false) {}

};

class ToDoList{
    private:
        vector<Task> tasks;

    public:
        void addTask(string description){
            tasks.push_back(Task(description));
            cout<<"Task added Successfully!!.\n";
        }

        void viewTasks(){
            if(tasks.empty()){
                cout<<"No tasks in the list. Add a task first!!.\n";
                return;
            }
            cout<<"\nTO-Do-List:\n";
            for(int i=0; i<tasks.size(); i++){
                cout<<i+1<<". "<<tasks[i].description<<" ["
                <<(tasks[i].isCompleted? "Completed" : "Pending")<<"]\n";
            }
        }

        void markTaskCompleted(int index){
            if(index<1 || index>tasks.size()){
                cout<<"Invalid task number.Check it again!!.\n";
                return;
            }

            tasks[index-1].isCompleted=true;
            cout<<"Task marked as completed!!.\n";
        }

        void removeTask(int index){
            if(index<1 || index>tasks.size()){
                cout<<"Invalid task number.Check it again!!.\n";
                return;
            }

            tasks.erase(tasks.begin()+index-1);
            cout<<"Task removed Successfully!!.\n";
        }

        void UI(){
            int choice;
            string description;
            int taskNumber;

            while(true){
                cout<<"\nTo-Do List Menu:\n";
                cout<<"1. Add Task\n";
                cout<<"2. View Tasks\n";
                cout<<"3. Mark Task as Completed\n";
                cout<<"4. Remove Task\n";
                cout<<"5. Exit\n";
                cout<<"Enter your choice: ";
                cin>>choice;

                switch(choice){
                    case 1:
                        cout<<"Enter task description: ";
                        cin.ignore();
                        getline(cin, description);
                        addTask(description);
                        break;
                    case 2:
                        viewTasks();
                        break;
                    case 3:
                        cout<<"Enter task number to mark as completed: ";
                        cin>>taskNumber;
                        markTaskCompleted(taskNumber);
                        break;
                    case 4:
                        cout<<"Enter task number to remove: ";
                        cin>>taskNumber;
                        removeTask(taskNumber);
                        break;
                    case 5:
                        return;
                    default:
                        cout<<"Invalid choice. Please try again.\n";
                }
            }
        }
};


int main(){
    ToDoList todoList;
    todoList.UI();
    
    return 0;
}