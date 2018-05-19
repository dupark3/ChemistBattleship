Each element on the periodic table has an electron configuration "address" associated with it. 

RULES:
1. Player must add one 3-block ship.
2. Player must "shoot" by writing the electron configuration in the following format: 
                
                        1s2.2s2.2p6.3s2.3p3 
                                OR 
                            [Ne]3s2.3p3

3. You win if you sink their boat before your boats are sunk.
4. The only exceptions to electron configurations are Chromium ([Ar] 4s1 3d5) and Copper ([Ar] 4s1 3d10). Assume all others follow Aufbau's principle. 

DESIGN DECISIONS:
- answer key
    static map<string element, int atomic #> atomic_numbers;
    static map<int atomic #, string config> electron_configs; 
    REFACTOR: dynamically determine config based on its atomic number?

- players
    player class gets instantiated twice, once for computer AI and once for the user
    player objects instantiated places their ships. organized into a map<int atomic #, bool status>
    REFACTOR: allow to choose if play against comptuer or player2