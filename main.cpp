#include<iostream>
#include<iomanip>
#include<cstring>
using namespace std;

const int MAX=1000;
int n,k;//测试数据组数
int TIME,CLOCK;//时间
int LifeTotal;//每个司令部总的生命值
int city;
int arrowR;
int lionK;
int dragonlife,ninjalife,icemanlife,lionlife,wolflife;//初始生命值
int dragonATK,ninjaATK,icemanATK,lionATK,wolfATK;
char *weaponname[4]={"sword","bomb","arrow","no weapon"};

class Cweapon//武器类
{
    int number;//编号
    int weaponattack;//攻击值
    int arrowavailable;
    friend class Cdragon;
    friend class Cninja;
    friend class Ciceman;
    friend class Clion;
    friend class Cwolf;
public:
    Cweapon(int number=3):number(number)
    {
        if(number==2)
        {
            weaponattack=arrowR;
            arrowavailable=3;
        }
    }
    int getnumber(){return number;}
    Cweapon & operator=(Cweapon weapon)
    {
        number=weapon.number;
        weaponattack=weapon.weaponattack;
        arrowavailable=weapon.arrowavailable;
        return *this;
    }
};

class Cwarrior;
class Cheadquarter
{
public:
    int lifetotal;
    int warriortotal;
    int arrive;
    Cwarrior *warrior[MAX];
    string name;
    Cheadquarter(string n,int warriortotal=0,int arrive=0):name(n),warriortotal(warriortotal),arrive(arrive){}
    bool makeredwarrior();
    bool makebluewarrior();
    bool ifistaken();
};

class Cwarrior//武士类
{
protected:
    int number;//编号
    int life;//生命值
    int warriorattack;//攻击力
    Cheadquarter *quarter;
    int citynumber;
public:
    Cwarrior(int number,int life,int warriorattack,Cheadquarter *q):number(number),life(life),warriorattack(warriorattack),quarter(q)
    {
        if(q->name=="red") citynumber=0;
        else if(q->name=="blue") citynumber=city+1;
    }
    int getnumber(){return number;}
    int getcitynumber(){return citynumber;}
    int getlife(){return life;}
    int hurt(int reduce) {life-=reduce;return life;}
    void addlife(int add){life+=add;}
    void earnelement(int earn) {quarter->lifetotal+=earn;}
    virtual void addmorale(){}
    virtual void reducemorale(){}
    virtual void reduceloyalty(){}
    virtual void addelement(int element){}
    virtual void addelement1(int element){}
    virtual void runaway(){}
    virtual int getloyalty(){}
    virtual void goforward(){}
    virtual bool ifhasarrow(){}
    virtual bool ifhasbomb(){}
    virtual void shot(){}
    virtual bool ifdieofarrow(){}
    virtual bool tryattack(Cwarrior *enemy){}
    virtual bool attack(Cwarrior *enemy){}
    virtual bool tryfightback(Cwarrior *enemy){}
    virtual bool fightback(Cwarrior *enemy){}
    virtual void usebomb(){}
    virtual void dieofbomb(){}
    virtual void get(){}
    virtual void die(){}
    virtual void yell(){}
    virtual void report(){}
    virtual void getweapon(Cwarrior *enemy){}
    virtual Cweapon takeweaponaway(int a){}
};

class Cdragon:public Cwarrior
{
    Cweapon weapon;
    double morale;
public:
    Cdragon(int number,int life,int warriorattack,Cheadquarter *q,int weaponnumber,double morale):Cwarrior(number,life,warriorattack,q),weapon(weaponnumber),morale(morale)
    {
        if(weaponnumber==0)
        {
            weapon.weaponattack=warriorattack*0.2;
            if(weapon.weaponattack==0) weapon.number=3;
        }
        cout<<setw(3)<<setfill('0')<<TIME/60<<":";
        cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
        cout<<q->name<<" dragon "<<number<<" born"<<endl;
        cout<<"Its morale is "<<fixed<<setprecision(2)<<morale<<endl;
    }
    virtual void addmorale(){morale+=0.2;}
    virtual void reducemorale(){morale-=0.2;}
    virtual void goforward();
    virtual void addelement(int element);
    virtual void addelement1(int element);
    virtual bool ifhasarrow();
    virtual bool ifhasbomb();
    virtual void shot();
    virtual bool ifdieofarrow();
    virtual bool tryattack(Cwarrior *enemy);
    virtual bool attack(Cwarrior *enemy);
    virtual bool tryfightback(Cwarrior *enemy);
    virtual bool fightback(Cwarrior *enemy);
    virtual void usebomb();
    virtual void dieofbomb();
    virtual void get();
    virtual void die();
    virtual void yell();
    virtual void report();
    virtual Cweapon takeweaponaway(int a);
};
void Cdragon::goforward()
{
    if(quarter->name=="red") citynumber++;
    else if(quarter->name=="blue") citynumber--;
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    if(quarter->name=="red" && citynumber==city+1)
    {
        cout<<"red dragon "<<number<<" reached blue headquarter with "<<life<<" elements and force "<<warriorattack<<endl;
        quarter->arrive++;
    }
    else if(quarter->name=="blue" && citynumber==0)
    {
        cout<<"blue dragon "<<number<<" reached red headquarter with "<<life<<" elements and force "<<warriorattack<<endl;
        quarter->arrive++;
    }
    else
        cout<<quarter->name<<" dragon "<<number<<" marched to city "<<citynumber<<" with "<<life<<" elements and force "<<warriorattack<<endl;
}
void Cdragon::addelement(int element)
{
    quarter->lifetotal+=element;
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" dragon "<<number<<" earned "<<element<<" elements for his headquarter"<<endl;
}
void Cdragon::addelement1(int element)
{
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" dragon "<<number<<" earned "<<element<<" elements for his headquarter"<<endl;
}
bool Cdragon::ifhasarrow()
{
    if(weapon.getnumber()==2) return true;
    else return false;
}
void Cdragon::shot()
{
    weapon.arrowavailable--;
    if(weapon.arrowavailable==0) weapon.number=3;
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" dragon "<<number<<" shot";
}
bool Cdragon::ifdieofarrow()
{
    if(life<=0)
    {
        quarter->warrior[number]=NULL;
        cout<<" and killed "<<quarter->name<<" dragon "<<number;
        return true;
    }
    else return false;
}
bool Cdragon::ifhasbomb()
{
    if(weapon.getnumber()==1) return true;
    else return false;
}
bool Cdragon::tryattack(Cwarrior *enemy)
{
    if(weapon.number==0)
    {
        int tmp=enemy->getlife();
        tmp=tmp-(warriorattack+weapon.weaponattack);
        if(tmp<=0) return true;
        else return false;
    }
    else
    {
        int tmp=enemy->getlife();
        tmp=tmp-warriorattack;
        if(tmp<=0) return true;
        else return false;
    }
}
bool Cdragon::tryfightback(Cwarrior *enemy)
{
    if(weapon.number==0)
    {
        int tmp=enemy->getlife();
        tmp=tmp-(warriorattack/2+weapon.weaponattack);
        if(tmp<=0) return true;
        else return false;
    }
    else
    {
        int tmp=enemy->getlife();
        tmp=tmp-warriorattack/2;
        if(tmp<=0) return true;
        else return false;
    }
}
bool Cdragon::attack(Cwarrior *enemy)
{
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" dragon "<<number<<" attacked ";
    enemy->get();
    cout<<" in city "<<citynumber<<" with "<<life<<" elements and force "<<warriorattack<<endl;
    if(weapon.number==0)
    {
        int tmp=enemy->hurt(warriorattack+weapon.weaponattack);
        weapon.weaponattack=weapon.weaponattack*0.8;
        if(weapon.weaponattack==0) weapon.number=3;
        if(tmp<=0) return true;
        else return false;
    }
    else
    {
        int tmp=enemy->hurt(warriorattack);;
        if(tmp<=0) return true;
        else return false;
    }
}
void Cdragon::usebomb()
{
    quarter->warrior[number]=NULL;
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" dragon "<<number<<" used a bomb ";
    delete this;
}
void Cdragon::dieofbomb()
{
    quarter->warrior[number]=NULL;
    cout<<"and killed "<<quarter->name<<" dragon "<<number;
    delete this;
}
void Cdragon::get()
{
   cout<<quarter->name<<" dragon "<<number;
}
bool Cdragon::fightback(Cwarrior *enemy)
{
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" dragon "<<number<<" fought back against ";
    enemy->get();
    cout<<" in city "<<citynumber<<endl;
    if(weapon.number==0)
    {
        int tmp=enemy->hurt(warriorattack/2+weapon.weaponattack);
        weapon.weaponattack=weapon.weaponattack*0.8;
        if(weapon.weaponattack==0) weapon.number=3;
        if(tmp<=0) return true;
        else return false;
    }
    else
    {
        int tmp=enemy->hurt(warriorattack/2);
        if(tmp<=0) return true;
        else return false;
    }
}
void Cdragon::die()
{
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" dragon "<<number<<" was killed in city "<<citynumber<<endl;
    quarter->warrior[number]=NULL;
}
void Cdragon::yell()
{
    if(morale>0.8)
    {
        cout<<setw(3)<<setfill('0')<<TIME/60<<":";
        cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
        cout<<quarter->name<<" dragon "<<number<<" yelled in city "<<citynumber<<endl;
    }
}
void Cdragon::report()
{
    if(weapon.number==0 && weapon.weaponattack==0) weapon.number=3;
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" dragon "<<number<<" has "<<weaponname[weapon.number];
    if(weapon.number==0) cout<<"("<<weapon.weaponattack<<")";
    if(weapon.number==2) cout<<"("<<weapon.arrowavailable<<")";
    cout<<endl;
}
Cweapon Cdragon::takeweaponaway(int a)
{
    if(weapon.number==a)
        return weapon;
    else
    {
        Cweapon tmp;
        return tmp;
    }
}

