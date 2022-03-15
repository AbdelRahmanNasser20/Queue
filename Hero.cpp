#include "Hero.h"

Hero::Hero(){}

Hero::Hero(string name, string desc, int hp, int combat, int rarity){
    m_name = name;
    m_desc = desc;
    m_combat = combat;
    m_hp = hp;
    m_rarity = rarity;
}


int Hero::GetCombat(){return m_combat;}


int Hero::GetHp(){return m_hp;}


int Hero::GetRarity(){return m_rarity;}

string Hero::GetName(){return m_name;}


string Hero::GetDesc(){return m_desc;}


void Hero::SetHp(int newHp){m_hp = newHp;}


void Hero::SetCombat(int newCombat){m_combat = newCombat;}


void Hero::Train(){m_combat+=10;}


void Hero::Attack(){cout << " Hero deals " << m_combat << endl;}


ostream& operator<< (ostream& os, Hero &myHero){
  cout << myHero.GetName() << "(hp:" << myHero.GetHp() << " combat:" << myHero.GetCombat() << ") " << endl;
    return os;
  }
