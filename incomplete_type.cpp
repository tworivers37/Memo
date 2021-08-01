/*

타입은 완전(complete) 할 수도 불완전(incomplete) 할 수 도 있음.

불완전한 타입은 다음 아래 중 하나임.
- 선언은 되었지만 아직 정의되지 않은 class, struct, enum(class test;)
- 크기 지정되지 않은 배열형(int a[])
- 요소의 형식이 불완전한 배열형(test a[10])
- void
- 사용할 타입이나 열거 값이 정의되지 않은 상태의 열거형
- 위 정의된 모든 타입에 const나 volatile이 적용된 타입

이 외의 타입은 완전함.

*/