class Cninja:public Cwarrior
{
    Cweapon weapon1,weapon2;
public:
    Cninja(int number,int life,int warriorattack,Cheadquarter *q,int weaponnumber1,int weaponnumber2):Cwarrior(number,life,warriorattack,q),weapon1(weaponnumber1),weapon2(weaponnumber2)
    {
        if(weaponnumber1==0)
        {
            weapon1.weaponattack=warriorattack*0.2;
            if(weapon1.weaponattack==0) weapon1.number=3;
        }
        if(weaponnumber2==0)
        {
            weapon2.weaponattack=warriorattack*0.2;
            if(weapon2.weaponattack==0) weapon2.number=3;
        }
        cout<<setw(3)<<setfill('0')<<TIME/60<<":";
        cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
        cout<<q->name<<" ninja "<<number<<" born"<<endl;
    }
    virtual void goforward();
    virtual void addelement(int element);
    virtual void addelement1(int element);
    virtual bool ifhasarrow();
    virtual bool ifhasbomb();
    virtual void shot();
    virtual bool ifdieofarrow();
    virtual bool tryattack(Cwarrior *enemy);
    virtual bool attack(Cwarrior *enemy);
    virtual bool tryfightback(Cwarrior *enemy);
    virtual bool fightback(Cwarrior *enemy);
    virtual void usebomb();
    virtual void dieofbomb();
    virtual void get();
    virtual void die();
    virtual void report();
    virtual Cweapon takeweaponaway(int a);
};
void Cninja::goforward()
{
    if(quarter->name=="red") citynumber++;
    else if(quarter->name=="blue") citynumber--;
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    if(quarter->name=="red" && citynumber==city+1)
    {
        cout<<"red ninja "<<number<<" reached blue headquarter with "<<life<<" elements and force "<<warriorattack<<endl;
        quarter->arrive++;
    }
    else if(quarter->name=="blue" && citynumber==0)
    {
        cout<<"blue ninja "<<number<<" reached red headquarter with "<<life<<" elements and force "<<warriorattack<<endl;
        quarter->arrive++;
    }
    else
        cout<<quarter->name<<" ninja "<<number<<" marched to city "<<citynumber<<" with "<<life<<" elements and force "<<warriorattack<<endl;
}
void Cninja::addelement(int element)
{
    quarter->lifetotal+=element;
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" ninja "<<number<<" earned "<<element<<" elements for his headquarter"<<endl;
}
void Cninja::addelement1(int element)
{
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" ninja "<<number<<" earned "<<element<<" elements for his headquarter"<<endl;
}
bool Cninja::ifhasarrow()
{
    if(weapon1.getnumber()==2 || weapon2.getnumber()==2) return true;
    else return false;
}
void Cninja::shot()
{
    if(weapon1.number==2)
    {
        weapon1.arrowavailable--;
        if(weapon1.arrowavailable==0) weapon1.number=3;
    }
    else if(weapon2.number==2)
    {
        weapon2.arrowavailable--;
        if(weapon2.arrowavailable==0) weapon2.number=3;
    }
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" ninja "<<number<<" shot";
}
bool Cninja::ifdieofarrow()
{
    if(life<=0)
    {
        quarter->warrior[number]=NULL;
        cout<<" and killed "<<quarter->name<<" ninja "<<number;
        return true;
    }
    else return false;
}
bool Cninja::ifhasbomb()
{
    if(weapon1.getnumber()==1 || weapon2.getnumber()==1) return true;
    else return false;
}
bool Cninja::tryattack(Cwarrior *enemy)
{
    if(weapon1.number==0)
    {
        int tmp=enemy->getlife();
        tmp=tmp-(warriorattack+weapon1.weaponattack);
        if(tmp<=0) return true;
        else return false;
    }
    else if(weapon2.number==0)
    {
        int tmp=enemy->getlife();
        tmp=tmp-(warriorattack+weapon2.weaponattack);
        if(tmp<=0) return true;
        else return false;
    }
    else
    {
        int tmp=enemy->getlife();
        tmp=tmp-warriorattack;
        if(tmp<=0) return true;
        else return false;
    }
}
bool Cninja::attack(Cwarrior *enemy)
{
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" ninja "<<number<<" attacked ";
    enemy->get();
    cout<<" in city "<<citynumber<<" with "<<life<<" elements and force "<<warriorattack<<endl;
    if(weapon1.number==0)
    {
        int tmp=enemy->hurt(warriorattack+weapon1.weaponattack);
        weapon1.weaponattack=weapon1.weaponattack*0.8;
        if(weapon1.weaponattack==0) weapon1.number=3;
        if(tmp<=0) return true;
        else return false;
    }
    else if(weapon2.number==0)
    {
        int tmp=enemy->hurt(warriorattack+weapon2.weaponattack);
        weapon2.weaponattack=weapon2.weaponattack*0.8;
        if(weapon2.weaponattack==0) weapon2.number=3;
        if(tmp<=0) return true;
        else return false;
    }
    else
    {
        int tmp=enemy->hurt(warriorattack);
        if(tmp<=0) return true;
        else return false;
    }
}
bool Cninja::tryfightback(Cwarrior *enemy)
{
    return false;
}
void Cninja::usebomb()
{
    quarter->warrior[number]=NULL;
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" ninja "<<number<<" used a bomb ";
    delete this;
}
void Cninja::dieofbomb()
{
    quarter->warrior[number]=NULL;
    cout<<"and killed "<<quarter->name<<" ninja "<<number;
    delete this;
}
void Cninja::get()
{
   cout<<quarter->name<<" ninja "<<number;
}
bool Cninja::fightback(Cwarrior *enemy)
{
    return false;
}
void Cninja::die()
{
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" ninja "<<number<<" was killed in city "<<citynumber<<endl;
    quarter->warrior[number]=NULL;
}
Cweapon Cninja::takeweaponaway(int a)
{
    if(weapon1.number==a)
        return weapon1;
    else if(weapon2.number==a)
        return weapon2;
    else
    {
        Cweapon tmp;
        return tmp;
    }
}
void Cninja::report()
{
    if(weapon1.number==0 && weapon1.weaponattack==0) weapon1.number=3;
    if(weapon2.number==0 && weapon2.weaponattack==0) weapon2.number=3;
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" ninja "<<number<<" has ";
    if(weapon1.number==3 && weapon2.number==3) cout<<weaponname[weapon1.number];
    else
    {
        if(weapon1.number==2)
        {
            cout<<"arrow("<<weapon1.arrowavailable<<")";
            if(weapon2.number!=3) cout<<",";
        }
        if(weapon2.number==2)
        {
            cout<<"arrow("<<weapon2.arrowavailable<<")";
            if(weapon1.number!=3) cout<<",";
        }
        if(weapon1.number==1)
        {
            cout<<"bomb";
            if(weapon2.number==0) cout<<",";
        }
        if(weapon2.number==1)
        {
            cout<<"bomb";
            if(weapon1.number==0) cout<<",";
        }
        if(weapon1.number==0) cout<<"sword("<<weapon1.weaponattack<<")";
        if(weapon2.number==0) cout<<"sword("<<weapon2.weaponattack<<")";
    }
    cout<<endl;
}

