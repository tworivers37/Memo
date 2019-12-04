#include<iostream>
#include<boost/multi_index_container.hpp>
#include<boost/multi_index/indexed_by.hpp>
#include<boost/multi_index/ordered_index.hpp>
#include<boost/multi_index/member.hpp>


//boost::multi_index_container
//하나의 데이터를 여러 키들로 관리하고자 할 때 사용.


struct person{
    int age;
    std::string name;
    std::string email;
};

//Tag용. 접근하기 위해서 index번호(0,1,2,...) 를 사용하나 가독성이 떨어지므로 태그를 붙임.
struct age{};
struct name{};
struct email{};

using PERSON = boost::multi_index_container<
                    person,
                    boost::multi_index::indexed_by<

                        boost::multi_index::ordered_unique<
                            boost::multi_index::tag<age>,
                            boost::multi_index::member<person, int, &person::age>
                        >,
                        boost::multi_index::ordered_unique<
                            boost::multi_index::tag<name>,
                            boost::multi_index::member<person, std::string, &person::name>
                        >,
                        boost::multi_index::ordered_non_unique<
                            boost::multi_index::tag<email>,
                            boost::multi_index::member<person, std::string, &person::email>
                        >
                    >
                >;

int main(){

    PERSON p;

    p.insert({20,"tester1","tester1@mail.com"});
    p.insert({20,"tester2","tester11@mail.com"});
    p.insert({20,"tester16","tester31@mail.com"});
    p.insert({55,"tester15","tester11@mail.com"});
    p.insert({21,"tester14","tester41@mail.com"});
    p.insert({22,"tester13","tester61@mail.com"});
    p.insert({24,"tester11","tester71@mail.com"});
    p.insert({25,"tester12","tester81@mail.com"});

/////////////////////////////////////////////////////////////////////////////////
    std::cout<<"1111111111111111111111111111111111111111111111111111111111111111111111\n";

    //ordered_unique 때문에 age가 20으로 중복되는 객체(age가 20인게 3개)가 하나만 가장 첫 번째꺼 하나만 존재.
    for(auto const& tmp : p)
        std::cout<<tmp.age<<"   "<<tmp.name<<"   "<<tmp.email<<"\n"; 
    
    std::cout<<std::endl;
/////////////////////////////////////////////////////////////////////////////////
    std::cout<<"2222222222222222222222222222222222222222222222222222222222222222222222\n";

    PERSON::index<name>::type& name_key = p.get<name>();

    for(auto itr = name_key.begin(); itr != name_key.end(); ++itr)
        std::cout<<itr->age<<"   "<<itr->name<<"   "<<itr->email<<"\n";

    std::cout<<std::endl;

    for(auto const& tmp : name_key)
        std::cout<<tmp.age<<"   "<<tmp.name<<"   "<<tmp.email<<"\n";

    std::cout<<std::endl;
/////////////////////////////////////////////////////////////////////////////////
    std::cout<<"3333333333333333333333333333333333333333333333333333333333333333333333\n";

    //0 : age
    //1 : name
    //2 : email
    PERSON::nth_index<1>::type& name_key2 = p.get<1>();
    std::cout<<name_key2.find("tester1")->age<<"\n";
    std::cout<<name_key2.find("tester1")->email<<"\n";

    std::cout<<std::endl;
////////////////////////////////////////////////////////////////////////////////
    std::cout<<"4444444444444444444444444444444444444444444444444444444444444444444444\n";    

    PERSON::index<email>::type& email_key = p.get<email>();
    std::cout<<email_key.find("tester41@mail.com")->age<<"\n";
    std::cout<<email_key.find("tester41@mail.com")->name<<"\n";

    //erase
    email_key.erase("tester41@mail.com");
    for(auto const& tmp : email_key)
        std::cout<<tmp.age<<"   "<<tmp.name<<"   "<<tmp.email<<"\n";

    std::cout<<std::endl;

    return 0;
}