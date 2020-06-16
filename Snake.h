#ifndef __SNAKE_H__
#define __SNAKE_H__
#include <vector>
using namespace std;

class Snake
{
public:
    // 생성자, 소멸자
    Snake(SnakeMap &m); // SnakeMap 객체를 받아서 map 객체에 link
    ~Snake();

    void makeSnake();
    /*
     *  가장 처음에 맵에 랜덤한 위치에 정해진 크기의 snake를 그리는 함수
     */
    void move(int dir);
    /* 
     *  이동할 때마다 클래스 멤버 m 객체 안에 있는 map을 수정한다.
     *  dir의 방향으로 head를 움직이고 lenth에서 1을 뺀 값을 길이로 갖게끔
     *  body를 수정한다. 헤드가 dir 방향으로 나아갈 때 헤드가 있던 Point는
     *  다시 body에 들어가고 body에서 가장 오래된 Point는 삭제된다.
     */
    int findRoute(int key);
    /*  
     *  사용자의 key 입력을 저장하고
     *  나아갈 방향에 사물이 존재하면 거기에 해당하는    
     *  이벤트 변수를 true로 만든다.
     */
    void passGate(Point *gates);
    /*
     *  게이트의 위치를 받고 prevKey를 고려해 게이트를 통과해서 움직이는 head를
     *  그린다.
     */

    SnakeMap& m;
    int length;
    int prevKey;
    Point head;   //머리
    vector<Point> body;  //몸체 
};

#endif __SNAKE_H__
