#include "../entity/index.cpp"
class BoardController  {
    std::map<int , Mover > moversMap;
    static BoardController* boardControl;
    Board board;
    BoardController(int dim): board(dim){
        if(!board.deserialize()){
            board= Board(dim);
        }

        for(Mover mv: board.getMovers())
            moversMap[mv.getFrom()] = mv;
    }

    public: 
        static BoardController getInstance(int dim=100){
            if(boardControl == nullptr)
                boardControl = new BoardController(dim);
            
            return *boardControl;
        }

        static int getTo(int from){
            if(boardControl-> moversMap.count(from)){
                Mover mover= boardControl-> moversMap[from];
                if(mover.getType() == TYPE_OF_MOVER::LADDER) 
                    std::cout<<"Oho! Got a ladder: "<<mover.getFrom()<<" -> "<<mover.getTo()<<std::endl;
                else 
                    std::cout<<"Oops!! Caught by snake: "<<mover.getFrom()<<" -> "<<mover.getTo()<<std::endl;
                
                return mover.getTo();
            }     

            return from;
        }

        static void add(Mover mover){
            boardControl->moversMap[mover.getFrom()] = mover;
            boardControl->board.addMover(mover);
        }

        static int getPosition(int from){
            if(boardControl->moversMap.count(from)==0)
                return from;
            
            return boardControl->moversMap[from].getTo();
        }

        static void resetBoard(int dim=100){
            boardControl-> moversMap.clear();
            boardControl-> board.reset();
        }

        static int getLastPosition(){
            return boardControl->board.getLastPosition();
        }

};

BoardController* BoardController::boardControl=nullptr;


class PlayerController{
    static PlayerController* playerControl;
    Dice dice;
    int turn ;
    int noOfPlayers;
    Players players;
    PlayerController(){

        if(!players.deserialize()){
            players=Players();
        }

        turn =0;
        noOfPlayers=players.getPlayers().size();
    }
    static void wait(int sec){
        for(int i=0;i<sec*1e8;i++);
    }
    public: 

    static PlayerController getInstance(){
        if(playerControl == nullptr)
                playerControl = new PlayerController();

        return *playerControl;
    }

    static void resetGame(){
        playerControl-> players.reset();
        playerControl-> turn=0;
        playerControl-> noOfPlayers=0;
    }

    static int rollDice(){ 
        if(playerControl-> noOfPlayers==0){
            std::cout<<"No players\n";
            return false;
        }
        
        std::cout<<"Rolling dice.......";
        for(int i=0;i<rand()%7;i++){
            int rd= rand()%6+1;
            std::cout<<rd;
            wait(1);
            std::cout<<"\b";
        } 
        int top= playerControl->dice.rollDice();
        BoardController boardController = BoardController::getInstance();
        int currentPosition= playerControl->players[playerControl-> turn].getPosition();
        int lastTurn = playerControl->turn;
        playerControl->turn++;
        playerControl->turn%= playerControl-> noOfPlayers;

        if(currentPosition + top <= boardController.getLastPosition()){
            int reached = boardController.getTo(currentPosition + top);
            playerControl->players[lastTurn].setPosition(reached);
            if(reached == boardController.getLastPosition())
                return lastTurn;
        }
        
        return -1;
    }
    

    static void addPlayer(std::string name){
        Player newPlayer(name) ;
        playerControl-> players.push_back(newPlayer);
        playerControl-> noOfPlayers++;
    }

    static int getPosition(int playerNo){
        return playerControl->players[playerNo].getPosition();
    }

    static Player getPlayer(int playerNo){
        return playerControl->players[playerNo];
    }

    static int getTurn(){
        return playerControl->turn;
    }

    static int getNoOfPlayers(){
        return playerControl->noOfPlayers;
    }

    static void showStatus(){
        BoardController boardController = BoardController::getInstance();
        std::cout<<"-------------------------------";
        std::cout<<"Turn of "<<playerControl ->getTurn()+1 <<"/"<<playerControl->getNoOfPlayers(); 
        std:: cout<<"-------------------------------\n";

        std::cout<<"____________________________________________________\n";
        for(Player p: playerControl->players.getPlayers()){
            std::cout<<"|               "<<p.getName()<< "                 |" <<p.getPosition()
                <<"              |"<< boardController.getLastPosition()<<std::endl;
        }
        std::cout<<"____________________________________________________\n";
    }
};

PlayerController* PlayerController::playerControl = nullptr;