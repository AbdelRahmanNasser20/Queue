#include "Villain.h"

Villain::Villain(){}

Villain::Villain(string name, string desc, int hp, int combat, int rarity){
    m_name = name;
    m_desc = desc;
    m_combat = combat;
    m_hp = hp;
    m_rarity = rarity;
}

int Villain::GetCombat(){return m_combat;}

int Villain::GetHp(){return m_hp;}

int Villain::GetRarity(){return m_rarity;}

string Villain::GetName(){return m_name;}

string Villain::GetDesc(){return m_desc;}

void Villain::SetHp(int newHp){m_hp = newHp;}

void Villain::SetCombat(int newCombat){m_combat = newCombat;}

void Villain::Attack(){cout << " Villain deals " << m_combat << endl;}

ostream& operator<< (ostream& os, Villain &myVillain){
  cout << myVillain.GetName() << "(hp:" << myVillain.GetHp() << " combat:" << myVillain.GetCombat() << ") " << endl;
    return os;
  }
