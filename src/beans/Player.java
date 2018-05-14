/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package beans;

import bl.Hand;

/**
 *
 * @author Philipp
 */
public class Player {

    private Hand h;
    private int tower;
    private int  wall;
    
    private int bestiary =1;
    private int quarry = 1;
    private int magic = 1;
    
    private int beasts = 0;
    private int bricks = 0;
    private int gems = 0;
    
    private boolean win;
    
    private int wintowerval =0;
    
    public Player() {  //win value
        h = new Hand();
        tower = 50;
        wall = 0;
        wintowerval = 100;
    }

    public Player(int tower, int wall) {
        this.tower = tower;
        this.wall = wall;
        wintowerval = 100;
    }

    public Player(int tower, int wall, int wintowerval) {
        this.tower = tower;
        this.wall = wall;
        this.wintowerval = wintowerval;
    }
    
    
    
    public void usecard(Card c) throws Notusableerror
    {     
        
        switch(c.getType())
        {
            case 1:if(beasts >= c.getRequirement()){ beasts -= c.getRequirement();} break;
             case 2:if(bricks >= c.getRequirement()){ bricks -= c.getRequirement();}break;
              case 3:if(gems >= c.getRequirement()){ gems -= c.getRequirement();};break;
              default: throw new Notusableerror(); 
        }
        
        
//    private int mod_enemy_bestiary;
//    private int mod_enemy_quarry;
//    private int mod_enemy_magic;
//    private int mod_player_bestiary;
//    private int mod_player_quarry;
//    private int mod_player_magic;
//    private int changes_enemy_beats;
//    private int changes_enemy_bricks;
//    private int changes_enemy_gems;
//    private int changes_player_beats;
//    private int changes_player_bricks;
//    private int changes_player_gems;
        
        
            if(c.getDamage_self()!=0)
            {
                healthchange(c.getDamage_self());
            }
            
            //hand von slot verwenden und neue ziehen
    }
    
    public void healthchange(int value)
    {
        
        tower += value; 
        
        if(tower >= wintowerval)
        {
            endgame(true);
        }

        if(tower <= 0)
        {
            endgame(false);
        }
    }
    
    
    public void endgame(boolean w)
    {
        win = w;//... todo falls gewonnen
    }
    

    
class Notusableerror extends Exception
{
    Notusableerror()
    {
        super("Diese karte kann nicht gespielt werden");
    }
}
}
