#include "Game.h"

Game::Game(string f_fileName){
    m_fileName = f_fileName;
}

Game::~Game(){

    for (int i = 0; i < int(m_heroes.size());i++){
        delete m_heroes[i];
    }

    for (int i = 0; i < int(m_villains.size());i++){
        delete m_villains[i];
    }

}

void Game::LoadFile(){

    ifstream myfile(m_fileName); 

    if (myfile.is_open()){

        string HeroVillan, name, desc, hp, combat, rarity, empty;
        int HeroCount = 0;
        int VillanCount = 0;
        
        while(getline(myfile, HeroVillan, '|') and getline(myfile, name, '|') and getline(myfile, desc, '|'), getline(myfile, hp,'|'), getline(myfile, combat,'|'), getline(myfile, rarity,'\n')){
            if (HeroVillan == "HERO"){
                Hero *hero = new Hero(name, desc, stoi(hp), stoi(combat), stoi(rarity));
                HeroCount++;
                m_heroes.push_back(hero);
            }
            
            else{
                Villain *villain = new Villain(name, desc, stoi(hp), stoi(combat), stoi(rarity));
                VillanCount++;          
                m_villains.push_back(villain);
            }
            
        }
        myfile.close();
        
        int totalWizards = HeroCount + VillanCount;
        cout << "Heros Loaded " << HeroCount << " Villan Loaded " << VillanCount << " Total Loaded: " << totalWizards<< endl;
    }
    
    else{
       cout<< "error opening file " << endl;
    }
}

void Game::PrintHeroes(){
    for (int i = 0; i < int(m_heroes.size());i++){
        cout << i+1 << ". " << *m_heroes[i];
    }
}

void Game::PrintVillains(){
    for (int i = 0; i < int(m_villains.size());i++){
        cout << i+1 << ". " << *m_villains[i];
    }
}

void Game::PrintMyHeroes(){
    if (m_myHeroes.IsEmpty()){
        cout << "You have no heroes yet! You should try to acquire some first!" << endl;
        return;
    }
    for (int i = 0; i < int(m_myHeroes.size()); i++){
        cout << i+1 << ". " << *m_myHeroes.operator[](i);
    }
}

void Game::AcquireHero(){
    // constants for rarity
    const int VERY_COMMON = 1;
    const int COMMON = 2;
    const int UNCOMMON = 3;
    const int RARE = 4;
    const int ULTRA_RARE = 5;
    
    int rarity;
    cout << "How rare of a wizard would you like to recruit?:" << endl;
    cout << "1. Very Common (Very High Probability)" << endl;
    cout << "2. Common (High Probability)" << endl;
    cout << "3. Uncommon (Normal Probability)" << endl;
    cout << "4. Rare (Low Probability)" << endl;
    cout << "5. Ultra Rare (Extremely Low Probability)" << endl;
    cin >> rarity;

    while (rarity > 5 or rarity < 0){
        cout << "How rare of a wizard would you like to recruit?:" << endl;
        cout << "1. Very Common (Very High Probability)" << endl;
        cout << "2. Common (High Probability)" << endl;
        cout << "3. Uncommon (Normal Probability)" << endl;
        cout << "4. Rare (Low Probability)" << endl;
        cout << "5. Ultra Rare (Extremely Low Probability)" << endl;
        cin >> rarity;
    }
    int randNum = rand() % 100 + 1;     // num in the range of 1 to 100
    
    switch (rarity)
    {
    case VERY_COMMON:
        cout << "You ask around to see if anyone would be willing to join you." << endl;
        // if the random number is in the range of percentage of 1 to 65
        if (randNum <= RARITY[VERY_COMMON -1]){
            FoundHero(rarity);
        }   
        else{
            cout << "No one would join your cause." << endl;
        }
        break;
    
    case COMMON:
        cout << "You ask around to see if anyone would be willing to join you." << endl;
        // if the random number is in the range of percentage of 1 to 45
        if (randNum <= RARITY[COMMON-1]){
            FoundHero(rarity);
        }   
        else{
            cout << "No one would join your cause." << endl;
        }
        break;
        
    case UNCOMMON:
        cout << "You ask around to see if anyone would be willing to join you." << endl;

        // if the random number is in the range of percentage of 1 to 25
        if (randNum <= RARITY[UNCOMMON-3]){
            FoundHero(rarity);
        }   
        else{
            cout << "No one would join your cause." << endl;
        }
        break;    
    
    case RARE:
        cout << "You ask around to see if anyone would be willing to join you." << endl;

        // if the random number is in the range of percentage of 1 to 10
        if (randNum <= RARITY[RARE-1]){
            FoundHero(rarity);
        }   
        else{
            cout << "No one would join your cause." << endl;
        }
        break;    
    
    case ULTRA_RARE:
        cout << "You ask around to see if anyone would be willing to join you." << endl;

        // if the random number is in the range of percentage of 1 to 5
        if (randNum <= RARITY[ULTRA_RARE-1]){
            FoundHero(rarity);
        }   
        else{
            cout << "No one would join your cause." << endl;
        }
        break;
    
    default:
        break;
    }
}

