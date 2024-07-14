# include<iostream>
# include<string>
# include<ctime>
# include<unordered_map>
# include<vector>

using namespace std;

class Book{
    public:
        Book() {}
        Book(string t, string a, string i, bool available = true){
        title = t;
        author = a;
        ISBN = i;
        isAvaliable = available;
        }

        string title;
        string author;
        string ISBN;
        bool isAvaliable;

    
};


class Borrower{
    public:
        Borrower(){}
        Borrower(string n,string bid){
            name=n;
            borrower_id=bid;
        }

        string name;
        string borrower_id;

        
};


class Transaction{
    public:
        string ISBN;
        string Borrower_id;
        time_t issuingdate;
        time_t returndate;
        bool isReturned;

        Transaction() : isReturned(false), issuingdate(time(NULL)) {}
        Transaction(string bid, string i){
            Borrower_id = bid;
            ISBN = i;
            isReturned = false;
            issuingdate = time(NULL);//current time in sec
        }

        void returnBook(){
            isReturned = true;
            returndate=time(NULL);
        }

        double fine(){
            if(isReturned==true){
                return 0;
            }
            double totalFine=0;
            const int noOfduedays=14;
            const double finePerday=20;//in Rs
            time_t duedate=issuingdate+noOfduedays*24*60*60;
            if(duedate < returndate){
                totalFine = finePerday*(returndate-duedate)/(24*60*60);
            }
            return totalFine;
        }
};


class Library_Mgmt_System{
    private:
        unordered_map<string, Book> books;
        unordered_map<string, Borrower> borrower;
        vector<Transaction> transactions;

    public:
        void addBook(string title, string author, string ISBN){
            books[ISBN]= Book(title, author,ISBN, true);
;        }

        void addBorrower(string name, string borrower_id){
            borrower[borrower_id]= Borrower(name,borrower_id);
        }

        void displayBookInfo(Book& book){
            cout<<"Title: "<<book.title<<", Author: "<<book.author<<", ISBN: "<<book.ISBN<<", Avaliable: "<<(book.isAvaliable?"Yes":"No")<<endl;
        }

        void srchBookByTitle(string title){
            for(auto i : books){
                if(i.second.title==title){
                    displayBookInfo(i.second);
                }
            }
        }

        void srchBookByAuthor(string author){
            for(auto i : books){
                if(i.second.author==author){
                    displayBookInfo(i.second);
                }
            }
        }

        void srchBookByISBN(string ISBN){
                if(books.find(ISBN)!=books.end()){
                    displayBookInfo(books[ISBN]);
                }
                else{
                    cout<<"Book not found. "<<endl;
                }
        }

        void chkOutBook(string Borrower_id,string ISBN){
            if(borrower.find(Borrower_id)==borrower.end()){
                cout<<"Borrower not found. "<<endl;
                return;
            }

            if(books.find(ISBN)==books.end()){
                cout<<"Book not found. "<<endl;
                return;
            }

            if(!books[ISBN].isAvaliable){
                cout<<"Book is currently unavaliable. "<<endl;
            }

            books[ISBN].isAvaliable=false;
            transactions.push_back(Transaction(Borrower_id,ISBN));
            cout<<"Book checked out successfully. "<<endl;
        }

        void returnBook(string Borrower_id, string ISBN){
            for(auto& i: transactions){
                if(Borrower_id==i.Borrower_id && ISBN==i.ISBN && !i.isReturned){
                    i.returnBook();
                    books[ISBN].isAvaliable=true;
                    cout<<"Book returned successfully. "<<endl;
                    cout<<"Fine: "<<i.fine()<<"Rs ."<<endl;
                    return;
                }
            }
            cout<<"Transaction not found. "<<endl;
        }

        void UI(){
            int choice;
            string title, author, ISBN, name, borrowerID;
            while (true) {
                cout << "\nLibrary System Menu:\n";
                cout << "1. Add Book\n";
                cout << "2. Add Borrower\n";
                cout << "3. Search Book by Title\n";
                cout << "4. Search Book by Author\n";
                cout << "5. Search Book by ISBN\n";
                cout << "6. Checkout Book\n";
                cout << "7. Return Book\n";
                cout << "8. Exit\n";
                cout << "Enter your choice: ";
                cin >> choice;
                switch(choice) {
                    case 1:
                    cout << "Enter title, author, ISBN: ";
                    cin >> title >> author >> ISBN;
                    addBook(title, author, ISBN);
                    break;
                case 2:
                    cout << "Enter name, BorrowerID: ";
                    cin >> name >> borrowerID;
                    addBorrower(name, borrowerID);
                    break;
                case 3:
                    cout << "Enter title: ";
                    cin >> title;
                    srchBookByTitle(title);
                    break;
                case 4:
                    cout << "Enter author: ";
                    cin >> author;
                    srchBookByAuthor(author);
                    break;
                case 5:
                    cout << "Enter ISBN: ";
                    cin >> ISBN;
                    srchBookByISBN(ISBN);
                    break;
                case 6:
                    cout << "Enter borrowerID, ISBN: ";
                    cin >> borrowerID >> ISBN;
                    chkOutBook(borrowerID, ISBN);
                    break;
                case 7:
                    cout << "Enter borrowerID, ISBN: ";
                    cin >> borrowerID >> ISBN;
                    returnBook(borrowerID, ISBN);
                    break;
                case 8:
                    return;
                default:
                    cout << "Invalid choice. Please try again.\n";
                }
        }
     }
};

int main(){
    Library_Mgmt_System library;
    library.UI();
    return 0;
}