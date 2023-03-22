import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.border.Border;

public class GameSource {
    GameFrame f;

    GameSource() {
        f = new GameFrame();
        this.f = f;
    }

    // ************************************* (1.)GamePanel
    // Class**************************************************************//
    class GamePanel extends JPanel {
        int score = 0;
        boolean flag = false;
        private int gridColumns;
        private int gridRows;
        private int gridCellSize;
        private TetrisBlock block;
        private Color[][] background;
        boolean[][] store;

        private int[][][] arr = {
                { { 1, 0 }, { 1, 0 }, { 1, 1 } }, // L shape
                { { 0, 1 }, { 0, 1 }, { 1, 1 } }, // left sided l shape
                { { 1, 1 }, { 1, 1 } }, // square
                { { 1 }, { 1 }, { 1 }, { 1 } }, // | shape of 4 size
                { { 0, 1 }, { 1, 1 }, { 1, 0 } }, // N shape
                { { 1, 0 }, { 1, 1 }, { 0, 1 } }, // opposite N shape
                { { 1, 0 }, { 1, 1 }, { 1, 0 } } // |- shape
        };

        private Color[] color_arr = {Color.blue, new Color(120, 37, 179), new Color(80, 34, 22), Color.magenta, new Color(80, 134, 22), new Color(180, 34, 22), new Color(100, 179, 179)};

        GamePanel(int columns) {
            this.setBounds(150, 20, 200, 400);
            this.setBackground(Color.lightGray);
            gridColumns = columns;
            gridCellSize = this.getWidth() / gridColumns;
            gridRows = this.getHeight() / gridCellSize;
            background = new Color[gridRows + 2][gridColumns];
            store = new boolean[gridRows + 2][gridColumns + 1];

            for (int i = 0; i < gridRows + 2; i++) {
                for (int j = 0; j <= gridColumns; j++) {
                    store[i][j] = false;
                    if (j == gridColumns)
                        store[i][j] = true;
                }
            }
        }

        public void spawnBlock() {
            Random rand = new Random();
            int option = rand.nextInt(7);
            block = new TetrisBlock(arr[option], color_arr[option]); 
            block.spawn(gridColumns);
        }

        public boolean check_down() {
            int row = block.getY() + 2;
            int col = block.getX();
            int val = col + block.getShape()[0].length, j, i = 0;
            int[][] shape_in_use = block.getShape();
            // System.out.println(col);
            // shape_in_use[shape_in_use.length-1][i]==1 && store[row+1][j]==true
            for (i = 0; i < shape_in_use.length; i++) {
                j = col;
                for (int k = 0; k < shape_in_use[0].length; k++) {
                    if (shape_in_use[i][k] == 1 && store[row + i + 1][j] == true)
                        return true;
                    j++;
                }
                ;

            }
            return false;
        }

        public boolean moveBlockDown() {
            // check_down()==true
            if (checkBottom() == true) {
                moveBlockToBackground();
                check_row();
                return true;
            }
            // System.out.println(block.getY());
            if (check_down() == true) {
                moveBlockToBackground();
                check_row();
                // paintComponent();

                return true;
            }
            block.moveDown();
            repaint();
            return false;
        }

        public boolean check_to_continue() {
            int row_of_interest = block.getY() + 2 + block.getHeight(), col = block.getX();

            for (int i = 0; i < block.getWidth(); i++) {
                if (store[row_of_interest][col + i] == true || store[row_of_interest + 1][col + i] == true)
                    return true;
            }
            return false;

        }

        public void update_score(int row) {
            int i, j;
            score += 5;
            // Graphics gr;
            System.out.println("YOU GOT 5 POINTS:");

            for (i = row; i > 0; i--) {
                for (j = 0; j < gridColumns; j++) {
                    store[i][j] = store[i - 1][j];
                    background[i][j] = background[i - 1][j];
                }
            }
        }

        public void check_row() {
            int row = block.getY() + 2;

            System.out.println(row);
            int i, flag = 0, j;
            // for(i=gridRows+2;i>1;i--)
            // {
            // flag=0;
            // for(j=0;j<gridColumns;j++)
            // {
            // if(store[i][j]==false)
            // {
            // flag=1;
            // break;
            // }
            // if(flag==0)
            // break;
            // }
            // }
            for (j = row; j < row + block.getHeight(); j++) {
                flag = 0;
                for (i = 0; i < gridColumns; i++) {
                    if (store[j][i] == true) {
                        flag += 1;
                        // break;
                    }
                    if (flag == gridColumns)
                        break;
                }
                if (flag == gridColumns)
                    update_score(j);
            }
        }