void Game::FoundHero(int rarity){
    
    int numHeros = int(m_heroes.size());
    bool randHeroNotInMyVector = false;
    
    
    // find a unique wizard with the right rarity
    while (!randHeroNotInMyVector){
        
        int randNumHeroIndex = rand() % numHeros+1;// num in the range of 0 to 230

        // checks if the the wizard is uniqe
        int uniqe = m_myHeroes.Find(m_heroes[randNumHeroIndex]);
        
        // if the wizard is uniqe and the wiard has the same rarity then while loop quits
        if (m_heroes[randNumHeroIndex]->GetRarity() == rarity and uniqe == -1){
            
            // uniqe hero found
            randHeroNotInMyVector = true;

            // add hero to my hero lqueue
            m_myHeroes.Push(m_heroes[randNumHeroIndex]);
            cout << "With some amount of effort, " << m_heroes[randNumHeroIndex]->GetName() << " has agreed to join you!" << endl;

        }    
    }
    
    
}

void Game::MainMenu(){

    const int SEE_ALL_HEROS = 1;
    const int SEE_ALL_VILLAINS = 2;
    const int SEE_YOUR_VILLIANS = 3;
    const int ACQUIRE_NEW_HERO = 4;
    const int TRAIN_HERO = 5;
    const int ENTER_WIZARD_BATTLE = 6;
    const int EXIT = 7;
    
    bool flag = true;

    int choice;

    while (flag){
        
        cout << "What would you like to do?:" << endl;
        cout << "1. See All Heroes" << endl;
        cout << "2. See All Villains" << endl;
        cout << "3. See Your Heroes" << endl;
        cout << "4. Try to Acquire a New Hero" << endl;
        cout << "5. Train a Hero" << endl;
        cout << "6. Enter a Wizard Battle" << endl;
        cout << "7. Exit" << endl;
        cin >> choice;
        // choice = 6;

        switch (choice){
            
            case SEE_ALL_HEROS:
                PrintHeroes();
                break;        
            
            case SEE_ALL_VILLAINS:
                PrintVillains();
                break;
            
            case SEE_YOUR_VILLIANS:
                PrintMyHeroes();
                break;
            
            case ACQUIRE_NEW_HERO:
                AcquireHero();
                break;
            
            case TRAIN_HERO:
	      if (m_myHeroes.IsEmpty() == false){
		TrainHero();
                }
                else{cout << "You have no Heros to enter to train, Aquire some first" << endl;}


                break;

            case ENTER_WIZARD_BATTLE:
                // ensures player has heros to choose from 
                if (m_myHeroes.IsEmpty() == false){
                    Battle();
                }
                else{cout << "You have no Heros to enter to battle, Aquire some first" << endl;}

                break;

            case EXIT:
                flag = false;
                break;
            
            default:
            break;
        }
    }
}

