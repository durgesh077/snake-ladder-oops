#include "./controller/index.cpp"
#include "time.h"
int main(){
    srand(time(0));
    int option_no =0;
    std::vector<std::string>options{
        "1.Start a New Game",
        "2.Add a player" , 
        "3.Roll the dice" ,
        "4.Add snake" , 
        "5.Add ladder",
        "6.Clear Board Layout"
    };
    do{
        for(std::string opt: options)
            std::cout<<opt<<std::endl;
        PlayerController playerController = PlayerController::getInstance();
        std::cout<<"Turn of "<<playerController.getTurn() <<"/"<<playerController.getNoOfPlayers()<<"\n"; 
        option_no = IO::readInt("Enter option No............");

        switch (option_no)
        {
            case 1:{
                playerController.resetGame();
                break;
            }

            case 2: {
                std::string name = IO::readLine("Enter the name of player.............");
                playerController.addPlayer(name);
                break;
            }

            case 3: {
                int winner = playerController.rollDice();
                if(winner >=0){
                    std::cout<<playerController.getPlayer(winner).getName()<<" won the match"<<std::endl;
                    playerController.resetGame();
                }
                break;
            }
            
            case 4 : {
                int head= IO::readInt("Enter head position................");
                int tail = IO::readInt("Enter tail position................");
                Snake snake(head , tail);
                BoardController boardController  = BoardController::getInstance();
                boardController.add(snake);
                break;
            }

            case 5 : {
                int bottom= IO::readInt("Enter bottom position................");
                int top = IO::readInt("Enter top position................");
                Ladder Ladder(bottom , top);
                BoardController boardController  = BoardController::getInstance();
                boardController.add(Ladder);
                break;
            }

            case 6: {
                BoardController boardController  = BoardController::getInstance();
                boardController.resetBoard();
                break;
            }

            default:{
                std::cout<<"Please enter invalid options"<<std::endl;
            }
                
        }
    } while(option_no!=-1); 
}