class Ciceman:public Cwarrior
{
    Cweapon weapon;
    int step;
public:
    Ciceman(int number,int life,int warriorattack,Cheadquarter *q,int weaponnumber,int step=0):Cwarrior(number,life,warriorattack,q),weapon(weaponnumber),step(step)
    {
        if(weaponnumber==0)
        {
            weapon.weaponattack=warriorattack*0.2;
            if(weapon.weaponattack==0) weapon.number=3;
        }
        cout<<setw(3)<<setfill('0')<<TIME/60<<":";
        cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
        cout<<q->name<<" iceman "<<number<<" born"<<endl;
    }
    virtual void goforward();
    virtual void addelement(int element);
    virtual void addelement1(int element);
    virtual bool ifhasarrow();
    virtual bool ifhasbomb();
    virtual void shot();
    virtual bool ifdieofarrow();
    virtual bool tryattack(Cwarrior *enemy);
    virtual bool attack(Cwarrior *enemy);
    virtual bool tryfightback(Cwarrior *enemy);
    virtual bool fightback(Cwarrior *enemy);
    virtual void usebomb();
    virtual void dieofbomb();
    virtual void get();
    virtual void die();
    virtual void report();
    virtual Cweapon takeweaponaway(int a);
};
void Ciceman::goforward()
{
    step++;
    if(step==2)
    {
        step=0;
        life-=9;
        if(life<=0) life=1;
        warriorattack+=20;
    }
    if(quarter->name=="red") citynumber++;
    else if(quarter->name=="blue") citynumber--;
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    if(quarter->name=="red" && citynumber==city+1)
    {
        cout<<"red iceman "<<number<<" reached blue headquarter with "<<life<<" elements and force "<<warriorattack<<endl;
        quarter->arrive++;
    }
    else if(quarter->name=="blue" && citynumber==0)
    {
        cout<<"blue iceman "<<number<<" reached red headquarter with "<<life<<" elements and force "<<warriorattack<<endl;
        quarter->arrive++;
    }
    else
        cout<<quarter->name<<" iceman "<<number<<" marched to city "<<citynumber<<" with "<<life<<" elements and force "<<warriorattack<<endl;
}
void Ciceman::addelement(int element)
{
    quarter->lifetotal+=element;
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" iceman "<<number<<" earned "<<element<<" elements for his headquarter"<<endl;
}
void Ciceman::addelement1(int element)
{
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" iceman "<<number<<" earned "<<element<<" elements for his headquarter"<<endl;
}
bool Ciceman::ifhasarrow()
{
    if(weapon.getnumber()==2 && weapon.arrowavailable>0) return true;
    else return false;
}
void Ciceman::shot()
{
    weapon.arrowavailable--;
    if(weapon.arrowavailable==0) weapon.number=3;
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" iceman "<<number<<" shot";
}
bool Ciceman::ifdieofarrow()
{
    if(life<=0)
    {
        quarter->warrior[number]=NULL;
        cout<<" and killed "<<quarter->name<<" iceman "<<number;
        return true;
    }
    else return false;
}
bool Ciceman::ifhasbomb()
{
    if(weapon.getnumber()==1) return true;
    else return false;
}
void Ciceman::usebomb()
{
    quarter->warrior[number]=NULL;
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" iceman "<<number<<" used a bomb ";
    delete this;
}
void Ciceman::dieofbomb()
{
    quarter->warrior[number]=NULL;
    cout<<"and killed "<<quarter->name<<" iceman "<<number;
    delete this;
}
bool Ciceman::tryattack(Cwarrior *enemy)
{
    if(weapon.number==0)
    {
        int tmp=enemy->getlife();
        tmp=tmp-(warriorattack+weapon.weaponattack);
        if(tmp<=0) return true;
        else return false;
    }
    else
    {
        int tmp=enemy->getlife();
        tmp=tmp-warriorattack;
        if(tmp<=0) return true;
        else return false;
    }
}
bool Ciceman::tryfightback(Cwarrior *enemy)
{
    if(weapon.number==0)
    {
        int tmp=enemy->getlife();
        tmp=tmp-(warriorattack/2+weapon.weaponattack);
        if(tmp<=0) return true;
        else return false;
    }
    else
    {
        int tmp=enemy->getlife();
        tmp=tmp-warriorattack/2;
        if(tmp<=0) return true;
        else return false;
    }
}
bool Ciceman::attack(Cwarrior *enemy)
{
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" iceman "<<number<<" attacked ";
    enemy->get();
    cout<<" in city "<<citynumber<<" with "<<life<<" elements and force "<<warriorattack<<endl;
    if(weapon.number==0)
    {
        int tmp=enemy->hurt(warriorattack+weapon.weaponattack);
        weapon.weaponattack=weapon.weaponattack*0.8;
        if(weapon.weaponattack==0) weapon.number=3;
        if(tmp<=0) return true;
        else return false;
    }
    else
    {
        int tmp=enemy->hurt(warriorattack);;
        if(tmp<=0) return true;
        else return false;
    }
}
void Ciceman::get()
{
   cout<<quarter->name<<" iceman "<<number;
}
bool Ciceman::fightback(Cwarrior *enemy)
{
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" iceman "<<number<<" fought back against ";
    enemy->get();
    cout<<" in city "<<citynumber<<endl;
    if(weapon.number==0)
    {
        int tmp=enemy->hurt(warriorattack/2+weapon.weaponattack);
        weapon.weaponattack=weapon.weaponattack*0.8;
        if(weapon.weaponattack==0) weapon.number=3;
        if(tmp<=0) return true;
        else return false;
    }
    else
    {
        int tmp=enemy->hurt(warriorattack/2);
        if(tmp<=0) return true;
        else return false;
    }
}
void Ciceman::die()
{
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" iceman "<<number<<" was killed in city "<<citynumber<<endl;
    quarter->warrior[number]=NULL;
}
Cweapon Ciceman::takeweaponaway(int a)
{
    if(weapon.number==a) return weapon;
    else
    {
        Cweapon tmp;
        return tmp;
    }
}
void Ciceman::report()
{
    if(weapon.number==0 && weapon.weaponattack==0) weapon.number=3;
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" iceman "<<number<<" has "<<weaponname[weapon.number];
    if(weapon.number==0) cout<<"("<<weapon.weaponattack<<")";
    if(weapon.number==2) cout<<"("<<weapon.arrowavailable<<")";
    cout<<endl;
}

