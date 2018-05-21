Each element on the periodic table has an electron configuration "address" associated with it. 

RULES:
1. Player must add three 1-block ships.
2. Player must "shoot" by writing the electron configuration in the following format: 
                
                        1s2.2s2.2p6.3s2.3p3 

3. You win if you sink their boat before your boats are sunk.
4. The only exceptions to electron configurations are Chromium ([Ar] 4s1.3d5) and Copper ([Ar] 4s1.3d10). Assume all others follow Aufbau's principle. 

DESIGN DECISIONS:
    - answer key
        map<string element, int atomic#> atomic_numbers;
        map<int atomic#, string config> electron_configs; 
        decided to add a reverse of the map for electron configs and atomic numbers
            so that we can quickly access information during set-up and playing of the game.
            The extra space used is insignificant as at most we have only 118 elements.
        REFACTOR: dynamically determine config based on its atomic number? 
    - players
        player class gets instantiated twice, once for computer AI and once for the user
        player objects instantiated places their ships. organized into a map<string electron_config, bool ship_status>
        REFACTOR: allow to choose if play against comptuer or player2

TODO:
    - use boost::bimap?