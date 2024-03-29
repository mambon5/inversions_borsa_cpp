using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <thread>
//#include <string.h> // dont use string.h, use cstring instead
#include <cstring>
#include <dirent.h>
#include <sys/types.h>


#include <curl/curl.h>
// compile by the command: g++ yh_download_data.cpp -o prova -lcurl
// hint: Yahoo data won't show stocks if the list is greater than 9000. Trick: inspect this 
// list by pieces.
// this guy got a list of all US stock symbols, apparently: https://github.com/rreichel3/US-Stock-Symbols/tree/main
// it is worth checking it out



bool compareStrings(const std::string& str1, const std::string& str2) {
  return str1 < str2;
}

void sortarray(vector<std::string>& arrayDeStrings) {
    // Ejemplo de un array de strings
    // std::vector<std::string> arrayDeStrings = {"baababa","zzz", "abc", "aaaaa", "xyz", "def"};

    // Ordenar el array utilizando la función compareStrings como criterio de ordenamiento
    std::sort(arrayDeStrings.begin(), arrayDeStrings.end(), compareStrings);

    // Imprimir el array ordenado
    // std::cout << "Array ordenado:" << std::endl;
    // for (const auto& str : arrayDeStrings) {
    //     std::cout << str << " ";
    // }

}

class sort_indices
{
    // sorts the indices instead of the array!
    // how to use it:
    // int arr[5]={4,1,3,6,2}
    // string arr1[5]={"a1","b1","c1","d1","e1"};
    // int indices[5]={0,1,2,3,4};
    // arr[indices[0]]
    // std::sort(indices, indices+5, sort_indices(arr));
    //
   private:
     int* mparr;
   public:
     sort_indices(int* parr) : mparr(parr) {}
     bool operator()(int i, int j) const { return mparr[i]<mparr[j]; }
};

string DownloadWebBody(const string& url) {
    CURL *curl = curl_easy_init();
    string webContent;
    if(curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &webContent);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);     
        if (res != CURLE_OK) {
            cerr << "Failed to download web content: " << curl_easy_strerror(res) << endl;
            webContent.clear();
        }   
    }
    
    return webContent;
}

// Define the write callback function
size_t WriteCallback(void* ptr, size_t size, size_t nmemb, string* userdata) {
    size_t totalSize = size * nmemb;
    userdata->append(static_cast<char*>(ptr), totalSize);
    return totalSize;
}


// Function to download content from a URL using libcurl
std::string DownloadWebContent(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string webContent;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &webContent);
        // cout << "all curl_easy_setopt() done efore easy_perform()" << endl;
        res = curl_easy_perform(curl);
        // cout << "curl_easy_perform() done" << endl;
        if (res != CURLE_OK) {
            cerr << "Failed to download web content: " << curl_easy_strerror(res) << endl;
            webContent.clear();
        }

        curl_easy_cleanup(curl);
    }
    std::cout << "DownloadWebContent() succeded" << endl;
    return webContent;
}

std::string getTableStocks(const std::string& body) {
    size_t pos = 0;
    std::string table;
    pos = body.find("lookup-table", pos); // start of the table of interest
    size_t endPos = body.find("<span>Next", pos); // end of the table of interest
    if(int(pos) < body.length() && int(endPos) < body.length()){
            table = body.substr(pos, endPos - pos);
    } else{
        cout << "ERROR in getTableStocks(): no stock data found for this url" << endl;
        table = "";
    }
    return table;
}

std::string DirectWebContent(std::string& searchGroup, std::string B, std::string  C) {
    std::string baseUrl = "https://finance.yahoo.com/lookup/all?s=";
    std::string url = baseUrl + searchGroup + "&t=A&b="+B+"&c="+C;
    std::string webContent = DownloadWebContent(url);
    return webContent;
}

// String filtering for the tickers:
bool StringInVector(const std::string& ticker, const vector<std::string>& tickers) {
    // return true if ticker in string vector
    return find(begin(tickers), end(tickers), ticker) != end(tickers);
}

void LenghtOfVector(const vector<std::string>& tickers) {
    int n = 0;
    for(std::string str : tickers) {
        n++;
    }
    cout << endl;
    cout << "length of vector is: " << to_string(n) << endl;

}

int LenghtOfVectorInt(const vector<int>& tickers) {
    int n = 0;
    for(int str : tickers) {
        n++;
    }
    return n;

}

int LenghtOfVectorDoub(const vector<double>& tickers) {
    int n = 0;
    for(int str : tickers) {
        n++;
    }
    return n;

}


void OutputVector( const vector<std::string>& tickers) {
    int n = 0;
    for(std::string str : tickers) {
        cout << str << " - ";
        n++;
    }
    cout << endl;
    cout << "length of vector is: " << to_string(n) << endl;

}

void OutputVectorInt( const vector<int>& tickers) {
    for(int str : tickers) {
        cout << str << " - ";
    }
    cout << endl;
}

void OutputVectorDouble( const vector<double>& tickers) {
    for(double str : tickers) {
        cout << str << " - ";
    }
    cout << endl;
}

void Output2DVectorDouble( const vector<vector<double>>& matrix) {
    for (vector<double> vect : matrix) {
        for(double str : vect) {
            cout << str << " - ";
    }
        cout << endl;
    }
}

