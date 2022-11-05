#include<fstream>
class Serializable {
        const std::string filename;
        public:
        virtual bool serialize()=0;
        virtual bool deserialize()=0;
};

