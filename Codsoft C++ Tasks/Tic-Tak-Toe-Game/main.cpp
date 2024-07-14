# include<iostream>
# include<vector>
using namespace std;

class TicTakToe{
    private:
        vector<vector<char>>board;
        char currPlayer;

    
    void displayboardinitial(){
        cout << "Current board state:\n";
        for (int i = 0; i < 3; ++i) { 
            for (int j = 0; j < 3; ++j) {
                cout << " ";
                if (j < 2) cout << " | ";
            }
            cout << endl;
            if (i < 2) cout << "--+---+--\n";
        }
    }

    void displayboard(){
        cout << "Current board state:\n";
        for (int i = 0; i < 3; ++i) { 
            for (int j = 0; j < 3; ++j) {
                cout << board[i][j];
                if (j < 2) cout << " | ";
            }
            cout << endl;
            if (i < 2) cout << "--+---+--\n";
        }
    }

    void player_Turn(){
        int row,col;
        while(true){
            cout << "Player " << currPlayer << ", enter your move (row and column): ";
            cin >> row >> col;

            if(row>=1 && row<=3 && col>=1 && col<=3 && board[row-1][col-1]==' '){
                board[row-1][col-1] =currPlayer;
                break;
            }
            else{
                cout << "Invalid move. Please try again.\n";
            }

        }
    }

    bool chkWin(){
        for(int i=0; i<3;i++){
            if(board[i][0]==currPlayer && board[i][1]==currPlayer && board[i][2]==currPlayer){
                return true;
            }
            if(board[0][i]==currPlayer && board[1][i]==currPlayer && board[2][i]==currPlayer){
                return true;
            }

            if(board[0][0]==currPlayer && board[1][1]==currPlayer && board[2][1]==currPlayer){
                return true;
            }
            if(board[0][2]==currPlayer && board[1][1]==currPlayer && board[2][0]==currPlayer){
                return true;
            }
            return false;
        }
    }

    bool chkdraw(){
        for(int i=0; i<3;i++){
            for(int j=0; j<3;j++){
                if(board[i][j]==' '){
                    return false;
                }
            }
        }
        return true;
    }

    void playerswitch(){
        currPlayer = (currPlayer == 'X')? 'O': 'X';
    }

    void reset(){
        board= vector<vector<char>>(3,vector<char>(3,' '));
        currPlayer = 'X';
    }

    public:
        TicTakToe(){
        board=vector<vector<char>>(3,vector<char>(3,' '));
        currPlayer='X';
        }

        void playgame(){
            displayboardinitial();
            bool won = false;
            bool draw = false;

            while(true){
                player_Turn();
                displayboard();
                won=chkWin();
                draw=chkdraw();

                if(won){
                    displayboard();
                    cout<<"Game Over!!"<<endl;
                    cout<<"Player "<<currPlayer<<" wins!"<<endl;
                    break;
                }

                if(draw){
                    displayboard();
                    cout<<"Game Draw!"<<endl;
                    break;
                }

                playerswitch();

            }
        }
};

int main(){
    TicTakToe game;
    game.playgame();
    
    return 0;
}