void Output2Dvector_custom1( const vector<vector<double>>& matrix, const vector<string>& strings) {
    for (vector<double> vect : matrix) {
        cout << vect[0] << " - " << vect[1] << " - " << strings[int(vect[2])] << endl;
    
    }
}

void Output2Dvector_firstFew( const vector<vector<double>>& matrix, const vector<string>& strings, int show=5) {
    for (vector<double> vect : matrix) {
        if(show==0) return;
        cout << vect[0] << " - " << vect[1] << " - " << strings[int(vect[2])] << endl;
        show --;
    }
}


void WriteToFileSimple( const std::string& output, const std::string& outputFile) {
    ofstream outFile;
    outFile.open(outputFile, ios_base::out); // append instead of overwrite
    if (!outFile.is_open()) {
        cerr << "Failed to open the output file: " << outputFile << endl;
        return;
    }
    cout << "writing output to ouput file: " << outputFile << endl;
    outFile << output << endl;
    outFile.close();
}

void WriteToFile(const vector<std::string>& tickers, const std::string& outputFile) {
    ofstream outFile;
    outFile.open(outputFile, ios_base::app); // append instead of overwrite
    if (!outFile.is_open()) {
        cerr << "Failed to open the output file: " << outputFile << endl;
        return;
    }
    cout << "writing output to ouput file: " << outputFile << endl;
    cout << "there are " << size(tickers) << " tickers:" << endl;
    // int len = sizeof(tickers)/sizeof(tickers[0]);
    // tickers = sort(tickers.begin(), tickers.end());
    // Write tickers to the output file
    for (const std::string& ticker : tickers) {
        cout << ticker << ", ";
        outFile << ticker << ",";
    }
    outFile.close();
    
}

vector <std::string> getLastSearchGroup() {
    std::string line;
    std::string block;
    std::string filename = "last_save_ticks.txt";
    std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int size = sizeof(characters);
    int first;
    int second;

    ifstream file(filename);
    if (file.is_open()) {
        getline(file, line);
        getline(file, block);
        file.close();
        first = characters.find(line[0]);
        second = characters.find(line[1]);
    } else {
        cout << endl << "ERROR! Could not open file " + filename;
        line = "";
        first = 0;
        second = 0;
    }
    cout << endl << "Opened file for last tickers used, got this: " + line << endl;
    
    std::string characters1 = characters.substr(first, size - first);
    std::string characters2 = characters.substr(second, size - second);
    if (block=="") block="0";
    vector <std::string> vect;
    vect.push_back(line);
    vect.push_back(characters1);
    vect.push_back(characters2);
    vect.push_back(block);
    
    return vect;
}

int getLastFileNumber() {
   DIR *dr;
   struct dirent *en;
   int files = 0;
   int lastn=1;
   dr = opendir("."); //open all directory
   if (dr) {
      while ((en = readdir(dr)) != NULL) {
        //  cout<<" \n"<<en->d_name; //print all directory name
        std::string filename = en->d_name;
        int n = filename.length();


        if( filename.find(".csv") < n && filename.find("_") <  n) {
            filename = filename.substr(0, n-4);
            std::string number = filename.substr(filename.find("_")+1, filename.length()-1);
            if(stoi(number) > lastn) lastn = stoi(number);
            files = files + 1;
        }
      }
      closedir(dr); //close all directory
      
   }
   return lastn;
}

vector<std::string> readCsv(const std::string& filename)
{
    vector<std::string>   result;
    std::string                line;
    ifstream file(filename);
    
    while(getline(file,line)) {

        stringstream          lineStream(line);
        std::string                cell;

        while(getline(lineStream,cell, ','))
        {
                result.push_back(cell);
     
        }
        // This checks for a trailing comma with no data after it.
        if (!lineStream && cell.empty())
        {
            // If there was a trailing comma then add nothing
        }
    }
    return result;
}

vector<std::string> readPartialCsv(const std::string& filename, const int& elems, bool printOutput=false) {
    // elems són els elements a llegir
    ifstream fitxer(filename);
    vector<std::string> elements;
    
    std::string tick;
    for (int i=0; i<elems;++i) { 
  
  
        // read an entire row and 
        // store it in a string variable 'line' 
        getline(fitxer, tick, ',');
        elements.push_back(tick);
  
       if(printOutput) cout << "ticker que hem llegit: " << tick << endl;
    }

    fitxer.close();
    return(elements);
}

vector<std::string> CsvFilterDuplicates(const std::string& filename)
{
    vector<std::string>   result;
    std::string                line;
    ifstream file(filename);
    int repeated = 0;
    
    while(getline(file,line)) {

        stringstream          lineStream(line);
        std::string                cell;

        while(getline(lineStream,cell, ','))
        {
            if(!StringInVector(cell, result)) {
                result.push_back(cell);
            }
            else {
                repeated++;
            }
        }
        // This checks for a trailing comma with no data after it.
        if (!lineStream && cell.empty())
        {
            // If there was a trailing comma then add nothing
        }
    }
    cout << to_string(repeated) << " repetitions deleted." << endl;
    return result;
}