class Clion:public Cwarrior
{
    int loyalty;
public:
    Clion(int number,int life,int warriorattack,Cheadquarter *q,int loyalty):Cwarrior(number,life,warriorattack,q),loyalty(loyalty)
    {
        cout<<setw(3)<<setfill('0')<<TIME/60<<":";
        cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
        cout<<q->name<<" lion "<<number<<" born"<<endl;
        cout<<"Its loyalty is "<<loyalty<<endl;
    }
    virtual void runaway();
    virtual int getloyalty(){return loyalty;}
    virtual void reduceloyalty(){loyalty-=lionK;}
    virtual void goforward();
    virtual void addelement(int element);
    virtual void addelement1(int element);
    virtual bool ifhasarrow();
    virtual bool ifhasbomb();
    virtual bool ifdieofarrow();
    virtual bool tryattack(Cwarrior *enemy);
    virtual bool attack(Cwarrior *enemy);
    virtual bool tryfightback(Cwarrior *enemy);
    virtual bool fightback(Cwarrior *enemy);
    virtual void usebomb();
    virtual void dieofbomb();
    virtual void get();
    virtual void die();
    virtual void report();
    virtual Cweapon takeweaponaway(int a);
};
void Clion::runaway()
{
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" lion "<<number<<" ran away"<<endl;
    quarter->warrior[number]=NULL;
    delete this;
}
void Clion::goforward()
{
    if(quarter->name=="red") citynumber++;
    else if(quarter->name=="blue") citynumber--;
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    if(quarter->name=="red" && citynumber==city+1)
    {
        cout<<"red lion "<<number<<" reached blue headquarter with "<<life<<" elements and force "<<warriorattack<<endl;
        quarter->arrive++;
    }
    else if(quarter->name=="blue" && citynumber==0)
    {
        cout<<"blue lion "<<number<<" reached red headquarter with "<<life<<" elements and force "<<warriorattack<<endl;
        quarter->arrive++;
    }
    else
    cout<<quarter->name<<" lion "<<number<<" marched to city "<<citynumber<<" with "<<life<<" elements and force "<<warriorattack<<endl;
}
void Clion::addelement(int element)
{
    quarter->lifetotal+=element;
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" lion "<<number<<" earned "<<element<<" elements for his headquarter"<<endl;
}
void Clion::addelement1(int element)
{
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" lion "<<number<<" earned "<<element<<" elements for his headquarter"<<endl;
}
bool Clion::ifhasarrow()
{
    return false;
}
bool Clion::ifdieofarrow()
{
    if(life<=0)
    {
        quarter->warrior[number]=NULL;
        cout<<" and killed "<<quarter->name<<" lion "<<number;
        return true;
    }
    else return false;
}
bool Clion::ifhasbomb()
{
    return false;
}
bool Clion::tryattack(Cwarrior *enemy)
{
    int tmp=enemy->getlife();
    tmp=tmp-warriorattack;
    if(tmp<=0) return true;
    else return false;
}
bool Clion::attack(Cwarrior *enemy)
{
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" lion "<<number<<" attacked ";
    enemy->get();
    cout<<" in city "<<citynumber<<" with "<<life<<" elements and force "<<warriorattack<<endl;
    int tmp=enemy->hurt(warriorattack);
    if(tmp<=0) return true;
    else return false;
}
bool Clion::tryfightback(Cwarrior *enemy)
{
    int tmp=enemy->getlife();
    tmp=tmp-warriorattack/2;
    if(tmp<=0) return true;
    else return false;
}
void Clion::usebomb()
{
    quarter->warrior[number]=NULL;
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" lion "<<number<<" used a bomb ";
    delete this;
}
void Clion::dieofbomb()
{
    quarter->warrior[number]=NULL;
    cout<<"and killed "<<quarter->name<<" lion "<<number;
    delete this;
}
void Clion::get()
{
   cout<<quarter->name<<" lion "<<number;
}
bool Clion::fightback(Cwarrior *enemy)
{
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" lion "<<number<<" fought back against ";
    enemy->get();
    cout<<" in city "<<citynumber<<endl;
    int tmp=enemy->hurt(warriorattack/2);
    if(tmp<=0) return true;
    else return false;
}
void Clion::die()
{
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" lion "<<number<<" was killed in city "<<citynumber<<endl;
    quarter->warrior[number]=NULL;
}
Cweapon Clion::takeweaponaway(int a)
{
    Cweapon tmp;
    return tmp;
}
void Clion::report()
{
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" lion "<<number<<" has no weapon"<<endl;
}

