/*
    move(O) & identity(O) : xvlaue
    move(X) & identity(O) : lvalue
    move(O) & identity(X) : prvalue

    xvalue, lvalue : glvalue
    xvalue, prvalue : rvalue

    glvalue(xvalue, lvalue) :   identity를 가지는 표현식들.
                                식별성. 공간의 성질을 가지고 있는 값의 통칭.
                                데이터를 저장할 수 있는 메모리의 위치정보.
    rvalue(xvalue, prvalue) :   move 될 수 있는 표현식들.
                                이동성. 자료의 성질을 가지고 있는 값의 통칭.
                                저장될 데이터를 표현하는 리터럴.
    
    *이동성 : 어떤 공간의 데이터가 다른 공간으로 옮겨지는 행위.
              메모리 접근이 가능한(포인터 접근이 가능한) 값은 주소를 이동 할 수 있기 때문에 move 될 수 있다.

    *copy
      ex) 
          char *c1 = "test1"; //  address : 0x10
          char *c2;           //  address : nullptr
          ---copy---
          char *c1 = "test1"; //  address : 0x10
          char *c2 = "test1"; //  address : 0x20
    *move
      ex) 
          char *m1 = "test2"; //  address : 0x10
          char *m2;           //  address : nullptr
          ---move---
          char *m1;           //  address : nullptr
          char *m2 = "test2"; //  address : 0x10


    lvalue :    identity를 가지면서 move 될 수 없는 표현식들.
                어떤 자료의 이름. 또는 그 참조형의 통칭.
                
                - 모든 변수, 함수, 배열의 이름
                - 전위증감
                - 문자열 리터럴
                - lvalue 참조
                - lvalue 참조 캐스팅
                - 등등
            
                - 좌측에 올수 있음 / & operator 피연산자로 사용 가능 / 표현식이 끝나도 살아있음
 
    
    prvalue :   identity를 가지지 않으면서 move 될 수 있는 표현식들.
                데이터 값. 또는 그 참조형의 통칭.
                유일하게 identity를 가지지 않음.
                
                pure rvalue의 약자로 후의 증감연산자, 문자열 리터럴을 제외한 모든 리터럴 등이 prvalue에 속함.
                prvalue는 대입문의 오른쪽에 위치할 수 있으며 주소를 가지지 않음.

                - 문자열 제외한 모든 리터럴 값.
                - 후위증감
                - 등등

                - 우측에 올수있다 / incomplete type 일 수 없음. identity를 가지지 않고, 표현식이 사용되는 시점에 값이 존재해야하기 때문
                  / 주소가 없다

                ex)
                  int a = 1;
                  int b = 2;
                  a++;
                  a+b;
                  if(a > b) // a > b의 결과는 prvalue
                  {
                  }

    
    xvalue :    identity를 가지면서 move 될 수 있는 표현식들.
                데이터성 정보가 위치성 정보를 가진 형태.

                eXpiriing을 따와 xvalue라고 부름. 말 그대로 만료되어가는 값을 의미.
                그래서 표현식이 끝나고 해당 주소로 접근했을 때, 값이 존재할 수 도, 안 할 수 도 있음.
                (std::move와 같은 rvalue reference를 리턴하는 함수, rvalue reference를 타입캐스팅하는 표현식 등)

                이동은 될 수 있지만 메모리에 올라가는 순간 주소를 가지므로 prvalue는 될 수 없음. 컴파일러는 이러한
                prvalue의 임시데이터를 저장할 공긴이 필요. 이러한 임시 데이터 객체를 xvalue라고 함.

                데이터(prvalue)가 메모리에 올라가면 주소를 가짐.
                컴파일러는 이런 데이터를 임시객체에 넣은 뒤 구체화 하는데, 이러한 데이터성 임시객체를 xvalue라 함.
                (xvalue는 데이터 제공을 위함이며, 컴파일러만 접근 가능.)

                - rvalue reference
                - rvalue reference 캐스팅
                - 등등

                - 컴파일러만 사용하는 객체이므로 & operator 허용되지 않음.
                - 표현식이 끝났을 때, 사라짐.
                
*/