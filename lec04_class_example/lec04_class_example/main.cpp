#include "Rectangle.h"
#include "Pet.h"
#include "Music.h"

using namespace std;   //std:: 생략

int main() {
    //Rectangle 1 객체 생성
    Rectangle rect1(3, 3);
    /*std::*/cout << "Rectangle 1:" << /*std::*/endl;  //iostream 헤더파일 include하면 쓸 수 있음
    //printf("Rectangle 1:\n"); 위에 코드랑 똑같음
    cout << "Area: " << rect1.getArea() << endl;
    //printf("Area: %lf", rect1.getArea());     //이렇게 하면 힘드니까 cout을 써줌
    cout << "Perimeter: " << rect1.GerPerimeter() << endl;
    cout << "isSquare?: " << boolalpha << rect1.isSquare() << endl;    //boolalpha: 1을 true 0을 false로 바꿔줌
    printf("==========================================\n");

    //Pet 클래스 테스트
    Pet myPet("Kong", 5, "Dog");
    cout << "My Pet's name is " << myPet.getName() << endl;
    //Puppy 클래스 테스트
    Puppy myPuppy("Lucky", 10, "Dog", "Puddle");
    cout << "My puppy's breed is " << myPuppy.getBreed() << endl;

    //Streaming Service 테스트
    MusicStreamingService myService("Spotify");
    //음악 Service에 추가
    myService.addMusic("SWIM", "BTS", "ARIRANG", 2026);
    myService.addMusic("RUDE", "Hearts2Hearts", "RUDE", 2026);
    myService.addMusic("BANG BANG", "IVE", "REVIVE", 2026);
    myService.addMusic("JUMP", "BlackPink", "JUMP", 2025);
    myService.addMusic("ShutDown", "BlackPink", "BornPink", 2022);

    //title로 search
    string music_title;
    cout << "Enter the Music Title: ";
    cin >> music_title;      //방향 잘 쓰기
    //scanf_s("%s", &music_title); 위에 문장과 똑같은 뜻
    Music* result = myService.searchByTitle(music_title);           //헤더함수처럼 포인터 써주기
    if (result != NULL) {
        cout << "Found: " << result->getTitle() << " by " << result->getArtist() << endl; //함수가 포인터면 this->이거로 써야함(.은 안됨)
    }
    else {
        cout << "Not Found" << endl;
    }
    //artist로 찾기는 다음시간

    return 0;
}