class Cwolf:public Cwarrior
{
    Cweapon weapon1;
    Cweapon weapon2;
    Cweapon weapon3;
public:
    Cwolf(int number,int life,int warriorattack,Cheadquarter *q):Cwarrior(number,life,warriorattack,q)
    {
        cout<<setw(3)<<setfill('0')<<TIME/60<<":";
        cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
        cout<<q->name<<" wolf "<<number<<" born"<<endl;
    }
    virtual void goforward();
    virtual void addelement(int element);
    virtual void addelement1(int element);
    virtual bool ifhasarrow();
    virtual bool ifhasbomb();
    virtual void shot();
    virtual bool ifdieofarrow();
    virtual bool tryattack(Cwarrior *enemy);
    virtual bool attack(Cwarrior *enemy);
    virtual bool tryfightback(Cwarrior *enemy);
    virtual bool fightback(Cwarrior *enemy);
    virtual void usebomb();
    virtual void dieofbomb();
    virtual void get();
    virtual void die();
    virtual void report();
    virtual void getweapon(Cwarrior *enemy);
    virtual Cweapon takeweaponaway(int a);
};
void Cwolf::goforward()
{
    if(quarter->name=="red") citynumber++;
    else if(quarter->name=="blue") citynumber--;
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    if(quarter->name=="red" && citynumber==city+1)
    {
        cout<<"red wolf "<<number<<" reached blue headquarter with "<<life<<" elements and force "<<warriorattack<<endl;
        quarter->arrive++;
    }
    else if(quarter->name=="blue" && citynumber==0)
    {
        cout<<"blue wolf "<<number<<" reached red headquarter with "<<life<<" elements and force "<<warriorattack<<endl;
        quarter->arrive++;
    }
    else
    cout<<quarter->name<<" wolf "<<number<<" marched to city "<<citynumber<<" with "<<life<<" elements and force "<<warriorattack<<endl;
}
void Cwolf::addelement(int element)
{
    quarter->lifetotal+=element;
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" wolf "<<number<<" earned "<<element<<" elements for his headquarter"<<endl;
}
void Cwolf::addelement1(int element)
{
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" wolf "<<number<<" earned "<<element<<" elements for his headquarter"<<endl;
    //cout<<life<<endl;
}
bool Cwolf::ifhasarrow()
{
    if(weapon1.getnumber()==2 && weapon1.arrowavailable>0) return true;
    if(weapon2.getnumber()==2 && weapon2.arrowavailable>0) return true;
    if(weapon3.getnumber()==2 && weapon3.arrowavailable>0) return true;
    else return false;
}
void Cwolf::shot()
{
    if(weapon1.number==2)
    {
        weapon1.arrowavailable--;
        if(weapon1.arrowavailable==0) weapon1.number=3;
    }
    if(weapon2.number==2)
    {
        weapon2.arrowavailable--;
        if(weapon2.arrowavailable==0) weapon2.number=3;
    }
    if(weapon3.number==2)
    {
        weapon3.arrowavailable--;
        if(weapon3.arrowavailable==0) weapon3.number=3;
    }
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" wolf "<<number<<" shot";
}
bool Cwolf::ifdieofarrow()
{
    if(life<=0)
    {
        quarter->warrior[number]=NULL;
        cout<<" and killed "<<quarter->name<<" wolf "<<number;
        return true;
    }
    else return false;
}
bool Cwolf::ifhasbomb()
{
    if(weapon1.number==1) return true;
    if(weapon2.number==1) return true;
    if(weapon3.number==1) return true;
    else return false;
}
bool Cwolf::tryattack(Cwarrior *enemy)
{
    if(weapon1.number==0)
    {
        int tmp=enemy->getlife();
        tmp=tmp-(warriorattack+weapon1.weaponattack);
        if(tmp<=0) return true;
        else return false;
    }
    else if(weapon2.number==0)
    {
        int tmp=enemy->getlife();
        tmp=tmp-(warriorattack+weapon2.weaponattack);
        if(tmp<=0) return true;
        else return false;
    }
    else if(weapon3.number==0)
    {
        int tmp=enemy->getlife();
        tmp=tmp-(warriorattack+weapon3.weaponattack);
        if(tmp<=0) return true;
        else return false;
    }
    else
    {
        int tmp=enemy->getlife();
        tmp=tmp-warriorattack;
        if(tmp<=0) return true;
        else return false;
    }
}
bool Cwolf::tryfightback(Cwarrior *enemy)
{
    if(weapon1.number==0)
    {
        int tmp=enemy->getlife();
        tmp=tmp-(warriorattack/2+weapon1.weaponattack);
        if(tmp<=0) return true;
        else return false;
    }
    else if(weapon2.number==0)
    {
        int tmp=enemy->getlife();
        tmp=tmp-(warriorattack/2+weapon2.weaponattack);
        if(tmp<=0) return true;
        else return false;
    }
    else if(weapon3.number==0)
    {
        int tmp=enemy->getlife();
        tmp=tmp-(warriorattack/2+weapon3.weaponattack);
        if(tmp<=0) return true;
        else return false;
    }
    else
    {
        int tmp=enemy->getlife();
        tmp=tmp-warriorattack/2;
        if(tmp<=0) return true;
        else return false;
    }
}
bool Cwolf::attack(Cwarrior *enemy)
{
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" wolf "<<number<<" attacked ";
    enemy->get();
    cout<<" in city "<<citynumber<<" with "<<life<<" elements and force "<<warriorattack<<endl;
    if(weapon1.number==0)
    {
        int tmp=enemy->hurt(warriorattack+weapon1.weaponattack);
        weapon1.weaponattack=weapon1.weaponattack*0.8;
        if(weapon1.weaponattack==0) weapon1.number=3;
        if(tmp<=0) return true;
        else return false;
    }
    else if(weapon2.number==0)
    {
        int tmp=enemy->hurt(warriorattack+weapon2.weaponattack);
        weapon2.weaponattack=weapon2.weaponattack*0.8;
        if(weapon2.weaponattack==0) weapon2.number=3;
        if(tmp<=0) return true;
        else return false;
    }
    else if(weapon3.number==0)
    {
        int tmp=enemy->hurt(warriorattack+weapon3.weaponattack);
        weapon3.weaponattack=weapon3.weaponattack*0.8;
        if(weapon3.weaponattack==0) weapon3.number=3;
        if(tmp<=0) return true;
        else return false;
    }
    else
    {
        int tmp=enemy->hurt(warriorattack);
        if(tmp<=0)  return true;
        else return false;
    }
}
void Cwolf::usebomb()
{
    quarter->warrior[number]=NULL;
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" wolf "<<number<<" used a bomb ";
    delete this;
}
void Cwolf::dieofbomb()
{
    quarter->warrior[number]=NULL;
    cout<<"and killed "<<quarter->name<<" wolf "<<number;
    delete this;
}
void Cwolf::get()
{
   cout<<quarter->name<<" wolf "<<number;
}
bool Cwolf::fightback(Cwarrior *enemy)
{
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" wolf "<<number<<" fought back against ";
    enemy->get();
    cout<<" in city "<<citynumber<<endl;
    if(weapon1.number==0)
    {
        int tmp=enemy->hurt(warriorattack/2+weapon1.weaponattack);
        weapon1.weaponattack=weapon1.weaponattack*0.8;
        if(weapon1.weaponattack==0) weapon1.number=3;
        if(tmp<=0) return true;
        else return false;
    }
    else if(weapon2.number==0)
    {
        int tmp=enemy->hurt(warriorattack/2+weapon2.weaponattack);
        weapon2.weaponattack=weapon2.weaponattack*0.8;
        if(weapon2.weaponattack==0) weapon2.number=3;
        if(tmp<=0) return true;
        else return false;
    }
    else if(weapon3.number==0)
    {
        int tmp=enemy->hurt(warriorattack/2+weapon3.weaponattack);
        weapon3.weaponattack=weapon3.weaponattack*0.8;
        if(weapon3.weaponattack==0) weapon3.number=3;
        if(tmp<=0) return true;
        else return false;
    }
    else
    {
        int tmp=enemy->hurt(warriorattack/2);
        if(tmp<=0) return true;
        else return false;
    }
}
void Cwolf::die()
{
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" wolf "<<number<<" was killed in city "<<citynumber<<endl;
    quarter->warrior[number]=NULL;
}
Cweapon Cwolf::takeweaponaway(int a)
{
    if(weapon1.number==a)
        return weapon1;
    else if(weapon2.number==a)
        return weapon2;
    else if(weapon3.number==a)
        return weapon3;
    else
    {
        Cweapon tmp;
        return tmp;
    }
}
void Cwolf::getweapon(Cwarrior *enemy)
{
    if(weapon1.number!=0 && weapon2.number!=0 && weapon3.number!=0)
    {
        if(weapon1.number==3) weapon1=enemy->takeweaponaway(0);
        else if(weapon2.number==3) weapon2=enemy->takeweaponaway(0);
        else if(weapon3.number==3) weapon3=enemy->takeweaponaway(0);
    }
    if(weapon1.number!=1 && weapon2.number!=1 && weapon3.number!=1)
    {
        if(weapon1.number==3) weapon1=enemy->takeweaponaway(1);
        else if(weapon2.number==3) weapon2=enemy->takeweaponaway(1);
        else if(weapon3.number==3) weapon3=enemy->takeweaponaway(1);
    }
    if(weapon1.number!=2 && weapon2.number!=2 && weapon3.number!=2)
    {
        if(weapon1.number==3) weapon1=enemy->takeweaponaway(2);
        else if(weapon2.number==3) weapon2=enemy->takeweaponaway(2);
        else if(weapon3.number==3) weapon3=enemy->takeweaponaway(2);
    }
}
void Cwolf::report()
{
    if(weapon1.number==0 && weapon1.weaponattack==0) weapon1.number=3;
    if(weapon2.number==0 && weapon2.weaponattack==0) weapon2.number=3;
    if(weapon3.number==0 && weapon3.weaponattack==0) weapon3.number=3;
    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
    cout<<quarter->name<<" wolf "<<number<<" has ";
    if(weapon1.number==3 && weapon2.number==3 && weapon3.number==3) cout<<weaponname[weapon1.number];
    else
    {
        if(weapon1.number==2)
        {
            cout<<"arrow("<<weapon1.arrowavailable<<")";
            if(weapon2.number!=3 || weapon3.number!=3) cout<<",";
        }
        if(weapon2.number==2)
        {
            cout<<"arrow("<<weapon2.arrowavailable<<")";
            if(weapon1.number!=3 || weapon3.number!=3) cout<<",";
        }
        if(weapon3.number==2)
        {
            cout<<"arrow("<<weapon3.arrowavailable<<")";
            if(weapon1.number!=3 || weapon2.number!=3) cout<<",";
        }
        if(weapon1.number==1)
        {
            cout<<"bomb";
            if(weapon2.number==0 || weapon3.number==0) cout<<",";
        }
        if(weapon2.number==1)
        {
            cout<<"bomb";
            if(weapon1.number==0 || weapon3.number==0) cout<<",";
        }
        if(weapon3.number==1)
        {
            cout<<"bomb";
            if(weapon1.number==0 || weapon2.number==0) cout<<",";
        }
        if(weapon1.number==0) cout<<"sword("<<weapon1.weaponattack<<")";
        if(weapon2.number==0) cout<<"sword("<<weapon2.weaponattack<<")";
        if(weapon3.number==0) cout<<"sword("<<weapon3.weaponattack<<")";
    }
    cout<<endl;
}

