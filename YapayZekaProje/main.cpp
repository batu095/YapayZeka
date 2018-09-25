#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;
int main(int argc, const char * argv[]) {
    float pSpam=1, pNot=1,  pTotal=1;
    int spam=0, notspam=0;
    vector <float> hesap2;
    vector <float> hesap, hesapyer;
    string testword;
    bool flag=false;
    string dummy, dummy2, textword;
    char dummy3;
    float N=0, F=0,total=0;
    float pN, pF;
    int i,counter=0, j;
    vector<string> wordsN, wordsF;
    ifstream hotelRM ("/Users/erolpazarbasi/Desktop/Ders/Projeler/Spam_Detector_Final/HotelMeta2.txt", ios::in);
    ifstream hotelR ("/Users/erolpazarbasi/Desktop/Ders/Projeler/Spam_Detector_Final/Hotel_Train.txt", ios::in);
    ifstream hotelRM2 ("/Users/erolpazarbasi/Desktop/Ders/Projeler/Spam_Detector_Final/HotelMeta2.txt", ios::in);
    ifstream hotelR2("/Users/erolpazarbasi/Desktop/Ders/Projeler/Spam_Detector_Final/Hotel_Train.txt", ios::in);
    ifstream test("/Users/erolpazarbasi/Desktop/Ders/Projeler/Spam_Detector_Final/Hotel_Test.txt", ios::in);
    ifstream test2("/Users/erolpazarbasi/Desktop/Ders/Projeler/Spam_Detector_Final/Hotel_Test.txt", ios::in);
    while(hotelRM>>dummy){
        if(dummy[0]=='N')
            N++;
        else
            F++;
        total++;
    }

    pF = F/total;
    pN = N/total;
    cout<<"pF: "<<pF<<" "<<"pN: "<<pN<<endl;

    while(getline(hotelR2, dummy2)){
        hotelRM2 >> dummy3;
        istringstream iss(dummy2);
        string word;
        counter=-1;
        if(dummy3=='N'){
            while(iss >> word) {
                counter++;
                flag=false;
                if(word[word.size()-1]==','){
                    word.erase(std::remove(word.begin(), word.end(), ','), word.end());
                }
                else if(word[word.size()-1]=='.'){
                    word.erase(std::remove(word.begin(), word.end(), '.'), word.end());
                }
                else if(word[word.size()-1]=='!'){
                    word.erase(std::remove(word.begin(), word.end(), '!'), word.end());
                }
                else if(word[word.size()-1]=='?'){
                    word.erase(std::remove(word.begin(), word.end(), '?'), word.end());
                }


                for(i=0;i<counter;i++){
                    if(wordsN[wordsN.size()-i-1]==word)
                        flag=true;
                }
                if(flag==false)
                    wordsN.push_back(word);
            }
        }
        else {
            while(iss >> word) {
                counter++;
                flag=false;
                if(word[word.size()-1]==','){
                    word.erase(std::remove(word.begin(), word.end(), ','), word.end());
                }
                for(i=0;i<counter;i++){
                    if(wordsF[wordsF.size()-i-1]==word)
                        flag=true;
                }
                if(flag==false)
                    wordsF.push_back(word);
            }
        }
    }

    int m=0;





    while(getline(test, textword)){
        m++;
        cout<<m<<endl;
        istringstream iss1(textword);
        istringstream iss2(textword);
        hesap2.clear();
        hesap.clear();
        hesapyer.clear();
        pNot=1;
        pSpam=1;
        pTotal=0;

        while(iss1 >> testword){
            counter=0;
            for(i=0;i<wordsF.size();i++){
                if(!wordsF[i].compare(testword)){
                    counter++;
                    hesapyer.push_back(i);
                }
            }
            hesap.push_back(counter);
        }


        int k;
        bool flag2=false;
        counter=0;
        for(i=0;i<wordsF.size();i++){
            counter=0;
            flag2=false;
            for(k=0;k<hesapyer.size();k++){
                if (hesapyer[k]==i) {
                    flag2=true;
                    break;
                }
            }
            if(flag2==true)
                continue;
            for(j=i;j<wordsF.size();j++){
                if(!wordsF[i].compare(wordsF[j])){
                    counter++;
                }
            }
            hesap2.push_back(counter);
        }




        for(i=0;i<hesap.size();i++){
            if(hesap[i]==0)
                continue;
            pSpam=pSpam*(hesap[i]/F);
        }

        for(i=0;i<hesap2.size();i++){
            if(hesap2[i]==0)
                continue;
            pSpam=pSpam*(1-(hesap2[i]/F));
        }



        hesap2.clear();
        hesap.clear();
        hesapyer.clear();




        while(iss2 >> testword){
            counter=0;
            for(i=0;i<wordsN.size();i++){
                if(!wordsN[i].compare(testword)){
                    counter++;
                    hesapyer.push_back(i);
                }
            }
            hesap.push_back(counter);
        }

        k=0;
        flag=false;
        counter=0;
        for(i=0;i<wordsN.size();i++){
            counter=0;
            flag2=false;
            for(k=0;k<hesapyer.size();k++){
                if (hesapyer[k]==i) {
                    flag2=true;
                    break;
                }
            }
            if(flag2==true)
                continue;
            for(j=i;j<wordsN.size();j++){
                if(!wordsN[i].compare(wordsN[j])){
                    counter++;
                }
            }
            hesap2.push_back(counter);
        }


        for(i=0;i<hesap.size();i++){
            if(hesap[i]<15)
                continue;
            pNot=pNot*(hesap[i]/N);
        }

        for(i=0;i<hesap2.size();i++){
            if(hesap2[i]<15)
                continue;
            pNot=pNot*(1-(hesap2[i]/N));
        }

        pTotal=(pSpam*pF)/(((pSpam*pF))+(pNot*pN));
        cout<<"pSpam: "<<pSpam<<endl<<"pNot: "<<pNot<<endl<<"pTotal: "<<pTotal<<endl;
        if(pTotal>=(0.5)){
            cout<<"spam"<<endl<<endl;
            spam++;
        }
        else{
            cout<<"not Spam"<<endl<<endl;
            notspam++;
        }
    }

    cout<<"spam sayýsý: "<<spam<<" "<<"dogal sayýsý: "<<notspam<<endl;
    cout<<endl<<endl;
    return 0;
}
