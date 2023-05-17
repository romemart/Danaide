#include "jsontask.h"

std::string ReadJSONFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return "";
    }

    std::string jsonStr((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    return jsonStr;
}

void ParseJSONArray(const std::string& jsonString,std::vector<sensores>&sen) {
    rapidjson::Document document;
    document.Parse(jsonString.c_str());

    if (!document.IsArray()) {
        std::cerr << "Invalid JSON format. Expected array of objects." << std::endl;
        return;
    }

    for (rapidjson::Value::ConstValueIterator it = document.Begin(); it != document.End(); ++it) {
        if (!it->IsObject()) {
            std::cerr << "Invalid JSON format. Expected object." << std::endl;
            continue;
        }

        sensores s(
            (*it)["index"].GetInt(),
            (*it)["id"].GetString(),
            (*it)["isActive"].GetBool(),
            (*it)["zone"].GetString(),
            (*it)["value"].GetString()
        );
        sen.push_back(s);
    }
}

void ConvJSONtoOhtersFormat(const std::string& jsonString,
                            unsigned int ctrl,
                            std::string pathXML,
                            std::string pathCSV,...){
    
    format files(pathXML,pathCSV,ctrl);
    files.opening();

    rapidjson::Document document;
    document.Parse(jsonString.c_str());

    if (!document.IsArray()) {
        std::cerr << "Invalid JSON format. Expected array of objects." << std::endl;
        return;
    }

    for (rapidjson::Value::ConstValueIterator it = document.Begin(); it != document.End(); ++it) {
        if (!it->IsObject()) {
            std::cerr << "Invalid JSON format. Expected object." << std::endl;
            continue;
        }
        files.procesing(it);
    }   
    files.closing();
} 

void ConvJSONtoOhtersFormat(const std::string& jsonString,
                            unsigned int ctrl,
                            std::string pathXML,
                            std::string pathCSV){
    
    format files(pathXML,pathCSV,ctrl);
    files.opening();

    rapidjson::Document document;
    document.Parse(jsonString.c_str());

    if (!document.IsArray()) {
        std::cerr << "Invalid JSON format. Expected array of objects." << std::endl;
        return;
    }

    for (rapidjson::Value::ConstValueIterator it = document.Begin(); it != document.End(); ++it) {
        if (!it->IsObject()) {
            std::cerr << "Invalid JSON format. Expected object." << std::endl;
            continue;
        }
        files.procesing(it);
    }   
    files.closing();
} 

std::string getIdMayorValor(std::vector<sensores>sen){
        auto result = std::max_element(sen.begin(),sen.end(),
                [](sensores& s1,sensores & s2){
                    return s1.getValuef() < s2.getValuef();
                }
    );
    return (*result).getId();
}

float getValorMedio(std::vector<sensores>sen){
    float result = 0.0;
    for(auto i:sen)
        result += i.getValuef();
    return result/sen.size();
}

void CreaValorMedioZona(std::map< std::string, zonavalor > &zv, std::vector<sensores>sen){
    for(auto i:sen){
        zonavalor x(i.getValuef(),1);
        zv[i.getZona()] += x;
    }
}

void CreaCantSenActZona(std::map<std::string,int> &zc, std::vector<sensores>sen){
    for(auto i:sen){
        if(i.getIsActive())
            zc[i.getZona()] ++;
    }
}

void WriteJSONfile( const std::string& filename,
                    std::map<std::string,zonavalor> &zv,
                    std::map<std::string,int> &zc,
                    std::vector<sensores>sen
 ){
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Value val; 
    val.SetString(getIdMayorValor(sen).c_str(),document.GetAllocator());
    document.AddMember("IdMayorValor",val,document.GetAllocator());

    document.AddMember("valorMedio",getValorMedio(sen),document.GetAllocator());

    CreaValorMedioZona(zv,sen);
    for(auto i:zv){
        rapidjson::Value key;
        std::string name = i.first+"valorMedio";
        key.SetString(name.c_str(),document.GetAllocator());
        document.AddMember(key,i.second.getValue()/i.second.getCount(),document.GetAllocator());
    }

    CreaCantSenActZona(zc,sen);
    for(auto i:zc){
        rapidjson::Value key;
        std::string name = i.first+"cantSenAct";
        key.SetString(name.c_str(),document.GetAllocator());
        document.AddMember(key,i.second,document.GetAllocator());
    }

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    std::string jsonString = buffer.GetString();
    std::ofstream file(filename);

    file << jsonString;
    file.close();
}