void Game::PrepareVillains(){

    int villainsCount;
    // Gets the number of villains and checks the user input
    cout << "How many villains would you like to battle?" << endl;
    cin >> villainsCount;
        
    while (villainsCount  < 1 or villainsCount > MAX_VILLAINS){
    
        cout << "How many villains would you like to battle? (Enter a number between 1 and 5)" << endl;
        cin >> villainsCount;
    }
    cout << SEP << endl;
    cout << "The enemy wizards stand ready to battle" << endl;

    // while the size of the battle villans is less then the user input num of villans 
    int i = 0;
    while (m_bVillains.size() < villainsCount)    
    {
        int randIndex = rand() % int(m_villains.size())+1; // num in the range of 0 to the number of villains
	
	Villain *villain = new Villain(m_villains.operator[](randIndex)->GetName(),
                                        m_villains.operator[](randIndex)->GetDesc(),
                                        m_villains.operator[](randIndex)->GetHp(),
                                        m_villains.operator[](randIndex)->GetCombat(), 
                                        m_villains.operator[](randIndex)->GetRarity());	
        m_bVillains.Push(villain); //addes that villan to the lqueue
	
	//m_bVillains.Push(m_villains[randIndex]);
	cout << *m_bVillains.operator[](i);
	i++;
    }
    cout << SEP << endl;
}

void Game::PrepareHeroes(){

    int hero;
    cout << "Add from 1 to 5 heroes to your battle roster " << endl;
    cout << "Enter -1 when done" << endl;
    PrintMyHeroes();
    cin >> hero;
    
    
    while (hero != -1 and m_bHeroes.size() < MAX_HEROES){       
        
        if (hero >= 1 and hero <= m_myHeroes.size()){
            int index = hero - 1;
	    // allocate new hero with the same data 
	    Hero *hero = new Hero(m_myHeroes.operator[](index)->GetName(),
				  m_myHeroes.operator[](index)->GetDesc(),
				  m_myHeroes.operator[](index)->GetHp(),
				  m_myHeroes.operator[](index)->GetCombat(), 
				  m_myHeroes.operator[](index)->GetRarity());
            
            m_bHeroes.Push(hero); // add to the battle lqueue
            //m_bHeroes.Push(m_myHeroes.operator[](index));
	}
  
        cout << "Add from 1 to 5 heroes to your battle roster " << endl;
        cout << "Enter -1 when done" << endl;
        PrintMyHeroes(); 
        cin >> hero;

    }
    cout << SEP << endl;
    cout << "The hero wizards stand ready to battle" << endl;
    // prints my battle heros
    for (int i = 0; i < m_bHeroes.size(); i++){
        cout << *m_bHeroes.operator[](i);
    }
    cout << SEP << endl;

}

