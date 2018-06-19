/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package gui;

import beans.Player;
import beans.Playercard;
import clientserver.ArcoClient;
import database.DB_Access;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Philipp
 */
public class ClientGUI extends javax.swing.JFrame {

    /**
     * Creates new form GUI
     */
    private ArcoClient c;
    private int playernr = 0;
    private Player p = null;
    //private Gamestate gs;
    private ClientThread ct;

    public ClientGUI(int nr) {
        initComponents();
        setplayernr(nr);

        c = new ArcoClient();
        try {
            actplayer(c.sendRequest(playernr));
        } catch (IOException ex) {
            Logger.getLogger(ClientGUI.class.getName()).log(Level.SEVERE, null, ex);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(ClientGUI.class.getName()).log(Level.SEVERE, null, ex);
        }
        ct = new ClientThread();
        ct.start();
    }

    private ClientGUI() {
        // throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    public void setplayernr(int nr) {
        playernr = nr;
        lbplayer.setText("Player " + playernr);
    }

    private void actplayer(Player p) {

        //as player die werte setzten zb. quarry
        bt1.setText(+p.getHand()[0].getRequirement()+" "+ p.getHand()[0].getDescription());//beschreibung hinzufügen
//        System.out.println(p.getHand()[0].getName());
//        System.out.println(p.getHand()[0].getDescription());
//        System.out.println("Enemy_Tower:"+p.getHand()[0].getChanges_enemy_tower());
//        System.out.println("Enemy_Wall:"+p.getHand()[0].getChanges_enemy_wall());
//        System.out.println("Enemy_Damage:"+p.getHand()[0].getDamage_enemy());
//        System.out.println("Player_Tower:"+p.getHand()[0].getChanges_player_tower());
//        System.out.println("Player_Wall:"+p.getHand()[0].getChanges_player_wall());

        bt2.setText(p.getHand()[1].getName() + " " + p.getHand()[1].getDescription());
        bt3.setText(p.getHand()[2].getName() + " " + p.getHand()[2].getDescription());
        bt4.setText(p.getHand()[3].getName() + " " + p.getHand()[3].getDescription());
        bt5.setText(p.getHand()[4].getName() + " " + p.getHand()[4].getDescription());
        bt6.setText(p.getHand()[5].getName() + " " + p.getHand()[5].getDescription());

        lbbricks.setText("Bricks:" + p.getBricks() + "/ Quarry:" + p.getQuarry());
        lbgems.setText("Gems:" + p.getGems() + "/ Magic:" + p.getMagic());
        lbbeasts.setText("Beasts:" + p.getBeasts() + "/ Beasiary:" + p.getBestiary());

        lbwall.setText("Wall:" + p.getWall());
        //System.out.println(p.getWall());
        lbtower.setText("Tower:" + p.getTower());

        lbwall2.setText("Wall:" + p.getWall2());
        lbtower2.setText("Tower:" + p.getTower2());

        lbbricks2.setText("Bricks:" + p.getBricks2() + "/ Quarry:" + p.getQuarry2());
        lbgems2.setText("Gems:" + p.getGems2() + "/ Magic:" + p.getMagic2());
        lbbeasts2.setText("Beasts:" + p.getBeasts2() + "/ Beasiary:" + p.getBestiary2());

    }

    //thread machen!!!
    class ClientThread extends Thread {

        @Override
        public void run() {
            while (!interrupted()) {
                try {
                    sleep(100);
                } catch (InterruptedException ex) {
                    System.out.println("wait fehler");
                }

                try {
                    p = c.sendRequest(playernr);
                } catch (IOException ex) {
                    Logger.getLogger(ClientGUI.class.getName()).log(Level.SEVERE, null, ex);
                } catch (ClassNotFoundException ex) {
                    Logger.getLogger(ClientGUI.class.getName()).log(Level.SEVERE, null, ex);
                }
                actplayer(p);
                //System.out.println(p.getPlayernr());
                if (playernr != p.getActualplayer()) {
                    bt1.setEnabled(false);
                    bt2.setEnabled(false);
                    bt3.setEnabled(false);
                    bt4.setEnabled(false);
                    bt5.setEnabled(false);
                    bt6.setEnabled(false);
                } else {
                    //if....
                    //buton aus, wenn zu wenig resoucen
                    bt1.setEnabled(true);
                    bt2.setEnabled(true);
                    bt3.setEnabled(true);
                    bt4.setEnabled(true);
                    bt5.setEnabled(true);
                    bt6.setEnabled(true);
                }

            }
        }
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jLabel1 = new javax.swing.JLabel();
        jPanel2 = new javax.swing.JPanel();
        lbplayer = new javax.swing.JLabel();
        jLabel4 = new javax.swing.JLabel();
        jLabel5 = new javax.swing.JLabel();
        jLabel7 = new javax.swing.JLabel();
        lbbricks = new javax.swing.JLabel();
        jLabel10 = new javax.swing.JLabel();
        jLabel11 = new javax.swing.JLabel();
        lbbricks2 = new javax.swing.JLabel();
        lbgems = new javax.swing.JLabel();
        lbwall = new javax.swing.JLabel();
        lbwall2 = new javax.swing.JLabel();
        lbgems2 = new javax.swing.JLabel();
        lbbeasts = new javax.swing.JLabel();
        lbtower = new javax.swing.JLabel();
        lbtower2 = new javax.swing.JLabel();
        lbbeasts2 = new javax.swing.JLabel();
        jPanel1 = new javax.swing.JPanel();
        bt1 = new javax.swing.JButton();
        bt2 = new javax.swing.JButton();
        bt3 = new javax.swing.JButton();
        bt4 = new javax.swing.JButton();
        bt5 = new javax.swing.JButton();
        bt6 = new javax.swing.JButton();

