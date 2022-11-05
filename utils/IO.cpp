class IO{
    public: 
        static std::string readLine(std::string out=""){
            std::cout<<out;
            std::cin.ignore();
            std::string line;
            std::getline( std::cin , line);
            return line;
        }

        static int readInt(std::string out=""){
            std::cout<<out;
            int num;
            std::cin>>num;
            return num;
        }
};