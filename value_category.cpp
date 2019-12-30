/*
    move(O) & identity(O) : xvlaue
    move(X) & identity(O) : lvalue
    move(O) & identity(X) : prvalue

    xvalue, lvalue : glvalue
    xvalue, prvalue : rvalue

    glvalue(xvalue, lvalue) :   식별성. 공간의 성질을 가지고 있는 값의 통칭.
                                데이터를 저장할 수 있는 메모리의 위치정보.
    rvalue(xvalue, prvalue) :   이동성. 자료의 성질을 가지고 있는 값의 통칭.
                                저장될 데이터를 표현하는 리터럴.
    
    *이동성 : 어떤 공간의 데이터가 다른 공간으로 옮겨지는 행위

    lvalue :    어떤 자료의 이름. 또는 그 참조형의 통칭.
                - 모든 변수, 함수, 배열의 이름
                - 전위증감
                - 문자열 리터럴
                - lvalue 참조
                - lvalue 참조 캐스팅
                - 등등
            
                - 좌측에 올수 있음 / & operator 피연산자로 사용 가능 / 표현식이 끝나도 살아있음
    
    prvalue :   데이터 값. 또는 그 참조형의 통칭.
                유일하게 identity를 가지지 않음.
                - 문자열 제외한 모든 리터럴 값.
                - 후위증감
                - 등등

                - 우측에 올수있다 / incomplete type 일 수 없음. identity를 가지지 않고, 표현식이 사용되는 시점에 값이 존재해야하기 때문
                  / 주소가 없다
    
    xvalue :    데이터성 정보가 위치성 정보를 가진 형태.
                표현식이 끝나고 해당 주소로 접근했을 때, 값이 존재할 수 도, 안 할 수 도 있음.
                (rvalue reference를 리턴하는 함수, rvalue reference를 타입캐스팅하는 표현식 등)
                데이터(prvalue)가 메모리에 올라가면 주소를 가짐.
                컴파일러는 이런 데이터를 임시객체에 넣은 뒤 구체화 하는데, 이러한 데이터성 임시객체를 xvalue라 함.
                (xvalue는 데이터 제공을 위함이며, 컴파일러만 접근 가능.)
                - rvalue reference
                - rvalue reference 캐스팅
                - 등등

                - & operator 허용 X / 표현식이 끝났을 때, 사라짐.
                
*/