        jLabel1.setText("jLabel1");

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        getContentPane().setLayout(new java.awt.GridLayout(2, 0));

        jPanel2.setLayout(new java.awt.GridLayout(4, 4));

        lbplayer.setText("Player");
        jPanel2.add(lbplayer);
        jPanel2.add(jLabel4);
        jPanel2.add(jLabel5);

        jLabel7.setText("Enemy");
        jPanel2.add(jLabel7);

        lbbricks.setText("Bricks/Quarry:");
        jPanel2.add(lbbricks);
        jPanel2.add(jLabel10);
        jPanel2.add(jLabel11);

        lbbricks2.setText("Bricks/Quarry:");
        jPanel2.add(lbbricks2);

        lbgems.setText("Gems/Magic:");
        jPanel2.add(lbgems);

        lbwall.setText("Wall:");
        jPanel2.add(lbwall);

        lbwall2.setText("Wall:");
        jPanel2.add(lbwall2);

        lbgems2.setText("Gems/Magic:");
        jPanel2.add(lbgems2);

        lbbeasts.setText("Beasts/Beastiary:");
        jPanel2.add(lbbeasts);

        lbtower.setText("Tower:");
        jPanel2.add(lbtower);

        lbtower2.setText("Tower:");
        jPanel2.add(lbtower2);

        lbbeasts2.setText("Beasts/Beastiary:");
        jPanel2.add(lbbeasts2);

        getContentPane().add(jPanel2);

        jPanel1.setLayout(new java.awt.GridLayout(1, 0));

        bt1.setText("1");
        bt1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                bt1ActionPerformed(evt);
            }
        });
        jPanel1.add(bt1);

        bt2.setText("2");
        bt2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                bt2ActionPerformed(evt);
            }
        });
        jPanel1.add(bt2);

        bt3.setText("3");
        bt3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                bt3ActionPerformed(evt);
            }
        });
        jPanel1.add(bt3);

        bt4.setText("4");
        bt4.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                bt4ActionPerformed(evt);
            }
        });
        jPanel1.add(bt4);

        bt5.setText("5");
        bt5.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                bt5ActionPerformed(evt);
            }
        });
        jPanel1.add(bt5);

        bt6.setText("6");
        bt6.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                bt6ActionPerformed(evt);
            }
        });
        jPanel1.add(bt6);

        getContentPane().add(jPanel1);

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void bt1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_bt1ActionPerformed
        try {
            c.sendRequest(new Playercard(0, playernr));
        } catch (IOException ex) {
            Logger.getLogger(ClientGUI.class.getName()).log(Level.SEVERE, null, ex);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(ClientGUI.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_bt1ActionPerformed

    private void bt2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_bt2ActionPerformed
        try {
            c.sendRequest(new Playercard(1, playernr));
        } catch (IOException ex) {
            Logger.getLogger(ClientGUI.class.getName()).log(Level.SEVERE, null, ex);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(ClientGUI.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_bt2ActionPerformed

    private void bt3ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_bt3ActionPerformed
        try {
            c.sendRequest(new Playercard(2, playernr));
        } catch (IOException ex) {
            Logger.getLogger(ClientGUI.class.getName()).log(Level.SEVERE, null, ex);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(ClientGUI.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_bt3ActionPerformed

    private void bt4ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_bt4ActionPerformed
        try {
            c.sendRequest(new Playercard(3, playernr));
        } catch (IOException ex) {
            Logger.getLogger(ClientGUI.class.getName()).log(Level.SEVERE, null, ex);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(ClientGUI.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_bt4ActionPerformed

    private void bt5ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_bt5ActionPerformed
        try {
            c.sendRequest(new Playercard(4, playernr));
        } catch (IOException ex) {
            Logger.getLogger(ClientGUI.class.getName()).log(Level.SEVERE, null, ex);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(ClientGUI.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_bt5ActionPerformed

    private void bt6ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_bt6ActionPerformed
        try {
            c.sendRequest(new Playercard(5, playernr));
        } catch (IOException ex) {
            Logger.getLogger(ClientGUI.class.getName()).log(Level.SEVERE, null, ex);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(ClientGUI.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_bt6ActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(ClientGUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(ClientGUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(ClientGUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(ClientGUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new ClientGUI().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton bt1;
    private javax.swing.JButton bt2;
    private javax.swing.JButton bt3;
    private javax.swing.JButton bt4;
    private javax.swing.JButton bt5;
    private javax.swing.JButton bt6;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel10;
    private javax.swing.JLabel jLabel11;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel jLabel7;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JLabel lbbeasts;
    private javax.swing.JLabel lbbeasts2;
    private javax.swing.JLabel lbbricks;
    private javax.swing.JLabel lbbricks2;
    private javax.swing.JLabel lbgems;
    private javax.swing.JLabel lbgems2;
    private javax.swing.JLabel lbplayer;
    private javax.swing.JLabel lbtower;
    private javax.swing.JLabel lbtower2;
    private javax.swing.JLabel lbwall;
    private javax.swing.JLabel lbwall2;
    // End of variables declaration//GEN-END:variables
}
