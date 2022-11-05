#include "../utils/headers.cpp"

class Board : public Serializable{
    int SIZE;
    std::vector<Mover> movers;
    const std::string filename ;
    public:
    Board(int dim): SIZE(dim), filename(BOARD_DATA_LOC) {
    }

    Board operator=(Board bd){
        SIZE=bd.SIZE;
        movers = bd.movers;
        serialize();
        return *this;
    }

    void addMover(Mover& mover){
        movers.push_back(mover);
        serialize();
    }

    std::vector<Mover>& getMovers(){
        return movers;
    }

    int getLastPosition(){
        return SIZE;
    }

    void reset(){
        SIZE=0;
        movers.clear();
        serialize();
    }
    bool serialize(){
        std::ofstream fout(filename, std::ios::binary);
        if(!fout)
            return false;
        fout.write((char*)this, sizeof (*this));

        return true;
    }
        
    bool deserialize(){
        return false;
        std::ifstream fin(filename, std::ios::binary);
        if(!fin)
            return false;
        fin.read((char*)this, sizeof (*this));
        return true;
    }
} ;


class Mover  {
    TYPE_OF_MOVER tom;
    int to , from;
    public: 

        Mover() {
        }

        int getTo(){
            return to;
        }

        int getFrom(){
            return from;
        }
        
        void setTo(int _to){
            to=_to;
        }

        void setFrom(int _from){
            from=_from;
        }

        void setTOM(TYPE_OF_MOVER _tom){
            tom=_tom;
        }

        TYPE_OF_MOVER getType(){
            return tom;
        }
};

class Snake : public Mover {
    public : 
        Snake( int _from ,int _to) {
            assert(_from > _to);
            setFrom(_from);
            setTo(_to);
            setTOM(TYPE_OF_MOVER::SNAKE);
        }
};

class Ladder : public Mover {
    public : 
        Ladder( int _from ,int _to){
            assert(_from < _to);
            setTOM(TYPE_OF_MOVER::LADDER);
        }
};
class Player {
    std::string name;
    int position;
    public:
        Player( std::string _name ) {
            name = _name ;
            position=1;
        }

        int getPosition(){
            return position;
        }

        void setPosition(int _position){
            position = _position;
        }
        std::string getName(){
            return name;
        }
} ;

class Players : public Serializable{
    std::vector<Player> players;
    const std::string filename;
    public:
        Players() : filename(PLAYERS_DATA_LOC) {
        }

        void operator=(Players _players){
            players.clear();
            for(Player p: _players.getPlayers())
                players.push_back(p);
            serialize();
        }   

    Player& operator[](int ind){
        return players[ind];
    }

    void push_back(Player p){
        players.push_back(p);
        serialize();
    }
    
    std::vector<Player>& getPlayers(){
       return players; 
    }

    void reset(){
        players.clear();
        serialize();
    }

    bool serialize(){
        std::ofstream fout(filename, std::ios::binary);
        if(!fout)
            return false;
        fout.write((char*)this, sizeof (*this));

        return true;
    }
        
    bool deserialize(){
        return false;
        std::ifstream fin(filename, std::ios::binary);
        if(!fin)
            return false;
           
        fin.read((char*)this, sizeof (*this));
        return true;
    }
};

class Dice {
    int faces;
    public:
        Dice(int _faces=6){
            faces=_faces;
        }

        int rollDice(){
            return (rand())%faces+1;
        }
} ;