//红方司令部按照 iceman、lion、wolf、ninja、dragon 的顺序制造武士。
bool Cheadquarter::makeredwarrior()
{
    if(warriortotal%5==0 && lifetotal>=icemanlife)
    {
        warriortotal++;
        lifetotal-=icemanlife;
        warrior[warriortotal]=new Ciceman(warriortotal,icemanlife,icemanATK,this,warriortotal%3);
        return true;
    }
    else if(warriortotal%5==1 && lifetotal>=lionlife)
    {
        warriortotal++;
        lifetotal-=lionlife;
        warrior[warriortotal]=new Clion(warriortotal,lionlife,lionATK,this,lifetotal);
        return true;
    }
    else if(warriortotal%5==2 && lifetotal>=wolflife)
    {
        warriortotal++;
        lifetotal-=wolflife;
        warrior[warriortotal]=new Cwolf(warriortotal,wolflife,wolfATK,this);
        return true;
    }
    else if(warriortotal%5==3 && lifetotal>=ninjalife)
    {
        warriortotal++;
        lifetotal-=ninjalife;
        warrior[warriortotal]=new Cninja(warriortotal,ninjalife,ninjaATK,this,warriortotal%3,(warriortotal+1)%3);
        return true;
    }
    else if(warriortotal%5==4 && lifetotal>=dragonlife)
    {
        warriortotal++;
        lifetotal-=dragonlife;
        warrior[warriortotal]=new Cdragon(warriortotal,dragonlife,dragonATK,this,warriortotal%3,lifetotal*1.00/dragonlife);
        return true;
    }
    return false;

}
//蓝方司令部按照 lion、dragon、ninja、iceman、wolf 的顺序制造武士。
bool Cheadquarter::makebluewarrior()
{
    if(warriortotal%5==0 && lifetotal>=lionlife)
    {
        warriortotal++;
        lifetotal-=lionlife;
        warrior[warriortotal]=new Clion(warriortotal,lionlife,lionATK,this,lifetotal);
        return true;
    }
    else if(warriortotal%5==1 && lifetotal>=dragonlife)
    {
        warriortotal++;
        lifetotal-=dragonlife;
        warrior[warriortotal]=new Cdragon(warriortotal,dragonlife,dragonATK,this,warriortotal%3,lifetotal*1.00/dragonlife);
        return true;
    }
    else if(warriortotal%5==2 && lifetotal>=ninjalife)
    {
        warriortotal++;
        lifetotal-=ninjalife;
        warrior[warriortotal]=new Cninja(warriortotal,ninjalife,ninjaATK,this,warriortotal%3,(warriortotal+1)%3);
        return true;
    }
    else if(warriortotal%5==3 && lifetotal>=icemanlife)
    {
        warriortotal++;
        lifetotal-=icemanlife;
        warrior[warriortotal]=new Ciceman(warriortotal,icemanlife,icemanATK,this,warriortotal%3);
        return true;
    }
    else if(warriortotal%5==4 && lifetotal>=wolflife)
    {
        warriortotal++;
        lifetotal-=wolflife;
        warrior[warriortotal]=new Cwolf(warriortotal,wolflife,wolfATK,this);
        return true;
    }
    return false;
}
bool Cheadquarter::ifistaken()
{
    if(arrive==2 && name=="red")
    {
        cout<<setw(3)<<setfill('0')<<TIME/60<<":";
        cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
        cout<<"blue headquarter was taken"<<endl;
        return true;
    }
    else if(arrive==2 && name=="blue")
    {
        cout<<setw(3)<<setfill('0')<<TIME/60<<":";
        cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
        cout<<"red headquarter was taken"<<endl;
        return true;
    }
    return false;
}

class City//城市类
{
    int number;//编号
    int elements;//生命元
    int sumwarrior;//武士数量
public:
    int lastwin;
    int nowwin;
    char flag;
    Cwarrior *warrior[2];
    City(int number,int elements=0,int sumwarrior=0,char flag='N',int lastwin=-1,int nowwin=-1):number(number),elements(elements),sumwarrior(sumwarrior),flag(flag),lastwin(lastwin),nowwin(nowwin)
    {
        warrior[0]=NULL;
        warrior[1]=NULL;
    }
    void addelement() {elements+=10;}
    int getelement()
    {
        int save=elements;
        elements=0;
        return save;
    }
    int getelements(){return elements;}
    int &getsumwarrior() {return sumwarrior;}
    void addwarrior()  {sumwarrior++;}
    void reducewarrior() {sumwarrior--;}
};

