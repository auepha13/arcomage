/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package database;

/**
 *
 * @author Stefan
 */
public enum DB_Stmt_Type {
    GetAllCards("SELECT * FROM card"),
    InsertCardOLD("INSERT INTO card (card_id, name, description, picture_path, type, requirement,"
            + " damage_self, damage_enemy) "
            + "VALUES(?,?,?,?,?,?,?,?);"),
    InsertCard("INSERT INTO card (name, description, type, requirement, additional_turn, discardable, damage_enemy,damage_self)"
            + " VALUES (?,?,?,?,?,?,?,?)"),
    InsertChanges("INSERT INTO changes (beasts, bricks, gems, tower, wall) VALUES (?,?,?,?,?)"),
    InsertMod("INSERT INTO mod (bestiary, quarry, magic) VALUES (?,?,?)"),
    DeleteDoubleChanges("DELETE FROM changes\n"
            + "WHERE  changes_id NOT IN (SELECT MAX(changes_id)\n"
            + "FROM   changes\n"
            + "GROUP  BY beasts,\n"
            + "bricks,\n"
            + "gems\n"
            + "HAVING MAX(changes_id) IS NOT NULL);\n"
            + "DELETE  FROM changes;"),
    CardUpdate("UPDATE card SET mod_enemy = ?, mod_player = ?, "
            + "changes_enemy = ?, changes_player = ?\n"
            + "WHERE card_id = ?"),
    GetChangesID("SELECT MIN(changes_id) \n"
            + "FROM changes\n"
            + "WHERE beasts = ? AND bricks = ? AND gems = ? AND tower = ? AND wall = ?;"),
    GetModID("SELECT MIN(mod_id)\n"
            + "FROM mod\n"
            + "WHERE bestiary = ? AND quarry = ? AND magic = ?"),
    SetPicture("UPDATE card SET picture = ? \n"
            + "WHERE card_id = ?"),
    GetCardCount("SELECT COUNT(*) FROM card;"),
    GetCard("SELECT * "
            + "FROM card ca INNER JOIN mod moe ON ca.mod_enemy = moe.mod_id "
            + "INNER JOIN mod mop ON ca.mod_player = mop.mod_id "
            + "INNER JOIN changes che ON ca.changes_enemy = che.changes_id "
            + "INNER JOIN changes chp ON ca.changes_player = chp.changes_id "
            + "WHERE ca.card_id = ?");

    private String pStatString;

    private DB_Stmt_Type(String pStat) {
        this.pStatString = pStat;
    }

    public String getpStatString() {
        return pStatString;
    }

}