void Game::Battle(){
    PrepareVillains();
    PrepareHeroes();
    
 
    cout << "Done Preparing" << endl;
    
    // prints out the battle and attack
    cout << m_bHeroes.Front()->GetName() << " VS " << m_bVillains.Front()->GetName() << endl;

    while(m_bHeroes.IsEmpty() == false and m_bVillains.IsEmpty() == false){

        // The Hero attacks                                                                                                                                                 
        cout << m_bHeroes.Front()->GetName() << " waves their wand and screams 'Avadakadavra!' " << endl;

        // subtracts the hp of the villan - the hero combat damage                                                                                                          
        m_bVillains.Front()->SetHp(m_bVillains.Front()->GetHp() - m_bHeroes.Front()->GetCombat());

        // if the villan dies and there is only one villan                                                                                                                  
        if (m_bVillains.Front()->GetHp() <= 0 and m_bVillains.size() == 1){

            // print they are defeated                                                                                                                                      
            cout << m_bVillains.Front()->GetName() << " is defeated" << endl;
            delete m_bVillains.Front();
            m_bVillains.Pop(); // remove villan                                                                                                                             
        }

        // if there are more villans continue the battle                                                                                                                    
        else if (m_bVillains.Front()->GetHp() <= 0 and m_bVillains.size() > 1){

            // print the villan was defated                                                                                                                                 
            cout << m_bVillains.Front()->GetName() << " is defeated" << endl;
            delete m_bVillains.Front();
            m_bVillains.Pop(); // remove villan                                                                                                                             

            cout << "New battle " << m_bHeroes.Front()->GetName() << " VS " << m_bVillains.Front()->GetName() << endl;
            cout << m_bVillains.Front()->GetName() << " waves their evil wand and screams 'hausofhbsa' " << endl;

            // subtracts the hero hp - villans damage                                                                                                                       
            m_bHeroes.Front()->SetHp(m_bHeroes.Front()->GetHp() - m_bVillains.Front()->GetCombat());

            // checks if the villan defeates the Hero                                                                                                                       
            if (m_bHeroes.Front()->GetHp() <= 0){
                // print the hero is defeated                                                                                                                               
                cout << m_bHeroes.Front()->GetName() << " is defeated" << endl;
                delete m_bHeroes.Front();
                m_bHeroes.Pop();

                // checks to see if there are more heros before it startes a new battle                                                                                     
                if (m_bHeroes.IsEmpty() != true){
                    cout << "New battle " << m_bHeroes.Front()->GetName() << " VS " << m_bVillains.Front()->GetName() << endl;
                }

            }
        }

        // if villan survies they attack                                                                                                                                    
        else{
            cout << m_bVillains.Front()->GetName() << " waves their wand and screams 'Sectumsempra!' " << endl;

            // subtracts the hero hp - villans damage                                                                                                                       
            m_bHeroes.Front()->SetHp(m_bHeroes.Front()->GetHp() - m_bVillains.Front()->GetCombat());

            // if the hero dies remove them from the lqueue                                                                                                                 
            if (m_bHeroes.Front()->GetHp() <= 0){

                // prints they are defeated                                                                                                                                 
                cout << m_bHeroes.Front()->GetName() << " is defeated" << endl;
                delete m_bHeroes.Front();
                m_bHeroes.Pop(); // removes them                                                                                                                            

                if (m_bHeroes.IsEmpty() != true){
                    cout << "New Battle" << m_bHeroes.Front()->GetName() << " VS " << m_bVillains.Front()->GetName() << endl;
                }
            }
        }

    }
    // checks who wins
    ResolveBattle();
}

void Game::ResolveBattle(){
        //all heros die, villans won                                                                                                                                                                                                         
  if (m_bHeroes.IsEmpty() == true){
    cout << SEP << endl;
    cout << "Villans have won" << endl;
    cout << SEP << endl;
    for (int i = 0; i < m_bVillains.size();i++){
      delete m_bVillains.operator[](i);
    } 

    // clear the villan lqueue
    m_bVillains.Clear();
  }
    else{
      // Hero wons                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
      cout << SEP << endl;
      cout << "Victory! Heroes have won." << endl;
      cout << SEP << endl;
        for (int i = 0; i < m_bHeroes.size();i++){
            delete m_bHeroes[i];}
	m_bHeroes.Clear();
    }
}

void Game::TrainHero(){

    int hero;
    cout << "Which of your wizards would you like to train?:" << endl;
    PrintMyHeroes();
    cin >> hero;

    while (hero < 0 or hero > m_myHeroes.size())
    {
        cout << "Which of your wizards would you like to train?:" << endl;

        PrintMyHeroes();
        cin >> hero;
    }
    int index = hero-1;

    m_myHeroes.operator[](index)->Train();    
    cout << "Your Hero " << m_myHeroes.operator[](index)->GetName() << " has been trained" << endl;
    cout << m_myHeroes.operator[](index)->GetName() << " combat has increased to " << m_myHeroes.operator[](index)->GetCombat() << endl;


}

