A dictionary made using the free dictionary API c++

# Compilation instructions
To compile this program you need to download and link libcurl and jsoncpp.  
## Windows(using WSL)&Linux
1.Install and set-up libcurl  
```
sudo apt-get install libcurl4-openssl-dev
```
```
curl-config --libs
```
2.Install Jsoncpp  
```
sudo apt-get install libjsoncpp-dev
```
3.Clone the repo and navigate to the directory containing main.cpp
4.Compile main.cpp
```
g++ main.cpp -o main -lcurl -ljsoncpp
```
5.Run
```
./main
```
