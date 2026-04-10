#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Music Class
class Music {
private:
    string title;
    string artist;
    string album;
    int year;
public:
    //생성자
    Music(string title, string artist, string album, int year) {
        this->title = title; //<-매개변수 title        //this->title : 내 객체를 의미함 (music1, music2 등등 )
        this->artist = artist;             //다른 헤더파일에 했던 생성자로 해도됨. 그냥 개인차이
        this->album = album;
        this->year = year;
    }

    //Getters
    string getTitle() { return title; }    //내 객체의 title
    string getArtist() { return artist; }
    string getAlbum() { return album; }
    int getYear() { return year; }
};

//Music Streaming Service Class
class MusicStreamingService {
private:
    string serviceName;
    vector<Music> musicList;
public:
    MusicStreamingService(string serviceName) {
        this->serviceName = serviceName;
    }

    //Music 객체를 service에 추가
    void addMusic(string title, string artist, string album, int year) {
        Music newMusic(title, artist, album, year);
        musicList.push_back(newMusic);
        cout << title << " by " << artist << " added to " << serviceName << endl;
    }

    //Title로 검색하기
    Music* searchByTitle(string title) {           //*: 포인터
        for (int i = 0; i < musicList.size(); i++) {
            if (musicList[i].getTitle() == title) {
                return &musicList[i];             //주소값 return이기 때문에 Music에 포인터 붙여줌
            }
        }
        return NULL;
    }
};