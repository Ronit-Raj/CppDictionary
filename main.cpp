#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>
#include <curl/curl.h>
using namespace std;
using namespace Json;
const string API_URl= "https://api.dictionaryapi.dev/api/v2/entries/en/";

void parseJSON(string resp);
void apiCall(string url);
string response;


int main(){
    curl_global_init(CURL_GLOBAL_DEFAULT);
    while(true){
        string word;
        cout<<"Enter a Word or q to quit:";
        cin>>word;
        if(word=="q")
            break;
        string finalURL=API_URl+word;
        response="";
        apiCall(finalURL);
        parseJSON(response);
    }
    curl_global_cleanup();
}
void parseJSON(string resp){
    Value root;
    CharReaderBuilder builder;
    CharReader* reader=builder.newCharReader();
    string err;
    bool result=reader->parse(resp.c_str(),resp.c_str()+resp.size(),&root,&err);
    if(!result){
        cout<<"JSON parsing failed:\n"<<err<<endl;
        return;
    }
    Value meanings=root[0]["meanings"];
    for(int i=0;i<meanings.size();i++){
        Value meaning=meanings[i];
        cout<<meaning["partOfSpeech"].asString()<<endl;
        Value definitions=meaning["definitions"];
        for(int j=0;j<definitions.size();j++){
            cout<<" "<<j+1<<".";
            cout<<definitions[j]["definition"].asString()<<endl;
        }
    }
}
size_t handleChunk(void* contents,size_t size,size_t nmemb,void* userp){
    response.append((char*)contents);
    return size*nmemb;
}
void apiCall(string url){
    CURL* curl=curl_easy_init();
    if(!curl){
        cout<<"Failed to intialize CURL\n";
        return;
    }
    curl_easy_setopt(curl,CURLOPT_URL,url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handleChunk);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    if (res != CURLE_OK) {
        cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        return ;
    }
}