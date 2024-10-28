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
    int noOfMeanings=meanings.size();
    for(int i=0;i<noOfMeanings;i++){
        cout<<i+1<<": ";
        cout<<meanings[i]["definitions"][i]["definition"]<<endl;
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