        private boolean checkBottom() {
            if (block.getBottomEdge() == gridRows) {
                return true;
            }
            return false;
        }

        private void moveBlockToBackground() {
            int[][] shape = block.getShape();
            int h = block.getHeight();
            int w = block.getWidth();
            int xPos = block.getX();
            int yPos = block.getY();
            int myy = yPos + 2;
            // System.out.println(yPos);
            Color color = block.getColor();
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    if (shape[i][j] == 1) {
                        background[i + yPos + 2][j + xPos] = color;
                        store[myy + i][xPos + j] = true;
                    }
                }
            }
        }

        public void drawBlock(Graphics g) {
            for (int i = 0; i < block.getHeight(); i++) {
                for (int j = 0; j < block.getWidth(); j++) {
                    if (block.getShape()[i][j] == 1) {
                        int x = (block.getX() + j) * gridCellSize;
                        int y = (block.getY() + i) * gridCellSize;

                        drawGridSquare(g, block.getColor(), x, y);
                    }
                }
            }
        }

        private void drawBackground(Graphics g) {
            Color color;
            for (int i = 0; i < gridRows; i++) {
                for (int j = 0; j < gridColumns; j++) {
                    color = background[i + 2][j];
                    if (color != null) {
                        int x = j * gridCellSize;
                        int y = i * gridCellSize;
                        drawGridSquare(g, color, x, y);
                    }
                }
            }
        }

        public void drawGridSquare(Graphics g, Color color, int x, int y) {
            g.setColor(color);
            g.fillRect(x, y, gridCellSize, gridCellSize);
            g.setColor(Color.black);
            g.drawRect(x, y, gridCellSize, gridCellSize);
        }

        public void paintComponent(Graphics g) {
            super.paintComponent(g);
            for (int i = 0; i < gridRows; i++) {
                for (int j = 0; j < gridColumns; j++) {
                    g.drawRect(j * gridCellSize, i * gridCellSize, gridCellSize, gridCellSize);
                }
            }
            drawBackground(g);
            drawBlock(g);
        }

        public boolean check_side(int i) {
            int row = block.getY() + 2;
            int col = block.getX();
            int[][] sh = block.getShape();
            if (i == 0) {
                if (col == 0)
                    return true;
                for (int j = 0; j < block.getHeight(); j++) {
                    if (store[row + j][col - 1] == true && sh[j][0] == 1)
                        return true;
                }
                return false;
            } else {
                col = col + sh[0].length - 1;

                for (int j = 0; j < block.getHeight(); j++) {
                    if (store[row + j][col + 1] == true && sh[j][block.getWidth() - 1] == 1)
                        return true;
                }
                return false;
            }
        }

        public void moveBlockRight() {
            if (block.getX() + block.getWidth() == 10)
                return;
            if (check_side(1) == false) {
                block.moveRight(block.getShape());
                repaint();
            }
        }

        public void moveBlockLeft() {
            if (check_side(0) == false) {
                block.moveLeft();
                repaint();
            }

        }

        public void dropBlock() {
            while (check_down() != true) {
                block.moveDown();
                if (checkBottom() == true) {
                    // moveBlockToBackground();
                    check_row();
                    break;
                }
            }
            // flag=true;
            // moveBlockToBackground();

            repaint();
        }

        public void rotateBlock() {
            int s[][] = block.getShape();
            block.rotate();
            if (check_behind()) {
                block.shape = s;
            }
            repaint();
        }

        public boolean check_behind() {
            int row = block.getY() + 2;
            int col = block.getX();
            int val = col + block.getShape()[0].length, j, i = 0;
            int[][] shape_in_use = block.getShape();
            // System.out.println(col);
            // shape_in_use[shape_in_use.length-1][i]==1 && store[row+1][j]==true
            for (i = 0; i < shape_in_use.length; i++) {
                j = col;
                for (int k = 0; k < shape_in_use[0].length; k++) {
                    if (shape_in_use[i][k] == 1 && store[row + i][j] == true)
                        return true;
                    j++;
                }

            }
            return false;
        }
    }

    // *************************************(2.) GameThread
    // Class**************************************************************//

    class GameThread extends Thread // Child class of Thread class (inbuilt)
    {
        private GamePanel panel;
        GameFrame fr;

        // boolean flag = false;
        GameThread(GamePanel panel, GameFrame fr) // Creating a constructor that takes an object of GamePanel class as
                                                  // parameter
        {
            this.panel = panel; // Initializing Panel attribute of GameThread class to Panel Object of GamePanel
                                // class
            this.fr = fr;
        }

        public void run() // Method overloading which works as default constructor to run the game
        {
            while (true) {
                panel.spawnBlock(); // Using spawnBlock method of GamePanel class to generate figures
                // panel.check_to_continue()
                if (panel.check_down() == true) {
                    break;
                }
                // panel.flag=false;
                // Using moveBlockDown method of GamePanel class to move the figures in downward
                // direction
                while (panel.moveBlockDown() == false) // Iterating an infinite loop for this purpose
                {

                    try {
                        Thread.sleep(400); // Pausing the blocks for 0.4 sec on each cell
                    } catch (InterruptedException e) // Creating alternative command in case any error occurs
                    {
                        e.printStackTrace();
                    }
                }

            }
            // panel.setVisible(false);
            // flag = true;
            fr.dispose();
            endGame(panel.score);
            System.out.println("Game Over!");
            System.out.println("your score: " + panel.score);
        }

        public void endGame(int sc) {
            Border border = BorderFactory.createLineBorder(new Color(192, 192, 192), 3);

            JLabel label1 = new JLabel();
            JLabel label2 = new JLabel();
            JLabel label3 = new JLabel();
            JFrame jf = new JFrame();

            label1.setText("Game ended");
            label1.setBounds(160, 50, 100, 30);
            label1.setBorder(border);
            label1.setVisible(true);

            label2.setText("Your Score");
            label2.setBounds(10, 50, 100, 30);
            label2.setBorder(border);
            label2.setVisible(true);

            String s = String.valueOf(sc);

            label3.setText(s);
            label3.setBounds(10, 90, 100, 30);
            label3.setBorder(border);
            label3.setVisible(true);

            jf.add(label1);
            jf.add(label2);
            jf.add(label3);

            jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Setting close option for the game window
            // this.setLocationRelativeTo(null); // Setting relative location of the game
            // panel to the screen
            jf.setSize(500, 500); // Setting dimensions of panel
            jf.setTitle("Score Card");
            jf.setLayout(null); // Initializing layout to null
            jf.setResizable(false);
            jf.setVisible(true);
        }
    }

    // ************************************* (3.) GameFrame
    // Class**************************************************************//
    class GameFrame extends JFrame // Game Frame class inherited from inbuilt JFrame class
    {
        GamePanel panel; // Creating an object of GamePanel class

        GameFrame() // Creating a constructor for initializing the attributes of game panel
        {
            panel = new GamePanel(10);
            this.add(panel);
            this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Setting close option for the game window
            // this.setLocationRelativeTo(null); // Setting relative location of the game
            // panel to the screen
            this.setSize(500, 500); // Setting dimensions of panel
            this.setTitle("Tetris Game");
            this.setLayout(null); // Initializing layout to null
            this.setResizable(false);
            this.setVisible(true);

            // Calling the class methods defined later
            startGame();
            initControls();
        }

        public void startGame() {
            new GameThread(panel, this).start(); // creating a new object of GameThread class
        }

        // we are using the utility functions for down,rotate,right,left by help of key
        // bindings
        public void initControls() { // Defining game controls in the initControls method

            InputMap im = this.getRootPane().getInputMap(); // Creating 'im' object of InputMap Class (inbuilt)
            ActionMap am = this.getRootPane().getActionMap();// Creating 'am' object of ActionMap Class (inbuilt)
            // input maps contains key strokes
            // keystrokes controls the action of keyboard and key press.

            // Binding the keystrokes to Objects using 'put' method of InputMap class
            // calling the getKeyStroke static method from KeyStroke Class.
            im.put(KeyStroke.getKeyStroke("RIGHT"), "right"); // right is object type
            im.put(KeyStroke.getKeyStroke("LEFT"), "left");
            im.put(KeyStroke.getKeyStroke("UP"), "up");
            im.put(KeyStroke.getKeyStroke("DOWN"), "down");

            // Associating the arrow keys to respective actions in the game using 'put'
            // method of ActionMap class
            am.put("right", new AbstractAction() { // this cannot be instansiated so it is a abstract class
                // abstract class cannot be instanciated it can be extended.
                public void actionPerformed(ActionEvent e) {
                    panel.moveBlockRight();
                } // we are here using anonymous class here abstract action is implemented here
            });
            am.put("left", new AbstractAction() {
                public void actionPerformed(ActionEvent e) {
                    panel.moveBlockLeft();
                }
            });
            am.put("up", new AbstractAction() {
                public void actionPerformed(ActionEvent e) {
                    panel.rotateBlock();
                }
            });
            am.put("down", new AbstractAction() {
                public void actionPerformed(ActionEvent e) {
                    panel.dropBlock();
                }
            });
        }
    }

}