void process()
{
    Cheadquarter red("red"),blue("blue");
        cin>>LifeTotal>>city>>arrowR>>lionK>>CLOCK;
        red.lifetotal=LifeTotal;
        blue.lifetotal=LifeTotal;

        City *cities[city];
        for(int i=0;i<=city+1;i++)
            cities[i]=new City(i);

        cin>>dragonlife>>ninjalife>>icemanlife>>lionlife>>wolflife;
        cin>>dragonATK>>ninjaATK>>icemanATK>>lionATK>>wolfATK;

        cout<<"Case "<<k<<":"<<endl;
        for(TIME=0;TIME<=CLOCK;TIME++)
        {
            if(TIME%60==0)
            {
                bool tmp=red.makeredwarrior();
                if(tmp)
                {
                    cities[0]->warrior[0]=red.warrior[red.warriortotal];
                }
                bool tmpp=blue.makebluewarrior();
                if(tmpp)
                {
                    cities[city+1]->warrior[1]=blue.warrior[blue.warriortotal];
                }
                TIME+=4;
            }
            else if(TIME%60==5)
            {
                if(cities[0]->warrior[0]!=NULL && cities[0]->warrior[0]->getnumber()%5==2)
                {
                    if(cities[0]->warrior[0]->getloyalty()<=0)
                    {
                        cities[0]->warrior[0]->runaway();
                        cities[0]->warrior[0]=NULL;
                    }
                }
                for(int i=1;i<=city;i++)
                {
                    if(cities[i]->warrior[0]!=NULL && cities[i]->warrior[0]->getnumber()%5==2)
                    {
                        if(cities[i]->warrior[0]->getloyalty()<=0)
                        {
                            cities[i]->warrior[0]->runaway();
                            cities[i]->warrior[0]=NULL;
                        }
                    }
                    if(cities[i]->warrior[1]!=NULL && cities[i]->warrior[1]->getnumber()%5==1)
                    {
                        if(cities[i]->warrior[1]->getloyalty()<=0)
                        {
                            cities[i]->warrior[1]->runaway();
                            cities[i]->warrior[1]=NULL;
                        }
                    }
                }
                if(cities[city+1]->warrior[1]!=NULL && cities[city+1]->warrior[1]->getnumber()%5==1)
                {
                    if(cities[city+1]->warrior[1]->getloyalty()<=0)
                    {
                        cities[city+1]->warrior[1]->runaway();
                        cities[city+1]->warrior[1]=NULL;
                    }
                }
                TIME+=4;
            }
            else if(TIME%60==10)
            {
                bool tmp1=0,tmp2=0;
                if(cities[1]->warrior[1]!=NULL)
                {
                    cities[1]->warrior[1]->goforward();
                    tmp1=blue.ifistaken();
                }
                for(int i=1;i<=city;i++)
                {
                    if(cities[i-1]->warrior[0]!=NULL)
                    {
                        cities[i-1]->warrior[0]->goforward();
                    }
                    if(cities[i+1]->warrior[1]!=NULL)
                    {
                        cities[i+1]->warrior[1]->goforward();
                    }
                }
                if(cities[city]->warrior[0]!=NULL)
                {
                    cities[city]->warrior[0]->goforward();
                    tmp2=red.ifistaken();
                }
                if(tmp1==1 || tmp2==1) return;
                for(int i=0;i<=city+1;i++)
                {
                    cities[i]->warrior[0]=NULL;
                    cities[i]->warrior[1]=NULL;
                    cities[i]->getsumwarrior()=0;
                }
                for(int i=1;i<=red.warriortotal;i++)
                {
                    if(red.warrior[i]!=NULL)
                    {
                        cities[red.warrior[i]->getcitynumber()]->warrior[0]=red.warrior[i];
                        cities[red.warrior[i]->getcitynumber()]->addwarrior();
                    }
                }
                for(int i=1;i<=blue.warriortotal;i++)
                {
                    if(blue.warrior[i]!=NULL)
                    {
                        cities[blue.warrior[i]->getcitynumber()]->warrior[1]=blue.warrior[i];
                        cities[blue.warrior[i]->getcitynumber()]->addwarrior();
                    }
                }
                TIME+=9;
            }
            else if(TIME%60==20)
            {
                for(int i=1;i<=city;i++)
                    cities[i]->addelement();
                TIME+=9;
            }
            else if(TIME%60==30)
            {
                for(int i=1;i<=city;i++)
                {
                    if(cities[i]->getsumwarrior()==1)
                    {
                        if(cities[i]->warrior[0]!=NULL)
                        {
                            cities[i]->warrior[0]->addelement(cities[i]->getelement());
                        }
                        else if(cities[i]->warrior[1]!=NULL)
                        {
                            cities[i]->warrior[1]->addelement(cities[i]->getelement());
                        }
                    }
                }
                TIME+=4;
            }
            else if(TIME%60==35)
            {
                if(cities[1]->warrior[0]!=NULL && cities[1]->warrior[0]->ifhasarrow()==true)
                {
                    if(cities[2]->warrior[1]!=NULL)
                    {
                        cities[1]->warrior[0]->shot();
                        cities[2]->warrior[1]->hurt(arrowR);
                        cities[2]->warrior[1]->ifdieofarrow();
                        cout<<endl;
                    }
                }
                for(int i=2;i<=city-1;i++)
                {
                    if(cities[i]->warrior[0]!=NULL && cities[i]->warrior[0]->ifhasarrow()==true)
                    {
                        if(cities[i+1]->warrior[1]!=NULL)
                        {
                            cities[i]->warrior[0]->shot();
                            cities[i+1]->warrior[1]->hurt(arrowR);
                            cities[i+1]->warrior[1]->ifdieofarrow();
                            cout<<endl;
                        }
                    }
                    if(cities[i]->warrior[1]!=NULL && cities[i]->warrior[1]->ifhasarrow()==true)
                    {
                        if(cities[i-1]->warrior[0]!=NULL)
                        {
                            cities[i]->warrior[1]->shot();
                            cities[i-1]->warrior[0]->hurt(arrowR);
                            cities[i-1]->warrior[0]->ifdieofarrow();
                            cout<<endl;
                        }
                    }
                }
                if(cities[city]->warrior[1]!=NULL && cities[city]->warrior[1]->ifhasarrow()==true)
                {
                    if(cities[city-1]->warrior[0]!=NULL)
                    {
                        cities[city]->warrior[1]->shot();
                        cities[city-1]->warrior[0]->hurt(arrowR);
                        cities[city-1]->warrior[0]->ifdieofarrow();
                        cout<<endl;
                    }
                }
                TIME+=2;
            }
            else if(TIME%60==38)
            {
                for(int i=1;i<=city;i++)
                {
                    if(cities[i]->warrior[0]!=NULL && cities[i]->warrior[1]!=NULL)
                    {
                        if(cities[i]->warrior[0]->getlife()>0 && cities[i]->warrior[1]->getlife()>0)
                        {
                            if(cities[i]->warrior[0]->ifhasbomb())
                            {
                                if((cities[i]->warrior[0]->tryattack(cities[i]->warrior[1])==false && cities[i]->warrior[1]->tryfightback(cities[i]->warrior[0])==true
                                    && (cities[i]->flag=='R' || (cities[i]->flag=='N' && i%2==1)))
                                   || (cities[i]->warrior[1]->tryattack(cities[i]->warrior[0])==true) && (cities[i]->flag=='B' || (cities[i]->flag=='N' && i%2==0)))
                                {
                                    cities[i]->warrior[0]->usebomb();
                                    cities[i]->warrior[1]->dieofbomb();
                                    cout<<endl;
                                    cities[i]->warrior[0]=NULL;
                                    cities[i]->warrior[1]=NULL;
                                    cities[i]->reducewarrior();
                                    cities[i]->reducewarrior();
                                    continue;
                                }
                            }
                            if(cities[i]->warrior[1]->ifhasbomb())
                            {
                                if((cities[i]->warrior[1]->tryattack(cities[i]->warrior[0])==false && cities[i]->warrior[0]->tryfightback(cities[i]->warrior[1])==true
                                    && (cities[i]->flag=='B' || (cities[i]->flag=='N' && i%2==0)))
                                   || (cities[i]->warrior[0]->tryattack(cities[i]->warrior[1])==true) && (cities[i]->flag=='R' || (cities[i]->flag=='N' && i%2==1)))
                                {
                                    cities[i]->warrior[1]->usebomb();
                                    cities[i]->warrior[0]->dieofbomb();
                                    cout<<endl;
                                    cities[i]->warrior[0]=NULL;
                                    cities[i]->warrior[1]=NULL;
                                    cities[i]->reducewarrior();
                                    cities[i]->reducewarrior();
                                }
                            }
                        }
                    }
                }
                TIME+=1;
            }
            else if(TIME%60==40)
            {
                for(int i=1;i<=city;i++)
                {
                    int rred=0,bblue=0;
                    if(cities[i]->getsumwarrior()==2)
                    {
                        if(cities[i]->warrior[0]->getlife()>0 && cities[i]->warrior[1]->getlife()>0)
                        {
                            if(cities[i]->warrior[0]->getnumber()%5==2) rred=cities[i]->warrior[0]->getlife();
                            if(cities[i]->warrior[1]->getnumber()%5==1) bblue=cities[i]->warrior[1]->getlife();

                            if(cities[i]->flag=='R' || (cities[i]->flag=='N' && i%2==1))
                            {
                                bool win1=cities[i]->warrior[0]->attack(cities[i]->warrior[1]);
                                if(win1)
                                    cities[i]->warrior[1]->die();
                                else
                                {
                                    bool win2=cities[i]->warrior[1]->fightback(cities[i]->warrior[0]);
                                    if(win2)
                                        cities[i]->warrior[0]->die();
                                }
                            }
                            else if(cities[i]->flag=='B' || (cities[i]->flag=='N' && i%2==0))
                            {
                                bool win3=cities[i]->warrior[1]->attack(cities[i]->warrior[0]);
                                if(win3)
                                    cities[i]->warrior[0]->die();
                                else
                                {
                                    bool win4=cities[i]->warrior[0]->fightback(cities[i]->warrior[1]);
                                    if(win4)
                                        cities[i]->warrior[1]->die();
                                }
                            }
                        }
                        //作战完毕
                        if(cities[i]->warrior[0]->getlife()>0 && cities[i]->warrior[1]->getlife()<=0)//红方赢
                        {
                            if(cities[i]->warrior[0]->getnumber()%5==0)
                            {
                                cities[i]->warrior[0]->addmorale();
                                if(cities[i]->flag=='R' || (cities[i]->flag=='N' && i%2==1))
                                    cities[i]->warrior[0]->yell();//武士欢呼
                            }
                            if(cities[i]->warrior[1]->getnumber()%5==1)
                                cities[i]->warrior[0]->addlife(bblue);
                            if(cities[i]->warrior[0]->getnumber()%5==3)
                                cities[i]->warrior[0]->getweapon(cities[i]->warrior[1]);
                            //获取生命元
                            cities[i]->warrior[0]->addelement1(cities[i]->getelements());
                            //旗帜升起
                            cities[i]->lastwin=cities[i]->nowwin;
                            cities[i]->nowwin=0;
                            if(cities[i]->lastwin==cities[i]->nowwin && cities[i]->flag!='R')
                            {
                                    cout<<setw(3)<<setfill('0')<<TIME/60<<":";
                                    cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
                                    cout<<"red flag raised in city "<<i<<endl;
                                    cities[i]->flag='R';
                            }
                        }
                        else if(cities[i]->warrior[1]->getlife()>0 && cities[i]->warrior[0]->getlife()<=0)//蓝方赢
                        {
                            if(cities[i]->warrior[1]->getnumber()%5==2)
                            {
                                cities[i]->warrior[1]->addmorale();
                                if(cities[i]->flag=='B' || (cities[i]->flag=='N' && i%2==0))
                                    cities[i]->warrior[1]->yell();
                            }
                            if(cities[i]->warrior[0]->getnumber()%5==2)
                                cities[i]->warrior[1]->addlife(rred);
                            if(cities[i]->warrior[1]->getnumber()%5==0)
                                cities[i]->warrior[1]->getweapon(cities[i]->warrior[0]);
                            //获取生命元
                            cities[i]->warrior[1]->addelement1(cities[i]->getelements());
                            //旗帜升起
                            cities[i]->lastwin=cities[i]->nowwin;
                            cities[i]->nowwin=1;
                            if(cities[i]->lastwin==cities[i]->nowwin && cities[i]->flag!='B')
                            {
                                cout<<setw(3)<<setfill('0')<<TIME/60<<":";
                                cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
                                cout<<"blue flag raised in city "<<i<<endl;
                                cities[i]->flag='B';
                            }
                        }
                        else if(cities[i]->warrior[0]->getlife()>0 && cities[i]->warrior[1]->getlife()>0)//平手
                        {
                            if(cities[i]->warrior[0]->getnumber()%5==0)
                            {
                                cities[i]->warrior[0]->reducemorale();
                                if(cities[i]->flag=='R' || (cities[i]->flag=='N' && i%2==1))
                                    cities[i]->warrior[0]->yell();
                            }
                            if(cities[i]->warrior[0]->getnumber()%5==2)
                                cities[i]->warrior[0]->reduceloyalty();
                            if(cities[i]->warrior[1]->getnumber()%5==2)
                            {
                                cities[i]->warrior[1]->reducemorale();
                                if(cities[i]->flag=='B' || (cities[i]->flag=='N' && i%2==0))
                                    cities[i]->warrior[1]->yell();
                            }
                            if(cities[i]->warrior[1]->getnumber()%5==1)
                                cities[i]->warrior[1]->reduceloyalty();
                            cities[i]->lastwin=cities[i]->nowwin;
                            cities[i]->nowwin=-1;
                        }
                    }
                }
                //删除已死武士
                for(int i=1;i<=city;i++)
                {
                    if(cities[i]->warrior[0]!=NULL && cities[i]->warrior[0]->getlife()<=0)
                    {
                        delete cities[i]->warrior[0];
                        cities[i]->warrior[0]=NULL;
                    }
                    if(cities[i]->warrior[1]!=NULL && cities[i]->warrior[1]->getlife()<=0)
                    {
                        delete cities[i]->warrior[1];
                        cities[i]->warrior[1]=NULL;
                    }
                }
                //奖励
                for(int i=city;i>=1;i--)
                {
                    if(cities[i]->getsumwarrior()==2 && cities[i]->warrior[0]!=NULL && cities[i]->warrior[1]==NULL)
                    {
                        cities[i]->warrior[0]->addlife(8);
                        red.lifetotal-=8;
                    }
                    if(red.lifetotal<8) break;
                }
                for(int i=1;i<=city;i++)
                {
                    if(cities[i]->getsumwarrior()==2 && cities[i]->warrior[1]!=NULL && cities[i]->warrior[0]==NULL)
                    {
                        cities[i]->warrior[1]->addlife(8);
                        blue.lifetotal-=8;
                    }
                    if(blue.lifetotal<8) break;
                }
                //司令部收回战利品
                for(int i=1;i<=city;i++)
                {
                    if(cities[i]->getsumwarrior()==2)
                    {
                        if(cities[i]->warrior[0]!=NULL && cities[i]->warrior[1]==NULL)
                        {
                            cities[i]->warrior[0]->earnelement(cities[i]->getelement());
                        }
                        if(cities[i]->warrior[1]!=NULL && cities[i]->warrior[0]==NULL)
                        {
                            cities[i]->warrior[1]->earnelement(cities[i]->getelement());
                        }
                    }
                }
                TIME+=9;
            }
            else if(TIME%60==50)
            {
                cout<<setw(3)<<setfill('0')<<TIME/60<<":";
                cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
                cout<<red.lifetotal<<" elements in red headquarter"<<endl;
                cout<<setw(3)<<setfill('0')<<TIME/60<<":";
                cout<<setw(2)<<setfill('0')<<TIME%60<<" ";
                cout<<blue.lifetotal<<" elements in blue headquarter"<<endl;;
                TIME+=4;
            }
            else if(TIME%60==55)
            {
                for(int i=0;i<=city+1;i++)
                {
                    if(cities[i]->warrior[0]!=NULL)
                        cities[i]->warrior[0]->report();
                }
                for(int i=0;i<=city+1;i++)
                {
                    if(cities[i]->warrior[1]!=NULL)
                        cities[i]->warrior[1]->report();
                }
                TIME+=4;
            }
        }
}

int main()
{
    cin>>n;
    for(k=1;k<=n;k++)
    {
        process();
    }
    return 0;
}